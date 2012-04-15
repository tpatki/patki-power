#!/bin/bash

#export IRS_DIR=/home/tpatki/tapasya/test-p/patki-power/bmark/irs
export IRS_DIR=$HOME/local/src/power/bmark/irs


#Remove the local version if it exists

rm -rf $IRS_DIR/patki/irs-build

irs_build irs-build $IRS_DIR 
cd $IRS_DIR/patki/irs-build/build
irs_config chaos_3_x86_64_wo_silo
make depend
make

