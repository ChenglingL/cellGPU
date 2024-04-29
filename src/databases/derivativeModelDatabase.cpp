#include "derivativeModelDatabase.h"
/*! \file derivativeModelDatabase.cpp */

derivativeModelDatabase::derivativeModelDatabase(int np, string fn, NcFile::FileMode mode)
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

void derivativeModelDatabase::SetDimVar()
    {
    //Set the dimensions
    recDim = File.add_dim("rec");
    NvDim  = File.add_dim("Nv",  Nv);
    dofDim = File.add_dim("dof", Nv*2);
    boxDim = File.add_dim("boxdim",4);
    unitDim = File.add_dim("unit",1);
    neighborDim = File.add_dim("neighbor",Nv*20);

    //Set the variables
    d2EdgammadgammaVar  = File.add_var("d2Edgammadgamma",     ncDouble,recDim, unitDim);
    //overlapVar          = File.add_var("overlap",     ncDouble,recDim, unitDim);
    //sigmaVar  = File.add_var("sigma",     ncDouble,recDim, unitDim);
    sigmaiVar           = File.add_var("sigmai",     ncDouble,recDim, NvDim);
    }

void derivativeModelDatabase::GetDimVar()
    {
    
    //Get the dimensions
    recDim = File.get_dim("rec");
    boxDim = File.get_dim("boxdim");
    NvDim  = File.get_dim("Nv");
    dofDim = File.get_dim("dof");
    unitDim = File.get_dim("unit");
    //Get the variables

    d2EdgammadgammaVar = File.get_var("d2Edgammadgamma");
    //sigmaVar = File.get_var("dEdgamma");
    sigmaiVar = File.get_var("sigmai");
    }

void derivativeModelDatabase::writeState(STATE c, double time, int rec)
    {
    shared_ptr<VoronoiQuadraticEnergy> s = dynamic_pointer_cast<VoronoiQuadraticEnergy>(c);
    if(rec<0)   rec = recDim->size();
    if (time < 0) time = s->currentTime;
    s->computeGeometry();
    std::vector<double> boxdat(4,0.0);
    double x11,x12,x21,x22;
    s->Box->getBoxDims(x11,x12,x21,x22);
    boxdat[0]=x11;
    boxdat[1]=x12;
    boxdat[2]=x21;
    boxdat[3]=x22;
    double area = x11*x22;

    std::vector<double> d2Eidgammadgammadat;
    std::vector<double> sigmaidat;
    int idx = 0;

    ArrayHandle<double2> h_p(s->cellPositions,access_location::host,access_mode::read);
    ArrayHandle<double2> h_v(s->returnVelocities());
    ArrayHandle<double2> h_m(s->returnAreaPeri(),access_location::host,access_mode::read);
    ArrayHandle<int> h_ct(s->cellType,access_location::host,access_mode::read);
    ArrayHandle<int> h_nn(s->neighborNum,access_location::host, access_mode::read);
    ArrayHandle<int> h_n(s->neighbors,access_location::host,access_mode::read);

    double d2Edgammadgammadat = s->getd2Edgammadgamma(d2Eidgammadgammadat);
    double sigma = s->getSigmaXY(sigmaidat);
    sigma=sigma*area;
    //double overlap = dynFeat.computeOverlapFunction(s->returnPositions());


    //overlapVar       ->put_rec(&overlap,         rec);
    d2EdgammadgammaVar  ->put_rec(&d2Edgammadgammadat, rec);
    sigmaiVar        ->put_rec(&sigmaidat[0], rec);
    //sigmaVar         ->put_rec(&sigma, rec);
    File.sync();
    }

void derivativeModelDatabase::readState()
    {
  
    }