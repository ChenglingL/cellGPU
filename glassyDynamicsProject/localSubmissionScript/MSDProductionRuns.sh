#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime


# Ns=(32768 128 512)
# ps=(3.75 3.85)
# Ts=(0.02 0.002)
# records=(0 1 2 3 4 5 6 7 8 9)
# for N in "${Ns[@]}"; do
#     for i in ${!ps[@]}; do
#         p=${ps[$i]}
#         temp=${Ts[$i]}
#         for recordIdx in ${records[@]}; do
#             /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n $N -p $p -v ${temp} -r ${recordIdx} -t 100 -g -1 
#         done
#     done
# done


number=4096
p=3.900

temperatures=(0.039 0.01 0.005 0.002 0.001 0.0005 0.00033 0.00014 9.1E-05 7.7E-05 5.4E-05 4.5E-05 3.6E-05)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(0.596396 1.36006 8.39117 8.32344 46.2416 35.0693 135.321 564.239 829.48 897.484 1365.27 1522.57 3000)


for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done

nRelaxation=10
number=4096
p=3.85

temperatures=(0.00025 0.00014 9.1E-05 7.7E-05 5.4E-05 4.5E-05 3.6E-05)
records=(11 12 13)
waittime=999999

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
    done
done


number=4096
p=3.825

temperatures=(0.001 0.00067 0.0005)
records=(11 12 13)
waittime=999999

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
    done
done

number=4096
p=3.80

temperatures=(0.0028 0.0025 0.0022)
records=(11 12 13)
waittime=999999

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
    done
done

# nRelaxation=10
# number=4096
# p=3.85

# temperatures=(0.039 0.016 0.01 0.005 0.00385 0.0025 0.002 0.001 0.0005 0.00033 0.00025 0.00014 9.1E-05 7.7E-05 5.4E-05 4.5E-05 3.6E-05)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(2. 4. 10. 20. 40. 60. 80. 200. 500. 800. 1400. 2500. 4200. 5000. 6000. 8500. 9500.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done


# number=4096
# p=3.775

# temperatures=(0.03105 0.025 0.02 0.016 0.012 0.01 0.009 0.008 0.0075 0.007 0.0063 0.0056 0.0054)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(2 10 20 30 80 100 400 500 2500 2500 3000 7000 10000)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         waittime=${tauEstimate[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done
# number=4096
# p=3.825

# temperatures=(0.063 0.039 0.03105 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025 0.002 0.0015 0.001 0.00067 0.0005)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000. 1500. 5000. 10000.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done

# number=4096
# p=3.80

# temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022)
# records=(10 11 12 13 14 15 16 17 18 19)
# tauEstimate=(1. 3. 4. 8. 15. 40. 70. 150. 250. 600. 2000. 2500. 4500. 9500.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         waittime=${tauEstimate[$i]}
#         echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done

# number=4096
# p=3.75

# temperatures=(0.063 0.039 0.03105 0.025 0.02 0.016 0.014 0.012 0.011 0.01 0.0093)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(4. 5. 7. 10. 30. 70. 150. 700. 1400. 4000. 9500.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         waittime=${tauEstimate[$i]}
#         echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueMSDProductionRuns.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done


