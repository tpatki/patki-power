#!/bin/bash

#mkdir bin

make ep CLASS=D NPROCS=1
make ep CLASS=D NPROCS=2
make ep CLASS=D NPROCS=4
make ep CLASS=D NPROCS=8
make ep CLASS=D NPROCS=16
make ep CLASS=D NPROCS=32
make ep CLASS=D NPROCS=64
make ep CLASS=D NPROCS=128
make ep CLASS=D NPROCS=256
make ep CLASS=D NPROCS=512
make ep CLASS=D NPROCS=1024
make ep CLASS=D NPROCS=2048
