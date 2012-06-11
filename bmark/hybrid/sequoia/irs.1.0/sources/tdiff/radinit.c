#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "DiffusionData.h"
void radinit( DiffusionData_t *tblk )
{
   char *me = "radinit";
   int iblk, my_nblk = nblk ;
   double myflops = 0.0; 
   FT_INITIALIZE(me, gv_hash_tbl)
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int i;
      int ir;
      int *ndxmix;
      int *grdmix;
      double myphifloor, eradmax ;
      double *erad;
      double *trad;
      erad = domains[iblk].erad ;
      trad = domains[iblk].trad ;
      myphifloor = tfloor * tfloor * tfloor * tfloor ;
      for ( i = 0 ; i < domains[iblk].nnalls ; i++ ) {
         eradmax = MAX( erad[i], myphifloor ) ;
         trad[i] = sqrt( sqrt( eradmax ) )  ;
      }
      myflops += 8.0 * domains[iblk].nnalls ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      CopyArrayDouble( tblk[iblk].phi, domains[iblk].erad, domains[iblk].namix ) ;
   }
   FT_FINALIZE(me, gv_hash_tbl, myflops)
}
