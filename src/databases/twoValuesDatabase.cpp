#include "twoValuesDatabase.h"
/*! \file twoValuesDatabase.cpp */

twoValuesDatabase::twoValuesDatabase(string fn, NcFile::FileMode mode)
    :BaseDatabaseNetCDF(fn,mode)
    {
    switch(Mode)
        {
        case NcFile::ReadOnly:
            GetDimVar();
            break;
        case NcFile::Write:
            GetDimVar();
            break;
        case NcFile::Replace:
            SetDimVar();
            break;
        case NcFile::New:
            SetDimVar();
            break;
        default:
            ;
        };
    };

void twoValuesDatabase::SetDimVar()
    {
    //Set the dimensions
    recDim = File.add_dim("rec");
    unitDim = File.add_dim("unit",1);

    //Set the variables
    firstVar = File.add_var("firstValue", ncDouble,recDim);
    secondVar = File.add_var("secondValue",ncDouble,recDim);
    }

void twoValuesDatabase::GetDimVar()
    {
    //Get the dimensions
    recDim = File.get_dim("rec");
    unitDim = File.get_dim("unit");
    //Get the variables
    firstVar = File.get_var("firstValue");
    secondVar = File.get_var("secondValue");
    }

void twoValuesDatabase::writeValues(double firstdata,double seconddata)
    {
    int rec = recDim->size();
    firstVar->put_rec(&firstdata,rec);
    secondVar->put_rec(&seconddata,rec);
    File.sync();
    };
//No need to read for this dataset
void twoValuesDatabase::readState(int rec)
    {
    int totalRecords = GetNumRecs();
    if (rec >= totalRecords)
        {
        printf("Trying to read a database entry that does not exist\n");
        throw std::exception();
        };
    };
