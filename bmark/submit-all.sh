#!/bin/bash

cd ./NAS/BT/scripts

msub bt-16-node.msub
msub bt-32-node.msub
msub bt-64-node.msub
msub bt-128-node.msub

cd ../../CG/scripts

msub cg-16-node.msub
msub cg-32-node.msub
msub cg-64-node.msub
msub cg-128-node.msub

cd ../../EP/scripts

msub ep-16-node.msub
msub ep-32-node.msub
msub ep-64-node.msub
msub ep-128-node.msub

cd ../../FT/scripts

msub ft-16-node.msub
msub ft-32-node.msub
msub ft-64-node.msub
msub ft-128-node.msub

cd ../../LU/scripts

msub lu-16-node.msub
msub lu-32-node.msub
msub lu-64-node.msub
msub lu-128-node.msub

cd ../../MG/scripts

msub mg-16-node.msub
msub mg-32-node.msub
msub mg-64-node.msub
msub mg-128-node.msub

cd ../../SP/scripts

msub sp-16-node.msub
msub sp-32-node.msub
msub sp-64-node.msub
msub sp-128-node.msub

cd ../../../sweep/sweep3d-2.2b/scripts

msub sweep-16-node.msub
msub sweep-32-node.msub
msub sweep-64-node.msub
msub sweep-128-node.msub

cd ../../../sphot_v1.0/scripts

msub sphot-16-node.msub
msub sphot-32-node.msub
msub sphot-64-node.msub
msub sphot-128-node.msub

