#!/bin/bash
ps=(3.70)
for p in ${ps[@]}; do
    #/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 1024 -p $p -g -1 -t 1000000 -i 100 -e 0.00001 -k 1.0 -c 10
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 1024 -p $p -g -1 -t 1000000 -i 100 -e 0.0005 -k 1.0 -c 10
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 1024 -p $p -g -1 -t 1000000 -i 100 -e 0.0001 -k 1.0 -c 10
    # /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 1024 -p $p -g -1 -t 1000000 -i 100 -e 0.05 -k 1.0 -c 10
    # /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 1024 -p $p -g -1 -t 1000000 -i 100 -e 0.1 -k 1.0 -c 10
    #/home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 512 -p $p -g -1 -t 1000000 -i 100 -e 0.00001 -k 1.0 -c 10
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 512 -p $p -g -1 -t 1000000 -i 100 -e 0.0005 -k 1.0 -c 10
    /home/chengling/Research/Project/Cell/AnalyticalG/cellGPU/localTest/executable/inherentShearModulus.out -n 512 -p $p -g -1 -t 1000000 -i 100 -e 0.0001 -k 1.0 -c 10
done
