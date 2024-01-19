#ifndef DATABASE_TwoValues_H
#define DATABASE_TwoValues_H

#include "DatabaseNetCDF.h"

/*! \file twoValuesDatabase.h */
//! This is the database for storing only de/dgamma and d2e/dgamma2
/*!
The first value would be de/dgamma and the second value would be d2e/dgamma2
*/
class twoValuesDatabase : public BaseDatabaseNetCDF
    {
    public:
        twoValuesDatabase(string fn="temp.nc", NcFile::FileMode mode=NcFile::ReadOnly);
        ~twoValuesDatabase(){File.close();};

        //! NcDims we'll use
        NcDim *recDim, *dofDim, *unitDim;
        //! NcVars
        NcVar *firstVar, *secondVar;
        //!read values
        void readState(int rec);
        //!write values
        void writeValues(double firstdata,double seconddata);
        //!read the number of records in the database
        int GetNumRecs(){
                    NcDim *rd = File.get_dim("rec");
                    return rd->size();
                    };
        //!The variable that will be loaded for "de/dgamma" when state is read
        double firstdata;
        //!The variable that will be loaded for "d2e/dgamma2" when state is read
        double seconddata;

    protected:
        void SetDimVar();
        void GetDimVar();
    };
#endif
