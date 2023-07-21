#!/bin/bash
#SBATCH --mem=16g
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --partition=cpu
#SBATCH --account=bbtm-delta-cpu  # OR bbtm-delta-gpu
#SBATCH --time=48:00:00      # hh:mm:ss for the job
#SBATCH --constraint="scratch"

index=$1
../bd.out -n 1024 -t 100000000 -g -1 -i 10000000 -e 0.001 -p 3.75 -a 1.0 -v 0.15 -m 1.0 -x $index
