#include "irs.h"
#include "irsdmp.h"
#ifdef SILO
void wtmeshvar(
  void *var,
  int  var_type,
  int  var_cent,
  char *var_name,
  char *mesh_name,
  int  *mixzdx,            
  int   mixlen,            
  DBfile *idbid, 
  DBoptlist *ioptnod,
  Domain_t *domain)
{
   char *me = "wtmeshvar";
   int  ierr;
   int  ilim, jlim, klim, i, j, k, indout, indin, dimsize;
   int  dims[3], dimsz[3];
   int    *ivar_in;
   int    *ivar;
   int    *ivarmix;
   double *dvar_in;
   double *dvar;
   double *dvarmix;
   if (ndims == 2) {
      dims[0] = domain->imax - domain->imin + 1;
      dims[1] = domain->jmax - domain->jmin + 1;
      dimsz[0] = domain->imax - domain->imin;
      dimsz[1] = domain->jmax - domain->jmin;
      dimsz[2] = 0;
   } else {
      dims[0] = domain->imax - domain->imin + 1;
      dims[1] = domain->jmax - domain->jmin + 1;
      dims[2] = domain->kmax - domain->kmin + 1;
      dimsz[0] = domain->imax - domain->imin;
      dimsz[1] = domain->jmax - domain->jmin;
      dimsz[2] = domain->kmax - domain->kmin;
   } 
   dimsize = LENEXT((*domain));
   ilim = domain->imax;
   jlim = domain->jmax;
   klim = domain->kmax;
   if (var_cent == ZONAL_ARRAY) {
      ilim--;
      jlim--;
      klim--;
   }
   if (var_type == FLOAT) {
      dvar = MALLOT(double,dimsize);
      dvar_in = (double *) var;
      if (mixlen > 0) {
         dvarmix = MALLOT(double,mixlen);
      }
      if (ndims == 3) {
         indout = 0;
         for (k = domain->kmin; k <= klim; k++) {
            for (j = domain->jmin; j <= jlim; j++) {
               for (i = domain->imin; i <= ilim; i++) {
                  indin        = i + j*domain->jp + k*domain->kp;
                  dvar[indout] = dvar_in[indin];
                  indout       = indout + 1;
               }
            }
         }
      }  else {
         indout = 0;
         for (j = domain->jmin; j <= jlim; j++) {
            for (i = domain->imin; i <= ilim; i++) {
               indin        = i + j*domain->jp; 
               dvar[indout] = dvar_in[indin];
               indout       = indout + 1;
            }
         }
      }
      if (mixlen > 0) {
         for (i = 0; i < mixlen; i++) {
            dvarmix[i] = dvar_in[mixzdx[i]];
         }
         ierr = DBPutQuadvar1(idbid,var_name,mesh_name, (float *)dvar, 
                              dimsz, ndims, (float *)dvarmix, mixlen, 
                              DB_DOUBLE, DB_ZONECENT, ioptnod); 
          FREEMEM(dvarmix);
      } else {
         if (var_cent == NODAL_ARRAY) {
            ierr = DBPutQuadvar1(idbid,var_name,mesh_name, (float *)dvar, 
                                 dims, ndims, NULL, 0, 
                                 DB_DOUBLE, DB_NODECENT, ioptnod); 
         } else {
            ierr = DBPutQuadvar1(idbid,var_name,mesh_name, (float *)dvar, 
                                 dimsz, ndims, NULL, 0, 
                                 DB_DOUBLE, DB_ZONECENT, ioptnod); 
         } 
      } 
      FREEMEM(dvar);
   } else {
      ivar = MALLOT(int,dimsize);
      ivar_in = (int *) var;
      if (mixlen > 0) {
         ivarmix = MALLOT(int,mixlen);
      }
      if (ndims == 3) {
         indout = 0;
         for (k = domain->kmin; k <= klim; k++) {
            for (j = domain->jmin; j <= jlim; j++) {
               for (i = domain->imin; i <= ilim; i++) {
                  indin        = i + j*domain->jp + k*domain->kp;
                  ivar[indout] = ivar_in[indin];
                  indout       = indout + 1;
               }
            }
         }
      }  else {
         indout = 0;
         for (j = domain->jmin; j <= jlim; j++) {
            for (i = domain->imin; i <= ilim; i++) {
               indin        = i + j*domain->jp;
               ivar[indout] = ivar_in[indin];
               indout       = indout + 1;
            }
         }
      }
      if (mixlen > 0) {
         for (i = 0; i < mixlen; i++) {
            ivarmix[i] = ivar_in[mixzdx[i]];
         }
         ierr = DBPutQuadvar1(idbid,var_name,mesh_name, (float *)ivar, 
                              dimsz, ndims, (float *)ivarmix, mixlen, 
                              DB_INT, DB_ZONECENT, ioptnod); 
          FREEMEM(ivarmix);
      } else {
         if (var_cent == NODAL_ARRAY) {
            ierr = DBPutQuadvar1(idbid,var_name,mesh_name, (float *)ivar, 
                                 dims, ndims, NULL, 0, 
                                 DB_INT, DB_NODECENT, ioptnod); 
         } else {
            ierr = DBPutQuadvar1(idbid,var_name,mesh_name, (float *)ivar, 
                                 dimsz, ndims, NULL, 0, 
                                 DB_INT, DB_ZONECENT, ioptnod); 
         } 
      } 
      FREEMEM(ivar);
   }
   if (ierr != 0) ctlerror(me,gv_errmsg_DBPutQuadvar1);
}
#endif
