#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime



number=4096
p=3.90

temperatures=(0.039 0.01 0.005 0.002)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(0.596396 1.36006 8.39117 8.32344 46.2416 35.0693 135.321 564.239 829.48 897.484 1365.27 1522.57 3000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/ExtendedTrajectory.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1 -l 100000
    done
done


