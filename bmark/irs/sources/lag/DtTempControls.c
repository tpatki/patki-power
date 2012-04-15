#include "irs.h"
#include "irslag.h"
#include "irssys.h"
#include "irsreg.h"
#include "irsbndry.h"
#include "TimeStepControl.h"
#include "FunctionTimer.h"
#include "TimeStepControl.h"
void CalcDtTemp( Domain_t *domain )
{
   char *me = "CalcDtTemp";
   int i, j, dtndx, ir ;
   int *ndx ;
   double dte, mydti, dtr, dtrmnr, vfdenom, twovff ;
   double *deltmat, *deltion, *deltrad, *vffactor ;
   TimeStepControl_t *tsc;
   int imaxmix = domain->imaxmix ;
   int namix   = domain->namix   ;
   int nnalls  = domain->nnalls  ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   dtrmnr = dtrmin * dtrmin ;
   dtrmnr = dtrmnr * dtrmnr * 2.0 ;
   deltmat  = ALLOT(double,namix) ;
   vffactor = ALLOT(double,namix) ;
   if ( iftion == 1 ) {
      deltion = ALLOT(double,namix) ;
   }
   if ( ngroup > 0 ) {
      deltrad = ALLOT(double,namix) ;
   }
   for ( i = 0 ; i < nnalls ; i++ ) {
      vffactor[i] = 1.0 ;
   }
   for ( i = nnalls ; i < (nnalls + imaxmix) ; i++ ) {
      vfdenom     = MAX( domain->vol[i], vfdtmin ) ;
      vffactor[i] = domain->vol[i] / vfdenom ;
   }
   myflops += 4.0 * imaxmix ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      ndx = domain->rndx[ir] ;
      for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
         i = ndx[j] ;
         twovff     = 2.0 * vffactor[i] ;
         deltmat[i] = twovff *  fabs( domain->tmat[i] - domain->tmatold[i] ) /
	              ( domain->tmat[i] + domain->tmatold[i] +
		      2.0 * dtemin + ptiny ) ;
      }
      myflops += 15.0 * domain->rlen[ir] ;
   }
   if ( iftion == 1 ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         ndx = domain->rndx[ir] ;
         for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
            i = ndx[j] ;
            twovff     = 2.0 * vffactor[i] ;
            deltion[i] = twovff * fabs(domain->tion[i] - domain->tionold[i]) /
	                 ( domain->tion[i] + domain->tionold[i]
                         + 2.0 * dtimin + ptiny ) ;
         }
         myflops += 15.0 * domain->rlen[ir] ;
      }
   }
   if ( ngroup > 0 ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         ndx = domain->rndx[ir] ;
         for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
            i = ndx[j] ;
            twovff     = 2.0 * vffactor[i] ;
            deltrad[i] = twovff * fabs( domain->erad[i] - domain->eradold[i] ) /
                         ( domain->erad[i] + domain->eradold[i] + dtrmnr ) ;
         }
         myflops += 13.0 * domain->rlen[ir] ;
      }
   }
   setphony( deltmat, 0.0, domain ) ;
   if ( iftion == 1 ) {
      setphony( deltion, 0.0, domain ) ;
   }
   if ( ngroup > 0 ) {
      setphony( deltrad, 0.0, domain ) ;
   }
   dte = dtefc * deltatSubcycle
       / ( vmax( &dtndx, deltmat, namix ) + ptiny ) ;
   tsc = TimeStepControl_find("TSC_Electron",domain->hash) ;
   tsc->value = dte ;
   if ( dtndx >= nnalls ) {
      dtndx = domain->grdpnt[dtndx-nnalls] ;
   }
   if ( ndims == 3 ) {
      NDXEXT3D( dtndx, tsc->i, tsc->j, tsc->k, (*domain) ) ;
   } else {
      NDXEXT2D( dtndx, tsc->i, tsc->j , (*domain)) ;
   }
   if ( iftion == 1 ) {
      mydti = dtifc * deltatSubcycle
            / ( vmax( &dtndx, deltion, namix ) + ptiny ) ;
      tsc = TimeStepControl_find("TSC_Ion",domain->hash) ;
      tsc->value = mydti ;
      if ( dtndx >= nnalls ) {
         dtndx = domain->grdpnt[dtndx-nnalls] ;
      }
      if ( ndims == 3 ) {
         NDXEXT3D( dtndx, tsc->i, tsc->j, tsc->k , (*domain)) ;
      } else {
         NDXEXT2D( dtndx, tsc->i, tsc->j , (*domain)) ;
      }
   }
   if ( ngroup > 0 ) {
      dtr = dtrfc * deltatSubcycle
          / ( vmax( &dtndx, deltrad, namix ) + ptiny ) ;
      tsc = TimeStepControl_find("TSC_Radiation",domain->hash) ;
      tsc->value = dtr ;
      if ( dtndx >= nnalls ) {
         dtndx = domain->grdpnt[dtndx-nnalls] ;
      }
      if ( ndims == 3 ) {
         NDXEXT3D( dtndx, tsc->i, tsc->j, tsc->k , (*domain)) ;
      } else {
         NDXEXT2D( dtndx, tsc->i, tsc->j , (*domain)) ;
      }
   }
   FREEMEM(deltmat)  ;
   FREEMEM(vffactor) ;
   if ( iftion == 1 ) {
      FREEMEM(deltion)  ;
   }
   if ( ngroup > 0 ) {
      FREEMEM(deltrad)  ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
void CalcDtSource( Domain_t *domain )
{
   char *me = "CalcDtSource";
   int i, j, dtndx, ir ;
   int *ndx ;
   double dte, mydti, vfdenom ;
   double *deltmat, *deltion, *vffactor ;
   int     imaxmix = domain->imaxmix ;
   int     nnalls  = domain->nnalls  ;
   int     namix   = domain->namix   ;
   int     nmixzn  = domain->nmixzn  ;
   double *ematsrc = domain->ematsrc ;
   double *eionsrc = domain->eionsrc ;
   double *tmat    = domain->tmat    ;
   double *tion    = domain->tion    ;
   double *dedt    = domain->dedt    ;
   double *deidt   = domain->deidt   ;
   TimeStepControl_t *tsc;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   deltmat  = ALLOT(double,namix) ;
   vffactor = ALLOT(double,namix) ;
   if ( iftion == 1 ) {
      deltion = ALLOT(double,namix) ;
   }
   for ( i = 0 ; i < nnalls ; i++ ) {
      vffactor[i] = 1.0 ;
   }
   for ( i = nnalls ; i < (nnalls+imaxmix) ; i++ ) {
      vfdenom     = MAX( domain->vol[i], vfdtmin ) ;
      vffactor[i] = domain->vol[i] / vfdenom ;
   }
   myflops += 4.0 * imaxmix ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      ndx = domain->rndx[ir] ;
      for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
         i = ndx[j] ;
         deltmat[i] = vffactor[i] * ematsrc[i] /
                      ( dedt[i] * ( tmat[i] + dtsemin ) + ptiny ) ;
      }
      myflops += 8.0 * domain->rlen[ir] ;
   }
   if ( iftion == 1 ) {
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         double delta ;
         ndx = domain->rndx[ir] ;
         for ( j = 0 ; j < domain->rlen[ir] ; j++ ) {
            i = ndx[j] ;
            deltion[i] = vffactor[i] * eionsrc[i] /
                         ( deidt[i] * ( tion[i] + dtsimin ) + ptiny ) ;
         }
         myflops += 8.0 * domain->rlen[ir] ;
      }
   }
   setphony( deltmat, 0.0, domain ) ;
   if ( iftion == 1 ) {
      setphony( deltion, 0.0, domain ) ;
   }
   dte = dtsefc * deltat / ( vmax( &dtndx, deltmat, namix ) + ptiny ) ;
   tsc = TimeStepControl_find("TSC_ElectronSource",domain->hash) ;
   tsc->value = dte ;
   if ( dtndx >= nnalls ) {
      dtndx = domain->grdpnt[dtndx-nnalls] ;
   }
   if ( ndims == 3 ) {
      NDXEXT3D( dtndx, tsc->i, tsc->j, tsc->k, (*domain) ) ;
   } else {
      NDXEXT2D( dtndx, tsc->i, tsc->j , (*domain)) ;
   }
   if ( iftion == 1 ) {
      mydti = dtsifc * deltat / ( vmax( &dtndx, deltion, namix ) + ptiny ) ;
      tsc = TimeStepControl_find("TSC_IonSource",domain->hash) ;
      tsc->value = mydti ;
      if ( dtndx >= nnalls ) {
         dtndx = domain->grdpnt[dtndx-nnalls] ;
      }
      if ( ndims == 3 ) {
         NDXEXT3D( dtndx, tsc->i, tsc->j, tsc->k , (*domain)) ;
      } else {
         NDXEXT2D( dtndx, tsc->i, tsc->j , (*domain)) ;
      }
   }
   FREEMEM(deltmat)  ;
   FREEMEM(vffactor) ;
   if ( iftion == 1 ) {
      FREEMEM(deltion)  ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
