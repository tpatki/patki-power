#!/bin/bash

# Make sure we are using mvapich2 of the gnu persuasion.
#source /usr/local/tools/dotkit/init.sh
#use mvapich2-gnu-debug

#export MAGIC=source /usr/local/tools/dotkit/init.sh && use ic-12.1.273 && use mvapich2-intel-1.7
#$MAGIC && which icc
#source /usr/local/tools/dotkit/init.sh && use ic-12.1.273 && use mvapich2-intel-1.7 && which icc
#




cd ../rapl/libmsr/
make clean
make > makeMSR.out 2>&1
git add makeMSR.out
git commit -a -m "Just made msr common "

cd ./mpi/
make clean
make  > makeRAPL.out 2>&1
git add makeRAPL.out
git commit -a -m "Just made Librapl"

cd ../../../bmark

cd rapl-dummy/
make clean
make > makeDummy.out 2>&1
git add makeDummy.out
git commit -a -m "Just made rapl-dummy with RAPL"

cd ..

mkdir ./NAS/bin
cd ./NAS/
make clean
sh makeCG.sh > makeCG.out 2>&1
git add makeCG.out
git commit -a -m "Just made CG with RAPL"

sh makeBT.sh > makeBT.out 2>&1
git add makeBT.out
git commit -a -m "Just made BT with RAPL"

sh makeDT.sh > makeDT.out 2>&1
git add makeDT.out
git commit -a -m "Just made DT with RAPL"

sh makeEP.sh > makeEP.out 2>&1
git add makeEP.out
git commit -a -m "Just made EP with RAPL"

sh makeFT.sh > makeFT.out 2>&1
git add makeFT.out
git commit -a -m "Just made FT with RAPL"

sh makeIS.sh > makeIS.out 2>&1
git add makeIS.out
git commit -a -m "Just made IS with RAPL"

sh makeLU.sh > makeLU.out 2>&1
git add makeLU.out
git commit -a -m "Just made LU with RAPL"

sh makeMG.sh > makeMG.out 2>&1
git add makeMG.out
git commit -a -m "Just made MG with RAPL"

sh makeSP.sh > makeSP.out 2>&1
git add makeSP.out
git commit -a -m "Just made SP with RAPL"

cd ../sweep/sweep3d-2.2b/
sh makeSweep.sh > makeSweep.out 2>&1
git add makeSweep.out
git commit -a -m "Just made sweep with RAPL"

cd ../../sphot_v1.0/
make >makeSphot.out 2>&1
git add makeSphot.out
git commit -a -m "Just made Sphot with RAPL"

cd ../

#cd ./cg/scripts
#msub cg-experiment.sh
#git add .
#git commit -a -m "Data commit"


#cd ../../sweep/sweep3d-2.2b/scripts
#msub sweep-experiment.sh
#git add .
#git commit -a -m "Data commit"

