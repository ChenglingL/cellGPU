#ifndef VoronoiQuadraticEnergy_H
#define VoronoiQuadraticEnergy_H

#include "voronoiModelBase.h"
#include "voronoiQuadraticEnergy.cuh"

/*! \file voronoiQuadraticEnergy.h */
//!Implement a 2D Voronoi model, with and without some extra bells and whistles, using kernels in \ref spvKernels
/*!
 *A child class of voronoiModelBase, this implements a Voronoi model in 2D. This involves mostly calculating
  the forces in the Voronoi model. Optimizing these procedures for
  hybrid CPU/GPU-based computation involves declaring and maintaining several related auxiliary
  data structures that capture different features of the local topology and local geoemetry for each
  cell.
 */
class VoronoiQuadraticEnergy : public voronoiModelBase
    {
    public:
        //!initialize with random positions in a square box
        VoronoiQuadraticEnergy(int n,bool reprod = false, bool usegpu = true);
        //! initialize with random positions and set all cells to have uniform target A_0 and P_0 parameters
        VoronoiQuadraticEnergy(int n, double A0, double P0,bool reprod = false, bool gpu = true);
        //!Blank constructor
        VoronoiQuadraticEnergy(){};

        //!Initialize voronoiQuadraticEnergy and call the initializer chain
        void initializeVoronoiQuadraticEnergy(int n, bool useGPU = true);

        //!compute the geometry and get the forces
        virtual void computeForces();

        //!compute the quadratic energy functional
        virtual double computeEnergy();

        //cell-dynamics related functions...these call functions in the next section
        //in general, these functions are the common calls, and test flags to know whether to call specific versions of specialty functions

        //!Compute force sets on the GPU
        virtual void ComputeForceSetsGPU();
        //!Add up the force sets to get the net force per particle on the GPU
        void SumForcesGPU();

        //CPU functions
        //!Compute the net force on particle i on the CPU
        virtual void computeVoronoiForceCPU(int i);

        //GPU functions
        //!call gpu_force_sets kernel caller
        virtual void computeVoronoiForceSetsGPU();
        //! call gpu_sum_force_sets kernel caller
        void sumForceSets();
        //!call gpu_sum_force_sets_with_exclusions kernel caller
        void sumForceSetsWithExclusions();

        //!Report various cell infor for testing and debugging
        void reportCellInfo();
        //!Report information about net forces...
        void reportForces(bool verbose);

        //!Report information about net forces...
        void reportTotalForce();

        //!Save tuples for half of the dynamical matrix
        virtual void getDynMatEntries(vector<int2> &rcs, vector<double> &vals,double unstress = 1.0, double stress = 1.0);

        //!calculate the current global off-diagonal stress
        virtual double getSigmaXY();

        //!calculate the current global diagonal stress in x direction
        virtual double getSigmaXX();

        //!calculate the current global diagonal stress in y direction
        virtual double getSigmaYY();

        //!calculate the current global off-diagonal stress for each cell
        virtual double getSigmaXY(vector<double> &sigmai);

        //!calculate the current global d2Edgammadgamma
        virtual double getd2Edgammadgamma();

        //!calculate the current global getd2Edepsilondepsilon for pure shear
        virtual double getd2Edepsilondepsilon();

        //!calculate the current global getdEdepsilon for pure shear
        virtual double getdEdepsilon();

        //!calculate the current global getd2EdepsilonXdepsilonX
        virtual double getd2EdepsilonXdepsilonX();

        //!calculate the current global getd2EdepsilonYdepsilonY
        virtual double getd2EdepsilonYdepsilonY();

        //!calculate the current global d2Edgammadr for the shear modulus of inherent states
        virtual void getd2Edgammadr(vector<double2> &d2Edgammadr);

        //!calculate the current d2Edgammadgamma for each cell and return the global d2Edgammadgamma
        virtual double getd2Edgammadgamma(vector<double> &d2Eidgammadgamma);

        //!calculate the current d2Edgammadgamma for each cell and return the global d2Edgammadgamma
        //! Using the method to reproduce 2018 no jamming transition paper
        virtual double getd2EdgammadgammaOldPaper();

        //!calculate the current global d2Edgammadr for the shear modulus of inherent states
        //! Using the method to reproduce 2018 no jamming transition paper and this is the corrected one
        virtual void getd2EdgammadrOldPaper(vector<double2> &d2Edgammadr);

        //!calculate the current global d2Edgammadr for the shear modulus of inherent states
        //! Using the method to reproduce 2018 no jamming transition paper
        virtual void getd2EdgammadrOldPaperWrong(vector<double2> &d2Edgammadr);

        //!calculate the current sigmaXY for cells on the upper/lower boundary. This is equivilent to what's coded in 3D Voronoi
        //! Using the method to reproduce 2018 no jamming transition paper
        virtual double getSigmaXYonBoundary();

    protected:
        //! Second derivative of the energy w/r/t cell positions...for getting dynMat info
        Matrix2x2 d2Edridrj(int i, int j, neighborType neighbor,double unstress = 1.0, double stress = 1.0);

        //! First derivative of the energy of cell i w/r/t the position of nth vertex of cell i
        double2 deidHn(int i,int nn);

        //! Second derivative of the energy of cell i w/r/t the position of nth vertex of cell i and the position of jth vertex of cell i
        Matrix2x2 d2eidHndHj(int i,int nn, int j);

        //calculate the derivative of energy i w.r.t positions of cell j and k
        Matrix2x2 d2Eidrjdrk(int i, int j, int k);

    //be friends with the associated Database class so it can access data to store or read
    friend class SPVDatabaseNetCDF;
    friend class nvtModelDatabase;
    friend class nvtModelDatabase;
    friend class GlassyDynModelDatabase;
    };

#endif
