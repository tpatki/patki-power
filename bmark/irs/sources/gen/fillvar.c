#include "irs.h"
#include "irsbndry.h"
#include "irsctl.h"
#include "irsedits.h"
#include "irsgen.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "irssys.h"
#include "Spline.h"
#include "NodeList.h"
#include "ProblemArray.h"
#include "UserList.h"
#include "Transform.h"
#include "Region.h"
#define FILLVAR_SPLINE 0
#define FILLVAR_FUNC   1
#define FILLVAR_SCALE  2
#define FILLVAR_TABLE  3
#define FILLVAR_VALUE  4
static void fillvar_getcoord(double *x,double *y,double *z,double *r,double *t,
                      int *ndx, int len, int array_type, Domain_t *domain);
static void fillvar_expression(double *vptr, double *x, double *y, double *z,
                        double *r, double *t, int len, char *func, char *cnst,
			int mode);
static void fillvar_setvar(double *vptr, int *ndx, int len, char *varname,
                   int  *species, int mynspec, int mat, int iblk, 
		   Domain_t *domain) ;

static void fillvar_value(double *vptr, double *x, double *y, double *z, double *r,
                   double *t, int len, double value, char *cnst) ;
int fillvar_input(void) {
   char *me = "fillvar_input";
   char aname[MAXWORD];
   char varname[MAXWORD];
   char msg[MAXLINE];
   char op[MAXLINE];
   char field[MAXLINE];
   char *expression = NULL;
   char *constraint = NULL;
   int i;
   int cflag;
   int mat;
   int type;
   int array_type;
   int iblk;
   int error;
   int len;
   int mynspec = 0;
   int *ndx;
   int *species = NULL;
   double xmin, xmax;
   double value;
   Spline_t *spline  = NULL;

   NodeWindow_t *ndxin      = NULL;
   NodeWindow_t *ndxptr     = NULL;
   UserList_t   *ul         = NULL;
   sprintf(aname,"fillvar");
   error = NodeWindow_read(aname,&ndxin);
   if (error != 0) return(error);
   geta(op);
   if (strcmp(op,"=")) {
      sprintf(msg,"An equal sign is required after the fillvar.");
      ctlwarning(me,msg);
      return(-1);
   }
   geta(varname);
   if (!strcmp(varname,"species")) {
       if (genmd != 0) {
          sprintf(msg,"Fillvar cannot operate on species until after the gen command.");
          NodeWindow_free(ndxin);
          ctlwarning(me,msg);
          return(-1);
       }
       error = UserList_parse("FillVar");
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
      sprintf(msg,"Variable %s cannot be used in fillvar.",varname);
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   } 
   geta(op);
   mat         = -1;
   if (!strcmp(op,"mat")) {
      mat = geti(&cflag);
      geta(op);
   }
   if (!strcmp(op,"constraint")) {
      len = lineop_grab(&constraint,"}",ps);
      if (len < 0) {
         sprintf(msg,"Error parsing input for constraint.");
         NodeWindow_free(ndxin);
         ctlwarning(me,msg);
         return(-1);
      }
      geta(op);
   }
   ul = UserList_find("FillVar");
   if ((ul != NULL) && (mat == -1)) {
      sprintf(msg,"A material must be specified for fillvar to work with species.");
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   }
   if (ul != NULL) {
      species = MALLOT(int, reg[mat].nspec);
      mynspec = Species_getlist(species, "FillVar", reg[mat].species, 
                                 reg[mat].nspec);
   }
   if (!strcmp(op,"spline")) {
       geta(op);
       spline = spline_find(op);
       if (spline == NULL) {
          sprintf(msg,"Spline %s does not exits.",op);
          NodeWindow_free(ndxin);
          ctlwarning(me,msg);
          return(-1);
       }
       xmin = getf(&error);
       xmax = getf(&error);
       if (xmin > xmax) {
          double val = xmin;
          xmin = xmax;
          xmax = val;
       }
       if ((error = spline_chkrange(spline,xmin,xmax)) == -1) {
          NodeWindow_free(ndxin);
          return(-1);
       } 
       type = FILLVAR_SPLINE;
   } else if (!strcmp(op,"val")) {
       value = getf(&cflag);
       type = FILLVAR_VALUE;

   } else if (!strcmp(op,"func")) {
       len = lineop_grab(&expression,"}",ps);
       if (len < 0) {
          sprintf(msg,"Error parsing input for fucntion.");
          NodeWindow_free(ndxin);
          ctlwarning(me,msg);
          return(-1);
       }
       type = FILLVAR_FUNC;
   } else if (!strcmp(op,"scale")) {
       len = lineop_grab(&expression,"}",ps);
       if (len < 0) {
          sprintf(msg,"Error parsing input for scale.");
          NodeWindow_free(ndxin);
          ctlwarning(me,msg);
          return(-1);
       }
       type = FILLVAR_SCALE;
   } else {
       sprintf(msg,"Unrecognized operation - %s in fillvar command.",op);
       NodeWindow_free(ndxin);
       ctlwarning(me,msg);
       return(-1);
   } 
   ndxptr = ndxin;
   while (ndxptr != NULL) {
      for (iblk = 0; iblk < nblk; iblk++) {
         double *x;
         double *y;
         double *z;
         double *r;
         double *t;
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
            x    = MALLOT(double, len);
            y    = MALLOT(double, len);
            z    = MALLOT(double, len);
            r    = MALLOT(double, len);
            t    = MALLOT(double, len);
            vptr = MALLOT(double, len);
            for (i = 0; i < len; i++) {
               x[i] = 0;
               y[i] = 0;
               z[i] = 0;
               r[i] = 0;
               t[i] = 0;
            }
	    fillvar_getvar(vptr, ndx, &len, varname, species, mynspec, mat, 
	                         &domains[iblk]);
	    fillvar_getcoord(x,y,z,r,t, ndx, len, array_type,&domains[iblk]);
	    if (type == FILLVAR_SPLINE) {
	       fillvar_spline(vptr, x, y, z, r, t, len, spline, xmin, xmax, 
	                                                      constraint);
	    } else if (type == FILLVAR_VALUE) {
	       fillvar_value(vptr, x, y, z, r, t, len, value, constraint);

	    } else if (type == FILLVAR_FUNC) {
	       fillvar_expression(vptr, x, y, z, r, t, len, expression, 
	                                                       constraint, 0);
	    } else if (type == FILLVAR_SCALE) {
	       fillvar_expression(vptr, x, y, z, r, t, len, expression, 
	                                                       constraint, 1);
	    } 
	    fillvar_setvar(vptr, ndx, len, varname, species, mynspec, mat, 
	                         iblk ,&domains[iblk]);
            FREEMEM(x);
            FREEMEM(y);
            FREEMEM(z);
            FREEMEM(r);
            FREEMEM(t);
            FREEMEM(vptr);
         }
         NodeWindow_freendx(ndxptr);
      }
      ndxptr = ndxptr->next;
   }
   NodeWindow_free(ndxin);
   if ((type == FILLVAR_SCALE) || (type == FILLVAR_FUNC)) {
      FREEMEM(expression);
   }
   if (constraint != NULL) {
      FREEMEM(constraint);
   }
   if ((mat != -1) || (mynspec > 0)) {
      if (genmd == 0) {
         editor(FULL_STEP);
      }
   }
   if (mynspec > 0) {
      FREEMEM(species);
      UserList_del("FillVar");
   }
   return(0);
}
void fillvar_getvar(double *vptr, int *ndx, int *len, char *varname, 
                   int *species, int mynspec, int mat, 
		   Domain_t *domain) 
{
   char *me = "fillvar_getvar";
   char msg[MAXLINE];
   int i;
   int id;
   int is;
   int js;
   int mylen;
   int mycln;
   int mymix;
   int *myndx;
   double *data;
   ProblemArray_t *prb;
   myndx = MALLOT(int, *len);
   if (mat > -1) {
      regndx(domain);
      mycln = lists_overlap(ndx, *len, domain->rndx[mat], 
                                         domain->rlencln[mat], myndx);
      mymix = lists_overlap(ndx, *len, domain->rgrdmix[mat], 
                                         domain->rlenmix[mat], myndx + mycln);
      mylen = mycln + mymix;
   } else {
      mymix = 0;
      mycln = *len;
      mylen = *len;
      for (i = 0; i < mylen; i++) {
         myndx[i] = ndx[i];
      }
   } 
   for (i = 0; i < mylen; i++) {
      vptr[i] = 0.;
   }
   id = 0;
   if (mynspec > 0) {
      for (i = 0; i < mycln; i++) {
         for (js = 0; js < mynspec; js++) {
            is = species[js];
            vptr[id] += domain->specfrac[myndx[i]].mass_frac[is] *
                        domain->den[myndx[i]];
         }
         id++;
      }
      for (i = mycln; i < mycln + mymix; i++) {
         int grd = -domain->ireg[myndx[i]];
         while (grd > 0) {
            if (domain->ireg[grd] == mat) {
               for (js = 0; js < mynspec; js++) {
                  is = species[js];
                  vptr[id] += domain->specfrac[grd].mass_frac[is] *
                                domain->den[grd];
               }
               id++;
               break;
            }
            grd = grd - domain->nnalls;
            grd = domain->lnkmix[grd];
         }
      }
   } else {
      data  = (double *)ProblemArray_ptr(varname,domain->hash);
      for (i = 0; i < mycln; i++) {
         vptr[id++] = (double)data[myndx[i]];
      }
      if (mat != -1) {
         for (i = mycln; i < mycln + mymix; i++) {
            int grd = -domain->ireg[myndx[i]];
            while (grd > 0) {
               if (domain->ireg[grd] == mat) {
                  vptr[id++] = (double)data[grd];
                  break;
               }
               grd = grd - domain->nnalls;
               grd = domain->lnkmix[grd];
            }
         }
      }
   } 
   for (i = 0; i < mylen; i++) {
     ndx[i] = myndx[i];
   }
   *len = mylen;
   FREEMEM(myndx);
}   
static void fillvar_getcoord(double *x,double *y,double *z,double *r,double *t, 
                      int *ndx, int len, int array_type, Domain_t *domain)
{
   int i;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8; 
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8; 
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8; 
   if (ndims == 2) {
     if (array_type == ZONAL_ARRAY) {
        NDSET2D(domain->x,x1,x2,x3,x4);
        NDSET2D(domain->y,y1,y2,y3,y4);
        for (i = 0; i < len; i++) {
           x[i] = 0.25 * (x1[ndx[i]] + x2[ndx[i]] + x3[ndx[i]] + x4[ndx[i]]);
           y[i] = 0.25 * (y1[ndx[i]] + y2[ndx[i]] + y3[ndx[i]] + y4[ndx[i]]);
        }
     } else {
        for (i = 0; i < len; i++) {
           x[i] = domain->x[ndx[i]];
           y[i] = domain->y[ndx[i]];
        }
     }
   } else {
      if (array_type == ZONAL_ARRAY) {
         NDSET3D(domain->x,x1,x2,x3,x4,x5,x6,x7,x8);
         NDSET3D(domain->y,y1,y2,y3,y4,y5,y6,y7,y8);
         NDSET3D(domain->z,z1,z2,z3,z4,z5,z6,z7,z8);
         for (i = 0; i < len; i++) {
            int ip = ndx[i];
            x[i] = 0.125 * (x1[ip] + x2[ip] + x3[ip] + x4[ip] +
	                    x5[ip] + x6[ip] + x7[ip] + x8[ip] );
	    y[i] = 0.125 * (y1[ip] + y2[ip] + y3[ip] + y4[ip] +
	                    y5[ip] + y6[ip] + y7[ip] + y8[ip] );
	    z[i] = 0.125 * (z1[ip] + z2[ip] + z3[ip] + z4[ip] +
	                    z5[ip] + z6[ip] + z7[ip] + z8[ip] );
         } 
      } else {
        for (i = 0; i < len; i++) {
           x[i] = domain->x[ndx[i]];
           y[i] = domain->y[ndx[i]];
           z[i] = domain->z[ndx[i]];
        }
      } 
   } 
   Transform_xyz2rt(x,y,z,r,t,len, NULL);
}
void fillvar_spline(double *vptr, double *x, double *y, double *z, double *r, 
                    double *t, int len, Spline_t *spline, double xmin, 
		    double xmax, char *cnst)
{
   char msg[MAXLINE];
   double *ind;
   int i;
   int flag;
   int cflag;
   if (!strcmp("x",spline->indlab)) ind = x;
   if (!strcmp("y",spline->indlab)) ind = y;
   if (!strcmp("z",spline->indlab)) ind = z;
   if (!strcmp("t",spline->indlab)) ind = t;
   if (!strcmp("r",spline->indlab)) ind = r;
   if (cnst != NULL) {
      ps = NULL;
      symflag = 0; 
   }
   for (i = 0; i < len; i++) {
      flag = 1;
      if (cnst != NULL) {
         sprintf(msg,"%.14g",x[i]);
         gpdef0(0,"meshx",msg);
         sprintf(msg,"%.14g",y[i]);
         gpdef0(0,"meshy",msg);
         sprintf(msg,"%.14g",z[i]);
         gpdef0(0,"meshz",msg);
         sprintf(msg,"%.14g",r[i]);
         gpdef0(0,"meshr",msg);
         sprintf(msg,"%.14g",t[i]);
         gpdef0(0,"mesht",msg);
         line = cnst;
         ps   = line;
         flag = geti(&cflag);
      }
      if ((flag) && (ind[i] >= xmin) && (ind[i] <= xmax)) {
         spline_eval(ind[i], &vptr[i], spline);
      }
   }
   if (cnst != NULL) {
      symflag = 0;
      line = lnbuf;
      ps   = NULL;
   }
}
static void fillvar_expression(double *vptr, double *x, double *y, double *z, 
                        double *r, double *t, int len, char *func, 
			char *cnst, int mode)
{
   char msg[MAXLINE];
   int i;
   int cflag;
   int flag;
   double scl;
   ps = NULL;
   symflag = 0; 
   for (i = 0; i < len; i++) {
      sprintf(msg,"%.14g",x[i]);
      gpdef0(0,"meshx",msg);
      sprintf(msg,"%.14g",y[i]);
      gpdef0(0,"meshy",msg);
      sprintf(msg,"%.14g",z[i]);
      gpdef0(0,"meshz",msg);
      sprintf(msg,"%.14g",r[i]);
      gpdef0(0,"meshr",msg);
      sprintf(msg,"%.14g",t[i]);
      gpdef0(0,"mesht",msg);
      flag = 1;
      if (cnst != NULL) {
         line = cnst;
         ps   = line;
         flag = geti(&cflag);
      }
      if (flag) {
         line = func;
         ps   = line;
         if (mode == 0) {
            vptr[i] = getf(&cflag);
         } else {
            scl = getf(&cflag);
            vptr[i] *= scl;
         } 
      } 
   }
   symflag = 0;
   line = lnbuf;
   ps   = NULL;
}
static void fillvar_setvar(double *vptr, int *ndx, int len, char *varname, 
                   int  *species, int mynspec, int mat, int iblk, 
		   Domain_t *domain) 
{
   char *me = "fillvar_setvar";
   char msg[MAXLINE];
   int i,j;
   int id;
   int ir;
   int is;
   int js;
   int *myndx;
   double *data;
   ProblemArray_t *prb;
   id = 0;
   if (mynspec > 0) {
      data = domain->den;
      for (i = 0; i < len; i++) {
         int grd = -domain->ireg[ndx[i]];
         double den;
         double denp;
         double denpinv;
         double massf;
         double invmassf;
         if (grd > 0) {
            while (grd > 0) {
               if (domain->ireg[grd] == mat) {
                  den  = domain->den[grd];
                  for (is = 0; is < reg[mat].nspec; is++) {
                     domain->specfrac[grd].mass_frac[is] *= den;
                  }
                  massf = 0.;
                  for (js = 0; js < mynspec; js++) {
                     is   = species[js];
                     massf +=  domain->specfrac[grd].mass_frac[is] ;
                  }
                  invmassf = 1. / ( massf + ptiny);
                  for (js = 0; js < mynspec; js++) {
                     is   = species[js];
                     domain->specfrac[grd].mass_frac[is] = 
                     domain->specfrac[grd].mass_frac[is] * invmassf * vptr[id] ;
                  }
                  denp = 0.;
                  for (is = 0; is < reg[mat].nspec; is++) {
                     denp += domain->specfrac[grd].mass_frac[is];
                  }
                  for (is = 0; is < reg[mat].nspec; is++) {
                     domain->specfrac[grd].mass_frac[is] /= denp;
                  }
                  domain->den[grd] = denp;
                  id++;
                  break;
               }
               grd = grd - domain->nnalls;
               grd = domain->lnkmix[grd];
            }
         } else {
            grd = ndx[i];
            den  = domain->den[grd];
            for (is = 0; is < reg[mat].nspec; is++) {
               domain->specfrac[grd].mass_frac[is] *= den;
            }
            massf = 0.;
            for (js = 0; js < mynspec; js++) {
                is   = species[js];
               massf +=  domain->specfrac[grd].mass_frac[is] ;
            }
            invmassf = 1. / ( massf + ptiny);
            for (js = 0; js < mynspec; js++) {
               is   = species[js];
               domain->specfrac[grd].mass_frac[is] = 
               domain->specfrac[grd].mass_frac[is] * invmassf * vptr[id] ;
            }
            denp = 0.;
            for (is = 0; is < reg[mat].nspec; is++) {
               denp += domain->specfrac[grd].mass_frac[is];
            }
            for (is = 0; is < reg[mat].nspec; is++) {
               domain->specfrac[grd].mass_frac[is] /= denp;
            }
            domain->den[grd] = denp;
            id++;
         }
      }
   } else {
      data  = (double *)ProblemArray_ptr(varname,domain->hash);
      if (mat != -1) {
         for (i = 0; i < len; i++) {
            int grd = -domain->ireg[ndx[i]];
            if (grd > 0) {
               while (grd > 0) {
                  if (domain->ireg[grd] == mat) {
                     data[grd] = vptr[id++];
                     break;
                  }
                  grd = grd - domain->nnalls;
                  grd = domain->lnkmix[grd];
               }
            } else {
               data[ndx[i]] = vptr[id++];
            } 
         } 
      } else {
         for (i = 0; i < len; i++) {
            data[ndx[i]] = vptr[id++];
         }
      } 
   }
   if (mat != -1) {
      for (i = 0; i < domain->nnalls; i++) {
         if (domain->ireg[i] < 0) domain->ireg[i] = -1;
      }
   }
   if ((mat != -1) || (species != NULL)) {
   }
}

