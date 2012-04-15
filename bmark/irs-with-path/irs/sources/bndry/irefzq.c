#include "irs.h"
#include "irsbndry.h"
void irefzq( int *zq, Domain_t *domain ) {
   int i,ibc,*ndx,len ;
   int *qt,*qs ;
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
      if (domain->bc[ibc].type == LINE) continue ;
      ndx = domain->bc[ibc].ndx ;
      len = domain->bc[ibc].len - 1 ;
      qs = zq + domain->bc[ibc].rz ;
      qt = zq + domain->bc[ibc].pz ;
      if (domain->bc[ibc].type != FREE) {
	 for ( i = 0 ; i < len ; i++ ) {
            qt[ndx[i]] = qs[ndx[i]] ;
         }
      } else {
         for ( i = 0 ; i < len ; i++ ) {
            qt[ndx[i]] = 0 ;
         }
      }
   }
}
