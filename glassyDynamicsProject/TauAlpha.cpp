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
This file compiles to produce an executable that can be used to reproduce the timing information
in the main cellGPU paper. It sets up a simulation that takes control of a voronoi model and a simple
model of active motility
NOTE that in the output, the forces and the positions are not, by default, synchronized! The NcFile
records the force from the last time "computeForces()" was called, and generally the equations of motion will 
move the positions. If you want the forces and the positions to be sync'ed, you should call the
Voronoi model's computeForces() funciton right before saving a state.
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
    double numberOfRelaxationTimes =100.0;
    int numberofDerivatives = 50000;

    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double statesSavedPerDecadeOfTime = 20.;

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
    sprintf(loadDatabaseName,"/projects/bbtm/cli6/GlassAging/data/fluidConfigurations/monodisperseFluidConfigurations_N%i_TEq%.8f_p%.5f.nc",numpts,T0,p0);
    cout << "reading record " << recordIndex << " from " << loadDatabaseName << endl;
    nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);

    //set the max time to be 20000000 so the simulation can run 48h in the NCSADelta
    long long int maximumWaitingTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    if (maximumWaitingTimesteps>10000/dt){maximumWaitingTimesteps=100000/dt;};
    long long int maximumTimesteps = min(floor(200000/dt), maximumWaitingTimesteps+max(floor((numberOfRelaxationTimes * tauEstimate)/dt),1000/dt));
    cout << "tauAlpha estimate is " << tauEstimate << " and the system will be run for a maximum waiting time of " << equilibrationWaitingTimeMultiple << " multiples of that estimate." << endl;
    cout << "maximum waiting timesteps = " << maximumWaitingTimesteps << ", Total timesteps = " << maximumTimesteps << endl;

    
    int spacingofDerivative = maximumTimesteps/(numberofDerivatives);
    if (spacingofDerivative<1){spacingofDerivative=1;};

    cout<<"save the derivatives at every "<<spacingofDerivative*dt<<"tau"<<endl; 
    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. The arguement will save approximately the correct number of states per decade of time (up to integer rounding in the early decades)
    logEquilibrationStateWriter lewriter((1.0/statesSavedPerDecadeOfTime));
    logSACWritter lsacwriter;
    char dataname[256];
    char SACname[256];
    char Derivativename[256];
    char saveDirName[256];
    sprintf(saveDirName, "/projects/bbtm/cli6/glassyDynamics/data/N%i/p%.0f/",numpts,p0*100);
    sprintf(Derivativename,"%sSigmaSecD_N%i_p%.4f_T%.8f_Spacing%i_idx%i.nc",saveDirName,numpts,p0,T,spacingofDerivative,recordIndex);
    shared_ptr<twoValuesDatabase> derivativedat=make_shared<twoValuesDatabase>(Derivativename,NcFile::Replace);
     
    cout<<"Data are saved in "<<saveDirName<<endl;
    //set up a log spaced vector of offsets for the datasaveers
    vector<long long int> offsets;
    offsets.push_back(0);
    int lastOffset=0;
    double power = 5;
    while(lastOffset < maximumWaitingTimesteps)
        {
        lastOffset = power*maximumWaitingTimesteps/10;
        offsets.push_back(lastOffset);
        power+= 1;
        }

    for(int ii = 0; ii < offsets.size(); ++ii)
        {
        sprintf(dataname,"%sglassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.2f_idx%i.nc",saveDirName,numpts,p0,T,offsets[ii]*dt,recordIndex);
        cout << "initializing an offset of " << offsets[ii]*dt << endl;
        shared_ptr<nvtModelDatabase> ncdat=make_shared<nvtModelDatabase>(numpts,dataname,NcFile::Replace);
        lewriter.addDatabase(ncdat,offsets[ii]);
        }

    vector<long long int> offsetsSAC;
    int lastOffsetSAC=maximumTimesteps/4;
    int NwaitTauSAC=1;
    while(lastOffsetSAC < maximumTimesteps)
        {
        offsetsSAC.push_back(lastOffsetSAC);
        cout << "save stress auto correlation function with an offset of " << lastOffsetSAC << endl;
        NwaitTauSAC++;
        lastOffsetSAC = NwaitTauSAC*maximumTimesteps/4;
        }

    for(int ii = 0; ii < offsetsSAC.size(); ++ii)
        {
        sprintf(SACname,"%sSACtime_N%i_p%.4f_T%.8f_waitingTime%i_idx%i.nc",saveDirName,numpts,p0,T,lastOffsetSAC,recordIndex);
        shared_ptr<twoValuesDatabase> SACtime=make_shared<twoValuesDatabase>(SACname,NcFile::Replace);
        shared_ptr<autocorrelator> acdat = make_shared<autocorrelator>(16,2,dt);
        lsacwriter.addDatabase(SACtime,acdat,offsetsSAC[ii],2000000);//set the long time limmit to be 2*10^4tau
        }
    lewriter.identifyNextFrame();


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
    profiler derivativeProfiler("derivitive");
    profiler nvtProfiler("nvt");
    //run for a few initialization timesteps
    printf("starting glassy dynamics run\n");
    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    for(long long int ii = 0; ii < maximumTimesteps+2; ++ii)
        {
        simulationrunProfiler.start();
        addstressProfiler.start();
        voronoiModel->enforceTopology();
        double sigma = voronoiModel->getSigmaXY();
        lsacwriter.addData(sigma,ii);
        addstressProfiler.end();
        //save to one of the databases if needed
        if (ii % spacingofDerivative == 0 && ii<spacingofDerivative*numberofDerivatives){
            derivativeProfiler.start();
            derivativedat->writeValues(sigma,voronoiModel->getd2Edgammadgamma());
            derivativeProfiler.end();
            }
        if (ii == lewriter.nextFrameToSave)
            {
            nvtProfiler.start();
            lewriter.writeState(voronoiModel,ii);
            nvtProfiler.end();
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
    derivativeProfiler.print();
    nvtProfiler.print();
    SACProfiler.start();   
    lsacwriter.writeSAC();
    SACProfiler.end();
    addstressProfiler.print();
    SACProfiler.print();
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
