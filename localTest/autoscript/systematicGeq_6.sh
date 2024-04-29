#!/bin/bash

Ns=(1024)
Mus=(10.0 11.0)
for Mu in "${Mus[@]}"; do
    for N in "${Ns[@]}"; do
        ../executable/SimpleShearGeqBrownian.out -n $N -g -1 -t 1 -r 10 -v 0.01 -s 10000 -p 3.825 -i 2000 -m $Mu
    done
done
