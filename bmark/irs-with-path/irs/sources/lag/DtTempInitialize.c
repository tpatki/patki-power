#include "irs.h"
#include "irslag.h"
#include "FunctionTimer.h"
void DtTempInitialize(void)
{
   char *me = "DtTempInitialze";
   int my_nblk = nblk;
   int iblk ;
   FT_INITIALIZE(me, gv_hash_tbl)
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int i ;
      int namix = domains[iblk].namix ;
      if ( (iftmode == 1) || (iftion == 1) ) {
         for ( i = 0 ; i < namix ; i++ ) {
            domains[iblk].tmatold[i] = domains[iblk].tmat[i] ;
         }
      }
      if ( iftion == 1 ) {
         for ( i = 0 ; i < namix ; i++ ) {
            domains[iblk].tionold[i] = domains[iblk].tion[i] ;
         }
      }
      if ( ngroup > 0 ) {
         for ( i = 0 ; i < namix ; i++ ) {
            domains[iblk].eradold[i] = domains[iblk].erad[i] ;
         }
      }
   }
   FT_FINALIZE(me, gv_hash_tbl, 1)
}
