#!/bin/bash

#mkdir bin

make mg CLASS=D NPROCS=8
make mg CLASS=D NPROCS=16
make mg CLASS=D NPROCS=32
make mg CLASS=D NPROCS=64
make mg CLASS=D NPROCS=128
make mg CLASS=D NPROCS=256
make mg CLASS=D NPROCS=512
make mg CLASS=D NPROCS=1024
make mg CLASS=D NPROCS=2048
