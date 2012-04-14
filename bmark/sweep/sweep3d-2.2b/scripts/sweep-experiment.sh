#!/bin/bash
#MSUB -l nodes=128
#MSUB -q pbatch
#MSUB -l walltime=02:30:00

#Test 1: 256 tasks, vary from 2 to 16 cores/node

#Test to see if the cache performance of using all cores/node is better than fewer cores/node.
#This may not exactly result in a significant improvement in execution time, but is still
#an interesting trend.
#You need to use papi for this -- make sure that sweepCL.sh is running with PAPIEX
#Observe that when using all cores on a node the L3_TCM/L3_TCA ratio is low.
#On merl, we look at L3 instead of L2, as that's the last level cache. On hyperion the LLC is L2.

#sh ./runSweep.sh 128 128 2 2
#sh ./runSweep.sh 64 64 4 4
#sh ./runSweep.sh 32 32 8 8
#sh ./runSweep.sh 16 16 16 16


export PKG_MINW_MINS=0x38198
export PP0_MINW_MINS=0x38198
export DRAM_MINW_MINS=0x38078
export MSR_PKG_POWER_LIMIT=0x0
export MSR_PP0_POWER_LIMIT=0x0
export MSR_DRAM_POWER_LIMIT=0x0
export MSR_RANK_MOD=16
export BMARK_STRING=sweep.64

sh ./runSweep.sh 4 4 16 16

#Test 2: Test preliminary scalability for sweep -- from 128 tasks to 2048 tasks, using 16 cores/node
#sh ./runSweep.sh 8 128 16 16

