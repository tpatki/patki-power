#!/bin/bash
#MSUB -l nodes=1
#MSUB -q pbatch
#MSUB -l walltime=00:05:00

srun --nodes=1 --ntasks=1 -e dummy.err -o out.dat ./rapl-dummy


