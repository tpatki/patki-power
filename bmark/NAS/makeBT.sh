#!/bin/bash

#mkdir bin

#nprocs must be square

make bt CLASS=D NPROCS=1
make bt CLASS=D NPROCS=4
make bt CLASS=D NPROCS=16
make bt CLASS=D NPROCS=36
make bt CLASS=D NPROCS=64
make bt CLASS=D NPROCS=121
make bt CLASS=D NPROCS=256
make bt CLASS=D NPROCS=529
make bt CLASS=D NPROCS=1024
make bt CLASS=D NPROCS=2025

