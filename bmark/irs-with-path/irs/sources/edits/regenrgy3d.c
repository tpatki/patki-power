#include "irs.h"
#include "irsreg.h"
#include "irsedits.h"
#include "ProblemArray.h"
#include "FunctionTimer.h"
#include "Region.h"
void regenrgy3d( double *x,  double *y,  double *z, 
                 double *xv, double *yv, double *zv, Domain_t *domain ) 
{
   char *me = "regenrgy3d";
   int i, ir, ip, id, len, *ndx, *grdmix ;
   int is;
   int *i1, *i2, *i3, *i4, *i5, *i6, *i7, *i8 ;
   double mass, volume ;
   double xmom, ymom, zmom ;
   double *ke1, *ke2, *ke3, *ke4, *ke5, *ke6, *ke7, *ke8 ;
   double *xv1, *xv2, *xv3, *xv4, *xv5, *xv6, *xv7, *xv8 ;
   double *yv1, *yv2, *yv3, *yv4, *yv5, *yv6, *yv7, *yv8 ;
   double *zv1, *zv2, *zv3, *zv4, *zv5, *zv6, *zv7, *zv8 ;
   double *totke, *ntotke ;
   double *pote ;
   double *mass_frac;
   double *regetot  = (double *) ProblemArray_ptr("regetot",     domain->hash);
   double *regke    = (double *) ProblemArray_ptr("regke",       domain->hash);
   double *regie    = (double *) ProblemArray_ptr("regie",       domain->hash);
   double *regpe    = (double *) ProblemArray_ptr("regpe",       domain->hash);
   double *regtke   = (double *) ProblemArray_ptr("regtke",      domain->hash);
   double *regmass  = (double *) ProblemArray_ptr("regmass",     domain->hash);
   double *regvol   = (double *) ProblemArray_ptr("regvol",      domain->hash);
   double *regxmom  = (double *) ProblemArray_ptr("regxmom",     domain->hash);
   double *regymom  = (double *) ProblemArray_ptr("regymom",     domain->hash);
   double *regzmom  = (double *) ProblemArray_ptr("regzmom",     domain->hash);
   double *regxmomp = (double *) ProblemArray_ptr("regxmomp",    domain->hash);
   double *regymomp = (double *) ProblemArray_ptr("regymomp",    domain->hash);
   double *regzmomp = (double *) ProblemArray_ptr("regzmomp",    domain->hash);
   double *regxmomn = (double *) ProblemArray_ptr("regxmomn",    domain->hash);
   double *regymomn = (double *) ProblemArray_ptr("regymomn",    domain->hash);
   double *regzmomn = (double *) ProblemArray_ptr("regzmomn",    domain->hash);
   double *tmatavg  = (double *) ProblemArray_ptr("regtmatavg",  domain->hash);
   double *tionavg  = (double *) ProblemArray_ptr("regtionavg",  domain->hash);
   double *tradavg  = (double *) ProblemArray_ptr("regtradavg",  domain->hash);
   double *cveavg   = (double *) ProblemArray_ptr("regcveavg",   domain->hash);
   double *cviavg   = (double *) ProblemArray_ptr("regcviavg",   domain->hash);
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash) 
   totke  = ALLOT(double,domain->nnalls) ;
   ntotke = ALLOT(double,domain->nnodes) ;
   pote  = ALLOT(double,domain->nnalls) ;
   for ( i = 0 ; i < domain->nnodes ; i++ ) {
      ntotke[i] = xv[i]*xv[i] + yv[i]*yv[i] + zv[i]*zv[i] ;
   }
   myflops += 5.0 * domain->nnodes ;
      NDSET3D(ntotke,ke1,ke2,ke3,ke4,ke5,ke6,ke7,ke8) ;
      NDSET3D(xv,xv1,xv2,xv3,xv4,xv5,xv6,xv7,xv8) ;
      NDSET3D(yv,yv1,yv2,yv3,yv4,yv5,yv6,yv7,yv8) ;
      NDSET3D(zv,zv1,zv2,zv3,zv4,zv5,zv6,zv7,zv8) ;
      for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
         totke[i] = 0.125 * ( ke1[i] + ke2[i] + ke3[i] + ke4[i] +
                              ke5[i] + ke6[i] + ke7[i] + ke8[i] ) ;
      }
   myflops += 8.0 * (domain->lrz - domain->frz + 1) ;
   if ( (xgrav != 0.0) || (ygrav != 0.0) || (zgrav != 0.0) ) {
 ;    }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      len = domain->rlencln[ir] ;
      ndx = domain->rndx[ir]    ;
      regke[ir]    = 0.0 ;
      regie[ir]    = 0.0 ;
      regtke[ir]   = 0.0 ;
      regpe[ir]    = 0.0 ;
      regmass[ir]  = 0.0 ;
      regvol[ir]   = 0.0 ;
      regxmom[ir]  = 0.0 ;
      regymom[ir]  = 0.0 ;
      regzmom[ir]  = 0.0 ;
      regxmomp[ir] = 0.0 ;
      regymomp[ir] = 0.0 ;
      regzmomp[ir] = 0.0 ;
      regxmomn[ir] = 0.0 ;
      regymomn[ir] = 0.0 ;
      regzmomn[ir] = 0.0 ;
      tmatavg[ir]  = 0.0 ;
      tionavg[ir]  = 0.0 ;
      tradavg[ir]  = 0.0 ;
      cveavg[ir]   = 0.0 ;
      cviavg[ir]   = 0.0 ;
      for ( i = 0 ; i < len ; i++ ) {
	 ip = ndx[i] ;
         regke[ir]   += 0.5 * domain->zmass[ip] * totke[ip] ;
         regie[ir]   += domain->zmass[ip] * domain->emat[ip] ;
         regmass[ir] += domain->zmass[ip] ;
         regvol[ir]  += domain->vol[ip] ;
      }
      myflops += 6.0 * len ;
      if ( domain->e_cold != NULL ) {
         for ( i = 0 ; i < len ; i++ ) {
            ip = ndx[i] ;
            regie[ir] += domain->zmass[ip] * domain->e_cold[ip] ;
         }
         myflops += 2.0 * len ;
      }
      if ( (xgrav != 0.0) || (ygrav != 0.0) || (zgrav != 0.0) ) {
         for ( i = 0 ; i < len ; i++ ) {
	    ip = ndx[i] ;
            regpe[ir] += domain->zmass[ip] * pote[ip] ;
         }
         myflops += 2.0 * len ;
      }
      if (iftmode) {
         for ( i = 0 ; i < len ; i++ ) {
            ip = ndx[i] ;
            tmatavg[ir] += domain->zmass[ip] * domain->dedt[ip] *
                                          domain->tmat[ip] ;
            cveavg[ir]  += domain->zmass[ip] * domain->dedt[ip] ;
         }
         myflops += 5.0 * len ;
      }
      if (iftion) {
         for ( i = 0 ; i < len ; i++ ) {
            ip = ndx[i] ;
            regie[ir]   += domain->zmass[ip] * domain->eion[ip] ;
            tmatavg[ir] += domain->zmass[ip] * domain->dedt[ip]  *
                                          domain->tmat[ip] ;
            tionavg[ir] += domain->zmass[ip] * domain->deidt[ip] *
                                          domain->tion[ip] ;
            cveavg[ir]  += domain->zmass[ip] * domain->dedt[ip]  ;
            cviavg[ir]  += domain->zmass[ip] * domain->deidt[ip] ;
         }
         myflops += 12.0 * len ;
      }
      if (ngroup) {
         for ( i = 0 ; i < len ; i++ ) {
            regie[ir]   += sbc*domain->erad[ndx[i]]*domain->vol[ndx[i]] ;
            tradavg[ir] +=     domain->erad[ndx[i]]*domain->vol[ndx[i]] ;
         }
         myflops += 5.0 * len ; 
      }
         for ( i = 0 ; i < len ; i++ ) {
	    ip = ndx[i] ;
            xmom = 0.125 * domain->zmass[ip] * ( xv1[ip] + xv2[ip] + xv3[ip]
                                        + xv4[ip] + xv5[ip] + xv6[ip]
                                        + xv7[ip] + xv8[ip] ) ;
            if ( xmom >= 0.0 ) {
               regxmomp[ir] += xmom ;
            } else {
               regxmomn[ir] += xmom ;
            }
            regxmom[ir] += xmom ;
            ymom = 0.125 * domain->zmass[ip] * ( yv1[ip] + yv2[ip] + yv3[ip]
                                        + yv4[ip] + yv5[ip] + yv6[ip]
                                        + yv7[ip] + yv8[ip] ) ;
            if ( ymom >= 0.0 ) {
               regymomp[ir] += ymom ;
            } else {
               regymomn[ir] += ymom ;
            }
            regymom[ir] += ymom ;
            zmom = 0.125 * domain->zmass[ip] * ( zv1[ip] + zv2[ip] + zv3[ip]
                                        + zv4[ip] + zv5[ip] + zv6[ip]
                                        + zv7[ip] + zv8[ip] ) ;
            if ( zmom >= 0.0 ) {
               regzmomp[ir] += zmom ;
            } else {
               regzmomn[ir] += zmom ;
            }
            regzmom[ir] += zmom ;
         }
      myflops += 33.0 * len ;
      len = domain->rlenmix[ir];
      ndx = domain->rndxmix[ir];
      for ( i = 0 ; i < len ; i++ ) {
	 ip     = ndx[i] ;
	 id     = domain->grdpnt[ip-domain->nnalls] ;
         volume = domain->vol[ip] * domain->vol[id] ;
	 mass   = domain->den[ip] * volume ;
         regke[ir]   += 0.5  * mass * totke[id] ;
         regie[ir]   += mass * domain->emat[ip] ;
         regmass[ir] += mass ;
         regvol[ir]  += volume ;
      }
      myflops += 9.0 * len ;
      if ( domain->e_cold != NULL ) {
         for ( i = 0 ; i < len ; i++ ) {
            ip   = ndx[i];
            id   = domain->grdpnt[ip-domain->nnalls];
            mass = domain->den[ip] * domain->vol[ip] * domain->vol[id] ;
            regie[ir] += mass * domain->e_cold[ip] ;
         }
         myflops += 4.0 * len ;
      }
      if ( (xgrav != 0.0) || (ygrav != 0.0) || (zgrav != 0.0) ) {
         for ( i = 0 ; i < len ; i++ ) {
            ip   = ndx[i];
	    id   = domain->grdpnt[ip-domain->nnalls];
	    mass = domain->den[ip] * domain->vol[ip] * domain->vol[id] ;
            regpe[ir] += mass * pote[id] ;
         }
         myflops += 4.0 * len ;
      }
      if (iftmode) {
         for ( i = 0 ; i < len ; i++ ) {
            ip   = ndx[i];
	    id   = domain->grdpnt[ip-domain->nnalls];
	    mass = domain->den[ip] * domain->vol[ip] * domain->vol[id] ;
            tmatavg[ir] += mass * domain->dedt[ip] * domain->tmat[ip] ;
            cveavg[ir]  += mass * domain->dedt[ip] ;
         }
         myflops += 7.0 * len ;
      }
      if (iftion) {
         for ( i = 0 ; i < len ; i++ ) {
            ip   = ndx[i];
	    id   = domain->grdpnt[ip-domain->nnalls];
	    mass = domain->den[ip] * domain->vol[ip] * domain->vol[id] ;
            regie[ir]   += mass * domain->eion[ip] ;
            tmatavg[ir] += mass * domain->dedt[ip]  * domain->tmat[ip] ;
            tionavg[ir] += mass * domain->deidt[ip] * domain->tion[ip] ;
            cveavg[ir]  += mass * domain->dedt[ip]  ;
            cviavg[ir]  += mass * domain->deidt[ip] ;
         }
         myflops += 14.0 * len ;
      }
      if (ngroup) {
         grdmix = domain->rgrdmix[ir] ;
         for ( i = 0 ; i < len ; i++ ) {
            regie[ir] +=
                           sbc * domain->erad[grdmix[i]] * domain->vol[grdmix[i]] *
                                 domain->vol[ndx[i]] ;
            tradavg[ir] +=
                                 domain->erad[grdmix[i]] * domain->vol[grdmix[i]] *
                                 domain->vol[ndx[i]] ;
         }
         myflops += 7.0 * len ;
      }
         for ( i = 0 ; i < len ; i++ ) {
	    ip   = ndx[i] ;
	    id   = domain->grdpnt[ip-domain->nnalls] ;
	    mass = domain->den[ip] * domain->vol[ip] * domain->vol[id] ;
            xmom = 0.125 * mass * ( xv1[id] + xv2[id] + xv3[id] + xv4[id] +
                                    xv5[id] + xv6[id] + xv7[id] + xv8[id] ) ;
            if ( xmom >= 0.0 ) {
               regxmomp[ir] += xmom ;
            } else {
               regxmomn[ir] += xmom ;
            }
            regxmom[ir] += xmom ;
            ymom = 0.125 * mass * ( yv1[id] + yv2[id] + yv3[id] + yv4[id] +
                                    yv5[id] + yv6[id] + yv7[id] + yv8[id] ) ;
            if ( ymom >= 0.0 ) {
               regymomp[ir] += ymom ;
            } else {
               regymomn[ir] += ymom ;
            }
            regymom[ir] += ymom ;
            zmom = 0.125 * mass * ( zv1[id] + zv2[id] + zv3[id] + zv4[id] +
                                    zv5[id] + zv6[id] + zv7[id] + zv8[id] ) ;
            if ( zmom >= 0.0 ) {
               regzmomp[ir] += zmom ;
            } else {
               regzmomn[ir] += zmom ;
            }
            regzmom[ir] += zmom ;
         }
      myflops += 35.0 * len ;
      regetot[ir] = regke[ir] + regie[ir];
      if ( (xgrav != 0.0) || (ygrav != 0.0) || (zgrav != 0.0) ) {
         regetot[ir] += regpe[ir] ;
      }
      if (ifdynspec) {
         len = domain->rlencln[ir];
         ndx = domain->rndx[ir];
         for (i = 0; i < len; i++) {
            mass_frac = domain->specfrac[ndx[i]].mass_frac;
            mass      = domain->zmass[ndx[i]];
            for (is = 0; is < reg[ir].nspec; is++) {
               reg[ir].species[is].mass += mass * mass_frac[is];
            }
         }
         myflops += 2.0 * len * reg[ir].nspec ;
         len    = domain->rlenmix[ir];
         ndx    = domain->rndxmix[ir];
         grdmix = domain->rgrdmix[ir];
         for (i = 0; i < len; i++) {
            mass_frac = domain->specfrac[ndx[i]].mass_frac;
            mass      = domain->den[ndx[i]] * domain->vol[ndx[i]] * 
	                domain->vol[grdmix[i]]; 
            for (is = 0; is < reg[ir].nspec; is++) {
               reg[ir].species[is].mass += mass * mass_frac[is];
            }
         }
         myflops += 2.0 * len * reg[ir].nspec  + 3 * len;
      } else {
         for (is = 0; is < reg[ir].nspec; is++) {
            reg[ir].species[is].mass += regmass[ir] *
                       reg[ir].species[is].massFraction0;
         }
         myflops += 2.0 * reg[ir].nspec ;
      }
   }
   FREEMEM(totke) ;
   FREEMEM(ntotke) ;
   FREEMEM(pote) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
