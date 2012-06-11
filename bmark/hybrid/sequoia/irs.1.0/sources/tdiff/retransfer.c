#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "irsbndry.h"
#include "irscom.h"
#include "FunctionTimer.h"
#include "DiffusionData.h"
void retransfer( double dtrad, double depositionFraction,
                 DiffusionData_t *tblk, Domain_t *domain )
{
   char *me = "retransfer";
   int i, j, ir ;
   int *ndxmix, *grdmix, *ndx ;
   double de, wm, delm, cvbar ;
   double myflops = 0.0;
   int     nmixzn  = domain->nmixzn  ;
   int    *grdzn   = domain->grdzn   ;
   double *den     = domain->den     ;
   double *emat    = domain->emat    ;
   double *eion    = domain->eion    ;
   double *erad    = domain->erad    ;
   double *tmat    = domain->tmat    ;
   double *tion    = domain->tion    ;
   double *trad    = domain->trad    ;
   double *dedt    = domain->dedt    ;
   double *deidt   = domain->deidt   ;
   double *vol     = domain->vol     ;
   double *ematsrc = domain->ematsrc ;
   double *eionsrc = domain->eionsrc ;
   double *phi   = tblk->phi   ;
   double *alpha = tblk->alpha ;
   double *beta  = tblk->beta  ;
   double *gamma = tblk->gamma ;
   double *phim  = tblk->phim  ;
   double *rcm3t = tblk->rcm3t ;
   double *xplnk = tblk->xplnk ;
   double *kie   = tblk->kie   ;
   FT_INITIALIZE(me, domain->hash)
   setphony( tmat, 0.0, domain ) ;
   setphony( phi,  0.0, domain ) ;
   if ( iftion == 1 ) {
      setphony( tion, 0.0, domain ) ;
   }
   if ( iftmode == 1 ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         ndx = domain->rndx[ir] ;
         for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
            i = ndx[j] ;
            erad[i] = phi[i] ;
            de       = alpha[i] * ( sbc * ( phi[i] - phim[i] ) / den[i] +
                                    depositionFraction * ematsrc[i] /
                                    ( xplnk[i] + ptiny ) ) ;
            emat[i] += de ;
            tmat[i] += de / ( dedt[i] + ptiny ) ;
            tmat[i] = MAX( tmat[i], tfloor )   ;
            erad[i] = MAX( erad[i], phifloor ) ;
            trad[i] = sqrt( sqrt( phi[i] ) ) ;
         }
         myflops += 29.0 * domain->rlen[ir] ;
      }
   }
   if ( iftion == 1 ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         ndx = domain->rndx[ir] ;
         for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
            i = ndx[j] ;
            erad[i] = phi[i] ;
            de       = dedt[i] * rcm3t[i] *
                       ( sbc * xplnk[i] * ( phi[i] - phim[i] )
                       + beta[i] * ( tion[i] - tmat[i] ) + gamma[i] ) ;
            emat[i] += de ;
            tmat[i] += de / ( dedt[i] + ptiny ) ;
            cvbar    = deidt[i] + dedt[i] * kie[i] + ptiny ;
            de       = ( deidt[i] / cvbar ) *
                       ( dedt[i] * kie[i] * ( tmat[i] - tion[i] ) + 
                         depositionFraction * eionsrc[i] ) ;
            eion[i] += de ;
            tion[i] += de / ( deidt[i] + ptiny ) ;
            tmat[i] = MAX( tmat[i], tfloor )   ;
            tion[i] = MAX( tion[i], tfloor )   ;
            erad[i] = MAX( erad[i], phifloor ) ;
            trad[i] = sqrt( sqrt( phi[i] ) ) ;
         }
         myflops += 43.0 * domain->rlen[ir] ;
      }
   }
   if ( nmixzn ) {
      for ( i = 0 ; i < nmixzn ; i++ ) {
         phi[grdzn[i]]  = MAX( phi[grdzn[i]], phifloor ) ;
         erad[grdzn[i]] = phi[grdzn[i]] ;
         trad[grdzn[i]] = sqrt( sqrt( phi[grdzn[i]] ) ) ;
      }
      myflops += 8.0 * nmixzn ;
   }
   if ( nmixzn ) {
      for ( i = 0 ; i < nmixzn ; i++ ) {
         emat[grdzn[i]] = 0.0 ;
         tmat[grdzn[i]] = 0.0 ;
         dedt[grdzn[i]] = 0.0 ;
      }
      if ( iftion == 1 ) {
         for ( i = 0 ; i < nmixzn ; i++ ) {
            eion[grdzn[i]]  = 0.0 ;
            tion[grdzn[i]]  = 0.0 ;
            deidt[grdzn[i]] = 0.0 ;
         }
      }
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         if ( domain->rlenmix[ir] > 0 ) {
            ndxmix = domain->rndxmix[ir] ;
            grdmix = domain->rgrdmix[ir] ;
            for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
               wm               = den[ndxmix[i]]  * vol[ndxmix[i]] ;
               emat[grdmix[i]] += emat[ndxmix[i]] * wm ;
               tmat[grdmix[i]] += tmat[ndxmix[i]] * dedt[ndxmix[i]] * wm ;
               dedt[grdmix[i]] += dedt[ndxmix[i]] * wm ;
            }
            myflops += 8.0 * domain->rlenmix[ir] ;
            if ( iftion == 1 ) {
               for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
                  wm                = den[ndxmix[i]]   * vol[ndxmix[i]] ;
                  eion[grdmix[i]]  += eion[ndxmix[i]]  * wm ;
                  tion[grdmix[i]]  += tion[ndxmix[i]]  * deidt[ndxmix[i]] * wm ;
                  deidt[grdmix[i]] += deidt[ndxmix[i]] * wm ;
               }
               myflops += 8.0 * domain->rlenmix[ir] ;
	    }
	 }
      }
      for ( i = 0 ; i < nmixzn ; i++ ) {
         tmat[grdzn[i]] /= ( dedt[grdzn[i]] + ptiny ) ;
         tmat[grdzn[i]]  = MAX( tmat[grdzn[i]], tfloor ) ;
      }
      myflops += 5.0 * nmixzn ;
      for ( i = 0 ; i < nmixzn ; i++ ) {
         delm              = 1.0 / ( den[grdzn[i]] + ptiny ) ;
         emat[grdzn[i]] *= delm ;
         dedt[grdzn[i]] *= delm ;
      }
      myflops += 7.0 * nmixzn ;
      if ( iftion == 1 ) {
         for ( i = 0 ; i < nmixzn ; i++ ) {
            tion[grdzn[i]] /= ( deidt[grdzn[i]] + ptiny ) ;
            tion[grdzn[i]]  = MAX( tion[grdzn[i]], tfloor ) ;
         }
         myflops += 5.0 * nmixzn ;
         for ( i = 0 ; i < nmixzn ; i++ ) {
            delm               = 1.0 / ( den[grdzn[i]] + ptiny ) ;
            eion[grdzn[i]]  *= delm ;
            deidt[grdzn[i]] *= delm ;
         }
         myflops += 7.0 * nmixzn ;
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
