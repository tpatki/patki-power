#!/bin/bash
#MSUB -l nodes=16
#MSUB -q pbatch
#MSUB -l walltime=00:05:00

export PKG_MINW_MINS=0x38198
export PP0_MINW_MINS=0x38198
export DRAM_MINW_MINS=0x38078
export MSR_PKG_POWER_LIMIT=0x0
export MSR_PP0_POWER_LIMIT=0x0
export MSR_DRAM_POWER_LIMIT=0x0
export MSR_RANK_MOD=1


export BLR_BENCHMARK=$HOME/local/src/power/bmark/rapl-dummy/rapl-dummy

srun --nodes=16 --ntasks=16 -e dummy16.err -o out16.dat ./rapl-dummy


