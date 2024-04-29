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
#include "testModelDatabase.h"
#include <filesystem>

/*!
This is for cage-relative overlap calculation for brownian dynamics with different mu
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

    double Mu=1.0;
    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double statesSavedPerDecadeOfTime = 15.;
    double ks=6.28319; // the k position of first peak in the S(k)
    int dynamics=1.0;
    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': equilibrationWaitingTimeMultiple = atof(optarg); break;
            case 'm': Mu = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': T0 = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'k': ks = atof(optarg); break;
            case 's': dynamics = atoi(optarg); break;
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
    char dyna[256];
    if (dynamics==1)
    {
        sprintf(dyna,"bd");
    }else{
        sprintf(dyna,"nvt");
    }
    
    sprintf(savefolder, "/home/chengling/Research/Project/Cell/glassyDynamics/systematicGeq/");
    sprintf(loadfolder, "/home/chengling/Research/Project/Cell/glassyDynamics/systematicGeq/");

    namespace fs = std::filesystem;
    sprintf(loaddataname,"%sglassyDynamics_%s_N%i_p%.4f_T%.8f_mu%.4f_idx%i.nc",savefolder,dyna,numpts,p0,T,Mu,recordIndex);
    sprintf(saveDataName,"%sCRoverlapTime_%s_N%i_p%.4f_T%.8f_mu%.4f_idx%i.nc",savefolder,dyna,numpts,p0,T,Mu,recordIndex);
    if (fs::exists(loaddataname)) {
        cout << "reading record from " << loaddataname << endl;
    } else {
        std::cout <<loaddataname<< " does not exist." << std::endl;
        abort();
    }
    shared_ptr<twoValuesDatabase> overlapCRoverlap=make_shared<twoValuesDatabase>(saveDataName,NcFile::Replace);
    testModelDatabase fluidConfigurations(numpts,loaddataname,NcFile::ReadOnly);
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
        overlapCRoverlap->writeValues(dynFeat.computeCageRelativeOverlapFunction(voronoiModel->returnPositions()),voronoiModel->currentTime);        
    };   
        



    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
