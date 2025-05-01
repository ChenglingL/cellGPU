#include "trajectoryModelDatabase.h"
/*! \file trajectoryModelDatabase.cpp */

trajectoryModelDatabase::trajectoryModelDatabase(int np, string fn, NcFile::FileMode mode)
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

void trajectoryModelDatabase::SetDimVar()
    {
    //Set the dimensions
    recDim = File.add_dim("rec");
    NvDim  = File.add_dim("Nv",  Nv);
    dofDim = File.add_dim("dof", Nv*2);
    boxDim = File.add_dim("boxdim",4);
    unitDim = File.add_dim("unit",1);

    //Set the variables
    posVar              = File.add_var("postion",       ncDouble,recDim, dofDim);
    BoxMatrixVar        = File.add_var("BoxMatrix",     ncDouble,recDim, boxDim);
    timeVar             = File.add_var("time",     ncDouble,recDim, unitDim);
    }

    void trajectoryModelDatabase::GetDimVar()
    {
        // Disable automatic error reporting
        NcError err(NcError::silent_nonfatal);
    
        // Get the dimensions
        recDim  = File.get_dim("rec");
        boxDim  = File.get_dim("boxdim");
        NvDim   = File.get_dim("Nv");
        dofDim  = File.get_dim("dof");
        unitDim = File.get_dim("unit");
    
        // Check for both variable names
        posVar = File.get_var("position");
        if (posVar == nullptr) {
            posVar = File.get_var("postion");
            if (posVar == nullptr) {
                std::cerr << "Error: Neither 'position' nor 'postion' found." << std::endl;
                exit(EXIT_FAILURE); // Or handle it more gracefully
            }
        }
    
        // Get other variables
        BoxMatrixVar = File.get_var("BoxMatrix");
        timeVar      = File.get_var("time");
    
        // Re-enable error reporting (optional)
        NcError restore(NcError::verbose_fatal);
    }

void trajectoryModelDatabase::writeState(STATE c, double time, int rec)
    {
    shared_ptr<VoronoiQuadraticEnergy> s = dynamic_pointer_cast<VoronoiQuadraticEnergy>(c);
    if(rec<0)   rec = recDim->size();
    if (time < 0) time = s->currentTime;

    std::vector<double> boxdat(4,0.0);
    double x11,x12,x21,x22;
    s->Box->getBoxDims(x11,x12,x21,x22);
    boxdat[0]=x11;
    boxdat[1]=x12;
    boxdat[2]=x21;
    boxdat[3]=x22;

    std::vector<double> posdat(2*Nv);
    int idx = 0;

    ArrayHandle<double2> h_p(s->cellPositions,access_location::host,access_mode::read);

    for (int ii = 0; ii < Nv; ++ii)
        {
        int pidx = s->tagToIdx[ii];
        double px = h_p.data[pidx].x;
        double py = h_p.data[pidx].y;
        posdat[(2*idx)] = px;
        posdat[(2*idx)+1] = py;
        idx +=1;
        };

    //Write all the data
    posVar           ->put_rec(&posdat[0],       rec);
    timeVar          ->put_rec(&time,            rec);
    BoxMatrixVar     ->put_rec(&boxdat[0],       rec);
    File.sync();
    }

void trajectoryModelDatabase::readState(STATE c, int rec)
    {
    shared_ptr<VoronoiQuadraticEnergy> t = dynamic_pointer_cast<VoronoiQuadraticEnergy>(c);
    //initialize the NetCDF dimensions and variables
    GetDimVar();

    //get the current time
    timeVar-> set_cur(rec);
    timeVar->get(& t->currentTime,1,1);

    //set the box
    BoxMatrixVar-> set_cur(rec);
    std::vector<double> boxdata(4,0.0);
    BoxMatrixVar->get(&boxdata[0],1, boxDim->size());
    t->Box->setGeneral(boxdata[0],boxdata[1],boxdata[2],boxdata[3]);
    //get the positions
    posVar-> set_cur(rec);
    std::vector<double> posdata(2*Nv,0.0);
    posVar->get(&posdata[0],1, dofDim->size());
    ArrayHandle<double2> h_p(t->cellPositions,access_location::host,access_mode::overwrite);
    for (int idx = 0; idx < Nv; ++idx)
        {
        double px = posdata[(2*idx)];
        double py = posdata[(2*idx)+1];
        h_p.data[idx].x=px;
        h_p.data[idx].y=py;
        };

    }