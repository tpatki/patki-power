#!/bin/bash

# Make sure we are using mvapich2 of the gnu persuasion.
#source /usr/local/tools/dotkit/init.sh
#use mvapich2-gnu-debug

#export MAGIC=source /usr/local/tools/dotkit/init.sh && use ic-12.1.273 && use mvapich2-intel-1.7
#$MAGIC && which icc
#source /usr/local/tools/dotkit/init.sh && use ic-12.1.273 && use mvapich2-intel-1.7 && which icc
#

mkdir ./cg/bin
cd ./cg

sh makeCG.sh > makeCG.out 2>&1
git commit -a -m "Just made CG"

cd ..

#cd ./sweep/sweep3d-2.2b
#sh makeSweep.sh > makeSweep.out 2>&1
#git commit -a -m "Just made Sweep"

#cd ../..
#
#cd ./cg/scripts
#msub cg-experiment.sh
#git add .
#git commit -a -m "Data commit"
#
#
#cd ../../sweep/sweep3d-2.2b/scripts
#msub sweep-experiment.sh
#git add .
#git commit -a -m "Data commit"

