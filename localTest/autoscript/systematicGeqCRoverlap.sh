#!/bin/bash

Ns=(1024)
Mus=(0.1 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 10.0 11.0 12.0 13.0)
for Mu in "${Mus[@]}"; do
    for N in "${Ns[@]}"; do
        ../executable/CRoverlap.out -n $N -g -1 -r 10 -v 0.01 -p 3.825 -m $Mu
    done
done
