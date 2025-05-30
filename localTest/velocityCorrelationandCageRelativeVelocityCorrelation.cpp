#include "std_include.h"

#include "cuda_runtime.h"
#include "cuda_profiler_api.h"


#include "Simulation.h"
#include "voronoiQuadraticEnergy.h"
#include "brownianParticleDynamics.h"
#include "NoseHooverChainNVT.h"
#include "nvtModelDatabase.h"
#include "logEquilibrationStateWriter.h"
#include "analysisPackage.h"
#include "periodicBoundaries.h"
#include "GlassyDynModelDatabase.h"




/*This is the nose-hoove test under PBD to verify the results from 2018 anomalous paper*/
int main(int argc, char*argv[])
{
    //...some default parameters
    int numpts = 4096; //number of cells
    int USE_GPU = -1; //0 or greater uses a gpu, any negative number runs on the cpu
    int c;
    int tSteps = 5; //number of time steps to run after initialization
    int initSteps = 100; //number of initialization steps
    double dt = 0.01; //the time step size
    double p0 = 3.8;  //the preferred perimeter
    double a0 = 1.0;  // the preferred area
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

    clock_t t1,t2; //clocks for timing information
    bool reproducible = false; // if you want random numbers with a more random seed each run, set this to false
    //check to see if we should run on a GPU
    bool initializeGPU = true;
    bool gpu = chooseGPU(USE_GPU);
    if (!gpu)
        initializeGPU = false;

    // std::vector<double> TNVT = {0.002, 0.0025, 0.0031, 0.004949, 0.005965, 0.007287, 0.009038, 0.01141, 0.01471, 0.01945, 0.02652, 0.03756, 0.05586, 0.08868};
    // std::vector<double> TimeNVT = {1000000.0, 1000000.0, 316227.76, 1000000.0, 1000000.0, 316227.76, 100000.0, 100000.0, 31622.77, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0};

    // std::vector<double> TBD = {0.002, 0.005, 0.007, 0.008, 0.009038, 0.01141, 0.01471, 0.01945, 0.02652, 0.03756, 0.05586, 0.08868};
    // std::vector<double> TimeBD = {31622.77, 31622.77, 31622.77, 31622.77, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0};
    std::vector<double> TNVT = {0.002, 0.0025, 0.0031,0.01, 0.01584893, 0.02511886 , 0.03981072, 0.06309573};
    std::vector<int> Ncells = {512, 1024,4096};


    for (int i=0;i<TNVT.size();i++){
        for (int idx=0;idx<10;idx++){
            for (int nnn=0;nnn<3;nnn++){
                char loadDatabaseName[256];
                //sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/preTauAlpha/data/glassyDynamics_N4096_p3.8000_T%.8f_waitingTime%.6f_idx%i.nc",TNVT[i],TimeNVT[i],idx);
                sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/AnalyticalG/data/N%i/nvt_N%i_p%.3f_T%.8f_%i.nc",Ncells[nnn],Ncells[nnn],p0,TNVT[i],idx);
                
                std::ifstream fileCheck(loadDatabaseName);
                if (!fileCheck.is_open()) {
                    std::cout << "File " << loadDatabaseName << " does not exist. Skipping." << std::endl;
                    fileCheck.close();
                    continue; 
                };
                nvtModelDatabase fluidConfigurations(Ncells[nnn],loadDatabaseName,NcFile::ReadOnly);

                std::vector<double> velocityCorrelationdatNVT(fluidConfigurations.GetNumRecs());
                std::vector<double> cageRelativevelocityCorrelationdatNVT(fluidConfigurations.GetNumRecs());
                cout << "reading record from " << loadDatabaseName << endl;
                shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(Ncells[nnn],a0,p0,reproducible,initializeGPU);
                fluidConfigurations.readState(voronoiModel,0,true);
                dynamicalFeatures dynFeat(voronoiModel->returnVelocities());
                dynFeat.setCageNeighbors(voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx); 
                
                for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
                    fluidConfigurations.readState(voronoiModel,rec,false);
                    velocityCorrelationdatNVT[rec] = dynFeat.computeVelocityCorrelation(voronoiModel->returnVelocities());   
                    cageRelativevelocityCorrelationdatNVT[rec] = dynFeat.computeCageRelativeVelocityCorrelation(voronoiModel->returnVelocities());       
                };   
                //save the data
                char velocityCorrelationNameNVT[256];
                char cageRelativevelocityCorrelationNameNVT[256];
                //sprintf(velocityCorrelationNameNVT,"/home/chengling/Research/Project/Cell/preTauAlpha/data/velocityCoorelationNVT_N4096_p3.8000_T%.8f_waitingTime%.6f_idx%i.csv",TNVT[i],TimeNVT[i],idx);
                //sprintf(cageRelativevelocityCorrelationNameNVT,"/home/chengling/Research/Project/Cell/preTauAlpha/data/cageRelativeVelocityCorrelationNVT_N4096_p3.8000_T%.8f_waitingTime%.6f_idx%i.csv",TNVT[i],TimeNVT[i],idx);
                sprintf(velocityCorrelationNameNVT,"/home/chengling/Research/Project/Cell/AnalyticalG/data/N%i/nvt_VelCor_N%i_p%.3fT%.8f_%i.csv",Ncells[nnn],Ncells[nnn],p0,TNVT[i],idx);
                sprintf(cageRelativevelocityCorrelationNameNVT,"/home/chengling/Research/Project/Cell/AnalyticalG/data/N%i/nvt_CRVelCor_N%i_p%.3f_T%.8f_%i.csv",Ncells[nnn],Ncells[nnn],p0,TNVT[i],idx);

                std::ofstream outFile1(velocityCorrelationNameNVT);
                if (outFile1.is_open()) {
                    for (int ii = 0; ii < velocityCorrelationdatNVT.size(); ++ii) {
                        outFile1 << velocityCorrelationdatNVT[ii];
                        if (ii != velocityCorrelationdatNVT.size() - 1) {
                            outFile1 << ','; // Add a comma if it's not the last element
                        }
                    }
                    outFile1.close();
                    std::cout << "Vector saved to " << velocityCorrelationNameNVT << " successfully." << std::endl;
                } else {
                    std::cerr << "Unable to open file." << std::endl;
                };
                std::ofstream outFile2(cageRelativevelocityCorrelationNameNVT);
                if (outFile2.is_open()) {
                    for (int ii = 0; ii < cageRelativevelocityCorrelationdatNVT.size(); ++ii) {
                        outFile2 << cageRelativevelocityCorrelationdatNVT[ii];
                        if (ii != cageRelativevelocityCorrelationdatNVT.size() - 1) {
                            outFile2 << ','; // Add a comma if it's not the last element
                        }
                    }
                    outFile2.close();
                    std::cout << "Vector saved to " << cageRelativevelocityCorrelationNameNVT << " successfully." << std::endl;
                } else {
                    std::cerr << "Unable to open file." << std::endl;
                };
            }
        }
    }


    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
