#!/bin/bash
#MSUB -l nodes=1
#MSUB -q pbatch
#MSUB -l walltime=00:05:00

export PKG_MINW_MINS=0x38198
export PP0_MINW_MINS=0x38198
export DRAM_MINW_MINS=0x38078
export MSR_PKG_POWER_LIMIT=0x38198
export MSR_PP0_POWER_LIMIT=0x0
export MSR_DRAM_POWER_LIMIT=0x38078
export MSR_RANK_MOD=1

export BMARK_STRING=rapl-dummy


#srun -p pdebug -N1 -w rzmerl1 -e dbg1.err -o dbg1.dat ./rapl-dummy
srun -p pdebug -N1 -w rzmerl3 -e dbg3.err -o dbg3.dat ./rapl-dummy

