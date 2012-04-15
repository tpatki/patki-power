#include "irs.h"
#include "irstdiff.h"
#include "irscom.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rmatmult2( Domain_t *domain, RadiationData_t *rblk, double *x, double *y )
{
   char *me = "rmatmult2" ;
   int i, ii, jj ;
   int imin = domain->imin ;
   int imax = domain->imax ;
   int jmin = domain->jmin ;
   int jmax = domain->jmax ;
   int jp   = domain->jp   ;
   double *cbl = rblk->cbl ;
   double *cbc = rblk->cbc ;
   double *cbr = rblk->cbr ;
   double *ccl = rblk->ccl ;
   double *ccc = rblk->ccc ;
   double *ccr = rblk->ccr ;
   double *cfl = rblk->cfl ;
   double *cfc = rblk->cfc ;
   double *cfr = rblk->cfr ;
   double *xcbl = x - jp - 1 ;
   double *xcbc = x - jp     ;
   double *xcbr = x - jp + 1 ;
   double *xccl = x      - 1 ;
   double *xccc = x          ;
   double *xccr = x      + 1 ;
   double *xcfl = x + jp - 1 ;
   double *xcfc = x + jp     ;
   double *xcfr = x + jp + 1 ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   for ( jj = jmin ; jj < jmax ; jj++ ) {
      for ( ii = imin ; ii < imax ; ii++ ) {
	 i = ii + jj * jp ;
         y[i] = cbl[i] * xcbl[i] + cbc[i] * xcbc[i] + cbr[i] * xcbr[i] +
                ccl[i] * xccl[i] + ccc[i] * xccc[i] + ccr[i] * xccr[i] +
                cfl[i] * xcfl[i] + cfc[i] * xcfc[i] + cfr[i] * xcfr[i] ;
      }
   }
   myflops += 17.0 * ( imax - imin ) * ( jmax - jmin ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
