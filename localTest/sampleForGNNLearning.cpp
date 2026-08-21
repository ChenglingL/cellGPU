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
#include "GNNLearningModelDatabase.h"
#include <filesystem>


/*!
This .cpp is to load a well-equilbrated configuration and keept running for a bit and save state for a constant spacing
The net force vector is recorded for learning. The neighbor list of each cell is also recorded for later usage (potentially).
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



    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double logSpacing = 1000.0;
    long long int timeLimit = 9999999999; // The longest simulation timesteps
    double initialTime = 1000.0; // time for equilbration 
    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:l:p:t:e:w:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': initialTime = atof(optarg); break;
            case 'm': numberOfRelaxationTimes = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': timeLimit = atoi(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 's': logSpacing = atof(optarg); break;
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


    
    long long int equilibrationTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    //set the spacing for saving instantaneous states
    long long int logSpaceTimesteps = max(floor(100/dt),floor((logSpacing)/ dt));
    long long int runTimesteps = floor(logSpaceTimesteps * (numberOfRelaxationTimes-1));
    cout << "The simulation time limit " << floor(runTimesteps * dt)  << endl;

    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. The arguement will save approximately the correct number of states per decade of time (up to integer rounding in the early decades)
    char dataname[256];
    char saveDirName[256];

    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/forceInference/2D/N%i/p%.3f/",numpts,p0);
 
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
    sprintf(dataname,"%spositionsForces_N%i_p%.4f_T%.8f_idx%i.nc",saveDirName,numpts,p0,T,recordIndex);
    shared_ptr<GNNLearningModelDatabase> glassyDynamicsdat=make_shared<GNNLearningModelDatabase>(numpts,dataname,NcFile::Replace);



    cout<<"Data are saved in "<<saveDirName<<endl;



    cout << "Starting simulation with " << numpts << " cells at temperature " << T << endl;
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);
    nvt->setT(T);
    //specify the name of the database to *load data* from
    char loadDatabaseName[256];
    sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/productionRuns/p%.3f/glassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",numpts,p0,numpts,p0,T,floor(equilibrationTimesteps*dt),recordIndex);
    cout << "reading record " << recordIndex << " from " << loadDatabaseName << endl;
    nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);

    //define a voronoi configuration and load the relevant record from the database
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    int readSnap = fluidConfigurations.GetNumRecs() - 2;
    if(readSnap > 60) // if the productionRun data hasnot run for 1000tau
        {
        //cout<<"Start to load data!"<<endl;
        fluidConfigurations.readState(voronoiModel,readSnap,true);
        //cout<<"Successfully load data!"<<endl;
        }
    else
        {
        cout << "You have tried to load a frame from a database which hasn't run for long" << endl;
        return 0;
        }
    voronoiModel->enforceTopology();
    voronoiModel->computeGeometry();
    voronoiModel->computeForces();
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
    sim->setCurrentTime(voronoiModel->currentTime);
    //initialize Hilbert-curve sorting... can be turned off by commenting out this line or seting the argument to a negative number
    //sim->setSortPeriod(initSteps/10);
    //set appropriate CPU and GPU flags
    sim->setCPUOperation(!initializeGPU);
    if (!gpu)
        sim->setOmpThreads(abs(USE_GPU));
    sim->setReproducible(reproducible);


    cout<<"start running"<<endl;
    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    for(long long int ii = 0; ii < runTimesteps; ++ii)
        {
        if (ii % logSpaceTimesteps == 0)
            {
                glassyDynamicsdat->writeState(voronoiModel);
            }
        //advance the simulationcd
        sim->performTimestep();
        };
    //the reporting of the force should yield a number that is numerically close to zero.
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
