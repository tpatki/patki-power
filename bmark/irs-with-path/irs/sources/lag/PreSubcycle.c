#include "irs.h"
#include "irslag.h"
#include "FunctionTimer.h"
void PreSubcycle( void )
{
   char *me = "PreSubcycle";
   int my_nblk = nblk;
   int iblk ;
   FT_INITIALIZE(me, gv_hash_tbl)
   for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
      if ( (iftmode == 1) || (iftion == 1) ) {
         domains[iblk].tmatold = MALLOT(double, domains[iblk].namix) ;
      }
      if ( iftion == 1 ) {
         domains[iblk].tionold = MALLOT(double, domains[iblk].namix) ;
      }
      if ( ngroup > 0 ) {
         domains[iblk].eradold = MALLOT(double, domains[iblk].namix) ;
      }
   }
   FT_FINALIZE(me, gv_hash_tbl, 1)
}
