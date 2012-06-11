#include "irs.h"
#include "irsdmp.h"
#include "Extents.h"
#ifdef SILO
void rdmeshvar(
  void *var,
  int  var_type,
  int  var_cent,
  char *var_name,
  int  len,
  int  mixlen,
  DBfile *idbid, 
  Domain_t *domain)
{
   char *me = "rdmeshvar";
   char name[MAXLINE];
   char msg[MAXLINE];
   int  ilim, jlim, klim, i, j, k, indout, indin;
   int    *ivar;
   int    *ivarmix;
   double *dvar;
   double *dvarmix;
   ilim = domain->imax;
   jlim = domain->jmax;
   klim = domain->kmax;
   if (var_cent == ZONAL_ARRAY) {
      ilim--;
      jlim--;
      klim--;
   } 
   sprintf(name,"%s_data",var_name);
   if (var_type == FLOAT) {
      dvar = (double *) var;
      for (i = 0; i < len; i++) {
         dvar[i] = 0.;
      }
      if (DBReadVar(idbid, name, dvar) != 0) {
         sprintf(msg,"Failed to read in required mesh variable %s.  \n\t\tBad things may happen.",var_name);
         ctlwarning(me,msg);
      }
      if (ndims == 3) {
         indin = (ilim - domain->imin + 1) * (jlim - domain->jmin + 1) * 
                 (klim - domain->kmin + 1) - 1;
         for (k = klim; k >= domain->kmin; k--) {
            for (j = jlim; j >= domain->jmin; j--) {
               for (i = ilim; i >= domain->imin; i--) {
                  indout       = i + j*domain->jp + k*domain->kp;
                  dvar[indout] = dvar[indin];
                  dvar[indin]  = 0;
                  indin--; 
               }
            }
         }
      }  else {
         indin = (ilim - domain->imin + 1) * (jlim - domain->jmin + 1) - 1;
         for (j = jlim; j >= domain->jmin; j--) {
            for (i = ilim; i >= domain->imin; i--) {
               indout       = i + j*domain->jp; 
               dvar[indout] = dvar[indin];
               dvar[indin]  = 0;
               indin--; 
            }
         }
      }
      if (mixlen > 0) {
         dvarmix = dvar + domain->nnalls;
         sprintf(name,"%s_mix",var_name);
         if (DBReadVar(idbid, name, dvarmix) != 0) {
            sprintf(msg,"Failed to read in required mixed data for variable %s.  \n\t\tBad things may happen.",var_name);
            ctlwarning(me,msg);
         }
      }
   } else {
      ivar = (int *) var;
      for (i = 0; i < len; i++) {
         ivar[i] = 0;
      }
      if (DBReadVar(idbid, name, ivar) != 0) {
         sprintf(msg,"Failed to read in required mesh variable %s.  \n\t\tBad things may happen.",var_name);
         ctlwarning(me,msg);
      }
      if (ndims == 3) {
         indin = (ilim - domain->imin + 1) * (jlim - domain->jmin + 1) * 
                 (klim - domain->kmin + 1) - 1;
         for (k = klim; k >= domain->kmin; k--) {
            for (j = jlim; j >= domain->jmin; j--) {
               for (i = ilim; i >= domain->imin; i--) {
                  indout       = i + j*domain->jp + k*domain->kp;
                  ivar[indout] = ivar[indin];
                  ivar[indin]  = 0;
                  indin--; 
               }
            }
         }
      }  else {
         indin = (ilim - domain->imin + 1) * (jlim - domain->jmin + 1) - 1;
         for (j = jlim; j >= domain->jmin; j--) {
            for (i = ilim; i >= domain->imin; i--) {
               indout       = i + j*domain->jp; 
               ivar[indout] = ivar[indin];
               ivar[indin]  = 0;
               indin--; 
            }
         }
      }
      if (mixlen > 0) {
         ivarmix = ivar + domain->nnalls;
         sprintf(name,"%s_mix",var_name);
         if (DBReadVar(idbid, name, ivarmix) != 0) {
            sprintf(msg,"Failed to read in required mixed data for variable %s.  \n\t\tBad things may happen.",var_name);
            ctlwarning(me,msg);
         }
      }
   }
}
void rdmeshvar_ext(
  void *var,
  int  var_type,
  int  var_cent,
  char *var_name,
  int  len,
  int  mixlen,
  DBfile *idbid, 
  Extents_t ext,
  Domain_t *domain)
{
   char *me = "rdmeshvar_ext";
   char name[MAXLINE];
   char msg[MAXLINE];
   int  ilim, jlim, klim, i, j, k, indout, indin;
   int    *ivar;
   int    *ivarin;
   int    *ivarmix;
   double *dvar;
   double *dvarin;
   double *dvarmix;
   DBquadvar *quadvar;
   ilim = ext.imax;
   jlim = ext.jmax;
   klim = ext.kmax;
   if (var_cent == ZONAL_ARRAY) {
      ilim--;
      jlim--;
      klim--;
   } 
   sprintf(name,"%s_data",var_name);
   quadvar = DBGetQuadvar(idbid, var_name);
   if (quadvar == NULL) {
      sprintf(msg,"Failed trying to read mesh variable %s from restart.",var_name);
      ctlerror(me,msg);
   }
   if (var_type == FLOAT) {
      dvar   = (double *) quadvar->vals[0];
      dvarin = (double *) var;
      if (ndims == 3) {
         for (k = ext.kmin; k <= klim; k++) {
            for (j = ext.jmin; j <= jlim; j++) {
               for (i = ext.imin; i <= ilim; i++) {
                  indout       = i + j*domain->jp + k*domain->kp;
                  dvarin[indout] = 0;
               }
            }
         }
         indin = (ilim - ext.imin + 1) * (jlim - ext.jmin + 1) * 
                 (klim - ext.kmin + 1) - 1;
         for (k = klim; k >= ext.kmin; k--) {
            for (j = jlim; j >= ext.jmin; j--) {
               for (i = ilim; i >= ext.imin; i--) {
                  indout       = i + j*domain->jp + k*domain->kp;
                  dvarin[indout] = dvar[indin];
                  indin--; 
               }
            }
         }
      }  else {
         for (j = ext.jmin; j <= jlim; j++) {
            for (i = ext.imin; i <= ilim; i++) {
               indout       = i + j*domain->jp;
               dvarin[indout] = 0;
            }
         }
         indin = (ilim - ext.imin + 1) * (jlim - ext.jmin + 1) - 1;
         for (j = jlim; j >= ext.jmin; j--) {
            for (i = ilim; i >= ext.imin; i--) {
               indout       = i + j*domain->jp; 
               dvarin[indout] = dvar[indin];
               indin--; 
            }
         }
      }
      if (mixlen > 0) {
         dvarmix = dvarin + domain->nnalls + domain->imaxmix;
         dvarmix = dvarin + domain->nnalls;
         dvar    = (double *)quadvar->mixvals[0];
	 for (i = 0; i < quadvar->mixlen; i++) {
	    dvarmix[i] = dvar[i];
	 }
      }
   } else {
      ivar   = (int *) quadvar->vals[0];
      ivarin = (int *) var;
      if (ndims == 3) {
         for (k = ext.kmin; k <= klim; k++) {
            for (j = ext.jmin; j <= jlim; j++) {
               for (i = ext.imin; i <= ilim; i++) {
                  indout       = i + j*domain->jp + k*domain->kp;
                  ivarin[indout] = 0;
               }
            }
         }
         indin = (ilim - ext.imin + 1) * (jlim - ext.jmin + 1) * 
                 (klim - ext.kmin + 1) - 1;
         for (k = klim; k >= ext.kmin; k--) {
            for (j = jlim; j >= ext.jmin; j--) {
               for (i = ilim; i >= ext.imin; i--) {
                  indout         = i + j*domain->jp + k*domain->kp;
                  ivarin[indout] = ivar[indin];
                  indin--; 
               }
            }
         }
      }  else {
         for (j = ext.jmin; j <= jlim; j++) {
            for (i = ext.imin; i <= ilim; i++) {
               indout       = i + j*domain->jp;
               ivarin[indout] = 0;
            }
         }
         indin = (ilim - ext.imin + 1) * (jlim - ext.jmin + 1) - 1;
         for (j = jlim; j >= ext.jmin; j--) {
            for (i = ilim; i >= ext.imin; i--) {
               indout        = i + j*domain->jp; 
               ivarin[indout] = ivar[indin];
               indin--; 
            }
         }
      }
      if (mixlen > 0) {
         ivarmix = ivarin + domain->nnalls + domain->imaxmix;
         ivarmix = ivarin + domain->nnalls;
         ivar    = (int *)quadvar->mixvals[0];
	 for (i = 0; i < quadvar->mixlen; i++) {
	    ivarmix[i] = ivar[i];
	 }
      }
   }
   DBFreeQuadvar(quadvar);
}
#endif
