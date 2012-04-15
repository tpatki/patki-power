#include "irs.h"
#include "irslag.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void getnm2d0( double *nmass, Domain_t *domain )
{
   char *me = "getnm2d0";
   int i, nsld, offn, offt, offnt ;
   int *ndx ;
   double dm ;
   double myflops = 0.0 ;
   double *n1, *n2, *n3, *n4 ;
   double *mnodet, *mnodeb ;
   FT_INITIALIZE(me, domain->hash)
   setphony( domain->area, ptiny, domain ) ;
   for ( i = 0 ; i < domain->nnodes ; i++ ) {
      nmass[i] = 0.0 ;
   }
   NDSET2D(nmass,n1,n2,n3,n4) ;
   for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
      dm = 0.25 * domain->den[i] * domain->area[i] ;
      n1[i] += dm ;
      n2[i] += dm ;
      n3[i] += dm ;
      n4[i] += dm ;
   }
   myflops += 6.0 * ( domain->lrz - domain->frz + 1 ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
