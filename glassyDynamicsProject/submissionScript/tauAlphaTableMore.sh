#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
numberofWaitingTimes=3

p=3.825

temperatures=(0.063 0.039 0.025 0.016 0.01 0.008 0.0063 0.00385 0.0025 0.002 0.0018 0.001 0.00067 0.0005)
records=(3)

tauEstimate=(0.824644 1.43266 3.6161 8.18017 13.9436 22.804 37.9678 56.861 122.787 198.521 295.142 1262.1 3973.31 12618.3)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPUMore.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
    done
done




p=3.8
numberofWaitingTimes=3

temperatures=(0.063 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 )
records=(3)

tauEstimate=(1.18 3.87 5.57 11.92 33.81 54.58 107.30 216.97 565.32 1243.95 2065.00 3731.35 7000.00 12885.22)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPUMore.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
    done
done


p=3.85

temperatures=(0.063  0.03105 0.016  0.01 0.008  0.005 0.00385  0.0025  0.001 0.00067 0.00033 0.00025  0.00014 0.0001)
records=(3)

tauEstimate=(0.8786 2.21528  4.28562 8.7582 11.5562 23.3058 45.0726  76.8102 174.354 308.531  765.115 1258.7 2873.75  5026.2)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPUMore.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
    done
done

p=3.75

temperatures=(0.063 0.03105 0.025 0.02 0.016 0.014 0.012 0.011 0.01 0.0093)
records=(3)

tauEstimate=(3.90925 6.55747 9.97736 27.7627 60.8242 137.053 667.94 1386.6 3995.4 9287.15)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPUMore.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
    done
done