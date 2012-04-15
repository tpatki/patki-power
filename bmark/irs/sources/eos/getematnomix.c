#include "irs.h"
#include "irseos.h"
#include "FunctionTimer.h"
void getematnomix( double *emat,  double *eion, double *e_cold, double *dedt,
                   double *deidt, double *den,  double *tmat,   double *tion,
                   double *abar,  double *zbar, int    *ndx,    int     len,  
                   int ifgen,     Domain_t *domain,  int ir, int     ieos )
{
   char *me = "getematnomix";
   int i, number, index ;
   int fm ;
   double rr, t, refd ;
   double *data ;
   FT_INITIALIZE(me, domain->hash)
   if ( len <= 0 ) return ;
   fm     = reg[ir].eosGroup[ieos].database.form ;
   data   = reg[ir].eosGroup[ieos].database.data ;
   index  = reg[ir].eosGroup[ieos].database.index  ;
   number = reg[ir].eosGroup[ieos].database.number ;
   refd   = reg[ir].eosGroup[ieos].refd ;
   if ( ((fm >= 1) &&  (fm <= 30) && (fm != 15 && fm != 17 && fm != 19 ))  ) {
      rr  = 1.0 / refd ;
      for ( i = 0 ; i < len ; i++ ) {
         emat[ndx[i]] = rr * tmat[ndx[i]] ;
      }
   } else if ( (fm == 15) && (ifgen == 1) ) {
 ;    } else if ( (fm == 16) && (ifgen == 1) ) {
 ;    } else if ( (fm == 17) && (ifgen == 1) ) {
 ;    } else if ( (fm == 19) && (ifgen == 1) ) {
 ;    } else if ( (fm == 105) && (ifgen > 0) ) {
 ;    } else if ( (fm == 107) && (ifgen > 0) ) {
 ;    } else if ( (fm == 111) && (ifgen == 1) ) {
 ;    } else if ( (fm == 200) && (ifgen == 1) ) {
 ;    } else if ( (fm == 211) && (ifgen == 1) ) {
 ;    } else if ( (fm == 301) && (ifgen == 1) ) {
 ;    } else if ( (fm == 311) && (ifgen == 1) ) {
 ;    } else if ( (fm == 321) && (ifgen == 1) ) {
 ;    }
   FT_FINALIZE(me, domain->hash, 1)
}
