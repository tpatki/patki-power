#!/bin/bash

mkdir ./cg/bin
cd ./cg
sh makeCG.sh

cd ..

cd ./sweep/sweep3d-2.2b
sh makeSweep.sh

cd ../..

cd ./cg/scripts
msub cg-experiment.sh
git add .
git commit -a


cd ../../sweep/sweep3d-2.2b/scripts
msub sweep-experiment.sh
git add .
git commit -a
