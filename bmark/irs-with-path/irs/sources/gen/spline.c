#include "irs.h"
#include "irsgen.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Rgst.h"
#include "Spline.h"
#include "Hash.h"
#include "NodeList.h"
#include "Transform.h"
typedef struct {
   int    optype;
   char   opname[MAXWORD];
   char   oprand[MAXWORD];
   double *opdata;  
} SPLINE_OPS;
#define MAXSPLINEOPS 30   
#define SPLINE_CONVERT 30
#define MAX_ITER 100 
static int spline_getrt(double *r, double *t, int n, double xmin, 
                        double xmax, double x0, double y0, Spline_t *spline);
static int spline_monot(Spline_t *spline);
static int spline_getdata(char *var, char *valid, int type, Spline_t *spline);
static int spline_calc(Spline_t *spline );
static void spline_copy(Spline_t * next_sp, Spline_t * spline_ref);
static void spline_add(Spline_t *spline);
static void spline_convert(Spline_t *spline, char* op) ;
static void spline_repack(Spline_t *spline, double ll, double ul); 
static int spline_resample(double *pts, double *dep, int type, int len,
                            Spline_t *spline, char *op);
static void spline_flip(double *data, int len);
int spline_input( void )
{
   char *me = "spline_input";
   char msg[128];
   char op[MAXLINE];
   char name[MAXLINE];
   char splinename[MAXLINE];
   char valid[6];
   int i;
   int j;
   int combined = 0;
   int ns;
   int iop;
   int len;
   int cflag;
   int gotone;
   int goterr;
   int gotref;
   int nsplineops;
   int skip;
   int sublen;
   int loopcount;
   int first;
   double *data;
   double *subdata;
   double *temp;
   double *dptr;
   double ll;
   double ul;
   double lower;
   double upper;
   Spline_t *spline;
   Spline_t *spline_ref;
   Spline_t *ref;
   Spline_t *next_sp;
   Spline_t *sptr;
   Spline_t *lptr;
   SPLINE_OPS *splineop;
   geta(op);
   if (!strcmp("delete", op)){
       geta(op);
       sprintf(name, "%s", op);
       spline_delete(name);
       return (0);
   }else{
       strcpy(splinename, op);
   }
   spline = spline_find(splinename);
   if (spline == NULL) { spline = Spline_construct(1); } 
   sprintf(spline->name,splinename);
   geta(op);
   gotref = 0;
   if (!strcmp("cubic",op)) {
      spline->type = CUBIC;
   } else if (!strcmp("ref",op)) {
      geta(op);
      spline_ref = spline_find(op);
      if (spline_ref != NULL) {
         gotref = 1;
         spline->flip  = spline_ref->flip;
         spline->len   = spline_ref->len;
         spline->ind   = ALLOT(double,spline_ref->len);
         spline->dep   = ALLOT(double,spline_ref->len);
         spline->dep1  = spline_ref->dep1;
         spline->dep2  = spline_ref->dep2;
         spline->type  = spline_ref->type;
         spline->coord = spline_ref->coord;
         spline->x0 = spline_ref->x0;
         spline->y0 = spline_ref->y0;
         spline->z0 = spline_ref->z0;
         strcpy(spline->deplab,spline_ref->deplab);
         strcpy(spline->indlab,spline_ref->indlab);
         for (i = 0; i < spline->len; i++) {
           spline->ind[i] = spline_ref->ind[i];
           spline->dep[i] = spline_ref->dep[i];
         }
         peekc(op); 
         if (!strcmp(op, "resample")) {
             geta(op);
             geta(op);
             len  = getflst(&data, -1);
             temp = MALLOT(double, len);
             next_sp        = spline;
             sptr           = spline;
             ref            = spline_ref;
             loopcount = 1;
             FREEMEM(spline->b); 
             FREEMEM(spline->c); 
             FREEMEM(spline->d);
             FREEMEM(spline->ind);
             FREEMEM(spline->dep);
             spline_copy(next_sp, spline_ref);                  
	     while (spline_ref != NULL) {
                 skip = 0;
                 if ((!strcmp(op, "xy")) || (!strcmp(op, "yx"))) {
                     skip = spline_resample(data, temp, XYDATA, len, next_sp, op);
                     if ( (skip != 0) && (ref->next == NULL)) {
                         sprintf(msg, "The specified range is outside the limits of spline %s", 
                                      next_sp->name);  
                         ctlwarning(me, msg);
                         return(-1); 
                     }
                     if (skip == 0) {
                         next_sp->coord = XYDATA;
                         FREEMEM(next_sp->b);
                         FREEMEM(next_sp->c);
                         FREEMEM(next_sp->d);
                         if (!strcmp(op, "xy")){
                             strcpy(next_sp->indlab, "x");
                             strcpy(next_sp->deplab, "y");
                         } else {
                             strcpy(next_sp->indlab, "y");
                             strcpy(next_sp->deplab, "x");
                         }
                     }
                 } else if ((!strcmp(op, "rt")) || (!strcmp(op, "tr"))) {
                     skip = spline_resample(data, temp, RTDATA, len, next_sp, op);
                     if ((skip != 0) && (ref->next == NULL)) {
                         sprintf(msg, "The specified range is outside the limits of spline %s", 
                                      next_sp->name);  
                         ctlwarning(me, msg);
                         return(-1);
                     }
                     if (skip == 0) {
                         next_sp->coord = RTDATA;
                         FREEMEM(next_sp->b);
                         FREEMEM(next_sp->c);
                         FREEMEM(next_sp->d);
                         if (!strcmp(op, "tr")){
                             strcpy(next_sp->indlab, "t");
                             strcpy(next_sp->deplab, "r");
                         } else {
                             strcpy(next_sp->indlab, "r");
                             strcpy(next_sp->deplab, "t");
                         }
                     }
                 } else {
                     sprintf(msg, "Spline resample coord must be either xy or rt.");
                     ctlwarning(me, msg);
                     return(-1);
                 }
                 if (skip == 0) spline_monot(next_sp);    
	         spline_ref = spline_ref->next;
		 if (spline_ref != NULL) {
		    if (skip == 0) {
                       next_sp = Spline_construct(1);
		       sptr->next = next_sp;
		       sptr = next_sp;
		       loopcount++;
                    }
                    FREEMEM(next_sp->b); 
                    FREEMEM(next_sp->c); 
                    FREEMEM(next_sp->d);
                    FREEMEM(next_sp->ind);
                    FREEMEM(next_sp->dep);
                    spline_copy(next_sp, spline_ref);
		    if (skip == 0) sprintf(next_sp->name, "%s_%d", spline->name, loopcount);
		 }
             }
             if (skip != 0) {
                lptr = spline;
                while (lptr->next->next != NULL) lptr = lptr->next;
                lptr->next = NULL;
                FREEMEM(next_sp->dep);
                FREEMEM(next_sp->ind);
                if (next_sp->type == CUBIC){
                    FREEMEM(next_sp->b);
                    FREEMEM(next_sp->c);
                    FREEMEM(next_sp->d);
                }
                FREEMEM(next_sp);
                FREEMEM(data);
                FREEMEM(temp);
             }
         } 
      } else {
         sprintf(msg,"Spline reference name %s not recognized.", op);
         ctlwarning(me, msg);
         return(-1);
      }
   } else if (!strcmp("linear",op)) {
      spline->type = LINEAR;
   } else if (!strcmp("=",op)) {
     combined = 1;
     geta(op);
     spline_ref = spline_find(op);
     if (spline_ref == NULL){
         sprintf(msg,"Spline %s does not exist.",op);
         ctlwarning(me, msg);
         return(-1);
      }
      first = 1;
      sptr = spline;    
      j = 2;
      while (spline_ref != NULL) { 
          spline_copy(sptr, spline_ref);
          skip = 0;
          if (first) {
             peekc(op);
          }
          if (!strcmp(op, "on")) {
              if (first) { 
                  geta(op);
                  ll = getf(&cflag);
                  ul = getf(&cflag);
                  first = 0;
              }
              if (ll < spline_ref->ind[0]) {
                  lower = spline_ref->ind[0];
              }   else if (ll >= spline_ref->ind[spline_ref->len - 1]){
                  skip = 1;
              } else {
                  lower = ll;
              }
              if (ul > spline_ref->ind[spline_ref->len - 1]) {
                  upper = spline_ref->ind[spline_ref->len - 1];
              } else if (ul <= spline_ref->ind[0]) {
                  skip = 1;
              } else {
                  upper = ul;
              }
              if (!skip){
                  spline_repack(sptr, lower, upper); 
              }
          }
          if (!skip) {
              if (!strcmp(op, "on")) {
                  spline_calc(sptr);
              }
              if (spline_ref->next != NULL) {
                  next_sp = Spline_construct(1);
                  sptr->next = next_sp;
                  sptr = next_sp;
                  sprintf(next_sp->name, "%s_%d", spline->name, j);
                  j++;
              }
          }
          if (spline_ref->next != NULL) {
              FREEMEM(sptr->ind);
              FREEMEM(sptr->dep);
              FREEMEM(sptr->b);
              FREEMEM(sptr->c);
              FREEMEM(sptr->d);
          }
          spline_ref = spline_ref->next;
      } 
      peekc(op);
      if (iplusmin == 0) {
         sprintf(msg,"A combined spline must be a combination of at least two splines. ");
         ctlwarning(me, msg);
         return(-1);
      } 
      while (iplusmin == 1) {
          geta(op);
          geta(op);
          spline_ref = spline_find(op);
          if (spline_ref == NULL) {
             sprintf(msg,"Spline %s does not exist.",op);
             ctlwarning(me, msg);
             return(-1);
          }
          next_sp = Spline_construct(1);
          spline_copy(next_sp, spline_ref);
          sprintf(next_sp->name, "%s_%d", spline->name, j);
          j++;
          sptr->next = next_sp; 
          sptr = sptr->next; 
          peekc(op);
          first = 1;
          while (spline_ref != NULL) {
              skip = 0;
              if (!strcmp(op, "on")) {
                  if (first) {          
                      geta(op);
                      ll = getf(&cflag);
                      ul = getf(&cflag);
                      first = 0;
                  }
                  if (ll < spline_ref->ind[0]) {
                      lower = spline_ref->ind[0];
                  }   else if (ll >= spline_ref->ind[spline_ref->len - 1]) {
                      skip = 1;
                  } else {
                      lower = ll;
                  }
                  if (ul > spline_ref->ind[spline_ref->len - 1]) {
                      upper = spline_ref->ind[spline_ref->len - 1];
                  } else if (ul <= spline_ref->ind[0]) {
                      skip = 1;
                  } else {
                      upper = ul;
                  }
                  if (!skip) {
                      spline_repack(sptr, lower, upper); 
                  }
              }
              if (!skip){
                  if (!strcmp(op, "on")) {
                      spline_calc(sptr);     
                  }
                  if (spline_ref->next != NULL) {
                      next_sp = Spline_construct(1);
                      sptr->next = next_sp;
                      sptr = next_sp;
                      sprintf(next_sp->name, "%s_%d", spline->name, j);
                      j++;
                  }
              }
              spline_ref = spline_ref->next;
              if (spline_ref != NULL) {
                  FREEMEM(sptr->ind);
                  FREEMEM(sptr->dep);
                  FREEMEM(sptr->b);
                  FREEMEM(sptr->c);
                  FREEMEM(sptr->d);
                  spline_copy(next_sp, spline_ref);
              }
          }
          peekc(op);
      } 
   } else {
     sprintf(msg,"Spline type %s not recognized.",op);
     ctlwarning(me, msg);
     return(-1);
   }
   splineop = MALLOT(SPLINE_OPS,MAXSPLINEOPS);
   nsplineops = 0;
   gotone = 1;
   while (gotone) {
      peekc(op);
      gotone = 1;
      goterr = 0;
      if (!strcmp(op,"x")) {
         geta(op);
         strcpy(valid,"vxy");
         goterr = spline_getdata(op,valid,XYDATA,spline);
         if (goterr) {
            sprintf(msg,"Error reading spline %s data",spline->name);
            gotone = 0;
         }
      } else if (!strcmp(op,"y")) {
         geta(op);
         strcpy(valid,"xy");
         goterr = spline_getdata(op,valid,XYDATA,spline);
         if (goterr) {
            sprintf(msg,"Error reading spline %s data",spline->name);
            gotone = 0;
         }
      } else if (!strcmp(op,"r")) {
         geta(op);
         strcpy(valid,"vrt");
         goterr = spline_getdata(op,valid,RTDATA,spline);
         if (goterr) {
            sprintf(msg,"Error reading spline %s data",spline->name);
            gotone = 0;
         }
      } else if (!strcmp(op,"t")) {
         geta(op);
         strcpy(valid,"vrt");
         goterr = spline_getdata(op,valid,RTDATA,spline);
         if (goterr) {
            sprintf(msg,"Error reading spline %s data",spline->name);
            gotone = 0;
         }
      } else if (!strcmp(op,"v")) {
         geta(op);
         strcpy(valid,"vrtx");
         if (spline->coord == UNKNOWNDATA) {
            sprintf(msg,"Variable data type cannot be the independent variable in spline %s.",spline->name);
            gotone = 0;
            goterr = 1;
            break;
         }
         if (!strcmp(spline->indlab,"r")) spline->coord = VRDATA;
         if (!strcmp(spline->indlab,"t")) spline->coord = VTDATA;
         if (!strcmp(spline->indlab,"x")) spline->coord = VXDATA;
         goterr = spline_getdata(op,valid,spline->coord,spline);
         if (goterr) {
            sprintf(msg,"Error reading spline %s data",spline->name);
            gotone = 0;
         }
      } else if (!strcmp(op,"d0")) {
         geta(op);
         spline->dep1 = getf(&cflag);
      } else if (!strcmp(op,"d1")) {
         geta(op);
         spline->dep2 = getf(&cflag);
      } else if (!strcmp(op,"axis")) {
         geta(op);
         spline->axis_x = getf(&cflag);
         spline->axis_y = getf(&cflag);
	 if (ndims == 3) spline->axis_z = getf(&cflag);
      } else if (!strcmp(op,"normal")) {
         geta(op);
         spline->norm_x = getf(&cflag);
         spline->norm_y = getf(&cflag);
	 spline->norm_z = 0.;
	 if (ndims == 3) spline->norm_z = getf(&cflag);
      } else if (!strcmp(op,"add")) {
         geta(op);
         splineop[nsplineops].optype = SPLINE_ADD;
         sprintf(splineop[nsplineops].opname,"add");
         geta(op);
         strcpy(splineop[nsplineops].oprand,op);
         splineop[nsplineops].opdata = MALLOT(double,1);
         splineop[nsplineops].opdata[0] = getf(&cflag); 
         nsplineops++;
      } else if (!strcmp(op,"invert")) {
         geta(op);
         splineop[nsplineops].optype = SPLINE_INVERT;
         sprintf(splineop[nsplineops].opname,"invert");
         geta(op);
         strcpy(splineop[nsplineops].oprand,op);
         nsplineops++;
      } else if (!strcmp(op,"convert")) {
         geta(op);
         splineop[nsplineops].optype = SPLINE_CONVERT;
         sprintf(splineop[nsplineops].opname,"convert");
         geta(op);
         strcpy(splineop[nsplineops].oprand,op);
         nsplineops++;
      } else if (!strcmp(op,"scale")) {
         geta(op);
         splineop[nsplineops].optype = SPLINE_SCALE;
         sprintf(splineop[nsplineops].opname,"scale");
         geta(op);
         strcpy(splineop[nsplineops].oprand,op);
         splineop[nsplineops].opdata = MALLOT(double,1);
         splineop[nsplineops].opdata[0] = getf(&cflag); 
         nsplineops++;
      } else if (!strcmp(op,"offset")) {
         geta(op);
         spline->x0 = getf(&cflag);
         spline->y0 = getf(&cflag);
         if (ndims == 3) spline->z0 = getf(&cflag);
         sptr = spline->next;
         while(sptr != NULL){
            sptr->x0 = spline->x0;
            sptr->y0 = spline->y0;
            if (ndims == 3){ 
                sptr->z0 = spline->z0;
            }
            sptr = sptr->next;
         }
      } else if (!strcmp(op,"delta")) {
         geta(op);
         splineop[nsplineops].optype = SPLINE_DELTA;
         strcpy(splineop[nsplineops].oprand,spline->deplab);
         sprintf(splineop[nsplineops].opname,"delta");
         peekc(op);
         if (!strcmp(op,"=")) {
            char *expression;
            geta(op);
	    len = spline->len;
	    splineop[nsplineops].opdata = MALLOT(double, len);
	    cflag = lineop_grab(&expression, "}", ps); 
	    ps = NULL;
            for (i = 0; i < len; i++) {
               if (spline->flip == 1) {
                  sprintf(op,"%.14g",spline->ind[len - 1 - i]);
               } else {
                  sprintf(op,"%.14g",spline->ind[i]);
               } 
               gpdef0(0, "indep", op);
	       line = expression;
	       ps   = line;
	       splineop[nsplineops].opdata[i] = getf(&cflag);
            }
	    FREEMEM(expression);
            line = lnbuf;
            ps   = NULL;
         } else {
            len = getflst(&splineop[nsplineops].opdata,-1);
            if (len != spline->len) {
               goterr = 1;
               sprintf(msg,"Len of delta data not equal to spline %s len.",
                       spline->name);
               break;
            }
         }
         nsplineops++;
      } else {
         gotone = 0;
      } 
   }
   if ((!goterr) && ((spline->ind == NULL) || (spline->dep == NULL))) {
      sprintf(msg,"Missing independent or dependent variable in spline %s.",
              spline->name);
      goterr = 1;
   }
   if (goterr) {
     ctlwarning(me, msg);
     return(-1);
   }
   for (iop = 0; iop < nsplineops; iop++) {
      if (!strcmp(spline->indlab,splineop[iop].oprand)) {
         data = spline->ind;
      } else if (!strcmp(spline->deplab,splineop[iop].oprand)) {
         data = spline->dep;
      } else if (!strcmp("delta",splineop[iop].oprand)) {
         for (i = iop + 1; i < nsplineops; i++) {
            if ( splineop[i].optype == SPLINE_DELTA ) break;
         }
	 if (i >= nsplineops) {
	    sprintf(msg,"Operation %s on delta failed in spline %s.\n\tMake sure delta is specified AFTER this operation.", splineop[iop].opname,spline->name);
	    ctlwarning(me,msg);
	    continue;
	 }
	 data = splineop[i].opdata;
      } else if (splineop[iop].optype == SPLINE_CONVERT) {
      } else {
         sprintf(msg,"Operand %s not valid for spline %s operation.",
                 splineop[iop].oprand,spline->name);
         ctlwarning(me, msg);
         return(-1);
      }
      switch (splineop[iop].optype) {
         case SPLINE_INVERT:
            temp = MALLOT(double,spline->len);
            for (i = 0; i < spline->len; i++) {
               temp[i] = data[i] ;
            }
            for (i = 0; i < spline->len; i++) {
               data[i] = temp[spline->len - 1 - i] ;
            }
            FREEMEM(temp);
            break;
         case SPLINE_CONVERT:
            spline_convert(spline, splineop[iop].oprand);
            gotref = 0;
            break;
         case SPLINE_SCALE:
            sptr = spline;
            while(sptr != NULL){
                if (!strcmp(sptr->indlab,splineop[iop].oprand)) {
                    data = sptr->ind;
               } else if (!strcmp(sptr->deplab,splineop[iop].oprand)) {
                    data = sptr->dep;
               } else if (!strcmp("delta",splineop[iop].oprand)) {
                    if (spline->next != NULL){
                        break;
                    }
	            data = splineop[i].opdata;
               }
               for (i = 0; i < sptr->len; i++) {
                     data[i] *= splineop[iop].opdata[0];
               }
               sptr = sptr->next;
            }
            FREEMEM(splineop[iop].opdata);
            break;
         case SPLINE_ADD:
            sptr = spline;
            while(sptr != NULL){
                if (!strcmp(sptr->indlab,splineop[iop].oprand)) {
                    data = sptr->ind;
               } else if (!strcmp(sptr->deplab,splineop[iop].oprand)) {
                    data = sptr->dep;
               } else if (!strcmp("delta",splineop[iop].oprand)) {
                    if (spline->next != NULL){
                        break;
                    }
	            data = splineop[i].opdata;
               }
               for (i = 0; i < sptr->len; i++) {
                     data[i] += splineop[iop].opdata[0];
               }
               sptr = sptr->next;
            }
            FREEMEM(splineop[iop].opdata);
            break;
         case SPLINE_DELTA:
            if (spline->next != NULL) {
                sprintf(msg, "Delta's not allowed for combined splines. \
                        spline %s is a combined spline", spline->name);
                ctlwarning(me, msg);
                break;
            }
            if (spline->flip) {
               for (i = 0; i < spline->len; i++) {
                  spline->dep[i] = spline->dep[i] + 
                                      splineop[iop].opdata[spline->len - 1 - i];
               }
            } else {
               for (i = 0; i < spline->len; i++) {
                  spline->dep[i] = spline->dep[i] + splineop[iop].opdata[i];
               }
            }
            FREEMEM(splineop[iop].opdata);
            break;
         default:
            break;
      }
   }
   FREEMEM(splineop);
   if (gotref == 0) {
      goterr = spline_monot(spline);
   }
   if (goterr) {
      sprintf(msg,"Independent variable in spline %s is not monotonic.",
             spline->name);
      ctlwarning(me, msg);
      return(-1);
   }
   if (!combined) goterr = spline_calc(spline);
   if (goterr) {
      sprintf(msg,"Error calculating spline %s coefficients.",
             spline->name);
      ctlwarning(me, msg);
      return(-1);
   }
   spline_add(spline);
   return(0);
}   
static void spline_add(Spline_t *spline)
{
   char name[MAXLINE];
   Spline_t *spline_ptr;
   sprintf(name,"Spline_%s",spline->name);
   rgst_add(name,"Spline_t",spline,NULL);
}
void spline_free( void )
{
   char name[MAXLINE];
   char *me = "spline_free";
   char ** names = NULL;
   int num_sp, i;
   Spline_t *spline_ptr;
   Spline_t *sptr;
   names = rgst_list_objs_by_type(&num_sp, "Spline_t");
   for (i = 0; i<num_sp; i++) {
      spline_ptr = rgst_get_t(names[i], "Spline_t");
      if (spline_ptr == NULL)
         ctlerror(me, logic_err);
      rgst_del(names[i]);
      while(spline_ptr != NULL){
          if (spline_ptr->len > 0) {
              FREEMEM(spline_ptr->ind);
              FREEMEM(spline_ptr->dep);
              if (spline_ptr->type == CUBIC) {
                 FREEMEM(spline_ptr->b);
                 FREEMEM(spline_ptr->c);
                 FREEMEM(spline_ptr->d);
              }
          }
          sptr = spline_ptr;
          spline_ptr = spline_ptr->next; 
          FREEMEM(sptr);
      } 
   }
   for (i=0; i<num_sp; i++)
       FREEMEM(names[i]);
   FREEMEM(names);
}
static int spline_monot(Spline_t *spline)
{
  int i, n;
  double direction;
  double tmpd;
  double *x, *y; 
  double *tmpx;
  double *tmpy; 
  n = spline->len - 1;
  x = spline->ind;
  y = spline->dep;
  if (n > 0) {
    direction = ( x[0] < x[1] ? 1.0 : -1.0 );
    for (i=0; i<n; i++) {
      if (direction*x[i] >= direction*x[i+1]) {
        return(-1);
      }
    }
    spline->flip = (direction < 0);
    if (spline->flip) {
      n = spline->len;
      tmpx = MALLOT(double,n);
      tmpy = MALLOT(double,n);
      for (i = 0; i < n; i++) {
        tmpx[i] = x[i];
        tmpy[i] = y[i];
      }
      for (i = 0; i < n; i++) {
        x[i] = tmpx[n - 1 - i];
        y[i] = tmpy[n - 1 - i];
      }
      FREEMEM(tmpx);
      FREEMEM(tmpy);
      tmpd = spline->dep1;
      spline->dep1 = spline->dep2;
      spline->dep2 = tmpd;
    }
  }
  return(0);
}
static int spline_getdata(char *var, char *valid, int coord, Spline_t *spline) {
   int i;
   int len;
   int cflag;
   int j;
   int error = 0;
   char *expression;
   char op[MAXWORD];
   double *data1;
   double *data2;
   if (ifnotin(valid,var)) {
      error = 1;
      return(error);
   }
   if (spline->coord == UNKNOWNDATA) {
      strcpy(spline->indlab,var);
      peekc(op);
      if (isalpha(op[0])) {
         geta(op);
         if (ifnotin(valid,op)) {
            error = 1;
            return(error);
         }
         strcpy(spline->deplab,op);
         if (!strcmp(spline->deplab,"v")) { 
            if (!strcmp(spline->indlab,"r")) coord = VRDATA;
            if (!strcmp(spline->indlab,"t")) coord = VTDATA;
            if (!strcmp(spline->indlab,"x")) coord = VXDATA;
         }
         len = getflst(&data1,-1);
         if (len%2 != 0) {
            error = 1;
            return(error);
         }
         len = len/2;
         if ((spline->ind != NULL) || (spline->dep != NULL)) {
            error = 1;
            return(error);
         }
         spline->ind = MALLOT(double,len);
         spline->dep = MALLOT(double,len);
	 j = 0;
         for (i = 0; i < len; i++) {
            spline->ind[i] = data1[j++];
            spline->dep[i] = data1[j++];
         }
         FREEMEM(data1);
         spline->len = len;
      } else {
         len = getflst(&data1,-1);
         if (spline->ind != NULL) {
            error = 1;
            return(error);
         }
         spline->ind = MALLOT(double,len);
         for (i = 0; i < len; i++) {
            spline->ind[i] = data1[i];
         }
         FREEMEM(data1);
         spline->len = len;
      } 
   } else if (spline->coord == coord) {
      if (spline->len == 0) {
         error = 1;
         return(error);
      }
      if (spline->dep != NULL) {
         error = 1;
         return(error);
      }
      strcpy(spline->deplab,var);
      peekc(op);
      if (!strcmp(op,"=")) {
         geta(op);
	 len   = spline->len;
	 data1 = MALLOT(double, len);
	 cflag = lineop_grab(&expression, "}", ps); 
	 ps = NULL;
         for (i = 0; i < len; i++) {
            sprintf(op,"%.14g",spline->ind[i]);
            gpdef0(0, "indep", op);
	    line = expression;
	    ps   = line;
	    data1[i] = getf(&cflag);
         }
	 FREEMEM(expression);
         line = lnbuf;
         ps   = NULL;
      } else {
         len = getflst(&data1,-1);
         if (len != spline->len) {
            error = 1;
            return(error);
         }
      } 
      spline->dep = MALLOT(double,len);
      for (i = 0; i < len; i++) {
         spline->dep[i] = data1[i];
      }
      FREEMEM(data1);
   } 
   spline->coord = coord;
   return(error);
}

