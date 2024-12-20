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
#include <filesystem>


/*!
THis is to test if changing the frequency of NH thermostats mass would change the result of stress-fluctuation formula
Sevral files will be saved: (data are saving at every tau)
isoCompressionDerivativesFristSecond_.nc saves the first and second derivative of E wrt epsilon. 
timePotentialEnergy_.nc saves the time and energy.
*/

int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 64; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;

    double KA=1.0;
    double KP=1.0;



    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together
    double omega = 1.0; //frequency of NH thermostats

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:w:d:k:o:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': T0 = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'a': KA = atof(optarg); break;
            case 'k': KP = atof(optarg); break;
            case 'm': Nchain = atoi(optarg); break;
            case 'o': omega = atof(optarg); break;
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
    //set the max time to be 20000000 so the simulation can run 48h in the NCSADelta
    //long long int runTimesteps = max(floor(100000/dt),floor((tauEstimate * numberOfRelaxationTimes)/ dt));
    long long int runTimesteps = 10000000; // get as many data points as possible for low T

    char saveDirName[256];
    char derivativename[256];

    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/systematicGeq/");

    sprintf(derivativename,"%ssimpleShearDerivatives1st2nd_nvt_N%i_p%.4f_T%.8f_omega%.4f.nc",saveDirName,numpts,p0,T,omega);
    shared_ptr<twoValuesDatabase> derivativedat=make_shared<twoValuesDatabase>(derivativename,NcFile::Replace);

    cout<<"Data are saved in "<<saveDirName<<endl;

        //specify the name of the database to *load data* from



    cout << "initializing a system of " << numpts << " cells at temperature " << T << endl;
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);
    nvt->setT(T, omega);

    //define a voronoi configuration and load the relevant record from the database
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    voronoiModel->setCellVelocitiesMaxwellBoltzmann(T);

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
    for(long long int ii = 0; ii < runTimesteps+2; ++ii)
        {
            if(ii%100==0){
                potentialEnergydat->writeValues(voronoiModel->currentTime,voronoiModel->computeEnergy());
                kineticEnergydat->writeValues(voronoiModel->currentTime,voronoiModel->computeKineticEnergy());
            }
            if(ii%100000==0){
                //nvt->reportBathData();
                voronoiModel->reportTotalForce();
            }
        //advance the simulationcd
        sim->performTimestep();
        }



    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
