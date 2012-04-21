#!/bin/bash

# Invoke (on hyperion) via 
#pdsh -w "hyperion-fio[1-64]" sh setCpuFreq.sh 2667000 8 
#(need proper command on merl)

# $1: CPU freq
# $2: First core
# $3: Last core

#2668000 2667000 2533000 2400000 2267000 2133000 
#2000000 1867000 1733000 1600000 

cd ..

echo "setting frequency to ${1} KHz on cores ${2} through ${3}"

# Already set to userspace and we don't have write perms.
#for i in `seq 0 $2`; do echo userspace > /sys/devices/system/cpu/cpu${i}/cpufreq/scaling_governor; done

for i in `seq $2 $3`; do echo $1 > /sys/devices/system/cpu/cpu${i}/cpufreq/scaling_setspeed; done