#ifdef SILO
int spline_rdsilo(DBfile *idbid) {
   char *me = "spline_rdsilo";
   char msg[MAXLINE];
   char name[MAXLINE];
   char cdir[MAXLINE];
   int ns;
   int nspline;
   int error;
   int dims[3];
   Spline_t *spline;
   error = 0;
   dims[0] = 1;
   if (DBGetDir(idbid, cdir)  != 0) ctlerror(me,gv_errmsg_DBGetDir);
   DBShowErrors(DB_NONE, NULL);
   error = DBSetDir(idbid,"/Global/Splines");
   if (error != 0) {
      DBShowErrors(DB_TOP, NULL);
      return(0);
   }
   error += DBReadVar(idbid, "NumSplines", &nspline);
   for (ns = 0; ns < nspline; ns++) {
      sprintf(name,"Spline%d",ns);
      error = DBSetDir(idbid,"/Global/Splines");
      if (error != 0) {
         DBShowErrors(DB_TOP, NULL);
         return(0);
      }
      spline = rgst_read_linked_list(idbid, name, "Spline_t");    
      if (spline == NULL) ctlerror(me,"error reading spline in func rgst_read_linked_list");
      spline_calc(spline);
      spline_add(spline);
   }
   error += DBSetDir(idbid, cdir); 
   return(error);
}
#endif

