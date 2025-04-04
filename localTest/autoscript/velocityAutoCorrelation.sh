#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime

nRelaxation=10
number=4096
p=3.85

temperatures=(0.002)
records=(10)


tauEstimate=(100.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/velocityAutoCorrelation.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1 &
    done
done

p=3.75

temperatures=(0.02)
records=(10)


tauEstimate=(100.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/velocityAutoCorrelation.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1 &
    done
done


