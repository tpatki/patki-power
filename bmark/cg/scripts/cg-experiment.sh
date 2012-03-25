#!/bin/bash
#MSUB -l nodes=128
#MSUB -q pbatch
#MSUB -l walltime=01:00:00


#Test 1 for Memory Contention -- total 256 tasks (2 to 16 cores per node)

sh ./runCG.sh 128 128 2 2
sh ./runCG.sh 64 64 4 4
sh ./runCG.sh 32 32 8 8


#Test 2 for Memory Contention -- total 128 tasks (1 to 16 cores per node)

sh ./runCG.sh 128 128 1 1
sh ./runCG.sh 64 64 2 2
sh ./runCG.sh 32 32 4 4
sh ./runCG.sh 16 16 8 8

            
