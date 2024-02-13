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
#include "twoValuesDatabase.h"


/*!
This .cpp calculate the translational and orientational order parameters to indentify the phase of 
the systems as in 2d melting. The time information of SISFCRSISF.nc is in the file of orientatoinal
order parameter.
*/

/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 100; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 1000000; //number of time steps to run after initialization
    int initSteps = 100; //number of initialization steps
    double tauEstimate = 100.; //number of initialization steps

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
            case 's': tauEstimate = atof(optarg); break;
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

    initSteps=max(1000/dt,floor(10*tauEstimate/dt));
    char saveDirName[256];
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/localTest/2DmeltingPhase/N%i/",numpts);
    char orientationDataname[256];
    char translationDataname[256];
    sprintf(orientationDataname,"%sorientationReIm_N%i_p%.3f_T%.8f_%i.nc",saveDirName,numpts,p0,T,id);
    sprintf(translationDataname,"%stimeTranslation_N%i_p%.3f_T%.8f_%i.nc",saveDirName,numpts,p0,T,id);
    shared_ptr<twoValuesDatabase> orientational=make_shared<twoValuesDatabase>(orientationDataname,NcFile::Replace);
    shared_ptr<twoValuesDatabase> translational=make_shared<twoValuesDatabase>(translationDataname,NcFile::Replace);
    cout<<"Order parameters at p0="<<p0<<" T="<<T<<" for configuration "<<id<<endl;
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);

    //define a voronoi configuration with a quadratic energy functional
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,a0,p0,reproducible,initializeGPU);

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

    //the reporting of the force should yield a number that is numerically close to zero.
    voronoiModel->reportMeanCellForce(false);

//    cudaProfilerStart();
    t1=clock();
    for(long long int ii = 0; ii < initSteps; ++ii)
        {
        sim->performTimestep();
        };
    structuralFeatures strucFeat(voronoiModel->Box);

    for(long long int ii = 0; ii < tSteps; ++ii)
        {
        //voronoiModel->computeGeometry();
        //cout <<"d2Edg2"<< voronoiModel->getd2Edgammadgamma()<<endl;
        if (ii % 100 == 0)
            {
            voronoiModel->enforceTopology();
            double2 psi;
            psi=strucFeat.computeBondOrderParameter(voronoiModel->returnPositions(),voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx);
            std::vector<double2> posdat(numpts);
            ArrayHandle<double2> h_p(voronoiModel->returnPositions());
            for (int ii = 0; ii < numpts; ++ii)
            {
                int pidx = voronoiModel->tagToIdx[ii];
                double px = h_p.data[pidx].x;
                double py = h_p.data[pidx].y;
                posdat[ii].x = px;
                posdat[ii].y = py;
            }
            translational->writeValues(voronoiModel->currentTime,strucFeat.computeTranslationalOrderParameter(posdat));
            orientational->writeValues(psi.x,psi.y);
            }
        sim->performTimestep();
        };
//    cudaProfilerStop();
    t2=clock();
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
