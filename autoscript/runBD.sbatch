#!/bin/bash
#SBATCH --mem=2g
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --partition=cpu
#SBATCH --account=bbtm-delta-cpu  # OR bbtm-delta-gpu
#SBATCH --time=48:00:00      # hh:mm:ss for the job
#SBATCH --constraint="scratch"

T=$1
p=$2
idx=$3
./bd.out -n 1024 -t 5000000 -g -1 -p $p -a 1.0 -v $T -x $idx
