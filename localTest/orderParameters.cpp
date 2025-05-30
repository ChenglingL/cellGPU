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
#include "trajectoryModelDatabase.h"
#include <filesystem>


/*!
This .cpp calculate the translational and orientational order parameters to indentify the phase of 
the systems as in 2d melting. This is specificly for production runs.
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
    double kmax = 0.0; //largest k for Fs
    double waitingtime=100000;

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
            case 'k': kmax = atof(optarg); break;
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

    char saveDirName[256];
    char loadfolder[256];
    sprintf(saveDirName,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/orderParameter/p%.3f/",numpts,p0);
    sprintf(loadfolder,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/productionRuns/p%.3f/",numpts,p0);
    char orientationDataname[256];
    char translationDataname[256];
    char loadDataname[256];
    waitingtime = max(10000.,(tauEstimate * equilibrationWaitingTimeMultiple));
    sprintf(loadDataname,"%sglassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",loadfolder,numpts,p0,T,waitingtime,id);
    sprintf(orientationDataname,"%sorientationReIm_N%i_p%.3f_T%.8f_%i.nc",saveDirName,numpts,p0,T,id);
    sprintf(translationDataname,"%stranslationReIm_N%i_p%.3f_T%.8f_%i.nc",saveDirName,numpts,p0,T,id);
    shared_ptr<twoValuesDatabase> orientational=make_shared<twoValuesDatabase>(orientationDataname,NcFile::Replace);
    shared_ptr<twoValuesDatabase> translational=make_shared<twoValuesDatabase>(translationDataname,NcFile::Replace);
    
    namespace fs = std::filesystem;
    if (fs::exists(loadDataname)) {
        cout << "reading record from " << loadDataname << endl;
    } else {
        std::cout <<loadDataname<< " does not exist." << std::endl;
        abort();
    }

    trajectoryModelDatabase fluidConfigurations(numpts,loadDataname,NcFile::ReadOnly);
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    fluidConfigurations.readState(voronoiModel,0);
    
    cout<<"Order parameters at p0="<<p0<<" T="<<T<<" for configuration "<<id<<endl;
 

    //combine the equation of motion and the cell configuration in a "Simulation"


    //run for a few initialization timesteps

    //the reporting of the force should yield a number that is numerically close to zero.

//    cudaProfilerStart();
    t1=clock();

    structuralFeatures strucFeat(voronoiModel->Box);
    for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
        fluidConfigurations.readState(voronoiModel,rec);
        double time =voronoiModel->currentTime;
        if(time<1e-12) break;
        //overlapdatNVT[rec] = dynFeat.computeOverlapFunction(voronoiModel->returnPositions());
        voronoiModel->enforceTopology();
        double2 ori;
        ori=strucFeat.computeBondOrderParameter(voronoiModel->returnPositions(),voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx);
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
        double2 trans,k;
        k.x=kmax,k.y=0;//Just pick the
        trans=strucFeat.computeTranslationalOrderParameter(posdat,k);
        translational->writeValues(trans.x,trans.y);
        orientational->writeValues(ori.x,ori.y);        
    };   

    
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
