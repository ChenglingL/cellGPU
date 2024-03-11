#!/bin/bash
ps=(3.74 3.78)
for p in ${ps[@]}; do
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 512 -p $p -g -1 -t 1000000 -e 0.001 -k 1.0 -c 30 -v 1.0301
done
