#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "irscom.h"
double norml2( Domain_t *domain,   double *x )
{
   char *me = "norml2";
   double norm ;
   int i ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   norm = 0. ;
   for ( i = domain->frz ; i <= domain->lrz ; i++ )
   {
      norm += x[i]*x[i] ;
   }
   myflops += 2.*(domain->lrz - domain->frz + 1) ;
   FT_FINALIZE(me, domain->hash, myflops)
   return ( norm ) ;
}
