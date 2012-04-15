#include "irs.h"
#include "irsreg.h"
#include "FunctionTimer.h" 
void regcnst( int ir, double region_value, double *za, Domain_t *domain )
{
   char *me = "regcnst";
   int i ;
   int length_clean = domain->rlencln[ir] ;
   int length_mix   = domain->rlenmix[ir] ;
   int *ndx         = domain->rndx[ir]    ;
   int *ndxmix      = domain->rndxmix[ir] ;
   int *grdmix      = domain->rgrdmix[ir] ;
   double *vf       = domain->vol         ;
   double myflops   = 1;
   FT_INITIALIZE(me, domain->hash) 
   for ( i = 0 ; i < length_clean ; i++ ) {
      za[ndx[i]] = region_value ;
   }
   if ( length_mix > 0 ) {
      for ( i = 0 ; i < length_mix ; i++ ) {
         za[grdmix[i]] += vf[ndxmix[i]] * region_value ;
      }
      myflops += 2.0 * length_mix ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
