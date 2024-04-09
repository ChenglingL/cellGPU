#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
#p=3.75
p=3.80

eqWaitMultiple=100.
nRelaxations=10.

#temperatures=(0.10 0.09 0.08 0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025)
#tauEstimates=(5. 5. 5. 6.68761 14.5619 19.7405 30.1575 88.8258 4999.69 5000. 5000. 5000. 5000. 5000. 5000.)
tauEstimates=(0.999983 2.50014 3.9034 7.24834 14.011 33.8089 63.6444 110.477 213.261 510.714 1507.02 2327.63 4012.09 5000.)
temperatures=(0.063 0.039 0.03105 0.025 0.016  0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022)
records=(0)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        tauEstimate=${tauEstimates[$i]}
        echo ${number} ${p} ${temp} ${tauEstimate} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/2DmeltingPhase.out -n ${number} -p ${p} -v ${temp} -s ${tauEstimate} -x ${recordIdx} -g -1
    done
done


