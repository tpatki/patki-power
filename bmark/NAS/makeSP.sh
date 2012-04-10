#!/bin/bash

#mkdir bin

#nprocs must be square

make sp CLASS=C NPROCS=1
make sp CLASS=C NPROCS=4
make sp CLASS=C NPROCS=16
make sp CLASS=C NPROCS=36
make sp CLASS=C NPROCS=64
make sp CLASS=C NPROCS=121
make sp CLASS=C NPROCS=256
make sp CLASS=C NPROCS=529
make sp CLASS=C NPROCS=1024
make sp CLASS=C NPROCS=2025

