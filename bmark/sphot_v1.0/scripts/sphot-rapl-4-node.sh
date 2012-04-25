#!/bin/bash

#BLR_BENCHMARK is exported by runCL.sh


#51W 0x038198
#65W 0x038208
#80W 0x038280
#95W 0x0382f8

#15W 0x038078
#20W 0x0380a0
#25W 0x0380c8
#30W 0x0380f0

export PKG_MINW_MINS=0x38198
export PP0_MINW_MINS=0x38198
export DRAM_MINW_MINS=0x38078
export MSR_PKG_POWER_LIMIT=0x0
export MSR_PP0_POWER_LIMIT=0x0
export MSR_DRAM_POWER_LIMIT=0x0
export MSR_RANK_MOD=16

#LD_LIB_PATH should not be needed, ideally
#export LD_LIBRARY_PATH=$(HOME)/local/src/power/rapl/libmsr/lib:LD_LIBRARY_PATH

 for pkg in 0x38198 0x038208 0x038280 0x0382f8
       do
               export MSR_PKG_POWER_LIMIT=${pkg}
#               for dram in 0x038078 0x0380a0 0x0380c8 0x0380f0
#		do
#                    export MSR_DRAM_POWER_LIMIT=${dram}
		    #Run CG with 16 nodes, with 4,8,16 cores/node
		    sh ./runSphot.sh 4 4 4 16
#		done
	done

#Resetting is done by the top-level script
