#!/usr/bin/env Rscript
args <- commandArgs(trailingOnly = TRUE)
for(i in args){
a = read.table(i, header=T);
x <- c(mean(a$elapsed),
       mean(a$PKG_W_0),
       mean(a$PP0_W_0),
       mean(a$DRAM_W_0),
       mean(a$PKG_W_1),
       mean(a$PP0_W_1),
       mean(a$DRAM_W_1),
       sum(a$PKG_W_0),
       sum(a$PP0_W_0),
       sum(a$DRAM_W_0),
       sum(a$PKG_W_1),
       sum(a$PP0_W_1),
       sum(a$DRAM_W_1))
write.table(t(x), "", col.names=FALSE, row.names=FALSE)
}
