#include "irs.h"
#include "irsrgst.h"
#include "irsctl.h"
#include "irscom.h"
#include "Command.h"
#include "FunctionTimer.h"
#include "NodeList.h"
#include "Transform.h"
static double axis[3] = {1, 0, 0};
static double norm[3] = {-1000, 0, 0};
static double cent[3] = {0, 0, 0};
static double perp[3] = {0, 0, 0};
void Transform_add(char *name, double *mycent, double *myaxis, double *mynorm) {
   char realname[MAXLINE];
   double dot;
   Transform_t *trans;
   trans = Transform_find(name);
   if (trans == NULL) {
      trans = MALLOT(Transform_t,1);
      Transform_init(trans);
      trans->name = strsave(name);
      sprintf(realname,"Transform_%s",name);
      rgst_add(realname,"Transform_t", trans, NULL);
   }
   if (mycent != NULL) {
      trans->cent[0] = mycent[0];
      trans->cent[1] = mycent[1];
      trans->cent[2] = mycent[2];
   }
   if (myaxis != NULL) {
      trans->axis[0] = myaxis[0];
      trans->axis[1] = myaxis[1];
      trans->axis[2] = myaxis[2];
      dot = sqrt( trans->axis[0] * trans->axis[0] + 
                  trans->axis[1] * trans->axis[1] + 
                  trans->axis[2] * trans->axis[2]);
      trans->axis[0] = trans->axis[0] / (dot + ptiny);
      trans->axis[1] = trans->axis[1] / (dot + ptiny);
      trans->axis[2] = trans->axis[2] / (dot + ptiny);
   }
   if (mynorm != NULL) {
      trans->norm[0] = mynorm[0];
      trans->norm[1] = mynorm[1];
      trans->norm[2] = mynorm[2];
      if (mynorm[0] > -1000) { 
         dot = sqrt( trans->norm[0] * trans->norm[0] + 
                     trans->norm[1] * trans->norm[1] + 
                     trans->norm[2] * trans->norm[2]);
         trans->norm[0] = trans->norm[0] / (dot + ptiny);
         trans->norm[1] = trans->norm[1] / (dot + ptiny);
         trans->norm[2] = trans->norm[2] / (dot + ptiny);
         trans->perp[0] = (trans->axis[1]* trans->norm[2] - 
	                   trans->axis[2]* trans->norm[1]);
         trans->perp[1] = (trans->axis[2]* trans->norm[0] - 
	                   trans->axis[0]* trans->norm[2]);
         trans->perp[2] = (trans->axis[0]* trans->norm[1] - 
	                   trans->axis[1]* trans->norm[0]);
         dot = sqrt( trans->perp[0] * trans->perp[0] + 
                     trans->perp[1] * trans->perp[1] + 
		     trans->perp[2] * trans->perp[2]);
         trans->perp[0] = trans->perp[0] / (dot + ptiny);
         trans->perp[1] = trans->perp[1] / (dot + ptiny);
         trans->perp[2] = trans->perp[2] / (dot + ptiny);
      }
   }
}
void Transform_init(Transform_t *trans) {
   trans->name = NULL;
   trans->cent[0] = 0;
   trans->cent[1] = 0;
   trans->cent[2] = 0;
   trans->axis[0] = 1;
   trans->axis[1] = 0;
   trans->axis[2] = 0;
   trans->norm[0] = -1000;
   trans->norm[1] = 0;
   trans->norm[2] = 0;
   trans->perp[0] = 0;
   trans->perp[1] = 0;
   trans->perp[2] = 0;
}
void Transform_del (char *name) {
   char realname[MAXLINE];
   sprintf(realname,"Transform_%s",name);
   if (rgst_check_for_obj(realname)) {
      Transform_t *trans = (Transform_t *) rgst_get_t(realname, "Transform_t");
      FREEMEM(trans);
      rgst_del(realname);
   }
}
Transform_t* Transform_find(char *name) {
   char realname[MAXLINE];
   Transform_t *trans = NULL;
   sprintf(realname,"Transform_%s",name);
   if (rgst_check_for_obj(realname)) {
      trans = (Transform_t *) rgst_get_t(realname, "Transform_t");
   }
   return(trans);
}
int  Transform_set( int flag )
{
   char op[MAXLINE];
   double dot;
   double *array;
   int cflag;
   if (flag == 0) array = axis;
   if (flag == 1) array = norm;
   if (flag == 2) array = cent;
   peekc(op);
   if (!strcmp(op,"default")) {
      geta(op);
      if (flag == 0) { 
          axis[0] = 1;
          axis[1] = 0;
          axis[2] = 0;
      } else if (flag == 1) { 
          norm[0] = -1000;
          norm[1] = 0;
          norm[2] = 0;
      } else if (flag == 2) { 
          cent[0] = 0;
          cent[1] = 0;
          cent[2] = 0;
      } 
      flag = -1;
   } else {
      array[0] = getf(&cflag);
      array[1] = getf(&cflag);
      if (ndims == 3) {
         array[2] = getf(&cflag);
      }
   } 
   if (flag == 0) {
      dot = sqrt( axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
      axis[0] = axis[0] / (dot + ptiny);
      axis[1] = axis[1] / (dot + ptiny);
      axis[2] = axis[2] / (dot + ptiny);
   }
   if (flag == 1) {
      dot = sqrt( norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
      norm[0] = norm[0] / (dot + ptiny);
      norm[1] = norm[1] / (dot + ptiny);
      norm[2] = norm[2] / (dot + ptiny);
   }
   if (norm[0] > -1000) {
      perp[0] = (axis[1]* norm[2] - axis[2]* norm[1]);
      perp[1] = (axis[2]* norm[0] - axis[0]* norm[2]);
      perp[2] = (axis[0]* norm[1] - axis[1]* norm[0]);
      dot = sqrt( perp[0] * perp[0] + perp[1] * perp[1] + perp[2] * perp[2]);
      perp[0] = perp[0] / (dot + ptiny);
      perp[1] = perp[1] / (dot + ptiny);
      perp[2] = perp[2] / (dot + ptiny);
   }
   return(0);
}
void Transform_rt2xyz( double *x, double *y, double *z, double *r, double *t, 
                       int len, Transform_t *trans) 
{
   int i;
   int dimension;
   double dot;
   double theta;
   double radian;
   double dot2;
   double sign;
   double xt, yt, zt;
   double ax, ay, az;
   double cx, cy, cz;
   double nx, ny, nz;
   double px, py, pz;
   Transform_settrans(&cx, &cy, &cz, &ax, &ay, &az, &nx, &ny, &nz, 
                      &px, &py, &pz, trans);
   radian = PI / 180.;
   dimension = ndims;
   if (z == NULL) dimension = 2;
   if (dimension == 2) {
      for (i = 0; i < len; i++) {
         theta = (t[i])  * radian;
         xt = (r[i]) * cos (theta);
         yt = (r[i]) * sin (theta);
         x[i] = (xt * ax - yt * ay)  + cx;
         y[i] = (xt * ay + yt * ax)  + cy;
      }
   } else {
      for (i = 0; i < len ; i++) {
         xt = x[i] - cx;
         yt = y[i] - cy;
         zt = z[i] - cz;
         if (nx > -1000) {
            dot = ax * xt + ay * yt + az * zt;
            theta = t[i] * radian;
            x[i] = dot * ax  +  nx * r[i] * cos(theta)  +  
	                        px * r[i] * sin(theta);
            y[i] = dot * ay  +  ny * r[i] * cos(theta)  +  
	                        py * r[i] * sin(theta);
            z[i] = dot * az  +  nz * r[i] * cos(theta)  +  
	                        pz * r[i] * sin(theta);
            x[i] = x[i] + cx;
            y[i] = y[i] + cy;
            z[i] = z[i] + cz;
         } else {
            dot = ax * xt + ay * yt + az * zt;
            px   =  xt - ax * dot;
            py   =  yt - ay * dot;
            pz   =  zt - az * dot;
            dot2 = sqrt(px * px + py * py + pz * pz) + ptiny;
            px   =  px / dot2;
            py   =  py / dot2;
            pz   =  pz / dot2;
            theta = t[i] * radian;
            xt = (r[i]) * cos (theta);
            yt = (r[i]) * sin (theta);
            x[i] = xt * ax + yt * px + cx;
            y[i] = xt * ay + yt * py + cy;
            z[i] = xt * az + yt * pz + cz;
         }
      }
   }
}
void Transform_xyz2rt(double *x, double *y, double *z, double *r, double *t, 
                      int len, Transform_t *trans) 
{
   int i;
   int dimension;
   double dot;
   double cross; 
   double dot1, dot2;
   double sign;
   double xt, yt, zt;
   double cx, cy, cz;
   double ax, ay, az;
   double nx, ny, nz;
   double px, py, pz;
   Transform_settrans(&cx, &cy, &cz, &ax, &ay, &az, &nx, &ny, &nz, 
                      &px, &py, &pz, trans);
   dimension = ndims;
   if (z == NULL) dimension = 2;
   if (dimension == 2) {
      for (i = 0; i < len; i++) {
         xt = x[i] - cx;
         yt = y[i] - cy;
         r[i] = sqrt( xt * xt + yt * yt);
         cross = (yt * ax - xt * ay);
         dot = (xt * ax + yt * ay) / (r[i] + ptiny);
         sign = 1.;
         if (cross < 0) sign = -1;
         if (nx > -1000) {
            if ((xt * nx + yt * ny ) < 0) {
               sign = -1.;
            }
         }
         if (fabs(cross) < 1e-10) {
            if (dot > 0) t[i] = 0.;
            if (dot < 0) t[i] = 180.;
         } else {
            t[i] = sign * (180. * acos(dot)) / PI;
         }
      }
   } else {
      for (i = 0; i < len ; i++) {
         xt = x[i] - cx;
         yt = y[i] - cy;
         zt = z[i] - cz;
         sign = 1.;
         if (nx > -1000) {
            dot1 = (xt * nx + yt * ny + zt * nz);
            dot2 = (xt * px + yt * py + zt * pz);
            r[i] = sqrt(dot1 * dot1 + dot2 * dot2);
            dot = dot1 / (r[i] + ptiny);
            if (dot2 < 0.) sign = -1.;
         } else {
            r[i] = sqrt(xt * xt + yt * yt + zt * zt);
            dot = (ax * xt + ay * yt + az * zt)/ (r[i] + ptiny);
         }
         t[i] = sign * (180. * acos(dot))/ PI;
      }
   }
}
int Transform_setptr(char *name1, char *name2, char *name3, double *p[3],
                     double *x, double *y, double *z,
                     double *r, double *theta, double *phi, double *t)
{
   int ifrt = 0;
   if (!strcmp(name1,"x")) {
      p[0] = x;
   } else if (!strcmp(name1,"y")) {
      p[0] = y;
   } else if (!strcmp(name1,"z")) {
      p[0] = z;
   } else if (!strcmp(name1,"r")) {
      p[0] = r;
      ifrt = 1;
   } else if (!strcmp(name1,"t")) {
      p[0] = t;
      ifrt = 1;
   } else if (!strcmp(name1,"theta")) {
      p[0] = theta;
      ifrt = 1;
   } else if (!strcmp(name1,"phi")) {
      p[0] = phi;
      ifrt = 1;
   } 
   if (!strcmp(name2,"x")) {
      p[1] = x;
   } else if (!strcmp(name2,"y")) {
      p[1] = y;
   } else if (!strcmp(name2,"z")) {
      p[1] = z;
   } else if (!strcmp(name2,"r")) {
      p[1] = r;
      ifrt = 1;
   } else if (!strcmp(name2,"t")) {
      p[1] = t;
      ifrt = 1;
   } else if (!strcmp(name2,"theta")) {
      p[1] = theta;
      ifrt = 1;
   } else if (!strcmp(name2,"phi")) {
      p[1] = phi;
      ifrt = 1;
   } 
   if (!strcmp(name3,"x")) {
      p[2] = x;
   } else if (!strcmp(name3,"y")) {
      p[2] = y;
   } else if (!strcmp(name3,"z")) {
      p[2] = z;
   } else if (!strcmp(name3,"r")) {
      p[2] = r;
      ifrt = 1;
   } else if (!strcmp(name3,"t")) {
      p[2] = t;
      ifrt = 1;
   } else if (!strcmp(name3,"theta")) {
      p[2] = theta;
      ifrt = 1;
   } else if (!strcmp(name3,"phi")) {
      p[2] = phi;
      ifrt = 1;
   } 
   return(ifrt);
}
void Transform_getcoord(double *x,double *y,double *z,double *r,double *t,
                        double *p, int *ndx, int len, int array_type, 
			int ifrt, Domain_t *domain, Transform_t *trans)
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
   if (ifrt) Transform_xyz2rt(x,y,z,r,t,len,trans);
}
void Transform_settrans(double *cx, double *cy, double *cz,
                        double *ax, double *ay, double *az,
                        double *nx, double *ny, double *nz,
                        double *px, double *py, double *pz,
                        Transform_t *trans) {
   if (trans == NULL) {
      *cx = cent[0];
      *cy = cent[1];
      *cz = cent[2];
      *ax = axis[0];
      *ay = axis[1];
      *az = axis[2];
      *nx = norm[0];
      *ny = norm[1];
      *nz = norm[2];
      *px = perp[0];
      *py = perp[1];
      *pz = perp[2];
   } else {
      *cx = trans->cent[0];
      *cy = trans->cent[1];
      *cz = trans->cent[2];
      *ax = trans->axis[0];
      *ay = trans->axis[1];
      *az = trans->axis[2];
      *nx = trans->norm[0];
      *ny = trans->norm[1];
      *nz = trans->norm[2];
      *px = trans->perp[0];
      *py = trans->perp[1];
      *pz = trans->perp[2];
   } 
}
void Transform_parse(char *name) {
   char op[MAXLINE];
   double mycent[3];
   double myaxis[3];
   double mynorm[3];
   double *axisptr = NULL;
   double *centptr = NULL;
   double *normptr = NULL;
   int cflag;
   int gotone = 1;
   while (gotone) {
      peekc(op);
      if (!strcmp(op,"axis")) {
         geta(op);
         myaxis[0] = getf(&cflag);
         myaxis[1] = getf(&cflag);
         if (ndims == 3) myaxis[2] = getf(&cflag);
         axisptr = axis;
      } else if (!strcmp(op,"cent")) {
         geta(op);
         mycent[0] = getf(&cflag);
         mycent[1] = getf(&cflag);
         if (ndims == 3) mycent[2] = getf(&cflag);
         centptr = cent;
      } else if ((!strcmp(op,"norm")) ||
                 (!strcmp(op,"normal"))) {
         geta(op);
         mynorm[0] = getf(&cflag);
         mynorm[1] = getf(&cflag);
         if (ndims == 3) mynorm[2] = getf(&cflag);
         normptr = norm;
      } else {
         gotone = 0;
      } 
   }
   Transform_add(name, centptr, axisptr, normptr);
}

#ifdef SILO
int Transform_wtsilo(DBfile *idbid) {
   char *me = "Transform_wtsilo";
   char msg[MAXLINE];
   char name[MAXLINE];
   char **names = NULL;
   int i, num;
   int error = 0;
   int dims[3];
   Transform_t *trans;
   dims[0] = 1;
   names = rgst_list_objs_by_type(&num, "Transform_t");
   if (num == 0) return(0);
   error  = DBMkDir(idbid,"/Global/Transforms");
   error += DBSetDir(idbid,"/Global/Transforms");
   for (i = 0; i < num; i++) {
      trans = rgst_get_t(names[i], "Transform_t");
      if (trans == NULL) ctlerror(me, logic_err);
      sprintf(name,"Transform%d",i);
      error = rgst_write_struct_in_dir(idbid, name, "Transform_t",trans, NULL);
      if (error != 0) {
         ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
      }
   }
   dims[0] = 1;
   error += DBSetDir(idbid,"/Global/Transforms");
   error += DBWrite(idbid, "NumTransforms", &num, dims, 1, DB_INT);
   for(i = 0; i < num; i++) {
       FREEMEM(names[i]);
   }
   FREEMEM(names);
   return(error);
}
#endif
#ifdef SILO
int Transform_rdsilo ( DBfile *idbid ) {
   char dirname[MAXLINE];
   int i,n;
   int error;
   Transform_t *trans;
   DBShowErrors(DB_NONE, NULL);
   error = DBSetDir(idbid, "/Global/Transforms");
   DBShowErrors(DB_TOP, NULL);
   if (error != 0) return(0);
   error += DBReadVar(idbid, "NumTransforms",&n);
   for (i = 0; i < n; i++) {
      sprintf(dirname,"Transform%i",i);
      trans = rgst_read_struct_in_dir(idbid, dirname, "Transform_t", 
                                      NULL, NULL);
      sprintf(dirname,"Transform_%s",trans->name);
      rgst_add(dirname,"Transform_t", trans, NULL);
   }
   return(0);
}
#endif

int Transform_free(void) {
   char realname[MAXLINE];
   char **names = NULL;
   int i, num;
   Transform_t *trans;
   names = rgst_list_objs_by_type(&num, "Transform_t");
   for (i = 0; i < num; i++) {
      trans = rgst_get_t(names[i], "Transform_t");
      sprintf(realname,"Transform_%s",trans->name);
      rgst_del(realname);
      FREEMEM(trans);
   }
   for(i = 0; i < num; i++) {
       FREEMEM(names[i]);
   }
   FREEMEM(names);
   return(0);
}
void Transform_setup_attrs( void ) {
  char *me = "Transform_setup_attrs";
  static int first_time_thru = TRUE;
  if (RGST_ADD_ATTR_TO_FIELDS("Transform_t","dump") != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  if (first_time_thru == TRUE) {
    inst_c("Transform_free", Transform_free, zargse, 0, symtab);
    rgst_add_attr(A_OBJECT,"Transform_free", "Function_Free");

#ifdef SILO
    inst_c("Transform_wtsilo", Transform_wtsilo, zargse, 0, symtab);
    rgst_add_attr(A_OBJECT,"Transform_wtsilo", "Function_WriteSilo");
    inst_c("Transform_rdsilo", Transform_rdsilo, zargse, 0, symtab);
    rgst_add_attr(A_OBJECT,"Transform_rdsilo", "Function_ReadSilo");
#endif
    first_time_thru = FALSE;
  }
}
int Transform_getpolar( int mode ) {
   char *me = "Transform_getpolar";
   char msg[MAXLINE];
   char name[MAXLINE];
   int error = 0; 
   int len;
   int i;
   double *x, *y, *z;
   double *r, *t, *p;
   double *m;
   NodeWindow_t *ndxin = NULL;
   NodeWindow_t *ndxin_cp = NULL;
   if (mode == 0) sprintf(name,"radius");
   if (mode == 1) sprintf(name,"theta");
   if (mode == 2) sprintf(name,"phi");
   error = NodeWindow_read(name,&ndxin);
   if (error != 0) return(-1);
   ndxin_cp = MALLOT(NodeWindow_t,1);
   len = NodeWindow_compact(ndxin, ndxin_cp, -1, NDX_NO_OVERLAP, NDX_REAL,
                            NDX_NODAL);
   NodeWindow_free(ndxin);
   x = MALLOT(double, 7 * ndxin_cp->len_total);
   y = x +  1 * ndxin_cp->len_total;
   z = x +  2 * ndxin_cp->len_total;
   m = x +  3 * ndxin_cp->len_total;
   r = x +  4 * ndxin_cp->len_total;
   t = x +  5 * ndxin_cp->len_total;
   p = x +  6 * ndxin_cp->len_total;
   for (i = 0; i < ndxin_cp->len_total; i++) {
      x[i] = 0.;
      y[i] = 0.;
      z[i] = 0.;
      r[i] = 0.;
      t[i] = 0.;
      p[i] = 0.;
      m[i] = 0.;
   }
   if (ndims == 2) {
      for (i = 0; i < ndxin_cp->len; i++) {
         int j    =  ndxin_cp->pos[i];
         int ip   =  ndxin_cp->ndx[i];
         int iblk =  ndxin_cp->blk[i];
         x[j] = domains[iblk].x[ip];
         y[j] = domains[iblk].y[ip];
         m[j] = m[j] + 1;
      }
   } else {
      for (i = 0; i < ndxin_cp->len; i++) {
         int j    =  ndxin_cp->pos[i];
         int ip   =  ndxin_cp->ndx[i];
         int iblk =  ndxin_cp->blk[i];
         x[j] = domains[iblk].x[ip];
         y[j] = domains[iblk].y[ip];
         z[j] = domains[iblk].z[ip];
         m[j] = m[j] + 1;
      }
   } 
   if (ifparallel) {
      comreduce(x,4*ndxin_cp->len_total, COM_SUM, COM_ALL, COM_DOUBLE);
   }
   len = ndxin_cp->len_total;
   NodeWindow_free(ndxin_cp);
   for (i = 0; i < len; i++) {
      if (m[i] > 1.) {
         x[i] = x[i] / m[i];
         y[i] = y[i] / m[i];
         z[i] = z[i] / m[i];
      }
   }
   Transform_xyz2rt(x, y, z, r, t, len, NULL);
   if (mode == 0) {
      if (len == 1) {
         ctloutput(me,name,R_DOUBLE, r[0]);
      } else if (len > 1) {
         ctloutput(me,name,R_DOUBLE_ARRAY, r,len);
      } 
   } else if (mode == 1) {
      if (len == 1) {
         ctloutput(me,name,R_DOUBLE, t[0]);
      } else if (len > 1) {
         ctloutput(me,name,R_DOUBLE_ARRAY, t,len);
      } 
   } else if (mode == 2) {
      if (len == 1) {
         ctloutput(me,name,R_DOUBLE, p[0]);
      } else if (len > 1) {
         ctloutput(me,name,R_DOUBLE_ARRAY, p,len);
      } 
   } 
   FREEMEM(x)
   return(error);
}
