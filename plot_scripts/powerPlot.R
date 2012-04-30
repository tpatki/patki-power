#!/usr/bin/env Rscript

args <- commandArgs(trailingOnly = TRUE)
a = read.table(args[1], header=T);

# get unique node counts

# get unique task counts

# plot total energy vs node and task count

pkgLimit = sort(unique(a$pkg.clamp.0), decreasing = T)[3]

a$avgNodePower = rowSums(a[, c('avg.pkg.0','avg.pkg.1','avg.dram.0','avg.dram.1')])
a$coresPerNode = a$cores / a$nodes

sel = which(a$pkg.clamp.0 == pkgLimit)
coresPerNode = unique(a[sel, 'coresPerNode'])
colors = rainbow(length(coresPerNode))

#plot(1:length(colors), col=colors)

sel1 = intersect(sel, which(a$coresPerNode == coresPerNode[1]))

a$totalPower = a$avgNodePower * a$nodes

plot(a$nodes[sel1],
     a$totalPower[sel1], 
     main='total power vs nodes',
     xlab='nodes',
     ylab='total power (watts)',
     xaxt='n',
     log='x',
     col=colors[1],
     xlim=range(a$nodes[sel]),
     ylim=c(0, max(a$totalPower[sel]))
     )
axis(1, at=unique(a$nodes[sel]))

legend(x='bottomleft', legend=paste(coresPerNode, 'cores/node'),
       col=colors, lty=1)

for(i in 2:length(coresPerNode)){
  sel1 = intersect(sel, which(a$coresPerNode == coresPerNode[i]))
  points(a$nodes[sel1],
         a$totalPower[sel1], 
         xaxt='n',
         col=colors[i]
         )
}

