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


/*!
This file compiles to produce an executable that can be used to reproduce the timing information
in the main cellGPU paper. It sets up a simulation that takes control of a voronoi model and a simple
model of active motility
NOTE that in the output, the forces and the positions are not, by default, synchronized! The NcFile
records the force from the last time "computeForces()" was called, and generally the equations of motion will 
move the positions. If you want the forces and the positions to be sync'ed, you should call the
Voronoi model's computeForces() funciton right before saving a state.
*/

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
    

    clock_t t1,t2; //clocks for timing information
    bool reproducible = false; // if you want random numbers with a more random seed each run, set this to false
    //check to see if we should run on a GPU
    bool initializeGPU = true;
    bool gpu = chooseGPU(USE_GPU);
    if (!gpu)
        initializeGPU = false;

    std::vector<double> TBD = {0.002, 0.005, 0.007, 0.008, 0.009038, 0.01141, 0.01471, 0.01945, 0.02652, 0.03756, 0.05586, 0.08868};
    std::vector<double> TimeBD = {31622.77, 31622.77, 31622.77, 31622.77, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0};

    std::vector<double> TNVT = {0.002, 0.0025, 0.0031, 0.004949, 0.005965, 0.007287, 0.009038, 0.01141, 0.01471, 0.01945, 0.02652, 0.03756, 0.05586, 0.08868};
    std::vector<double> TimeNVT = {1000000.0, 1000000.0, 316227.76, 1000000.0, 1000000.0, 316227.76, 100000.0, 100000.0, 31622.77, 10000.0, 10000.0, 10000.0, 10000.0, 10000.0};

    for (int i=0;i<TBD.size();i++){
        for (int idx=0;idx<10;idx++){
            char loadDatabaseName[256];
            sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/preTauAlpha/data/glassyBrownianDynamics_N4096_p3.8000_T%.8f_waitingTime%.6f_idx%i.nc",TBD[i],TimeBD[i],idx);
            
            std::ifstream fileCheck(loadDatabaseName);
            if (!fileCheck.is_open()) {
                std::cout << "File " << loadDatabaseName << " does not exist. Skipping." << std::endl;
                fileCheck.close();
                continue; 
            };
            

            nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);
            std::vector<double> cageEnhancedMSDdatBD(fluidConfigurations.GetNumRecs());

            shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,a0,p0,reproducible,initializeGPU);
            fluidConfigurations.readState(voronoiModel,0,true);
            dynamicalFeatures dynFeat(voronoiModel->returnPositions(),voronoiModel->Box);
            dynFeat.setCageNeighbors(voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx);   
            cout<<fluidConfigurations.GetNumRecs()<<endl; 
            cout << "reading record from " << loadDatabaseName << endl;
            for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
                fluidConfigurations.readState(voronoiModel,rec,false);
                cageEnhancedMSDdatBD[rec] = dynFeat.computeCageEnhancedMSD(voronoiModel->returnPositions());         
            };  

            char cageEnhancedMSDnameBD[256];
            sprintf(cageEnhancedMSDnameBD,"/home/chengling/Research/Project/Cell/preTauAlpha/data/cageEnhancedMSDBDModified.8000_T%.8f_waitingTime%.6f_idx%i.csv",TBD[i],TimeBD[i],idx);
            std::ofstream outFile1(cageEnhancedMSDnameBD);
            if (outFile1.is_open()) {
                for (int ii = 0; ii < cageEnhancedMSDdatBD.size(); ++ii) {
                    outFile1 << cageEnhancedMSDdatBD[ii];
                    if (ii != cageEnhancedMSDdatBD.size() - 1) {
                        outFile1 << ','; // Add a comma if it's not the last element
                    }
                }
                outFile1.close();
                std::cout << "Vector saved to " << cageEnhancedMSDnameBD << " successfully." << std::endl;
            } else {
                std::cerr << "Unable to open file." << std::endl;
            };

        }
    };

    for (int i=0;i<TNVT.size();i++){
        for (int idx=0;idx<10;idx++){
            char loadDatabaseName[256];
            sprintf(loadDatabaseName,"/home/chengling/Research/Project/Cell/preTauAlpha/data/glassyDynamics_N4096_p3.8000_T%.8f_waitingTime%.6f_idx%i.nc",TNVT[i],TimeNVT[i],idx);
            
            std::ifstream fileCheck(loadDatabaseName);
            if (!fileCheck.is_open()) {
                std::cout << "File " << loadDatabaseName << " does not exist. Skipping." << std::endl;
                fileCheck.close();
                continue; 
            };
            nvtModelDatabase fluidConfigurations(numpts,loadDatabaseName,NcFile::ReadOnly);

            std::vector<double> cageEnhancedMSDdatNVT(fluidConfigurations.GetNumRecs());

            shared_ptr<VoronoiQuadraticEnergy> voronoiModel  = make_shared<VoronoiQuadraticEnergy>(numpts,a0,p0,reproducible,initializeGPU);
            fluidConfigurations.readState(voronoiModel,0,true);
            dynamicalFeatures dynFeat(voronoiModel->returnPositions(),voronoiModel->Box);
            dynFeat.setCageNeighbors(voronoiModel->neighbors,voronoiModel->neighborNum,voronoiModel->n_idx); 
            cout << "reading record from " << loadDatabaseName << endl;
            for(int rec=0;rec<fluidConfigurations.GetNumRecs();rec++){
                fluidConfigurations.readState(voronoiModel,rec,false);
                cageEnhancedMSDdatNVT[rec] = dynFeat.computeCageEnhancedMSD(voronoiModel->returnPositions());        
            };   
            //save the data
            char cageEnhancedMSDnameNVT[256];
            sprintf(cageEnhancedMSDnameNVT,"/home/chengling/Research/Project/Cell/preTauAlpha/data/cageEnhancedMSDNVTModified_N4096_p3.8000_T%.8f_waitingTime%.6f_idx%i.csv",TNVT[i],TimeNVT[i],idx);
            std::ofstream outFile1(cageEnhancedMSDnameNVT);
            if (outFile1.is_open()) {
                for (int ii = 0; ii < cageEnhancedMSDdatNVT.size(); ++ii) {
                    outFile1 << cageEnhancedMSDdatNVT[ii];
                    if (ii != cageEnhancedMSDdatNVT.size() - 1) {
                        outFile1 << ','; // Add a comma if it's not the last element
                    }
                }
                outFile1.close();
                std::cout << "Vector saved to " << cageEnhancedMSDnameNVT << " successfully." << std::endl;
            } else {
                std::cerr << "Unable to open file." << std::endl;
            };

        }
    }



    if(initializeGPU)
        cudaDeviceReset();
    return 0;
};
