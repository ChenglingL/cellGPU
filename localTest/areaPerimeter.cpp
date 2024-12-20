#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"

#include "trajectoryModelDatabase.h"
#include "areaPerimeterDatabase.h"
#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "brownianParticleDynamics.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "twoValuesDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "periodicBoundaries.h"
#include "GlassyDynModelDatabase.h"
#include <filesystem>

/*!
This is for area and perimeter calculation to plot the statistics of p
*/

int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 200; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;

    double tauEstimate = 10;
    double equilibrationWaitingTimeMultiple = 10.0;
    double numberOfRelaxationTimes =10.0;
    int numberofDerivatives = 50000;

    double waitingtime=100000;
    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double statesSavedPerDecadeOfTime = 15.;
    double ks=6.28319; // the k position of first peak in the S(k)

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:k:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': equilibrationWaitingTimeMultiple = atof(optarg); break;
            case 'm': waitingtime = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': T0 = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'k': ks = atof(optarg); break;
            case 's': statesSavedPerDecadeOfTime = atof(optarg); break;
            case 'r': recordIndex = atoi(optarg); break;
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
    bool reproducible = true; // if you want random numbers with a more random seed each run, set this to false
    //check to see if we should run on a GPU
    bool initializeGPU = true;
    bool gpu = chooseGPU(USE_GPU);
    if (!gpu)
        initializeGPU = false;
    char loaddataname[256];
    char APDataName[256];
    char savefolder[256];
    char loadfolder[256];
    sprintf(savefolder,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/tauAlphaData/p%.3f/",numpts,p0);
    sprintf(loadfolder,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/productionRuns/p%.3f/",numpts,p0);
    namespace fs = std::filesystem;
    if (waitingtime == 100000) //if waiting time is an input of .cpp then use that one as waitingtime
    {
        waitingtime = max(10000.,floor(tauEstimate * equilibrationWaitingTimeMultiple));
    }
    sprintf(loaddataname,"%sglassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",loadfolder,numpts,p0,T,waitingtime,recordIndex);
    sprintf(APDataName,"%sareaPeri_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",savefolder,numpts,p0,T,waitingtime,recordIndex);
    if (fs::exists(loaddataname)) {
        cout << "reading record from " << loaddataname << endl;
    } else {
        std::cout <<loaddataname<< " does not exist." << std::endl;
        abort();
    }
    cout << "save record in " << APDataName << endl;
    shared_ptr<areaPerimeterDatabase> APdat=make_shared<areaPerimeterDatabase>(numpts,APDataName,NcFile::Replace);
    trajectoryModelDatabase fluidConfigurations(numpts,loaddataname,NcFile::ReadOnly);
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    if (fluidConfigurations.GetNumRecs()<20) {
        cout << "Congiguration is less than 20. Job abort!" <<endl;
        abort();
    };
    int totalRec = fluidConfigurations.GetNumRecs();
    for(int rec= totalRec - 10;rec<fluidConfigurations.GetNumRecs();rec++){
        fluidConfigurations.readState(voronoiModel,rec);
        double time =voronoiModel->currentTime;
        if(rec>10&&time<1e-12) break;
        APdat->writeState(voronoiModel);

    };   
        



    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};