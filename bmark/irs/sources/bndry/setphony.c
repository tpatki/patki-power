#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void setphony( double *v, double s, Domain_t *domain )
{
   char *me = "setphony";
   int i, *ndx, n ;
   ndx = domain->rndx[0] ;
   n   = domain->rlen[0] ;
   for ( i = 0 ; i < n ; i++ ) {
      v[ndx[i]] = s ;
   }
}
