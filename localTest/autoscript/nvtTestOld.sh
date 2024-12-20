#!/bin/bash
#THis is to test the modified nose-hoover thermostats. Here we use the old updater.
#Ts=(0.001 0.00158489 0.00251189 0.00398107 0.00630957 0.01 0.01584893 0.02511886 0.03981072 0.06309573 0.11 0.12 0.13 0.14 0.15)
Ts=(0.2 0.1 0.05 0.001)
ps=(3.75 3.85)
for T in "${Ts[@]}"; do
	for p in "${ps[@]}";do
		../executable/nvtTestOld.out -g -1 -n 1024 -p $p -v $T -e 0.01 -t 10000
	done
done