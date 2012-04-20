#!/usr/bin/env Rscript

args <- commandArgs(trailingOnly = TRUE)
a = read.table(args[1], header=T);

# get unique node counts

# get unique task counts

# plot total energy vs node and task count

pkgLimit = sort(unique(a$pkg.clamp.0), decreasing = T)[1]
