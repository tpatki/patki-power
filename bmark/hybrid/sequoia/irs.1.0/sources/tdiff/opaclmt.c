#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void opaclmt( double *kros, double kroslmt, int *ndx, int n, Domain_t *domain)
{
   char *me = "opaclmt";
   int i ;
   double f,x,alpha,beta ;
   double myflops = 0.0;  
   FT_INITIALIZE(me, domain->hash)
   alpha = 0.566267049 ;
   beta  = 3.01316495 ;
   for ( i = 0 ; i < n ; i++ )
   {
      x = kroslmt/kros[ndx[i]] ;
      f = (1. + x*(beta + x*alpha))/( 1. + alpha*x) ;
      kros[ndx[i]] *= f ;  
   }
   myflops += 14.*n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
