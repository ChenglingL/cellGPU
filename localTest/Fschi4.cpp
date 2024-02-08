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


/*!
This is for chi4 and cage-relative chi4 calculation
*/

/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 200; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;

    double tauEstimate = 10;
    double equilibrationWaitingTimeMultiple = 100.0;
    double numberOfRelaxationTimes =10.0;
    int numberofDerivatives = 50000;
    int id=0;

    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double statesSavedPerDecadeOfTime = 15.;
    double ks=6.28319; // the k position of first peak in the S(k)
    long long int offsets=100000;

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': equilibrationWaitingTimeMultiple = atof(optarg); break;
            case 'm': numberOfRelaxationTimes = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': T0 = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'k': ks = atof(optarg); break;
            case 'x': id = atof(optarg); break;
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
    char SISFDataName[256];
    //long long int maximumWaitingTimesteps = floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt);    
    long long int maximumWaitingTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    long long int maximumTimesteps = maximumWaitingTimesteps+floor((numberOfRelaxationTimes * tauEstimate)/dt);
    char saveDirName[256];
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/localTest/chi4Test/N%i/",numpts);


    sprintf(loaddataname,"%schi4Test_N%i_p%.3f_T%.8f_%i.nc",saveDirName,numpts,p0,T,id);
    sprintf(saveDataName,"%sCRFsCRchi4_N%i_p%.3f_T%.8f_%i.nc",saveDirName,numpts,p0,T,id);
    //sprintf(SISFDataName,"%sSISFCRSISF_N%i_p%.3f_T%.8f_%i.nc",saveDirName,numpts,p0,T,id);
    shared_ptr<twoValuesDatabase> chi4=make_shared<twoValuesDatabase>(saveDataName,NcFile::Replace);
    //shared_ptr<twoValuesDatabase> SISF=make_shared<twoValuesDatabase>(SISFDataName,NcFile::Replace);
    nvtModelDatabase fluidConfigurations(numpts,loaddataname,NcFile::ReadOnly);
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    fluidConfigurations.readState(voronoiModel,0,true);
    dynamicalFeatures dynFeat(voronoiModel->returnPositions(),voronoiModel->Box);
    dynFeat.setCageNeighbors(voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx); 
    cout << "reading record from " << loaddataname << endl;
    for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
        fluidConfigurations.readState(voronoiModel,rec,false);
        double2 FsChi4, CRFsChi4;
        //FsChi4=dynFeat.computeFsChi4(voronoiModel->returnPositions(),ks);
        CRFsChi4=dynFeat.computeCageRelativeFsChi4(voronoiModel->returnPositions(),ks);
        chi4->writeValues(CRFsChi4.x,CRFsChi4.y);       
        //SISF->writeValues(FsChi4.x,CRFsChi4.x);     

    }

    

    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
