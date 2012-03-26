#!/bin/bash
#setenv F77 mpif77
#export $F77=mpif77
#sh ./configure
./configure F77="mpif77" LIBS="-L/usr/lib64/slurm" LDFLAGS="-lpmi"
make
