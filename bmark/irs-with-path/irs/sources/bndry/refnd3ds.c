#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void refnd3ds( double *a, Domain_t *domain )
{
   char *me = "refnd3ds";
   int i,ip,ibc ;
   double *ap, *am, *ac ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->phonlen ; i++ ) {
      ibc = domain->phonbc[i];
      ip  = domain->phondx[i];
      ap = a ;
      ac = a + domain->bndndx[i];
      am = a + 2*domain->bndndx[i];
      if (domain->bc[ibc].type == FREE) {
         ap[ip] = ac[ip] ;
      } else {
         ap[ip] = am[ip] ;
      }
   }
   FT_FINALIZE(me, domain->hash, 1)
}
