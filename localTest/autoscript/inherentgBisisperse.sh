#!/bin/bash

number=1024
max_jobs=5


for p in $(seq 3.78 0.01 3.90); do
    for f in $(seq 0.5 0.1 1.0); do
        for r in $(seq 1.25 0.05 2.0); do
			while (( $(jobs -r | wc -l) >= max_jobs )); do
                sleep 10
            done
            /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulusBidisperse.out -n 1024 -p $p -g -1 -t 100000 -i 1 -e 0.001 -k 0.0 -c 10 -y $r -f $f &
        done
    done
done

# for p in $(seq 3.78 0.01 3.90); do
#     for f in $(seq 0.5 0.1 1.0); do
#         for r in $(seq 1.0 0.02 1.24); do
# 			while (( $(jobs -r | wc -l) >= max_jobs )); do
#                 sleep 10
#             done
#             /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulusBidisperse.out -n 1024 -p $p -g -1 -t 100000 -i 1 -e 0.001 -k 0.0 -c 10 -y $r -f $f &
#         done
#     done
# done

wait