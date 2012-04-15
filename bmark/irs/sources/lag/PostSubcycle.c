#include "irs.h"
#include "irslag.h"
#include "FunctionTimer.h"
void PostSubcycle( double timestep, double sub_timestep )
{
   char *me = "PostSubcycle";
   int my_nblk = nblk;
   int iblk ;
   FT_INITIALIZE(me, gv_hash_tbl)
   for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
      if ( (iftmode == 1) || (iftion == 1) ) {
         FREEMEM(domains[iblk].tmatold) ;
      }
      if ( iftion == 1 ) {
         FREEMEM(domains[iblk].tionold) ;
      }
      if ( ngroup > 0 ) {
         FREEMEM(domains[iblk].eradold) ;
      }
   }
   FT_FINALIZE(me, gv_hash_tbl, 1)
}
