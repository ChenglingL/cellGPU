#ifndef __ENERGYMINIMIZERGRADIENTDESCENT_CUH__
#define __ENERGYMINIMIZERGRADIENTDESCENT_CUH__

#include "std_include.h"
#include <cuda_runtime.h>

/*!
 \file EnergyMinimizerGradientDescent.cuh
A file providing an interface to the relevant cuda calls for the EnergyMinimizerGradientDescent class
*/

/** @addtogroup simpleEquationOfMotionKernels simpleEquationsOfMotion Kernels
 * @{
 */

//!set the vector of displacements from forces and noise
bool gpu_gradientdescent_eom_integration(
                    double2 *forces,
                    double2 *displacements,
                    curandState *RNGs,
                    int N,
                    double deltaT,
                    double mu);

/** @} */ //end of group declaration
 #endif
