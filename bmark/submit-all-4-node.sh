#!/bin/bash

cd ./NAS/BT/scripts
#echo `pwd`

#msub bt-4-node.msub

cd ../../CG/scripts
echo `pwd`

msub cg-4-node.msub

cd ../../EP/scripts
echo `pwd`

msub ep-4-node.msub

cd ../../FT/scripts
echo `pwd`

msub ft-4-node.msub

cd ../../LU/scripts
echo `pwd`

msub lu-4-node.msub

cd ../../MG/scripts
echo `pwd`

msub mg-4-node.msub

#cd ../../SP/scripts
#echo `pwd`

#msub sp-4-node.msub

cd ../../../sweep/sweep3d-2.2b/scripts
echo `pwd`

msub sweep-4-node.msub

cd ../../../sphot_v1.0/scripts
echo `pwd`

msub sphot-4-node.msub

