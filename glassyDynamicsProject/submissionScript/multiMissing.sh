#!/bin/bash

## make the trajectory to save 20 states per decade

number=4096
p0s=(3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75)
ids=(14 15 17 15 17 16 15 16 17 14 16 17 15 16 17 14 15 16 14 15 17 14 15 16 15 16 16 19 19 16 17 18 19 18 15 17 19 17 18 18 19)
temperatures=(0.063 0.063 0.063 0.039 0.039 0.03105 0.025 0.025 0.025 0.016 0.016 0.016 0.01 0.01 0.01 0.008 0.008 0.008 0.0063 0.0063 0.0063 0.005 0.005 0.005 0.00385 0.00385 0.063 0.039 0.03105 0.025 0.025 0.025 0.025 0.02 0.016 0.016 0.016 0.014 0.014 0.012 0.012)
tauEstimate=(1 1 1 3 3 4 8 8 8 15 15 15 40 40 40 70 70 70 150 150 150 250 250 250 600 600 4 5 7 10 10 10 10 30 70 70 70 150 150 700 700)
for i in ${!temperatures[@]}; do
    tauEst=${tauEstimate[$i]}
    temp=${temperatures[$i]}
    p=${p0s[$i]}
    recordIdx=${ids[$i]}
    echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleMissingTrajectory.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
done
# number=4096
# p0s=(3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75)
# ids=(14 15 17 15 17 16 15 16 17 14 16 17 15 16 17 14 15 16 14 15 17 14 15 16 15 16 14 16 19 19 16 17 18 19 18 15 17 19 17 18 18 19 19)
# temperatures=(0.063 0.063 0.063 0.039 0.039 0.03105 0.025 0.025 0.025 0.016 0.016 0.016 0.01 0.01 0.01 0.008 0.008 0.008 0.0063 0.0063 0.0063 0.005 0.005 0.005 0.00385 0.00385 0.0031 0.063 0.039 0.03105 0.025 0.025 0.025 0.025 0.02 0.016 0.016 0.016 0.014 0.014 0.012 0.012 0.011)
# tauEstimate=(1 1 1 3 3 4 8 8 8 15 15 15 40 40 40 70 70 70 150 150 150 250 250 250 600 600 2000 4 5 7 10 10 10 10 30 70 70 70 150 150 700 700 1400)
# for i in ${!temperatures[@]}; do
#     tauEst=${tauEstimate[$i]}
#     temp=${temperatures[$i]}
#     p=${p0s[$i]}
#     recordIdx=${ids[$i]}
#     echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#     sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleMissingTrajectory.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
# done


# number=4096
# p0s=(3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75)
# ids=(14 15 17 15 17 16 15 16 17 14 16 17 15 16 17 14 15 16 14 15 17 14 15 16 15 16 14 14 15 16 15 16 19 10 14 16 16 19 19 16 17 18 19 18 15 17 19 17 18 18 19 19 16 18 15 16 19)
# temperatures=(0.063 0.063 0.063 0.039 0.039 0.03105 0.025 0.025 0.025 0.016 0.016 0.016 0.01 0.01 0.01 0.008 0.008 0.008 0.0063 0.0063 0.0063 0.005 0.005 0.005 0.00385 0.00385 0.0031 0.0028 0.0028 0.0028 0.0025 0.0025 0.0025 0.0022 0.0022 0.0022 0.063 0.039 0.03105 0.025 0.025 0.025 0.025 0.02 0.016 0.016 0.016 0.014 0.014 0.012 0.012 0.011 0.01 0.01 0.0093 0.0093 0.0093)
# tauEstimate=(1 1 1 3 3 4 8 8 8 15 15 15 40 40 40 70 70 70 150 150 150 250 250 250 600 600 2000 2500 2500 2500 4500 4500 4500 9500 9500 9500 4 5 7 10 10 10 10 30 70 70 70 150 150 700 700 1400 4000 4000 9500 9500 9500)
# for i in ${!temperatures[@]}; do
#     tauEst=${tauEstimate[$i]}
#     temp=${temperatures[$i]}
#     p=${p0s[$i]}
#     recordIdx=${ids[$i]}
#     echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
#     sbatch /u/cli6/cellGPU/glassyDynamicsProject/submissionScript/singleProductionRunCPU.sh ${number} ${p} ${temp} ${recordIdx} ${tauEst}
# done

