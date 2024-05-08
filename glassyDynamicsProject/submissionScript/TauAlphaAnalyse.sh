#!/bin/bash
#SBATCH --mem=2g
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1    # <- match to OMP_NUM_THREADS
#SBATCH --partition=cpu      # <- or one of: gpuA100x4 gpuA40x4 gpuA100x8 gpuMI100x8
#SBATCH --account=bbtm-delta-cpu  # OR bbtm-delta-gpu 
#SBATCH --job-name=cpuGlassyCellDynamics
#SBATCH --time=5:00:00      # hh:mm:ss for the job

number=4096
p=3.825

temperatures=(0.063 0.039 0.03105 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025 0.002 0.0015)
records=(0 1 2 3 4 5 6 7 8 9)

tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000.)


for offsetIdx in {0..19}; do
    for recordIdx in ${records[@]}; do
        for i in ${!temperatures[@]}; do
            tauEst=${tauEstimate[$i]}
            temp=${temperatures[$i]}
            echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
            /u/cli6/cellGPU/glassyDynamicsProject/tauAlphaTableAnalyse.out -n ${number} -p ${p} -v ${temp} -r  ${recordIdx} -t ${tauEst} -g -1 -o ${offsetIdx}
        done
    done
done

