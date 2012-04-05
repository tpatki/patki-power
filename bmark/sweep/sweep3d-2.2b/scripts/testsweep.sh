#!/bin/bash
#MSUB -l nodes=16
#MSUB -q pbatch
#MSUB -l walltime=00:05:00


#srun --nodes=16 --ntasks=256 -ppbatch -e sweep.err -o sweep.dat --cpu_bind=sockets sh ../sweep
sh runCL.sh 16 256

