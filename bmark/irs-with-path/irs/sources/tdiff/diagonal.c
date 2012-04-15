#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "irsbndry.h"
#include "irscom.h"
#include "DiffusionData.h"
#include "FunctionTimer.h" 
#include "RadiationData.h"
void diagonal( RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain,
               double dtrad, double depositionFraction )
{
   char *me = "diagonal";
   int i, ir, j ;
   int *ndx, *ndxmix, *grdmix ;
   double *rccr ;
   double *rcfl ;
   double *rcfc ;
   double *rcfr ;
   double *rubl ;
   double *rubc ;
   double *rubr ;
   double *rucl ;
   double *rucc ;
   double *rucr ;
   double *rufl ;
   double *rufc ;
   double *rufr ;
   double *sie  ;
   double dtn, tm3, sbc4, vf, omega, sbci, temp ;
   int     nnalls  = domain->nnalls  ;
   int     nmixzn  = domain->nmixzn  ;
   int    *grdzn   = domain->grdzn   ;
   double *den     = domain->den     ;
   double *tmat    = domain->tmat    ;
   double *tion    = domain->tion    ;
   double *dedt    = domain->dedt    ;
   double *deidt   = domain->deidt   ;
   double *vol     = domain->vol     ;
   double *ematsrc = domain->ematsrc ;
   double *eionsrc = domain->eionsrc ;
   double *phi   = tblk->phi   ;
   double *esrc  = tblk->esrc  ;
   double *alpha = tblk->alpha ;
   double *beta  = tblk->beta  ;
   double *gamma = tblk->gamma ;
   double *phim  = tblk->phim  ;
   double *rcm3t = tblk->rcm3t ;
   double *xplnk = tblk->xplnk ;
   double *kie   = tblk->kie   ;
   double *rhs   = tblk->rhs   ;
   double myflops = 0.0; 
   FT_INITIALIZE(me, domain->hash)
   sbc4 = 4.0 * sbc ;
   sbci = 1.0 / sbc ;
   rccr = rblk->ccl + 1 ;
   rcfl = rblk->cbr + domain->jp - 1 ;   
   rcfc = rblk->cbc + domain->jp ;   
   rcfr = rblk->cbl + domain->jp + 1 ;   
   if ( ndims == 3 ) {
      rubl = rblk->dfr + domain->kp - domain->jp - 1 ;
      rubc = rblk->dfc + domain->kp - domain->jp ;
      rubr = rblk->dfl + domain->kp - domain->jp + 1 ;
      rucl = rblk->dcr + domain->kp - 1 ;
      rucc = rblk->dcc + domain->kp ;
      rucr = rblk->dcl + domain->kp + 1 ;
      rufl = rblk->dbr + domain->kp + domain->jp - 1 ;
      rufc = rblk->dbc + domain->kp + domain->jp ;
      rufr = rblk->dbl + domain->kp + domain->jp + 1 ;
   }
   dtn = -2.998e4 * dtrad ; 
   for ( i = 0 ; i < nnalls ; i++ ) {
      rblk->ccl[i] *= dtn ;
      rblk->cbr[i] *= dtn ;
      rblk->cbc[i] *= dtn ;
      rblk->cbl[i] *= dtn ;
   }
   myflops += 4.0 * nnalls ;
   if ( ndims == 3 ) {
      for ( i = 0 ; i < nnalls ; i++ ) {
         rblk->dfr[i] *= dtn ;
         rblk->dfc[i] *= dtn ;
         rblk->dfl[i] *= dtn ;
         rblk->dcr[i] *= dtn ;
         rblk->dcc[i] *= dtn ;
         rblk->dcl[i] *= dtn ;
         rblk->dbr[i] *= dtn ;
         rblk->dbc[i] *= dtn ;
         rblk->dbl[i] *= dtn ;
      }
      myflops += 9.0 * nnalls ;
   }
   if ( iftmode == 1 ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         ndx = domain->rndx[ir] ;
         for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
            i        = ndx[j] ;
            tmat[i]  = MAX( tmat[i], tfloor ) ;
            tm3      = tmat[i] * tmat[i] * tmat[i] ;
            omega    = sbc4 * xplnk[i] * tm3 ;
            temp     = 1.0 / ( den[i] * dedt[i] + omega + ptiny ) ;
            phim[i]  = tm3 * tmat[i] ;
            alpha[i] = den[i] * dedt[i] * xplnk[i] * temp ;
            esrc[i]  = den[i] * omega * depositionFraction * ematsrc[i]
                     * sbci * temp ;
         }
         myflops += 20.0 * domain->rlen[ir] ;
         if ( domain->rlenmix[ir] > 0 ) {
            ndxmix = domain->rndxmix[ir] ;
            grdmix = domain->rgrdmix[ir] ;
            for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
               j  = ndxmix[i] ;
               vf = vol[j]   ;
               alpha[grdmix[i]] += alpha[j] * vf ;
               phim[grdmix[i]]  += phim[j]  * vf * alpha[j] ;
               esrc[grdmix[i]]  += esrc[j]  * vf ;
	    }
            myflops += 7.0 * domain->rlenmix[ir] ;
	 }
      }
      for ( i = 0 ; i < nnalls ; i++ ) {
         rblk->ccc[i] = ( 1.0 + alpha[i] ) * vol[i] ;
         rblk->ccc[i] = MAX( rblk->ccc[i], ptiny ) ;
         rhs[i] = ( phi[i] + esrc[i] + alpha[i] * phim[i] ) * vol[i] ;
      }
      myflops += 6.0 * nnalls ;
   }
   if ( iftion == 1 ) {
      sie = ALLOT(double,domain->namix) ;
      geteicouple( kie, tmat, den, eifrac*dtrad, domain ) ;
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         ndx = domain->rndx[ir] ;
         for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
            i        = ndx[j] ;
            temp     = dedt[i] * kie[i]
                     / ( deidt[i] + dedt[i] * kie[i] + ptiny ) ;
            gamma[i] = den[i] * depositionFraction
                     * ( temp * eionsrc[i] + ematsrc[i] ) ;
            beta[i]  = den[i] * deidt[i] * temp ;
            tmat[i]  = MAX( tmat[i], tfloor ) ;
            tion[i]  = MAX( tion[i], tfloor ) ;
            tm3      = tmat[i] * tmat[i] * tmat[i] ;
            omega    = sbc4 * xplnk[i] * tm3 ;
            phim[i]  = tm3 * tmat[i] ;
            rcm3t[i] = 1.0 / ( den[i] * dedt[i] + beta[i] + omega + ptiny ) ;
            alpha[i] = rcm3t[i] * ( den[i] * dedt[i] + beta[i] ) * xplnk[i] ;
            sie[i]   = rcm3t[i] * 4.0 * tm3 * xplnk[i] * beta[i] *
                       ( tion[i] - tmat[i] ) ;
            esrc[i]  = omega * gamma[i] * rcm3t[i] * sbci ;
         }
         myflops += 40.0 * domain->rlen[ir] ;
         if ( domain->rlenmix[ir] > 0 ) {
            ndxmix = domain->rndxmix[ir] ;
            grdmix = domain->rgrdmix[ir] ;
            for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
               j  = ndxmix[i] ;
               vf = vol[j]   ;
               alpha[grdmix[i]] += alpha[j] * vf ;
               phim[grdmix[i]]  += phim[j]  * vf * alpha[j] ;
               sie[grdmix[i]]   += sie[j]   * vf ;
               esrc[grdmix[i]]  += esrc[j]  * vf ;
	    }
            myflops += 9.0 * domain->rlenmix[ir] ;
	 }
      }
      for ( i = 0 ; i < nnalls ; i++ ) {
         rblk->ccc[i] = ( 1.0 + alpha[i] ) * vol[i] ;
         rblk->ccc[i] = MAX( rblk->ccc[i], ptiny ) ;
         rhs[i]  = ( phi[i] + sie[i] + esrc[i] + alpha[i] * phim[i] ) 
	   * vol[i] ;
      }
      myflops += 7.0 * nnalls ;
      FREEMEM(sie) ;
   }
   rsrcbc( rblk, tblk, domain ) ;
   setphony( phi, 0.0, domain ) ;
   setphony( rhs, 0.0, domain ) ;
   rdiffbc( rblk, tblk, domain ) ;
   for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
      rblk->ccc[i] -= rblk->cbl[i] + rblk->cbc[i] + rblk->cbr[i] +
                      rblk->ccl[i]                +      rccr[i] + 
                           rcfl[i] +      rcfc[i] +      rcfr[i] ;
   }
   myflops += 8.0 * ( domain->lrz - domain->frz + 1 ) ;
   if ( ndims == 3 ) {
      for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
         rblk->ccc[i] -= rblk->dbl[i] + rblk->dbc[i] + rblk->dbr[i] +
                         rblk->dcl[i] + rblk->dcc[i] + rblk->dcr[i] + 
                         rblk->dfl[i] + rblk->dfc[i] + rblk->dfr[i] +
                              rubl[i] +      rubc[i] +      rubr[i] +
                              rucl[i] +      rucc[i] +      rucr[i] + 
                              rufl[i] +      rufc[i] +      rufr[i] ;
      }
      myflops += 18.0 * ( domain->lrz - domain->frz + 1 ) ;
   }
   FT_FINALIZE(me, domain->hash, myflops) 
}
