#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime



number=4096
p=3.825

temperatures=(0.0015)
copies=(0 1 2 3 4 5 6 7 8 9)

tauEstimate=(1000)

for copy in ${copies[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} 10 ${tauEst} ${copy}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleSACDifferentVelocity.sh ${number} ${p} ${temp} 10 ${tauEst} ${copy}
    done
done



