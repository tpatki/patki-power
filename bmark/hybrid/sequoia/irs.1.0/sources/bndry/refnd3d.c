#include "irs.h"
#include "irsbndry.h"
#include "FunctionTimer.h"
void refnd3d( double *x, double *y, double *z, Domain_t *domain ) 
{
   char *me = "refnd3d";
   int i, ip, ibc, ndx ;
   int len, off;
   int *ndxp;
   int *pn;
   double *xm, *ym, *zm, *xp, *yp, *zp, *xc, *yc, *zc;
   double dx, dy, dz, dot, nx, ny, nz, norm, nr ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->phonlen ; i++ ) {
      ndx = domain->bndndx[i];
      ip  = domain->phondx[i];
      ibc = domain->phonbc[i];
      xm  = x + 2*ndx ;
      ym  = y + 2*ndx ;
      zm  = z + 2*ndx ;
      xc  = x + ndx ;
      yc  = y + ndx ;
      zc  = z + ndx ;
      xp  = x ;
      yp  = y ;
      zp  = z ;
      nx  = domain->bc[ibc].nx ;
      ny  = domain->bc[ibc].ny ;
      nz  = domain->bc[ibc].nz ;
      if ( domain->bc[ibc].type == XVCNST ) {
         yp[ip] = ym[ip] ;
         zp[ip] = zm[ip] ;
         xp[ip] = 2.0 * xc[ip] - xm[ip] ;
         myflops += 2.0 ;
      } else if ( domain->bc[ibc].type == YVCNST ) {
         xp[ip] = xm[ip] ;
         zp[ip] = zm[ip] ;
         yp[ip] = 2.0 * yc[ip] - ym[ip] ;
         myflops += 2.0 ;
      } else if ( domain->bc[ibc].type == ZVCNST ) {
         xp[ip] = xm[ip] ;
         yp[ip] = ym[ip] ;
         zp[ip] = 2.0 * zc[ip] - zm[ip] ;
         myflops += 2.0 ;
      } else if ( domain->bc[ibc].type == FIXED ) {
         xp[ip] = xc[ip] ;
         yp[ip] = yc[ip] ;
         zp[ip] = zc[ip] ;
      } else if ( (domain->bc[ibc].type == WALL) || (domain->bc[ibc].type == PLANE) ) {
         dx  = xm[ip] - xc[ip] ;
         dy  = ym[ip] - yc[ip] ;
         dz  = zm[ip] - zc[ip] ;
         dot = 2.0 * ( nx * dx + ny * dy + nz * dz ) ;
         dx -= nx * dot ;
         dy -= ny * dot ;
         dz -= nz * dot ;
         xp[ip] = xc[ip] + dx ;
         yp[ip] = yc[ip] + dy ;
         zp[ip] = zc[ip] + dz ;
         myflops += 18.0 ;
      } else if (domain->bc[ibc].type == LINE) {
         dx  = xm[ip] - xc[ip] ;
         dy  = ym[ip] - yc[ip] ;
         dz  = zm[ip] - zc[ip] ;
         dot = 2.0 * ( nx * dx + ny * dy + nz * dz ) ;
         dx = -dx + nx * dot ;
         dy = -dy + ny * dot ;
         dz = -dz + nz * dot ;
         xp[ip] = xc[ip] + dx ;
         yp[ip] = yc[ip] + dy ;
         zp[ip] = zc[ip] + dz ;
         myflops += 21.0 ;
      } else if ( domain->bc[ibc].type == CYLINDER ) {
         nx = domain->bc[ibc].nx * xc[ip] ;
         ny = domain->bc[ibc].ny * yc[ip] ;
         nz = domain->bc[ibc].nz * zc[ip] ;
         norm = 1.0 / sqrt( nx * nx + ny * ny + nz * nz + ptiny ) ;
         nx *= norm ;
         ny *= norm ;
         nz *= norm ;
         dx  = xm[ip] - xc[ip] ;
         dy  = ym[ip] - yc[ip] ;
         dz  = zm[ip] - zc[ip] ;
         dot = 2.0 * ( nx * dx + ny * dy + nz * dz ) ;
         dx -= nx * dot ;
         dy -= ny * dot ;
         dz -= nz * dot ;
         xp[ip] = xc[ip] + dx ;
         yp[ip] = yc[ip] + dy ;
         zp[ip] = zc[ip] + dz ;
         myflops += 38.0 ;
      } else if ( domain->bc[ibc].type == SPHERE ) {
         nx = xc[ip] ;
         ny = yc[ip] ;
         nz = zc[ip] ;
         norm = 1.0 / sqrt( nx * nx + ny * ny + nz * nz + ptiny ) ;
         nx *= norm ;
         ny *= norm ;
         nz *= norm ;
         dx  = xm[ip] - xc[ip] ;
         dy  = ym[ip] - yc[ip] ;
         dz  = zm[ip] - zc[ip] ;
         dot = 2.0 * ( nx * dx + ny * dy + nz * dz ) ;
         dx -= nx * dot ;
         dy -= ny * dot ;
         dz -= nz * dot ;
         xp[ip] = xc[ip] + dx ;
         yp[ip] = yc[ip] + dy ;
         zp[ip] = zc[ip] + dz ;
         myflops += 35.0 ;
      } else if ( domain->bc[ibc].type == CONE ) {
         nr = nx ;
         nx = xc[ip] ;
         ny = yc[ip] ;
         norm = 1.0 / sqrt( nx * nx + ny * ny + ptiny ) ;
         nx *= nr * norm ;
         ny *= nr * norm ;
         dx  = xm[ip] - xc[ip] ;
         dy  = ym[ip] - yc[ip] ;
         dz  = zm[ip] - zc[ip] ;
         dot = 2.0 * ( nx * dx + ny * dy + nz * dz ) ;
         dx -= nx * dot ;
         dy -= ny * dot ;
         dz -= nz * dot ;
         xp[ip] = xc[ip] + dx ;
         yp[ip] = yc[ip] + dy ;
         zp[ip] = zc[ip] + dz ;
         myflops += 34.0 ;
      } else if ( domain->bc[ibc].type == FREE ) {
         xp[ip]  = xc[ip] ;
         yp[ip]  = yc[ip] ;
         zp[ip]  = zc[ip] ;
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
