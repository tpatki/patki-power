#include "irs.h"
#include "irslag.h"
#include "FunctionTimer.h"
void getnm3d( double *nmass, Domain_t *domain ) {
   char *me = "getnm3d";
   int i, ii, jj, off, nsld, offn, offt1, offt2, offt12 ;
   int min1, min2, max1, max2 ;
   int *ndx ;
   double dm ;
   double myflops = 0.0 ;
   double *n1,*n2,*n3,*n4,*n5,*n6,*n7,*n8 ;
   double *mnodet, *mnodeb, *zmassn ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->nnodes ; i++ ) {
      domain->nmass[i] = 0.0 ;
   }
   NDSET3D(nmass,n1,n2,n3,n4,n5,n6,n7,n8) ;
   for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
      dm     = 0.125 * domain->zmass[i] ;
      n1[i] += dm ;
      n2[i] += dm ;
      n3[i] += dm ;
      n4[i] += dm ;
      n5[i] += dm ;
      n6[i] += dm ;
      n7[i] += dm ;
      n8[i] += dm ;
   }
   myflops += 9.0 * ( domain->lrz - domain->frz + 1 ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
