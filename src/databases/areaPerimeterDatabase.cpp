#include "areaPerimeterDatabase.h"
/*! \file areaPerimeterDatabase.cpp */

areaPerimeterDatabase::areaPerimeterDatabase(int np, string fn, NcFile::FileMode mode)
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

void areaPerimeterDatabase::SetDimVar()
    {
    //Set the dimensions
    recDim = File.add_dim("rec");
    NvDim  = File.add_dim("Nv",  Nv);
    dofDim = File.add_dim("dof", Nv*2);
    boxDim = File.add_dim("boxdim",4);
    unitDim = File.add_dim("unit",1);

    //Set the variables
    areaVar             = File.add_var("area",       ncDouble,recDim, NvDim);
    perimeterVar           = File.add_var("perimeter",      ncDouble,recDim, NvDim);
    timeVar             = File.add_var("time",     ncDouble,recDim, unitDim);
    }

void areaPerimeterDatabase::GetDimVar()
    {
    //Get the dimensions
    recDim = File.get_dim("rec");
    boxDim = File.get_dim("boxdim");
    NvDim  = File.get_dim("Nv");
    dofDim = File.get_dim("dof");
    unitDim = File.get_dim("unit");
    //Get the variables
    areaVar = File.get_var("area");
    perimeterVar = File.get_var("perimeter");
    timeVar = File.get_var("time");

    }

void areaPerimeterDatabase::writeState(STATE c, double time, int rec)
    {
    shared_ptr<VoronoiQuadraticEnergy> s = dynamic_pointer_cast<VoronoiQuadraticEnergy>(c);
    if(rec<0)   rec = recDim->size();
    if (time < 0) time = s->currentTime;
    s->enforceTopology();
    s->computeGeometry();
    std::vector<double> areadat(Nv);
    std::vector<double> perimeterdat(Nv);
    int idx = 0;
    ArrayHandle<double2> h_m(s->returnAreaPeri());

    for (int ii = 0; ii < Nv; ++ii)
        {
        int pidx = s->tagToIdx[ii];
        double ma = h_m.data[pidx].x;
        double mp = h_m.data[pidx].y;
        areadat[idx] = ma;
        perimeterdat[idx] = mp;
        idx +=1;
        };

    //Write all the data
    areaVar          ->put_rec(&areadat[0],       rec);
    perimeterVar        ->put_rec(&perimeterdat[0],       rec);
    timeVar          ->put_rec(&time,            rec);
    File.sync();
    }

