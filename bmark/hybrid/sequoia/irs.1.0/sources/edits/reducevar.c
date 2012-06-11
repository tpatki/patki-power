#include "irs.h"
#include "irsgen.h"
#include "irscom.h"
#include "irsedits.h"
#include "irsrgst.h"
#include "irsreg.h"
#include "FunctionTimer.h"
#include "NodeList.h"
#include "ProblemArray.h"
#include "UserList.h"
#include "Region.h"
#define REDUCEVAR_MAX  0
#define REDUCEVAR_MIN  1
#define REDUCEVAR_AVE  2
#define REDUCEVAR_AVEV 3
#define REDUCEVAR_AVEM 4
#define REDUCEVAR_SUM  5
int reducevar(int type) {
   char *me = "reducevar";
   char varname[MAXWORD];
   char msg[MAXLINE];
   char op[MAXLINE];
   char field[MAXLINE];
   char aname[MAXLINE];
   char function[MAXLINE];
   int i;
   int cflag;
   int mat;
   int array_type;
   int iblk;
   int error;
   int len;
   int mynspec = 0;
   int *ndx;
   int *species = NULL;
   double value;
   double denom;
   double data[2];
   NodeWindow_t *ndxin      = NULL;
   NodeWindow_t *ndxptr     = NULL;
   UserList_t   *ul         = NULL;
   value = 0;
   denom = 1;
   if ( type == REDUCEVAR_MAX ) {
      value = -plarge;
      sprintf(function,"maxvar");
   } else if ( type == REDUCEVAR_MIN ) {
      value = plarge;
      sprintf(function,"minvar");
   } else if ( type == REDUCEVAR_AVE ) {
      denom = 0;
      sprintf(function,"avevar");
   } else if ( type == REDUCEVAR_AVEV ) {
      denom = 0;
      sprintf(function,"avevvar");
   } else if ( type == REDUCEVAR_AVEM ) {
      denom = 0;
      sprintf(function,"avemvar");
   } else if ( type == REDUCEVAR_SUM ) {
      sprintf(function,"sumvar");
   } 
   geta(op);
   if (strcmp(op,"(")) {
      sprintf(msg,"An open parenthesis is required after %s.",function);
      ctlwarning(me,msg);
      return(-1);
   }
   geta(varname);
   if (!strcmp(varname,"species")) {
       if (genmd != 0) {
          sprintf(msg,"You cannot operate on species until after the gen command.");
          NodeWindow_free(ndxin);
          ctlwarning(me,msg);
          return(-1);
       }
       error = UserList_parse("ReduceVar");
       if (error != 0) {
          sprintf(msg,"Error encountered while parsing list of species.");
          ctlwarning(me,msg);
          NodeWindow_free(ndxin);
          return(-1);
       }
       array_type = ZONAL_ARRAY;
   } else if (RGST_QUERY_OBJECT_ATTR(varname,"Zonal") == TRUE) {
      array_type = ZONAL_ARRAY;
   } else if (RGST_QUERY_OBJECT_ATTR(varname,"Nodal") == TRUE) {
      array_type = NODAL_ARRAY;
   } else {
      sprintf(msg,"Variable %s cannot be used in %s.",varname,function);
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   } 
   strcpy(aname,varname);
   error = NodeWindow_read(aname,&ndxin);
   if (error != 0) return(error);
   peekc(op);
   mat = -1;
   if (!strcmp(op,",")) {
      geta(op);
      geta(op);
      if (strcmp(op,"mat")) {
         sprintf(msg,"Expecting a keyword following comma in %s command.",function);
         ctlwarning(me,msg);
         return(-1);
      } else {
         mat = geti(&cflag);
      } 
      peekc(op);
   }
   if (strcmp(op,")")) {
      sprintf(msg,"A closed parenthesis is required after %s.",function);
      ctlwarning(me,msg);
      return(-1);
   } else {
      geta(op);
   } 
   ul = UserList_find("ReduceVar");
   if ((ul != NULL) && (mat == -1)) {
      sprintf(msg,"A material must be specified for %s to work with species.",function);
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   }
   if (ul != NULL) {
      species = MALLOT(int, reg[mat].nspec);
      mynspec = Species_getlist(species, "ReduceVar", reg[mat].species, 
                                 reg[mat].nspec);
   }
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      for (iblk = 0; iblk < nblk; iblk++) {
         double *vol;
         double *mass;
         double *vptr;
         if (array_type == ZONAL_ARRAY) {
            len = NodeWindow_fastndx(ndxptr,domains[iblk].gblk, NDX_REAL, 
	                          NDX_ZONAL);
         } else {
            len = NodeWindow_fastndx(ndxptr,domains[iblk].gblk, NDX_REAL, 
	                          NDX_NODAL);
         } 
         ndx = ndxptr->ndx;
         if (len > 0) {
            vol   = MALLOT(double, len);
            mass  = MALLOT(double, len);
            vptr  = MALLOT(double, len);
            for (i = 0; i < len; i++) {
               vol[i]  = 0;
               mass[i] = 0;
            }
	    fillvar_getvar(vptr, ndx, &len, varname, species, mynspec, mat, 
	                         &domains[iblk]);
	    if (mat > 0) {
	        for (i = 0; i < len; i++) {
	           if (domains[iblk].ireg[ndx[i]] < 0) {
	              int grd = -domains[iblk].ireg[ndx[i]];
	              while (grd > 0) { 
	                 if (domains[iblk].ireg[grd] == mat) {
	                    ndx[i] = grd;
	                    break;
	                 }
	                 grd = grd - domains[iblk].nnalls;
	                 grd = domains[iblk].lnkmix[grd];
	              }
	           }
	        }
	    }
            if (type == REDUCEVAR_MAX) {
               for (i = 0; i < len; i++) {
                  if (vptr[i] > value) value = vptr[i];
               }
            } else if (type == REDUCEVAR_MIN) {
               for (i = 0; i < len; i++) {
                  if (vptr[i] < value) value = vptr[i];
               }
            } else if (type == REDUCEVAR_AVE) {
               for (i = 0; i < len; i++) {
                  value += vptr[i];
                  denom += 1.0;
               }
            } else if (type == REDUCEVAR_AVEV) {
               for (i = 0; i < len; i++) {
                  int ip = ndx[i];
                  if (ip < domains[iblk].nnalls) {
                     vol[i] = domains[iblk].vol[ip];
                  } else {
                     int slot = domains[iblk].grdzn[ip - domains[iblk].nnalls];
                     vol[i] = domains[iblk].vol[ip] * domains[iblk].vol[slot];
                  } 
               }
               for (i = 0; i < len; i++) {
                  value += vptr[i] * vol[i];
                  denom += vol[i];
               }
            } else if (type == REDUCEVAR_AVEM) {
               if (array_type == ZONAL_ARRAY) {
                  for (i = 0; i < len; i++) {
                     mass[i] = domains[iblk].zmass[ndx[i]];
                  }
               } else {
                  for (i = 0; i < len; i++) {
                     mass[i] = domains[iblk].nmass[ndx[i]];
                  }
               } 
               for (i = 0; i < len; i++) {
                  value += vptr[i] * mass[i];
                  denom += mass[i];
               }
            } else if (type == REDUCEVAR_SUM) {
               for (i = 0; i < len; i++) {
                  value += vptr[i];
               }
            }
            FREEMEM(mass);
            FREEMEM(vol);
            FREEMEM(vptr);
            if (mat > 0) {
               for (i = 0; i < domains[iblk].nnalls; i++) {
                  if (domains[iblk].ireg[i] < 0) domains[iblk].ireg[i] = -1;
               }     
            }
         }
         NodeWindow_freendx(ndxptr);
      }
      ndxptr = ndxptr->next;
   }
   NodeWindow_free(ndxin);
   if (ifparallel) {
      if (type == REDUCEVAR_MAX) {
         data[0] = value;
         comreduce(data, 1, COM_MAX, COM_ALL, COM_DOUBLE);	 
         value = data[0];
      } else if (type == REDUCEVAR_MIN) {
         data[0] = value;
         comreduce(data, 1, COM_MIN, COM_ALL, COM_DOUBLE);	 
         value = data[0];
      } else if ((type == REDUCEVAR_AVE) ||
                 (type == REDUCEVAR_AVEV) ||
                 (type == REDUCEVAR_AVEM)) {
         data[0] = value;
         data[1] = denom;
         comreduce(data, 2, COM_SUM, COM_ALL, COM_DOUBLE);	 
         value = data[0];
         denom = data[1];
      } else if (type == REDUCEVAR_SUM) {
         data[0] = value;
         comreduce(data, 1, COM_SUM, COM_ALL, COM_DOUBLE);	 
         value = data[0];
      } 
   }
   value = value / ( denom + ptiny);
   if (mat == -1) {
      sprintf(field,"%s(%s)",function,aname);
   } else {
      sprintf(field,"%s(%s,%i)",function,aname,mat);
   } 
   ctloutput(me, field, R_DOUBLE, value);
   if (mynspec > 0) {
      FREEMEM(species);
      UserList_del("ReduceVar");
   }
   return(0);
}
