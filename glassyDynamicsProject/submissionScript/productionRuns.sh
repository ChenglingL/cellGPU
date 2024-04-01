#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
p=3.85

temperatures=(0.039 0.016 0.01 0.005 0.00385 0.0025 0.002 0.001 0.0005 0.00033 0.00025 0.00014 9.1E-05 7.7E-05 5.4E-05 4.5E-05 3.6E-05)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(2. 4. 10. 20. 40. 60. 80. 200. 500. 800. 1400. 2500. 4200. 5000. 6000. 8500. 9500.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    done
done


# number=4096
# p=3.825

# temperatures=(0.063 0.039 0.03105 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025 0.002 0.0015 0.001 0.00067 0.0005)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000. 1500. 5000. 10000.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         tauEst=${tauEstimate[$i]}
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#         sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#     done
# done

# number=4096
# p=3.80

# temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(1. 3. 4. 8. 15. 40. 70. 150. 250. 600. 2000. 2500. 4500. 9500.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         tauEst=${tauEstimate[$i]}
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#         sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#     done
# done


# number=4096
# p=3.75

# temperatures=(0.063	0.039 0.03105 0.025 0.02 0.016 0.014 0.012 0.011 0.01 0.0093)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(4. 5. 7. 10. 30. 70. 150. 700. 1400. 4000. 9500.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         tauEst=${tauEstimate[$i]}
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#         sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#     done
# done
#test all the scripts for N=64
# number=64
# p=3.80

# temperatures=(0.1 0.01 0.005 0.001 0.0005)
# records=(0)

# tauEstimate=(9. 99. 999. 5000. 9999.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         tauEst=${tauEstimate[$i]}
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#         sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#     done
# done

