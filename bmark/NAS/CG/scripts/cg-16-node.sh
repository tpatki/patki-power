#!/bin/bash
#MSUB -l nodes=16
#MSUB -q pbatch
#MSUB -l walltime=02:40:00

#Call the child script that does the runs

export POWER_DIR=${HOME}/local/src/power

echo $POWER_DIR

cd ${POWER_DIR}/bmark/NAS/CG/scripts
sh cg-rapl-16-node.sh
cd ${POWER_DIR}/dummy-tmp


#Reset by running a 256 task cg benchmark...
export PKG_MINW_MINS=0x0
export PP0_MINW_MINS=0x0
export DRAM_MINW_MINS=0x0
export MSR_PKG_POWER_LIMIT=0x0
export MSR_PP0_POWER_LIMIT=0x0
export MSR_DRAM_POWER_LIMIT=0x0
export MSR_RANK_MOD=16

echo 'Resetting now...'
srun --nodes=16 --ntasks=256 -o rapl-dummy.out -e rapl-dummy.err ../bmark/rapl-dummy/rapl-dummy
cd ..