static void fillvar_value(double *vptr, double *x, double *y, double *z, double *r, 
                   double *t, int len, double value, char *cnst) 
{
   char *me = "fillvar_value";
   char msg[MAXLINE];
   int i;
   int *flag;
   int cflag;
   if (cnst != NULL) {
      ps = NULL;
      symflag = 0; 
   }
   flag = MALLOT(int, len);
   for (i = 0; i < len; i++) {
      flag[i] = 1;
      if (cnst != NULL) {
         sprintf(msg,"%.14g",x[i]);
         gpdef0(0,"meshx",msg);
         sprintf(msg,"%.14g",y[i]);
         gpdef0(0,"meshy",msg);
         sprintf(msg,"%.14g",z[i]);
         gpdef0(0,"meshz",msg);
         sprintf(msg,"%.14g",r[i]);
         gpdef0(0,"meshr",msg);
         sprintf(msg,"%.14g",t[i]);
         gpdef0(0,"mesht",msg);
         line = cnst;
         ps   = line;
         flag[i] = geti(&cflag);
      }
   }
   for (i = 0; i < len; i++) {
       if (flag[i] == 1) {
          vptr[i] = value;
       }
   }
   FREEMEM(flag);
   if (cnst != NULL) {
      symflag = 0;
      line = lnbuf;
      ps   = NULL;
   }
}
