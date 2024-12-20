#ifndef DATABASE_AP_H
#define DATABASE_AP_H

#include "voronoiQuadraticEnergy.h"
#include "DatabaseNetCDF.h"

/*! \file areaPerimeterDatabase.h */
//!Simple databse for recording areas and perimeter

class areaPerimeterDatabase : public BaseDatabaseNetCDF
{
private:
    typedef shared_ptr<Simple2DCell> STATE;
    int Nv; //!< number of vertices in delaunay triangulation
    NcDim *recDim, *NvDim, *dofDim, *boxDim, *unitDim; //!< NcDims we'll use
    //!Currently using "additionalData" to hold target a_0 and p_0 information
    NcVar *areaVar, *perimeterVar, *timeVar; //!<NcVars we'll use
    int Current;    //!< keeps track of the current record when in write mode


public:
    areaPerimeterDatabase(int np, string fn="temp.nc", NcFile::FileMode mode=NcFile::ReadOnly);
    ~areaPerimeterDatabase(){File.close();};

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

};
#endif