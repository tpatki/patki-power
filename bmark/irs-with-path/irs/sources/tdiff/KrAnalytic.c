#include "irsdefs.h"
#include "irs.h"
#include "irseos.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void KrAnalytic_fm1( double *kros, double *den, double *coef,
                     double dtrad, int ir, Domain_t *domain,
                     OpacityGroup_t *opacityGroup )
{
   char *me = "KrAnalytic_fm1";
   int i,*ndx,n ;
   double kp,kr ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   kp = dtrad*2.998e4*coef[0]*opacityGroup->planckMultiplier ;
   kr = 3.*opacityGroup->rosMultiplier*coef[0] ;
   ndx = domain->rndx[ir] ;
   n   = domain->rlen[ir] ;
   for ( i = 0 ; i < n ; i++ ) {
      kros[i]  = kr * den[i] ;
   }
   myflops += 2.*domain->rlen[ir] ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void KrAnalytic_fm3( double *kros, double *den, double *tmax, double *abar,
                     double *coef, double dtrad, int ir,
	             Domain_t *domain, OpacityGroup_t *opacityGroup )
{
   char *me = "KrAnalytic_fm3";
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
void KrAnalytic_fm5( double *kros, double *den, double *tmax, double *abar,
                     double *zbar, double dtrad, int ir,
	             Domain_t *domain, OpacityGroup_t *opacityGroup )
{
  char *me = "KrAnalytic_fm5";
  int i,*ndx,n ;
  double kt,t ;
  double rosMultiplier = opacityGroup->rosMultiplier;
  double planckMultiplier = opacityGroup->planckMultiplier;
  double myflops = 0.0;
  FT_INITIALIZE(me, domain->hash)
  ndx = domain->rndx[ir] ;
  n   = domain->rlen[ir] ;
  if (ioneq) {
    for ( i = 0 ; i < n ; i++ ){
      double kr = 1.411e-2 / ( abar[i] * abar[i] + ptiny ) ;
      double kp = dtrad*31.37*2.998e4*kr ;
      double kcr = 0.4005 / ( abar[i] + ptiny ) ;
      double kcp = dtrad*2.998e4*kcr ;
      kr *= 3.0 * rosMultiplier ;
      kp *= planckMultiplier ;
      kcr = 3.0*kcr ;
      t = tmax[ndx[i]] ;
      if (t < tfloor) t = tfloor ;
      t *= tscale ;
      kt = domain->zstar[ndx[i]]/t ;
      kt = kt * kt * kt * den[i] ;
      kt = kt/sqrt(t) ;
      kros[i]  = (kr*kt + kcr*domain->zstar[ndx[i]]) * den[i] ;
    }
    myflops += 27.*n ;
  }    else       {
    for ( i = 0 ; i < n ; i++ ){
      double kr = 1.411e-2 / ( abar[i] * abar[i] + ptiny ) ;
      double kp = dtrad*31.37*2.998e4*kr ;
      double kcr = 0.4005 / ( abar[i] + ptiny ) ;
      double kcp = dtrad*2.998e4*kcr ;
      kr *= 3.0 * rosMultiplier ;
      kp *= planckMultiplier ;
      kcr = 3.0*kcr ;
      kt = zbar[i]/(tmax[ndx[i]] + ptiny) ;
      kt = kt * kt * kt * den[i] ;
      kt = kt/(sqrt(tmax[ndx[i]]) + ptiny) ;
      kros[i]  = (kr*kt + kcr*zbar[i]) * den[i] ;
    }
    myflops += 27.*n ;
  }
  FT_FINALIZE(me, domain->hash, myflops)
}
void KrAnalytic_fm6( double *kros, double *den, double *tmax, double *abar,
                     double *zbar, double *coef, double  dtrad, 
                     int ir, Domain_t *domain, OpacityGroup_t *opacityGroup )
{ 
   char *me = "KrAnalytic_fm6";
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
void KrAnalytic_fm7( double *kros, double *den, double *tmax, double *coef,
                     double dtrad, int ir, Domain_t *domain,
                     OpacityGroup_t *opacityGroup )
{
   char *me = "KrAnalytic_fm7";
   int i,*ndx,n ;
   double kp,kr ;
   double kden,r,t,rexp,texp ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   kp = dtrad*2.998e4*KAPPA*opacityGroup->planckMultiplier ;
   kr = 3.*KAPPA*opacityGroup->rosMultiplier ;
   rexp = RHOEXP ;
   texp = TMPEXP ;
   ndx = domain->rndx[ir] ;
   n   = domain->rlen[ir] ;
   for ( i = 0 ; i < n ; i++ ) {
      r = pow(den[i],rexp) ;
      t = pow(tmax[ndx[i]],texp) ;
      kden = r * t * den[i] ;
      kros[i]  = kr * kden ;
   }
   myflops += 36.*domain->rlen[ir] ;
   FT_FINALIZE(me, domain->hash, myflops)
}
#undef KAPPA 
#undef RHOEXP
#undef TMPEXP
void KrAnalytic_fm8( double *kros, double *den, double *coef,
                     double dtrad, int ir, Domain_t *domain,
                     OpacityGroup_t *opacityGroup )
{
   char *me = "KrAnalytic_fm8";
   int i,*ndx ;
   double kr,kp,t ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   kr = 4.*2.998e4*sbc*opacityGroup->rosMultiplier/coef[0] ;
   kp = dtrad*2.998e4*1.0e6*opacityGroup->planckMultiplier ;
   ndx = domain->rndx[ir] ;
   for ( i = 0 ; i < domain->rlen[ir] ; i++ ) {
      t = domain->tmat[ndx[i]] ;
      if ( t < tfloor )  t = tfloor ;
      kros[i] = kr*t*t*t ;
   }
   myflops += 6.*domain->rlen[ir] ;
   FT_FINALIZE(me, domain->hash, myflops)
}
#define SIG0  data[0]
#define GAM0  data[1]
#define GA    data[2]
#define TM0   data[3]
#define SPOW  data[4]
#define FMLTX data[5]
#define RBOIL data[6]
#define FBOIL data[7]
void KrAnalytic_fm9( double *kros, double *den, double *abar, double *data,
                     double refd, double dtrad, int ir,
                     Domain_t *domain, OpacityGroup_t *opacityGroup )
{
  char *me = "KrAnalytic_fm9";
  int i, *ndx ;
  double t, d, z, tf, b1, b2, bmax, rt, bmin, coulog ;
  double x, y, a, b, plasma, tau, tbar, vbar, rion, tmin ;
  double phase3, rd ;
  double tm0, tm, tb, rpow, rpowm1, rpowm2, eta, econ ;
  double kr, kp, kr1, kp1, kre, kpe ; 
  double onethird  = 1.0 / 3.0 ;
  double twothirds = 2.0 / 3.0 ;
  double myflops = 0.0;
  FT_INITIALIZE(me, domain->hash)
  rd   = 1.0 / refd ;
  tm0  = tscale * TM0 ;
  rpow   = 2.0 *   GAM0 + SPOW ;
  rpowm1 = 2.0 * ( GAM0 - GA - 1.0 / 3.0 ) ;
  rpowm2 = 2.0 * ( GAM0 - 1.0 / 3.0 ) ;
  kr1 = 4.0   * 2.998e4 * sbc   * opacityGroup->rosMultiplier ;
  kp1 = dtrad * 2.998e4 * 1.0e6 * opacityGroup->planckMultiplier ;
  ndx = domain->rndx[ir] ;
  if ( ioneq == 1 ) {
    for ( i = 0 ; i < domain->rlen[ir] ; i++ ) {
      double kr0 = 3.0 * 1.548 / ( abar[i] * abar[i] + ptiny ) ;
      double kp0 = dtrad * 2.998e4 * 0.6192 / ( abar[i] * abar[i] + ptiny ) ;
      double kcr = 0.4005 / ( abar[i] + ptiny ) ;
      double kcp = dtrad * 2.998e4 * kcr ;
      kcr *= 3.0 ;
      t  = MAX( domain->tmat[ndx[i]], tfloor ) ;
      t *= tscale ;
      d = den[i] + ptiny ;
      z = MAX( domain->zstar[ndx[i]], 1.0 ) ;
      tf = 0.01734 * pow( z * d / ( abar[i] + ptiny ), twothirds ) ;
      b1 = 9.175 * abar[i] / ( d * z + ptiny )
	/ ( 1.0 / sqrt( t * t + tf * tf + ptiny ) + z / t ) ;
      b2 = 0.5396 * pow( abar[i] / d, twothirds ) ;
      bmax = MAX( b1, b2 ) ;
      rt = 1.0 / t ;
      bmin = rt * ( 2.304e-5 * rt * z * z + 2.507e-2 ) + ptiny ;
      coulog = 0.5 * log( 1.0 + bmax / bmin ) ;
      coulog = MAX( coulog, 2.0 ) ;
      x = sqrt( 1.5 * tf / t ) ;
      y = ( 0.7531 + x * ( 0.1679 + x * 0.3108 ) ) * x * x * x
	/ ( 1.0 + x * ( 0.2696 + x * ( 0.2280 + x * 0.3099 ) ) + ptiny ) ;
      a = ( 13.5 + y * ( 0.976 + y * 0.437 ) )
	/ (  1.0 + y * ( 0.510 + y * 0.126 ) + ptiny ) ;
      b = 0.882 - 0.16 * y + sqrt( y ) * ( 0.20 + 0.671 * y ) ;
      tau = 2.039e-14 *abar[i]*t*sqrt( t ) / ( d * z * z * coulog ) * b ;
      rion = 7.3461e-9 * pow( abar[i] / d, onethird ) ;
      tbar = 1.5 * sqrt( t * t + tf * tf ) ;
      vbar = 1.8753e9 * sqrt( tbar ) ;
      tmin = rion / vbar ;
      tau = MAX( tau, tmin ) ;
      plasma = 1.6966e15 * z * d * tau * t / ( abar[i] + ptiny ) * a * tscale ;
      x = 1.0 / ( z * ( 1.0 + y ) ) ;
      a = 0.961 + x * ( 0.7778 + x * ( 1.5956 + x * 1.3008 ) ) ;
      b = 1.200 + x * ( 5.4053 + x * ( 4.4080 + x * 0.9067 ) ) ;
      plasma = plasma * ( 0.0961 * b ) / ( 1.2 * a ) ;
      eta = MAX( rd * d, 0.001 ) ;
      phase3 = SIG0 * pow( eta, rpow ) ;
      if ( eta > 1.0 ) {
	tm = tm0 * pow( eta, rpowm1 ) * exp(2.0 * GA * (1.0 - 1.0/eta)) ;
      } else {
	tm = tm0 * pow( eta, rpowm2 ) ;
      }
      tb = tm * RBOIL ;
      if ( t > tm ) phase3 = phase3 * FMLTX ;
      if ( t > tb ) phase3 = phase3 * FBOIL ;
      econ = plasma + phase3 ;
      t = d * d * z * z * z / ( t * t * t * sqrt(t) ) ;
      kr = kr0 * t + kcr * z * d ;
      kp = kp0 * t + kcp * z * d ;
      t = MAX( domain->tmat[ndx[i]], tfloor ) ;
      kre = kr1 * t * t * t / ( econ + ptiny ) ;
      kpe = kp1 * d ; 
      kros[i]  = kr * kre / ( kr + kre ) ;
    }
    myflops += 116.0 * domain->rlen[ir] ;
  }
  FT_FINALIZE(me, domain->hash, myflops)
}
#undef SIG0 
#undef GAM0 
#undef GA   
#undef TM0  
#undef SPOW 
#undef FMLTX 
#undef RBOIL
#undef FBOIL 
