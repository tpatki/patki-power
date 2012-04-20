#!/bin/bash


########################
#actual power data -- to be passed on to R
########################


cat $1/rzmerl* | grep ZZZ | cut -d " " -f 2 > .elapsed

cat $1/rzmerl* | grep ZZZ | cut -d " " -f 3 > .PKG_W_0
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 4 > .PP0_W_0
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 5 > .DRAM_W_0

cat $1/rzmerl* | grep ZZZ | cut -d " " -f 60 > .PKG_W_1
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 61 > .PP0_W_1
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 62 > .DRAM_W_1

paste -d ' ' .elapsed .PKG_W_0 .PP0_W_0 .DRAM_W_0 .PKG_W_1 .PP0_W_1 .DRAM_W_1 > .node_data
sed '1 i elapsed PKG_W_0 PP0_W_0 DRAM_W_0 PKG_W_1 PP0_W_1 DRAM_W_1' .node_data > node_data.R.$2


########################
#Clamp and Enable information, just to be sure we're not beating around the bush here.
########################

cat $1/rzmerl* | grep ZZZ | cut -d " " -f 37 > .PKG_C_0
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 36 > .PKG_E_0

cat $1/rzmerl* | grep ZZZ | cut -d " " -f 53 > .DRAM_C_0
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 52 > .DRAM_E_0


cat $1/rzmerl* | grep ZZZ | cut -d " " -f 94 > .PKG_C_1
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 93 > .PKG_E_1

cat $1/rzmerl* | grep ZZZ | cut -d " " -f 110 > .DRAM_C_1
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 109 > .DRAM_E_1

paste -d ' ' .PKG_C_0 .PKG_E_0 .DRAM_C_0 .DRAM_E_0 .PKG_C_1 .PKG_E_1 .DRAM_C_1 .DRAM_E_1 > .en_bits

sed '1 i PKG_C_0 PKG_E_0 DRAM_C_0 DRAM_E_0 PKG_C_1 PKG_E_1 DRAM_C_1 DRAM_E_1' .en_bits > enable_bits


########################
#General Clamp Data
########################

cat $1/rzmerl* | grep ZZZ | cut -d " " -f 43 > .PKG_Lim1_W_0
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 100 > .PKG_Lim1_W_1

cat $1/rzmerl* | grep ZZZ | cut -d " " -f 59 > .DRAM_Lim1_W_0
cat $1/rzmerl* | grep ZZZ | cut -d " " -f 116 > .DRAM_Lim1_W_1

paste -d ' ' .PKG_Lim1_W_0 .PKG_Lim1_W_1 .DRAM_Lim1_W_0 .DRAM_Lim1_W_1 > .c_data

#Don't insert the header so you can just pick this data up and the top level script can add in the header.
#sed '1 i PKG_Lim1_W_0 PKG_Lim1_W_1 DRAM_Lim1_W_0 DRAM_Lim1_W_1' .c_data > clamp_data

#only grab one node, everything else is uniform
head -1 .c_data >> clamp_data

####################

rm .elapsed .PKG_W_0 .PP0_W_0 .DRAM_W_0 .PKG_W_1 .PP0_W_1 .DRAM_W_1 .node_data
rm .PKG_C_0 .PKG_E_0 .DRAM_C_0 .DRAM_E_0 .PKG_C_1 .PKG_E_1 .DRAM_C_1 .DRAM_E_1 .en_bits
rm .PKG_Lim1_W_0 .PKG_Lim1_W_1 .DRAM_Lim1_W_0 .DRAM_Lim1_W_1 .c_data

