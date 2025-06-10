#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime


nRelaxation=10
number=64
p=3.825

temperatures=(0.0031 0.0025 0.002 0.0015 0.001 0.00067 0.0005)
records=(0)

tauEstimate=(120. 200. 300. 1000. 1500. 5000. 10000.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/SAC_Different_SigmaXY_voronoi.out -n ${number} -v ${temp} -g -1 -a 1.0 -p ${p} -t ${tauEstimate[$i]} -r ${recordIdx} &
    done
done

