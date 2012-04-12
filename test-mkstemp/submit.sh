#!/bin/bash
#MSUB -l nodes=4
#MSUB -q pbatch
#MSUB -l walltime=00:05:00

srun --nodes=4 --ntasks=4 -e test-mkstemp.err -o out.dat ./test-mkstemp


