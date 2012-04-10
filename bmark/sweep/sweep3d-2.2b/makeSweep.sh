#!/bin/bash
#setenv F77 mpif77
#export $F77=mpif77
#sh ./configure
#./configure F77="mpif77" LIBS="-L/usr/lib64/slurm" LDFLAGS="-lpmi"

export LD_LIBRARY_PATH=/home/tpatki/tapasya/patki-power/rapl/libmsr/lib:$LD_LIBRARY_PATH
./configure F77="mpif77" LDFLAGS="-L/home/tpatki/tapasya/patki-power/rapl/libmsr/lib" LIBS="-lrapl" --with-mpi
make
