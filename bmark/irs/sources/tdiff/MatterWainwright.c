#include "irs.h"
#include "irsreg.h"
#include "irsdefs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void MatterWainwright( double *t52, double *temperature, int stride,
                       Domain_t *domain )
{
   char *me = "MatterWainwright";
   int ir, i, ii, j, jj, k, kk, imin, imax, jmin, jmax, kmin, kmax ;
   int nmixzn, namix ;
   double *t1, *t2, *tstar ;
   double t11, t12, t13, t14, t15, t16 ;
   double t21, t22, t23, t24, t25, t26 ;
   double t, t1bar, t6bar, twoSevenths = 2.0 / 7.0, myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   namix  = domain->namix  ;
   nmixzn = domain->nmixzn ;
   imin  = domain->imin  ;
   imax  = domain->imax  ;
   jmin  = domain->jmin  ;
   jmax  = domain->jmax  ;
   kmin  = domain->kmin  ;
   kmax  = domain->kmax  ;
   tstar = MALLOT( double, namix ) ;
   for ( i = 0 ; i < namix ; i++ ) {
      t        = MAX( temperature[i], tfloor ) ;
      tstar[i] = sqrt( t ) ;
      t52[i]   = 0.0 ;
   }
   myflops += 4.0 * namix ;
   t2 = tstar          ;
   t1 = tstar - stride ;
   if ( ndims == 2 ) {
      for ( jj = jmin ; jj <= jmax ; jj++ ) {
	 j = jj * domain->jp ;
	 for ( ii = imin ; ii <= imax ; ii++ ) {
	    i = ii + j ;
            t11 = t1[i]     ;
            t12 = t11 * t11 ;
            t13 = t12 * t11 ;
            t14 = t13 * t11 ;
            t15 = t14 * t11 ;
            t16 = t15 * t11 ;
            t21 = t2[i]     ;
            t22 = t21 * t21 ;
            t23 = t22 * t21 ;
            t24 = t23 * t21 ;
            t25 = t24 * t21 ;
            t26 = t25 * t21 ;
            t1bar = t11 + t21 ;
            t6bar = t16 + t15*t21 + t14*t22 + t13*t23
                                  + t12*t24 + t11*t25 + t26 ;
            t52[i] = twoSevenths * t6bar / t1bar ;
	 }
      }
      myflops += 27.0 * ( imax - imin + 1 ) * ( jmax - jmin  + 1 ) ;
   }
   if ( ndims == 3 ) {
      for ( kk = kmin ; kk <= kmax ; kk++ ) {
	 k = kk * domain->kp ;
         for ( jj = jmin ; jj <= jmax ; jj++ ) {
	    j = jj * domain->jp ;
	    for ( ii = imin ; ii <= imax ; ii++ ) {
	       i = ii + j + k ;
               t11 = t1[i]     ;
               t12 = t11 * t11 ;
               t13 = t12 * t11 ;
               t14 = t13 * t11 ;
               t15 = t14 * t11 ;
               t16 = t15 * t11 ;
               t21 = t2[i]     ;
               t22 = t21 * t21 ;
               t23 = t22 * t21 ;
               t24 = t23 * t21 ;
               t25 = t24 * t21 ;
               t26 = t25 * t21 ;
               t1bar = t11 + t21 ;
               t6bar = t16 + t15*t21 + t14*t22 + t13*t23
                                     + t12*t24 + t11*t25 + t26 ;
               t52[i] = twoSevenths * t6bar / t1bar ;
	    }
	 }
      }
      myflops += 27.0 * ( imax - imin + 1 ) *
			( jmax - jmin + 1 ) *
			( kmax - kmin + 1 ) ;
   }
   FREEMEM(tstar) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
