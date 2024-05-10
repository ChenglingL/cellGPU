#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
# number=4096
number=256
p=3.90

#temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
temperatures=(0.039 0.01 0.00385 0.002 0.001 0.0005 0.00033 0.00025 0.00014 9.1E-05 7.7E-05 5.4E-05 4.5E-05 3.6E-05 2.4E-05 1.8E-05 1.6E-05 1.4E-05)
records=(0)

tauEstimate=(2. 10. 40. 80. 200. 500. 800. 1400. 2500. 4200. 5000. 6000. 8500. 9500. 3000 6000 8000 10000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        tauEst=${tauEstimate[$i]}
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
        ../executable/simulationTime.out -n ${number} -p ${p} -v ${temp} -r ${recordIdx} -t ${tauEst} -g -1
    done
done



