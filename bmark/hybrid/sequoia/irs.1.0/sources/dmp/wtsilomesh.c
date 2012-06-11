#include "irs.h"
#include "irsdmp.h"
#include "Extents.h"
static char *coordnames[]={"X","Y","Z"};

#ifdef SILO
int wtsilomesh (DBfile *idbid, DBoptlist *ioptnod, char *mesh_name, double *x, 
            double *y, double *z, Extents_t ext, int jp, int kp)
{
   char *me = "wtsilomesh";
   char msg[MAXLINE];
   int i,j,k,indout,indin;
   int len;
   int dims[3];
   double *coords[3];
   double *xloc, *yloc, *zloc;
   int ierr;
   ierr = 0;
   dims[0] = ext.imax - ext.imin + 1;
   dims[1] = ext.jmax - ext.jmin + 1;
   dims[2] = ext.kmax - ext.kmin + 1;
   if (ndims == 3) {
      len = dims[0]*dims[1]*dims[2];
      xloc = ALLOT(double,len);
      yloc = ALLOT(double,len);
      zloc = ALLOT(double,len);
      coords[0] = xloc;
      coords[1] = yloc;
      coords[2] = zloc;
      indout = 0;
      for (k = ext.kmin; k <= ext.kmax; k++) {
         for (j = ext.jmin; j <= ext.jmax; j++) {
            for (i = ext.imin; i <= ext.imax; i++) {
               indin        = i + j*jp + k*kp;
               xloc[indout] = x[indin];
               yloc[indout] = y[indin];
               zloc[indout] = z[indin];
               indout       = indout + 1;
            }
         }
      }
      ierr = DBPutQuadmesh(idbid, mesh_name, coordnames, 
                           (float **)coords, dims, ndims, DB_DOUBLE, 
                            DB_NONCOLLINEAR,ioptnod);
      if (ierr != 0) {
         ctlerror(me,gv_errmsg_DBPutQuadmesh);
      }
      FREEMEM(xloc);
      FREEMEM(yloc);
      FREEMEM(zloc);
   } else {
      len = dims[0]*dims[1];
      xloc = ALLOT(double,len);
      yloc = ALLOT(double,len);
      coords[0] = xloc;
      coords[1] = yloc;
      indout = 0;
      for (j = ext.jmin; j <= ext.jmax; j++) {
         for (i = ext.imin; i <= ext.imax; i++) {
            indin        = i + j*jp;
            xloc[indout] = x[indin];
            yloc[indout] = y[indin];
            indout       = indout + 1;
         }
      }
      ierr = DBPutQuadmesh(idbid, mesh_name, coordnames, 
                           (float **)coords, dims, ndims, DB_DOUBLE, 
                            DB_NONCOLLINEAR,ioptnod);
      if (ierr != 0) {
         ctlerror(me,gv_errmsg_DBPutQuadmesh);
      }
      FREEMEM(xloc);
      FREEMEM(yloc);
   } 
   return(ierr) ;
}
#endif
