#!/bin/bash

#export IRS_DIR=/home/tpatki/tapasya/test-p/patki-power/bmark/irs
export IRS_DIR=$HOME/local/src/power/bmark/irs

../scripts/irs_build irs-build $IRS_DIR
cd $IRS_DIR/patki/irs-build/build
../../../scripts/irs_config chaos_3_x86_64
make depend
make

