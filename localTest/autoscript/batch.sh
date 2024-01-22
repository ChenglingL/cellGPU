#!/bin/bash
Ts=(0.001 0.00158489 0.00251189 0.00398107 0.00630957 0.01 0.01584893 0.02511886 0.03981072 0.06309573 0.1)
#Ts=(0.00001 0.0000158489 0.0000251189 0.0000398107 0.0000630957 0.0001 0.0001584893 0.0002511886 0.0003981072 0.0006309573 0.11 0.12 0.13 0.14 0.15)
ps=(3.70 3.72 3.74 3.76 3.78 3.80 3.82 3.84 3.86 3.88 3.90)
idxs=(0 1 2)
for T in "${Ts[@]}"; do
	for p in "${ps[@]}";do
		for idx in "${idxs[@]}";do
			sbatch --job-name=preliminaryGD_T${T}_p_${p} --output=nvt.txt runNVT.sbatch $T $p $idx
			sbatch --job-name=preliminaryGD_T${T}_p_${p} --output=bd.txt runBD.sbatch $T $p $idx
		done
	done
done
