#ifndef DATABASE_test_H
#define DATABASE_test_H

#include "voronoiQuadraticEnergy.h"
#include "dynamicalFeatures.h"
#include "DatabaseNetCDF.h"

/*! \file testModelDatabase.h */
//!Simple databse for reading/writing 2d spv states
/*!
Class for a state database for a 2d delaunay triangulation
the box dimensions are stored, the 2d unwrapped coordinate of the delaunay vertices,
and the shape index parameter for each vertex
*/
class testModelDatabase : public BaseDatabaseNetCDF
{
private:
    typedef shared_ptr<Simple2DCell> STATE;
    int Nv; //!< number of vertices in delaunay triangulation
    NcDim *recDim, *NvDim, *dofDim, *boxDim, *unitDim, *neighborDim; //!< NcDims we'll use
    //!Currently using "additionalData" to hold target a_0 and p_0 information
    NcVar *posVar, *velVar, *typeVar, *additionalDataVar, *BoxMatrixVar, *timeVar, *meanqVar, *d2EdgammadgammaVar, *d2EidgammadgammaVar, *sigmaVar, *sigmaiVar, *neighborVar; //!<NcVars we'll use. The additional data is the current A and O in cell GPU
    int Current;    //!< keeps track of the current record when in write mode


public:
    testModelDatabase(int np, string fn="temp.nc", NcFile::FileMode mode=NcFile::ReadOnly);
    ~testModelDatabase(){File.close();};

protected:
    void SetDimVar();
    void GetDimVar();

public:
    int  GetCurrentRec(); //!<Return the current record of the database
    //!Get the total number of records in the database
    int GetNumRecs(){
                    NcDim *rd = File.get_dim("rec");
                    return rd->size();
                    };

    //!Write the current state of the system to the database. If the default value of "rec=-1" is used, just append the current state to a new record at the end of the database
    virtual void writeState(STATE c, double time = -1.0, int rec=-1);
    //!Read the "rec"th entry of the database into SPV2D state c. If geometry=true, the local geometry of cells computed (so that further simulations can be run); set to false if you just want to load and analyze configuration data.
    virtual void readState(STATE c, int rec,bool geometry=true);

};
#endif
