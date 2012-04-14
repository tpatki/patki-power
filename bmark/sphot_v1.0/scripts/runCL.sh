#!/bin/bash
# $1 = number of nodes desired
# $2 = number of CPU cores desired
set -x

export BMARK_STRING=sphot.$2

name=`date +%Y_%m_%d_%H_%M_%S_%N`
mkdir $name
cd $name
env >> env
hostname >> info
echo $name >> info
uname -a >> info
srun --nodes=1 --ntasks=1 -ppbatch cat /proc/cpuinfo | grep MHz >> info
echo 'cores: '$2 >> info
echo 'nodes: '$1 >> info

echo $1 
echo $name

#Copy the right input file
cp ../../input.dat ./input.dat
cp ../../opac.txt ./opac.txt

srun --nodes=$1 --ntasks=$2 -ppbatch -e sphot.err -o sphot.dat --cpu_bind=sockets sh ../sphotCL.sh

