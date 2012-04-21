#!/bin/bash
# $1 = number of nodes desired
# $2 = number of CPU cores desired
set -x

export BMARK_STRING=cg.D.$2

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


#srun --nodes=$1 --ntasks=$2 -ppbatch -e cg.err -o out.dat --cpu_bind=sockets ../cgCL.sh $2

#Use auto-affinity instead of cpu_bind=sockets
#Also, if the second socket is not in use, then set the other socket at a lower frequency

if [ $2 -le 8 ]
then
	sh ../../../../../setcpufreq.sh 1200000 8 15
fi

srun --nodes=$1 --ntasks=$2 -ppbatch -e cg.err -o out.dat --auto-affinity=start=0,verbose,cpt=1 ../cgCL.sh $2

#Reset all cores back to original freq which is 2600000 after the run
sh ../../../../../setcpufreq.sh 2600000 0 15
