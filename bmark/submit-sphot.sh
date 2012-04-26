#!/bin/bash

cd ./sphot_v1.0/scripts
echo `pwd`

msub sphot-4-node.msub
msub sphot-8-node.msub
msub sphot-16-node.msub
msub sphot-32-node.msub
