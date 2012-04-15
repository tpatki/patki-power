#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void reicouple( double *rate, double *den, double *tmat, int    *ndx, int n,
                double *zstar, double *abar, double *mu, double eimlt,
                double dtrad, Domain_t *domain )
{
   char *me = "reicouple";
   int i ;
   double fact, factor, lambdasq, loglam, te, d, z, za, esq, zsq ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   esq  = exp( 2.00001 ) ;
   fact = eimlt * 1.911151e7 * dtrad ;
   for ( i = 0 ; i < n ; i++ ) {
      z      = MAX( 0.01, zstar[i] ) ;
      za     = z / ( abar[i] + ptiny ) ;
      zsq    = z * z ;
      factor = fact * za ;
      d = MAX( den[i], 1.0e-6 ) ;
      te = MAX( tmat[ndx[i]], tfloor ) ;
      lambdasq = 1.555e4 * te * te * te /
                 ( d * za * ( 0.04319 * zsq + te ) + ptiny ) ;
      loglam   = 0.5 * log( esq + lambdasq ) ;
      loglam   = MAX( loglam, 1.0 ) ;
      rate[i]  = factor * loglam / ( 1.0 + exp(-mu[i] / te) ) ;
   }
   myflops += 48.0 * n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
