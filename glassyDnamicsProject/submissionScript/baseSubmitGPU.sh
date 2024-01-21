#!/bin/bash
#SBATCH --mem=2g
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --gpus-per-task=1    # <- match to OMP_NUM_THREADS
#SBATCH --gpu-bind=none
#SBATCH --partition=gpuA100x4      # <- or one of: gpuA100x4 gpuA40x4 gpuA100x8 gpuMI100x8
#SBATCH --account=bbtm-delta-gpu  # OR bbtm-delta-gpu 
#SBATCH --job-name=gpuGlassyCellDynamics
#SBATCH --time=48:00:00      # hh:mm:ss for the job
/u/dsussman/USG/glassyCellDynamics/build/voronoiGlassyDynamics.out -n ${1} -p ${2} -v ${3} -t ${4} -i ${5} -m ${6} -r ${7} -g 0
