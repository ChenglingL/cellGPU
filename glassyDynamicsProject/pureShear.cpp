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


/*!
This .cpp is for numerically test the pure shear modulus. We first load the configuration from equlibrated
simulations. Then apply a pure shear deformation to record energy and time, first/Second derivatives
of E wrt epsilon / g.
Sevral files will be saved: (data are saving at every tau)
simpleShearDerivativesFristSecond_.nc saves the first and second derivative of E wrt gamma. 
pureShearDerivativesFristSecond_.nc saves the first and second derivative of E wrt epsilon. 
timeEnergy_.nc saves the time and energy.
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

    bool zeroEp = false;
    if (abs(epsilon)<1e-12)
        zeroEp = true;

    //set the equilibration time to be 1000tau if
    long long int equilibrationTimesteps = max(floor(10000/dt),floor((tauEstimate * equilibrationWaitingTimeMultiple)/ dt));
    //set the max time to be 20000000 so the simulation can run 48h in the NCSADelta
    long long int runTimesteps = max(floor(1000/dt),floor((tauEstimate * numberOfRelaxationTimes)/ dt));
    cout << "tauAlpha estimate is " << tauEstimate  << endl;
    

    //set the spacing for saving instantaneous states
    long long int spacingofInstantaneous = floor(runTimesteps/10);
    int spacingofDerivative = round(1/dt);
    cout<<"data collecting timesteps = " << runTimesteps <<"; data will be saved at every "<<spacingofDerivative<<"dt"<< endl;

    cout<<"save the derivatives at every "<<spacingofDerivative*dt<<"tau"<<endl; 
    char pureShearname[256]; // in case the job can not be finished with 48 hours, save SAC at t=50000
    char simpleShearname[256];
    char saveDirName[256];
    char energyname[256];
    char initialConfname[256];

    sprintf(saveDirName, "/scratch/bbtm/cli6/glassyDynamics/data/N%i/pureShear/p%.3f/",numpts,p0);
    sprintf(simpleShearname,"%ssimpleShearDerivatives1st2nd_N%i_p%.4f_T%.8f_epsilon%.8f_idx%i.nc",saveDirName,numpts,p0,T,epsilon,recordIndex);
    shared_ptr<twoValuesDatabase> simplesheardat=make_shared<twoValuesDatabase>(simpleShearname,NcFile::Replace);
     
    sprintf(initialConfname,"%spureShearInitialConf_N%i_p%.4f_T%.8f_epsilon%.8f_idx%i.nc",saveDirName,numpts,p0,T,epsilon,recordIndex);
    shared_ptr<trajectoryModelDatabase> initialConfdat=make_shared<trajectoryModelDatabase>(numpts,initialConfname,NcFile::Replace);


    sprintf(pureShearname,"%spureShearDerivatives1st2nd_N%i_p%.4f_T%.8f_epsilon%.8f_idx%i.nc",saveDirName,numpts,p0,T,epsilon,recordIndex);
    shared_ptr<twoValuesDatabase> puresheardat=make_shared<twoValuesDatabase>(pureShearname,NcFile::Replace);

    sprintf(energyname,"%stimeEnergy_N%i_p%.4f_T%.8f_epsilon%.8f_idx%i.nc",saveDirName,numpts,p0,T,epsilon,recordIndex);
    shared_ptr<twoValuesDatabase> energydat=make_shared<twoValuesDatabase>(energyname,NcFile::Replace);

    char pureShearSACname[256];
    char simpleShearSACname[256];

    shared_ptr<autocorrelator> pureShearSacdat = make_shared<autocorrelator>(16,2,dt);
    shared_ptr<autocorrelator> simpleShearSacdat = make_shared<autocorrelator>(16,2,dt);
    cout<<"Data are saved in "<<saveDirName<<endl;

        //specify the name of the database to *load data* from
    char loadDatabaseName[256];
    sprintf(loadDatabaseName,"/projects/bbtm/cli6/glassyDynamics/data/N%i/productionRuns/p%.3f/glassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",numpts,p0,numpts,p0,T,floor(equilibrationTimesteps*dt),recordIndex);
    cout << "reading record 0 from " << loadDatabaseName << endl;
    nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);



    cout << "initializing a system of " << numpts << " cells at temperature " << T << endl;
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);
    nvt->setT(T);

    //define a voronoi configuration and load the relevant record from the database
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    fluidConfigurations.readState(voronoiModel,0,true);
    cout<<"epsilon: "<<epsilon<<endl;
    double namda = 1+epsilon;
    cout<<"namda: "<<namda<<endl;
    double b1,b2,b3,b4;
    voronoiModel->Box->getBoxDims(b1,b2,b3,b4);
    double area = b1*b4;
    cout<<"area: "<<area<<endl;
    double l1=b1*namda;
    double l4=b4/namda;
    cout<<"new lx ly: "<<l1<<", "<<l4<<endl;
    voronoiModel->setRectangularUnitCell(l1,l4);
    initialConfdat->writeState(voronoiModel);
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


    profiler simpleShearProfiler("simpleShear");
    profiler pureShearProfiler("pureShear");

    //run for a few initialization timesteps
    cout<<"staring pure shear runs"<<endl;
    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    for(long long int ii = 0; ii < runTimesteps+2; ++ii)
        {

        if (zeroEp){
            double sigma = voronoiModel->getSigmaXY();
            simpleShearSacdat->add(sigma,0);
            double sigmaPureShear = voronoiModel->getdEdepsilon();
            pureShearSacdat->add(sigmaPureShear/area,0);
        }
        //save to one of the databases if needed
        if (ii < floor(initialData/dt)){
            simpleShearProfiler.start();
            voronoiModel->enforceTopology();
            double sigma = voronoiModel->getSigmaXY();
            simplesheardat->writeValues(sigma*area,voronoiModel->getd2Edgammadgamma());
            simpleShearProfiler.end();

            pureShearProfiler.start();
            puresheardat->writeValues(voronoiModel->getdEdepsilon(),voronoiModel->getd2Edepsilondepsilon());
            pureShearProfiler.end();

            energydat->writeValues(voronoiModel->currentTime,voronoiModel->computeEnergy()); 

            }else if (ii % spacingofDerivative == 0){
            simpleShearProfiler.start();
            voronoiModel->enforceTopology();
            double sigma = voronoiModel->getSigmaXY();
            simplesheardat->writeValues(sigma*area,voronoiModel->getd2Edgammadgamma());
            simpleShearProfiler.end();

            pureShearProfiler.start();
            puresheardat->writeValues(voronoiModel->getdEdepsilon(),voronoiModel->getd2Edepsilondepsilon());
            pureShearProfiler.end();

            energydat->writeValues(voronoiModel->currentTime,voronoiModel->computeEnergy());
            }
        
        //advance the simulationcd
        sim->performTimestep();
        };
    simpleShearProfiler.print();
    pureShearProfiler.print();

    if (zeroEp){
        sprintf(pureShearSACname,"%stimePureShearSAC_N%i_p%.4f_T%.8f_epsilon%.8f_idx%i.nc",saveDirName,numpts,p0,T,epsilon,recordIndex);
        shared_ptr<twoValuesDatabase> pureShearSAC=make_shared<twoValuesDatabase>(pureShearSACname,NcFile::Replace);
        sprintf(simpleShearSACname,"%stimeSimpleShearSAC_N%i_p%.4f_T%.8f_epsilon%.8f_idx%i.nc",saveDirName,numpts,p0,T,epsilon,recordIndex);
        shared_ptr<twoValuesDatabase> simpleShearSAC=make_shared<twoValuesDatabase>(simpleShearSACname,NcFile::Replace);
        cout<<"SAC for pure shear are saved in "<<pureShearSACname<<endl;
        cout<<"SAC for simple shear are saved in "<<simpleShearSACname<<endl;
        simpleShearSacdat->evaluate(false);
        for(int j = 0; j < simpleShearSacdat->correlator.size(); ++j)
            {
            simpleShearSAC->writeValues(simpleShearSacdat->correlator[j].x,simpleShearSacdat->correlator[j].y);
            }
        pureShearSacdat->evaluate(false);
        for(int j = 0; j < pureShearSacdat->correlator.size(); ++j)
            {
            pureShearSAC->writeValues(pureShearSacdat->correlator[j].x,pureShearSacdat->correlator[j].y);
            }    
    }


    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
