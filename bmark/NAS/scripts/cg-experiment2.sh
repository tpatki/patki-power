#!/bin/bash
#MSUB -l nodes=64
#MSUB -q pbatch
#MSUB -l walltime=01:00:00


#Test 2 for Memory Contention -- total 64 tasks (1 to 16 cores per node)

sh ./runCG.sh 64 64 1 1
sh ./runCG.sh 32 32 2 2
sh ./runCG.sh 16 16 4 4
sh ./runCG.sh 18 8 8 8
sh ./runCG.sh 4 4 16 16
