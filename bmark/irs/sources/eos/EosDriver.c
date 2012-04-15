#include "irs.h"
#include "irsreg.h"
#include "irseos.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void EosDriver( double eostime, double eosdeltat )
{
   char *me = "EosDriver";
   int iblk ;
   int my_nblk  = nblk;
   int ifsource = 1 ;
   int ifzstar  = 1 ;
   FT_INITIALIZE(me, gv_hash_tbl)
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      RegionTableInitialize( &domains[iblk], reg, nreg,
                              domains[iblk].specfrac ) ;
      geteos( domains[iblk].p,      domains[iblk].pion,
              domains[iblk].p_cold, domains[iblk].cs2,
              domains[iblk].dedt,   domains[iblk].deidt,
              domains[iblk].den,    domains[iblk].emat,
              domains[iblk].eion,   domains[iblk].e_cold,
              domains[iblk].tmat,   domains[iblk].tion,
              domains[iblk].work3,    domains[iblk].work1,
              domains[iblk].work2,   eostime, eosdeltat,
             &domains[iblk],        domains[iblk].specfrac,
              ifsource,             ifzstar ) ;
   }
   FT_FINALIZE(me, gv_hash_tbl, 1)
}
