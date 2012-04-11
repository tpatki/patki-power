#!/bin/bash
#MSUB -l nodes=16
#MSUB -q pbatch
#MSUB -l walltime=02:40:00

#Call the child script that does the runs

sh cg-rapl-16-node.sh


#Reset by running a 256 task cg benchmark...
export PKG_MINW_MINS=0x38198
export PP0_MINW_MINS=0x38198
export DRAM_MINW_MINS=0x38078
export MSR_PKG_POWER_LIMIT=0x0
export MSR_PP0_POWER_LIMIT=0x0
export MSR_DRAM_POWER_LIMIT=0x0
export MSR_RANK_MOD=16

echo 'Resetting now...'
srun --nodes=16 --ntasks=256 -o rapl-dummy.out -e rapl-dummy.err ../../../rapl-dummy/rapl-dummy

