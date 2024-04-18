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
/*This is to save 10 trajactories for each run. The simulations will be run for 30 *1000 tau: 10 for equilibruition, 20 to record 
data. This .cpp should only be used for tau_alpha <1000.*/

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

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:w:")) != -1)
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
    long long int maximumWaitingTimesteps = max(round(20000/dt),round((tauEstimate * numberOfRelaxationTimes)/ dt));
    long long int maximumTimesteps = min(round(30000/dt), maximumWaitingTimesteps+max(round((equilibrationMultiple * tauEstimate)/dt),1000/dt));
    cout << "tauAlpha estimate is " << tauEstimate << " and the system will be run for a maximum waiting time of " << numberOfRelaxationTimes << " multiples of that estimate after equilibration." << endl;
    cout << "maximum waiting timesteps = " << maximumWaitingTimesteps << ", Total timesteps = " << maximumTimesteps << endl;



    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. The arguement will save approximately the correct number of states per decade of time (up to integer rounding in the early decades)
    logEquilibrationStateWriter lewriter((1.0/statesSavedPerDecadeOfTime));
    logSACWritter lsacwriter;
    char dataname[256];
    char SACname[256];
    char Derivativename[256];
    char saveDirName[256];
    sprintf(saveDirName, "/scratch/bbtm/cli6/glassyDynamics/data/N%i/p%.3f/",numpts,p0); 
    cout<<"Data are saved in "<<saveDirName<<endl;
    //set up a log spaced vector of offsets for the datasaveers
    vector<long long int> offsets;
    for (int power = 0; power < numberofWaitingtime; power++)
    {
        long long int lastOffset = power*maximumWaitingTimesteps/20+max(round((equilibrationMultiple * tauEstimate)/dt),1000/dt);
        offsets.push_back(lastOffset);
    }
    

    for(int ii = 0; ii < offsets.size(); ++ii)
        {
        sprintf(dataname,"%sglassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",saveDirName,numpts,p0,T,offsets[ii]*dt,recordIndex);
        cout << "initializing an offset of " << offsets[ii]*dt << endl;
        shared_ptr<nvtModelDatabase> ncdat=make_shared<nvtModelDatabase>(numpts,dataname,NcFile::Replace);
        lewriter.addDatabase(ncdat,offsets[ii]);
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
    //run for a few initialization timesteps
    printf("starting glassy dynamics run\n");
    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    for(long long int ii = 0; ii < maximumTimesteps+2; ++ii)
        {

        voronoiModel->enforceTopology();

        if (ii == lewriter.nextFrameToSave)
            {
            lewriter.writeState(voronoiModel,ii);
            }

        //advance the simulationcd
        sim->performTimestep();
        };
    //the reporting of the force should yield a number that is numerically close to zero.
    voronoiModel->reportMeanCellForce(false);

    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