#ifdef SILO
int spline_wtsilo(DBfile *idbid) {
   char *me = "wtsplines";
   char msg[MAXLINE];
   char name[MAXLINE];
   char cdir[MAXLINE];
   char ** names = NULL;
   int i, num_sp;
   int error = 0;
   int dims[3];
   Spline_t *spline_ptr;
   dims[0] = 1;
   if (DBGetDir(idbid, cdir)  != 0) ctlerror(me,gv_errmsg_DBGetDir);
   error  = DBMkDir(idbid,"/Global/Splines");
   error += DBSetDir(idbid,"/Global/Splines");
   names = rgst_list_objs_by_type(&num_sp, "Spline_t");
   for (i = 0; i<num_sp; i++) {
      spline_ptr = rgst_get_t(names[i], "Spline_t");
      if (spline_ptr == NULL)
          ctlerror(me, logic_err);
      sprintf(name,"Spline%d",i);
      if (rgst_write_linked_list(idbid, name, "Spline_t", spline_ptr) != 0) {
	      ctlerror(me,gv_errmsg_rgst_write_linked_list);
      }
   }
   dims[0] = 1;
   error += DBSetDir(idbid,"/Global/Splines");
   error += DBWrite(idbid, "NumSplines", &num_sp, dims, 1, DB_INT);
   error += DBSetDir(idbid, cdir); 
   for (i=0; i<num_sp; i++) FREEMEM(names[i]);
   FREEMEM(names);    
   return(error);
}
#endif


