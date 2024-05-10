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
#include "testModelDatabase.h"
#include "trajectoryModelDatabase.h"
#include <chrono>


/*!
This is to test if simulation runs longer at lower T for high p0
*/

int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 200; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;

    double tauEstimate = 10;
    double equilibrationWaitingTimeMultiple = 10.0;
    double numberOfRelaxationTimes =20.0;
    int numberofDerivatives = 50000;



    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double epsilon = 0.0;
    int initialData = 100; //The initial time when we save derivatives at every dt
    long int timeSteps = 100000;
    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:w:d:")) != -1)
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
            case 's': epsilon = atof(optarg); break;
            case 'r': recordIndex = atoi(optarg); break;
            case 'd': initialData = atoi(optarg); break;
            case 'a': timeSteps = atoi(optarg); break;
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


    //set the equilibration time to be 1000tau if
    long long int equilibrationTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    //set the max time to be 20000000 so the simulation can run 48h in the NCSADelta
    long long int runTimesteps = max(floor(1000/dt),floor((tauEstimate * numberOfRelaxationTimes)/ dt));
    cout << "tauAlpha estimate is " << tauEstimate  << endl;
    long long int maximumWaitingTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    if (maximumWaitingTimesteps>10000/dt){maximumWaitingTimesteps=100000/dt;};

    //set the spacing for saving instantaneous states

    char trajectoryName[256];
    char saveDirName[256];
    char simulationTimeName[256];


    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/N%i/simulationTime/p%.3f/",numpts,p0);
    sprintf(trajectoryName,"%strajectoryMostTimeComsuming_N%i_p%.4f_T%.8f_idx%i.nc",saveDirName,numpts,p0,T,recordIndex);
    shared_ptr<trajectoryModelDatabase> trajactorydat=make_shared<trajectoryModelDatabase>(numpts,trajectoryName,NcFile::Replace);
     
    sprintf(simulationTimeName,"%ssimTime&TimeCostForthePreviousTau_N%i_p%.4f_T%.8f_idx%i.nc",saveDirName,numpts,p0,T,recordIndex);
    shared_ptr<twoValuesDatabase> simulationTimedat=make_shared<twoValuesDatabase>(simulationTimeName,NcFile::Replace);

    cout<<"Data are saved in "<<saveDirName<<endl;

        //specify the name of the database to *load data* from
    char loadDatabaseName[256];
    sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/p%.3f/glassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",numpts,p0,numpts,p0,T,floor(maximumWaitingTimesteps*dt),recordIndex);
    cout << "reading record 0 from " << loadDatabaseName << endl;
    nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);



    cout << "initializing a system of " << numpts << " cells at temperature " << T << endl;
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);
    nvt->setT(T);

    //define a voronoi configuration and load the relevant record from the database
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    fluidConfigurations.readState(voronoiModel,0,true);

    //cout<<"The box has been scaled from ("<<b1<<", "<<b4<<") to ("<<l1<<", "<<l4<<") by applying pure shear epsilon "<<epsilon<<endl;

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


    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    double maxTimePerStep = 0.0;
    double timeTakePerStep = 0.0;
    int stepsPerTau = 1/dt;
    for(long long int ii = 0; ii < timeSteps+2; ++ii)
    {
        auto start = std::chrono::high_resolution_clock::now();
        sim->performTimestep();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        timeTakePerStep += duration.count();
        if (ii<floor(10/dt))
        {
            if (duration.count() > maxTimePerStep)
            {
                maxTimePerStep = duration.count();
            }   
        }else if (duration.count() > maxTimePerStep)
        {
            trajactorydat->writeState(voronoiModel);
            maxTimePerStep = duration.count();
        }
        
        if (ii % stepsPerTau == 0 && ii >0)
        {
            simulationTimedat->writeValues(voronoiModel->currentTime,timeTakePerStep/stepsPerTau);
            timeTakePerStep = 0;
        }
        
        
        

    };

    

    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
