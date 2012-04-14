#!/bin/bash
# $1 = number of nodes desired
# $2 = number of CPU cores desired
set -x

export BLR_BENCHMARK=cg.D.$2

name=`date +%Y_%m_%d_%H_%M_%S_%N`
mkdir $name
cd $name
touch out.dat
env > env
hostname >> info
echo $name >> info
uname -a >> info
#srun --nodes=1 --ntasks=1 -ppfio cat /proc/cpuinfo | grep MHz >> info
#srun --nodes=1 --ntasks=1 --time=1 -ppbatch cat /proc/cpuinfo | grep MHz >> info
srun --nodes=1 --ntasks=1 -ppbatch cat /proc/cpuinfo | grep MHz >> info
echo 'cores: '$2 >> info
echo 'nodes: '$1 >> info

#srun --nodes=$2 --ntasks=$3 -ppfio --cpu_bind=sockets ./cgCL.sh $3 > out.dat
#srun --nodes=$1 --ntasks=$2 --time=10 -ppbatch --cpu_bind=sockets ../cgCL.sh $2 > out.dat


srun --nodes=$1 --ntasks=$2 -ppbatch -e cg.err -o out.dat --cpu_bind=sockets ../cgCL.sh $2

