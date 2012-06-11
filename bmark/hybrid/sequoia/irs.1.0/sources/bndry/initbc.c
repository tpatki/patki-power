#include "irs.h"
#include "irsbndry.h"
void initbc( Domain_t *domain )
{
   int ibc  ;
   int len  ;
   int len2 ;
   int i    ;
   int stride;
   int i1,i2;
   int j1,j2;
   int k1,k2;
   int n1,n2;
   int flag1,flag2;
   int *ndx;
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
      ndx = domain->bc[ibc].ndx;
      len = domain->bc[ibc].len;
      if (ndims == 2) {
         n1 = ndx[0] ;
         n2 = ndx[len-1] ;
         j1 = n1 / domain->jp ;
         i1 = n1 - j1 * domain->jp ;
         j2 = n2 / domain->jp ;
         i2 = n2 - j2 * domain->jp ;
         if ((i1 == i2) & (j1 != j2)) stride = 1 ;
         if ((i1 != i2) & (j1 == j2)) stride = domain->jp ;
      } else {
         n1 = ndx[0] ;
         n2 = ndx[len-1] ;
         k1 = n1 / domain->kp ;
         j1 = (n1 - k1 * domain->kp) / domain->jp ;
         i1 =  n1 - k1 * domain->kp - j1 * domain->jp ;
         k2 = n2 / domain->kp ;
         j2 = (n2 - k2 * domain->kp) / domain->jp ;
         i2 =  n2 - k2 * domain->kp - j2 * domain->jp ;
         if ((i1 == i2) & (j1 != j2) & (k1 != k2)) stride = 1 ;
         if ((i1 != i2) & (j1 == j2) & (k1 != k2)) stride = domain->jp ;
         if ((i1 != i2) & (j1 != j2) & (k1 == k2)) stride = domain->kp ;
      }
      domain->bc[ibc].pn = stride;
      flag1 = 1 ;
      flag2 = 1 ;
      len2 = len - 1 ;
      if (len2 < 2) len2 = 2 ;
      for ( i = 1 ; i < len2 ; i++ ) {
         i1 = ndx[i] + stride ;
         i2 = ndx[i] - stride ;
         if (domain->node[i1] == 0) flag1 = 0 ;
         if (domain->node[i2] == 0) flag2 = 0 ;
      }
      if (flag1 == 1) {
         domain->bc[ibc].pn = -stride ;
         domain->bc[ibc].rz = 0 ;
         domain->bc[ibc].pz = -stride ;
      } else if (flag2 == 1) {
         domain->bc[ibc].pn = stride ;
         domain->bc[ibc].pz = 0 ;
         domain->bc[ibc].rz = -stride ;
      }
   }
   for (ibc = 0; ibc < domain->nbnd; ibc++) {
      ndx = domain->bnd[ibc].ndx_send;
      len = domain->bnd[ibc].len_nsend1;
      stride = 0;
      if (len == 0) continue;
      if (ndims == 2) {
         n1 = ndx[0] ;
         n2 = ndx[len-1] ;
         j1 = n1 / domain->jp ;
         i1 = n1 - j1 * domain->jp ;
         j2 = n2 / domain->jp ;
         i2 = n2 - j2 * domain->jp ;
         if ((i1 == i2) & (j1 != j2)) stride = 1 ;
         if ((i1 != i2) & (j1 == j2)) stride = domain->jp ;
      } else {
         n1 = ndx[0] ;
         n2 = ndx[len-1] ;
         k1 = n1 / domain->kp ;
         j1 = (n1 - k1 * domain->kp) / domain->jp ;
         i1 =  n1 - k1 * domain->kp - j1 * domain->jp ;
         k2 = n2 / domain->kp ;
         j2 = (n2 - k2 * domain->kp) / domain->jp ;
         i2 =  n2 - k2 * domain->kp - j2 * domain->jp ;
         if ((i1 == i2) & (j1 != j2) & (k1 != k2)) stride = 1 ;
         if ((i1 != i2) & (j1 == j2) & (k1 != k2)) stride = domain->jp ;
         if ((i1 != i2) & (j1 != j2) & (k1 == k2)) stride = domain->kp ;
      }
      if (stride != 0) {
         domain->bnd[ibc].pn = stride;
         flag1 = 1 ;
         flag2 = 1 ;
         len2 = len - 1 ;
         if (len2 < 2) len2 = 2 ;
         for ( i = 1 ; i < len2 ; i++ ) {
            i1 = ndx[i] + stride ;
            i2 = ndx[i] - stride ;
            if (domain->node[i1] == 0) flag1 = 0 ;
            if (domain->node[i2] == 0) flag2 = 0 ;
         }
         if (flag1 == 1) {
            domain->bnd[ibc].pn = -stride ;
            domain->bnd[ibc].rz = 0 ;
            domain->bnd[ibc].pz = -stride ;
         } else if (flag2 == 1) {
            domain->bnd[ibc].pn = stride ;
            domain->bnd[ibc].pz = 0 ;
            domain->bnd[ibc].rz = -stride ;
         }
      }
   }
}
