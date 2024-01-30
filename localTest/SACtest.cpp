#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


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


/*!
This is to test the stress auto-correlation function
*/

/*There will three output files. One is using the nvtModelBase and saves the log-spaced configurations; one 
is used to save data points of de/dgamma and d2e/dgamma2 with equalispaced time; the other one is to save the
stress autocorrelation function.*/
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

    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double statesSavedPerDecadeOfTime = 15.;

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

    //specify the name of the database to *load data* from
    char loadDatabaseName[256];
    sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/glassAging/fluidConfigurations/monodisperseFluidConfigurations_N%i_TEq%.8f_p%.5f.nc",numpts,T,p0);
    cout << "reading record " << recordIndex << " from " << loadDatabaseName << endl;
    nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);

    //long long int maximumWaitingTimesteps = floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt);    


    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. The arguement will save approximately the correct number of states per decade of time (up to integer rounding in the early decades)
    logSACWritter lsacwriter;
    char dataname[256];
    char SACname[256];
    char saveDirName[256];
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/SACtest/");


    vector<int> pvalues = {8, 16, 32, 64};

    for(int ii = 0; ii < pvalues.size(); ++ii)
        {
        sprintf(SACname,"%sSACtime_N%i_p%.4f_T%.8f_p%i_idx%i.nc",saveDirName,numpts,p0,T,pvalues[ii],recordIndex);
        shared_ptr<twoValuesDatabase> SACtime=make_shared<twoValuesDatabase>(SACname,NcFile::Replace);
        shared_ptr<autocorrelator> acdat = make_shared<autocorrelator>(pvalues[ii],2,dt);
        lsacwriter.addDatabase(SACtime,acdat,tauEstimate*10/dt);
        }



    cout << "initializing a system of " << numpts << " cells at temperature " << T << endl;
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);
    nvt->setT(T);

    //define a voronoi configuration and load the relevant record from the database
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    if(recordIndex <fluidConfigurations.GetNumRecs())
        {
        //cout<<"Start to load data!"<<endl;
        fluidConfigurations.readState(voronoiModel,recordIndex,true);
        //cout<<"Successfully load data!"<<endl;
        }
    else
        {
        cout << "You have tried to load a frame from a database which doesn't exist" << endl;
        return 0;
        }

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
    profiler simulationrunProfiler("simulationrun");
    profiler addstressProfiler("addstress");
    profiler SACProfiler("SAC");
    profiler timeStepProfiler("timeStep");
    //run for a few initialization timesteps
    printf("starting glassy dynamics run\n");
    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    for(long long int ii = 0; ii < 20*tauEstimate; ++ii)
        {
        simulationrunProfiler.start();
        addstressProfiler.start();
        voronoiModel->enforceTopology();
        double sigma = voronoiModel->getSigmaXY();
        lsacwriter.addData(sigma,ii);
        addstressProfiler.end();
        //save to one of the databases if needed
        //advance the simulationcd
        timeStepProfiler.start();
        sim->performTimestep();
        timeStepProfiler.end();
        simulationrunProfiler.end();
        };
    //the reporting of the force should yield a number that is numerically close to zero.
    voronoiModel->reportMeanCellForce(false);

    simulationrunProfiler.print();
    timeStepProfiler.print();
    SACProfiler.start();   
    lsacwriter.writeSAC();
    SACProfiler.end();
    addstressProfiler.print();
    SACProfiler.print();
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
