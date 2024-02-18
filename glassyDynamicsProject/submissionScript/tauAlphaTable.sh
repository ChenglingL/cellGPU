#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
numberofWaitingTimes=3
p=3.85

#temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
temperatures=(0.000091 0.000083 0.000077 0.000071 0.000067)
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

p=3.825

temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018 0.001 0.00067 0.0005 0.0004 0.00033)
records=(0 1 2)

tauEstimate=(1.18 2.46 3.87 5.57 11.92 33.81 54.58 107.30 216.97 565.32 800. 800. 800. 800. 800. 2000. 2000. 2000. 2000. 2000. 2000.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
    done
done



##below are parameters for the first batch
# p=3.8
# numberofWaitingTimes=3

# temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018)
# records=(0 1 2)

# tauEstimate=(1.18 2.46 3.87 5.57 11.92 33.81 54.58 107.30 216.97 565.32 1243.95 2065.00 3731.35 7000.00 12885.22 22000.00)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         tauEst=${tauEstimate[$i]}
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#         sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
#     done
# done


# p=3.85

# temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018)
# records=(0 1 2)

# tauEstimate=(1.18 2.46 3.87 5.57 11.92 33.81 54.58 107.30 216.97 565.32 1243.95 2065.00 3731.35 7000.00 12885.22 22000.00)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         tauEst=${tauEstimate[$i]}
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#         sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
#     done
# done

# p=3.75

# temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031)
# records=(0 1 2)

# tauEstimate=(2.37 7.39 15.46 27.87 71.55 236.67 436.61 965.66 2169.66 6218.51 14927.34)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         tauEst=${tauEstimate[$i]}
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#         sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/baseSubmitCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${numberofWaitingTimes}
#     done
# done