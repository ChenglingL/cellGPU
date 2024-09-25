#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"

#include "trajectoryModelDatabase.h"
#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "brownianParticleDynamics.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "twoValuesDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "periodicBoundaries.h"
#include "GlassyDynModelDatabase.h"
#include "EnergyMinimizerFIRE2D.h"
#include <filesystem>
#include <cstring>
#include "displacementModelDatabase.h"


/*!
This file is used to test how FIRE works fpr p0=3.85
*/
void setFIREParameters(shared_ptr<EnergyMinimizerFIRE> emin, double deltaT, double alphaStart,
        double deltaTMax, double deltaTInc, double deltaTDec, double alphaDec, int nMin,
        double forceCutoff)
    {
    emin->setDeltaT(deltaT);
    emin->setAlphaStart(alphaStart);
    emin->setDeltaTMax(deltaTMax);
    emin->setDeltaTInc(deltaTInc);
    emin->setDeltaTDec(deltaTDec);
    emin->setAlphaDec(alphaDec);
    emin->setNMin(nMin);
    emin->setForceCutoff(forceCutoff);
    };

int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 200; //number of cells
    int USE_GPU = 0; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;

    int tSteps = 5;
    int initSteps = 5;

    double tauEstimate = 10;
    double equilibrationWaitingTimeMultiple = 10.0;
    double numberOfRelaxationTimes =10.0;
    int numberofDerivatives = 50000;

    double waitingtime=100000;
    double dt = 0.01; //the time step size
    double T = 0.01;  // the target temperature
    double T0 = 0.1; // the temperature of the database to load from
    double p0 = 3.8; // the base p0 of the database to load from
    int recordIndex =0; // which element of the database to load the configuration from
    int Nchain = 4;     //The number of thermostats to chain together


    double pf = 4.0;
    double a0 = 1.0;
    double v0 = 0.1;
    double KA = 1.0;
    double thresh = 1e-12;

    //The defaults can be overridden from the command line
    while((c=getopt(argc,argv,"n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:k:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 't': tauEstimate = atof(optarg); break;
            case 's': equilibrationWaitingTimeMultiple = atof(optarg); break;
            case 'm': waitingtime = atof(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'v': T = atof(optarg); break;
            case 'l': T0 = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'k': tSteps = atoi(optarg); break;
            case 'i': initSteps = atoi(optarg); break;
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

    clock_t t1,t2,t3; //clocks for timing information
    bool reproducible = true; // if you want random numbers with a more random seed each run, set this to false
    //check to see if we should run on a GPU
    bool initializeGPU = true;
    bool gpu = chooseGPU(USE_GPU);
    if (!gpu)
        initializeGPU = false;
    char loaddataname[256];
    char loaddataGlassyname[256];
    char loaddataMissingname[256]; //see if we have missingTrajectory so that the time stamps are the same
    char savefolder[256];
    char loadfolder[256];
    char inherentStatesDataName[256];
    sprintf(savefolder,"/home/chengling/Research/Project/Cell/MCT/data/inherentStates/N%i/",numpts);
    sprintf(loadfolder,"/home/chengling/Research/Project/Cell/glassyDynamics/N%i/productionRuns/p%.3f/",numpts,p0);
    namespace fs = std::filesystem;
    if (waitingtime == 100000) //if waiting time is an input of .cpp then use that one as waitingtime
    {
        waitingtime = max(10000.,floor(tauEstimate * equilibrationWaitingTimeMultiple));
    }
    sprintf(loaddataGlassyname,"%sglassyDynamics_N%i_p%.4f_T%.8f_waitingTime%.0f_idx%i.nc",loadfolder,numpts,p0,T,waitingtime,recordIndex);
    sprintf(loaddataMissingname,"%smissingTrajectory_N%i_p%.4f_T%.8f_idx%i.nc",loadfolder,numpts,p0,T,recordIndex);
    char inherentgDataname[256];
    sprintf(inherentgDataname,"%sFIREtest_success_time_N%i_p%.4f_T%.8f_idx%i.nc",savefolder,numpts,p0,T,recordIndex);
    shared_ptr<twoValuesDatabase> inherentgDat=make_shared<twoValuesDatabase>(inherentgDataname,NcFile::Replace);
    sprintf(inherentStatesDataName,"%sinherentStates_N%i_p%.4f_T%.8f_idx%i.nc",savefolder,numpts,p0,T,recordIndex);
    shared_ptr<trajectoryModelDatabase> inherentStatesDat=make_shared<trajectoryModelDatabase>(numpts,inherentStatesDataName,NcFile::Replace);

    if (fs::exists(loaddataMissingname)) {
        cout << "reading record from " << loaddataMissingname << endl;
        std::strcpy(loaddataname,loaddataMissingname);
    } else if (fs::exists(loaddataGlassyname)) {
        cout << "reading record from " << loaddataGlassyname << endl;
        std::strcpy(loaddataname,loaddataGlassyname);
    } else {
        std::cout <<loaddataMissingname<<" and "<<loaddataGlassyname<< " does not exist." << std::endl;
        abort();
    }
    trajectoryModelDatabase fluidConfigurations(numpts,loaddataname,NcFile::ReadOnly);

    shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
    fluidConfigurations.readState(voronoiModel,0);
    voronoiModel->enforceTopology();
    dynamicalFeatures dynFeat(voronoiModel->returnPositions(),voronoiModel->Box);
 
    for(int rec=fluidConfigurations.GetNumRecs()-10;rec<fluidConfigurations.GetNumRecs();rec++){
        fluidConfigurations.readState(voronoiModel,rec);
        cout<<"ready for initialize FIRE"<<endl;
        shared_ptr<EnergyMinimizerFIRE> fireMinimizer = make_shared<EnergyMinimizerFIRE>(voronoiModel,initializeGPU);
        SimulationPtr sim = make_shared<Simulation>();
        sim->setConfiguration(voronoiModel);
        sim->addUpdater(fireMinimizer,voronoiModel);
        sim->setCPUOperation(!initializeGPU);

        //initialize FIRE parameters...these parameters are pretty standard for many MD settings, and shouldn't need too much adjustment
        double astart, adec, tdec, tinc; int nmin;
        nmin = 5;
        astart = .1;
        adec= 0.99;
        tinc = 1.1;
        tdec = 0.5;
        setFIREParameters(fireMinimizer,dt,astart,50*dt,tinc,tdec,adec,nmin,thresh);
        t1=clock();

        //minimize to tolerance
        double mf;
        for (int ii = 0; ii < initSteps; ++ii)
            {
            fireMinimizer->setMaximumIterations((tSteps)*(1+ii));
            clock_t tMinize1,tMinize2;//THis is to prevent neighbor list explotion
            tMinize1=clock();
            sim->performTimestep();
            tMinize2=clock();
            double minimizeTime = (tMinize2-tMinize1)/(double)CLOCKS_PER_SEC;
            if(minimizeTime > 10)
            {
                cout<<"Minimization failure: neighbor number explodes"<<endl;
                char dataname[256];
                sprintf(dataname,"%sFIREflaseConf_N%i_p%.3f_T%.8f_%i.nc",savefolder,numpts,p0,T,recordIndex);
                cout<<"store the false conf in "<<dataname<<endl;
                shared_ptr<GlassyDynModelDatabase> falseDat=make_shared<GlassyDynModelDatabase>(numpts,dataname,NcFile::Replace);
                falseDat->writeState(voronoiModel);
                throw std::exception();
            }
            voronoiModel->computeGeometryCPU();
            voronoiModel->computeForces();
            mf = voronoiModel->getMaxForce();
            printf("maxForce = %g\n",mf);
            t3=clock();
            double steptime = (t3-t1)/(double)CLOCKS_PER_SEC;
            if (steptime > 1800){
                cout<<"take too long to minimize"<<endl;
                break;
            }
                
            if (mf < thresh)
                break;
            };

        t2=clock();
        double steptime = (t2-t1)/(double)CLOCKS_PER_SEC;
        cout << "minimization was ~ " << steptime << endl;
        inherentStatesDat->writeState(voronoiModel,steptime);

        if (mf > thresh) inherentgDat->writeValues(0,steptime);
        else if (mf < thresh) inherentgDat->writeValues(1,steptime);

    };   
        



    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
