#include "irsdefs.h"
#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void geteicouple( double *rate, double *tmat, double *den, double dtcup,
                  Domain_t *domain )
{
   char *me = "geteicouple";
   int ir, i ;
   int *ndxmix, *grdmix ;
   double myflops = 0.0; 
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->namix ; i++ ) {
      rate[i] = 0.0 ;
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      int j ;
      int length = domain->rlen[ir] ;
      if ( length > 0 ) {
         int *ndx      = domain->rndx[ir]  ;
         int numGroups = reg[ir].numGroups ;
         double *crate = MALLOT(double,length) ;
         double *cden  = MALLOT(double,length) ;
         double *volFrac ;
         for ( j = 0 ; j < numGroups ; j++ ) {
            RegionTable_t regionTable =
                          domain->domainRegions[ir].regionTables[j] ;
            double eicouplemlt   = reg[ir].eosGroup[j].eicoupleMultiplier ;
            double *zstar        = regionTable.zstar ;
            double *abar         = regionTable.a ;
            double *mu           = regionTable.chemicalPotential ;
            double *massFraction = regionTable.massFrac ;
            if ( numGroups == 1 ) {
               for ( i = 0 ; i < length ; i++ ) {
                  cden[i] = den[ndx[i]] ;
	       }
            } else {
               volFrac = domain->eosvf + j * domain->namix ;
               for ( i = 0 ; i < length ; i++ ) {
                  cden[i] = massFraction[i] * den[ndx[i]] /
                            ( volFrac[ndx[i]] + ptiny ) ;
	       }
               myflops += 6.0 * length ;
	    }
            reicouple( crate, cden,  tmat, ndx, length, zstar, abar, mu,
                       eicouplemlt, dtcup, domain ) ;
            if ( numGroups == 1 ) {
               for ( i = 0 ; i < length ; i++ ) {
                  rate[ndx[i]] = crate[i] ;
	       }
            } else {
               for ( i = 0 ; i < length ; i++ ) {
                  rate[ndx[i]] += massFraction[i] * crate[i] ;
	       }
               myflops += 2.0 * length ;
	    }
         }
         FREEMEM(crate) ;
         FREEMEM(cden)  ;
         if ( domain->rlenmix[ir] > 0 ) {
            grdmix = domain->rgrdmix[ir] ;
            ndxmix = domain->rndxmix[ir] ;
            for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
               rate[grdmix[i]] += rate[ndxmix[i]] * domain->vol[ndxmix[i]] ;
            }
            myflops += 2.0 * domain->rlenmix[ir] ;
         }
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
