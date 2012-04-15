#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void refradnq( double *ndq, Domain_t *domain )
{
   char *me = "refradnq";
   int i, ip, stride ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->rphonlen ; i++ ) {
     stride = domain->rbndndx[i];
     ip     = domain->rphondx[i] ;
     ndq[ip] = ndq[ip + 2*stride] ;
   }
   FT_FINALIZE(me, domain->hash, 1)
}
