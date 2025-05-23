#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
p=3.85

temperatures=(0.00014 5.4E-05 3.6E-05)
records=(10)

tauEstimate=(2500 6000 9500)
epsilons=(0.12 0.2 -0.2 -0.12)

for recordIdx in ${records[@]}; do
    for epsilon in ${epsilons[@]}; do
        for i in ${!temperatures[@]}; do
            tauEst=${tauEstimate[$i]}
            temp=${temperatures[$i]}
            echo ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
            sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singlePureShearCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
        done
    done
done

# number=4096
# p=3.85

# temperatures=(3.6E-05)
# records=(10)

# tauEstimate=(9500)
# epsilons=(0.1 0.8 0.05 -0.05 -0.8 -0.1)

# for recordIdx in ${records[@]}; do
#     for epsilon in ${epsilons[@]}; do
#         for i in ${!temperatures[@]}; do
#             tauEst=${tauEstimate[$i]}
#             temp=${temperatures[$i]}
#             echo ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
#             sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singlePureShearCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
#         done
#     done
# done


# number=4096
# p=3.825

# temperatures=(0.063 0.039 0.03105 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025 0.002 0.0015)
# records=(10)

# tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000.)
# epsilons=(0.05 0 -0.05)

# for recordIdx in ${records[@]}; do
#     for epsilon in ${epsilons[@]}; do
#         for i in ${!temperatures[@]}; do
#             tauEst=${tauEstimate[$i]}
#             temp=${temperatures[$i]}
#             echo ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
#             sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singlePureShearCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
#         done
#     done
# done
# number=4096
# p=3.825

# temperatures=(0.063 0.039 0.03105 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025 0.002 0.0015)
# records=(10)

# tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000.)
# epsilons=(0.0001 -0.0001)

# for recordIdx in ${records[@]}; do
#     for epsilon in ${epsilons[@]}; do
#         for i in ${!temperatures[@]}; do
#             tauEst=${tauEstimate[$i]}
#             temp=${temperatures[$i]}
#             echo ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
#             sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singlePureShearCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
#         done
#     done
# done


# number=4096
# p=3.825

# temperatures=(0.063 0.039 0.03105 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025 0.002 0.0015)
# records=(10)

# tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000.)
# epsilons=(0.01 0 -0.01)

# for recordIdx in ${records[@]}; do
#     for epsilon in ${epsilons[@]}; do
#         for i in ${!temperatures[@]}; do
#             tauEst=${tauEstimate[$i]}
#             temp=${temperatures[$i]}
#             echo ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
#             sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singlePureShearCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst} ${epsilon}
#         done
#     done
# done
