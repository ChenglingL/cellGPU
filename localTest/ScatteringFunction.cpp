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
This is for S(k)
*/

/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 200; //number of cells
    int USE_GPU = -1; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 200000; //number of time steps to run after initialization
    int initSteps = 100000; //number of initialization steps 1000\tau

    double dt = 0.01; //the time step size
    double p0 = 3.8;  //the preferred perimeter
    double a0 = 1.0;  // the preferred area
    double T = 0.1;  // the temperature
    int Nchain = 4;     //The number of thermostats to chain together
    int Nsave = 10000;   //save every 100\tau
    double ks=6.50; // the k position of first peak in the S(k)
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
            case 'k': ks = atof(optarg); break;
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

    char dataname[256];
    sprintf(dataname,"/projects/bbtm/cli6/GlassAging/data/fluidConfigurations/monodisperseFluidConfigurations_N%i_TEq%.8f_p%.5f.nc",numpts,T,p0);
    nvtModelDatabase ncdat(numpts,dataname,NcFile::Replace);
    char loaddataname[256];
    char saveDataName[256];

    //long long int maximumWaitingTimesteps = floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt);    

    sprintf(loaddataname,"/home/chengling/Research/Project/Cell/glassAging/fluidConfigurations/monodisperseFluidConfigurations_N%i_TEq%.8f_p%.5f.nc",numpts,T,p0);
    nvtModelDatabase fluidConfigurations(numpts,loaddataname,NcFile::ReadOnly);
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    fluidConfigurations.readState(voronoiModel,0,true);
    structuralFeatures strucFeat(voronoiModel->Box);
    cout << "reading record from " << loaddataname << endl;
    for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
        sprintf(saveDataName,"/home/chengling/Research/Project/Cell/glassAging/fluidConfigurations/scatteringFunction_N%i_TEq%.8f_p%.5f_idx%i.nc",numpts,T,p0,rec);
        shared_ptr<twoValuesDatabase> Sk=make_shared<twoValuesDatabase>(saveDataName,NcFile::Replace);    
        fluidConfigurations.readState(voronoiModel,rec,false);
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
        strucFeat.computeStructureFactor(posdat,SofK,5.0,0.5);
        for(int ii=0;ii<SofK.size();ii++){
            Sk->writeValues(SofK[ii].x,SofK[ii].y);    
        }
        }

    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
