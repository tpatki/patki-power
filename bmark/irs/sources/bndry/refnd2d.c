#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void refnd2d( double *x, double *y, Domain_t *domain ) 
{
   char *me = "refnd2d";
   int i, ibc, ip, ndx ;
   int len, off;
   double *xm, *ym, *xp, *yp, *xc, *yc;
   double dx, dy, dot, nx, ny ;
   int *ndxp ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->phonlen ; i++ ) {
      ndx = domain->bndndx[i] ;
      ip  = domain->phondx[i] ;
      ibc = domain->phonbc[i] ;
      xm  = x + 2 * ndx ;
      ym  = y + 2 * ndx ;
      xc  = x +     ndx ;
      yc  = y +     ndx ;
      xp  = x ;
      yp  = y ;
      if ( domain->bc[ibc].type == XVCNST ) {
         yp[ip] = ym[ip] ;
         xp[ip] = 2.0 * xc[ip] - xm[ip] ;
         myflops += 2.0 ;
      } else if ( domain->bc[ibc].type == YVCNST ) {
         xp[ip] = xm[ip] ;
         yp[ip] = 2.0 * yc[ip] - ym[ip] ;
         myflops += 2.0 ;
      } else if ( domain->bc[ibc].type == FREE ) {
         xp[ip] = xc[ip] ;
         yp[ip] = yc[ip] ;
      } else if ( (domain->bc[ibc].type == WALL) || (domain->bc[ibc].type == PLANE) ) {
         nx  = domain->bc[ibc].nx ;
         ny  = domain->bc[ibc].ny ;
         dx  = xm[ip] - xc[ip] ;
         dy  = ym[ip] - yc[ip] ;
         dot = 2.0 * ( nx * dx + ny * dy ) ;
         dx -= nx * dot ;
         dy -= ny * dot ;
         xp[ip] = xc[ip] + dx ;
         yp[ip] = yc[ip] + dy ;
         myflops += 12.0 ;
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
