#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "irsbndry.h"
#include "irscom.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void MatterDiagonal(RadiationData_t *rblk, DiffusionData_t *tblk,
		    double *dedt, Domain_t *domain, double dtrad)
{
   char *me = "MatterDiagonal";
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
   double *vol     = domain->vol     ;
   double *phi   = tblk->phi   ;
   double *xplnk = tblk->xplnk ;
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
   dtn = - dtrad ; 
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
   for ( i = 0 ; i < nnalls ; i++ ) {
     rblk->ccc[i] = den[i] * dedt[i] * vol[i] ;
     rblk->ccc[i] = MAX( rblk->ccc[i], ptiny ) ;
     rhs[i] =  phi[i] * rblk->ccc[i];
   }
   myflops += 6.0 * nnalls ;
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
#include "irs.h"
#include "irscom.h"
void MatterUpdateTemperature(double dtrad, double *newTemperature,
			     double *conductivity, double *energy,
			     double *temperature, double *heatCapacity,
			     Domain_t *domain )
{
   char *me = "MatterUpdateTemperature";
   int i, j, ir ;
   int *ndxmix, *grdmix, *ndx ;
   double de, wm, delm, cvbar ;
   int     nmixzn  = domain->nmixzn  ;
   int    *grdzn   = domain->grdzn   ;
   double *den     = domain->den     ;
   double *vol     = domain->vol     ;
   double *weight  = MALLOT(double, domain->namix);
   double myflops = 0.0; 
   FT_INITIALIZE(me, domain->hash)
   setphony( weight, 0.0, domain ) ;
   setphony( temperature, 0.0, domain ) ;
   setphony( newTemperature,  0.0, domain ) ;
   for (i = domain->frz ; i <= domain->lrz ; i++){
     newTemperature[i] = MAX(tfloor, newTemperature[i]);
     newTemperature[i] = heatCapacity[i] * 
                     (newTemperature[i] - temperature[i]);
     weight[i]      = 0.;
   }
   FREEMEM(weight);
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
     ndx = domain->rndx[ir] ;
     for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
       i = ndx[j] ;
       de       = newTemperature[i];
       energy[i] += de ;
       temperature[i] += de / ( heatCapacity[i] + ptiny ) ;
       temperature[i] = MAX( temperature[i], tfloor ) ;
     }
     myflops += 29.0 * domain->rlen[ir] ;
   }
   if ( nmixzn ) {
      for ( i = 0 ; i < nmixzn ; i++ ) {
         energy[grdzn[i]] = 0.0 ;
         temperature[grdzn[i]] = 0.0 ;
         heatCapacity[grdzn[i]] = 0.0 ;
      }
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         if ( domain->rlenmix[ir] > 0 ) {
            ndxmix = domain->rndxmix[ir] ;
            grdmix = domain->rgrdmix[ir] ;
            for ( i = 0 ; i < domain->rlenmix[ir] ; i++ ) {
               wm               = den[ndxmix[i]]  * vol[ndxmix[i]] ;
               energy[grdmix[i]] += energy[ndxmix[i]] * wm ;
               temperature[grdmix[i]] += 
		 temperature[ndxmix[i]] * heatCapacity[ndxmix[i]] * wm ;
               heatCapacity[grdmix[i]] += heatCapacity[ndxmix[i]] * wm ;
            }
            myflops += 8.0 * domain->rlenmix[ir] ;
	 }
      }
      for ( i = 0 ; i < nmixzn ; i++ ) {
         temperature[grdzn[i]] /= ( heatCapacity[grdzn[i]] + ptiny ) ;
         temperature[grdzn[i]]  = MAX( temperature[grdzn[i]], tfloor ) ;
      }
      myflops += 5.0 * nmixzn ;
      for ( i = 0 ; i < nmixzn ; i++ ) {
         delm              = 1.0 / ( den[grdzn[i]] + ptiny ) ;
         energy[grdzn[i]] *= delm ;
         heatCapacity[grdzn[i]] *= delm ;
      }
      myflops += 7.0 * nmixzn ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
