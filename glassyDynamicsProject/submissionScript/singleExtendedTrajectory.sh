#!/bin/bash
#SBATCH --mem=2g
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1    # <- match to OMP_NUM_THREADS
#SBATCH --partition=cpu      # <- or one of: gpuA100x4 gpuA40x4 gpuA100x8 gpuMI100x8
#SBATCH --account=bbtm-delta-cpu  # OR bbtm-delta-gpu 
#SBATCH --job-name=cpuGlassyCellDynamics
#SBATCH --time=48:00:00      # hh:mm:ss for the job
/u/cli6/cellGPU/glassyDynamicsProject/ExtendedTrajectory.out -n ${1} -p ${2} -v ${3} -r ${4} -t ${5} -g -1
