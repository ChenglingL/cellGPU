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
#include <filesystem>

/*!
This is for overlap/cage-relative overlap/Fs/CRFs calculation for the data generated by taualpha.cpp
*/

/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
int main(int argc, char*argv[])
{
    //...some default parameters
int numpts = 200; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;

    double tauEstimate = 1000.0;
    double equilibrationMultiple = 10.0; // how many tau_alpha for equilibration
    double numberOfRelaxationTimes =20.0;// how many tau_alpha for data recording

    int numberofWaitingtime = 19;

    int timeLimitofSAC = 50000;

    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double statesSavedPerDecadeOfTime = 20.;
    double ks=6.80;
    int offsetIdx=0;

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:w:o:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': equilibrationMultiple = atof(optarg); break;
            case 'm': numberOfRelaxationTimes = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': T0 = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'w': numberofWaitingtime = atof(optarg); break;
            case 's': statesSavedPerDecadeOfTime = atof(optarg); break;
            case 'r': recordIndex = atoi(optarg); break;
            case 'o': offsetIdx = atoi(optarg); break;
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
    char overlapName[256];
    char CRoverlapName[256];
    char SISFlapName[256];
    char CRSISFName[256];
    char savefolder[256];
    char loadfolder[256];
    sprintf(savefolder,"/scratch/bbtm/cli6/glassyDynamics/data/N%i/tauAlphaData/p%.3f/",numpts,p0);
    sprintf(loadfolder,"/scratch/bbtm/cli6/glassyDynamics/data/N%i/p%.3f/",numpts,p0);


    long long int maximumWaitingTimesteps = max(round(20000/dt),round((tauEstimate * numberOfRelaxationTimes)/ dt));
    long long int maximumTimesteps = min(round(30000/dt), maximumWaitingTimesteps+max(round((equilibrationMultiple * tauEstimate)/dt),1000/dt));

    long long int offset = offsetIdx*maximumWaitingTimesteps/20+max(round((equilibrationMultiple * tauEstimate)/dt),1000/dt);




    namespace fs = std::filesystem;
    sprintf(loaddataname,"%sglassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",loadfolder,numpts,p0,T,offset * dt,recordIndex);
    sprintf(overlapName,"%stimeOverlap_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",savefolder,numpts,p0,T,offset * dt,recordIndex);
    sprintf(CRoverlapName,"%stimeCROverlap_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",savefolder,numpts,p0,T,offset * dt,recordIndex);
    sprintf(SISFlapName,"%stimeSISF_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",savefolder,numpts,p0,T,offset * dt,recordIndex);
    sprintf(CRSISFName,"%stimeCRSISF_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",savefolder,numpts,p0,T,offset * dt,recordIndex);

    if (fs::exists(loaddataname)) {
        cout << "reading record from " << loaddataname << endl;
    } else {
        std::cout <<loaddataname<< " does not exist." << std::endl;
        abort();
    }
    shared_ptr<twoValuesDatabase> overlapdat=make_shared<twoValuesDatabase>(overlapName,NcFile::Replace);
    shared_ptr<twoValuesDatabase> CRoverlapdat=make_shared<twoValuesDatabase>(CRoverlapName,NcFile::Replace);
    shared_ptr<twoValuesDatabase> SISFdat=make_shared<twoValuesDatabase>(SISFlapName,NcFile::Replace);
    shared_ptr<twoValuesDatabase> CRSISFdat=make_shared<twoValuesDatabase>(CRSISFName,NcFile::Replace);

    nvtModelDatabase fluidConfigurations(numpts,loaddataname,NcFile::ReadOnly);
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    fluidConfigurations.readState(voronoiModel,0,true);
    dynamicalFeatures dynFeat(voronoiModel->returnPositions(),voronoiModel->Box);
    dynFeat.setCageNeighbors(voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx); 
    if (fluidConfigurations.GetNumRecs()<20) {
        cout << "Congiguration is less than 20. Job abort!" <<endl;
        abort();
    };
    for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
        fluidConfigurations.readState(voronoiModel,rec,false);
        //overlapdatNVT[rec] = dynFeat.computeOverlapFunction(voronoiModel->returnPositions());
        overlapdat->writeValues(voronoiModel->currentTime, dynFeat.computeOverlapFunction(voronoiModel->returnPositions()));        
        CRoverlapdat->writeValues(voronoiModel->currentTime, dynFeat.computeCageRelativeOverlapFunction(voronoiModel->returnPositions()));        
        SISFdat->writeValues(voronoiModel->currentTime, dynFeat.computeSISF(voronoiModel->returnPositions()));        
        CRSISFdat->writeValues(voronoiModel->currentTime, dynFeat.computeCageRelativeSISF(voronoiModel->returnPositions(),ks));        
    
    };   
        



    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
