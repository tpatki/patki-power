#include "irs.h"
#include "irseos.h"
#include "FunctionTimer.h"
void etaminchk( double *den, double *p, double *cs2, int *ndx, int n,
                double rho0, double etamin, Domain_t *domain )
{
   char *me = "etaminchk";
   int i ;
   double rr, eta ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   rr = 1.0 / rho0 ;
   for ( i = 0 ; i < n ; i++ ) {
      eta = den[ndx[i]] * rr ;
      if ( eta < etamin ) {
         p[ndx[i]]   = 0.0 ;
         cs2[ndx[i]] = 0.0 ;
      }
   }
   myflops += 1.0 * n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
