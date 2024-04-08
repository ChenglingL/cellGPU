#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "EnergyMinimizerGradientDescent.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "twoValuesDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "periodicBoundaries.h"
#include "GlassyDynModelDatabase.h"


/*!
This file is to compute the relaxation time that gradient descent needs
to minimize the energy to a threshold.
*/

/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 100; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 4500000; //number of time steps to run after initialization
    double logSpace  = 0.05; //The space for log saving
    double dt = 0.01; //the time step size
    double p0 = 3.8;  //the preferred perimeter
    double a0 = 1.0;  // the preferred area
    int Nchain = 4;     //The number of thermostats to chain together
    int id = 0;      //The index of different configuration
    double Mu = 1.0; // the learning rate
    double forceThresh = 1e-12;
    double KA=0.0 ;// stiffness of area

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:f:k:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 't': tSteps = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 'f': forceThresh = atoi(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'a': a0 = atof(optarg); break;
            case 'm': Mu = atof(optarg); break;
            case 'k': KA = atof(optarg); break;
            case 'i': logSpace = atof(optarg); break;
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

    clock_t t1,t2; //clocks for timing information
    bool reproducible = false; // if you want random numbers with a more random seed each run, set this to false
    //check to see if we should run on a GPU
    bool initializeGPU = true;
    bool gpu = chooseGPU(USE_GPU);
    if (!gpu)
        initializeGPU = false;

     char saveDirName[256];
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/gdRelaxation/data/N%i/",numpts);


    char dataname[256];
    sprintf(dataname,"%sgdTimeEnergy_N%i_p%.3f_mu%.2f_%i.nc",saveDirName,numpts,p0,Mu,id);
    shared_ptr<twoValuesDatabase> energydat=make_shared<twoValuesDatabase>(dataname,NcFile::Replace);

    shared_ptr<EnergyMinimizerGradientDescent> gd = make_shared<EnergyMinimizerGradientDescent>(numpts);
    gd->setMu(Mu);


    //define a voronoi configuration with a quadratic energy functional
    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,a0,p0,reproducible,initializeGPU);
    voronoiModel->setCellPreferencesUniform(1.0,p0);
    voronoiModel->setModuliUniform(KA,1.0);
    //voronoiModel->setCellPreferencesWithRandomAreas(p0,0.8,1.2);

    //combine the equation of motion and the cell configuration in a "Simulation"
    SimulationPtr sim = make_shared<Simulation>();

    PeriodicBoxPtr newbox = make_shared<periodicBoundaries>(sqrt(numpts),sqrt(numpts));
    sim->setBox(newbox);

    sim->setConfiguration(voronoiModel);
    sim->addUpdater(gd,voronoiModel);
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
    long long int nextFrameToSave = 0;
    shared_ptr<logSpacedIntegers> lsi = make_shared<logSpacedIntegers>(0,logSpace);
    long long int ii=0;
    double mf = 999.0;
    double currentE = 999.9;
    while(ii<tSteps && mf>forceThresh && currentE>forceThresh)
        {
        //voronoiModel->computeGeometry();
        //cout <<"d2Edg2"<< voronoiModel->getd2Edgammadgamma()<<endl;

        sim->performTimestep();
        voronoiModel->enforceTopology();
        voronoiModel->computeGeometry();
        mf=voronoiModel->getMaxForce();
        currentE=voronoiModel->computeEnergy();
        if(ii==nextFrameToSave){
            energydat->writeValues(voronoiModel->currentTime,currentE);
            lsi->update();
            nextFrameToSave=lsi->nextSave;
            cout<<"Max Force: "<<mf<<", energy: "<<currentE<<",  next frame to save: "<<nextFrameToSave<<endl;
        }
        ii++;
        };
//    cudaProfilerStop();


    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
