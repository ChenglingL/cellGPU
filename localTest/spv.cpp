#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "brownianParticleDynamics.h"
#include "selfPropelledParticleDynamics.h"
#include "nvtModelDatabase.h"
#include "twoValuesDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "periodicBoundaries.h"
#include "trajectoryModelDatabase.h"
#include <filesystem>



/*!
spv model to reproduce Max's result
*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 200; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 5; //number of time steps to run after initialization
    int initSteps = 1; //number of initialization steps

    double dt = 0.01; //the time step size
    double p0 = 3.8;  //the preferred perimeter
    double a0 = 1.0;  // the preferred area
    double v0 = 0.1;  // the mobility
    double dr = 1.0;  // the noise
    int Nchain = 4;     //The number of thermostats to chain together

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
            case 'v': v0 = atof(optarg); break;
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

    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. "0.1" will save 10 states per decade of time
    logEquilibrationStateWriter lewriter(0.1);
    char dataname[256];
    char msdName[256];
    char crmsdName[256];
    char savefolder[256];

    cout << "initializing a system of " << numpts <<  endl;
    sprintf(savefolder,"/home/chengling/Research/Project/Cell/glassyDynamics/localTest/spv/");

    vector<long long int> offsets;
    offsets.push_back(0);
    //offsets.push_back(100);offsets.push_back(1000);offsets.push_back(50);

    sprintf(dataname,"%sspv_N%i_p%.5f_Dr%.4f_v0%.4f_dt%.4f.nc",savefolder,numpts,p0,dr,v0,dt);
    sprintf(msdName,"%stimeMSD_N%i_p%.5f_Dr%.4f_v0%.4f_dt%.4f.nc",savefolder,numpts,p0,dr,v0,dt);
    sprintf(crmsdName,"%stimeCRMSD_N%i_p%.5f_Dr%.4f_v0%.4f_dt%.4f.nc",savefolder,numpts,p0,dr,v0,dt);
    shared_ptr<trajectoryModelDatabase> ncdat=make_shared<trajectoryModelDatabase>(numpts,dataname,NcFile::Replace);
    lewriter.addDatabase(ncdat,offsets[0]);

    lewriter.identifyNextFrame();

    shared_ptr<twoValuesDatabase> CRMSD=make_shared<twoValuesDatabase>(crmsdName,NcFile::Replace);
    shared_ptr<twoValuesDatabase> MSD=make_shared<twoValuesDatabase>(msdName,NcFile::Replace);
    cout << "initializing a system of " << numpts <<  endl;
    shared_ptr<selfPropelledParticleDynamics> sp = make_shared<selfPropelledParticleDynamics>();

    //define a voronoi configuration with a quadratic energy functional
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);

    //set the cell preferences to uniformly have A_0 = 1, P_0 = p_0

    voronoiModel->setv0Dr(0,dr);


    //combine the equation of motion and the cell configuration in a "Simulation"
    SimulationPtr sim = make_shared<Simulation>();
    sim->setConfiguration(voronoiModel);
    sim->addUpdater(sp,voronoiModel);
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
    voronoiModel->setv0Dr(v0,dr);


    //run for additional timesteps, compute dynamical features, and record timing information
    dynamicalFeatures dynFeat(voronoiModel->returnPositions(),voronoiModel->Box);
    dynFeat.setCageNeighbors(voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx); 
    std::vector<int2> previousWhichBox(numpts);
    std::vector<int2> previousWhichBoxCR(numpts);
    for (int i = 0; i < numpts; ++i) {
        previousWhichBox[i].x = 0;
        previousWhichBox[i].y = 0;
        previousWhichBoxCR[i].x = 0;
        previousWhichBoxCR[i].y = 0;
    }
    int rec = 0;
    double iniTime = voronoiModel->currentTime;
//    cudaProfilerStart();
    GPUArray<double2> previousPos;
    for(long long int ii = 0; ii < tSteps; ++ii)
        {

        if (ii == lewriter.nextFrameToSave)
            {

            lewriter.writeState(voronoiModel,ii);
            if(rec==0){
                previousPos = voronoiModel->returnPositions();
            }else if(rec>0) {
                MSD->writeValues(voronoiModel->currentTime - iniTime, dynFeat.computeMSD(voronoiModel->returnPositions(),previousPos,previousWhichBox));  
                CRMSD->writeValues(voronoiModel->currentTime  - iniTime, dynFeat.computeCageRelativeMSD(voronoiModel->returnPositions(),previousPos,previousWhichBoxCR));
                previousPos = voronoiModel->returnPositions();
            }
            rec++;
            }

        sim->performTimestep();
        };
//    cudaProfilerStop();


    return 0;
};
