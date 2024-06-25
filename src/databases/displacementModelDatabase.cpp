#include "displacementModelDatabase.h"
/*! \file displacementModelDatabase */

displacementModelDatabase::displacementModelDatabase(int np, string fn, NcFile::FileMode mode)
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
            SetDimVar();
            break;
        case NcFile::New:
            SetDimVar();
            break;
        default:
            ;
        };
    }

void displacementModelDatabase::SetDimVar()
    {
    //Set the dimensions
    recDim = File.add_dim("rec");
    NvDim  = File.add_dim("Nv",  Nv);
    dofDim = File.add_dim("dof", Nv*2);
    boxDim = File.add_dim("boxdim",4);
    unitDim = File.add_dim("unit",1);

    //Set the variables
    posVar              = File.add_var("displacementsField",       ncDouble,recDim, dofDim);
    timeVar             = File.add_var("time",     ncDouble,recDim, unitDim);
    }

void displacementModelDatabase::GetDimVar()
    {
    //Get the dimensions
    recDim = File.get_dim("rec");
    boxDim = File.get_dim("boxdim");
    NvDim  = File.get_dim("Nv");
    dofDim = File.get_dim("dof");
    unitDim = File.get_dim("unit");
    //Get the variables
    posVar = File.get_var("displacementsField");
    timeVar = File.get_var("time");

    }

void displacementModelDatabase::writeState(vector<double2> field, double time, int rec)
    {

    if(rec<0)   rec = recDim->size();


    std::vector<double> posdat(2*Nv);
    int idx = 0;

    

    for (int ii = 0; ii < Nv; ++ii)
        {
        double px = field[ii].x;
        double py = field[ii].y;
        posdat[(2*idx)] = px;
        posdat[(2*idx)+1] = py;
        idx +=1;
        };

    //Write all the data
    posVar           ->put_rec(&posdat[0],       rec);
    timeVar          ->put_rec(&time,            rec);
    File.sync();
    }

// not properly defined to read;
 void displacementModelDatabase::readState(){}
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