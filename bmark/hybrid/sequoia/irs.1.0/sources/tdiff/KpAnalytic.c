#include "irsdefs.h"
#include "irs.h"
#include "irseos.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void KpAnalytic_fm1( double *xplnk, double *den, double *coef, double  dtrad,
                     int ir, Domain_t *domain, OpacityGroup_t *opacityGroup )
{
   char *me = "KpAnalytic_fm1";
   int i, *ndx, len ;
   double kp ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   kp  = dtrad * 2.998e4 * coef[0] * opacityGroup->planckMultiplier ;
   ndx = domain->rndx[ir] ;
   len = domain->rlen[ir] ;
   for ( i = 0 ; i < len ; i++ ) {
      xplnk[i] = kp * den[i] ;
   }
   myflops += 1.0 * len ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void KpAnalytic_fm2( double *xplnk, double *den, double *abar, double *zbar,
                     double *zstar, double *mu, double dtrad, int ir,
                     double *phi, Domain_t *domain, OpacityGroup_t *opacityGroup )
{
   char *me = "KpAnalytic_fm2";
   int i, *ndx, n ;
   double za, z2a, kpm ;
   double te, tr, tr2, tr4, t3bar ;
   double tfloor4 ;
   double kc, relativc ;
   double kff, loglam, i0fit, logtr, gauntff ;
   double *kbf ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ndx = domain->rndx[ir] ;
   n   = domain->rlen[ir] ;
   kpm = dtrad * 2.998e4 * opacityGroup->planckMultiplier ;
   tfloor4 = tfloor  * tfloor  ;
   tfloor4 = tfloor4 * tfloor4 ;
   kbf  = MALLOT(double,n) ;
   bound_free( kbf, den, zbar, abar, mu, ndx, n, zstar, phi, domain )  ;
   for ( i = 0 ; i < n ; i++ ) {
      te  = MAX( domain->tmat[ndx[i]], tfloor ) ;
      tr4 = MAX( phi[ndx[i]], tfloor4 ) ;
      tr2 = sqrt( tr4 ) ;
      tr  = sqrt( tr2 ) ;
      za  = zstar[i] / ( abar[i] + ptiny ) ;
      z2a = zstar[i] * za ;
      relativc = exp( -0.01 * tr * ( 3.6 - 0.025 * tr ) ) +
                 0.004 * te * exp( -0.01 * tr * ( 6.75 + tr / 19.0 ) ) ;
      kc = 3.1281e-3 * tr4 * za * relativc ;
      loglam = log10( te / tr ) ;
      i0fit  = 1.13 * ( 1.5 + loglam * ( 0.42535 * loglam - 0.92535 ) ) ;
      logtr   = log10( tr ) ;
     if ( logtr < -3.0 ) {
	gauntff = 1.0 ;
      } else if ( logtr >  3.0 ){
	gauntff = 1.0 ;
      } else {
	gauntff = 1.2421 + logtr * 
                  ( -9.78064e-2 + logtr * (  5.42604e-2 + logtr *
                  ( -2.91233e-2 + logtr * ( -2.73358e-2 + logtr *
                  (  1.28980e-2 + logtr * (  5.44464e-3 + logtr *
                  ( -9.79565e-4 + logtr * ( -3.46401e-4 ) ) ) ) ) ) ) ) ;
      }
      kff = 0.427 * den[i] * za * z2a / ( sqrt(te) + 0.001 ) *
            i0fit * gauntff ;
      t3bar = ( te + tr ) * ( te * te + tr2 ) ;
      xplnk[i] = kpm * den[i] * ( kbf[i] + kff + kc ) / t3bar ;
   }
   myflops += 121.0 * n ;
   FREEMEM(kbf)  ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void KpAnalytic_fm3( Domain_t *domain, double *kros,  double *xplnk , 
		     double *den, double *tmax,   double dtrad,
                     int ir, double *coef, double *abar,
		     OpacityGroup_t *opacityGroup)
{
   char *me = "KpAnalytic_fm3";
   int i,j ;
   double *ftemp,*ftemp2 ;   
   double *xifrac ;          
   double *xkap0  ;
   double *xlev   ;
   double *slst   ;
   double *snxt   ;
   double *accum ;
   double *d      ;          
   double *t      ;          
   int    *indx   ;
   double en      ;          
   double ex      ;          
   double krate   ;
   double t3      ;          
   double t35   ;
   double kplnk   ;
   double strom[20] ;        
   double xstrom[20] ;       
   double xnlev2  ;          
   double xnlev3  ;          
   int     nlev   ;          
   double slo     ;
   double shi     ;
   double xlo     ;
   double xhi     ;
   int    *ndx    ;
   int     n      ;
   double  arg    ;
   double rosMultiplier = opacityGroup->rosMultiplier;
   double planckMultiplier = opacityGroup->planckMultiplier;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ndx = domain->rndx[ir] ;
   n   = domain->rlen[ir] ;
#define stromin(a,b)   \
   xstrom[j] = a ;     \
    strom[j] = b ;     \
   j++ ;
   j = 0 ;
   stromin (     0.  ,      0.  )
   stromin (1.900e+00, 3.066e-01)
   stromin (2.700e+00, 1.815e+00)
   stromin (3.200e+00, 4.148e+00)
   stromin (4.000e+00, 1.137e+01)
   stromin (4.800e+00, 2.389e+01)
   stromin (5.600e+00, 4.157e+01)
   stromin (6.400e+00, 6.302e+01)
   stromin (8.100e+00, 1.113e+02)
   stromin (8.900e+00, 1.314e+02)
   stromin (9.800e+00, 1.502e+02)
   stromin (1.100e+01, 1.687e+02)
   stromin (1.200e+01, 1.792e+02)
   stromin (1.300e+01, 1.860e+02)
   stromin (1.400e+01, 1.904e+02)
   stromin (1.500e+01, 1.930e+02)
   stromin (1.600e+01, 1.946e+02)
   stromin (1.800e+01, 1.960e+02)
   stromin (2.200e+01, 1.965e+02)
   stromin (3.000e+01, 1.965e+02)
   j = 0 ;
   ftemp  = ALLOT(double,8*n) ;
   ftemp2 = ftemp ;
   xifrac = FALLOT(n) ;
   xkap0  = FALLOT(n) ;
   xlev   = FALLOT(n) ;
   slst   = FALLOT(n) ;
   snxt   = FALLOT(n) ;
   accum  = FALLOT(n) ;
   d      = FALLOT(n) ;
   t      = FALLOT(n) ;
   indx = ALLOT(int,n) ;
   en = tscale*coef[0] ;
   dtrad = dtrad*2.998e4 ;
   for ( i = 0 ; i < n ; i++ ){
     double kcomp = 0.4005 / ( abar[i] + ptiny ) ;
     double k0    = 2.776  * rosMultiplier    / ( abar[i] * abar[i] + ptiny ) ;
     double kpff0 = 0.4275 * planckMultiplier / ( abar[i] * abar[i] + ptiny ) ;
     double kpbf0 = 2.217  * planckMultiplier / ( abar[i] + ptiny ) ;
      t[i] = tscale*tmax[ndx[i]] ;
      if ( t[i] < 1.0e-6 )  t[i] = 1.0e-6 ;
      d[i] = den[i] + ptiny ;
      ex = exp(-en/t[i]) ;
      krate = 158.5*abar[i]*t[i]*sqrt(t[i])/d[i]*ex + ptiny ;
      xifrac[i] = krate*(sqrt( 1.0 + 2.0/krate) - 1.0) ;
      if (xifrac[i] > 1.) xifrac[i] = 1.0 ;
      t3 = t[i]*t[i]*t[i] ;
      t35 = t3*sqrt(t[i]) ;
      kplnk = kpff0*xifrac[i]*xifrac[i]*d[i]/t3
            + kpbf0*ex*(1. - xifrac[i])/t35
            + kcomp ;
      xplnk[i] = dtrad*kplnk*d[i] ;
      xkap0[i] = k0*xifrac[i]*xifrac[i]*d[i]/(t35) ;
      xifrac[i] = 12.0*(1. - xifrac[i]) * ex / ( abar[i] * t3 + ptiny ) ;
      xlev[i] = en/(16.*t[i]) ;
      }
   myflops += 82.*n ;
   for ( i = 0 ; i < n ; i++ )  indx[i] = 0 ;
   for ( j = 1 ; j < 19 ; j++ )
      {
      for ( i = 0 ; i < n ; i++ )
         if ( xlev[i] > xstrom[j] )  indx[i] = j ;
      }
   myflops += 18.*n ;
   for ( i = 0 ; i < n ; i++ )
      {
      slo = strom[indx[i]] ;
      shi = strom[indx[i] + 1] ;
      xlo = xstrom[indx[i]] ;
      xhi = xstrom[indx[i] + 1] ;
      snxt[i] = (slo*(xhi - xlev[i]) + shi*(xlev[i] - xlo))/(xhi - xlo) ;
      if (xlev[i] > xstrom[19])  snxt[i] = strom[19] ;
      }
   myflops += 11.*n ;
   for ( i = 0 ; i < n ; i++ )
      {
      accum[i] = snxt[i]/(xkap0[i] + ptiny) ;
      arg = xlev[i] ;
      if (arg > 200)  arg = 200 ;
      xkap0[i] += xifrac[i]*exp(arg)/64. ;
      }
   myflops += 16.*n ;
   for ( nlev = 3 ; nlev >= 1 ; nlev-- )
      {
      xnlev3 = (double)nlev ;
      xnlev2 = xnlev3*xnlev3 ;
      xnlev3 = xnlev2*xnlev3 ;
      for ( i = 0 ; i < n ; i++ )
         {
         slst[i] = snxt[i] ;
         xlev[i] = en/(xnlev2*t[i]) ;
         indx[i] = 0 ;
         }
      myflops += 5.*n ;
      for ( j = 1 ; j < 19 ; j++ )
         {
         for ( i = 0 ; i < n ; i++ )
            if ( xlev[i] > xstrom[j] )  indx[i] = j ;
         }
      myflops += 18.*n ;
      for ( i = 0 ; i < n ; i++ )
         {
         slo = strom[indx[i]] ;
         shi = strom[indx[i] + 1] ;
         xlo = xstrom[indx[i]] ;
         xhi = xstrom[indx[i] + 1] ;
         snxt[i] = (slo*(xhi - xlev[i]) + shi*(xlev[i] - xlo))/(xhi - xlo) ;
         if (xlev[i] > xstrom[19])  snxt[i] = strom[19] ;
         }
      myflops += 11.*n ;
      for ( i = 0 ; i < n ; i++ )
         {
         accum[i] += (snxt[i] - slst[i])/(xkap0[i] + ptiny) ;
         arg = xlev[i] ;
         if (arg > 200)  arg = 200 ;
         xkap0[i] += xifrac[i]*exp(arg)/xnlev3 ;
         }
      myflops += 21.*n ;
      }
   for ( i = 0 ; i < n ; i++ ){
     double kcomp = 0.4005 / ( abar[i] + ptiny ) ;
     accum[i] += (strom[19] - snxt[i])/(xkap0[i] + ptiny) ;
     kros[i]= 3.0*opacityGroup->rosMultiplier * 
              d[i]*(1.0/(accum[i]+ ptiny) + kcomp) ;
   }
   myflops += 14.*n ;
   FREEMEM(ftemp) ;
   FREEMEM(indx) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void KpAnalytic_fm5( double *xplnk, double *den, double *abar, double *zstar,
                     double dtrad, int ir, Domain_t *domain,
                     OpacityGroup_t *opacityGroup )
{
   char *me = "KpAnalytic_fm5";
   int i, len, *ndx ;
   double kff, kcp, t, f, z, dtc ; 
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   dtc = dtrad * 2.998e4 * opacityGroup->planckMultiplier ;;
   ndx = domain->rndx[ir] ;
   len = domain->rlen[ir] ;
   for ( i = 0 ; i < len ; i++ ) {
      t        = MAX( domain->tmat[ndx[i]], tfloor ) ;
      z        = MAX( zstar[i], 1.0 ) ;
      f        = den[i] * z * z * z / ( t * t * t * sqrt( t ) ) ;
      kff      = 0.4426 * f / ( abar[i] * abar[i] ) ;
      kcp      = 0.4005 * z / abar[i] ;
      xplnk[i] = dtc * den[i] * ( kff + kcp ) ;
   }
   myflops += 28.0 * len ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void KpAnalytic_fm6( Domain_t *domain, double *kros, double *xplnk,
		     double *den, double *tmax, double  dtrad, 
		     int  ir, double *coef, double *abar, double *zbar,
		     OpacityGroup_t *opacityGroup)
{
   char *me = "KpAnalytic_fm6";
   int i,j ;
   double *ftemp,*ftemp2 ;   
   double *d      ;          
   double *t      ;          
   double *z      ;          
   double *e      ;          
   int    *indx   ;
   double e0      ;          
   double e1      ;          
   double e2      ;          
   double de      ;
   double kplnk   ;
   double k0ff    ;
   double k0bf    ;
   double xros    ;
   double ex      ;          
   double t3      ;          
   double t35   ;
   double k0      ;
   double k1      ;
   double a0      ;
   double a1      ;
   double q       ;
   double strom[20] ;        
   double xstrom[20] ;       
   double slo     ;
   double shi     ;
   double xlo     ;
   double xhi     ;
   double s       ;
   double kmltp   ;
   double kmltr   ;
   int    *ndx    ;
   int     n      ;
   double zmax  ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ndx = domain->rndx[ir] ;
   n   = domain->rlen[ir] ;
   kmltr = opacityGroup->rosMultiplier ;
   kmltp = opacityGroup->planckMultiplier ;
#define stromin(a,b)   \
   xstrom[j] = a ;     \
    strom[j] = b ;     \
   j++ ;
   j = 0 ;
   stromin (     0.  ,      0.  )
   stromin (1.900e+00, 3.066e-01)
   stromin (2.700e+00, 1.815e+00)
   stromin (3.200e+00, 4.148e+00)
   stromin (4.000e+00, 1.137e+01)
   stromin (4.800e+00, 2.389e+01)
   stromin (5.600e+00, 4.157e+01)
   stromin (6.400e+00, 6.302e+01)
   stromin (8.100e+00, 1.113e+02)
   stromin (8.900e+00, 1.314e+02)
   stromin (9.800e+00, 1.502e+02)
   stromin (1.100e+01, 1.687e+02)
   stromin (1.200e+01, 1.792e+02)
   stromin (1.300e+01, 1.860e+02)
   stromin (1.400e+01, 1.904e+02)
   stromin (1.500e+01, 1.930e+02)
   stromin (1.600e+01, 1.946e+02)
   stromin (1.800e+01, 1.960e+02)
   stromin (2.200e+01, 1.965e+02)
   stromin (3.000e+01, 1.965e+02)
   j = 0 ;
   ftemp  = ALLOT(double,4*n) ;
   ftemp2 = ftemp ;
   d      = FALLOT(n) ;
   t      = FALLOT(n) ;
   z      = FALLOT(n) ;
   e      = FALLOT(n) ;
   indx = ALLOT(int,n) ;
   dtrad = dtrad*2.998e4 ;
   e0  = tscale * coef[0] ;
   e1  = tscale * coef[1] ;
   e2  = tscale * coef[2] ;
   de  = e1 - e0 ;
   if ((fabs(e1) < ptiny)) zmax = 1.0 ;
   else                    zmax = 2.0 ;
   zmax *= 0.95 ;
   for ( i = 0 ; i < n ; i++ ){
     double k00 = 158.5 * abar[i] ;
     if (domain->trad[ndx[i]] < tfloor) domain->trad[ndx[i]]  = tfloor ;
     t[i] = tmax[ndx[i]] ;
     if ( t[i] < tfloor )  t[i] = tfloor ;
     t[i] = tscale*t[i] ;
     d[i] = den[i] + ptiny ;
     k0 = k00*t[i]*sqrt(t[i])*exp(-e0/t[i])/d[i] ;
     a0 = k0*( sqrt(1.0 + 2.0/(k0+ptiny)) - 1.0 ) ;
     k1 = k0*exp(-de/t[i]) ;
     a1 = k1*( sqrt(1.0 + 2.0/(k1+ptiny)) - 1.0 ) ;
     z[i] = a0*(1.0 + a1) ;
     e[i] = (e0*(1. - a0) + e1*a0*(1. - a1) + e2*a0*a1)/t[i] ;
   }
   myflops += 88.*n ;
   for ( i = 0 ; i < n ; i++ )  indx[i] = 0 ;
   for ( j = 1 ; j < 19 ; j++ )
      {
      for ( i = 0 ; i < n ; i++ )
         if ( e[i] > xstrom[j] )  indx[i] = j ;
      }
   myflops += 18.*n ;
   for ( i = 0 ; i < n ; i++ ){
     double krff0 = 2.776 / ( abar[i] * abar[i] + ptiny ) ;
     double krbf0 = 16.0  / ( abar[i] + ptiny ) ;
     double kpff0 = 0.4275 / ( abar[i] * abar[i] + ptiny ) ;
     double kpbf0 = 2.4638 / ( abar[i] + ptiny ) ;
     double kcomp = 0.4005 / ( abar[i] + ptiny ) ;
      ex = exp(-e[i]) ;
      q = z[i] ;
      if (q < 1.0)  q = 1.0 ; 
      if (z[i] > zmax)  t[i] = tscale*domain->trad[ndx[i]] ; 
      t3  = t[i]*t[i]*t[i] ;
      t35 = t3*sqrt(t[i]) ;
      kplnk = kpff0*q*z[i]*z[i]*d[i]/t35
            + kpbf0*ex*q*q*q*q / ( t3 * ( zbar[i] - z[i] ) + ptiny )
            + kcomp ;
      xplnk[i] = kmltp*dtrad*kplnk*d[i] ;
      slo = strom[indx[i]] ;
      shi = strom[indx[i] + 1] ;
      xlo = xstrom[indx[i]] ;
      xhi = xstrom[indx[i] + 1] ;
      s = (slo*(xhi - e[i]) + shi*(e[i] - xlo))/(xhi - xlo) ;
      if (e[i] > xstrom[19])     s = strom[19] ;
      k0ff = krff0*q*z[i]*z[i]*d[i]/t35 ;
      k0bf = krbf0*q*q*q*q / ( t3 * ( zbar[i] - z[i] ) + ptiny ) ;
      xros = s/(k0ff+ptiny) + (strom[19] - s)/(k0ff + k0bf + ptiny) ;
      kros[i] = 3.0*kmltr*d[i]*(1.0/(xros + ptiny) + kcomp) ;
   }
   myflops += 94.*n ;
   FREEMEM(ftemp) ;
   FREEMEM(indx) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
#define KAPPA  coef[0]
#define RHOEXP coef[1]
#define TMPEXP coef[2]
void KpAnalytic_fm7( double *xplnk, double *den, double *temp, double *coef,
                     double dtrad, int ir, Domain_t *domain,
                     OpacityGroup_t *opacityGroup )
{
   char *me = "KpAnalytic_fm7";
   int i, *ndx, len ;
   double kp, r, t, rexp, texp ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   kp   = dtrad * 2.998e4 * KAPPA * opacityGroup->planckMultiplier ;
   rexp = RHOEXP ;
   texp = TMPEXP ;
   ndx = domain->rndx[ir] ;
   len = domain->rlen[ir] ;
   for ( i = 0 ; i < len ; i++ ) {
      r = pow( den[i],       rexp ) ;
      t = pow( temp[ndx[i]], texp ) ;
      xplnk[i] = kp * den[i] * r * t ;
   }
   myflops += 35.0 * len ;
   FT_FINALIZE(me, domain->hash, myflops)
}
#undef KAPPA 
#undef RHOEXP
#undef TMPEXP
void KpAnalytic_fm8( double *xplnk, double *den, double *abar, double *zbar,
                     double dtrad, int ir, double *phi,
                     Domain_t *domain, OpacityGroup_t *opacityGroup )
{
   char *me = "KpAnalytic_fm8";
   int i, *ndx, n ;
   double t, sbcc ;
   double a, b, c, d, e, f, g, r, za, z2a, kpm ;
   double tr, tr2, tr3, tr4, tm2, tm3, tfloor4 ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ndx = domain->rndx[ir] ;
   n   = domain->rlen[ir] ;
   kpm  = dtrad * 2.998e4 * opacityGroup->planckMultiplier ;
   sbcc = 2.998e4 * sbc ;
   tfloor4 = tfloor  * tfloor  ;
   tfloor4 = tfloor4 * tfloor4 ;
   for ( i = 0 ; i < n ; i++ ) {
      t = MAX( domain->tmat[ndx[i]], tfloor ) ;
      tr4 = MAX( phi[ndx[i]], tfloor4 ) ;
      tr2 = sqrt( tr4 ) ;
      tr  = sqrt( tr2 ) ;
      tr3 = tr * tr2    ;
      tm2 = t   * t ;
      tm3 = tm2 * t ;
      za  = zbar[i] / ( abar[i] + ptiny ) ;
      z2a = zbar[i] * za ;
      f = 0.003984 - 2.6894e-4 * tr + 6.6644e-6 * tr2 - 5.6392e-8 * tr3 ;
      g = 1.2894e4 * ( 1.00221 - 0.03621 * tr + 7.5637e-4 * tr2
                     - 6.1573e-6 * tr3 + f * t ) ;
      a = 1.9426e6 * ( 1.0 + 0.00675 * t ) / sqrt( t ) ;
      r = MIN( tr / t, 1.0 ) ;
      b = a * ( 1.0 + r * ( 0.915 - 0.714 * r ) ) ;
      c = za * ( z2a * den[i] * b + g * tr4 ) ;
      d = t * tr + tr2 + tm2 ;
      e = sbcc * ( tr * d + tm3 + 1.0e-9 ) ;
      xplnk[i] = kpm * c * den[i] / e ;
   }
   myflops += 69.0 * n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void KpAnalytic_fm9( double *xplnk, double *den, double *abar, double *zbar,
                     double dtrad, int ir, double *phi,
                     Domain_t *domain, OpacityGroup_t *opacityGroup )
{
   char *me = "KpAnalytic_fm9";
   int i, *ndx, n ;
   double t, sbcc ;
   double c, e, f, g, za, z2a, kpm ;
   double t3bar, kc, ff, bf ;
   double tr, tr2, tr3, tr4, tfloor4 ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ndx = domain->rndx[ir] ;
   n   = domain->rlen[ir] ;
   kpm  = dtrad * 2.998e4 * opacityGroup->planckMultiplier ;
   sbcc = 2.998e4 * sbc ;
   tfloor4 = tfloor  * tfloor  ;
   tfloor4 = tfloor4 * tfloor4 ;
   for ( i = 0 ; i < n ; i++ ) {
      t = MAX( domain->tmat[ndx[i]], tfloor ) ;
      tr4 = MAX( phi[ndx[i]], tfloor4 ) ;
      tr2 = sqrt( tr4 ) ;
      tr  = sqrt( tr2 ) ;
      tr3 = tr * tr2    ;
      za  = zbar[i] / ( abar[i] + ptiny ) ;
      z2a = zbar[i] * za ;
      f = 0.003984 - 2.6894e-4 * tr + 6.6644e-6 * tr2 - 5.6392e-8 * tr3 ;
      g = 1.2894e4 * ( 1.00221 - 0.03621 * tr + 7.5637e-4 * tr2
                     - 6.1573e-6 * tr3 + f * t ) ;
      kc = g * tr4 ;
      ff = z2a * den[i] / sqrt( t + 0.001 ) ;
      bf = z2a * abar[i] / ( t + 0.001 ) ;
      c     = za * ( ff * (3.5e6 + bf * (0.85e5 + 1.245e4 * zbar[i]) ) + kc ) ;
      t3bar = ( t + tr ) * ( t * t + tr * tr ) + 1.0e-9 ;
      e = sbcc * t3bar ;
      xplnk[i] = kpm * c * den[i] / e ;
   }
   myflops += 67.0 * n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
