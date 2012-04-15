#include "irs.h"
#include "irsbndry.h"
int vsamein0(int len, int *ndx, int ibc, Domain_t *domain ) {
   char *me = "vsamein0";
   int error;
   int i,j;
   int id;
   int n1,n2,n3;
   int i1,i2;
   int j1,j2;
   int k1,k2;
   int imin, imax;
   int jmin, jmax;
   int kmin, kmax;
   int ip,jp;
   int base;
   int ind;
   int count;
   int flag1,flag2;
   double dist;
   double dx;
   double dy;
   double dz;
   char op[MAXWORD];
   error = 0 ;
   if (ndims == 2) {
      domain->bc[ibc].ngrp = 1;
      domain->bc[ibc].lgrp = domain->bc[ibc].len;
   } else {
      n1 = ndx[0];
      n2 = ndx[len-1];
      k1 = n1 / domain->kp ;
      j1 = (n1 - k1 * domain->kp) / domain->jp ;
      i1 =  n1 - k1 * domain->kp - j1 * domain->jp ;
      k2 = n2 / domain->kp ;
      j2 = (n2 - k2 * domain->kp) / domain->jp ;
      i2 =  n2 - k2 * domain->kp - j2 * domain->jp ;
      kmax = MAX(k1,k2);
      kmin = MIN(k1,k2);
      jmax = MAX(j1,j2);
      jmin = MIN(j1,j2);
      imax = MAX(i1,i2);
      imin = MIN(i1,i2);
      if ((imax == imin) && (jmax != jmin) && (kmax != kmin)) {
         n1 = imin + domain->jp*jmin + domain->kp*kmin;
         n2 = imin + domain->jp*jmax + domain->kp*kmin;
         n3 = imin + domain->jp*jmin + domain->kp*kmax;
         base = imin;   
         i1 = jmin;
         i2 = jmax;
         ip = domain->jp;
         j1 = kmin;
         j2 = kmax;
         jp = domain->kp;
      } else if ((imax != imin) && (jmax == jmin) && (kmax != kmin)) {
         n1 = imin + domain->jp*jmin + domain->kp*kmin;
         n2 = imax + domain->jp*jmin + domain->kp*kmin;
         n3 = imin + domain->jp*jmin + domain->kp*kmax;
         base = jmin*domain->jp;
         i1 = imin;
         i2 = imax;
         ip = 1;
         j1 = kmin;
         j2 = kmax;
         jp = domain->kp;
      } else if ((imax != imin) && (jmax != jmin) && (kmax == kmin)) {
         base = domain->kp*kmin;
         n1 = imin + domain->jp*jmin + domain->kp*kmin;
         n2 = imax + domain->jp*jmin + domain->kp*kmin;
         n3 = imin + domain->jp*jmax + domain->kp*kmin;
         base = domain->kp*kmin;
         i1 = imin;
         i2 = imax;
         ip = 1;
         j1 = jmin;
         j2 = jmax;
         jp = domain->jp;
      } else {
         ctlnotice(me,"vsame only works on boundaries which are degenerate in at least one direction");
         error = 1;
         return(error);
      } 
      flag1  = 0;
      flag2  = 0;
      dx = domain->x[n1] - domain->x[n2];
      dy = domain->y[n1] - domain->y[n2];
      dz = domain->z[n1] - domain->z[n2];
      dist = sqrt(dx*dx + dy*dy + dz*dz);
      if (dist < xcut ) {
         flag1 = 1;
      } 
      dx = domain->x[n1] - domain->x[n3];
      dy = domain->y[n1] - domain->y[n3];
      dz = domain->z[n1] - domain->z[n3];
      dist = sqrt(dx*dx + dy*dy + dz*dz);
      if (dist < xcut ) {
         flag2 = 1;
      } 
      count = 0;
      if ((flag1 == 1) && (flag2 == 0)) {
          for (j = j1; j <= j2; j++) {
             for (i = i1; i <= i2; i++) {
                ind = base + i*ip + j*jp;
                ndx[count] = ind;
                count++;
             }
          }
          domain->bc[ibc].ngrp = j2 - j1 + 1;
          domain->bc[ibc].lgrp = i2 - i1 + 1;
          getbcname(op,ibc,domain);
          bcin0(len,ndx,ibc,op,domain);
      } else if ((flag1 == 0) && (flag2 == 1)) {
          for (i = i1; i <= i2; i++) {
             for (j = j1; j <= j2; j++) {
                ind = base + i*ip + j*jp;
                ndx[count] = ind;
                count++;
             }
          }
          domain->bc[ibc].ngrp = i2 - i1 + 1;
          domain->bc[ibc].lgrp = j2 - j1 + 1;
          getbcname(op,ibc,domain);
          bcin0(len,ndx,ibc,op,domain);
      } else if ((flag1 == 1) && (flag2 == 1)) {
          domain->bc[ibc].ngrp = 1;
          domain->bc[ibc].lgrp = len;
      } else {
         ctlnotice(me,"vsame only works on boundaries which are degenerate in at least one direction");
         error = 1;
         return(error);
      } 
   } 
   id = 1;
   for (i = 0; i < domain->nbc; i++){
      if (domain->bc[i].id>0) {
          id = domain->bc[i].id + 1;
      }
   }
   domain->bc[ibc].id = id;
   return(error) ;
}
