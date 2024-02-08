#!/bin/bash

for ((i=0; i<=100; i++)); do
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/Fschi4.out -p 3.80 -n 4096 -v 0.018 -x $i -g -1
done