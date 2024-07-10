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
This is to test the the autpcorrelation function
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
    double statesSavedPerDecadeOfTime = 10.;
    long long int timeLimit = 9999999999; // The longest simulation timesteps

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:l:p:t:e:w:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': equilibrationWaitingTimeMultiple = atof(optarg); break;
            case 'm': numberOfRelaxationTimes = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': timeLimit = atoi(optarg); break;
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


    //set the equilibration time to be 1000tau if
    long long int equilibrationTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    //set the max time to be 20000000 so the simulation can run 48h in the NCSADelta
    long long int runTimesteps = max(floor(10000/dt),floor((tauEstimate * numberOfRelaxationTimes)/ dt));
    cout << "The simulation time limit " << floor(timeLimit * dt)  << endl;

    //set the spacing for saving instantaneous states



    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. The arguement will save approximately the correct number of states per decade of time (up to integer rounding in the early decades)
    char dataname16[256];
    char dataname32[256];
    char dataname64[256];
    char dataname128[256];
    char dataname256[256];
    char saveDirName[256];


    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/N%i/autocorrelatorTest/",numpts);
 
     
    sprintf(dataname16,"%sSACtime_p16_N%i_p%.4f_T%.8f_idx%i.nc",saveDirName,numpts,p0,T,recordIndex);
    sprintf(dataname32,"%sSACtime_p32_N%i_p%.4f_T%.8f_idx%i.nc",saveDirName,numpts,p0,T,recordIndex);
    sprintf(dataname64,"%sSACtime_p64_N%i_p%.4f_T%.8f_idx%i.nc",saveDirName,numpts,p0,T,recordIndex);
    sprintf(dataname128,"%sSACtime_p128_N%i_p%.4f_T%.8f_idx%i.nc",saveDirName,numpts,p0,T,recordIndex);
    sprintf(dataname256,"%sSACtime_p256_N%i_p%.4f_T%.8f_idx%i.nc",saveDirName,numpts,p0,T,recordIndex);
    shared_ptr<autocorrelator> acdat16 = make_shared<autocorrelator>(16,2,dt);
    shared_ptr<autocorrelator> acdat32 = make_shared<autocorrelator>(32,2,dt);
    shared_ptr<autocorrelator> acdat64 = make_shared<autocorrelator>(64,2,dt);
    shared_ptr<autocorrelator> acdat128 = make_shared<autocorrelator>(128,2,dt);
    shared_ptr<autocorrelator> acdat256 = make_shared<autocorrelator>(256,2,dt);




    cout<<"Data are saved in "<<saveDirName<<endl;



    cout << "initializing a system of " << numpts << " cells at temperature " << T << endl;
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
    if(readSnap > 100) // if the productionRun data hasnot run for 1000tau
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


    //run for a few initialization timesteps
    printf("starting extended glassy dynamics run\n");
    //equalibrating for 1000 tau to equalibrate the thermostat
    for(long long int ii = 0; ii < 100000; ++ii)
    {
        sim->performTimestep();
    };

    double exponent = 6;
    long int nextFrameToSave = floor(pow(10.0, exponent));
    for(long long int ii = 0; ii < timeLimit; ++ii)
        {
        voronoiModel->enforceTopology();
        double sigma = voronoiModel->getSigmaXY();
        acdat16->add(sigma,0);
        acdat32->add(sigma,0);
        acdat64->add(sigma,0);
        acdat128->add(sigma,0);
        acdat256->add(sigma,0);
        if (ii == nextFrameToSave)
            {
                twoValuesDatabase* SACtime16=new twoValuesDatabase(dataname16,NcFile::Replace);
                acdat16->evaluate(false);
                for(int j = 0; j < acdat16->correlator.size(); ++j)
                    {
                    SACtime16->writeValues(acdat16->correlator[j].y,acdat16->correlator[j].x);
                    }
                exponent += 1/statesSavedPerDecadeOfTime;
            
                delete SACtime16;

                twoValuesDatabase* SACtime32=new twoValuesDatabase(dataname32,NcFile::Replace);
                acdat32->evaluate(false);
                for(int j = 0; j < acdat32->correlator.size(); ++j)
                    {
                    SACtime32->writeValues(acdat32->correlator[j].y,acdat32->correlator[j].x);
                    }
                exponent += 1/statesSavedPerDecadeOfTime;
            
                delete SACtime32;

                twoValuesDatabase* SACtime64=new twoValuesDatabase(dataname64,NcFile::Replace);
                acdat64->evaluate(false);
                for(int j = 0; j < acdat64->correlator.size(); ++j)
                    {
                    SACtime64->writeValues(acdat64->correlator[j].y,acdat64->correlator[j].x);
                    }
                exponent += 1/statesSavedPerDecadeOfTime;
            
                delete SACtime64;

                twoValuesDatabase* SACtime128=new twoValuesDatabase(dataname128,NcFile::Replace);
                acdat128->evaluate(false);
                for(int j = 0; j < acdat128->correlator.size(); ++j)
                    {
                    SACtime128->writeValues(acdat128->correlator[j].y,acdat128->correlator[j].x);
                    }
                exponent += 1/statesSavedPerDecadeOfTime;
            
                delete SACtime128;

                twoValuesDatabase* SACtime256=new twoValuesDatabase(dataname256,NcFile::Replace);
                acdat256->evaluate(false);
                for(int j = 0; j < acdat256->correlator.size(); ++j)
                    {
                    SACtime256->writeValues(acdat256->correlator[j].y,acdat256->correlator[j].x);
                    }
                exponent += 1/statesSavedPerDecadeOfTime;
            
                delete SACtime256;

                nextFrameToSave = floor(pow(10.0, exponent));
            }
        //advance the simulationcd
        sim->performTimestep();
        };
    //the reporting of the force should yield a number that is numerically close to zero.
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
