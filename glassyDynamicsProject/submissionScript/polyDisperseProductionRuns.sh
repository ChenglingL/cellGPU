#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
p=3.000

#temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
temperatures=(0.22 0.2 0.18 0.16 0.14 0.12 0.1 0.09 0.08 0.075)
records=(0 1 2 3 4 5 6 7 8 9)

tauEstimate=(10 10 10 50 100 200 500 2000 5000 10000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singlePolyDisperseProductionRunCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    done
done

