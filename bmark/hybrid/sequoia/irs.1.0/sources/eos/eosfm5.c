#include "irs.h"
#include "irseos.h"
#include "FunctionTimer.h"
#define  a   coef[5]    
void eosfm5( Thermo_t deos,  int    *ndx,    int     n,     double  rho0,  
             double  etamin, double  etamax, double *coef,  int     ir,
             int     ieos,   int multieos, Domain_t *domain )
{
   char *me = "eosfm5";
   double *p,    *cs2,  *dpdr, *dpde ;
   double *dtdr, *dtde, *dedt ;
   double *den,  *emat,  *tmat,   *e_cold ;
   double *cmu,  *cmu_m, *cecold, *cdtdr  ;
   int i ;
   double gam1, gam1gam, gamma, rr, eta ;
   double dtdex ;
   double myflops = 0.0; 
   FT_INITIALIZE(me, domain->hash)
   p      = deos.p    ;
   dpdr   = deos.dpdr ;
   dpde   = deos.dpde ;
   dtdr   = deos.dtdr ;
   dtde   = deos.dtde ;
   dedt   = deos.dedt ;
   den    = deos.den  ;
   emat   = deos.emat ;
   tmat   = deos.tmat ;
   cs2    = deos.cs2  ;
   gam1    = coef[0] ;
   gamma   = gam1 + 1. ;
   gam1gam = gam1 * gamma ;
   rr      = 1.0 / rho0 ;
   dtdex = reg[ir].eosGroup[ieos].abar / 2894.394 ;
   for ( i = 0 ; i < n ; i++ ) {
      eta = den[ndx[i]] * rr ;
      eta = MAX( eta, etamin ) ;
      eta = MIN( eta, etamax ) ;
      tmat[ndx[i]] = rho0 * emat[ndx[i]] ;
      p[ndx[i]]    = gam1 * eta * tmat[ndx[i]] ;
      cs2[ndx[i]]  = gam1gam    * emat[ndx[i]] ;
      dedt[ndx[i]] = rr ;
   }
   myflops += 5.0 * n ;
   if ( multieos == 1 ) {
      for ( i = 0 ; i < n ; i++ ) {
         dpdr[ndx[i]] = gam1 * tmat[ndx[i]] * rr ;
         dpde[ndx[i]] = gam1 * eta * rho0 ;
         dtdr[ndx[i]] = 0.0 ;
         dtde[ndx[i]] = dtdex ;
      }
      myflops += 4.0 * n ;
   }
   if ( multieos == 1 ) {
      cmu    = deos.drdp ;
      cmu_m  = deos.drde ;
      cdtdr  = deos.dedr ;
      cecold = deos.dedp ;
      for ( i = 0 ; i < n ; i++ ) {
         cmu[i] = den[ndx[i]] * rr - 1.0 ;
      }
      myflops += 2.0 * n ;
      calc_dtdr_form ( cdtdr, cecold, cmu, cmu_m, rho0, dtdex,
                       etamax, etamin, n, ir, ieos, &myflops ) ;
      for ( i = 0 ; i < n ; i++ ) {
         dtdr[ndx[i]] = cdtdr[i] ;
         dtde[ndx[i]] = dtdex ; 
         tmat[ndx[i]] = ( emat[ndx[i]] - cecold[i] ) * dtdex ;
      }
      myflops += 2.0 * n ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
#undef a
