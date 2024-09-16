#!/bin/bash

nRelaxation=10
number=4096
p=3.85


# temperatures=(0.1 0.5 1.0 5.0 10 50 100 500 1000 5000)
temperatures=(1 2 5 10 20 50 100 200 500 1000 2000 5000)
dts=(0.001 0.0001 0.0001 0.0001 0.0001 0.0001 0.0001 0.00001 0.00001 0.00001 0.00001 0.00001)
for i in ${!temperatures[@]}; do
    temp=${temperatures[$i]}
    dt=${dts[$i]}
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/MCT/energy.out -n ${number} -p ${p} -v ${temp} -t 100000 -g -1 -e ${dt}
done
