#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime

nRelaxation=10
number=1024
p=3.85

temperatures=(0.039 0.016 0.01 0.005 0.00385)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(2. 4. 10. 20. 40. 60. 80. 200. 500. 800. 1400. 2500. 4200. 5000. 6000. 8500. 9500.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/forceInference.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done


number=1024
p=3.825

temperatures=(0.063 0.039 0.03105 0.016 0.01)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000. 1500. 5000. 10000.)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/forceInference.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done

number=1024
p=3.80

temperatures=(0.063 0.039 0.03105 0.025 0.016)
records=(10 11 12 13 14 15 16 17 18 19)
tauEstimate=(1. 3. 4. 8. 15. 40. 70. 150. 250. 600. 2000. 2500. 4500. 9500.)
for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/forceInference.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done

number=1024
p=3.775

temperatures=(0.03105 0.025 0.02)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(2 10 20 30 80 100 400 500 2500 2500 3000 7000 10000)
for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/forceInference.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done

number=1024
p=3.75

temperatures=(0.063	0.039 0.03105)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(4. 5. 7. 10. 30. 70. 150. 700. 1400. 4000. 9500.)
for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/forceInference.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done
# nRelaxation=10
# number=4096
# p=3.85

# temperatures=(0.039 0.016 0.01 0.005 0.00385)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(2. 4. 10. 20. 40. 60. 80. 200. 500. 800. 1400. 2500. 4200. 5000. 6000. 8500. 9500.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/sampleForGNNLearning.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done


# number=4096
# p=3.825

# temperatures=(0.063 0.039 0.03105 0.016 0.01)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000. 1500. 5000. 10000.)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/sampleForGNNLearning.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done

# number=4096
# p=3.80

# temperatures=(0.063 0.039 0.03105 0.025 0.016)
# records=(10 11 12 13 14 15 16 17 18 19)
# tauEstimate=(1. 3. 4. 8. 15. 40. 70. 150. 250. 600. 2000. 2500. 4500. 9500.)
# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/sampleForGNNLearning.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done

# number=4096
# p=3.775

# temperatures=(0.03105 0.025 0.02)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(2 10 20 30 80 100 400 500 2500 2500 3000 7000 10000)
# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/sampleForGNNLearning.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done

# number=4096
# p=3.75

# temperatures=(0.063	0.039 0.03105)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(4. 5. 7. 10. 30. 70. 150. 700. 1400. 4000. 9500.)
# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/sampleForGNNLearning.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -s ${tauEstimate[$i]} -r ${recordIdx} -g -1
#     done
# done