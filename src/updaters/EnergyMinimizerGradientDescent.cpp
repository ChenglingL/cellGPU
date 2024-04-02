#include "EnergyMinimizerGradientDescent.h"
#include "EnergyMinimizerGradientDescent.cuh"
/*! \file EnergyMinimizerGradientDescent.cpp */

/*!
An extremely simple constructor that does nothing, but enforces default GPU operation
\param the number of points in the system (cells or particles)
*/
EnergyMinimizerGradientDescent::EnergyMinimizerGradientDescent(int _N, bool usegpu)
    {
    Timestep = 0;
    deltaT = 0.01;
    GPUcompute = usegpu;
    if(!GPUcompute)
        displacements.neverGPU=true;
    mu = 1.0;
    forceMax=1.0;
    Ndof = _N;
    noise.initializeGPURNG = GPUcompute;
    noise.initialize(Ndof);
    displacements.resize(Ndof);
    };

/*!
When spatial sorting is performed, re-index the array of cuda RNGs... This function is currently
commented out, for greater flexibility (i.e., to not require that the indexToTag (or Itt) be the
re-indexing array), since that assumes cell and not particle-based dynamics
*/
void EnergyMinimizerGradientDescent::spatialSorting(const vector<int> &reIndexer)
    {
    //reIndexing = cellModel->returnItt();
    //reIndexRNG(noise.RNGs);
    };

/*!
Set the shared pointer of the base class to passed variable
*/
void EnergyMinimizerGradientDescent::set2DModel(shared_ptr<Simple2DModel> _model)
    {
    model=_model;
    cellModel = dynamic_pointer_cast<Simple2DCell>(model);
    }

/*!
Advances gradient descent dynamics by one time step
*/
void EnergyMinimizerGradientDescent::integrateEquationsOfMotion()
    {
    Timestep += 1;
    if (cellModel->getNumberOfDegreesOfFreedom() != Ndof)
        {
        Ndof = cellModel->getNumberOfDegreesOfFreedom();
        displacements.resize(Ndof);
        noise.initialize(Ndof);
        };
    if(GPUcompute)
        {
        integrateEquationsOfMotionGPU();
        }
    else
        {
        integrateEquationsOfMotionCPU();
        }
    };

/*!
The straightforward GPU implementation
*/
void EnergyMinimizerGradientDescent::integrateEquationsOfMotionGPU()
    {
    cellModel->computeForces();
    {//scope for array Handles
    ArrayHandle<double2> d_f(cellModel->returnForces(),access_location::device,access_mode::read);
    ArrayHandle<double2> d_disp(displacements,access_location::device,access_mode::overwrite);

    ArrayHandle<curandState> d_RNG(noise.RNGs,access_location::device,access_mode::readwrite);
    forceMax=0.0;
    for (int ii = 0; ii < Ndof; ++ii)
        {
        double fdot = dot(d_f.data[ii],d_f.data[ii]);
        if (fdot > forceMax) forceMax = fdot;
        };
    gpu_gradientdescent_eom_integration(d_f.data,
                 d_disp.data,
                 d_RNG.data,
                 Ndof,
                 deltaT,
                 mu);
    };//end array handle scope
    cellModel->moveDegreesOfFreedom(displacements);
    cellModel->enforceTopology();
    };

/*!
The straightforward CPU implementation
*/
void EnergyMinimizerGradientDescent::integrateEquationsOfMotionCPU()
    {
    cellModel->computeForces();
    {//scope for array Handles
    ArrayHandle<double2> h_f(cellModel->returnForces(),access_location::host,access_mode::read);
    ArrayHandle<double2> h_disp(displacements,access_location::host,access_mode::overwrite);

    forceMax=0.0;
    for (int ii = 0; ii < Ndof; ++ii)
        {
        double fdot = dot(h_f.data[ii],h_f.data[ii]);
        if (fdot > forceMax) forceMax = fdot;
        h_disp.data[ii].x = deltaT*mu*h_f.data[ii].x;
        h_disp.data[ii].y = deltaT*mu*h_f.data[ii].y;
        };
    };//end array handle scope
    cellModel->moveDegreesOfFreedom(displacements);
    cellModel->enforceTopology();
    };
