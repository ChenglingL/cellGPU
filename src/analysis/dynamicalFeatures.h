#ifndef dynamicalFeatures_H
#define dynamicalFeatures_H

#include "std_include.h"
#include "functions.h"
#include "periodicBoundaries.h"
#include "indexer.h"

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
        double computeMSD(GPUArray<double2> &currentPos);

        //!compute the overlap function
        double computeOverlapFunction(GPUArray<double2> &currentPos, double cutoff = 0.5);
        //!compute cage relative SISF with 2D angular averaging
        double computeSISF(GPUArray<double2> &currentPos, double k = 6.28319);

        //!compute cage relative MSD
        double computeCageRelativeMSD(GPUArray<double2> &currentPos);
        //!compute cage relative SISF with 2D angular averaging
        double computeCageRelativeSISF(GPUArray<double2> &currentPos, double k = 6.28319);
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
    protected:
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
        //!the vector of current cage displacements
        vector<double2> cageDisplacements;
        //!the vector of current displacements + the displacemennts of their cages
        vector<double2> cageEnhancedDisplacements;
        //!the vector of cage relative velocity correlations
        vector<double2> currentCageVelocity;

        //!the number of double2's
        int N;
        vector<vector<int>> cageNeighbors;
        Index2D nIdx;
    };
#endif
