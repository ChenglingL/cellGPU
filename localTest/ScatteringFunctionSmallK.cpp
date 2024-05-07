#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


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
#include "trajectoryModelDatabase.h"
#include <filesystem>

/*!
This is for S(k). We pick the second last snapshot at different (p0,T,idx).
*/

/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
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
    double intk=1.0; // largest k in the S(k)
    double dk=0.05; // largest k in the S(k)

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:")) != -1)
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
            case 'k': intk = atof(optarg); break;
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
    char saveDataName[256];
    char savefolder[256];
    char loadfolder[256];
    sprintf(savefolder,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/bulkModulus/p%.3f/",numpts,p0);
    sprintf(loadfolder,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/productionRuns/p%.3f/",numpts,p0);

    namespace fs = std::filesystem;
    long long int runTimesteps = max(floor(10000/dt),floor((tauEstimate * numberOfRelaxationTimes)/ dt));
    long long int spacingofInstantaneous = floor(runTimesteps/10);
    waitingtime = max(10000.,(tauEstimate * equilibrationWaitingTimeMultiple));
    sprintf(loaddataname,"%sinstantaneousStates_N%i_p%.4f_T%.8f_spacing%i_idx%i.nc",loadfolder,numpts,p0,T,spacingofInstantaneous,recordIndex);
    
    if (fs::exists(loaddataname)) {
        cout << "reading record from " << loaddataname << endl;
    } else {
        std::cout <<loaddataname<< " does not exist." << std::endl;
        abort();
    }

    trajectoryModelDatabase fluidConfigurations(numpts,loaddataname,NcFile::ReadOnly);

    for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
        sprintf(saveDataName,"%ssmallKSk_N%i_p%.4f_T%.8f_spacing%i_idx%i_rec%i.nc",savefolder,numpts,p0,T,spacingofInstantaneous,recordIndex,rec);
        shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
        fluidConfigurations.readState(voronoiModel,rec);
        structuralFeatures strucFeat(voronoiModel->Box);
        shared_ptr<twoValuesDatabase> Sk=make_shared<twoValuesDatabase>(saveDataName,NcFile::Replace);    
        vector<double2> SofK;
        //overlapdatNVT[rec] = dynFeat.computeOverlapFunction(voronoiModel->returnPositions());
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
        strucFeat.computeStructureFactor(posdat,SofK,intk,dk);
        for(int ii=0;ii<SofK.size();ii++){
            Sk->writeValues(SofK[ii].x,SofK[ii].y);    
        }
    }


    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
