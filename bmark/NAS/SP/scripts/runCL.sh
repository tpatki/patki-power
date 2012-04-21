#!/bin/bash
# $1 = number of nodes desired
# $2 = number of CPU cores desired
set -x

export BMARK_STRING=sp.D.$2


#The following is to set the right number of nodes and tasks in BT and SP

n=$1
cores=$2

# Need to run the closest square 
#128 tasks, 16 nodes, 8 cores/node
#Closest sqaure is 121, so at 8 cores/node, you need 8 (cores) * 15(nodes) + 1 (last node) 

if [ $cores -eq 128 ] && [ $n -eq 16 ]
then
	cores=121
	n=16
fi

#128 tasks, 32 nodes, 4 cores/node
#Closest sqaure is 121, so at 4 cores/node, you need 4 (cores) * 30(nodes) + 1 (last node) = total 31 nodes

if [ $cores -eq 128 ] && [ $n -eq 32 ]
then
	cores=121
	n=31
fi


#512 tasks, 32 nodes, 16 cores/node
#Closest square is 484, so at 16 cores/node, you need 16 * 30 + 4 * 1 = total 31 nodes

if [ $cores -eq 512 ] && [ $n -eq 32 ]
then
        cores=484
        n=31
fi

#512 tasks, 64 nodes, 8 cores/node
#Closest square is 484, so at 8 cores/node, you need 8 * 60 + 4 * 1 = total 61 nodes

if [ $cores -eq 512 ] && [ $n -eq 64 ]
then
        cores=484
        n=61
fi


#512 tasks, 128 nodes, 4 cores/node
#Closest square is 484, so at 4 cores/node, you need 4 * 121  = total 121 nodes

if [ $cores -eq 512 ] && [ $n -eq 128 ]
then
        cores=484
        n=121
fi

#2048 tasks, 128 nodes, 16 cores/node
#Closest square is 2025, so at 16 cores/node, you need 16 *126 + 9 * 1 = total 127 nodes

if [ $cores -eq 2048 ] && [ $n -eq 128 ]
then
        cores=2025
        n=127
fi


name=`date +%Y_%m_%d_%H_%M_%S_%N`
mkdir $name
cd $name
touch out.dat
env > env
hostname >> info
echo $name >> info
uname -a >> info
srun --nodes=1 --ntasks=1 -ppbatch cat /proc/cpuinfo | grep MHz >> info
echo 'cores: '$2 >> info
echo 'nodes: '$1 >> info


if [ $2 -le 8 ]
then

        sh ~/local/src/power/setcpufreq.sh 1200000 8 15
#       sh ../../../../../setcpufreq.sh 1200000 8 15
fi

srun --nodes=$n --ntasks=$cores -ppbatch -e sp.err -o out.dat --auto-affinity=start=0,verbose,cpt=1 ../spCL.sh $cores

#Reset all cores back to original freq which is 2600000 after the run
#sh ../../../../../setcpufreq.sh 2600000 0 15
sh ~/local/src/power/setcpufreq.sh 2600000 0 15


#srun --nodes=$n --ntasks=$cores -ppbatch -e sp.err -o out.dat --cpu_bind=sockets ../spCL.sh $cores

