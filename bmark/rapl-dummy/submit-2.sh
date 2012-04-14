#!/bin/bash
#MSUB -l nodes=2
#MSUB -q pbatch
#MSUB -l walltime=00:05:00

srun --nodes=2 --ntasks=2 -e dummy.err -o out.dat ./rapl-dummy


