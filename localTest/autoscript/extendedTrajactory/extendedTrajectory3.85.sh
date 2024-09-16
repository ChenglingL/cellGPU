#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime


nRelaxation=10
number=4096
p=3.85

temperatures=(0.039 0.016 0.01 0.005 0.00385)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(2. 4. 10. 20. 40. 60. 80. 200. 500. 800. 1400. 2500. 4200. 5000. 6000. 8500. 9500.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/ExtendedTrajectory.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1 -l 100000
    done
done
