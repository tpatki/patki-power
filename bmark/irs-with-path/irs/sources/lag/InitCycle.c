#include "irs.h"
#include "irslag.h"
#include "FunctionTimer.h"
void InitCycle( void )
{
   char *me = "InitCycle";
   int my_nblk = nblk;
   int iblk ;
   FT_INITIALIZE(me, gv_hash_tbl)
   if ( ngroup > 0 ) {
      if ( iftmode == 1 || (iftmode == 0 && iftion == 0) ) {
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
	    int i ;
            for ( i = 0 ; i < domains[iblk].namix ; i++ ) {
               domains[iblk].ematsrc[i] = 0.0 ;
            }
         }
      }
      if ( iftion == 1 ) {
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
	    int i ;
            for ( i = 0 ; i < domains[iblk].namix ; i++ ) {
               domains[iblk].ematsrc[i] = 0.0 ;
               domains[iblk].eionsrc[i] = 0.0 ;
            }
         }
      }
   }

   FT_FINALIZE(me, gv_hash_tbl, 1)
}
