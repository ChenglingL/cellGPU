#include "GNNLearningModelDatabase.h"
/*! \file GNNLearningModelDatabase.cpp */

GNNLearningModelDatabase::GNNLearningModelDatabase(int np, string fn, NcFile::FileMode mode)
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

void GNNLearningModelDatabase::SetDimVar()
    {
    //Set the dimensions
    recDim = File.add_dim("rec");
    NvDim  = File.add_dim("Nv",  Nv);
    dofDim = File.add_dim("dof", Nv*2);
    boxDim = File.add_dim("boxdim",4);
    unitDim = File.add_dim("unit",1);
    neighborDim = File.add_dim("neighbor",Nv*20);

    //Set the variables
    posVar              = File.add_var("postion",       ncDouble,recDim, dofDim);
    forceVar            = File.add_var("force",       ncDouble,recDim, dofDim);
    BoxMatrixVar        = File.add_var("BoxMatrix",     ncDouble,recDim, boxDim);
    timeVar             = File.add_var("time",     ncDouble,recDim, unitDim);
    neighborVar         = File.add_var("neighbor",     ncInt,recDim, neighborDim);
    }

void GNNLearningModelDatabase::GetDimVar()
    {
    //Get the dimensions
    recDim = File.get_dim("rec");
    boxDim = File.get_dim("boxdim");
    NvDim  = File.get_dim("Nv");
    dofDim = File.get_dim("dof");
    unitDim = File.get_dim("unit");
    //Get the variables
    posVar = File.get_var("postion");
    forceVar = File.get_var("force");
    BoxMatrixVar = File.get_var("BoxMatrix");
    timeVar = File.get_var("time");
    neighborVar = File.get_var("neighbor");

    }

void GNNLearningModelDatabase::writeState(STATE c, double time, int rec)
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
    std::vector<double> forcedat(2*Nv);
    int idx = 0;

    ArrayHandle<double2> h_p(s->cellPositions,access_location::host,access_mode::read);
    ArrayHandle<double2> h_f(s->cellForces,access_location::host,access_mode::read);
    ArrayHandle<int> h_nn(s->neighborNum,access_location::host, access_mode::read);
    ArrayHandle<int> h_n(s->neighbors,access_location::host,access_mode::read);

    int neighborListLength = 0;
    int maxcount = 0;
    // dynamicalFeatures dynFeat(s->returnPositions(),s->Box);
    Index2D nidx=s->n_idx;
    for (int ii = 0; ii < Nv; ++ii)
        {
            if (maxcount < h_nn.data[ii])
            {
                maxcount = h_nn.data[ii];
            }
            for (int j = 0; j < h_nn.data[ii]; j++)
            {
                neighborListLength++;
            }
        
        };
    std::vector<int> neighbordat(20*Nv,-1);
    for (int ii = 0; ii < Nv; ++ii)
        {
            for (int j = 0; j < h_nn.data[ii]; j++)
            {
                neighbordat[ii * maxcount + j] = h_n.data[nidx(j,ii)];
            }
        
        };
    for (int ii = 0; ii < Nv; ++ii)
        {
        int pidx = s->tagToIdx[ii];
        double px = h_p.data[pidx].x;
        double py = h_p.data[pidx].y;
        posdat[(2*idx)] = px;
        posdat[(2*idx)+1] = py;
        double fx = h_f.data[pidx].x;
        double fy = h_f.data[pidx].y;
        forcedat[(2*idx)] = fx;
        forcedat[(2*idx)+1] = fy;
        idx +=1;
        };

    //Write all the data
    posVar           ->put_rec(&posdat[0],       rec);
    forceVar           ->put_rec(&forcedat[0],       rec);
    timeVar          ->put_rec(&time,            rec);
    BoxMatrixVar     ->put_rec(&boxdat[0],       rec);
    neighborVar      ->put_rec(&neighbordat[0], rec);
    File.sync();
    }

void GNNLearningModelDatabase::readState(STATE c, int rec)
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