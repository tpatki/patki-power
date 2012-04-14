#!/bin/bash

#mkdir bin

#nprocs must be square

make sp CLASS=D NPROCS=1
make sp CLASS=D NPROCS=4
make sp CLASS=D NPROCS=16
make sp CLASS=D NPROCS=36
make sp CLASS=D NPROCS=64
make sp CLASS=D NPROCS=121
make sp CLASS=D NPROCS=256
make sp CLASS=D NPROCS=529
make sp CLASS=D NPROCS=1024
make sp CLASS=D NPROCS=2025

