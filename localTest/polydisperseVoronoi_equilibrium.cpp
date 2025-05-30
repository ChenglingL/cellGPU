#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "analysisPackage.h"


/*!
 This file generates high-temperture (T=0.2) configurations of polydisperse configurations
 to be loaded and used as initial configurations for future studies
*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 200; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 200000; //number of time steps to run after initialization
    int initSteps = 100000; //number of initialization steps 1000\tau

    double dt = 0.01; //the time step size
    double p0 = 3.8;  //the preferred perimeter
    double a0 = 1.0;  // the preferred area
    double T = 0.1;  // the temperature
    int Nchain = 4;     //The number of thermostats to chain together
    int Nsave = 10;   //save every 100\tau
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
    sprintf(dataname,"/home/chengling/Research/Project/Cell/glassAging/fluidConfigurations/polydisperseFluidConfigurations_N%i_TEq%.8f_p%.5f.nc",numpts,T,p0);
    nvtModelDatabase ncdat(numpts,dataname,NcFile::Replace);

    cout << "initializing a system of " << numpts << " cells at temperature " << T << endl;

    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);

    for (int i = 0; i < Nsave; i++)
    {
        //define a voronoi configuration with a quadratic energy functional
        shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,a0,p0,reproducible,initializeGPU);
        voronoiModel->setCellPreferencesWithRandomAreas(p0,0.8,1.2);

        voronoiModel->setCellVelocitiesMaxwellBoltzmann(T);
        nvt->setT(T);

        //combine the equation of motion and the cell configuration in a "Simulation"
        SimulationPtr sim = make_shared<Simulation>();
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
        printf("starting initialization\n");
        for(long long int ii = 0; ii < initSteps; ++ii)
            {
            sim->performTimestep();
            };
        printf("Finished with initialization\n");

        ncdat.writeState(voronoiModel);
    }


    
    
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
