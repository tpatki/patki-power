#include "irs.h"
#include "irsreg.h"
#include "irslag.h"
#include "irseos.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void updateblk( Domain_t *domain, int ifcalcdt, double dt )
{
   char *me = "updateblk";
   int i, ir, len, *ndxmix, *grdmix ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)

   RegionTableAllocate( domain, reg, nreg ) ;
   RegionTableInitialize( domain, reg, nreg, domain->specfrac ) ;
   geteos( domain->p, domain->pion, domain->p_cold, domain->cs2, domain->dedt,
           domain->deidt, domain->den, domain->emat, domain->eion,
           domain->e_cold, domain->tmat, domain->tion, domain->work3, 
	   domain->work1, domain->work2, ttime, dt, domain,
           domain->specfrac, 1, 0 ) ;
   RegionTableFree( domain, reg, nreg ) ;
   if ( (iftmode == 1) || (iftion == 1) ) {
      if ( ifcalcdt == 1 ) {
         CalcDtTemp( domain ) ;
      }
   }


 ; 
   if ( ngroup > 0 ) {
      double myphifloor, eradmax ;
      myphifloor = tfloor * tfloor * tfloor * tfloor ;
      for ( i = 0 ; i < domain->nnalls ; i++ ) {
         eradmax         = MAX( domain->erad[i], myphifloor ) ;
         domain->trad[i] = sqrt( sqrt( eradmax ) ) ;
      }
      myflops += 8.0 * domain->nnalls ;
      for ( ir = 1 ; ir <= nreg ; ir++ ) {
         ndxmix = domain->rndxmix[ir] ;
         len    = domain->rlenmix[ir] ;
         for ( i = 0 ; i < len ; i++ ) {
            eradmax                 = MAX( domain->erad[ndxmix[i]], myphifloor ) ;
            domain->trad[ndxmix[i]] = sqrt( sqrt( eradmax ) ) ;
         }
         myflops += 8.0 * len ;
      }
   }
   HydroDtControls(domain);
   FT_FINALIZE(me, domain->hash, myflops)
}
