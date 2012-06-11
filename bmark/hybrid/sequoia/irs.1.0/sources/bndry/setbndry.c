#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void setbndry( double *v, double s, Domain_t *domain )
{
   char *me = "setbndry";
   int i ;
   int ibnd ;
   int len ;
   int *ndx ;
   if ( domain->nbnd == 0 ) {
      return ;
   }
   FT_INITIALIZE(me, domain->hash)
   for ( ibnd = 0 ; ibnd < domain->nbnd ; ibnd++ ) {
      len = domain->bnd[ibnd].len_zrecv1 + domain->bnd[ibnd].len_zrecvc ;
      ndx = domain->bnd[ibnd].zdx_recv ;
      for ( i = 0 ; i < len ; i++ ) {
         v[ndx[i]] = s ;
      }
   }
   FT_FINALIZE(me, domain->hash, 1)
}
