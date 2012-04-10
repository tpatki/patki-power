#!/bin/bash

#mkdir bin

#nprocs must be square

make bt CLASS=C NPROCS=1
make bt CLASS=C NPROCS=4
make bt CLASS=C NPROCS=16
make bt CLASS=C NPROCS=36
make bt CLASS=C NPROCS=64
make bt CLASS=C NPROCS=121
make bt CLASS=C NPROCS=256
make bt CLASS=C NPROCS=529
make bt CLASS=C NPROCS=1024
make bt CLASS=C NPROCS=2025

