#!/bin/bash
# $1 = number of nodes desired
# $2 = number of CPU cores desired
set -x

export BLR_BENCHMARK=$HOME/local/src/power/bmark/NAS/bin/is.C.$2

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


srun --nodes=$1 --ntasks=$2 -ppbatch -e is.err -o out.dat --cpu_bind=sockets ../isCL.sh $2

