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
#include "trajectoryModelDatabase.h"


/*!
This to simulate uniformly distributed area to aviod crystalization to test stiff voronoi model and their G_p. 
For known preliminary estimates tau_alpha, we equlibrate for 10 tau_alpha
and run for another 10 tau_alpha. Sevral files will be saved:
glassyDynamics_.nc saves the log-sapced nvt database.
SACtime_.nc saves the stress-autocorrelation function with the correspongding time.
instantaneousStates_.nc saves 10 snapshots after every tau_alpha.
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



    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double statesSavedPerDecadeOfTime = 100.;

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:w:l:")) != -1)
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
    //sprintf(loadDatabaseName,"/projects/bbtm/cli6/GlassAging/data/fluidConfigurations/monodisperseFluidConfigurations_N%i_TEq%.8f_p%.5f.nc",numpts,T0,p0);
    sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/glassAging/fluidConfigurations/polydisperseFluidConfigurations_N%i_TEq%.8f_p%.5f.nc",numpts,T0,p0);
    cout << "reading record " << recordIndex << " from " << loadDatabaseName << endl;
    nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);

    //set the equilibration time to be 1000tau if
    long long int equilibrationTimesteps = max(floor(1000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    //set the max time to be 20000000 so the simulation can run 48h in the NCSADelta
    long long int runTimesteps = max(floor(10000/dt),floor((tauEstimate * numberOfRelaxationTimes)/ dt));
    cout << "tauAlpha estimate is " << tauEstimate  << endl;
    cout << "equilibration timesteps = " << equilibrationTimesteps << ", data collecting timesteps = " << runTimesteps << endl;

    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. The arguement will save approximately the correct number of states per decade of time (up to integer rounding in the early decades)
    logEquilibrationStateWriter lewriter((1.0/statesSavedPerDecadeOfTime));
    char dataname[256];
    char SACname[256];
    char SACnameHalfTime[256]; // in case the job can not be finished with 48 hours, save SAC at t=50000
    char saveDirName[256];
    //sprintf(saveDirName, "/scratch/bbtm/cli6/glassyDynamics/data/N%i/p%.3f/",numpts,p0);
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/N%i/p%.3f/",numpts,p0);
     
    sprintf(dataname,"%sglassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",saveDirName,numpts,p0,T,floor(equilibrationTimesteps*dt),recordIndex);
    shared_ptr<trajectoryModelDatabase> glassyDynamicsdat=make_shared<trajectoryModelDatabase>(numpts,dataname,NcFile::Replace);
    lewriter.addDatabase(glassyDynamicsdat,0);
    lewriter.identifyNextFrame();

    sprintf(SACname,"%sSACtime_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",saveDirName,numpts,p0,T,floor(equilibrationTimesteps*dt),recordIndex);
    shared_ptr<autocorrelator> acdat = make_shared<autocorrelator>(32,2,dt);


    cout<<"Data are saved in "<<saveDirName<<endl;



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

    printf("starting equilibration run\n");
    for(long long int ii = 0; ii < equilibrationTimesteps; ++ii)
        {
        sim->performTimestep();
        };
    voronoiModel->computeGeometry();
    printf("Finished with initialization\n");
    cout << "current q = " << voronoiModel->reportq() << endl;

    profiler simulationrunProfiler("simulationrun");
    profiler addstressProfiler("addstress");
    profiler SACProfiler("SAC");
    profiler timeStepProfiler("timeStep");
    profiler nvtProfiler("nvt");

    //run for a few initialization timesteps
    printf("starting glassy dynamics run\n");
    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    double exponent_SAC = 5; // this is to save SAC regularly in case the simulation is stopped when it finises
    long int nextFrameToSave_SAC = floor(pow(10.0, exponent_SAC));
    for(long long int ii = 0; ii < runTimesteps+2; ++ii)
        {
        simulationrunProfiler.start();
        addstressProfiler.start();
        voronoiModel->enforceTopology();
        double sigma = voronoiModel->getSigmaXY();
        acdat->add(sigma,0);
        addstressProfiler.end();
        //save to one of the databases if needed
        if (ii == lewriter.nextFrameToSave)
            {
            nvtProfiler.start();
            lewriter.writeState(voronoiModel,ii);
            nvtProfiler.end();
            }
        if (ii == nextFrameToSave_SAC)
            {
                twoValuesDatabase* SACtime=new twoValuesDatabase(SACname,NcFile::Replace);
                acdat->evaluate(false);
                for(int j = 0; j < acdat->correlator.size(); ++j)
                    {
                    SACtime->writeValues(acdat->correlator[j].y,acdat->correlator[j].x);
                    }
                exponent_SAC += 1/statesSavedPerDecadeOfTime;
                nextFrameToSave_SAC = floor(pow(10.0, exponent_SAC));
                delete SACtime;
            }
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
    nvtProfiler.print();
    SACProfiler.start();   
    twoValuesDatabase* SACtime=new twoValuesDatabase(SACname,NcFile::Replace);
    acdat->evaluate(false);
        for(int j = 0; j < acdat->correlator.size(); ++j)
            {
            SACtime->writeValues(acdat->correlator[j].y,acdat->correlator[j].x);
            }
    SACProfiler.end();
    addstressProfiler.print();
    SACProfiler.print();
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
