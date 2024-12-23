#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "periodicBoundaries.h"
#include "GlassyDynModelDatabase.h"


/*!
This file save the log spaced nvt database data with equally spaced de/dgamma and d2e/dgamma2 saved
in csv files
*/

int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 100; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 5; //number of time steps to run after initialization
    int initSteps = 100; //number of initialization steps

    double dt = 0.01; //the time step size
    double p0 = 3.8;  //the preferred perimeter
    double a0 = 1.0;  // the preferred area
    double T = 0.1;  // the temperature
    int Nchain = 4;     //The number of thermostats to chain together
    int id = 0;      //The index of different configuration

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 't': tSteps = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 'i': initSteps = atoi(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'a': a0 = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'x': id = atof(optarg); break; //indentify different simulations
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
    //set-up a log-spaced state saver...can add as few as 1 database, or as many as you'd like. "0.1" will save 10 states per decade of time
    logEquilibrationStateWriter lewriter(0.05);
    
    clock_t t1,t2; //clocks for timing information
    bool reproducible = false; // if you want random numbers with a more random seed each run, set this to false
    //check to see if we should run on a GPU
    bool initializeGPU = true;
    bool gpu = chooseGPU(USE_GPU);
    if (!gpu)
        initializeGPU = false;

    char dataname[256];
    sprintf(dataname,"/home/chengling/Research/Project/Cell/AnalyticalG/data/N%i/enforceTopology/nvt_N%i_p%.3f_T%.8f_t%i_%i.nc",numpts,numpts,p0,T,tSteps,id);
    char stressname[256];
    sprintf(stressname,"/home/chengling/Research/Project/Cell/AnalyticalG/data/N%i/enforceTopology/stressNVT_N%i_p%.3f_T%.8f_t%i_%i.csv",numpts,numpts,p0,T,tSteps,id);
    char insGname[256];
    sprintf(insGname,"/home/chengling/Research/Project/Cell/AnalyticalG/data/N%i/enforceTopology/insGNVT_N%i_p%.3f_T%.8f_t%i_%i.csv",numpts,numpts,p0,T,tSteps,id);

    shared_ptr<nvtModelDatabase> ncdat=make_shared<nvtModelDatabase>(numpts,dataname,NcFile::Replace);
    lewriter.addDatabase(ncdat,0);
    lewriter.identifyNextFrame();
    shared_ptr<NoseHooverChainNVT> nvt = make_shared<NoseHooverChainNVT>(numpts,Nchain,initializeGPU);

    //define a voronoi configuration with a quadratic energy functional
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,a0,p0,reproducible,initializeGPU);

    //voronoiModel->setCellPreferencesWithRandomAreas(p0,0.8,1.2);

    voronoiModel->setCellVelocitiesMaxwellBoltzmann(T);
    nvt->setT(T);

    //combine the equation of motion and the cell configuration in a "Simulation"
    SimulationPtr sim = make_shared<Simulation>();

    PeriodicBoxPtr newbox = make_shared<periodicBoundaries>(sqrt(numpts),sqrt(numpts));
    sim->setBox(newbox);

    sim->setConfiguration(voronoiModel);
    sim->addUpdater(nvt,voronoiModel);
    //set the time step size
    sim->setIntegrationTimestep(dt);
    //initialize Hilbert-curve sorting... can be turned off by commenting out this line or seting the argument to a negative number
    //sim->setSortPeriod(initSteps/10);
    //set appropriate CPU and GPU flags
    sim->setCPUOperation(!initializeGPU);
    if (!gpu)
        sim->setOmpThreads(abs(USE_GPU));
    sim->setReproducible(reproducible);

    //run for a few initialization timesteps

    //the reporting of the force should yield a number that is numerically close to zero.
    voronoiModel->reportMeanCellForce(false);

    //store the instantaneous stress and d2E/dgamma2 at every tau
    //Note stress is (dE/dgamma)/Area
    std::vector<double> stressdat(tSteps/100);
    std::vector<double> insGdat(tSteps/100);

//    cudaProfilerStart();
    t1=clock();
    for(long long int ii = 0; ii < initSteps; ++ii)
        {
        //voronoiModel->computeGeometry();
        //cout <<"d2Edg2"<< voronoiModel->getd2Edgammadgamma()<<endl;
        sim->performTimestep();
        };

    int stessidx = 0;
    for(long long int ii = 0; ii < tSteps; ++ii)
        {
        //voronoiModel->computeGeometry();
        //cout <<"d2Edg2"<< voronoiModel->getd2Edgammadgamma()<<endl;
        if (ii % 100 == 0){
            voronoiModel->enforceTopology();
            stressdat[stessidx] = voronoiModel->getSigmaXY();
            insGdat[stessidx] = voronoiModel->getd2Edgammadgamma();
            stessidx ++;
        }
        if (ii == lewriter.nextFrameToSave)
            {
            voronoiModel->enforceTopology();
            lewriter.writeState(voronoiModel,ii);
            }
        sim->performTimestep();
        };
//    cudaProfilerStop();
    t2=clock();
    //save the stress to a csv file
    std::ofstream outFile1(stressname);
    if (outFile1.is_open()) {
        for (int i = 0; i < stressdat.size(); ++i) {
            outFile1 << stressdat[i];
            if (i != stressdat.size() - 1) {
                outFile1 << ','; // Add a comma if it's not the last element
            }
        }
        outFile1.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    };
    //save the instantaneous d2E/dgamma2 to a csv file
    std::ofstream outFile2(insGname);
    if (outFile2.is_open()) {
        for (int i = 0; i < insGdat.size(); ++i) {
            outFile2 << insGdat[i];
            if (i != insGdat.size() - 1) {
                outFile2 << ','; // Add a comma if it's not the last element
            }
        }
        outFile2.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }

    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
