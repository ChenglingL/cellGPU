#ifndef DATABASE_structureFactor_H
#define DATABASE_structureFactor_H

#include "voronoiQuadraticEnergy.h"
#include "DatabaseNetCDF.h"
#include "dynamicalFeatures.h"

/*! \file structureFactorModelDatabase.h */
//!Simple databse for reading/writing 2d spv states
/*!
Class for a state database for a 2d delaunay triangulation
the box dimensions are stored
Need to re-triangulate after readState
*/
class structureFactorModelDatabase : public BaseDatabaseNetCDF
{
private:
    typedef shared_ptr<dynamicalFeatures> STATE;
    int Nv; //!< number of vertices in delaunay triangulation
    NcDim *recDim, *NvDim, *dofDim, *boxDim, *unitDim; //!< NcDims we'll use
    //!Currently using "additionalData" to hold target a_0 and p_0 information
    NcVar *kVar, *sqVar, *timeVar; //!<NcVars we'll use
    int Current;    //!< keeps track of the current record when in write mode


public:
    structureFactorModelDatabase(int np, string fn="temp.nc", NcFile::FileMode mode=NcFile::ReadOnly, int numK=100);
    ~structureFactorModelDatabase(){File.close();};

protected:
    void GetDimVar();
    void SetDimVar(int numK);

public:
    int  GetCurrentRec(); //!<Return the current record of the database
    //!Get the total number of records in the database
    int GetNumRecs(){
                    NcDim *rd = File.get_dim("rec");
                    return rd->size();
                    };

    //!Write the current state of the system to the database. If the default value of "rec=-1" is used, just append the current state to a new record at the end of the database
    virtual void writeState(vector<double2> field, double time = -1.0, int rec=-1);
    //!Read the "rec"th entry of the database into SPV2D state c. If geometry=true, the local geometry of cells computed (so that further simulations can be run); set to false if you just want to load and analyze configuration data.
    virtual void readState();
    virtual void writeK(vector<double2> field);
};
#endif