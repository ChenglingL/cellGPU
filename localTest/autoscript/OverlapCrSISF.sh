#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
p=3.8

eqWaitMultiple=100.
nRelaxations=10.

tauEstimate=(10. 21.54 46.41 100. 215.44 464.15 1000.)
temperatures=(0.08868 0.05586 0.03756 0.02652 0.01945 0.01471 0.01141)


records=(0 1 2)

for recordIdx in ${records[@]}; do
    for i in ${!tauEstimate[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${tauEst} ${eqWaitMultiple} ${nRelaxations}  ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/overlapCRSISF.out -n ${number} -p ${p} -v ${temp} -t ${tauEst} -i ${eqWaitMultiple} -m ${nRelaxations} -r ${recordIdx} -g -1
    done
done


