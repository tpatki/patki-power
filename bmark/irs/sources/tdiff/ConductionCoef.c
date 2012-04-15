#include "irs.h"
#include "irsreg.h"
#include "irsdefs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void ElectronConductionCoef( double *diffCoef, double *t52, Domain_t *domain )
{
   char *me = "ElectronConductionCoef";
   int ir, i, j, nmixzn ;
   double myflops = 0.0 ;
   double *den = domain->den ;
   double *vol = domain->vol ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->namix ; i++ ) {
      diffCoef[i] = 0.0 ;
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      int length    = domain->rlen[ir] ;
      int *ndx      = domain->rndx[ir] ;
      int numGroups = reg[ir].numGroups ;
      double *cden  = MALLOT( double, length ) ;
      double *coef  = MALLOT( double, length ) ;
      RegionTable_t *regionTable = domain->domainRegions[ir].regionTables ;
      for ( j = 0 ; j < numGroups ; j++ ) {
         int econform  = reg[ir].eosGroup[j].econform ;
         double value  = reg[ir].eosGroup[j].econvalue ;
         double *abar  = regionTable[j].a ;
         double *zstar = regionTable[j].zstar ;
         double *mf    = regionTable[j].massFrac ;
         double *volFrac ;
         if ( numGroups == 1 ) {
            for ( i = 0 ; i < length ; i++ ) {
               cden[i] = den[ndx[i]] ;
	    }
	 } else {
            volFrac = domain->eosvf + j * domain->namix ;
            for ( i = 0 ; i < length ; i++ ) {
               cden[i] = mf[i] * den[ndx[i]] / ( volFrac[ndx[i]] + ptiny ) ;
	    }
            myflops += 6.0 * length ;
	 }
         if        ( econform == 1 ) {
	    Econ_fm1( coef, value, length, domain ) ;
	 } else if ( econform == 2 ) {
	    Econ_fm2( coef, t52, value, ndx, length, domain ) ;
	 } else if ( econform == 3 ) {
	    Econ_fm3( coef, t52, cden, zstar, abar, ndx, length, domain ) ;
	 }
         if ( numGroups == 1 ) {
   	    for ( i = 0 ; i < length ; i++ ) {
	       diffCoef[ndx[i]] = coef[i] ;
	    }
	 } else {
   	    for ( i = 0 ; i < length ; i++ ) {
	       diffCoef[ndx[i]] += volFrac[ndx[i]] * coef[i] ;
	    }
            myflops += 2.0 * length ;
         }
      }
      FREEMEM(cden) ;
      FREEMEM(coef) ;
   }
   nmixzn = domain->nmixzn ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void IonConductionCoef( double *diffCoef, double *t52, Domain_t *domain )
{
   char *me = "IonConductionCoef";
   int ir, i, j, nmixzn ;
   double myflops = 0.0 ;
   double *den = domain->den ;
   double *vol = domain->vol ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->namix ; i++ ) {
      diffCoef[i] = 0.0 ;
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      int length    = domain->rlen[ir] ;
      int *ndx      = domain->rndx[ir] ;
      int numGroups = reg[ir].numGroups ;
      double *cden  = MALLOT( double, length ) ;
      double *coef  = MALLOT( double, length ) ;
      RegionTable_t *regionTable = domain->domainRegions[ir].regionTables ;
      for ( j = 0 ; j < numGroups ; j++ ) {
         int iconform  = reg[ir].eosGroup[j].iconform ;
         double value  = reg[ir].eosGroup[j].iconvalue ;
         double *abar  = regionTable[j].a ;
         double *zstar = regionTable[j].zstar ;
         double *mf    = regionTable[j].massFrac ;
         double *volFrac ;
         if ( numGroups == 1 ) {
            for ( i = 0 ; i < length ; i++ ) {
               cden[i] = den[ndx[i]] ;
	    }
	 } else {
            volFrac = domain->eosvf + j * domain->namix ;
            for ( i = 0 ; i < length ; i++ ) {
               cden[i] = mf[i] * den[ndx[i]] / ( volFrac[ndx[i]] + ptiny ) ;
	    }
            myflops += 6.0 * length ;
	 }
         if        ( iconform == 1 ) {
	    Icon_fm1( coef, value, length, domain ) ;
	 } else if ( iconform == 2 ) {
	    Icon_fm2( coef, t52, value, ndx, length, domain ) ;
	 } else if ( iconform == 3 ) {
	    Icon_fm3( coef, t52, cden, zstar, abar, ndx, length, domain ) ;
	 }
         if ( numGroups == 1 ) {
   	    for ( i = 0 ; i < length ; i++ ) {
	       diffCoef[ndx[i]] = coef[i] ;
	    }
	 } else {
   	    for ( i = 0 ; i < length ; i++ ) {
	       diffCoef[ndx[i]] += volFrac[ndx[i]] * coef[i] ;
	    }
            myflops += 2.0 * length ;
         }
      }
      FREEMEM(cden) ;
      FREEMEM(coef) ;
   }
   nmixzn = domain->nmixzn ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void Econ_fm1( double *coef, double value, int length, Domain_t *domain )
{
   char *me = "Econ_fm1" ;
   int i ;
   double inverse_value, myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   inverse_value = 1.0 / ( value + ptiny ) ;
   for ( i = 0 ; i < length ; i++ ) {
      coef[i] = inverse_value ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
void Econ_fm2( double *coef, double *t52, double value, int *ndx, int length,
               Domain_t *domain )
{
   char *me = "Econ_fm2" ;
   int i ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < length ; i++ ) {
      coef[i] = 1.0 / ( value * t52[ndx[i]] + ptiny ) ;
   }
   myflops += 6.0 * length ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void Econ_fm3( double *coef, double *t52, double *cden, double *zstar,
               double *abar, int *ndx, int length, Domain_t *domain )
{
   char *me = "Econ_fm3" ;
   int i ;
   double aInverse, FcInverse, fInverse ;
   double twothirds = 2.0 / 3.0, myflops = 0.0 ;
   double a1 = 13.5   ;
   double a2 =  0.976 ;
   double a3 =  0.437 ;
   double b1 =  1.000 ;
   double b2 =  0.510 ;
   double b3 =  0.126 ;
   double c1 =  1.555e4 ;
   double c2 =  0.04319 ;
   double c3 =  exp( 2.00001 ) ;
   double d1 =  4.50  ;
   double d2 =  3.67  ;
   double d3 =  0.756 ;
   double e1 =  8.09  ;
   double e2 = 16.6   ;
   double e3 = 13.5   ;
   double f1 =  0.88  ;
   double f2 = -0.16  ;
   double f3 =  0.2   ;
   double f4 =  0.67  ;
   double constFactori = 1.0 / 34.52 ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < length ; i++ ) {
      double t   = pow( t52[ndx[i]], 0.4 ) ;
      double z   = zstar[i] ;
      double za  = z / abar[i]  ;
      double zsq = z * z ;
      double denmax = MAX( cden[i], 1.0e-10 ) ;
      double ef     = 0.026012 * pow( za * denmax, twothirds ) ;
      double xf     = sqrt( ef / t ) ;
      double zeta = ( 0.7531 + xf * (0.1679 + xf * 0.3108) ) * xf * xf * xf
                  / ( 1.0    + xf * (0.2676 + xf * (0.2280 + xf * 0.3099) ) ) ;
      double x    = 1.0 / ( z * ( 1.0 + zeta ) ) ;
      double coulombLog =
             0.5 * log( c3 + ( c1 * t * t * t /
                               (denmax * za * (c2 * zsq + t)) ) ) ;
      aInverse  = (b1 + zeta * ( b2 + zeta * b3 ) ) /
	          (a1 + zeta * ( a2 + zeta * a3 ) ) ;
      FcInverse = ( 1.0 + x * ( e1 + x * ( e2 + x * e3 ) ) ) /
	          ( 1.0 + x * ( d1 + x * ( d2 + x * d3 ) ) ) ;
      fInverse  = 1.0 / ( f1 + f2 * zeta + sqrt(zeta) * (f3 + f4 * zeta) ) ;
      coef[i]   = constFactori * z * coulombLog *
                  aInverse * FcInverse * fInverse / t52[ndx[i]] ;
   }
   myflops += 142.0 * length ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void Icon_fm1( double *coef, double value, int length, Domain_t *domain )
{
   char *me = "Icon_fm1" ;
   int i ;
   double inverse_value, myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   inverse_value = 1.0 / ( value + ptiny ) ;
   for ( i = 0 ; i < length ; i++ ) {
      coef[i] = inverse_value ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
void Icon_fm2( double *coef, double *t52, double value, int *ndx, int length,
               Domain_t *domain )
{
   char *me = "Icon_fm2" ;
   int i ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < length ; i++ ) {
      coef[i] = 1.0 / ( value * t52[ndx[i]] + ptiny ) ;
   }
   myflops += 6.0 * length ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void Icon_fm3( double *coef, double *t52, double *cden, double *zstar,
               double *abar, int *ndx, int length, Domain_t *domain )
{
   char *me = "Icon_fm3";
   int i ;
   double myflops = 0.0 ;
   double constFactori = 1.0 / 0.80505 ;
   double a1 = 13.5   ;
   double a2 =  0.976 ;
   double a3 =  0.437 ;
   double b1 =  1.000 ;
   double b2 =  0.510 ;
   double b3 =  0.126 ;
   double c1 =  1.555e4 ;
   double c2 =  0.04319 ;
   double c3 =  exp( 2.00001 ) ;
   double f1 =  0.88  ;
   double f2 = -0.16  ;
   double f3 =  0.2   ;
   double f4 =  0.67  ;
   double y  = log( 2.0 ) ;
   double aInverse = (b1 + y * ( b2 + y * b3 ) ) /
                     (a1 + y * ( a2 + y * a3 ) ) ;
   double fInverse = 1.0 / ( f1 + f2 * y + sqrt(y) * (f3 + f4 * y) ) ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < length ; i++ ) {
      double t   = pow( t52[ndx[i]], 0.4 ) ;
      double z   = zstar[i] ;
      double za  = z / abar[i]  ;
      double zsq = z * z ;
      double denmax = MAX( cden[i], 1.0e-10 ) ;
      double coulombLog =
             0.5 * log( c3 + ( c1 * t * t * t /
                               (denmax * za * (c2 * zsq + t)) ) ) ;
      coef[i] = constFactori * zsq * zsq * coulombLog *
                sqrt( abar[i] ) * aInverse * fInverse / t52[ndx[i]] ;
   }
   myflops += 53.0 * length ;
   FT_FINALIZE(me, domain->hash, myflops)
}
