#!/bin/bash
# $1 = number of nodes desired
# $2 = number of CPU cores desired
set -x

export BMARK_STRING=lu.C.$2

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


srun --nodes=$1 --ntasks=$2 -ppbatch -e lu.err -o out.dat --cpu_bind=sockets ../luCL.sh $2

