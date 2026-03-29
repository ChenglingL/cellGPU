#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
p=3.75

#temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
temperatures=(0.013 0.0115 0.0105 0.0096)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(1000 1000 3000 10000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU_additional.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    done
done

number=4096
p=3.815

#temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
temperatures=(0.063 0.025 0.01 0.0063 0.005 0.00385 0.0028 0.0022 0.0015 0.0012 0.001 0.0008 0.00067)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(1000 1000 1000 1000 1000 1000 1000 3000 5000 10000 10000 10000 10000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU_additional.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    done
done

number=4096
p=3.825

#temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
temperatures=(0.0022 0.0013 0.00033 0.00025 0.00018 0.00014 0.0001)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(1000 1000 10000 10000 10000 10000 10000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU_additional.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    done
done

number=4096
p=3.85

#temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
temperatures=(0.00067 0.00018)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(1000 3000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU_additional.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    done
done


