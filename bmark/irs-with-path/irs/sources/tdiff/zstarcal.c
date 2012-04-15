#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void zstarcal( double *den, double *tmat, Domain_t *domain )
{
   char *me = "zstarcal";
   int i, ir, j ;
   int *ndx, *ndxmix, *grdmix, n ;
   double dm ;
   double *z23bar, *wgt ;
   double *zstar = domain->zstar;
   double *cdzdr, *cdzdt ;
   double myflops = 0.0;
   int     derivs = 0 ;
   cdzdr = NULL ;
   cdzdt = NULL ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->namix ; i++ ) {
      zstar[i] = 0.0 ;
   }
   for ( ir = 1 ; ir <= nreg ;ir++ ) {
      ndx    = domain->rndx[ir]     ;
      ndxmix = domain->rndxmix[ir]  ;
      grdmix = domain->rgrdmix[ir]  ;
      n      = domain->rlen[ir]     ;
      if ( n > 0 ) {
         int numGroups  = reg[ir].numGroups ;
         double *cden   = MALLOT(double,n)  ;
         double *volFrac ; 
	 for ( j = 0 ; j < numGroups ; j++ ) {
            RegionTable_t regionTable =
                          domain->domainRegions[ir].regionTables[j] ;
            int     form         = reg[ir].eosGroup[j].zstarform ;
	    double *abar         = regionTable.a ;
            double *zbar         = regionTable.z ;
	    double *czstar       = regionTable.zstar;
	    double *atomFraction = regionTable.atomFrac ;
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
            if ( form == 0 ) {
               for ( i = 0 ; i < n ; i++ ) {
                  czstar[i] = zbar[i] ;
	       }
            } else if ( form == 1 ) {
               gettfzstar( cden, czstar, tmat, abar, zbar, ndx, n, domain ) ;
	    } 
            for ( i = 0 ; i < n ; i++ ) {
	       zstar[ndx[i]] += atomFraction[i] * czstar[i] ;
	    }
	 }
         FREEMEM(cden)   ;
         n = domain->rlenmix[ir] ;
         for ( i = 0 ; i < n ; i++ ) {
            dm = domain->vol[ndxmix[i]] * domain->den[ndxmix[i]] ;
            zstar[grdmix[i]] += zstar[ndxmix[i]] * dm ;
         }
         myflops += 3.0 * n ;
      }
   }
   if ( domain->nmixzn  > 0 ) {
      for ( i = 0 ; i < domain->nmixzn ; i++ ) {
         zstar[domain->grdzn[i]] = zstar[domain->grdzn[i]] /
                                   ( domain->den[domain->grdzn[i]] + ptiny ) ;
      }
      myflops += 5.0 * domain->nmixzn ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
