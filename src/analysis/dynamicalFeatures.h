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

        //!set the list of neighbors forming initial cages of the particles (to be used for cage-relative calculations)
        void setCageNeighbors(GPUArray<int> &neighbors, GPUArray<int> &neighborNum, Index2D n_idx);

        //!Compute the mean squared displacement of the passed vector from the initial positions
        double computeMSD(GPUArray<double2> &currentPos);

        //!compute the overlap function
        double computeOverlapFunction(GPUArray<double2> &currentPos, double cutoff = 0.5);

        //!compute cage relative MSD
        double computeCageRelativeMSD(GPUArray<double2> &currentPos);

        //!a helper function that computes vectors of current displacements and cage relative displacements
        void computeCageRelativeDisplacements(GPUArray<double2> &currentPos);

    protected:
        //!the box defining the periodic domain
        PeriodicBoxPtr Box;
        //!the initial positions
        vector<double2> iPos;
        //! a vector of displacements relative to the initializing positions 
        vector<double2> currentDisplacements;
        //!the vector of current cage releative displacements
        vector<double2> cageRelativeDisplacements;
        //!the number of double2's
        int N;
        vector<vector<int>> cageNeighbors;
        Index2D nIdx;
    };
#endif
