#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void setphony2(double *v, double s, Domain_t *domain)
{
   char *me = "setphony2";
   int i ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->nnalls ; i++ ) {
      if ( domain->ireg[i] == 0 ) {
         v[i] = s ;
      }
   }
   FT_FINALIZE(me, domain->hash, 1)
}
