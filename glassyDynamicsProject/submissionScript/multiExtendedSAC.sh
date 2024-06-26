#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime



number=4096
p=3.825

temperatures=(0.00067 0.0005)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(5000. 10000.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleExtendedSAC.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    done
done

number=4096
p=3.80

temperatures=(0.0025 0.0022)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(4500. 9500.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleExtendedSAC.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    done
done

