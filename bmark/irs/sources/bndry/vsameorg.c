#include "irs.h"
#include "irsbndry.h"
#include "BlockMapping.h"
void vsameorg( void ) {
   int ibc;
   int iblk;
   int idmax;
   int idc;
   int id;
   int i,j;
   int n1,n2;
   int i1,i2;
   int j1,j2;
   int k1,k2;
   int gblk;
   int lgrp;
   int ngrp;
   int count;
   int *blks;
   int *blk;
   int *bc;
   int *match;
   int *newid;
   int *imax;
   int *imin;
   int *ndx;
   blks = ALLOT(int,nbcx);
   for (ibc = 0; ibc  < nbcx; ibc++ ) {
      blks[ibc] = 0;
   }
   idmax = 0;
   for (iblk = 0; iblk < nblk; iblk++) {
      for (ibc = 0; ibc < domains[iblk].nbc; ibc++) {
         if (domains[iblk].bc[ibc].id > 0) {
            if (domains[iblk].bc[ibc].id > idmax) idmax = domains[iblk].bc[ibc].id;
            blks[domains[iblk].bc[ibc].id]++;
         }
      }
   }
   idc = idmax;
   for (id = 1 ; id <= idmax; id++) {
      imax = ALLOT(int,blks[id]);
      imin = ALLOT(int,blks[id]);
      blk  = ALLOT(int,blks[id]);
      bc  = ALLOT(int,blks[id]);
      newid  = ALLOT(int,blks[id]);
      match  = ALLOT(int,blks[id]);
      count = 0;
      for (iblk = 0; iblk < nblk; iblk++) {
         gblk = domains[iblk].gblk;
         for (ibc = 0; ibc < domains[iblk].nbc; ibc++) {
            if (domains[iblk].bc[ibc].id == id) {
               blk[count] = iblk;
               bc[count] = ibc;
               newid[count] = id;
               ngrp = domains[iblk].bc[ibc].ngrp;
               lgrp = domains[iblk].bc[ibc].lgrp;
               ndx = domains[iblk].bc[ibc].ndx;
               imax[count] = -1;
               imin[count] = -1;
               match[count] = -1;
               if ((ngrp > 1)&&(ndims == 3)) {
                  n1 = ndx[0];
                  n2 = ndx[(ngrp-1)*lgrp];
                  NDXEXT3D(n1,i1,j1,k1,domains[iblk]);
                  NDXEXT3D(n2,i2,j2,k2,domains[iblk]);
                  if ((i1 != i2) && (j1 == j2) && (k1 == k2 )) {
                     imax[count] = MAX(i1,i2)+gmap[gblk].imin; 
                     imin[count] = MIN(i1,i2)+gmap[gblk].imin; 
                  } else if ((i1 == i2) && (j1 != j2) && (k1 == k2 )) {
                     imax[count] = MAX(j1,j2)+gmap[gblk].jmin; 
                     imin[count] = MIN(j1,j2)+gmap[gblk].jmin; 
                  } else if ((i1 == i2) && (j1 == j2) && (k1 != k2 )) {
                     imax[count] = MAX(k1,k2)+gmap[gblk].kmin; 
                     imin[count] = MIN(k1,k2)+gmap[gblk].kmin; 
                  }
               } 
               count++;
            }
         }
      }
      i = 0;
      while (i < count ) {
         match[i] = 1;
         for (j = i+1 ; j < count; j++) {
            if ((imax[i] == imax[j]) && (imin[i] == imin[j])) {
               match[j] = 1;
               newid[j] = newid[i];
            }
         }
         for (j = i+1 ; j < count; j++) {
            if (match[j] < 0) {
               idc++;
               newid[j] = idc;
               break;
            }
         }
         i = j;
      }
      for (i = 0; i < count; i++) {
         iblk = blk[i];
         ibc = bc[i];
         domains[iblk].bc[ibc].id = newid[i];
      }
      FREEMEM(imax);
      FREEMEM(imin);
      FREEMEM(blk);
      FREEMEM(bc);
      FREEMEM(newid);
      FREEMEM(match);
   }
   vsame_max_id = idc;
   FREEMEM(blks);
   return;
}
