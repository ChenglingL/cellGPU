#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "periodicBoundaries.h"
#include "GlassyDynModelDatabase.h"
#include "testModelDatabase.h"


/*!
This file compiles to produce an executable that can be used to reproduce the timing information
in the main cellGPU paper. It sets up a simulation that takes control of a voronoi model and a simple
model of active motility
NOTE that in the output, the forces and the positions are not, by default, synchronized! The NcFile
records the force from the last time "computeForces()" was called, and generally the equations of motion will 
move the positions. If you want the forces and the positions to be sync'ed, you should call the
Voronoi model's computeForces() funciton right before saving a state.
*/

/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 100; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 5; //number of time steps to run after initialization
    int initSteps = 100; //number of initialization steps

    double dt = 0.01; //the time step size
    double p0 = 3.8;  //the preferred perimeter
    double a0 = 1.0;  // the preferred area
    double T = 0.1;  // the temperature
    int Nchain = 4;     //The number of thermostats to chain together
    int id = 0;      //The index of different configuration

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 't': tSteps = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 'i': initSteps = atoi(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'a': a0 = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'x': id = atof(optarg); break; //indentify different simulations
            case '?':
                    if(optopt=='c')
                        std::cerr<<"Option -" << optopt << "requires an argument.\n";
                    else if(isprint(optopt))
                        std::cerr<<"Unknown option '-" << optopt << "'.\n";
                    else
                        std::cerr << "Unknown option character.\n";
                    return 1;
            default:
                       abort();
        };

    clock_t t1,t2; //clocks for timing information
    bool reproducible = false; // if you want random numbers with a more random seed each run, set this to false
    //check to see if we should run on a GPU
    bool initializeGPU = true;
    bool gpu = chooseGPU(USE_GPU);
    if (!gpu)
        initializeGPU = false;

    char dataname[256];
    double equilibrationTime = dt*initSteps;
    sprintf(dataname,"/home/chengling/Research/Project/Cell/AnalyticalG/data/N%i/derivativeTest/CPUtest_N%i_p%.3f_T%.8f_%i.nc",numpts,numpts,p0,T,id);
    shared_ptr<testModelDatabase> ncdat=make_shared<testModelDatabase>(numpts,dataname,NcFile::Replace);


    cout << "initializing a system of " << numpts << " cells at temperature " << T << endl;
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);

    //define a voronoi configuration with a quadratic energy functional
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,a0,p0,reproducible,initializeGPU);

    vector<double2> MixedPre; // Vector to store double2 elements

    //set the system to be 50:50 mixed and a0/a1=4/3
    // for (int i = 0; i < numpts; ++i) {
    //     if (i < numpts/2) {
    //         double2 element1;
    //         element1.x = 1.0;
    //         element1.y = p0 * 1.0;
    //         MixedPre.push_back(element1);
    //     } else {
    //         double2 element2;
    //         element2.x = 0.75;
    //         element2.y = p0 * sqrt(0.75);
    //         MixedPre.push_back(element2);
    //     }
    // }
    // voronoiModel->setCellPreferences(MixedPre);
    //voronoiModel->setCellPreferencesWithRandomAreas(p0,0.8,1.2);

    voronoiModel->setCellVelocitiesMaxwellBoltzmann(T);
    nvt->setT(T);

    //combine the equation of motion and the cell configuration in a "Simulation"
    SimulationPtr sim = make_shared<Simulation>();

    PeriodicBoxPtr newbox = make_shared<periodicBoundaries>(sqrt(numpts),sqrt(numpts));
    sim->setBox(newbox);

    sim->setConfiguration(voronoiModel);
    sim->addUpdater(nvt,voronoiModel);
    //set the time step size
    sim->setIntegrationTimestep(dt);
    //initialize Hilbert-curve sorting... can be turned off by commenting out this line or seting the argument to a negative number
    //sim->setSortPeriod(initSteps/10);
    //set appropriate CPU and GPU flags
    sim->setCPUOperation(!initializeGPU);
    if (!gpu)
        sim->setOmpThreads(abs(USE_GPU));
    sim->setReproducible(reproducible);

    //run for a few initialization timesteps
    printf("starting running case %i\n", id);
    //the reporting of the force should yield a number that is numerically close to zero.

    //run for additional timesteps, compute dynamical features, and record timing information
    dynamicalFeatures dynFeat(voronoiModel->returnPositions(),voronoiModel->Box);
    t1=clock();
//    cudaProfilerStart();
    for(long long int ii = 0; ii < tSteps; ++ii)
        {
        //voronoiModel->computeGeometry();
        //cout <<"d2Edg2"<< voronoiModel->getd2Edgammadgamma()<<endl;
        if (ii % 1000 == 0){
            ncdat->writeState(voronoiModel);
        }
        
        //printf("time_step: %i *0.001 \t energy %f \t msd %f \t overlap %f\n", ii, voronoiModel->computeEnergy(),dynFeat.computeMSD(voronoiModel->returnPositions()),dynFeat.computeOverlapFunction(voronoiModel->returnPositions()));
        sim->performTimestep();
        };
//    cudaProfilerStop();
    t2=clock();
    //printf("final state:\t\t energy %f \t msd %f \t overlap %f\n",voronoiModel->computeEnergy(),dynFeat.computeMSD(voronoiModel->returnPositions()),dynFeat.computeOverlapFunction(voronoiModel->returnPositions()));
    double steptime = (t2-t1)/(double)CLOCKS_PER_SEC/tSteps;
    cout << "timestep ~ " << steptime << " per frame; " << endl;

    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
