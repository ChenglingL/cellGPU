#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
numberofWaitingTimes=3
p=3.85

temperatures=(0.001 0.00067 0.0005 0.0004 0.00033)
records=(0 1 2)

tauEstimate=(1000. 1000. 1000. 1000. 1000.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
    done
done

p=3.75

# temperatures=(0.02 0.014 0.012 0.011 0.0093 0.0084)
# records=(0 1 2)

# tauEstimate=(100. 100000. 100000. 100000. 100000.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         tauEst=${tauEstimate[$i]}
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#         sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
#     done
# done