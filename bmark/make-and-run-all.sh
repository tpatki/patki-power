#!/bin/bash

mkdir ./cg/bin
cd ./cg
sh makeCG.sh > makeCG.out
git commmit -a -m "Just made CG"

cd ..

cd ./sweep/sweep3d-2.2b
sh makeSweep.sh > makeSweep.out
git commmit -a -m "Just made Sweep"

cd ../..

cd ./cg/scripts
msub cg-experiment.sh
git add .
git commit -a -m "Data commit"


cd ../../sweep/sweep3d-2.2b/scripts
msub sweep-experiment.sh
git add .
git commit -a -m "Data commit"
