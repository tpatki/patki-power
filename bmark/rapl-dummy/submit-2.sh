#!/bin/bash
#MSUB -l nodes=2
#MSUB -q pbatch
#MSUB -l walltime=00:05:00

export BLR_BENCHMARK=$HOME/local/src/power/bmark/rapl-dummy/rapl-dummy

srun --nodes=2 --ntasks=2 -e dummy2.err -o out2.dat ./rapl-dummy


