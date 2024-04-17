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
#include <filesystem>


/*!
This .cpp is to calculate the sigmaxx and sigmaYY. This is specificly for production runs.
*/

/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 100; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 1000000; //number of time steps to run after initialization
    double tauEstimate = 100.; //number of initialization steps

    double equilibrationWaitingTimeMultiple = 10.0;
    double numberOfRelaxationTimes =10.0;
    int numberofDerivatives = 50000;

    double dt = 0.01; //the time step size
    double p0 = 3.8;  //the preferred perimeter
    double a0 = 1.0;  // the preferred area
    double T = 0.1;  // the temperature
    int Nchain = 4;     //The number of thermostats to chain together
    int id = 0;      //The index of different configuration
    double KA = 1.0; //largest k for Fs

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:k:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'a': a0 = atof(optarg); break;
            case 's': tauEstimate = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'k': KA = atof(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': equilibrationWaitingTimeMultiple = atof(optarg); break;
            case 'm': numberOfRelaxationTimes = atof(optarg); break;
            case 'r': id = atof(optarg); break; //indentify different simulations
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

    long long int equilibrationTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    //set the max time to be 20000000 so the simulation can run 48h in the NCSADelta
    long long int runTimesteps = max(floor(10000/dt),floor((tauEstimate * numberOfRelaxationTimes)/ dt));
    cout << "equilibration timesteps = " << equilibrationTimesteps << ", data collecting timesteps = " << runTimesteps << endl;

    //set the spacing for saving instantaneous states
    long long int spacingofInstantaneous = floor(runTimesteps/10);
    int spacingofDerivative = runTimesteps/(numberofDerivatives);
    if (spacingofDerivative<1){spacingofDerivative=1;};



    char saveDirName[256];
    char loadfolder[256];
    sprintf(saveDirName,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/tauAlphaData/p%.3f/",numpts,p0);
    sprintf(loadfolder,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/productionRuns/p%.3f/",numpts,p0);
    char stressTensorDataname[256];
    char loadDataname[256];
    sprintf(loadDataname,"%sinstantaneousStates_N%i_p%.4f_T%.8f_spacing%.i_idx%i.nc",loadfolder,numpts,p0,T,spacingofInstantaneous,id);
    sprintf(stressTensorDataname,"%ssigmaXXsigmaYY_perimeter_N%i_p%.3f_T%.8f_%i.nc",saveDirName,numpts,p0,T,id);
    shared_ptr<twoValuesDatabase> stressTensor=make_shared<twoValuesDatabase>(stressTensorDataname,NcFile::Replace);
    
    namespace fs = std::filesystem;
    if (fs::exists(loadDataname)) {
        cout << "reading record from " << loadDataname << endl;
    } else {
        std::cout <<loadDataname<< " does not exist." << std::endl;
        abort();
    }
    nvtModelDatabase fluidConfigurations(numpts,loadDataname,NcFile::ReadOnly);
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    fluidConfigurations.readState(voronoiModel,0,true);
    
    cout<<"Order parameters at p0="<<p0<<" T="<<T<<" for configuration "<<id<<endl;
 

    //combine the equation of motion and the cell configuration in a "Simulation"


    //run for a few initialization timesteps

    //the reporting of the force should yield a number that is numerically close to zero.

//    cudaProfilerStart();
    t1=clock();

    structuralFeatures strucFeat(voronoiModel->Box);
    for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
        fluidConfigurations.readState(voronoiModel,rec,false);
        double time =voronoiModel->currentTime;
        if(time<1e-12) break;
        //overlapdatNVT[rec] = dynFeat.computeOverlapFunction(voronoiModel->returnPositions());
        voronoiModel->enforceTopology();
        voronoiModel->setModuliUniform(KA,1.0);
        stressTensor->writeValues(voronoiModel->getSigmaXX(),voronoiModel->getSigmaYY());        
    };   

    
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
