#!/bin/bash

nRelaxation=10
number=4096
p=3.85

records=(10)
temperatures=(3.6E-05 4.5E-05 5.4E-05 7.7E-05 9.1E-05 0.00014 0.00025 0.00033 0.0005 0.001 0.002 0.0025 0.00385 0.005 0.01 0.016 0.039)
tauEstimate=(99999.9 99999.9 99999.9 99999.9 99999.9 99999.9 99999.9 800. 500. 200. 80. 60. 40. 20. 10. 4. 2.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/MCT/FIREtest.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} 
        -g -1 -k 100000 -i 10
    done
done