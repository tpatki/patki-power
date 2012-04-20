#!/usr/bin/env Rscript

args <- commandArgs(trailingOnly = TRUE)
a = read.table(args[1], header=T);

# get unique node counts

# get unique task counts

# plot total energy vs node and task count

pkgLimit = sort(unique(a$pkg.clamp.0), decreasing = T)[1]

a$avgNodePower = rowSums(a[, c('avg.pkg.0','avg.pkg.1','avg.dram.0','avg.dram.1')])
a$coresPerNode = a$cores / a$nodes

sel = which(a$pkg.clamp.0 == pkgLimit)
coresPerNode = unique(a[sel, 'coresPerNode'])
sel1 = intersect(sel, which(a$coresPerNode == coresPerNode[1]))

totalEnergy = a$avgNodePower[sel]*a$nodes[sel]*a$avg.time[sel]
plot(a$cores[sel], totalEnergy, 
		    main='total energy vs nodes & cores',
#		    sub=paste(coresPerNode[1], 'cores per node'),
		    xlab='cores',
		    ylab='log total energy (joules)',
		    log='y',
		    ylim=c(1,10*max(totalEnergy)))
