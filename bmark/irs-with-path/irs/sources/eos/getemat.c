#include "irs.h"
#include "irsreg.h"
#include "irseos.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void getemat( double *emat,  double *eion, double *e_cold, double *dedt,
              double *deidt, double *den,  double *tmat,   double *tion,
              double timestep, int ifgen,  Domain_t *domain )
{
   char *me = "getemat";
   int i, ir, *ndx, n, number, index ;
   int ieos, fm ;
   double rr, t, refd ;
   double *data, *abar, *zbar ;
   int lenx, clenx ;
   int *cndx, *cnvg, *indx, *rzon ;
   double *cmf, *fe, *fi, *csave ;
   int ifmeos ;    
   int *wcnvg = NULL ; 
   Thermo_t ceos ;     
   Thermo_t deos ;     
   Thermo_t weos ;     
   int namix  = domain->namix  ;
   int nmixzn = domain->nmixzn ;
   int *grdzn = domain->grdzn  ;
   FT_INITIALIZE(me, domain->hash)
   THERMO_NULL(ceos) ;
   THERMO_NULL(deos) ;
   THERMO_NULL(weos) ;
   ifmeos = 0 ;
   lenx   = 0 ;
   clenx  = 0 ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      int myneos = reg[ir].numGroups ;
      int len  = domain->rlen[ir]  ;
      lenx = MAX( len, lenx ) ;
      if ( myneos > 1 ) {
         clenx  = MAX( clenx, (myneos*len) ) ;
         ifmeos = 1 ;
      }
   }
   fe          = MALLOT(double,lenx) ;
   fi          = MALLOT(double,lenx) ;
   csave       = MALLOT(double,lenx) ;
   weos.p      = MALLOT(double,lenx) ;
   weos.dpdr   = MALLOT(double,lenx) ;
   weos.dpdt   = MALLOT(double,lenx) ;
   weos.dedr   = MALLOT(double,lenx) ;
   weos.dedt   = MALLOT(double,lenx) ;
   weos.den    = MALLOT(double,lenx) ;
   weos.emat   = MALLOT(double,lenx) ;
   weos.tmat   = MALLOT(double,lenx) ;
   weos.cs2    = MALLOT(double,lenx) ;
   weos.dpde   = MALLOT(double,lenx) ;
   weos.dtde   = MALLOT(double,lenx) ;
   weos.cs     = MALLOT(double,lenx) ;
   weos.work1    = MALLOT(double,lenx) ;
   weos.work2   = MALLOT(double,lenx) ;
   weos.p_cold = MALLOT(double,lenx) ;
   weos.e_cold = MALLOT(double,lenx) ;
   weos.dtlast = MALLOT(double,lenx) ;
   wcnvg       = MALLOT(int,lenx)    ;
   if ( iftion == 1 ) {
      weos.pion   = MALLOT(double,lenx) ;
      weos.deidti = MALLOT(double,lenx) ;
      weos.eion   = MALLOT(double,lenx) ;
      weos.tion   = MALLOT(double,lenx) ;
   }
   if ( ifmeos == 1 ) {
      cndx = MALLOT(int,lenx) ;
      cnvg = MALLOT(int,lenx) ;
      indx = MALLOT(int,lenx) ;
      rzon = MALLOT(int,lenx) ;
      cmf       = MALLOT(double,clenx) ;
      ceos.p    = MALLOT(double,clenx) ;
      ceos.dpdr = MALLOT(double,clenx) ;
      ceos.dpde = MALLOT(double,clenx) ;
      ceos.dpdt = MALLOT(double,clenx) ;
      ceos.dtdr = MALLOT(double,clenx) ;
      ceos.dtde = MALLOT(double,clenx) ;
      ceos.drdp = MALLOT(double,clenx) ;
      ceos.drde = MALLOT(double,clenx) ;
      ceos.drdt = MALLOT(double,clenx) ;
      ceos.dedp = MALLOT(double,clenx) ;
      ceos.dedr = MALLOT(double,clenx) ;
      ceos.dedt = MALLOT(double,clenx) ;
      ceos.den  = MALLOT(double,clenx) ;
      ceos.emat = MALLOT(double,clenx) ;
      ceos.tmat = MALLOT(double,clenx) ;
      ceos.cs2  = MALLOT(double,clenx) ;
      ceos.delast = MALLOT(double,clenx) ;
      ceos.drlast = MALLOT(double,clenx) ;
      ceos.abar  = MALLOT(double,clenx) ;
      ceos.zbar  = MALLOT(double,clenx) ;
      ceos.zstar = MALLOT(double,clenx) ;
      if ( iftion == 1  ||  if_eos_mix_zeq == 1 ) {
         ceos.pion   = MALLOT(double,clenx) ;
         ceos.dpidr  = MALLOT(double,clenx) ;
         ceos.dpidei = MALLOT(double,clenx) ;
         ceos.dpidti = MALLOT(double,clenx) ;
         ceos.dtidr  = MALLOT(double,clenx) ;
         ceos.dedti  = MALLOT(double,clenx) ;
         ceos.deidp  = MALLOT(double,clenx) ;
         ceos.deidr  = MALLOT(double,clenx) ;
         ceos.deidti = MALLOT(double,clenx) ;
         ceos.deidte = MALLOT(double,clenx) ;
         ceos.dtidei = MALLOT(double,clenx) ;
         ceos.dtedei = MALLOT(double,clenx) ;
         ceos.drdti  = MALLOT(double,clenx) ;
         ceos.eion   = MALLOT(double,clenx) ;
         ceos.tion   = MALLOT(double,clenx) ;
         ceos.e_cold = MALLOT(double,clenx) ;
         ceos.p_cold = MALLOT(double,clenx) ;
         ceos.dp_cdr = MALLOT(double,clenx) ;
         ceos.deilast = MALLOT(double,clenx) ;
         ceos.tdedte  = MALLOT(double,lenx) ;
         ceos.tdedti  = MALLOT(double,lenx) ;
         ceos.tdedp   = MALLOT(double,lenx) ;
         ceos.tdeidte = MALLOT(double,lenx) ;
         ceos.tdeidti = MALLOT(double,lenx) ;
         ceos.tdeidp  = MALLOT(double,lenx) ;
         ceos.tdrdte  = MALLOT(double,lenx) ;
         ceos.tdrdti  = MALLOT(double,lenx) ;
         ceos.tdrdp   = MALLOT(double,lenx) ;
      }
   }
   deos.dpdr   = MALLOT(double,namix) ;
   deos.dpdt   = MALLOT(double,namix) ;
   deos.dedr   = MALLOT(double,namix) ;
   deos.dedt   = dedt   ;
   deos.den    = den    ;
   deos.emat   = emat   ;
   deos.tmat   = tmat   ;
   deos.e_cold = e_cold ;
   deos.zstar  = domain->zstar ;
   if ( iftion == 1 ) {
      deos.dpidr  = MALLOT(double,namix) ;
      deos.dpidti = MALLOT(double,namix) ;
      deos.deidr  = MALLOT(double,namix) ;
      deos.deidti = deidt  ;
      deos.eion   = eion   ;
      deos.tion   = tion   ;
   }
   if ( ioneq == 1 ) {
      zstarcal( den, tmat, domain ) ;
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      if ( domain->rlen[ir] > 0 ) {
         if ( reg[ir].numGroups <= 1 ) {
            abar = domain->domainRegions[ir].regionTables[0].a ;
            zbar = domain->domainRegions[ir].regionTables[0].z ;
            getematnomix( emat, eion, e_cold,  dedt, deidt, 
                          den,  tmat, tion,    abar, zbar,
                          domain->rndx[ir], domain->rlen[ir], ifgen, domain, ir, 0 ) ;
         } 
      }
   }
   if ( ifmeos == 1 ) {
      FREEMEM(cndx) ;
      FREEMEM(cnvg) ;
      FREEMEM(indx) ;
      FREEMEM(rzon) ;
      FREEMEM(cmf) ;
      FREEMEM(ceos.p)    ;
      FREEMEM(ceos.dpdr) ;
      FREEMEM(ceos.dpde) ;
      FREEMEM(ceos.dpdt) ;
      FREEMEM(ceos.dtdr) ;
      FREEMEM(ceos.dtde) ;
      FREEMEM(ceos.dedp) ;
      FREEMEM(ceos.dedr) ;
      FREEMEM(ceos.dedt) ;
      FREEMEM(ceos.drdp) ;
      FREEMEM(ceos.drde) ;
      FREEMEM(ceos.drdt) ;
      FREEMEM(ceos.den)  ;
      FREEMEM(ceos.emat) ;
      FREEMEM(ceos.tmat) ;
      FREEMEM(ceos.cs2)  ;
      FREEMEM(ceos.delast) ;
      FREEMEM(ceos.drlast) ;
      FREEMEM(ceos.abar) ;
      FREEMEM(ceos.zbar) ;
      FREEMEM(ceos.zstar);
      if ( iftion == 1  ||  if_eos_mix_zeq == 1 ) {
         FREEMEM(ceos.pion)   ;
         FREEMEM(ceos.dpidr)  ;
         FREEMEM(ceos.dpidei) ;
         FREEMEM(ceos.dpidti) ;
         FREEMEM(ceos.dtidr)  ;
         FREEMEM(ceos.dedti)  ;
         FREEMEM(ceos.deidp)  ;
         FREEMEM(ceos.deidr)  ;
         FREEMEM(ceos.deidti) ;
         FREEMEM(ceos.deidte) ;
         FREEMEM(ceos.dtidei) ;
         FREEMEM(ceos.dtedei) ;
         FREEMEM(ceos.drdti)  ;
         FREEMEM(ceos.eion)   ;
         FREEMEM(ceos.tion)   ;
         FREEMEM(ceos.e_cold) ;
         FREEMEM(ceos.p_cold) ;
         FREEMEM(ceos.dp_cdr) ;
         FREEMEM(ceos.deilast) ;
         FREEMEM(ceos.tdedte)  ;
         FREEMEM(ceos.tdedti)  ;
         FREEMEM(ceos.tdedp)   ;
         FREEMEM(ceos.tdeidte) ;
         FREEMEM(ceos.tdeidti) ;
         FREEMEM(ceos.tdeidp)  ;
         FREEMEM(ceos.tdrdte)  ;
         FREEMEM(ceos.tdrdti)  ;
         FREEMEM(ceos.tdrdp)   ;
      }
   }
   FREEMEM(fe)          ;
   FREEMEM(fi)          ;
   FREEMEM(csave)       ;
   FREEMEM(weos.p)      ;
   FREEMEM(weos.dpdr)   ;
   FREEMEM(weos.dpdt)   ;
   FREEMEM(weos.dedr)   ;
   FREEMEM(weos.dedt)   ;
   FREEMEM(weos.den)    ;
   FREEMEM(weos.emat)   ;
   FREEMEM(weos.tmat)   ;
   FREEMEM(weos.cs2)    ;
   FREEMEM(weos.dpde)   ;
   FREEMEM(weos.dtde)   ;
   FREEMEM(weos.cs)     ;
   FREEMEM(weos.work1)    ;
   FREEMEM(weos.work2)   ;
   FREEMEM(weos.p_cold) ;
   FREEMEM(weos.e_cold) ;
   FREEMEM(weos.dtlast) ;
   FREEMEM(deos.dpdr)   ;
   FREEMEM(deos.dpdt)   ;
   FREEMEM(deos.dedr)   ;
   FREEMEM(wcnvg) ;
   if ( iftion == 1 ) {
      FREEMEM(weos.pion)   ;
      FREEMEM(weos.deidti) ;
      FREEMEM(weos.eion)   ;
      FREEMEM(weos.tion)   ;
      FREEMEM(deos.dpidr)  ;
      FREEMEM(deos.dpidti) ;
      FREEMEM(deos.deidr)  ;
   }
   FT_FINALIZE(me, domain->hash, 1)
}
