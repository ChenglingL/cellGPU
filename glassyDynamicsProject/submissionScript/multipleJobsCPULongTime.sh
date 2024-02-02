#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
p=3.8

# temperatures=(0.08868 0.05586 0.03756 0.02652 0.01945 0.01471 0.01141)

#temperatures=(0.05409 0.03105 0.01782 0.01023 0.005873 0.003371 0.001935)

#temperatures=(0.00309559 0.00285428 0.00264787 0.00246931 0.0023133)
temperatures=(0.00222222 0.00210526 0.002 0.00190476 0.00181818)
records=(0 1 2)

for recordIdx in ${records[@]}; do
    for temp in ${temperatures[@]}; do
        echo ${number} ${p} ${temp} ${recordIdx}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPULongTime.sh ${number} ${p} ${temp} ${recordIdx}
    done
done


