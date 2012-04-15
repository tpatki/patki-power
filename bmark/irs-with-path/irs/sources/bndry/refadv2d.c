#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void refadv2d( Domain_t *domain )
{
   char *me = "refadv2d";
   int i, ibc, *ndx, ifref, ivar ;
   double *zmassi, *zmassp, *voli, *volp ;
   double *vari, *varp ;
   FT_INITIALIZE(me, domain->hash)
   refnd2d( domain->x,    domain->y,    domain ) ;
   refnd2d( domain->xdot, domain->ydot, domain ) ;
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
      ifref = 1;
      if ( domain->bc[ibc].type == FREE ) {
         ifref = 0 ;
      }
      if (ifref) {
         ndx    = domain->bc[ibc].ndx ;
         zmassi = domain->zmass + domain->bc[ibc].rz ;
         zmassp = domain->zmass + domain->bc[ibc].pz ;
         voli   = domain->vol + domain->bc[ibc].rz ;
         volp   = domain->vol + domain->bc[ibc].pz ;
         for ( i = 0 ; i < domain->bc[ibc].len - 1 ; i++ ) {
            zmassp[ndx[i]] = zmassi[ndx[i]] ;
            volp[ndx[i]]   = voli[ndx[i]] ;
	 }
      }
   }
   FT_FINALIZE(me, domain->hash, 1)
}
