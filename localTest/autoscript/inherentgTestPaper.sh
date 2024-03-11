#!/bin/bash
ps=(3.70 3.71 3.72 3.73 3.74 3.75 3.76 3.77 3.75)
for p in ${ps[@]}; do
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulusPaper.out -n 1024 -p $p -g -1 -t 100000 -i 5 -e 0.001 -k 1.0 -c 50
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulusPaper.out -n 1024 -p $p -g -1 -t 100000 -i 5 -e 0.001 -k 0.01 -c 50
done
