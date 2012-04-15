#include "irs.h"
#include "irsdmp.h"
#include "Extents.h"
#ifdef SILO
void rdsilomesh(DBfile *idbid, char *mesh_name, double *x, double *y, 
                double *z, int *node, Extents_t ext, int jp, int kp) 
{
   char *me = "rdsilomesh";
   int i,j,k,indout,indin;
   double *xloc, *yloc, *zloc;
   DBquadmesh    *quadmesh;
   quadmesh = DBGetQuadmesh(idbid,mesh_name);
   if (ndims == 2) {
      indin = 0;
      xloc = (double *)quadmesh->coords[0];
      yloc = (double *)quadmesh->coords[1];
      for ( j = ext.jmin ; j <= ext.jmax ; j++ ) {
         for ( i = ext.imin ; i <= ext.imax ; i++ ) {
            indout = i + j * jp ;
            x[indout] = xloc[indin] ;
            y[indout] = yloc[indin] ;
            node[indout] = 1;
            indin++ ;
         }
      }
   } else {
      indin = 0;
      xloc = (double *)quadmesh->coords[0];
      yloc = (double *)quadmesh->coords[1];
      zloc = (double *)quadmesh->coords[2];
      for ( k = ext.kmin ; k <= ext.kmax ; k++ ) {
         for ( j = ext.jmin ; j <= ext.jmax ; j++ ) {
            for ( i = ext.imin ; i <= ext.imax ; i++ ) {
               indout = i + j * jp + k * kp;
               x[indout] = xloc[indin] ;
               y[indout] = yloc[indin] ;
               z[indout] = zloc[indin] ;
               node[indout] = 1;
               indin++ ;
            }
         }
      } 
   } 
   DBFreeQuadmesh(quadmesh);
} 
#endif
