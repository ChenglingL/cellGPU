#!/bin/bash

#jobs on the GPU -- for n=4096 and n=32768, I estimate that if tau_alpha <= 10^(13/3) then it will finish within the 48 hour maxJobTime
#                   as a result, this script does the complement of the CPU submit scripts will need to write some extra logic to get around the 48 maxJobTime limit for even longer runs
p=3.8
number=4096

eqWaitMultiple=100.
nRelaxations=10.

#note for p=3.8 I have two different estimates of the longer relaxation times... not sure which is right, so we'll go to the lower temperature and check for consistency
tauEstimate=(4642.59 10000. 21544.3 4641.59 10000. 20000)
temperatures=(0.007287 0.005965 0.004949 0.0031 0.0025 0.002)

records=(0 1 2 3 4 5 6 7 8 9)

for recordIdx in ${records[@]}; do
    for i in ${!tauEstimate[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${tauEst} ${eqWaitMultiple} ${nRelaxations}  ${recordIdx}
        sbatch baseSubmitGPU.sh ${number} ${p} ${temp} ${tauEst} ${eqWaitMultiple} ${nRelaxations} ${recordIdx}
    done
done

number=32768
tauEstimate=(464.15 1000. 2154.43 4641.59 10000. 21544.3 4641.59 10000. 21544.3)
temperatures=(0.01471 0.01141 0.009038 0.007287 0.005965 0.004949 0.0031 0.0025 0.002)

for recordIdx in ${records[@]}; do
    for i in ${!tauEstimate[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${tauEst} ${eqWaitMultiple} ${nRelaxations}  ${recordIdx}
        sbatch baseSubmitGPU.sh ${number} ${p} ${temp} ${tauEst} ${eqWaitMultiple} ${nRelaxations} ${recordIdx}
    done
done