static int spline_calc(Spline_t *spline )
{
   char *me = "spline_calc";
   char msg[128];
   int error;
   int n, m;
   int i;
   int IsNatural0, IsNaturalN;
   Spline_t * ptr;
   double *x, *a, *b, *c, *d;       
   double *h, *alpha, *mu, *z, *l;  
   ptr = spline;
   while(ptr != NULL){
       error = 0;
       m = ptr->len;
       n = m - 1;
       if (ptr->type == CUBIC) {
          IsNatural0 = (ptr->dep1 == plarge);
          IsNaturalN = (ptr->dep2 == plarge);
          x = ptr->ind;
          a = ptr->dep;
          b = ptr->b = ALLOT(double,m);
          c = ptr->c = ALLOT(double,m);
          d = ptr->d = ALLOT(double,m);
          h     = ALLOT(double,m);
          alpha = ALLOT(double,m);
          mu    = ALLOT(double,m);
          z     = ALLOT(double,m);
          l     = ALLOT(double,m);
          for (i=0; i<=n-1; i++){
	      h[i]= x[i+1]-x[i];
          }
          if (!IsNatural0){
	    alpha[0] = 3.0*((a[1]-a[0])/h[0] - ptr->dep1);
          }
          for (i=1; i<=n-1; i++){
	    alpha[i] = 3.0*(a[i+1]*h[i-1]-a[i]*(x[i+1]-x[i-1])+a[i-1]*h[i])/(h[i-1]*h[i]);
          }
          if (!IsNatural0){
	    l[0]  = 2*h[0];
	    mu[0] = 0.5;
	    z[0]  = alpha[0]/l[0];
          }
          else {
	    l[0]  = 1.;
	    mu[0] = 0.;
	    z[0]  = 0.;
          }
          for (i=1; i<=n-1; i++) {
	    l[i]  = 2*(x[i+1]-x[i-1]) - h[i-1]*mu[i-1];
	    mu[i] = h[i]/l[i];
	    z[i]  = (alpha[i] - h[i-1]*z[i-1])/l[i];
          }
          if (!IsNaturalN){
	    alpha[n] = 3.0*(-(a[n]-a[n-1])/h[n-1] + ptr->dep2);
	    l[n] = h[n-1]*(2. - mu[n-1]);
	    z[n] = (alpha[n] - h[n-1]*z[n-1])/l[n];
	    c[n] = z[n];
          }
          else {
	    l[n] = 1.;
	    z[n] = 0.;
	    c[n] = z[n];
          }
          for (i=n-1; i>=0; i--) {
	    c[i] = z[i] - mu[i]*c[i+1];
	    b[i] = (a[i+1]-a[i])/h[i] - h[i]*(c[i+1]+ 2.*c[i])/3.;
	    d[i] = (c[i+1] - c[i])/(3.*h[i]);
          }
          FREEMEM(h);
          FREEMEM(alpha);
          FREEMEM(mu);
          FREEMEM(z);
          FREEMEM(l);
       } else if (ptr->type == LINEAR) {
       } else {
          sprintf(msg,"Spline %s has unknown type.\n",ptr->name);
          ctlwarning(me,msg);
       }
       ptr = ptr->next;
   } 
   return(error);
}
#include "irs.h"
#include "irsgen.h"
int spline_eval(double val, double *dep, Spline_t *spline)
{
   char *me = "spline_eval";
   Spline_t * ptr;
   Spline_t * high_ptr;
   Spline_t * low_ptr;
   char msg[128];
   int i;
   int imin,imax;
   int between;
   int badpoint = 0;
   double v, x1, x2, y1, y2;
   double xmin, xmax;
   ptr = spline;
   x1 = ptr->ind[0];
   x2 = ptr->ind[ptr->len - 1];
   between = 1;
   while(ptr != NULL){
       if (x1 > ptr->ind[0]) x1 = ptr->ind[0];
       if (x2 < ptr->ind[ptr->len - 1]) x2 = ptr->ind[ptr->len - 1];
       ptr = ptr->next;
    }
    xmin = x1;
    xmax = x2;
    if (val < xmin) {
        if (fabs(val - xmin) <  (1.0e-6 * fabs(xmin))) {
            val = xmin;
        } else if ((xmin == 0.) &&  (fabs(val) < 1.0e-6)) {
            val = xmin;
        } else {
            badpoint = 1;
            *dep = 0.;
        }
    }
    if (val > xmax){
       if (fabs(val - xmax) <  (1.0e-6 * fabs(xmax))) {
          val = xmax;
       } else if ((xmax == 0.) && (fabs(val) < 1.0e-6)) {
          val = xmax;
       } else {
          badpoint = 1;
          *dep = 0;
       }
   }
   if (badpoint == 1) {
      sprintf(msg,"Bad interpolation point in spline %s",spline->name);
      ctlnotice(me,msg);
      return(1);
   }
   ptr = spline;       
   while (ptr != NULL){
      if ((val >= ptr->ind[0]) && (val <= ptr->ind[ptr->len - 1])){
         between = 0;
         break;
      }
      ptr = ptr->next;
   } 
   if (!between) {
      imin = 0;
      imax = ptr->len - 1;
      while(imax > imin){
         i = (imax + imin) >> 1;
         if ((ptr->ind[i] <= val) && ( ptr->ind[i+1] >= val)){
             imin = i;
             imax = i+1;
             break;
         } else if (ptr->ind[i] > val){
            imax = i;
         } else {
            imin = i;
         }
      } 
   } else {
      ptr = spline;
      while (ptr != NULL){
         if (val < ptr->ind[0]) {
             if (x2 > ptr->ind[0]) {
                 x2 = ptr->ind[0];
                 high_ptr = ptr;
             } 
         } 
         if (val > ptr->ind[ptr->len - 1]) {
             if (x1 < ptr->ind[ptr->len - 1]) {
                 x1 = ptr->ind[ptr->len - 1];
                 low_ptr = ptr;
             } 
         }  
         ptr = ptr->next;
      } 
      y1 = low_ptr->dep[low_ptr->len - 1];
      y2 = high_ptr->dep[0];
      *dep = y1 + ((y2-y1)/(x2-x1+ptiny))*(val-x1);
   }
   if (!between)  {
       if (imax <= imin) {
          if (fabs(val - ptr->ind[imin]) <  (1.0e-6 * fabs(ptr->ind[imin]))) {
             val = ptr->ind[imin];
          } else if ((ptr->ind[imin] == 0.) &&  (fabs(val) < 1.0e-6)) {
             val = ptr->ind[imin];
          }  else  {
             badpoint = 1;
             *dep = 0.;
          } 
       }
   }
   if (badpoint == 1) {
      sprintf(msg,"Bad interpolation point in spline %s",spline->name);
      ctlnotice(me,msg);
      return(1);
   }
   if (!between) {
       if (ptr->type == CUBIC) {
           v = val - ptr->ind[imin];
           *dep = ptr->dep[imin] + (ptr->b[imin] + (ptr->c[imin] + ptr->d[imin]*v)*v)*v; 
       } else if (ptr->type == LINEAR) {
           v = (ptr->dep[imax] - ptr->dep[imin] ) / 
           (ptr->ind[imax] - ptr->ind[imin] + ptiny);
           *dep = ptr->dep[imin] + v * (val - ptr->ind[imin]);
       } 
   }
   return(0);
}
Spline_t *spline_find(char *name) {
   char spname[MAXLINE];
   Spline_t *spline;
   sprintf(spname,"Spline_%s",name);
   spline = NULL;
   if (rgst_check_for_obj(spname)) {
      spline = (Spline_t *) rgst_get_t(spname,"Spline_t");
   }
   return(spline);
}
int spline_print(void) {
   char *me = "spline_print";
   char msg[MAXLINE];
   char op[MAXLINE];
   int i,j;
   int error;
   int count;
   int len;
   double *x, *y;
   Spline_t *spline;
   error = 0;
   geta(op);
   spline = spline_find(op);
   if (spline == NULL) {
      sprintf(msg,"Spline %s not defined.",op);
      ctlwarning(me, msg);
      spline = NULL;
      error = 1;
   } 
   len = getflst(&x,-1);
   if (len < 0) {
      sprintf(msg,"Error reading independent variable data.");
      ctlwarning(me, msg);
      error = 1;
   }
   if (error == 1) {
      return(error);
   }
   y = MALLOT(double,len);
   for (i = 0; i < len; i++) {
      spline_eval(x[i], &y[i], spline);
   }
   if (error == 1) {
      FREEMEM(x);
      FREEMEM(y);
      return(error);
   }
   count = 0;
   sprintf(msg,"%s(%f -> %f) = \n  ",spline->name,x[0],x[len - 1]);
   ctlmsg1(msg);
   for (i = 0; i < len; i++) {
      if (count >= 4) {
         ctlmsg1("\n  ");
         count = 0;
      }
      sprintf(msg," %.9e",y[i]);
      ctlmsg1(msg);
      count++;
   }
   ctlmsg1("\n");
   FREEMEM(x);
   FREEMEM(y);
   return(error);
}
int spline_getxy(double *x, double *y, int n, double xmin, double xmax, 
                        double x0, double y0, Spline_t *spline)
{
   char *me = "spline_getxy";
   char msg[MAXLINE];
   Spline_t *ptr;
   int error;
   int i;
   int imin,imax;
   double deltax;
   double rad;
   double *dep;
   double *ind;
   ptr = spline;
   if ((error = spline_chkrange(spline,xmin,xmax)) == -1) return(-1);
   ind = MALLOT(double,n);
   dep = MALLOT(double,n);
   ind[0] = xmin;  
   spline_eval(ind[0], &dep[0], spline);
   if (n > 1) {
      deltax = (xmax - xmin)/(double)(n - 1);
      for (i = 1; i < n; i++) {
         ind[i] = ind[i-1] + deltax;
         spline_eval(ind[i], &dep[i], ptr);
      } 
   }
   if (spline->coord == RTDATA) {
      rad = PI/180.0;
      if (!strcmp("r",spline->indlab)) {
         for (i = 0; i < n; i++) {
            x[i] = ind[i]*cos(dep[i]*rad) + spline->x0 + x0;
            y[i] = ind[i]*sin(dep[i]*rad) + spline->y0 + y0;
         }
     } else {
         for (i = 0; i < n; i++) {
             x[i] = dep[i]*cos(ind[i]*rad) + spline->x0 + x0;
             y[i] = dep[i]*sin(ind[i]*rad) + spline->y0 + y0;
         }
      }
   } else if (spline->coord == XYDATA) {
     if (!strcmp("x",spline->indlab)) {
         for (i = 0; i < n; i++) {
             x[i] = ind[i] + spline->x0 + x0;
             y[i] = dep[i] + spline->y0 + y0;
         }
     } else {
         for (i = 0; i < n; i++) {
             x[i] = dep[i] + spline->x0 + x0;
             y[i] = ind[i] + spline->y0 + y0;
         }
      }
   } else {
     sprintf(msg,"Attempting xy interpolation with a variable spline.");
     ctlwarning(me, msg);
     return(-1);
   }
   FREEMEM(ind);
   FREEMEM(dep);
   return(0);
}
int spline_chkrange(Spline_t *spline, double xmin, double xmax) {
   char *me = "spline_chkrange";
   char msg[MAXLINE];
   int error;
   int i,i1,i2;
   int out_of_range = 1;
   double myxmax, myxmin;
   double indmax, indmin;
   double sign;
   Spline_t * ptr1 = spline;
   myxmax = MAX(xmin,xmax);       
   myxmin = MIN(xmin,xmax);       
   indmin = plarge;
   indmax = -plarge;
   while(ptr1 != NULL){
      if (ptr1->ind[0] <= indmin) indmin = ptr1->ind[0];
      if (ptr1->ind[ptr1->len - 1] >= indmax) indmax = ptr1->ind[ptr1->len - 1];
      ptr1 = ptr1->next;
   }
   sign = 1;
   if (indmin < 0) sign = -1;
   indmin = indmin * (1. - sign * 1.0e-6);
   sign = 1;
   if (indmax < 0) sign = -1;
   indmax = indmax * (1. + sign * 1.0e-6);
   if (indmin == 0.) indmin = -1.0e-6;
   if (indmax == 0.) indmax =  1.0e-6;
   if ((myxmin >= indmin) && (myxmax <= indmax)) out_of_range = 0;
   if (out_of_range) { 
     sprintf(msg,"Bad limits (%f,%f) in spline interpolation.",xmin,xmax);
     ctlwarning(me, msg);
     return(-1);
   }
   return(0);
}
int spline_fit( void ) {
   char *me = "spline_fit";
   char msg[MAXLINE];
   char op[MAXLINE];
   int i;
   int len;
   int error;
   int *lblk;
   int *lndx;
   double r,t;
   double *x, *y;
   NodeWindow_t *ndxin;
   Spline_t *spline;
   ndxin = NULL;
   strcpy(msg,"spline_fit");
   error = NodeWindow_read(msg,&ndxin);
   if (error != 0) return(error);
   if (ndxin->next != NULL) {
      ctlwarning(me,
                "Cannot accept multi-block node lists in fitspline command.");
      NodeWindow_free(ndxin);
      return(-1);
   }
   if (ifparallel) {
      ctlwarning(me, "The fitspline command does not work in parallel.");
      NodeWindow_free(ndxin);
      return(-1);
   }
   geta(op);
   geta(op);
   spline = spline_find(op);
   if (spline != NULL) {
      sprintf(msg,"Spline %s has already been defined.",op);
      ctlwarning(me,msg);
      NodeWindow_free(ndxin);
      return(-1);
   }
   spline = Spline_construct(1);
   sprintf(spline->name,op);
   geta(op);
   if (!strcmp("cubic",op)) {
      spline->type = CUBIC;
   } else if (!strcmp("linear",op)) {
      spline->type = LINEAR;
   } else {
     sprintf(msg,"Spline type %s not recognized for spline %s.",
                op,spline->name);
     ctlwarning(me,msg);
     NodeWindow_free(ndxin);
     return(-1);
   } 
   len = NodeWindow_getndx(ndxin,-1, NDX_NO_OVERLAP, NDX_REAL, NDX_NODAL);
   lblk = ndxin->blk;
   lndx = ndxin->ndx;
   spline->len = len;
   x = MALLOT(double, len);
   y = MALLOT(double, len);
   for (i = 0; i < len; i++) {
      x[i] = domains[lblk[i]].x[lndx[i]];
      y[i] = domains[lblk[i]].y[lndx[i]];
   }
   NodeWindow_free(ndxin);
   geta(op);
   if (!strcmp(op,"xy")) {
      sprintf(spline->indlab,"y");
      sprintf(spline->deplab,"x");
      spline->ind = y;
      spline->dep = x;
      spline->coord = XYDATA;
   } else if (!strcmp(op,"yx")) {
      sprintf(spline->deplab,"y");
      sprintf(spline->indlab,"x");
      spline->ind = x;
      spline->dep = y;
      spline->coord = XYDATA;
   } else if (!strcmp(op,"rt")) {
      sprintf(spline->deplab,"r");
      sprintf(spline->indlab,"t");
      for (i = 0; i < len; i++) {
         r = sqrt(x[i] * x[i] + y[i] * y[i]);
         t = 180. * acos(x[i] / (r + ptiny)) / PI; 
         x[i] = t;
         y[i] = r;
      }
      spline->ind = x;
      spline->dep = y;
      spline->coord = RTDATA;
   } 
   error = spline_monot(spline);
   if (error != 0) {
      sprintf(msg,"Independent variable in spline %s is not monotonic.",
                   spline->name);
      ctlwarning(me,msg);
      FREEMEM(spline->ind);
      FREEMEM(spline->dep);
      FREEMEM(spline);
      return(-1);
   }
   error = spline_calc(spline);
   if (error) {
      sprintf(msg,"Error calculating spline %s coefficients.",
                   spline->name);
      ctlwarning(me,msg);
      FREEMEM(spline->ind);
      FREEMEM(spline->dep);
      FREEMEM(spline);
      return(-1);
   }
   spline_add(spline);
   return(0);
}
int spline_plsp( void ) {
   char *me = "spline_plsp";
   int error;
   int gotone;
   int count;
   char op[MAXLINE];
   char name[MAXLINE];
   char msg[256];
   Spline_t *spline;
   count = 0;
   gotone = 1;
   while (gotone) {
      peekc(op);
      spline = spline_find(op);
      if (spline == NULL) {
         geta(op);
         gotone = 0;
      } else {
         geta(op);
         sprintf(name,"Spline_%s",op);
         rgst_add_attr(A_OBJECT, name, "SplinePlotObj");
         count++;
      } 
      if (lfchk() > 0) gotone = 0;
   }
   if (count == 0) {
      sprintf(msg,"Could not find spline name %s.",op);
      ctlwarning(me,msg);
   } else {
   } 
   return(0);
}
int spline_plspoff( void ) {
   rgst_del_attr_all("SplinePlotObj");
   return(0);
}
void spline_plot( int iflab ) {
   char lab[MAXWORD];
   char *me = "spline_plot";
   char msg[MAXLINE];
   int i, count;
   int err;
   double *x,*y;
   RGST_AttributeElem_t  *splineobjs;
   RGST_AttributeElem_t  *splineobjs_ptr;
   Spline_t *spline;
   Spline_t *ptr;
   Spline_t * tmp;
   splineobjs = rgst_list_attr(A_OBJECT,"SplinePlotObj");
   splineobjs_ptr = splineobjs;
   count = rgst_num_with_attr(A_OBJECT, "SplinePlotObj");
   while (splineobjs_ptr != NULL) {
      spline = (Spline_t *)splineobjs_ptr->rgst_obj->obj;
      ptr = spline;
      while(ptr != NULL){
          if (iflab) {
              sprintf(lab,"plsp %s",ptr->name) ;
          }
          sprintf(lab,"%i",count);
          x = MALLOT(double, 3 * ptr->len);
          y = MALLOT(double, 3 * ptr->len);
          tmp = ptr->next;
          ptr->next = NULL;
          err = spline_getxy(x, y, 3 * ptr->len, ptr->ind[0], 
                 ptr->ind[ptr->len - 1], 0, 0, ptr);
          if (err != 0){
              FREEMEM(x);
              FREEMEM(y);
              sprintf(msg, "Cannot plot variable splines. ");
              ctlwarning(me, msg);
              return;
          }
          ptr->next = tmp;
          for (i = 0; i < 3 * ptr->len - 1; i++) {    
             if (((i % 10) == 0) || (i == 0)) {
             }
          }
          ptr = ptr->next;
          FREEMEM(x);
          FREEMEM(y);
      } 
      count--;
      splineobjs_ptr = splineobjs_ptr->next;
   }
}
static void spline_convert(Spline_t *spline, char* op) {
   char msg[MAXLINE];
   char *me = "spline_convert";
   double *myindtmp;
   double *ind;
   double *dep;
   int i;
   int last;
   ind = MALLOT(double,spline->len);
   dep = MALLOT(double,spline->len);
   last = spline->len - 1;
   spline_calc(spline);
   if ((!strcmp(spline->indlab,"x"))  && (!strcmp(spline->deplab,"y"))) {
      if (!strcmp(op,"yx")) {
         myindtmp = spline->ind;
         spline->ind = spline->dep;
         spline->dep = myindtmp;
	 strcpy(spline->indlab,"y");
	 strcpy(spline->deplab,"x");
      } else if (!strcmp(op,"rt")) {
         spline_getrt(ind, dep, spline->len, spline->ind[0], 
	    spline->ind[last], 0, 0, spline);
         for (i = 0; i < spline->len; i++) {
            spline->ind[i] = ind[i];
            spline->dep[i] = dep[i];
         }
	 strcpy(spline->indlab,"r");
	 strcpy(spline->deplab,"t");
	 spline->coord = RTDATA;
      } else if (!strcmp(op,"tr")) {
         spline_getrt(dep, ind, spline->len, spline->ind[0], 
	    spline->ind[last], 0, 0, spline);
         for (i = 0; i < spline->len; i++) {
            spline->ind[i] = ind[i];
            spline->dep[i] = dep[i];
         }
	 strcpy(spline->indlab,"t");
	 strcpy(spline->deplab,"r");
	 spline->coord = RTDATA;
      } 
   } else if ((!strcmp(spline->indlab,"y"))  && (!strcmp(spline->deplab,"x"))) {
      if (!strcmp(op,"xy")) {
         myindtmp = spline->ind;
         spline->ind = spline->dep;
         spline->dep = myindtmp;
	 strcpy(spline->indlab,"x");
	 strcpy(spline->deplab,"y");
      } else if (!strcmp(op,"rt")) {
         spline_getrt(ind, dep, spline->len, spline->ind[0], 
	    spline->ind[last], 0, 0, spline);
         for (i = 0; i < spline->len; i++) {
            spline->ind[i] = ind[i];
            spline->dep[i] = dep[i];
         }
	 strcpy(spline->indlab,"r");
	 strcpy(spline->deplab,"t");
	 spline->coord = RTDATA;
      } else if (!strcmp(op,"tr")) {
         spline_getrt(dep, ind, spline->len, spline->ind[0], 
	    spline->ind[last], 0, 0, spline);
         for (i = 0; i < spline->len; i++) {
            spline->ind[i] = ind[i];
            spline->dep[i] = dep[i];
         }
	 strcpy(spline->indlab,"t");
	 strcpy(spline->deplab,"r");
	 spline->coord = RTDATA;
      } 
   } else if ((!strcmp(spline->indlab,"r"))  && (!strcmp(spline->deplab,"t"))) {
      if (!strcmp(op,"tr")) {
         myindtmp = spline->ind;
         spline->ind = spline->dep;
         spline->dep = myindtmp;
	 strcpy(spline->indlab,"t");
	 strcpy(spline->deplab,"r");
      } else if (!strcmp(op,"xy")) {
         spline_getxy(ind, dep, spline->len, spline->ind[0], 
	  spline->ind[last], 0, 0, spline);
         for (i = 0; i < spline->len; i++) {
            spline->ind[i] = ind[i];
            spline->dep[i] = dep[i];
         }
	 strcpy(spline->indlab,"x");
	 strcpy(spline->deplab,"y");
	 spline->coord = XYDATA; 
       } else if (!strcmp(op,"yx")) { 
	 spline_getxy(dep, ind, spline->len, spline->ind[0], 
	                     spline->ind[last], 0, 0, spline);
         for (i = 0; i < spline->len; i++) {
            spline->ind[i] = ind[i];
            spline->dep[i] = dep[i];
         }
	 strcpy(spline->indlab,"y");
	 strcpy(spline->deplab,"x");
	 spline->coord = XYDATA; 
      } 
   } else if ((!strcmp(spline->indlab,"t"))  && (!strcmp(spline->deplab,"r"))) {
      if (!strcmp(op,"rt")) {
         double *locindtmp = spline->ind;
         spline->ind = spline->dep;
         spline->dep = locindtmp;
	 strcpy(spline->indlab,"r");
	 strcpy(spline->deplab,"t");
      } else if (!strcmp(op,"xy")) {
         spline_getxy(ind, dep, spline->len, spline->ind[0], 
	  spline->ind[last], 0, 0, spline);
         for (i = 0; i < spline->len; i++) {
            spline->ind[i] = ind[i];
            spline->dep[i] = dep[i];
         }
	 strcpy(spline->indlab,"x");
	 strcpy(spline->deplab,"y");
	 spline->coord = XYDATA; 
      } else if (!strcmp(op,"yx")) {
         spline_getxy(dep, ind, spline->len, spline->ind[0], 
	  spline->ind[last], 0, 0, spline);
         for (i = 0; i < spline->len; i++) {
            spline->ind[i] = ind[i];
            spline->dep[i] = dep[i];
         }
	 strcpy(spline->indlab,"y");
	 strcpy(spline->deplab,"x");
	 spline->coord = XYDATA; 
      } 
   } 
   if (spline->type == CUBIC) {
      FREEMEM(spline->b);
      FREEMEM(spline->c);
      FREEMEM(spline->d);
   }
   FREEMEM(ind);
   FREEMEM(dep);
}
static int spline_getrt(double *r, double *t, int n, double xmin, double xmax, 
                        double x0, double y0, Spline_t *spline)
{
   char *me = "spline_getrt";
   char msg[MAXLINE];
   int error;
   int i;
   int imin,imax;
   double deltax;
   double xt, yt;
   double cross, dot, sign;
   double *dep;
   double *ind;
   if ((error = spline_chkrange(spline,xmin,xmax)) == -1) return(-1);
   ind = MALLOT(double,n);
   dep = MALLOT(double,n);
   ind[0] = xmin;  
   spline_eval(ind[0], &dep[0], spline);
   if (n > 1) {
      deltax = (xmax - xmin)/(double)(n - 1);
      for (i = 1; i < n; i++) {
         ind[i] = ind[i-1] + deltax;
         spline_eval(ind[i], &dep[i], spline);
      }
   }
   if (spline->coord == RTDATA) {
      if (!strcmp("r",spline->indlab)) {
         for (i = 0; i < n; i++) {
	    r[i] = ind[i];
	    t[i] = dep[i];
         }
      } else {
         for (i = 0; i < n; i++) {
	    r[i] = dep[i];
	    t[i] = ind[i];
         }
      }
   }
   if (spline->coord == XYDATA) {
      if (!strcmp("x",spline->indlab)) {
         for (i = 0; i < n; i++) {
            xt = ind[i] - spline->x0 - x0;
            yt = dep[i] - spline->y0 - y0;
	    r[i] = sqrt(xt * xt + yt * yt);
	    cross = (yt * spline->axis_x - xt * spline->axis_y);
	    dot = (xt * spline->axis_x + yt * spline->axis_y) / (r[i] + ptiny);
	    sign = 1.;
	    if (cross < 0) sign = -1;
	    t[i] = sign * (180. * acos(dot)) / PI;
         }
      }
      if (!strcmp("y",spline->indlab)) {
         for (i = 0; i < n; i++) {
            xt = dep[i] - spline->x0 - x0;
            yt = ind[i] - spline->y0 - y0;
	    r[i] = sqrt(xt * xt + yt * yt);
	    cross = (yt * spline->axis_x - xt * spline->axis_y);
	    dot = (xt * spline->axis_x + yt * spline->axis_y) / (r[i] + ptiny);
	    sign = 1.;
	    if (cross < 0) sign = -1;
	    t[i] = sign * (180. * acos(dot)) / PI;
         }
      }
   } else {
     sprintf(msg,"Attempting rt interpolation with a variable spline.");
     ctlwarning(me, msg);
     return(-1);
   }
   FREEMEM(ind);
   FREEMEM(dep);
   return(0);
}
static void spline_copy(Spline_t * next_sp, Spline_t * spline_ref){
    int i;
    next_sp->flip  = spline_ref->flip;
    next_sp->len   = spline_ref->len;
    next_sp->ind   = ALLOT(double,spline_ref->len);
    next_sp->dep   = ALLOT(double,spline_ref->len);
    next_sp->dep1  = spline_ref->dep1;
    next_sp->dep2  = spline_ref->dep2;
    next_sp->type  = spline_ref->type;
    next_sp->coord = spline_ref->coord;
    next_sp->x0 = spline_ref->x0;
    next_sp->y0 = spline_ref->y0;
    next_sp->z0 = spline_ref->z0;
    if (next_sp->type == CUBIC){
        next_sp->b = ALLOT(double,spline_ref->len);
        next_sp->c = ALLOT(double,spline_ref->len);      
        next_sp->d = ALLOT(double,spline_ref->len);
    }
    strcpy(next_sp->deplab,spline_ref->deplab);
    strcpy(next_sp->indlab,spline_ref->indlab);
    for (i = 0; i < next_sp->len; i++) {
       next_sp->ind[i] = spline_ref->ind[i];
       next_sp->dep[i] = spline_ref->dep[i];
    }
    if (next_sp->type == CUBIC){
        for (i = 0; i < next_sp->len; i++) {
          next_sp->b[i] = spline_ref->b[i];
          next_sp->c[i] = spline_ref->c[i];
          next_sp->d[i] = spline_ref->d[i];
        }
    }
}
void spline_getvalues(int mode){
    char *me = "spline_getvalues";
    char msg[MAXLINE];
    char op[MAXLINE];
    double *r, *t, *x, *y;
    double start, finish, *ind;
    double *dep;
    double rad;
    double cross, dot, sign;
    double xt, yt;
    double delta;
    int len, i;
    int scalar;
    int cflag;
    Spline_t * spline;
    Spline_t * ptr;
    Spline_t * ptr1;
    geta(op);
    geta(op);
   spline = spline_find(op);
   if (spline == NULL){
       sprintf(msg, "Spline %s not found.", op);
       ctlerror(me, msg);
       return;
   }
   geta(op);
   start = getf(&cflag);
   geta(op);
   if (!strcmp(")", op)){
       len = 1;
       scalar = 1; 
   }  else {
       scalar = 0;
       finish = getf(&cflag);
       geta(op);
       len = geti(&cflag);
       geta(op);
       if (strcmp(")", op)) {
           sprintf(msg, "Error parsing spline.");
           ctlerror(me, msg);
           return;
       }     
   }
   dep = MALLOT(double,len);
   ind = MALLOT(double,len);
   r = MALLOT(double,len);
   t = MALLOT(double,len);
   x = MALLOT(double,len);
   y = MALLOT(double,len);
   *ind = start;
   if (len > 1) {
       delta = (finish - start)/(double)(len - 1);
   } else {
       finish = start;
   } 
   if (spline_chkrange(spline, start, finish) == -1) return;
   ptr = spline;
   while(ptr != NULL){
       ptr1 = ptr;
       ptr = ptr->next;
   }
   for (i = 0; i < len; i++){
       if (i == 0)
           ind[i] = start;
       else if (i == (len - 1))
           ind[i] = finish;
       else
           ind[i] = ind[i-1] + delta;
       spline_eval(ind[i], &dep[i], spline);
   }
       if (spline->coord == RTDATA) {
          rad = PI/180.0;
          if (!strcmp("r",spline->indlab)) {
              for (i=0; i<len; i++){  
                 x[i] = ind[i]*cos(dep[i]*rad) + spline->x0;
                 y[i] = ind[i]*sin(dep[i]*rad) + spline->y0;
              }
          } else {
              for (i=0; i<len; i++){
                 x[i] = dep[i]*cos(ind[i]*rad) + spline->x0;
                 y[i] = dep[i]*sin(ind[i]*rad) + spline->y0;
              }
          }
       } else if (spline->coord == XYDATA) {
         if (!strcmp("x",spline->indlab)) {
             for (i=0; i<len; i++){
                 x[i] = ind[i] + spline->x0;
                 y[i] = dep[i] + spline->y0;
             }
         } else {
             for (i=0; i<len; i++){
                 x[i] = dep[i] + spline->x0;
                 y[i] = ind[i] + spline->y0;
             }
          }
       } else {
         sprintf(msg,"Attempting xy interpolation with a variable spline.");
         ctlwarning(me, msg);
         return;
       }
       if (spline->coord == RTDATA) {
           if (!strcmp("r",spline->indlab)) {
               for (i=0; i<len; i++){ 
	               r[i] = ind[i];
	               t[i] = dep[i];
               }
           } else {
               for (i=0; i<len; i++){
	               r[i] = dep[i];
	               t[i] = ind[i];
               }
           }
       }
       if (spline->coord == XYDATA) {
           if (!strcmp("x",spline->indlab)) {
               for (i=0; i<len; i++){
                   xt = ind[i] - spline->x0;
                   yt = dep[i] - spline->y0;
	               r[i] = sqrt(xt * xt + yt * yt);
	               cross = (yt * spline->axis_x - xt * spline->axis_y);
	               dot = (xt * spline->axis_x + yt * spline->axis_y) / (r[i] + ptiny);
	               sign = 1.;
	               if (cross < 0) sign = -1;
	               t[i] = sign * (180. * acos(dot)) / PI;
                }
           }
           if (!strcmp("y",spline->indlab)) {
               for (i=0; i<len; i++){
                   xt = dep[i] - spline->x0;
                   yt = ind[i] - spline->y0;
	               r[i] = sqrt(xt * xt + yt * yt);
	               cross = (yt * spline->axis_x - xt * spline->axis_y);
	               dot = (xt * spline->axis_x + yt * spline->axis_y) / (r[i] + ptiny);
	               sign = 1.;
	               if (cross < 0) sign = -1;
	               t[i] = sign * (180. * acos(dot)) / PI;
               }
           }
       } 
          switch(mode){
              case 0:
                  if (scalar){
                      ctloutput(me, "dep", R_DOUBLE, dep[0]);
                  } 
                  else{
                      ctloutput(me, "dep", R_DOUBLE_ARRAY, dep, len); 
                  }
                  break;
              case 1:
                  if (scalar){
                      ctloutput(me, "x", R_DOUBLE, x[0]);
                  } 
                  else{
                      ctloutput(me, "x", R_DOUBLE_ARRAY, x, len);
                  }  
                  break;
              case 2:
                  if (scalar){
                      ctloutput(me, "y", R_DOUBLE, y[0]);
                  } 
                  else{
                      ctloutput(me, "y", R_DOUBLE_ARRAY, y, len);
                  }  
                  break;
              case 3:
                  if (scalar){
                      ctloutput(me, "r", R_DOUBLE, r[0]);
                  } 
                  else{
                      ctloutput(me, "r", R_DOUBLE_ARRAY, r, len);
                  }  
                  break;
              case 4:
                  if (scalar){
                      ctloutput(me, "t", R_DOUBLE, t[0]);
                  } 
                  else{
                      ctloutput(me, "t", R_DOUBLE_ARRAY, t, len);
                  }  
                  break;
              case 5:
                  if (scalar){
                      ctloutput(me, "x", R_DOUBLE, x[0]);
                      ctloutput(me, "y", R_DOUBLE, y[0]);
                  } 
                  else{
                      ctloutput(me, "x", R_DOUBLE_ARRAY, x, len);
                      ctloutput(me, "y", R_DOUBLE_ARRAY, y, len);
                  }  
                  break;
              case 6:
                  if (scalar){
                      ctloutput(me, "r", R_DOUBLE, r[0]);
                      ctloutput(me, "t", R_DOUBLE, t[0]);
                  } 
                  else{
                      ctloutput(me, "r", R_DOUBLE_ARRAY, r, len);
                      ctloutput(me, "t", R_DOUBLE_ARRAY, t, len);
                  }  
                  break;
              default:
                  break;
          }
   FREEMEM(dep);
   FREEMEM(ind);
   FREEMEM(r);
   FREEMEM(t);
   FREEMEM(x);
   FREEMEM(y);
}
static void spline_repack(Spline_t *spline, double ll, double ul){
    char *me = "spline_repack";
    char msg[MAXLINE];
    int discard, size, i, j;
    int lower;
    int upper;
    double *newdep, *newind, *newb, *newc, *newd;
    if ((ll < spline->ind[0]) || (ll > spline->ind[spline->len-1]) ||
       (ul < spline->ind[0]) || (ul > spline->ind[spline->len-1])){
         sprintf(msg,"limits out of range: ll = %f ul = %f", ll, ul);
         ctlwarning(me, msg);
         return;
    }
    discard = 0;
    i = 0;
    while((ll > spline->ind[i]) && (i < spline->len)){
        discard++;
        i++;
    }
    if (fabs(ll - spline->ind[i]) < 1e-16) {
        discard++;
        i++;
    }
    lower = i; 
    i = spline->len - 1;
    while((ul < spline->ind[i]) && (i >= 0)){
        discard++;
        i--;
    } 
    if (fabs(ul - spline->ind[i]) < 1e-16) {
        discard++;
        i--;
    }
    upper = i;
    size = spline->len - discard + 2;
    newdep = MALLOT(double, size);
    newind = MALLOT(double, size);
    newind[0] = ll;
    newind[size-1] = ul;
    spline_eval(ll, &newdep[0], spline);
    spline_eval(ul, &newdep[size-1], spline);
    for (j = 1, i=lower; i<=upper; i++, j++){
        newind[j] = spline->ind[i];
        newdep[j] = spline->dep[i];
        spline_eval(newind[j], &newdep[j], spline);
    }
    FREEMEM(spline->dep);
    FREEMEM(spline->ind);
    FREEMEM(spline->b);
    FREEMEM(spline->c);
    FREEMEM(spline->d);
    spline->len = size;
    spline->dep = newdep;
    spline->ind = newind;
}
static int spline_resample(double *pts, double *dep, int type, int len,
                            Spline_t *spline, char *op){
    char *me = "spline_resample";
    char msg[MAXLINE];
    int i, j, lower, upper;
    int imin, imax;
    int counter;
    int newcoord = 0;
    int skip = 0;
    int size;
    int first;
    double *x = NULL, *y = NULL;
    double *r = NULL, *t = NULL;
    double *subind, *subdep;
    double *rad, *theta;
    double *cind, *cdep;
    double x1, y1, x2, y2;
    double r1, t1, r2, t2;
    double yest, rest;
    double rn, tn;
    double xn, yn;
    double err;
    double *ptr;
    double dmin, dmax;
    double tol = 1e-8;
    if (pts[0] > pts[len - 1]) {
        spline_flip(pts, len);
        spline_flip(dep, len);
    }
    if (type != spline->coord) newcoord = 1;
    if ((type == XYDATA) && (newcoord == 1)) {
       x = MALLOT(double, spline->len);
       y = MALLOT(double, spline->len);
       r = MALLOT(double, 1);
       t = MALLOT(double, 1);
       if (!strcmp(spline->indlab, "t")) {
          Transform_rt2xyz(x, y, NULL, spline->dep, spline->ind, spline->len, NULL);
       } else {
          Transform_rt2xyz(x, y, NULL, spline->ind, spline->dep, spline->len, NULL);
       } 
       if (!strcmp(op, "xy")) {
          cind = x;
          cdep = y;
       } else {
          cind = y;
          cdep = x;
       }
        if (cind[0] > cind[spline->len-1]) {
           spline_flip(x, spline->len);
           spline_flip(y, spline->len); 
        }
        dmin = cind[0];
        dmax = cind[spline->len - 1];
        for (i = 0; i < spline->len; i++) {
           if (dmin > cind[i]) dmin = cind[i];
           if (dmax < cind[i]) dmax = cind[i];
        }
        imin = 0;
        for (i = 0; i < len; i++) {
           if (pts[i] >= (dmin - tol)) break;
        }
        imin = i;
        for (i = len - 1; i >= 0; i--) {
           if (pts[i] <= (dmax + tol)) break;
        }
        imax = i;
        if ((imin == len) || (imax == -1)) {
           FREEMEM(x);
           FREEMEM(y);
           FREEMEM(r);
           FREEMEM(t);
           return(1);
        }
        for (i = 0; i < spline->len; i++){
           if (pts[imin] < cind[i] ) {
              break;
           }
        } 
        lower = i - 1;
        if (lower < 0) lower = 0;
        for (i = spline->len - 1; i >= 0; i--){
           if (pts[imax] > cind[i]) {
              break;
           }
        }
        upper = i + 1;
        if (upper >= spline->len) upper = spline->len - 1;
        for (i = lower+1; i < upper; i++) {
           if (cind[i-1] > cind[i]) {
              sprintf(msg, "Transformed spline, %s,  variable not monotonic.", 
                                spline->name);
              ctlwarning(me, msg);
              FREEMEM(x);
              FREEMEM(y);
              FREEMEM(r);
              FREEMEM(t);
              return(1);
           }
        }
        for (i = imin; i <= imax; i++){
           for (j = lower; j < spline->len; j++) {
              if (pts[i] <= cind[j]) break;
           }
           j--;
           x1 = cind[j];
           x2 = cind[j+1];
           y1 = cdep[j];
           y2 = cdep[j+1];
           counter = 0;
           err = x2 - pts[i];
           if (err <= 1e-12) {
              yest = y2;
           } else if ((pts[i] - x1) <= 1e-12) {
              yest = y1;
              err = 0.0;
           }
           while (err > 1e-12) {
              if (!strcmp(op, "xy")){
                 Transform_xyz2rt(&x2, &y2, NULL, &r1, &t1, 1, NULL);
                 Transform_xyz2rt(&x1, &y1, NULL, &r2, &t2, 1, NULL);
              } else {
                 Transform_xyz2rt(&y2, &x2, NULL, &r1, &t1, 1, NULL);
                 Transform_xyz2rt(&y1, &x1, NULL, &r2, &t2, 1, NULL);
              }
              if (!strcmp(spline->indlab, "t")) {
                 t[0] = t1 + (t2 - t1)/2;
                 spline_eval(t[0], r, spline);
              } else {
                 r[0] = r1 + (r2 - r1)/2;
                 spline_eval(r[0], t, spline);
              }
              if (!strcmp(op, "xy")) {
                 Transform_rt2xyz(&xn, &yn, NULL, r, t, 1, NULL);
              } else {
                 Transform_rt2xyz(&yn, &xn, NULL, r, t, 1, NULL);
              } 
              counter++;
              if (counter > MAX_ITER){
                 sprintf(msg, "point %f did not converge", pts[i]);
                 ctlwarning(me, msg);
                 return(1);
              } 
              if (pts[i] > xn) {
                 x1 = xn;
                 y1 = yn;
              } else {
                 x2 = xn;
                 y2 = yn;
              }
              if ((x2-pts[i]) < (pts[i]-x1)) {
                 err = x2-pts[i];
                 yest = y2;
              } else {
                 err = pts[i]-x1;
                 yest = y1;
              }
           }
           dep[i] = yest;            
        }
        spline->len = imax - imin + 1;  
        subind = MALLOT(double, spline->len);
        subdep = MALLOT(double, spline->len);
        j = imin;
        for (i = 0; i < spline->len; i++){
           subind[i] = pts[j];
           subdep[i] = dep[j]; 
           j++;
        } 
        FREEMEM(spline->ind);
        spline->ind = subind;
        FREEMEM(spline->dep);
        spline->dep = subdep;
    } else if ((type == XYDATA) && (newcoord == 0)) {
        size = 0;
        first = 1;
        for (i = 0; i < len; i++) {
           if ((spline->ind[0] <= pts[i]) && 
	       (pts[i] <= spline->ind[spline->len - 1])) {
                size++;
                if (first) {
                    imin = i;
                    first = 0;
                }
                imax = i;
            }
        }           
        if (size < 2){
            return(1);
        }
        subind = MALLOT(double, size);
        subdep = MALLOT(double, size);
        j = 0;
        for (i = imin; i <= imax; i++){
           subind[j] = pts[i];
           spline_eval(pts[i], &subdep[j], spline);
           j++;
        }
        FREEMEM(spline->ind);
        spline->ind = subind;
        FREEMEM(spline->dep);
        spline->dep = subdep;
        spline->len = size;
    } else if ((type == RTDATA) && (newcoord == 1)) {
        t = MALLOT(double, spline->len);
        r = MALLOT(double, spline->len);
        x = MALLOT(double, 1);
        y = MALLOT(double, 1);
        if (!strcmp(spline->indlab, "x")) {
           Transform_xyz2rt(spline->ind, spline->dep, NULL, r, t, spline->len, NULL);
        } else {
           Transform_xyz2rt(spline->dep, spline->ind, NULL, r, t, spline->len, NULL);
        } 
        if (!strcmp(op, "tr")) {
           cind = t;
           cdep = r;
        } else {
           cind = r;
           cdep = t;
        }
        if (cind[0] > cind[spline->len-1]) {
           spline_flip(t, spline->len);
           spline_flip(r, spline->len);
        }
        dmin = cind[0];
        dmax = cind[spline->len - 1];
        for (i=0; i< spline->len; i++){
            if (dmin > cind[i]) dmin = cind[i];
            if (dmax < cind[i]) dmax = cind[i];
        }
        imin = 0;
        for (i = 0; i < len; i++) {
           if (pts[i] >= (dmin - tol)) break;
        }
        imin = i;
        for (i = len - 1; i >= 0; i--) {
           if (pts[i] <= (dmax + tol)) break;
        }
        imax = i;
        if ((imin == len) || (imax == -1)) {
           FREEMEM(x);
           FREEMEM(y);
           FREEMEM(r);
           FREEMEM(t);
           return(1);
        }
        for (i = 0; i < spline->len; i++){
           if (pts[imin] < cind[i]) {
              break;
           }
        } 
        lower = i - 1;
        if (lower < 0) lower = 0;
        for (i = spline->len - 1; i >= 0; i--){
           if (pts[imax] > cind[i]) {
              break;
           }
        }
        upper = i + 1;
        if (upper >= spline->len) upper = spline->len - 1;
        for (i = lower+1; i < upper; i++) {
           if (cind[i-1] > cind[i]) {
              sprintf(msg, "Transformed spline, %s,  variable not monotonic.", 
                                spline->name);
              ctlwarning(me, msg);
              FREEMEM(x);
              FREEMEM(y);
              FREEMEM(r);
              FREEMEM(t);
              return(1);
           }
        }
        for (i = imin; i <= imax; i++){
           for (j = lower; j < spline->len; j++) {
              if (pts[i] <= cind[j]) break;
           }
           j--;
           if (j < 0) j++;
           t1 = cind[j];
           t2 = cind[j+1];
           r1 = cdep[j];
           r2 = cdep[j+1];
           counter = 0;
           err = t2 - pts[i];
           if (err <= 1e-12) {
              rest = r2;
           } else if ((pts[i] - t1) <= 1e-12) {
              rest = r1;
              err = 0.0;
           }
           while(err > 1e-12){
              if (!strcmp(op, "tr")){
                  Transform_rt2xyz(&x2, &y2, NULL, &r1, &t1, 1, NULL);
                  Transform_rt2xyz(&x1, &y1, NULL, &r2, &t2, 1, NULL);
              } else {
                  Transform_rt2xyz(&x2, &y2, NULL, &t1, &r1, 1, NULL);
                  Transform_rt2xyz(&x1, &y1, NULL, &t2, &r2, 1, NULL);
              }
              if (!strcmp(spline->indlab, "x")){
                  x[0] = x1 + (x2 - x1)/2.0;
                  spline_eval(x[0], y, spline);
              } else {
                  y[0] = y1 + (y2 - y1)/2.0;
                  spline_eval(y[0], x, spline);
              }
              if (!strcmp(op, "tr")) {
                 Transform_xyz2rt(x, y, NULL, &rn, &tn, 1, NULL);
              } else {
                 Transform_xyz2rt(x, y, NULL, &tn, &rn, 1, NULL);
              } 
              counter++;
              if (counter > MAX_ITER) {
                  sprintf(msg, "point %f did not converge", pts[i]);
                  ctlwarning(me, msg);
                  return(1);
              } 
              if (pts[i] > tn) {    
                 r1 = rn;
                 t1 = tn;
              } else {
                 r2 = rn;
                 t2 = tn;
              }
              if ((t2 - pts[i]) < (pts[i] - t1)) {
                  err = t2 - pts[i];           
                  rest = r2;
              } else {
                  err = pts[i] - t1;
                  rest = r1;
              }   
           }
           dep[i] = rest;            
        }
        spline->len = imax - imin + 1;  
        subind = MALLOT(double, spline->len);
        subdep = MALLOT(double, spline->len);
        j = imin;
        for (i = 0; i < spline->len; i++){
           subind[i] = pts[j];
           subdep[i] = dep[j]; 
           j++;
        } 
        FREEMEM(spline->ind);
        spline->ind = subind;
        FREEMEM(spline->dep);
        spline->dep = subdep;
    } else if ((type == RTDATA) && (newcoord == 0)) {
        size = 0;
        first = 1;
        for (i = 0; i < len; i++){
            if ((spline->ind[0] <= pts[i]) && 
	         (pts[i] <= spline->ind[spline->len - 1])) {
                size++;
                if (first) {
                    imin = i;
                    first = 0;
                }
                imax = i;
            }
        }           
        if (size < 2){
           return(1);
        }
        subind = MALLOT(double, size);
        subdep = MALLOT(double, size);
        j = 0;
        for (i = imin; i <= imax; i++){
            subind[j] = pts[i];
            spline_eval(pts[i], &subdep[j], spline);
            j++;
        }
        FREEMEM(spline->ind);
        spline->ind = subind;
        FREEMEM(spline->dep);
        spline->dep = subdep;
        spline->len = size;
    } 
    if (x != NULL) FREEMEM(x);
    if (y != NULL) FREEMEM(y);
    if (r != NULL) FREEMEM(r);
    if (t != NULL) FREEMEM(t);
    return(0);
}
static void spline_flip(double *data, int len){
    int i, j, max;
    double temp;
    max = len / 2;
    j = len - 1;
    for (i = 0; i < max; i++){
        temp =  data[j];
        data[j] = data[i];
        data[i] = temp;
        j--;
    } 
}
void spline_delete( char *nmn )
{
   char name[MAXLINE];
   char msg[MAXLINE];
   char *me = "spline_delete";
   int num_sp, i;
   Spline_t *spline_ptr;
   Spline_t *sptr;
   sprintf(name, "Spline_%s", nmn);
   spline_ptr = rgst_get_t(name, "Spline_t");
   if (spline_ptr == NULL){
       sprintf(msg, "spline %s is not in the registry.", name);
       ctlwarning(me, msg);
       return;
   }  
   sptr = spline_ptr;
   rgst_del(name);
   while (spline_ptr != NULL) {
       if (spline_ptr->len > 0) {
           FREEMEM(spline_ptr->ind);
           FREEMEM(spline_ptr->dep);
           if (spline_ptr->type == CUBIC) {
              FREEMEM(spline_ptr->b);
              FREEMEM(spline_ptr->c);
              FREEMEM(spline_ptr->d);
           }
       }
       sptr = spline_ptr;
       spline_ptr = spline_ptr->next; 
       FREEMEM(sptr);
   } 
}
