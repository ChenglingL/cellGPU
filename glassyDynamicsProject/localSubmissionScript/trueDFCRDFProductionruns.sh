#!/bin/bash

#jobs on the CPU -- for n=4096, I estimate that if tau_alpha <= 10^(10/3) then it will finish within the 48 hour maxJobTime
#jobs on the CPU -- for n=32768, I estimate that if tau_alpha <= 10^(7/3) then it will finish within the 48 hour maxJobTime


number=4096
p0s=(3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.8 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75 3.75)
ids=(14 15 17 15 17 16 15 16 17 14 16 17 15 16 17 14 15 16 14 15 17 14 15 16 15 16 14 16 19 19 16 17 18 19 18 15 17 19 17 18 18 19 19)
temperatures=(0.063 0.063 0.063 0.039 0.039 0.03105 0.025 0.025 0.025 0.016 0.016 0.016 0.01 0.01 0.01 0.008 0.008 0.008 0.0063 0.0063 0.0063 0.005 0.005 0.005 0.00385 0.00385 0.0031 0.063 0.039 0.03105 0.025 0.025 0.025 0.025 0.02 0.016 0.016 0.016 0.014 0.014 0.012 0.012 0.011)
tauEstimate=(1 1 1 3 3 4 8 8 8 15 15 15 40 40 40 70 70 70 150 150 150 250 250 250 600 600 2000 4 5 7 10 10 10 10 30 70 70 70 150 150 700 700 1400)
for i in ${!temperatures[@]}; do
    tauEst=${tauEstimate[$i]}
    temp=${temperatures[$i]}
    p=${p0s[$i]}
    recordIdx=${ids[$i]}
    echo ${number} ${p} ${temp} ${recordIdx} ${tauEst}
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDFCRDFProductionRun.out -n ${number} -p ${p} -v ${temp} -t ${tauEst} -r ${recordIdx} -g -1
done




nRelaxation=10
number=4096
p=3.85

temperatures=(0.039 0.016 0.01 0.005 0.00385 0.0025 0.002 0.001 0.0005 0.00033 0.00025 0.00014 9.1E-05 7.7E-05 5.4E-05 4.5E-05 3.6E-05)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(2. 4. 10. 20. 40. 60. 80. 200. 500. 800. 99999.9 99999.9 99999.9 99999.9 99999.9 99999.9 99999.9)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDFCRDFProductionRun.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done



number=4096
p=3.825

temperatures=(0.063 0.039 0.03105 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0025 0.002 0.0015 0.001 0.00067 0.0005)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(1. 2. 4. 9. 15. 25. 40. 60. 80. 120. 200. 300. 1000. 99999.9 99999.9 99999.9)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDFCRDFProductionRun.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done

number=4096
p=3.80

temperatures=(0.063 0.039 0.03105 0.025 0.016 0.01 0.008 0.0063 0.005 0.00385 0.0031 0.0028 0.0025 0.0022)
records=(10 11 12 13 14 15 16 17 18 19)
tauEstimate=(1. 3. 4. 8. 15. 40. 70. 150. 250. 600. 2000. 99999.9 99999.9 99999.9)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDFCRDFProductionRun.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done

number=4096
p=3.75

temperatures=(0.063 0.039 0.03105 0.025 0.02 0.016 0.014 0.012 0.011 0.01 0.0093)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(4. 5. 7. 10. 30. 70. 150. 700. 1400. 99999.9 99999.9)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${waittime} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDFCRDFProductionRun.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done



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
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDFCRDFProductionRun.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done

number=4096
p=3.775

temperatures=(0.03105 0.025 0.02 0.016 0.012 0.01 0.009 0.008 0.0075 0.007 0.0063 0.0056 0.0054)
records=(10 11 12 13 14 15 16 17 18 19)

tauEstimate=(2 10 20 30 80 100 400 500 2500 2500 3000 7000 10000)

for recordIdx in ${records[@]}; do
    for i in ${!temperatures[@]}; do
        temp=${temperatures[$i]}
        waittime=${tauEstimate[$i]}
        echo ${number} ${p} ${temp} ${recordIdx}
        /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/trueDFCRDFProductionRun.out -n ${number} -p ${p} -v ${temp} -t ${tauEstimate[$i]} -r ${recordIdx} -g -1
    done
done