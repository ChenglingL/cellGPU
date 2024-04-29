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
#include "derivativeModelDatabase.h"
#include "brownianParticleDynamics.h"




/*!
This .cpp is for numerically simulate the 1st simple shear derivatives for each partile.
*/

int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 200; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;

    double tauEstimate = 10;
    double numberOfRelaxationTimes =20.0;
    int numberofDerivatives = 50000;



    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together

    double Mu = 1.0; 
    long long int timesteps=1000;
    long long int initialSteps=1000;
    int numofInstantaneous = 100;
    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:w:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 'i': initialSteps = atoi(optarg); break;
            case 'w': numofInstantaneous = atoi(optarg); break;
            case 'm': Mu = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': T0 = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'r': recordIndex = atoi(optarg); break;
            case 's': timesteps = atoi(optarg); break;
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
    long long int runTimesteps = floor(timesteps/dt);
    long long int initialRunTimesteps = floor(initialSteps/dt);
    cout << "Brownian dynamics is applied with mu= " << Mu  << endl;
    

    //set the spacing for saving instantaneous states
    long long int spacingofInstantaneous = floor(runTimesteps/numofInstantaneous);
    int spacingofDerivative = round(1/dt);
    cout<<"data collecting timesteps = " << runTimesteps <<"; data will be saved at every "<<spacingofDerivative<<"dt"<< endl;

    logEquilibrationStateWriter lewriter(0.05);

    cout<<"save the derivatives at every "<<spacingofDerivative*dt<<"tau"<<endl; 
    char simpleShearPerCellname[256];
    char saveDirName[256];
    char dataname[256];
    char simpleShearname[256];
    char SACname[256];

    logSACWritter lsacwriter;
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/glassyDynamics/systematicGeq/");
    sprintf(simpleShearPerCellname,"%ssimpleShearDerivativesPerCell_bd_N%i_p%.4f_T%.8f_mu%.4f_idx%i.nc",saveDirName,numpts,p0,T,Mu,recordIndex);
    shared_ptr<derivativeModelDatabase> simpleshearPerCelldat=make_shared<derivativeModelDatabase>(numpts, simpleShearPerCellname,NcFile::Replace);

    sprintf(SACname,"%sSACtime_bd_N%i_p%.4f_T%.8f_mu%.4f_idx%i.nc",saveDirName,numpts,p0,T,Mu,recordIndex);
    shared_ptr<twoValuesDatabase> SACtime=make_shared<twoValuesDatabase>(SACname,NcFile::Replace);
    shared_ptr<autocorrelator> acdat = make_shared<autocorrelator>(16,2,dt);
    lsacwriter.addDatabase(SACtime,acdat,0,10000000);

    sprintf(simpleShearname,"%ssimpleShearDerivatives1st2nd_bd_N%i_p%.4f_T%.8f_mu%.4f_idx%i.nc",saveDirName,numpts,p0,T,Mu,recordIndex);
    shared_ptr<twoValuesDatabase> simplesheardat=make_shared<twoValuesDatabase>(simpleShearname,NcFile::Replace);
    
    sprintf(dataname,"%sglassyDynamics_bd_N%i_p%.4f_T%.8f_mu%.4f_idx%i.nc",saveDirName,numpts,p0,T,Mu,recordIndex);
    shared_ptr<testModelDatabase> glassyDynamicsdat=make_shared<testModelDatabase>(numpts,dataname,NcFile::Replace);
    lewriter.addDatabase(glassyDynamicsdat,0);
    lewriter.identifyNextFrame();


    cout<<"Data are saved in "<<saveDirName<<endl;

        //specify the name of the database to *load data* from
    // char loadDatabaseName[256];
    // sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/productionRuns/p%.3f/glassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",numpts,p0,numpts,p0,T,floor(equilibrationTimesteps*dt),recordIndex);
    // cout << "reading record 0 from " << loadDatabaseName << endl;
    // nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);



    cout << "initializing a system of " << numpts << " cells at temperature " << T << endl;
    shared_ptr<brownianParticleDynamics> bd = make_shared<brownianParticleDynamics>(numpts);
    bd->setT(T);
    bd->setMu(Mu);

    //define a voronoi configuration and load the relevant record from the database
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    //fluidConfigurations.readState(voronoiModel,0,true);
    voronoiModel->setCellVelocitiesMaxwellBoltzmann(T);
   
    double b1,b2,b3,b4;
    voronoiModel->Box->getBoxDims(b1,b2,b3,b4);
    double area = b1*b4;
    //cout<<"The box has been scaled from ("<<b1<<", "<<b4<<") to ("<<l1<<", "<<l4<<") by applying pure shear epsilon "<<epsilon<<endl;

    //set the cell preferences to uniformly have A_0 = 1, P_0 = p_0 -- this line was used to generate the states, but now we just load the data
//    voronoiModel->setCellPreferencesWithRandomAreas(p0,0.8,1.2);
    //voronoiModel->setCellVelocitiesMaxwellBoltzmann(T);
    //combine the equation of motion and the cell configuration in a "Simulation"
    SimulationPtr sim = make_shared<Simulation>();
    sim->setConfiguration(voronoiModel);
    sim->addUpdater(bd,voronoiModel);
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
    //cout<<"staring pure shear runs"<<endl;
    //the "+2" is to ensure there are no fence-post problems for the very longest equilibrated state
    for(long long int ii = 0; ii < initialRunTimesteps; ++ii)
        {
        sim->performTimestep();
        };
    for(long long int ii = 0; ii < runTimesteps+2; ++ii)
        {
        //save to one of the databases if needed
        if (ii % spacingofInstantaneous == 0){
            voronoiModel->enforceTopology();
            simpleshearPerCelldat->writeState(voronoiModel);
            };
        if (ii % spacingofDerivative == 0){
            voronoiModel->enforceTopology();
            double sigmatotal = voronoiModel->getSigmaXY();
            simplesheardat->writeValues(sigmatotal*area,voronoiModel->getd2Edgammadgamma());
            };
        if (ii == lewriter.nextFrameToSave){
            lewriter.writeState(voronoiModel,ii);
        }
        double sigma = voronoiModel->getSigmaXY();
        lsacwriter.addData(sigma,ii);
        //advance the simulationcd
        sim->performTimestep();
        };
    //the reporting of the force should yield a number that is numerically close to zero.
    lsacwriter.writeSAC();
    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
