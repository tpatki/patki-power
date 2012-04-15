#include "irs.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "irscom.h"
void tblkinit( DiffusionData_t *tblk )
{
   char *me = "tblkinit";
   int iblk, my_nblk = nblk ;
   double myflops = 0.0; 
   FT_INITIALIZE(me, gv_hash_tbl)
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int i ;
      for ( i = 0 ; i < domains[iblk].namix ; i++ ) {
         tblk[iblk].phi[i]    = 0.0 ;
         tblk[iblk].dphi[i]   = 0.0 ;
         tblk[iblk].adphi[i]  = 0.0 ;
         tblk[iblk].rhs[i]    = 0.0 ;
         tblk[iblk].esrc[i]   = 0.0 ;
         tblk[iblk].flmt[i]   = 0.0 ;
         tblk[iblk].phim[i]   = 0.0 ;
         tblk[iblk].xplnk[i]  = 0.0 ;
         tblk[iblk].alpha[i]  = 0.0 ;
         tblk[iblk].diffcl[i] = 0.0 ;
         tblk[iblk].diffcr[i] = 0.0 ;
         tblk[iblk].diffcb[i] = 0.0 ;
         tblk[iblk].diffcf[i] = 0.0 ;
      }
   }
   if ( ndims == 3 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         int i ;
         for ( i = 0 ; i < domains[iblk].namix ; i++ ) {
            tblk[iblk].diffcd[i] = 0.0 ;
            tblk[iblk].diffcu[i] = 0.0 ;
         }
      }
   }
   if ( iftion == 1 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
	 int i ;
         for ( i = 0 ; i < domains[iblk].namix ; i++ ) {
            tblk[iblk].kie[i]   = 0.0 ;
            tblk[iblk].beta[i]  = 0.0 ;
            tblk[iblk].gamma[i] = 0.0 ;
            tblk[iblk].rcm3t[i] = 0.0 ;
         }
      }
   }
   FT_FINALIZE(me, gv_hash_tbl, myflops)
}
