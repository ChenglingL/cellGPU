#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"
#include <filesystem>

#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "twoValuesDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "profiler.h"
#include "autocorrelator.h"
#include "logSACWritter.h"
#include "trajectoryModelDatabase.h"


/*!
Here we want to test if the stress auto correlation has a plateau for KA=0 2d Voronoi

Here we also want to test if we use the stress on the boundary (equivalent to defaut sigmaXY for 3D Voronoi) is equivalent to the uniform sigmaXY we calculated in 2D voronoi

This file is for production runs. For known preliminary estimates tau_alpha, we equlibrate for 10 tau_alpha
and run for another 10 tau_alpha. trajectory files will be saved:
nvt_.nc saves the log-sapced nvt database.
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

    double KA = 0.0;
    int numberOfWaitingTime = 10;


    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double statesSavedPerDecadeOfTime = 20.;

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:w:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 'q': numberOfWaitingTime = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': equilibrationWaitingTimeMultiple = atof(optarg); break;
            case 'm': numberOfRelaxationTimes = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': T0 = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'a': KA = atof(optarg); break;
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
    bool reproducible = false; // if you want random numbers with a more random seed each run, set this to false
    //check to see if we should run on a GPU
    bool initializeGPU = true;
    bool gpu = chooseGPU(USE_GPU);
    if (!gpu)
        initializeGPU = false;


    //set the equilibration time to be 1000tau if
    long long int equilibrationTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    //set the max time to be 20000000 so the simulation can run 48h in the NCSADelta
    long long int runTimesteps = max(floor(10000/dt),floor((tauEstimate * numberOfRelaxationTimes)/ dt));
    cout << "tauAlpha estimate is " << tauEstimate  << endl;
    cout << "equilibration timesteps = " << equilibrationTimesteps << ", data collecting timesteps = " << runTimesteps << endl;


    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. The arguement will save approximately the correct number of states per decade of time (up to integer rounding in the early decades)
    logEquilibrationStateWriter lewriter((1.0/statesSavedPerDecadeOfTime));
    char dataname[256];
    char stressTrajname[256];
    char saveDirName[256];
    char SACname[256];
    char SACBoundaryname[256];
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/localTest/SACTest/");
    shared_ptr<autocorrelator> acdat = make_shared<autocorrelator>(16,2,dt);
    shared_ptr<autocorrelator> acdatBoundary = make_shared<autocorrelator>(16,2,dt);
    if (!std::filesystem::exists(saveDirName)) {
        // Create the folder
        if (std::filesystem::create_directory(saveDirName)) {
            std::cout << "Folder created successfully: " << saveDirName << std::endl;
        } else {
            std::cerr << "Failed to create folder: " << saveDirName << std::endl;
        }
    } else {
        std::cout << "Folder already exists: " << saveDirName << std::endl;
    }

    cout<<"Data is saved in "<<saveDirName<<endl;

    vector<long long int> offsets;
    offsets.push_back(0);
    for(int ii = 1; ii < numberOfWaitingTime; ii++)
        {
        long long int lastOffset = ii*ceil(tauEstimate/dt);
        if(10*ceil(tauEstimate/dt) < 1000000){
        lastOffset = ii*ceil(1000/dt);
        }
        offsets.push_back(lastOffset);
        }
    for(int ii = 0; ii < offsets.size(); ++ii)
    {
        sprintf(dataname,"%snvt_N%i_p%.4f_T%.8f_KA%.3f_waitingTime%.0f_idx%i.nc",saveDirName,numpts,p0,T,KA,floor(offsets[ii]*dt),recordIndex);
        shared_ptr<trajectoryModelDatabase> nvtdat=make_shared<trajectoryModelDatabase>(numpts,dataname,NcFile::Replace);
        lewriter.addDatabase(nvtdat,offsets[ii]);
        lewriter.identifyNextFrame();
    }


    cout << "initializing a system of " << numpts << " cells at temperature " << 0.1 << endl;
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);
    nvt->setT(0.1);

    //define a voronoi configuration and load the relevant record from the database
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    voronoiModel->setModuliUniform(KA , 1.0);
    voronoiModel->setCellVelocitiesMaxwellBoltzmann(0.1);
    
    //if N=32768, we load configurations well equlibrated at T = 0.1; Otherwise, we just randomly initlize the vornoi model.


    //specify the name of the database to *load data* from



    //set the cell preferences to uniformly have A_0 = 1, P_0 = p_0 -- this line was used to generate the states, but now we just load the data
//    voronoiModel->setCellPreferencesWithRandomAreas(p0,0.8,1.2);
    //voronoiModel->setCellVelocitiesMaxwellBoltzmann(T);
    //combine the equation of motion and the cell configuration in a "Simulation"
    SimulationPtr sim = make_shared<Simulation>();
    sim->setConfiguration(voronoiModel);
    sim->addUpdater(nvt,voronoiModel);
    //set the time step size
    sim->setIntegrationTimestep(dt);
    //set the time to zero
    sim->setCurrentTime(0.0);
    //initialize Hilbert-curve sorting... can be turned off by commenting out this line or seting the argument to a negative number
    //sim->setSortPeriod(initSteps/10);
    //set appropriate CPU and GPU flags
    sim->setCPUOperation(!initializeGPU);
    if (!gpu)
        sim->setOmpThreads(abs(USE_GPU));
    sim->setReproducible(reproducible);

    printf("starting equilibration run\n");
    for(long long int ii = 0; ii < 100000; ++ii)
        {
        sim->performTimestep();
        };
    nvt->setT(T);
    for(long long int ii = 0; ii < equilibrationTimesteps; ++ii)
        {
        sim->performTimestep();
        };
    printf("Finished with initialization\n");
    //run for a few initialization timesteps
    printf("starting glassy dynamics run\n");
    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    sprintf(stressTrajname,"%suniformStress_boundaryStress_N%i_p%.4f_T%.8f_KA%.3f_idx%i.nc",saveDirName,numpts,p0,T,KA,recordIndex);
    shared_ptr<twoValuesDatabase> SACandSACBoundary=make_shared<twoValuesDatabase>(stressTrajname,NcFile::Replace);
    for(long long int ii = 0; ii < runTimesteps+2; ++ii)
        {
        voronoiModel->enforceTopology();
        double sigma = voronoiModel->getSigmaXY();
        double sigmaBounday = voronoiModel->getSigmaXYonBoundary();
        acdat->add(sigma,0);
        acdatBoundary->add(sigmaBounday,0);
        //SACandSACBoundary->writeValues(sigma,sigmaBounday);
        if (ii == lewriter.nextFrameToSave)
            {
                if (ii==0)
                {
                    cout<<"initial stress on boundary: "<<sigmaBounday<<endl;
                }
                
            lewriter.writeState(voronoiModel,ii);
            }
        //advance the simulationcd
        sim->performTimestep();
        };
    sprintf(SACname,"%sSACtime_N%i_p%.4f_T%.8f_KA%.3f_waitingTime%.0f_idx%i.nc",saveDirName,numpts,p0,T,KA,floor(equilibrationTimesteps*dt),recordIndex);
    shared_ptr<twoValuesDatabase> SACtime=make_shared<twoValuesDatabase>(SACname,NcFile::Replace);
    sprintf(SACBoundaryname,"%sSAC_boundarytime_N%i_p%.4f_T%.8f_KA%.3f_waitingTime%.0f_idx%i.nc",saveDirName,numpts,p0,T,KA,floor(equilibrationTimesteps*dt),recordIndex);
    shared_ptr<twoValuesDatabase> SACBoundarytime=make_shared<twoValuesDatabase>(SACBoundaryname,NcFile::Replace);
    acdat->evaluate(false);
    for(int j = 0; j < acdat->correlator.size(); ++j)
        {
        SACtime->writeValues(acdat->correlator[j].x,acdat->correlator[j].y);
        }
    acdatBoundary->evaluate(false);
    for(int j = 0; j < acdatBoundary->correlator.size(); ++j)
        {
        SACBoundarytime->writeValues(acdatBoundary->correlator[j].x,acdatBoundary->correlator[j].y);
        }
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
