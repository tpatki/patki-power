#!/bin/bash

#Bash script that uses msr-tools-1.1.2
#to enable turbo and to set
#the MSR_PKG_POWER_LIMIT to its default value


#set -x

NUM_PACKAGES=2
NUM_CORES_PER_PACKAGE=8

IA32_PERF_CTL_ADDR=0x199
MSR_PKG_POWER_LIMIT_ADDR=0x610
MSR_PKG_POWER_LIMIT_DEFAULT=0x6845000148398

core=0;
#Set bit 32 to zero
disable_turbo_bit=$((~(1<<32)))
while [ $core -lt $(($NUM_PACKAGES * $NUM_CORES_PER_PACKAGE)) ]
do

	#First Enable Turbo
	#Read-modify-write on IA32_PERF_CTL
	#Note that input to ./wrmsr needs to be in hex.

	IA32_PERF_CTL=`./rdmsr -p $core $IA32_PERF_CTL_ADDR`
	temp=$(($disable_turbo_bit & 0x$IA32_PERF_CTL))
	val=`echo "ibase=10;obase=16;$temp"|bc`
	
	./wrmsr -p $core $IA32_PERF_CTL_ADDR 0x$val

	./wrmsr -p $core $MSR_PKG_POWER_LIMIT_ADDR $MSR_PKG_POWER_LIMIT_DEFAULT
	core=$(($core+1));
done 
