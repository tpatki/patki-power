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


if [ $2 -le 8 ]
then

        sh ~/local/src/power/setcpufreq.sh 1200000 8 15
#       sh ../../../../../setcpufreq.sh 1200000 8 15
fi

srun --nodes=$1 --ntasks=$2 -ppbatch -e lu.err -o out.dat --auto-affinity=start=0,verbose,cpt=1 ../luCL.sh $2

#Reset all cores back to original freq which is 2600000 after the run
#sh ../../../../../setcpufreq.sh 2600000 0 15
sh ~/local/src/power/setcpufreq.sh 2600000 0 15


#srun --nodes=$1 --ntasks=$2 -ppbatch -e lu.err -o out.dat --cpu_bind=sockets ../luCL.sh $2

