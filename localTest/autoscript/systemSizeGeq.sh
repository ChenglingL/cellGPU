#!/bin/bash

Ns=(1024)
Mus=(11.0 12.0 13.0)
for Mu in "${Mus[@]}"; do
    for N in "${Ns[@]}"; do
        ../executable/SimpleShearSystemSizeBrownian.out -n $N -g -1 -t 1 -r 10 -v 0.063 -s 1000 -p 3.825 -i 1000 -m $Mu
    done
done
