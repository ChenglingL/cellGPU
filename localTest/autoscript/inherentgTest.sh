#!/bin/bash
ps=(3.70 3.72 3.74)
for p in ${ps[@]}; do
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 1024 -p $p -g -1 -t 1000000 -i 100 -e 0.001 -k 1.0 -c 10
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 1024 -p $p -g -1 -t 1000000 -i 100 -e 0.001 -k 0.01 -c 10
done
