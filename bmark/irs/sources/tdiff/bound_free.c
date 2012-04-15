#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void bound_free( double *kbf, double *den, double *zbar, double *abar,
                 double *mu, int *ndx, int n, double *zstar, double *phi,
		 Domain_t *domain )
{
   char *me = "bound_free";
   int i ;
   double te, tr, acof, dt1, trp, emm, zn  ;
   double en, enp, exn, exnp, exr, al, rad, tr4, tfloor4 ;
   double zs2, zs4, z1, z1i, dilog1, dilog2, z2, z2i, logz1, logz2, ans ;
   double val1, val2, val3 ;
   double convert   = 703.0 / 2.998e4 ;
   double n2        = 4.0 ;
   double n3        = 8.0 ;
   double ninth     = 1.0 / 9.0 ;
   double pi26      = PI * PI / 6.0 ;
   double srn3      = 2.0 * 0.202056903159594 ; 
   double th16      = 1.0 / 16.0 ;
   double twothirds = 2.0 /  3.0 ;
   double myflops   = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   tfloor4 = tfloor  * tfloor  ;
   tfloor4 = tfloor4 * tfloor4 ;
   for ( i = 0 ; i < n ; i++ ) {
      te  = MAX( domain->tmat[ndx[i]], tfloor ) ;
      tr4 = MAX( phi[ndx[i]], tfloor4 ) ;
      tr  = sqrt( sqrt( tr4 ) ) ;
      dt1 = MAX( fabs( tr - te ), 0.0001 * te ) ;
      if ( tr >= te ) {
         trp = te + dt1 ;
      } else {
         trp = te - dt1 ;
      }
      val1 = MAX( (-mu[i] / te), -100.0 ) ;
      emm  = exp( val1 ) ;
      zs2 = zstar[i] * zstar[i] ;
      zs4 = zs2 * zs2 ;
      zn = zbar[i] - twothirds ;
      zn = MAX( zstar[i], zn ) ;
      en   = 0.0136 * zn   * zn ;
      enp  = 0.0136 * srn3 * zs2 ;
      val1 = MAX( (-en  / te), -100.0 ) ;
      val2 = MAX( (-enp / te), -100.0 ) ;
      val3 = MAX( (-(en - enp) / trp), -100.0 ) ;
      exn  = exp( val1 ) ;
      exnp = exp( val2 ) ;
      exr  = exp( val3 ) ;
      al   = (enp + mu[i]) / te + log( 1.0 + exnp * emm ) ;
      rad  = (trp * exr * exnp - te * exn) * emm / (1.0 + exn * emm) ;
      acof = 2.0 * al * rad ;
      zn = zbar[i] - twothirds * n3 ;
      zn = MAX( zstar[i], zn ) ;
      en   = 0.0136 * zn * zn / n2 ;
      enp  = 0.0136 * ( srn3 - 2.0 / n3 ) * zs2 ;
      val1 = MAX( (-en  / te), -100.0 ) ;
      val2 = MAX( (-enp / te), -100.0 ) ;
      val3 = MAX( (-(en - enp) / trp), -100.0 ) ;
      exn  = exp( val1 ) ; 
      exnp = exp( val2 ) ;
      exr  = exp( val3 ) ;
      al   = (enp + mu[i]) / te + log( 1.0 + exnp * emm ) ;
      rad  = (trp * exr * exnp - te * exn) * emm / (1.0 + exn * emm) ;
      acof = acof + 2.0 * al * rad / n3 ;
      z1  = -1.0 / ( emm * exnp + 1.0e-5 ) ;
      z1i =  1.0 / z1 ;
      if ( fabs(z1) < 1.0 ) {
         dilog1 = z1 * ( 1.0 + z1 * ( 0.25 + z1 * ( ninth + th16 * z1 ) ) ) ;
      } else {
         logz1  = log( -z1 + 1.e-5 ) ;
         dilog1 = z1i * ( 1.0 + z1i * ( 0.25 + z1i * ( ninth + th16 * z1i ) ) )
                  - 0.5 * logz1 * logz1 - pi26 ;
      }
      z2  = -1.0 / ( emm + 1.e-5 ) ;
      z2i =  1.0 / z2 ;
      if ( fabs(z2) < 1.0 ) {
         dilog2 = z2 * ( 1.0 + z2 * ( 0.25 + z2 * ( ninth + th16 * z2 ) ) ) ;
      } else {
         logz2  = log( -z2 + 1.e-5 ) ;
         dilog2 = z2i * ( 1.0 + z2i * ( 0.25 + z2i * ( ninth + th16 * z2i ) ) ) 
                  - 0.5 * logz2 * logz2 - pi26 ;
      }
      logz1 = log( -z1 + 1.0 ) ;
      logz2 = log( -z2 + 1.0 ) ;
      ans = -0.5 * logz1 * logz1 - dilog1
          +  0.5 * logz2 * logz2 + dilog2 ;
      kbf[i] = ( 78.68 * zs4 * acof / ( trp - te ) +
                 78.68 / 0.0136 * zs2 * te *ans ) * convert
               / ( abar[i] + ptiny ) ;
   }
   myflops += 281.0 * n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
