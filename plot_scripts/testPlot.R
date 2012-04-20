#!/usr/bin/env Rscript

args <- commandArgs(trailingOnly = TRUE)
a = read.table(args[1], header=T);

# get unique node counts

# get unique task counts

# plot total energy vs node and task count

pkgLimit = sort(unique(a$pkg.clamp.0), decreasing = T)[1]

a$avgNodePower = rowSums(a[, c('avg.pkg.0','avg.pkg.1','avg.dram.0','avg.dram.1')])

sel = which(a$pkg.clamp.0 == pkgLimit)

plot(a$cores[sel], a$avgNodePower[sel])
