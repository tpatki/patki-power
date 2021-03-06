#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void refadv3d( Domain_t *domain )
{
   char *me = "refadv3d";
   int i, ibc, *ndx, ifref, ivar ;
   double *zmassi, *zmassp, *voli, *volp ;
   double *vari, *varp ;
   FT_INITIALIZE(me, domain->hash)
   refnd3d( domain->x,    domain->y,    domain->z,    domain ) ;
   refnd3d( domain->xdot, domain->ydot, domain->zdot, domain ) ;
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
      if ( domain->bc[ibc].type == XVCNST ) {
         ifref = 1 ;
      } else if ( domain->bc[ibc].type == YVCNST ) {
         ifref = 1 ;
      } else if ( domain->bc[ibc].type == ZVCNST ) {
         ifref = 1 ;
      } else if ( domain->bc[ibc].type == FIXED ) {
         ifref = 1 ;
      } else if ( (domain->bc[ibc].type == WALL) | (domain->bc[ibc].type == PLANE) ) {
         ifref = 1 ;
      } else if ( domain->bc[ibc].type == CYLINDER ) {
         ifref = 1 ;
      } else if ( domain->bc[ibc].type == LINE ) {
         ifref = 1 ;
      } else if ( domain->bc[ibc].type == SPHERE ) {
         ifref = 1 ;
      } else if ( domain->bc[ibc].type == CONE ) {
         ifref = 1 ;
      } else if ( domain->bc[ibc].type == FREE ) {
         ifref = 0 ;
      }
      if (ifref) {
         ndx    = domain->bc[ibc].ndx ;
         zmassi = domain->zmass + domain->bc[ibc].rz ;
         zmassp = domain->zmass + domain->bc[ibc].pz ;
         voli   = domain->vol + domain->bc[ibc].rz ;
         volp   = domain->vol + domain->bc[ibc].pz ;
         for ( i = 0 ; i < domain->bc[ibc].len-1 ; i++ ) {
            zmassp[ndx[i]] = zmassi[ndx[i]] ;
            volp[ndx[i]]   = voli[ndx[i]] ;
	 }
      }
   }
   FT_FINALIZE(me, domain->hash, 1)
}
