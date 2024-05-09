#!/bin/bash

Ns=(1024)
#omegas=(0.1 0.2 0.4 0.8 1.0 2.0 4.0 0.85 0.95 1.05 1.10)
omegas=(0.86 0.87 0.88 0.89 0.90 0.91 0.92 0.93 0.94 0.96 0.97 0.98 0.99 0.05 0.01 5 6 7 8 9 10)
# omegas=(0.1 0.2 0.4 0.8 1.0 2.0 4.0)
for omega in "${omegas[@]}"; do
    for N in "${Ns[@]}"; do
        ../executable/SimpleShearGeqNVT.out -n $N -g -1 -t 1 -r 10 -v 0.01 -s 10000 -p 3.825 -i 2000 -m $omega
    done
done
