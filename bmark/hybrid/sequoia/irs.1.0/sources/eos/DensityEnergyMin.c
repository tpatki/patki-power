#include "irs.h"
#include "irseos.h"
#include "FunctionTimer.h"
void DensityEnergyMin( double *den, double *emat,  double *eion, int *ndx,
                       int len, double DensityMin, double EnergyMin,
                       Domain_t *domain )
{
   char *me = "DensityEnergyMin" ;
   int i ;
   double myflops = 0.0; 
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < len ; i++ ) {
      den[ndx[i]]  = MAX( den[ndx[i]],  DensityMin ) ;
      emat[ndx[i]] = MAX( emat[ndx[i]], EnergyMin  ) ;
   }
   if ( iftion == 1 ) {
      for ( i = 0 ; i < len ; i++ ) {
         eion[ndx[i]] = MAX( eion[ndx[i]], EnergyMin  ) ;
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
