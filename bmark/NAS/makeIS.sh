#!/bin/bash

#mkdir bin

make is CLASS=C NPROCS=4
make is CLASS=C NPROCS=8
make is CLASS=C NPROCS=16
make is CLASS=C NPROCS=32
make is CLASS=C NPROCS=64
make is CLASS=C NPROCS=128
make is CLASS=C NPROCS=256
make is CLASS=C NPROCS=512
make is CLASS=C NPROCS=1024
make is CLASS=C NPROCS=2048
