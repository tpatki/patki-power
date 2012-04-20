#!/bin/bash
#MSUB -l nodes=16
#MSUB -q pbatch
#MSUB -l walltime=00:05:00

srun --nodes=16 --ntasks=16 -e dummy.err -o out.dat ./rapl-dummy


