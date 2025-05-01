#!/bin/bash
#Ts=(0.001 0.00158489 0.00251189 0.00398107 0.00630957 0.01 0.01584893 0.02511886 0.03981072 0.06309573 0.11 0.12 0.13 0.14 0.15)
Ns=(1024 512 128)
ps=(3.75 3.85)
for N in "${Ns[@]}"; do
	for p in "${ps[@]}";do
		../executable/monodisperseVoronoi_equilibrium.out -g -1 -n $N -v 0.1 -p $p &
	done
done