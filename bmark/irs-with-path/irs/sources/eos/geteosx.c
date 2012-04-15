#include "irs.h"
#include "irseos.h"
#include "FunctionTimer.h"
#include "SpeciesFraction.h"
void geteosx( Thermo_t ceos,   Thermo_t weos,  double *fe,   double *fi,
              double  *csave,  int     *wcnvg, double  teos, double  dt,
              int     *ndx,    int      len,   int     ir,   int     ieos,
              DATABASETYPE_t dbeos,     Domain_t *domain, 
	      SpeciesFraction_t *specfrac )
{
   char *me = "geteosx";
   int i, fm, multieos, number, index, ndata, *ndxmix, *grdmix  ;
   double ssmin2, fv, refd, etamin, etamax, pmin ;
   double *coef, *abar, *zbar, *zstar, *p, *cs2, *den ;
   FT_INITIALIZE(me, domain->hash)
   p     = ceos.p     ;
   cs2   = ceos.cs2   ;
   den   = ceos.den   ;
   abar  = ceos.abar  ;
   zbar  = ceos.zbar  ;
   zstar = ceos.zstar ;
   ssmin2 = sndmin * sndmin ;
   multieos = 1 ;
   fm     = reg[ir].eosGroup[ieos].database.form   ;
   coef   = reg[ir].eosGroup[ieos].database.data   ;
   ndata  = reg[ir].eosGroup[ieos].database.ndata  ;
   index  = reg[ir].eosGroup[ieos].database.index  ;
   number = reg[ir].eosGroup[ieos].database.number ;
   refd   = reg[ir].eosGroup[ieos].refd            ;
   etamin = reg[ir].eosGroup[ieos].etamin          ;
   etamax = reg[ir].eosGroup[ieos].etamax          ;
   pmin   = reg[ir].pmin                           ;
   if ( dbeos == _Table_){

     } else if ( fm == 1 ) {
 ;    } else if ( fm == 2 ) {
 ;    } else if ( fm == 3 ) {
 ;    } else if ( fm == 4 ) {
 ;    } else if ( fm == 5 ) {
      eosfm5( ceos, ndx, len, refd, etamin, etamax, coef, ir, ieos,
              multieos, domain ) ;
   } else if ( fm == 6 ) {
 ;    } else if ( fm == 7 ) {
 ;    } else if ( fm == 15 ) {
 ;    } else if ( fm == 16 ) {
 ;    } else if ( fm == 17 ) {
 ;    } else if ( fm == 18 ) {
   } else if ( fm == 19 ) {
 ;    } else if ( fm == 105 ) {
 ;    } else if ( fm == 107 ) {
 ;    } else if ( fm == 111 ) {
 ;    } else if ( fm == 200 ) {
 ;    } else if ( fm == 211 ) {
 ;    } else if ( fm == 301 ) {
 ;    } else if ( fm == 311 ) {
 ;    } else if ( fm == 321 ) {
 ;    }
   etaminchk( den, p, cs2, ndx, len, refd, etamin, domain ) ;
   for ( i = 0 ; i < len ; i++ ) {
      cs2[ndx[i]] = MAX( cs2[ndx[i]], ssmin2 ) ;
   }
   FT_FINALIZE(me, domain->hash, 1)
}
