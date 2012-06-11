#include "irs.h"
#include "irsreg.h"
#include "irssrc.h"
#include "irseos.hh"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "Source.h"
#include "SpeciesFraction.h"
void geteos( double *p,    double *pion,   double *p_cold, double *cs2,
             double *dedt, double *deidt,  double *den,    double *emat,
             double *eion, double *e_cold, double *tmat,   double *tion,
             double *work3,  double *work1,    double *work2,   double  teos,
             double dt,    Domain_t *domain, SpeciesFraction_t *specfrac,
             int ifsource, int ifzstar )
{
   char *me = "geteos";
   int i, ir, n, lenx, clenx ;
   double ssmin2, fv ;
   int *cndx, *cnvg, *indx, *rzon ;
   double *cmf, *fe, *fi, *csave ;
   int ifmeos ;    
   int *wcnvg = NULL ; 
   Thermo_t ceos ;     
   Thermo_t deos ;     
   Thermo_t weos ;     
   int namix  = domain->namix  ;
   int nmixzn = domain->nmixzn ;
   int mynsrc = domain->nsrc   ;
   int *grdzn = domain->grdzn  ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   THERMO_NULL(ceos) ;
   THERMO_NULL(deos) ;
   THERMO_NULL(weos) ;
   ssmin2 = sndmin * sndmin ;
   if (ifsource == 1) {
      SourceNew_general( den, domain->vol, "SourceDensity", teos, domain, 
                        _SourceEdit_);
      SourceNew_general( emat, den, "SourceEnergy", teos, domain, 
                        _SourceEdit_);
      SourceNew_temperature( emat, tmat, dedt, den, 
                             "SourceElectronTemperature", teos, 
			      domain, _SourceNoEdit_);
      if ( iftion  == 1 ) {
         SourceNew_temperature( eion, tion, deidt, den, 
                                "SourceIonTemperature", teos, 
			         domain, _SourceNoEdit_);
      }
   }
   if ( (mynsrc > 0) && (ifsource == 1) ) {
      dsrc(  teos, den,  domain ) ;
      esrc(  teos, emat, domain ) ;
      tmsrc( teos, emat, tmat, dedt, 
                   eion, tion, deidt, domain ) ;
   }
   ifmeos = 0 ;
   lenx   = 0 ;
   clenx  = 0 ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      int locneos = reg[ir].numGroups ;
      int len     = domain->rlen[ir]  ;
      lenx = MAX( len, lenx ) ;
      if ( locneos > 1 ) {
         clenx  = MAX( clenx, (locneos*len) ) ;
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
      ceos.p      = MALLOT(double,clenx) ;
      ceos.dpdr   = MALLOT(double,clenx) ;
      ceos.dpde   = MALLOT(double,clenx) ;
      ceos.dpdt   = MALLOT(double,clenx) ;
      ceos.dtdr   = MALLOT(double,clenx) ;
      ceos.dtde   = MALLOT(double,clenx) ;
      ceos.drdp   = MALLOT(double,clenx) ;
      ceos.drde   = MALLOT(double,clenx) ;
      ceos.drdt   = MALLOT(double,clenx) ;
      ceos.dedp   = MALLOT(double,clenx) ;
      ceos.dedr   = MALLOT(double,clenx) ;
      ceos.dedt   = MALLOT(double,clenx) ;
      ceos.dedt_v = MALLOT(double,clenx) ;
      ceos.den    = MALLOT(double,clenx) ;
      ceos.emat   = MALLOT(double,clenx) ;
      ceos.tmat   = MALLOT(double,clenx) ;
      ceos.cs2    = MALLOT(double,clenx) ;
      ceos.delast = MALLOT(double,clenx) ;
      ceos.drlast = MALLOT(double,clenx) ;
      ceos.cdmin  = MALLOT(double,clenx) ;
      ceos.cdmax  = MALLOT(double,clenx) ;
      ceos.cpmin  = MALLOT(double,clenx) ;
      ceos.cpmax  = MALLOT(double,clenx) ;
      ceos.ceemin = MALLOT(double,clenx) ;
      ceos.ceemax = MALLOT(double,clenx) ;
      ceos.ctemin = MALLOT(double,clenx) ;
      ceos.ctemax = MALLOT(double,clenx) ;
      ceos.abar   = MALLOT(double,lenx) ;
      ceos.zbar   = MALLOT(double,lenx) ;
      if ( if_eos_mix_zeq == 1 ) {
         ceos.zstar = MALLOT(double,lenx) ;
      }
      if ( (iftion == 1) || (if_eos_mix_zeq == 1) ) {
         ceos.pion    = MALLOT(double,clenx) ;
         ceos.dpidr   = MALLOT(double,clenx) ;
         ceos.dpidei  = MALLOT(double,clenx) ;
         ceos.dpidti  = MALLOT(double,clenx) ;
         ceos.dtidr   = MALLOT(double,clenx) ;
         ceos.dedti   = MALLOT(double,clenx) ;
         ceos.deidp   = MALLOT(double,clenx) ;
         ceos.deidr   = MALLOT(double,clenx) ;
         ceos.deidti  = MALLOT(double,clenx) ;
         ceos.deidte  = MALLOT(double,clenx) ;
         ceos.deidt_v = MALLOT(double,clenx) ;
         ceos.dtidei  = MALLOT(double,clenx) ;
         ceos.dtedei  = MALLOT(double,clenx) ;
         ceos.drdti   = MALLOT(double,clenx) ;
         ceos.eion    = MALLOT(double,clenx) ;
         ceos.tion    = MALLOT(double,clenx) ;
         ceos.e_cold  = MALLOT(double,clenx) ;
         ceos.p_cold  = MALLOT(double,clenx) ;
         ceos.dp_cdr  = MALLOT(double,clenx) ;
         ceos.deilast = MALLOT(double,clenx) ;
         ceos.ceimin  = MALLOT(double,clenx) ;
         ceos.ceimax  = MALLOT(double,clenx) ;
         ceos.ctimin  = MALLOT(double,clenx) ;
         ceos.ctimax  = MALLOT(double,clenx) ;
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
   deos.p      = p      ;
   deos.dpdr   = MALLOT(double,namix) ;
   deos.dpdt   = MALLOT(double,namix) ;
   deos.dedr   = MALLOT(double,namix) ;
   deos.dedt   = dedt   ;
   deos.den    = den    ;
   deos.emat   = emat   ;
   deos.tmat   = tmat   ;
   deos.cs2    = cs2    ;
   deos.e_cold = e_cold ;
   deos.p_cold = p_cold ;
   deos.work3    = work3    ;
   deos.work1    = work1    ;
   deos.work2   = work2   ;
   deos.zstar  = domain->zstar ;
   if ( iftion == 1 ) {
      deos.pion   = pion   ;
      deos.dpidr  = MALLOT(double,namix) ;
      deos.dpidti = MALLOT(double,namix) ;
      deos.deidr  = MALLOT(double,namix) ;
      deos.deidti = deidt  ;
      deos.eion   = eion   ;
      deos.tion   = tion   ;
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      int *ndx    = domain->rndx[ir]    ;
      int  len    = domain->rlen[ir]    ;
      int  lenmix = domain->rlenmix[ir] ;
      int *myndxmix = domain->rndxmix[ir] ;
      int *mygrdmix = domain->rgrdmix[ir] ;
      double refd       = reg[ir].eosGroup[0].refd   ;
      double etamin     = reg[ir].eosGroup[0].etamin ;
      double etahold    = reg[ir].etahold ;
      double DensityMin = reg[ir].dmin ;
      double EnergyMin  = reg[ir].emin ;
      if ( len == 0 ) continue ;
      if ( e_cold != NULL ) {
	 for ( i = 0 ; i < len ; i++ ) {
            eion[ndx[i]] += e_cold[ndx[i]] ;
	 }
         myflops += 1.0 * len ;
      }
      DensityEnergyMin( den, emat, eion, ndx, len, DensityMin, EnergyMin, domain ) ;
      if ( reg[ir].numGroups == 1 ) {
         geteosnomix( deos, weos, fe, fi, csave, wcnvg, 
                      teos, dt,   domain, ir, 0, specfrac ) ;
      }
      pminchk( p, pion, p_cold, cs2, ndx, len, 
               reg[ir].pmin, reg[ir].pminmd, ir, domain ) ;
      if ( e_cold != NULL ) {
	 for ( i = 0 ; i < len ; i++ ) {
            eion[ndx[i]] -= e_cold[ndx[i]] ;
	 }
         myflops += 1.0 * len ;
      }
      if ( ir == irvoid ) {
         setvoid( den, emat, tmat, eion, tion, p, pion, cs2, dedt, deidt,
                  ndx, len, domain ) ;
      }
      for ( i = 0 ; i < len ; i++ ) {
         cs2[ndx[i]] = MAX( cs2[ndx[i]], ssmin2 ) ;
      }
      if ( lenmix > 0 ) {
         int *locndxmix = domain->rndxmix[ir] ;
         int *locgrdmix = domain->rgrdmix[ir] ;
         double *volf = domain->vol ;
         if ( iftion == 1 ) {
            for ( i = 0 ; i < lenmix ; i++ ) {
               fv               = volf[locndxmix[i]] ;
               p   [locgrdmix[i]] += p   [locndxmix[i]] * fv ;
               pion[locgrdmix[i]] += pion[locndxmix[i]] * fv ;
               cs2 [locgrdmix[i]] += den [locndxmix[i]] * cs2[locndxmix[i]] * fv ;
               den [locgrdmix[i]] += den [locndxmix[i]] * fv ;
            }
            myflops += 9.0 * lenmix ;
            if ( e_cold != NULL ) {
               for ( i = 0 ; i < lenmix ; i++ ) {
                  p_cold[locgrdmix[i]] += p_cold[locndxmix[i]] * volf[locndxmix[i]] ;
                  e_cold[locgrdmix[i]] += e_cold[locndxmix[i]] * volf[locndxmix[i]] *
                                          den   [locndxmix[i]] ;
               }
	    }
            myflops += 5.0 * lenmix ;
	 } else {
            for ( i = 0 ; i < lenmix ; i++ ) {
               fv                 = volf[locndxmix[i]] ;
               p  [locgrdmix[i]] += p   [locndxmix[i]] * fv ;
               cs2[locgrdmix[i]] += den [locndxmix[i]] * cs2[locndxmix[i]] * fv ;
               den[locgrdmix[i]] += den [locndxmix[i]] * fv ;
            }
            myflops += 7.0 * lenmix ;
	 }
      }
   }
   if (ifsource == 1) {
      SourceNew_general( p, NULL, "SourcePressure", teos, domain, 
                        _SourceNoEdit_);
      SourceNew_temperature( emat, tmat, dedt, den, 
                             "SourceElectronTemperature", teos, 
			      domain, _SourceEdit_);
      if ( iftion  == 1 ) {
         SourceNew_temperature( eion, tion, deidt, den, 
                                "SourceIonTemperature", teos, 
			         domain, _SourceEdit_);
      }
   }
   if ( (mynsrc > 0) && (ifsource == 1) ) {
      psrc(  teos, domain ) ;
      tmsrc( teos, emat, tmat, dedt, 
                   eion, tion, deidt, domain ) ;
   }
   if ( (ioneq == 1) && (ifzstar == 1) ) {
      zstarcal( den, tmat, domain ) ;
   }
   if ( ifmeos == 1 ) {
      FREEMEM(cndx) ;
      FREEMEM(cnvg) ;
      FREEMEM(indx) ;
      FREEMEM(rzon) ;
      FREEMEM(cmf) ;
      FREEMEM(ceos.p)      ;
      FREEMEM(ceos.dpdr)   ;
      FREEMEM(ceos.dpde)   ;
      FREEMEM(ceos.dpdt)   ;
      FREEMEM(ceos.dtdr)   ;
      FREEMEM(ceos.dtde)   ;
      FREEMEM(ceos.dedp)   ;
      FREEMEM(ceos.dedr)   ;
      FREEMEM(ceos.dedt)   ;
      FREEMEM(ceos.dedt_v) ;
      FREEMEM(ceos.drdp)   ;
      FREEMEM(ceos.drde)   ;
      FREEMEM(ceos.drdt)   ;
      FREEMEM(ceos.den)    ;
      FREEMEM(ceos.emat)   ;
      FREEMEM(ceos.tmat)   ;
      FREEMEM(ceos.cs2)    ;
      FREEMEM(ceos.delast) ;
      FREEMEM(ceos.drlast) ;
      FREEMEM(ceos.cdmin)  ;
      FREEMEM(ceos.cdmax)  ;
      FREEMEM(ceos.cpmin)  ;
      FREEMEM(ceos.cpmax)  ;
      FREEMEM(ceos.ceemin) ;
      FREEMEM(ceos.ceemax) ;
      FREEMEM(ceos.ctemin) ;
      FREEMEM(ceos.ctemax) ;
      FREEMEM(ceos.abar)   ;
      FREEMEM(ceos.zbar)   ;
      if ( if_eos_mix_zeq == 1 ) {
         FREEMEM(ceos.zstar) ;
      }
      if ( iftion == 1  ||  if_eos_mix_zeq == 1 ) {
         FREEMEM(ceos.pion)    ;
         FREEMEM(ceos.dpidr)   ;
         FREEMEM(ceos.dpidei)  ;
         FREEMEM(ceos.dpidti)  ;
         FREEMEM(ceos.dtidr)   ;
         FREEMEM(ceos.dedti)   ;
         FREEMEM(ceos.deidp)   ;
         FREEMEM(ceos.deidr)   ;
         FREEMEM(ceos.deidti)  ;
         FREEMEM(ceos.deidte)  ;
         FREEMEM(ceos.deidt_v) ;
         FREEMEM(ceos.dtidei)  ;
         FREEMEM(ceos.dtedei)  ;
         FREEMEM(ceos.drdti)   ;
         FREEMEM(ceos.eion)    ;
         FREEMEM(ceos.tion)    ;
         FREEMEM(ceos.e_cold)  ;
         FREEMEM(ceos.p_cold)  ;
         FREEMEM(ceos.dp_cdr)  ;
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
         FREEMEM(ceos.ceimin)  ;
         FREEMEM(ceos.ceimax)  ;
         FREEMEM(ceos.ctimin)  ;
         FREEMEM(ceos.ctimax)  ;
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
   FT_FINALIZE(me, domain->hash, myflops)
}
