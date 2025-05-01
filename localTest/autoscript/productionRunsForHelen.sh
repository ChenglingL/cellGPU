#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
Ns=(128 512 1024)
ps=(3.75 3.85)
Ts=(0.02 0.002)
records=(0 1 2 3 4 5 6 7 8 9)
for N in "${Ns[@]}"; do
    for i in ${!ps[@]}; do
        p=${ps[$i]}
        temp=${Ts[$i]}
        for recordIdx in ${records[@]}; do
            ../executable/productionRunForHelen.out -n $N -p $p -v ${temp} -r ${recordIdx} -t 100 -g -1 
        done
    done
done


# Ns=(32768)
# ps=(3.75 3.85)
# Ts=(0.02 0.002)
# records=(0 1 2 3 4 5 6 7 8 9)
# for N in "${Ns[@]}"; do
#     for i in ${!ps[@]}; do
#         p=${ps[$i]}
#         temp=${Ts[$i]}
#         for recordIdx in ${records[@]}; do
#             ../executable/productionRunForHelen.out -n $N -p $p -v ${temp} -r ${recordIdx} -t 100 -g 1 
#         done
#     done
# done