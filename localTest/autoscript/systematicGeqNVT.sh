#!/bin/bash

Ns=(1024)
dts=(0.001 0.005 0.01 0.02 0.04 0.06 0.08 0.1)
for dt in "${dts[@]}"; do
    for N in "${Ns[@]}"; do
        ../executable/SimpleShearGeqNVT.out -n $N -g -1 -t 1 -r 10 -v 0.01 -s 10000 -p 3.825 -i 2000 -e $dt
    done
done
