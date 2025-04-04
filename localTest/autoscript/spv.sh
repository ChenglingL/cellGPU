#!/bin/bash


number=400

ps=(3.5 3.65 3.7 3.75 3.8 3.85)


for i in ${!ps[@]}; do
    p=${ps[$i]}
    echo ${number} ${p}
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/spv.out -n ${number} -p ${p} -v 0.1 -t 1000000 -e 0.1 -i 100 -g -1 &
done



