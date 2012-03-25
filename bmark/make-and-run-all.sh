#!/bin/bash

# Make sure we are using mvapich2 of the gnu persuasion.
source /usr/local/tools/dotkit/init.sh
use mvapich2-gnu-debug

mkdir ./cg/bin
cd ./cg
sh makeCG.sh > makeCG.out 2>&1
git commmit -a -m "Just made CG"

cd ..

cd ./sweep/sweep3d-2.2b
sh makeSweep.sh > makeSweep.out 2>&1
git commmit -a -m "Just made Sweep"

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

