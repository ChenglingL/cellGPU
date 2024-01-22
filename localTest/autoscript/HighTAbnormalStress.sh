#!/bin/bash
#Ts=(0.001 0.00158489 0.00251189 0.00398107 0.00630957 0.01 0.01584893 0.02511886 0.03981072 0.06309573 0.11 0.12 0.13 0.14 0.15)
Ts=(0.5)
ps=(3.80)
#idxs=($(seq 0 4))
idxs=($(seq 0 1))
for T in "${Ts[@]}"; do
	for p in "${ps[@]}";do
		for idx in "${idxs[@]}";do
			../executable/HighTAbnormalStress.out -g -1 -i 100000  -n 100 -v $T -x $idx -p $p
		done
	done
done