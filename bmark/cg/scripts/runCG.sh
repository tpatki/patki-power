#!/bin/bash

#Assumes powers of two for number of nodes.

#$1: minimum number of nodes (32)
#$2: maximum number of nodes (128)
#$3: minumum number of cores per node (1)
#$4: number of cores per node (16)

i=$1

while [ $i -le $2 ]
do
  j=$3
  while [ $j -le $4 ]
  do
      echo "nodes=$i ntasks=$(($i * $j))"
      ./runCL.sh $i $(($i * $j))
      j=$(( $j * 2))
  done
  i=$(($i*2))
done

