#!/bin/bash
Ts=(0.002 0.0025 0.0031)
#Ts=(0.00001 0.0000158489 0.0000251189 0.0000398107 0.0000630957 0.0001 0.0001584893 0.0002511886 0.0003981072 0.0006309573 0.11 0.12 0.13 0.14 0.15)
ps=(3.80)
idxs=(3 4 5 6 7 8 9)
for T in "${Ts[@]}"; do
	for p in "${ps[@]}";do
		for idx in "${idxs[@]}";do
			../executable/nvtLogSpacedwithG.out -g -1 -i 1000000 -t 10000000 -n 512 -v $T -x $idx
		done
	done
done