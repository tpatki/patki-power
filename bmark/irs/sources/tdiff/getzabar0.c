#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void getzabar0( double *zbar, double *abar, double *wgt, int ir,
                Domain_t *domain )
{
   char *me = "getzabar0";
   int i, n ;
   double myflops = 0.0;   
   FT_INITIALIZE(me, domain->hash)
   n = domain->rlen[ir] ;
   for ( i = 0 ; i < n ; i++ ) {
      zbar[i] = reg[ir].eosGroup[0].zbar ;
      abar[i] = reg[ir].eosGroup[0].abar ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
