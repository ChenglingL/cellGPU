#include "std_include.h"
#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "vertexQuadraticEnergy.h"
#include "selfPropelledParticleDynamics.h"
#include "EnergyMinimizerFIRE2D.h"
#include "DatabaseNetCDFSPV.h"
#include "eigenMatrixInterface.h"
#include "twoValuesDatabase.h"
#include "nvtModelDatabase.h"

/*!
This is to run vertex model quenched from infinite T.
*/

//! A function of convenience for setting FIRE parameters
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
    //as in the examples in the main directory, there are a bunch of default parameters that
    //can be changed from the command line
    int numpts = 200;
    int USE_GPU = -1;
    int c;
    int tSteps = 5;
    int initSteps = 5;
    int Nconfigurations = 100;


    double dt = 0.1;
    double fraction = 0.8;
    double p0 = 4.0;
    double pf = 4.0;
    double a0 = 1.0;
    double alpha;
    double sizeRatio = 5.0 / 4.0;
    double KA = 1.0;
    double thresh = 1e-12;

    //This example is a bit more ragged than the others, and program_switch has been abused for testing features that have not been cleaned up yet
    int program_switch = 0;
    while((c=getopt(argc,argv,"k:n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:q:c:f:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 't': tSteps = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 'i': initSteps = atoi(optarg); break;
            case 'z': program_switch = atoi(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'k': KA = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'q': pf = atof(optarg); break;
            case 'f': fraction = atof(optarg); break;
            case 'a': a0 = atof(optarg); break;
            case 'y': sizeRatio = atof(optarg); break;
            case 'r': thresh = atof(optarg); break;
            case 'c': Nconfigurations = atof(optarg); break;
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

    clock_t t1,t2;
    bool reproducible = false;
    bool initializeGPU = true;

    alpha = sizeRatio * sizeRatio;

    if (USE_GPU >= 0)
        {
        bool gpu = chooseGPU(USE_GPU);
        if (!gpu) return 0;
        cudaSetDevice(USE_GPU);
        }
    else
        initializeGPU = false;

    char saveDirName[256];
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/vertexInherentEnergy/");
    char energyDataname[256];
    sprintf(energyDataname,"%smaxForceEnergy_N%i_p%.3f_KA%.4f_sizeRatio%.3f_fraction%.3f.nc",saveDirName,numpts,p0,KA,sizeRatio,fraction);
    shared_ptr<twoValuesDatabase> energyDat=make_shared<twoValuesDatabase>(energyDataname,NcFile::Replace);
    for (int idx = 0; idx < Nconfigurations; idx++)
    {

        //the voronoi model set up is just as before
        shared_ptr<VertexQuadraticEnergy> spv = make_shared<VertexQuadraticEnergy>(numpts,1.0,p0,reproducible,false,initializeGPU);
        //..and instead of a self-propelled cell equation of motion, we use a FIRE minimizer
        cout<<"ready for initialize fire"<<endl;
        shared_ptr<EnergyMinimizerFIRE> fireMinimizer = make_shared<EnergyMinimizerFIRE>(spv,initializeGPU);

        spv->setBidisperseCellPreferences(p0,alpha,fraction);
        //spv->setCellPreferencesUniform(1.0,p0);
        spv->setModuliUniform(KA,1.0);
        printf("initializing with KA = %f\t p_0 = %f\n",KA,p0);
        SimulationPtr sim = make_shared<Simulation>();

        sim->setConfiguration(spv);
        sim->addUpdater(fireMinimizer,spv);
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
        double mf=1.0;
        int Nfire=0;
        while (mf > thresh)
            {
            fireMinimizer->setMaximumIterations(tSteps);
            sim->performTimestep();
            spv->computeGeometryCPU();
            spv->computeForces();
            mf = sqrt(fireMinimizer->getMaxForce());
            cout<<"maxForce = "<<mf<<endl;
            Nfire++;
            if (mf < thresh)
                break;
            if (Nfire > initSteps)
                break;
            };
        // quasistatic pure shear
        double energy = spv->computeEnergy();

        cout<<"at p0="<<p0<<", size ratio="<<sizeRatio<<", fraction = "<<fraction<<", final energy: "<<energy<<endl;
        energyDat->writeValues(mf, energy);

    }
    


    return 0;
};
