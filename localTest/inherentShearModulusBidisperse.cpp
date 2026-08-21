#include "std_include.h"
#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "selfPropelledParticleDynamics.h"
#include "EnergyMinimizerFIRE2D.h"
#include "DatabaseNetCDFSPV.h"
#include "eigenMatrixInterface.h"
#include "twoValuesDatabase.h"
#include "nvtModelDatabase.h"

/*!
This is to investigate if the critical point of rigidity transition is impacted by bidispersity
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

    int failureNumber = 100; // how many numbers of initial runs to fail before breaking
    while((c=getopt(argc,argv,"k:n:g:m:s:r:a:i:v:b:x:y:z:p:t:e:q:c:f:")) != -1)
        switch(c)
        {
            case 'n': numpts = atoi(optarg); break;
            case 't': tSteps = atoi(optarg); break;
            case 'g': USE_GPU = atoi(optarg); break;
            case 'i': initSteps = atoi(optarg); break;
            case 'z': failureNumber = atoi(optarg); break;
            case 'e': dt = atof(optarg); break;
            case 'k': KA = atof(optarg); break;
            case 'p': p0 = atof(optarg); break;
            case 'q': pf = atof(optarg); break;
            case 'a': a0 = atof(optarg); break;
            case 'f': fraction = atof(optarg); break;
            case 'r': thresh = atof(optarg); break;
            case 'y': sizeRatio = atof(optarg); break;
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
    sprintf(saveDirName, "/home/chengling/Research/Project/Cell/2dVoronoiBidisperse/");
    char inherentgDataname[256];
    sprintf(inherentgDataname,"%smaxForce&ShearModulus_N%i_p%.3f_KA%.4f_sizeRatio%.3f_fraction%.3f.nc.nc",saveDirName,numpts,p0,KA,sizeRatio,fraction);
    char energyDataname[256];
    sprintf(energyDataname,"%senergy&ShearModulus_N%i_p%.3f_KA%.4f_sizeRatio%.3f_fraction%.3f.nc.nc",saveDirName,numpts,p0,KA,sizeRatio,fraction);

    shared_ptr<twoValuesDatabase> inherentgDat=make_shared<twoValuesDatabase>(inherentgDataname,NcFile::Replace);
    shared_ptr<twoValuesDatabase> energyDat=make_shared<twoValuesDatabase>(energyDataname,NcFile::Replace);

    int idx = 0;
    int fail_count = 0;
    while (idx < Nconfigurations)
    {
        if (fail_count >= failureNumber)
        {
            cout<<failureNumber<<" attempts of FIRE are failed. Terminate the simulation."<<endl;
            break;
        }
        
        //the voronoi model set up is just as before
        shared_ptr<VoronoiQuadraticEnergy> spv = make_shared<VoronoiQuadraticEnergy>(numpts,1.0,p0,reproducible,initializeGPU);
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
        
        fireMinimizer->setMaximumIterations(tSteps);
        sim->performTimestep();
        spv->computeGeometryCPU();
        spv->computeForces();
        mf = spv->getMaxForce();
        printf("maxForce = %g\n",mf);

        if (mf > thresh)
        {
            fail_count ++ ;
            continue;
        }
        
        idx++;

        t2=clock();
        double steptime = (t2-t1)/(double)CLOCKS_PER_SEC;
        cout << "minimization cost ~ " << steptime << " s" << endl;


        //build the dynamical matrix
        spv->computeGeometryCPU();
        vector<int2> rowCols;
        vector<double> entries;
        spv->getDynMatEntries(rowCols,entries,1.0,1.0);
        printf("Number of partial entries: %lu\n",rowCols.size());
        EigMat D(2*numpts);
        for (int ii = 0; ii < rowCols.size(); ++ii)
            {
            int2 ij = rowCols[ii];
            D.placeElementSymmetric(ij.x,ij.y,entries[ii]);
            };

        D.SASolve();
        //cout<<"D.solve"<<endl;

        //calculate the non-affine relaxation
        double nonaffine = 0.0;
        vector<double2> derivative;
        spv->getd2Edgammadr(derivative);
        //cout<<"getd2Edgammadr"<<endl;
        for (int i = 0; i < D.eigenvalues.size(); i++)
        {
            //cout<<"eigen value"<<D.eigenvalues[i]<<endl;
            if (D.eigenvalues[i]>thresh)
            {
                vector<double> localEigenVector;
                D.getEvec(i,localEigenVector);
                double localnonA = 0.0;
                for (int ii = 0; ii < numpts; ++ii)
                {
                    localnonA += derivative[ii].x * localEigenVector[2*ii];
                    localnonA += derivative[ii].y * localEigenVector[2*ii+1];
                };
                nonaffine += 1.0/D.eigenvalues[i] * localnonA * localnonA;
            }

        }
        double d2edg2=spv->getd2Edgammadgamma();
        double g = (d2edg2 - nonaffine)/numpts;
        cout<<"the affine shear modulus is "<<d2edg2/numpts<<" and the non-affine shear modulus is "<<g<<endl;
        inherentgDat->writeValues(mf,g);
        energyDat->writeValues(spv->computeEnergy(),g);
    }
    


    return 0;
};
