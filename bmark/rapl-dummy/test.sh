#!/bin/bash

cat rzmerl* | grep ZZZ | cut -d " " -f 2 > .elapsed

cat rzmerl* | grep ZZZ | cut -d " " -f 3 > .PKG_W_0
cat rzmerl* | grep ZZZ | cut -d " " -f 4 > .PP0_W_0
cat rzmerl* | grep ZZZ | cut -d " " -f 5 > .DRAM_W_0

cat rzmerl* | grep ZZZ | cut -d " " -f 60 > .PKG_W_1
cat rzmerl* | grep ZZZ | cut -d " " -f 61 > .PP0_W_1
cat rzmerl* | grep ZZZ | cut -d " " -f 62 > .DRAM_W_1

paste -d ' ' .elapsed .PKG_W_0 .PP0_W_0 .DRAM_W_0 .PKG_W_1 .PP0_W_1 .DRAM_W_1 > .node_data
sed '1 i elapsed PKG_W_0 PP0_W_0 DRAM_W_0 PKG_W_1 PP0_W_1 DRAM_W_1' .node_data > node_data.R


