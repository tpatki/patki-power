#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void ChemPotCalc( double *den, double *tmat, Domain_t *domain )
{
   char *me = "ChemPotCalc" ;
   int i, ir, j, n, *ndx ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      ndx = domain->rndx[ir] ;
      n   = domain->rlen[ir] ;
      if ( n > 0 ) {
         int numGroups  = reg[ir].numGroups ;
         double *cden   = MALLOT(double,n)  ;
         double *ctmat  = MALLOT(double,n)  ;
         double *volFrac ; 
	 for ( j = 0 ; j < numGroups ; j++ ) {
            RegionTable_t regionTable =
                          domain->domainRegions[ir].regionTables[j] ;
	    double *abar         = regionTable.a ;
	    double *zstar        = regionTable.zstar ;
            double *mu           = regionTable.chemicalPotential ;
            double *massFraction = regionTable.massFrac ;
            if ( numGroups == 1 ) {
               for ( i = 0 ; i < n ; i++ ) {
                  cden[i] = den[ndx[i]] ;
	       }
            } else {
               volFrac = domain->eosvf + j * domain->namix ;
               for ( i = 0 ; i < n ; i++ ) {
                  cden[i] = massFraction[i] * den[ndx[i]] /
                            ( volFrac[ndx[i]] + ptiny ) ;
	       }
               myflops += 6.0 * n ;
	    }
            for ( i = 0 ; i < n ; i++ ) {
               ctmat[i] = MAX( tmat[ndx[i]], tfloor ) ;
	    }
            ChemPot_fm1( mu, cden, ctmat, zstar, abar, n, domain ) ;
	 }
         FREEMEM(cden)  ;
         FREEMEM(ctmat) ;
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
void ChemPot_fm1( double *mu,   double *den,  double *tmat, double *zstar,
                  double *abar, int n, Domain_t *domain )
{
   char *me = "ChemPot_fm1" ;
   int i ;
   double z, za, ef, x, zeta, denmax ;
   double myflops = 0.0, twothirds = 2.0 / 3.0 ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < n ; i++ ) {
      z  = MAX( 0.01, zstar[i] ) ;
      za = z / abar[i] ;
      denmax = MAX( den[i], 1.0e-10 ) ;
      ef     = 0.026012 * pow( za * denmax, twothirds ) ;
      x    = sqrt( ef / tmat[i] ) ;
      zeta = ( 0.7531 + x * (0.1679 + x * 0.3108) ) * x * x * x
           / ( 1.0 + x * (0.2676 + x * (0.2280 + x * 0.3099) ) ) ;
      mu[i] = tmat[i] * ( zeta + log( 1.0 - exp(-zeta) ) ) ;
   }
   myflops += 67.0 * n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
