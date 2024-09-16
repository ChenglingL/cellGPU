#include "structureFactorModelDatabase.h"
/*! \file structureFactorModelDatabase */

structureFactorModelDatabase::structureFactorModelDatabase(int np, string fn, NcFile::FileMode mode, int numK)
    : BaseDatabaseNetCDF(fn,mode),
      Nv(np),
      Current(0)
    {
    switch(Mode)
        {
        case NcFile::ReadOnly:
            break;
        case NcFile::Write:
            GetDimVar();
            break;
        case NcFile::Replace:
            SetDimVar(numK);// set the length of vector
            break;
        case NcFile::New:
            SetDimVar(numK);
            break;
        default:
            ;
        };
    }

void structureFactorModelDatabase::SetDimVar(int numK)
    {
    //Set the dimensions
    recDim = File.add_dim("rec");
    NvDim  = File.add_dim("Nv",  Nv);
    dofDim = File.add_dim("dof", numK);
    boxDim = File.add_dim("boxdim",4);
    unitDim = File.add_dim("unit",1);

    //Set the variables
    kVar              = File.add_var("k",       ncDouble,unitDim, dofDim);
    sqVar              = File.add_var("structureFactor",       ncDouble,recDim, dofDim);
    timeVar             = File.add_var("time",     ncDouble,recDim, unitDim);
    }

void structureFactorModelDatabase::GetDimVar()
    {
    //Get the dimensions
    recDim = File.get_dim("rec");
    boxDim = File.get_dim("boxdim");
    NvDim  = File.get_dim("Nv");
    dofDim = File.get_dim("dof");
    unitDim = File.get_dim("unit");
    //Get the variables
    kVar = File.get_var("k");
    sqVar = File.get_var("kstructureFactor");
    timeVar = File.get_var("time");

    }
void structureFactorModelDatabase::writeK(vector<double2> field)
    {


    std::vector<double> kdat(field.size());
    std::vector<double> sqdat(field.size());
    int idx = 0;

    
    Nv = field.size();
    for (int ii = 0; ii < Nv; ++ii)
        {
        double px = field[ii].x;
        double py = field[ii].y;
        kdat[ii] = px;
        sqdat[ii] = py;
        };

    //Write all the data
    kVar           ->put_rec(&kdat[0],       0);
    File.sync();
    }
void structureFactorModelDatabase::writeState(vector<double2> field, double time, int rec)
    {

    if(rec<0)   rec = recDim->size();


    //std::vector<double> kdat(field.size());
    std::vector<double> sqdat(field.size());
    int idx = 0;

    
    Nv = field.size();
    for (int ii = 0; ii < Nv; ++ii)
        {
        //double px = field[ii].x;
        double py = field[ii].y;
        //kdat[ii] = px;
        sqdat[ii] = py;
        };

    //Write all the data
    //kVar           ->put_rec(&kdat[0],       rec);
    sqVar           ->put_rec(&sqdat[0],       rec);
    timeVar          ->put_rec(&time,            rec);
    File.sync();
    }

// not properly defined to read;
 void structureFactorModelDatabase::readState(){}
//     {
//     shared_ptr<VoronoiQuadraticEnergy> t = dynamic_pointer_cast<VoronoiQuadraticEnergy>(c);
//     //initialize the NetCDF dimensions and variables
//     GetDimVar();

//     //get the current time
//     timeVar-> set_cur(rec);
//     timeVar->get(& t->currentTime,1,1);

//     //set the box
//     BoxMatrixVar-> set_cur(rec);
//     std::vector<double> boxdata(4,0.0);
//     BoxMatrixVar->get(&boxdata[0],1, boxDim->size());
//     t->Box->setGeneral(boxdata[0],boxdata[1],boxdata[2],boxdata[3]);
//     //get the positions
//     posVar-> set_cur(rec);
//     std::vector<double> posdata(2*Nv,0.0);
//     posVar->get(&posdata[0],1, dofDim->size());
//     ArrayHandle<double2> h_p(t->cellPositions,access_location::host,access_mode::overwrite);
//     for (int idx = 0; idx < Nv; ++idx)
//         {
//         double px = posdata[(2*idx)];
//         double py = posdata[(2*idx)+1];
//         h_p.data[idx].x=px;
//         h_p.data[idx].y=py;
//         };

//     }