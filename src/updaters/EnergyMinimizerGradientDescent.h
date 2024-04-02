#ifndef EnergyMinimizerGradientDescent_H
#define EnergyMinimizerGradientDescent_H

#include "simpleEquationOfMotion.h"
#include "Simple2DCell.h"

/*! \file EnergyMinimizerGradientDescent.h */
//!A class that implements simple gradientdescent particle dynamics in 2D
/*!
implements \Delta r  = mu*F\Delta t, where mu is the learning rate,
*/
class EnergyMinimizerGradientDescent : public simpleEquationOfMotion
    {
    public:
        //!base constructor sets the default time step size
        EnergyMinimizerGradientDescent(){deltaT = 0.01; GPUcompute =true;Timestep = 0;};
        //!additionally set the number of particles and initialize things
        EnergyMinimizerGradientDescent(int N, bool usegpu=true);

        //!the fundamental function that models will call, using vectors of different data structures
        virtual void integrateEquationsOfMotion();
        //!call the CPU routine to integrate the e.o.m.
        virtual void integrateEquationsOfMotionCPU();
        //!call the GPU routine to integrate the e.o.m.
        virtual void integrateEquationsOfMotionGPU();


        //! virtual function to allow the model to be a derived class
        virtual void set2DModel(shared_ptr<Simple2DModel> _model);

        //!call the Simple2DCell spatial vertex sorter, and re-index arrays of cell activity
        virtual void spatialSorting(const vector<int> &reIndexer);

        //!Set the value of the learning rate
        void setMu(double _mu){mu=_mu;};
        //!Return the maximum force
        double getMaxForce(){return forceMax;};
    protected:
        //!A shared pointer to a simple cell model
        shared_ptr<Simple2DCell> cellModel;
        //!The value of the inverse friction constant
        double mu;
        //!The current maximum force
        double forceMax;
    };
#endif
