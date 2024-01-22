#!/bin/bash
#Ts=(0.001 0.00158489 0.00251189 0.00398107 0.00630957 0.01 0.01584893 0.02511886 0.03981072 0.06309573 0.11 0.12 0.13 0.14 0.15)
Ts=(0.1584893 0.2511886 0.3981072 0.6309573)
ps=(3.80)
idxs=(0)
for T in "${Ts[@]}"; do
	for p in "${ps[@]}";do
		for idx in "${idxs[@]}";do
			../executable/nvtLogSpacedwithG.out -g -1 -i 100000 -t 5000000 -n 1024 -v $T -x $idx
		done
	done
done