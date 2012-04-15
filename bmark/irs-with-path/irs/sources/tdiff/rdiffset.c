#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rdiffset(Domain_t *domain, double dtrad )
{
   char *me = "rdiffset";
   int i, ibc, len, dir, ir ;
   int *ndx, *ndxmix, *grdmix ;
   double wm ;
   double *tmat, *trad ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
      dir = domain->bc[ibc].pn ;
      if ( dir != 0 ) {
         len  = domain->bc[ibc].len ;
         ndx  = domain->bc[ibc].ndx ;
         tmat = domain->tmat + domain->bc[ibc].pz ;
         for ( i = 0 ; i < len ; i++ ) {
            tmat[ndx[i]] = tfloor ;
         }
      }
   }
   if ( domain->nmixzn ) {
      for ( i = 0 ; i < domain->nmixzn ; i++ ) {
         domain->tmat[domain->grdzn[i]] = 0.0 ;
         domain->dedt[domain->grdzn[i]] = 0.0 ;
      }
      if ( iftion == 1 ) {
         for ( i = 0 ; i < domain->nmixzn ; i++ ) {
            domain->tion[domain->grdzn[i]]  = 0.0 ;
            domain->deidt[domain->grdzn[i]] = 0.0 ;
         }
      }
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         if ( domain->rlenmix[ir] > 0 ) {
            ndxmix = domain->rndxmix[ir] ;
            grdmix = domain->rgrdmix[ir] ;
            for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
               wm                = domain->den[ndxmix[i]]  * domain->vol[ndxmix[i]] ;
               domain->tmat[grdmix[i]] += domain->tmat[ndxmix[i]] * domain->dedt[ndxmix[i]] * wm ;
               domain->dedt[grdmix[i]] += domain->dedt[ndxmix[i]] * wm ;
            }
            myflops += 6.0 * domain->rlenmix[ir] ;
            if ( iftion == 1 ) {
               for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
                  wm                 = domain->den[ndxmix[i]] * domain->vol[ndxmix[i]] ;
                  domain->tion[grdmix[i]]  += domain->tion[ndxmix[i]]* domain->deidt[ndxmix[i]]* wm ;
                  domain->deidt[grdmix[i]] += domain->deidt[ndxmix[i]] * wm ;
               }
               myflops += 6.0 * domain->rlenmix[ir] ;
	    }
	 }
      }
      for ( i = 0 ; i < domain->nmixzn ; i++ ) {
         domain->tmat[domain->grdzn[i]] /= ( domain->dedt[domain->grdzn[i]] + ptiny ) ;
      }
      myflops += 5.0 * domain->nmixzn ;
      for ( i = 0 ; i < domain->nmixzn ; i++ ) {
         domain->dedt[domain->grdzn[i]] /= ( domain->den[domain->grdzn[i]] + ptiny ) ;
      }
      myflops += 5.0 * domain->nmixzn ;
      if ( iftion == 1 ) {
         for ( i = 0 ; i < domain->nmixzn ; i++ ) {
            domain->tion[domain->grdzn[i]] /= ( domain->deidt[domain->grdzn[i]] + ptiny ) ;
         }
         myflops += 5.0 * domain->nmixzn ;
         for ( i = 0 ; i < domain->nmixzn ; i++ ) {
            domain->deidt[domain->grdzn[i]] /= ( domain->den[domain->grdzn[i]] + ptiny ) ;
         }
         myflops += 5.0 * domain->nmixzn ;
      }
   }
   gtkappabnd(domain, dtrad ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
