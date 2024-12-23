#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
#numbers=(4096 32768)
numbers=(64)
temp=0.1

#records=(0 1 2 3 4 5 6 7 8 9)
#ps=(3.75 3.8 3.825 3.85 3.9 4.0)
ps=(3.8)
for number in ${numbers[@]}; do
    for p in ${ps[@]}; do
        echo ${number} ${p} ${temp}
        sbatch /u/cli6/cellGPU/agingProject/submissionScript/baseSubmitCPU.sh ${number} ${p} ${temp}
    done
done


