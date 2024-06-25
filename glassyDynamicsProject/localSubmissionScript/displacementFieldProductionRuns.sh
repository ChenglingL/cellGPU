#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime

# number=4096
# p=3.900

# temperatures=(0.0005 9.1E-05 3.6E-05)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(35.0693 829.48 3000)


# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         waittime=${tauEstimate[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDisplacementFiledProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done

nRelaxation=10
number=4096
p=3.85

temperatures=(0.002 0.00033 9.1E-05)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(80 800 99999.9)


for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDisplacementFiledProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${waittime} -r ${recordIdx} -g -1
    done
done


number=4096
p=3.825

temperatures=(0.00385 0.001 0.0005)
records=(10 11 12 13 14 15 16 17 18 19)
tauEstimate=(80 99999.9 99999.9)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDisplacementFiledProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${waittime} -r ${recordIdx} -g -1
    done
done

number=4096
p=3.80

temperatures=(0.0063 0.0031 0.0022)
records=(10 11 12 13 14 15 16 17 18 19)
tauEstimate=(150 2000 99999.9)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDisplacementFiledProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${waittime} -r ${recordIdx} -g -1
    done
done




number=4096
p=3.775

temperatures=(0.01  0.007  0.0054)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(100 2500 10000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDisplacementFiledProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done


number=4096
p=3.75

temperatures=(0.014 0.011 0.0093)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(150. 1400. 9500.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDisplacementFiledProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done


