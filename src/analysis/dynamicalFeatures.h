#ifndef dynamicalFeatures_H
#define dynamicalFeatures_H

#include "std_include.h"
#include "functions.h"
#include "periodicBoundaries.h"
#include "indexer.h"
#include <unordered_set>
/*! \file dynamicalFeatures.h */

//! A class that calculates various dynamical features for 2D systems
class dynamicalFeatures
    {
    public:
        //!The constructor takes in a defining set of boundary conditions
        dynamicalFeatures(GPUArray<double2> &initialPos, PeriodicBoxPtr _bx, double fractionAnalyzed = 1.0);

        //!The constructor takes in a defining set of boundary conditions
        dynamicalFeatures(GPUArray<double2> &initialVel);

        //!set the list of neighbors forming initial cages of the particles (to be used for cage-relative calculations)
        void setCageNeighbors(GPUArray<int> &neighbors, GPUArray<int> &neighborNum, Index2D n_idx);

        //!Compute the mean squared displacement of the passed vector from the initial positions
        double computeMSD(GPUArray<double2> &currentPos, GPUArray<double2> &previousPos, vector<int2> &previousWhichBox);
        //a helper function that computes the true (no more PBD) mean squared displacement of the passed vector from the initial positions
        void computeTrueDisplacements(GPUArray<double2> &currentPos, GPUArray<double2> &previousPos, vector<int2> &previousWhichBox);

        //!compute the overlap function
        double computeOverlapFunction(GPUArray<double2> &currentPos, double cutoff = 0.5);
        //!compute the overlap function for neighbors
        double computeNeighborOverlapFunction(GPUArray<int> &neighbors, GPUArray<int> &neighborNum, Index2D n_idx);
        //!compute the overlap function
        double computeCageRelativeOverlapFunction(GPUArray<double2> &currentPos, double cutoff = 0.5);
        //!compute cage relative SISF with 2D angular averaging
        double computeSISF(GPUArray<double2> &currentPos, double k = 6.28319);
        //!compute cage relative SISF with 2D angular averaging
        double computeScatteringFuncion(GPUArray<double2> &currentPos, double k = 6.28319);

        //!compute cage relative MSD
        double computeCageRelativeMSD(GPUArray<double2> &currentPos, GPUArray<double2> &previousPos, vector<int2> &previousWhichBox);
        //a helper function that computes the true (no more PBD) cage relative displacement
        void computeCageRelativeTrueDisplacements(GPUArray<double2> &currentPos, GPUArray<double2> &previousPos, vector<int2> &previousWhichBox);
        //!compute cage relative SISF with 2D angular averaging
        double computeCageRelativeSISF(GPUArray<double2> &currentPos, double k = 6.28319);
        //!compute chi_4 and F_s (result.x = Fs, result.y=chi_4)
        double2 computeFsChi4(GPUArray<double2> &currentPos, double k = 6.28319);
        //!compute cage-relative verions of above function
        double2 computeCageRelativeFsChi4(GPUArray<double2> &currentPos, double k = 6.28319);
        //!compute cage-relative overlap function and chi4 from overlapfunction (result.x = overlap function, result.y=chi_4)
        double2 computeCageRelativeOverlapChi4(GPUArray<double2> &currentPos, double cutoff);
        //!compute a mobility correlation function
        double computeCageRelativeMobilityCorrelation(GPUArray<double2> &currentPos);


        //!compute *un-normalized* flenner-Szamel psi_6 bond correlation decay (i.e., without the average |\psi_6|^2) that would make the function 1 at t=0. return.x is real, return.y is imaginary part
        double2 computeOrientationalCorrelationFunction(GPUArray<double2> &currentPos,GPUArray<int> &currentNeighbors, GPUArray<int> &currentNeighborNum, Index2D n_idx, int n=6);
        //!compute cage MSD
        double computeCageMSD(GPUArray<double2> &currentPos);
        //!compute cage enhanced MSD
        double computeCageEnhancedMSD(GPUArray<double2> &currentPos);
        //!compute the velocity correlations
        double computeVelocityCorrelation(GPUArray<double2> &currentVel);
        //!compute the correlations between the velocity of the cell and it's cage
        double computeCageRelativeVelocityCorrelation(GPUArray<double2> &currentVel);

        //!a helper function that computes vectors of current displacements and cage relative displacements
        void computeCageRelativeDisplacements(GPUArray<double2> &currentPos);
        //!a helper function that computes vectors of current displacements
        void computeDisplacements(GPUArray<double2> &currentPos);


        //!helper function that computes the angular average self-intermediate scattering function associated with a vector of displacements
        double angularAverageSISF(vector<double2> &displacements, double k);
        //!helper function that computes the mean dot product of a vector of double2's
        double MSDhelper(vector<double2> &displacements);

        //!helper function that computes the angular average of <F_s^2(q,t)>
        double chi4Helper(vector<double2> &displacements, double k);
        //!helper function that computes the average of <Q^2(t)>
        double overlapChi4Helper(vector<double2> &displacements, double cutoff);
    
        //!the box defining the periodic domain
        PeriodicBoxPtr Box;
        //!the initial positions
        vector<double2> iPos;
        //!the initial velocities
        vector<double2> iVel;
        //! a vector of displacements relative to the initializing positions 
        vector<double2> currentDisplacements;
        //!the vector of current cage releative displacements
        vector<double2> cageRelativeDisplacements;
        //! a vector of true (no PBD) displacements relative to the initializing positions 
        vector<double2> currentTrueDisplacements;
        //!the vector of true (no PBD)current cage releative displacements
        vector<double2> cageRelativeTrueDisplacements;
        //!the vector of current cage displacements
        vector<double2> cageDisplacements;
        //!the vector of current displacements + the displacemennts of their cages
        vector<double2> cageEnhancedDisplacements;
        //!the vector of cage relative velocity correlations
        vector<double2> currentCageVelocity;
        bool initialBondOrderComputed = false;
        vector<double2> initialConjugateBondOrder;

        //!the number of double2's
        int N;
        vector<vector<int>> cageNeighbors;
        Index2D nIdx;
    };
#endif
