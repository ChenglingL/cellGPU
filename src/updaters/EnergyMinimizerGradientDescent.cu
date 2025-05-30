#include <cuda_runtime.h>
#include "curand_kernel.h"
#include "EnergyMinimizerGradientDescent.cuh"

/** \file EnergyMinimizerGradientDescent.cu
    * Defines kernel callers and kernels for GPU calculations of simple gradientdescent 2D cell models
*/

/*!
    \addtogroup simpleEquationOfMotionKernels
    @{
*/

/*!
Each thread calculates the displacement of an individual cell
*/
__global__ void gradientdescent_eom_integration_kernel(double2 *forces,
                                           double2 *displacements,
                                           curandState *RNGs,
                                           int N,
                                           double deltaT,
                                           double mu)
    {
    unsigned int idx = blockIdx.x*blockDim.x + threadIdx.x;
    if (idx >=N)
        return;
    curandState_t randState;

    randState=RNGs[idx];
    displacements[idx].x = deltaT*mu*forces[idx].x;
    displacements[idx].y = deltaT*mu*forces[idx].y;

    RNGs[idx] = randState;
    return;
    };

//!get the current timesteps vector of displacements into the displacement vector
bool gpu_gradientdescent_eom_integration(
                    double2 *forces,
                    double2 *displacements,
                    curandState *RNGs,
                    int N,
                    double deltaT,
                    double mu)
    {
    unsigned int block_size = 128;
    if (N < 128) block_size = 32;
    unsigned int nblocks  = N/block_size + 1;


    gradientdescent_eom_integration_kernel<<<nblocks,block_size>>>(
                                forces,displacements,
                                RNGs,
                                N,deltaT,mu);
    HANDLE_ERROR(cudaGetLastError());
    return cudaSuccess;
    };

/** @} */ //end of group declaration
