#!/bin/bash
for p in $(seq 3.805 0.001 3.82); do
	/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/vertexFIRE.out -n 1024 -p $p -g -1 -t 100000 -i 5 -e 0.001 -k 1.0 -c 10 -f 0.8 -y 1.0
done
for p in $(seq 3.81 0.001 3.90); do
	/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/vertexFIRE.out -n 1024 -p $p -g -1 -t 100000 -i 5 -e 0.001 -k 1.0 -c 10 -f 0.8 -y 1.25
done




