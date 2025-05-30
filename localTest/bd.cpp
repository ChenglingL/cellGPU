#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "brownianParticleDynamics.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "periodicBoundaries.h"
#include "GlassyDynModelDatabase.h"


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
    double Mu = 1.0; 

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
            case 'm': Mu = atof(optarg); break;
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

    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. "0.1" will save 10 states per decade of time
    char dataname[256];
    sprintf(dataname,"../../data/N1024/bd_N%i_p%.3f_T%.8f_%i.nc",numpts,p0,T,id);
    char overlapname[256];
    char cageRelativeSISFname[256];
    sprintf(overlapname,"../../data/N1024/overlapBD_N%i_p%.3f_T%.8f_%i.csv",numpts,p0,T,id);
    sprintf(cageRelativeSISFname,"../../data/N1024/cageRelativeSISFBD_N%i_p%.3f_T%.8f_%i.csv",numpts,p0,T,id);
    shared_ptr<GlassyDynModelDatabase> ncdat=make_shared<GlassyDynModelDatabase>(numpts,dataname,NcFile::Replace);

    shared_ptr<brownianParticleDynamics> bd = make_shared<brownianParticleDynamics>(numpts);
    bd->setT(T);
    bd->setMu(Mu);


    //define a voronoi configuration with a quadratic energy functional
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,a0,p0,reproducible,initializeGPU);

    //voronoiModel->setCellPreferencesWithRandomAreas(p0,0.8,1.2);

    voronoiModel->setCellVelocitiesMaxwellBoltzmann(T);

    //combine the equation of motion and the cell configuration in a "Simulation"
    SimulationPtr sim = make_shared<Simulation>();

    PeriodicBoxPtr newbox = make_shared<periodicBoundaries>(sqrt(numpts),sqrt(numpts));
    sim->setBox(newbox);

    sim->setConfiguration(voronoiModel);
    sim->addUpdater(bd,voronoiModel);
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

    //the reporting of the force should yield a number that is numerically close to zero.
    voronoiModel->reportMeanCellForce(false);

    //store the overlap function from initSteps to tSteps
    std::vector<double> overlapdat(tSteps-initSteps);
    std::vector<double> cageRelativeSISFdat(tSteps-initSteps);
//    cudaProfilerStart();
    for(long long int ii = 0; ii < initSteps; ++ii)
        {
        //voronoiModel->computeGeometry();
        //cout <<"d2Edg2"<< voronoiModel->getd2Edgammadgamma()<<endl;
        if (ii % 100 == 0){
            ncdat->writeState(voronoiModel);
        }
        sim->performTimestep();
        };
    dynamicalFeatures dynFeat(voronoiModel->returnPositions(),voronoiModel->Box);
    dynFeat.setCageNeighbors(voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx);
    int overlapidx = 0;
    for(long long int ii = initSteps; ii < tSteps; ++ii)
        {
        //voronoiModel->computeGeometry();
        //cout <<"d2Edg2"<< voronoiModel->getd2Edgammadgamma()<<endl;
        if (ii % 100 == 0){
            ncdat->writeState(voronoiModel);
            overlapdat[overlapidx] = dynFeat.computeOverlapFunction(voronoiModel->returnPositions());
            cageRelativeSISFdat[overlapidx] = dynFeat.computeCageRelativeSISF(voronoiModel->returnPositions());
            overlapidx ++;
        }
        sim->performTimestep();
        };
//    cudaProfilerStop();

    //save the overlap to a csv file
    std::ofstream outFile1(overlapname);
    if (outFile1.is_open()) {
        for (int i = 0; i < overlapdat.size(); ++i) {
            outFile1 << overlapdat[i];
            if (i != overlapdat.size() - 1) {
                outFile1 << ','; // Add a comma if it's not the last element
            }
        }
        outFile1.close();
        std::cout << "Vector saved to " << overlapname << " successfully." << std::endl;
    } else {
        std::cerr << "Unable to open file." << std::endl;
    };

    std::ofstream outFile2(cageRelativeSISFname);
    if (outFile2.is_open()) {
        for (int i = 0; i < cageRelativeSISFdat.size(); ++i) {
            outFile2 << cageRelativeSISFdat[i];
            if (i != cageRelativeSISFdat.size() - 1) {
                outFile2 << ','; // Add a comma if it's not the last element
            }
        }
        outFile2.close();
        std::cout << "Vector saved to " << cageRelativeSISFname << " successfully." << std::endl;
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }

    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
