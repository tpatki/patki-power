#include "irs.h"
#include "irseos.h"
#include "FunctionTimer.h"
void pminchk( double *p, double *pion, double *p_cold, double *cs2, 
              int *ndx, int n, double pmin, int pminmd, int ir,
              Domain_t *domain )
{
   char *me = "pminchk";
   double spmin ;
   int i, fm ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   if ( reg[ir].eosGroup[0].database.type == _Form_ ) {
      fm = reg[ir].eosGroup[0].database.form ;
      if ( fm == 1 || fm == 6 ) {
         spmin = 0.0 ;
      } else if ( fm == 311 || fm == 312 || fm == 321 ) {
         spmin = 0.5 * pmin ;
      } else {
         spmin = pmin ;
      }
   } else {
      spmin = pmin ;
   }
   if ( pminmd == 0 ) {
      spmin = 0.0 ;
   }
   for ( i = 0 ; i < n ; i++ ) {
      if ( p[ndx[i]] < pmin ) {
         p[ndx[i]]    = spmin  ;
         cs2[ndx[i]] *= c2fail ;
      }
   }
   if ( iftion != 0 ) {
      for ( i = 0 ; i < n ; i++ ) {
         if ( pion[ndx[i]] < pmin ) {
            pion[ndx[i]] = spmin ;
         }
      }
   }
   myflops += 1.0 * n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
