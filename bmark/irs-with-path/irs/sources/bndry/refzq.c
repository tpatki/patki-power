#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void refzq( double *zq, Domain_t *domain )
{
   char *me = "refzq";
   int i, ip ;
   int id ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->phozlen ; i++ ) {
      id = domain->bndzdx[i] ;
      ip = domain->phozdx[i] ;
      zq[ip] = zq[id] ;
   }
   FT_FINALIZE(me, domain->hash, 1)
}
