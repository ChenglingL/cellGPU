#!/bin/bash
#THis is to test the modified nose-hoover thermostats
#Ts=(0.001 0.00158489 0.00251189 0.00398107 0.00630957 0.01 0.01584893 0.02511886 0.03981072 0.06309573 0.11 0.12 0.13 0.14 0.15)
Ts=(0.1)
Ms=(0 1 2 3 4)
for T in "${Ts[@]}"; do
	for M in "${Ms[@]}";do
		../executable/nvtTest.out -g -1 -n 64 -p 3.75 -v $T -e 0.001 -m $M
	done
done