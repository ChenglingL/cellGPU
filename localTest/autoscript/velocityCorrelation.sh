#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime

nRelaxation=10
number=4096
p=3.85

temperatures=(0.001 0.0005)
records=(10)


tauEstimate=(200. 500.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/velocityCorrelation.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1 &
    done
done


number=4096
p=3.825

temperatures=(0.0025 0.002)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(200. 300.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/velocityCorrelation.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1 &
    done
done

number=4096
p=3.80

temperatures=(0.0063 0.005)
records=(10)
tauEstimate=(150. 250.)
for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/velocityCorrelation.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1 &
    done
done

