#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime
number=4096
p=3.85

eqWaitMultiple=100.
nRelaxations=10.

#temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018)
waittimes=(0.  8000. 9000. 10000. 80000. 90000. 100000.)
temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
records=(0 1 2)


for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        for waittime in ${waittimes[@]}; do
            temp=${temperatures[$i]}
            echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
            /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/SISFCRSISF.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
            /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/overlapCRoverlap.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
        done
    done
done




# number=4096
# p=3.825

# eqWaitMultiple=100.
# nRelaxations=10.

# #temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018)
# waittimes=(0.  8000. 9000. 10000. 80000. 90000. 100000.)
# temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018 0.001 0.00067 0.0005 0.0004 0.00033)
# records=(0 1 2)


# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         for waittime in ${waittimes[@]}; do
#             temp=${temperatures[$i]}
#             echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#             /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/SISFCRSISF.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
#             /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/overlapCRoverlap.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
#         done
#     done
# done



# number=4096
# p=3.85

# eqWaitMultiple=100.
# nRelaxations=10.

# #temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018)
# waittimes=(0. 5000. 6000. 7000. 8000. 9000. 10000. 50000. 60000. 70000. 80000. 90000. 100000.)
# temperatures=(0.001 0.00067 0.0005 0.0004 0.00033)
# records=(0 1 2)


# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         for waittime in ${waittimes[@]}; do
#             temp=${temperatures[$i]}
#             echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#             /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/SISFCRSISF.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
#             /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/overlapCRoverlap.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
#         done
#     done
# done


# number=4096
# p=3.75

# eqWaitMultiple=100.
# nRelaxations=10.

# #temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018)
# waittimes=(0. 5000. 6000. 7000. 8000. 9000. 10000. 50000. 60000. 70000. 80000. 90000. 100000.)
# temperatures=(0.02 0.014 0.012 0.011 0.0093 0.0084)
# records=(0 1 2)


# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         for waittime in ${waittimes[@]}; do
#             temp=${temperatures[$i]}
#             echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#             /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/SISFCRSISF.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
#             /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/overlapCRoverlap.out -n ${number} -p ${p} -v ${temp} -m ${waittime} -r ${recordIdx} -g -1
#         done
#     done
# done