#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime

# number=4096
# p=3.80

# temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022)
# records=(10 11 12 13 14 15 16 17 18 19)
# tauEstimate=(99999.9 99999.9 99999.9 99999.9 99999.9 40. 70. 150. 250. 600. 2000. 99999.9 99999.9 99999.9)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         waittime=${tauEstimate[$i]}
#         echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/ScatteringFunctionMCT.out -n ${number} -p ${p} -v ${temp} -t ${waittime} -r ${recordIdx} -g -1
#     done
# done
# number=4096
# p=3.85

# temperatures=(0.039 0.016 0.01 0.005 0.00385 0.0025 0.002 0.001 0.0005 0.00033 0.00025 0.00014 9.1E-05 7.7E-05 5.4E-05 4.5E-05 3.6E-05)
# records=(10 11 12 13 14 15 16 17 18 19)
# tauEstimate=(99999.9 99999.9 99999.9 99999.9 99999.9 60. 80. 200. 500. 800. 99999.9 99999.9 99999.9 99999.9 99999.9 99999.9 99999.9)

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         waittime=${tauEstimate[$i]}
#         echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/ScatteringFunctionMCT.out -n ${number} -p ${p} -v ${temp} -t ${waittime} -r ${recordIdx} -g -1
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
#         echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/ScatteringFunctionSmallK.out -n ${number} -p ${p} -v ${temp} -t ${waittime} -r ${recordIdx} -g -1
#     done
# done

# nRelaxation=10
# number=4096
# p=3.825

# temperatures=(0.063 0.039 0.03105 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025 0.002 0.0015 0.001 0.00067 0.0005)
# records=(10 11 12 13 14 15 16 17 18 19)

# tauEstimate=(99999.9 99999.9 99999.9 99999.9 99999.9 25. 40. 60. 80. 120. 200. 300. 1000. 99999.9 99999.9 99999.9 )

# for recordIdx in ${records[@]}; do
#     for i in ${!temperatures[@]}; do
#         temp=${temperatures[$i]}
#         echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/ScatteringFunctionMCT.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
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
#         /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/ScatteringFunctionSmallK.out -n ${number} -p ${p} -v ${temp} -t ${waittime} -r ${recordIdx} -g -1
#     done
# done

number=4096
p=3.75

temperatures=(0.063	0.039 0.03105 0.025 0.02 0.016 0.014 0.012 0.011 0.01 0.0093)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(99999.9 99999.9 99999.9 10. 30. 70. 150. 700. 1400. 99999.9 99999.9)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/ScatteringFunctionMCT.out -n ${number} -p ${p} -v ${temp} -t ${waittime} -r ${recordIdx} -g -1
    done
done


# number=4096
# p=3.85

# eqWaitMultiple=100.
# nRelaxations=10.

# #temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022 0.002 0.0018)
# waittimes=(0.  8000. 9000. 10000. 80000. 90000. 100000.)
# temperatures=(0.00025 0.00018 0.00014 0.00011 0.0001 0.000087 0.000077)
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