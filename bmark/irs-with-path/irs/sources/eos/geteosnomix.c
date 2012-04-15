#include "irs.h"
#include "irseos.h"
#include "FunctionTimer.h"
#include "SpeciesFraction.h"
void geteosnomix( Thermo_t deos, Thermo_t weos,  double *fe,    
                  double  *fi,   double  *csave, int    *wcnvg, 
                  double   teos, double   dt, 
                  Domain_t *domain, int ir, int multieos, 
		  SpeciesFraction_t *specfrac  )
{
   char *me = "geteosnomix";
   int i, fm, *ndxmix, *grdmix, *ndx, len, ieos, number, index ;
   double ssmin2, fv, etamin, etamax, refd, *coef, *zbar, *abar ;
   double *p, *cs2, *dedt, *den,   *emat, *tmat ;
   double *p_cold,  *pion, *deidt, *eion, *tion ;
   FT_INITIALIZE(me, domain->hash)
   p    = deos.p    ;
   dedt = deos.dedt ;
   den  = deos.den  ;
   emat = deos.emat ;
   tmat = deos.tmat ;
   cs2  = deos.cs2  ;
   ndx = domain->rndx[ir] ;
   len = domain->rlen[ir] ;
   ieos = 0 ;
   if ( iftion == 1 ) {
      pion  = deos.pion   ;
      deidt = deos.deidti ;
      eion  = deos.eion   ;
      tion  = deos.tion   ;
   }
   ssmin2 = sndmin * sndmin ;
   etamin = reg[ir].eosGroup[ieos].etamin ;
   etamax = reg[ir].eosGroup[ieos].etamax ;
   refd   = reg[ir].eosGroup[ieos].refd ;
   fm     = reg[ir].eosGroup[ieos].database.form ;
   coef   = reg[ir].eosGroup[ieos].database.data ;
   index  = reg[ir].eosGroup[ieos].database.index  ;
   number = reg[ir].eosGroup[ieos].database.number ;
   zbar   = domain->domainRegions[ir].regionTables[ieos].z ;
   abar   = domain->domainRegions[ir].regionTables[ieos].a ;
   if ( reg[ir].eosGroup[ieos].database.type == _Table_ ) {

   } else if ( fm == 1 ) {
 ;    } else if ( fm == 2 ) {
 ;    } else if ( fm == 3 ) {
 ;    } else if ( fm == 4 ) {
 ;    } else if ( fm == 5 ) {
      eosfm5( deos, ndx, len, refd, etamin, etamax, coef, ir, ieos, multieos, 
              domain) ;
   } else if ( fm == 6 ) {
 ;    } else if ( fm == 7 ) {
 ;    } else if ( fm == 12 ) {
 ; 
   } else if ( fm == 13 ) {
 ; 
   } else if ( fm == 15 ) {
   } else if ( fm == 16 ) {
 ;    } else if ( fm == 17 ) {
 ;    } else if ( fm == 18 ) {
   } else if ( fm == 19 ) {
 ;    } else if ( fm == 105 ) {
 ;    } else if ( fm == 107 ) {
 ;    } else if ( fm == 111 ) {
 ;    } else if ( fm == 200 ) {
 ;    } else if ( fm == 301 ) {
 ;    } else if ( fm == 311 ) {
 ;    } else if ( fm == 321 ) {
 ;    }
   etaminchk( den, p, cs2, ndx, len, refd, etamin, domain ) ;
   FT_FINALIZE(me, domain->hash, 1)
}
