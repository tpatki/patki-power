#include "irs.h"
#include "irsbndry.h"
#include "irscom.h"
#include "irsctl.h"
#include "irsgen.h"
#include "BlockMapping.h"
#include "Boundary.h"
#include "Extents.h"
#include "NodeList.h"
#include "Spline.h"
#include "FunctionTimer.h"
#include "GbndList.h"
#include "Transform.h"
#include "UserList.h"
typedef struct {
   double rad;
   double t12;
   double t23;
   double t34;
   double t41;
   double insin12;
   double insin23;
   double insin34;
   double insin41;
   double v1[3];
   double v2[3];
   double v3[3];
   double v4[3];
   double vave[3];
} MeshGenSphericalSection_t;
typedef struct {
   Spline_t    *ptr;   
   double      ind[2];   
   char        indvar[4]; 
} MeshGenSpline_t;

typedef struct {
   int ifratio;      
   double ratio;     
   int logical;      
} MeshGenTransform_t;
typedef struct {
   double *x;   
   double *y;
   double *z;
   double *m;   
   int ip;      
   int jp;
   int kp;
   int len;     
   Extents_t ext;  
} MeshGenPackSurf_t;
struct MeshGen_t_ {
   int      type;         
   int      inputtype;    
   int      between  ;    
   int      notlocal ;    
   char     label[4];     
   int      ncoord;       
   int      ifdel;        
   double   coord[6];     
   Extents_t ext;         
   int id1, id2, id3;     
   int i1, i2;            
   double *x;             
   double *y;
   double *z;
   double *r;
   double *t;
   int scaleflag;         
   int    relax_iter;     
   int    relax_surf;     
   double relax_conv;     
   double  *mask;
   int len;               
   NodeWindow_t  *trans_ndx;  
   char       *func;       
   double     *points;     
   int        npoints;     
   MeshGenSphericalSection_t sphereSection;

   MeshGenSpline_t spline;
   MeshGenSpline_t spline_1;
   MeshGenSpline_t spline_2;
   struct MeshGen_t_ *next;
} ;
typedef struct MeshGen_t_ MeshGen_t;
#define MESHGEN_NULL             0
#define MESHGEN_SPLINE           1
#define MESHGEN_TRANS            2
#define MESHGEN_ENDS             3
#define MESHGEN_FUNC             4
#define MESHGEN_PRESET           5
#define MESHGEN_POINTS           6
#define MESHGEN_NORM             8
#define MESHGEN_TABLE            9
#define MESHGEN_ENDS_TO         10
#define MESHGEN_ENDS_FROM       11
#define MESHGEN_SPHERE_SEC      12
#define MESHGEN_PLANE           13
#define MESHGEN_CYL             14
#define MESHGEN_LINEARFILL      15
#define MESHGEN_TRANSFINITEFILL 16
#define MESHGEN_COORDS      0
#define MESHGEN_VELOCITY    1
static int meshgen_getcoord( MeshGen_t *data, NodeWindow_t *ndxin, int flag) ;
static void meshgen_apply( MeshGen_t *data, MeshGenTransform_t *transform, 
                    NodeWindow_t *ndxin);
static void meshgen_apply1d( MeshGen_t *data, MeshGenTransform_t *transform, 
                      int ublk, int id1, int id2, int id3) ;
static void meshgen_fillends( MeshGen_t *data, MeshGenTransform_t *transform) ;
static void meshgen_add(MeshGen_t *newmg, MeshGen_t **list) ;
static void meshgen_free(MeshGen_t *mgin) ;
static void meshgen_calcarc(double *arc, double *x, double *y, double *z,
                     int offset, int imin, int imax, int ip) ;
static int meshgen_setptr(char *label, MeshGen_t *data, double **p1, double **p2, 
                                 double **p3) ;
static void meshgen_trans(MeshGen_t *data, NodeWindow_t *ndxin, MeshGenTransform_t *transform) ;
static void meshgen_spline(MeshGen_t *data, MeshGenTransform_t *transform) ;
static void meshgen_unpack(MeshGen_t *data, int ublk, int id1, int id2, int id3);
static void meshgen_pack(MeshGen_t *data, int len, int ublk, int id1, int id2, int id3, 
                  int reduce) ;
static void meshgen_func(MeshGen_t *data, MeshGenTransform_t *transform) ;
static void meshgen_pnts(MeshGen_t *data, MeshGenTransform_t *transform) ;
static void  meshgen_norm(MeshGen_t *data, NodeWindow_t *ndxin) ;
static void  meshgen_sphereSection(MeshGen_t *data, 
                            MeshGenTransform_t *transform, 
                            NodeWindow_t *ndxin) ;
static void meshgen_sphereSection_getxyz(MeshGen_t *data, double s, double t, 
                                 double *x, double *y, double *z) ;
static void meshgen_fillbetween(MeshGen_t *data, MeshGenTransform_t *transform) ;
static void meshgen_init( MeshGen_t *data ) ;
static void  meshgen_sphereSection_init(MeshGenSphericalSection_t *sps) ;
static void meshgen_applybc(int *ndx, int *offset, double *nx, double *ny,
                     double *nz, int len, Domain_t *domain) ;
static void meshgen_bc(int *ondx, int *offset, double *nx, double *ny,
                double *nz, int *olen, int mode, Domain_t *domain) ;
void meshgen_linearfill(int logical, NodeWindow_t *ndxin) ;
static int meshgen_packsurfs(NodeWindow_t *ndxin, MeshGenPackSurf_t **lfin) ;
static void meshgen_freesurfs(MeshGenPackSurf_t **lfin, int ns) ;
static void meshgen_transfinite(int logical, NodeWindow_t *ndxin) ;
static void meshgen_sphereSection_parse(MeshGen_t *data, int intype) ;
static int coordinate_type ;  
int meshgen_input( int inputtype ) {
   char *me = "meshgen_input";
   char op[MAXLINE];
   char msg[MAXLINE];
   char aname[MAXLINE];
   char *valid = "xyzrt";
   int i;
   int iblk;
   int gotone;
   int len;
   int ifequal;
   int ifdel;
   int logical;
   int cflag;
   int error = 0 ;
   int iftransfinite = 0;
   double norm;
   MeshGen_t *meshargs;
   MeshGen_t *arg;
   MeshGenTransform_t *transform;
   NodeWindow_t *ndxin;
   Spline_t *spline;
   ndxin = NULL;
   meshargs = NULL;
   coordinate_type = MESHGEN_COORDS;
   if (inputtype == 0) {
      sprintf(aname,"point");
   } else if (inputtype == 1) {
      sprintf(aname,"line");
   } else if (inputtype == 2) {
      sprintf(aname,"fill");
   } else if (inputtype == 3) {
      sprintf(aname,"vpoint");
      inputtype = inputtype - 3;
      coordinate_type = MESHGEN_VELOCITY;
   } else if (inputtype == 4) {
      sprintf(aname,"vline");
      inputtype = inputtype - 3;
      coordinate_type = MESHGEN_VELOCITY;
   } else if (inputtype == 5) {
      sprintf(aname,"vfill");
      inputtype = inputtype - 3;
      coordinate_type = MESHGEN_VELOCITY;
   } 
   error = NodeWindow_read(aname,&ndxin);
   if (error != 0) return(-1);
   ifequal = 0;
   if (inputtype != 0) {
      peekc(op);
      if (!strcmp(op,"=")) {
        geta(op);
        ifequal = 1;
      } else {
        ifequal = 0;
      }
   } else {
      geta(op);
      if (strcmp(op,"=")) {
         sprintf(msg,"%s command needs an equal sign.",aname);
         ctlerror(me,msg);
      }
      ifequal = 1;
   } 
   transform = MALLOT(MeshGenTransform_t,1);
   transform->logical = -1;
   transform->ifratio = 0;
   transform->ratio = 1.0;
   gotone = 0;
   if (ifequal) gotone = 1;
   logical = -1;
   ifdel = 0;
   while (gotone) {
      peekc(op);
      if ((!strcmp(op,"x")) || 
          (!strcmp(op,"y")) ||
          (!strcmp(op,"z")) ||
          (!strcmp(op,"r")) ||
          (!strcmp(op,"t")) ||
          (!strcmp(op,"xy")) ||
          (!strcmp(op,"yx")) ||
          (!strcmp(op,"xz")) ||
          (!strcmp(op,"zx")) ||
          (!strcmp(op,"yz")) ||
          (!strcmp(op,"zy")) ||
          (!strcmp(op,"rt")) ||
          (!strcmp(op,"tr")) ||
          (!strcmp(op,"xyz")) ||
          (!strcmp(op,"yzx")) ||
          (!strcmp(op,"zxy")) ||
          (!strcmp(op,"yxz")) ||
          (!strcmp(op,"xzy")) ||
          (!strcmp(op,"zyx")) ||
          (!strcmp(op,"xyz"))) {
         if (*ps == '(') {
            gotone = 0;
            break;
         }
         arg = MALLOT(MeshGen_t,1);
         meshgen_init(arg);
         meshgen_add(arg,&meshargs);
	 geta(arg->label);
	 arg->scaleflag = 0;
	 arg->ifdel = ifdel;
	 ifdel = 0;
	 if (arg->ifdel) {
            arg->type = meshgen_getcoord( arg, ndxin, 0);
	 } else {
            arg->type = meshgen_getcoord( arg, ndxin, inputtype);
	 } 
      } else if (!strcmp(op,"del")) {
         geta(op);
         ifdel = 1;
      } else if (!strcmp(op,"i")) {
         geta(op);
         transform->logical = 0;
      } else if (!strcmp(op,"j")) {
         geta(op);
         transform->logical = 1;
      } else if (!strcmp(op,"k")) {
         geta(op);
         transform->logical = 2;
      } else if (!strcmp(op,"ij")) {
         geta(op);
         transform->logical = 3;
      } else if (!strcmp(op,"ji")) {
         geta(op);
         transform->logical = 3;
      } else if (!strcmp(op,"jk")) {
         geta(op);
         transform->logical = 4;
      } else if (!strcmp(op,"kj")) {
         geta(op);
         transform->logical = 4;
      } else if (!strcmp(op,"ik")) {
         geta(op);
         transform->logical = 5;
      } else if (!strcmp(op,"ki")) {
         geta(op);
         transform->logical = 5;
      } else if (!strcmp(op,"ijk")) {
         geta(op);
         transform->logical = 6;
      } else if (!strcmp(op,"tf")) {
         geta(op);
         iftransfinite = 1;
      } else if (!strcmp(op,"between")) {
         geta(op);
         arg = MALLOT(MeshGen_t,2);
         meshgen_init(&arg[0]);
         meshgen_init(&arg[1]);
         meshgen_add(arg,&meshargs);
         arg[0].type    = meshgen_getcoord( &arg[0], ndxin, inputtype);
         arg[0].between = 1;
         geta(op);
         arg[1].type = meshgen_getcoord( &arg[1], ndxin, inputtype);
         arg[1].between = 1;
      } else if (!strcmp(op,"ratio")) {
         geta(op);
         transform->ratio = getf(&cflag);
         transform->ifratio = geti(&cflag);
      } else {
         gotone = 0;
      } 
   }
   if (meshargs == NULL) {
      arg = MALLOT(MeshGen_t,1);
      meshgen_init(arg);
      arg->ifdel = 0;
      if (ndims == 2) strcpy(arg->label,"xy");
      if (ndims == 3) strcpy(arg->label,"xyz");
      arg->ncoord = strlen(arg->label);
      arg->type = MESHGEN_PRESET;
      if (transform->logical > 2)  arg->type = MESHGEN_LINEARFILL;
      if (transform->ifratio == 0) arg->type = MESHGEN_LINEARFILL;
      if (iftransfinite == 1)      arg->type = MESHGEN_TRANSFINITEFILL;
      meshgen_add(arg,&meshargs);
   }
   iftransfinite = 0;
   arg = meshargs;
   while (arg != NULL) {
      NodeWindow_t *ndxin_ptr = ndxin;
      arg->inputtype = inputtype;
         while (ndxin_ptr != NULL) {
            double ratio = transform->ratio;
            if (inputtype == 0) {
               transform->logical = 0;
            }
            if (inputtype == 1) {
               if (ndxin_ptr->imin != ndxin_ptr->imax) transform->logical = 0;
               if (ndxin_ptr->jmin != ndxin_ptr->jmax) transform->logical = 1;
               if (ndxin_ptr->kmin != ndxin_ptr->kmax) transform->logical = 2;
            }
            meshgen_apply(arg, transform, ndxin_ptr);
	    transform->ratio = ratio;
            ndxin_ptr = ndxin_ptr->next;
         }
      arg = arg->next;
   }
   NodeWindow_free(ndxin);
   meshgen_free(meshargs);
   FREEMEM(transform);
   return(0);
}
static void meshgen_init( MeshGen_t *data ) {
   data->type      = MESHGEN_NULL;
   data->inputtype = 0;
   data->between   = 0;
   data->notlocal  = 0;
   data->id1   = 0;
   data->id2   = 0;
   data->id3   = 0;
   data->i1    = 0;
   data->i2    = 0;
   data->label[0] = '\0';
   data->ncoord   = 0;
   data->ifdel    = 0;
   data->coord[0] = 0;
   data->coord[1] = 0;
   data->coord[2] = 0;
   data->coord[3] = 0;
   data->coord[4] = 0;
   data->coord[5] = 0;
   data->x = NULL;
   data->y = NULL;
   data->z = NULL;
   data->r = NULL;
   data->t = NULL;
   data->scaleflag = 0; 
   data->relax_iter = 0; 
   data->relax_surf = 0; 
   data->relax_conv = 0; 
   data->mask = NULL;
   data->len = 0;       
   data->trans_ndx = NULL;
   data->func  = NULL;
   data->points = NULL; 
   data->npoints = 0;
   data->next = NULL;
} 
static int meshgen_getcoord( MeshGen_t *data, NodeWindow_t *ndxin, int flag) {
   char *me = "meshgen_getcoord";
   char *valid = "xyzrt";
   char msg[MAXLINE];
   char op[MAXLINE];
   int i;
   int cflag;
   int len;
   int type;
   int ifun;
   int error = 0;
   type = -1;
   data->trans_ndx = NULL;
   data->ncoord = strlen(data->label);
   peekc(op);
   if (!strcmp(op,"spline")) {
      geta(op);
      geta(op);
      data->spline.ptr = spline_find(op);
      if (data->spline.ptr == NULL) {
         sprintf(msg,"Spline %s is not defined.",op);
         ctlwarning(me,msg);
         return(-1);
      }
      data->spline.indvar[0] = '\0';
      data->spline_1.indvar[0] = '\0';
      data->spline_2.indvar[0] = '\0';
      peekc(op);
      if (ifnotin(valid,op)) {
         data->spline.ind[0] = getf(&cflag);
         if (flag) {
            data->spline.ind[1] = getf(&cflag);
         } else {
            data->spline.ind[1] = data->spline.ind[0];
         } 
      } else {
         geta(op);
         strcpy(data->spline.indvar,op);
      } 
      type = MESHGEN_SPLINE; 
   } else if (!strcmp(op,"trans")) {
      geta(op);
      error = NodeWindow_read("trans",&data->trans_ndx);
      if (error != 0) return(-1);
      if (data->trans_ndx->next != NULL) {
         sprintf(msg,"Cannot accept multi-block node lists in trans command.");
         ctlwarning(me,msg);
         return(-1);
      }
      type = MESHGEN_TRANS; 
   } else if (!strcmp(op,"dnorm")) {
      geta(op);
      data->coord[0] = getf(&cflag);
      type = MESHGEN_NORM; 
   } else if (!strcmp(op,"scale")) {
      geta(op);
      ifun = lineop_grab(&data->func,"}",ps);
      data->scaleflag = 1;
      if (ifun < 0) {
         ctlwarning(me,"Error parsing input for scale.");
         return(-1);
      }
      ps   = NULL;
      if (data->ncoord > 1) {
         sprintf(msg,"Scale %s only returns a single argument and thus cannot be used to fill %s.",op,data->label);
         ctlwarning(me,msg);
         return(-1);
      }
      type = MESHGEN_FUNC; 
   } else if (!strcmp(op,"func")) {
      geta(op);
      ifun = lineop_grab(&data->func,"}",ps);
      if (ifun < 0) {
         ctlwarning(me,"Error parsing input for func.");
         return(-1);
      }
      ps   = NULL;
      if (data->ncoord > 1) {
         sprintf(msg,"Function %s only returns a single argument and thus cannot be used to fill %s.",op,data->label);
         ctlwarning(me,msg);
         return(-1);
      }
      type = MESHGEN_FUNC; 
   } else if (!strcmp(op,"pnts")) {
      geta(op);
      data->npoints = getflst(&data->points,-1);
      if (data->npoints == 0) {
         ctlwarning(me,"Error reading pnts data.");
         return(-1);
      }
      if ((data->npoints % data->ncoord) != 0) {
         sprintf(msg,"The number of data points in the pnts command must be "
                      "divisable by the number of coordinates");
         ctlwarning(me,msg);
         return(-1);
      }
      type = MESHGEN_POINTS; 
   } else if ((!strcmp(op,"sphere_section")) ||
              (!strcmp(op,"cyl_section")) ||
              (!strcmp(op,"plane"))) {
      if (!strcmp(op,"sphere_section")) type = MESHGEN_SPHERE_SEC;
      if (!strcmp(op,"plane"))          type = MESHGEN_PLANE;
      if (!strcmp(op,"cyl_section"))    type = MESHGEN_CYL;
      geta(op);
      meshgen_sphereSection_parse(data, type) ;
   } else if (!strcmp(op,"table")) {
      
   } else if (!strcmp(op,"from")) {
      geta(op);
      for (i = 0; i < data->ncoord; i++) { 
         data->coord[i] = getf(&cflag);
      }
      type = MESHGEN_ENDS_FROM; 
   } else if (!strcmp(op,"to")) {
      geta(op);
      for (i = 0; i < data->ncoord; i++) { 
         data->coord[i] = getf(&cflag);
      }
      type = MESHGEN_ENDS_TO; 
   } else {
      for (i = 0; i < data->ncoord; i++) { 
         data->coord[i] = getf(&cflag);
      }
      if (flag) {
         for (i = 0; i < data->ncoord; i++) { 
            data->coord[i + data->ncoord] = getf(&cflag);
         }
      } else {
         for (i = 0; i < data->ncoord; i++) { 
            data->coord[i + data->ncoord] = data->coord[i];
         }
      } 
      type = MESHGEN_ENDS; 
   } 
   return(type);
}
static void meshgen_apply( MeshGen_t *data, MeshGenTransform_t *transform, 
                    NodeWindow_t *ndxin) {
   char *me = "meshgen_apply";
   char msg[MAXLINE];
   int i,j,k;
   int ublk;
   int id1,id2,id3;
   int i1,i2,i3;
   int type;
   int ip[3];
   double factor;
   ublk = ndxin->ublk;
   ip[0] = 1;
   ip[1] = umap[ublk].jp;
   ip[2] = umap[ublk].kp;
   type = data->inputtype;
   data->ext.imin = MIN(ndxin->in[0][0], ndxin->in[0][1]);
   data->ext.jmin = MIN(ndxin->in[1][0], ndxin->in[1][1]);
   data->ext.kmin = MIN(ndxin->in[2][0], ndxin->in[2][1]);
   data->ext.imax = MAX(ndxin->in[0][0], ndxin->in[0][1]);
   data->ext.jmax = MAX(ndxin->in[1][0], ndxin->in[1][1]);
   data->ext.kmax = MAX(ndxin->in[2][0], ndxin->in[2][1]);
   if (data->between == 0) {
      if (data->type == MESHGEN_TRANS) {
         meshgen_trans(data, ndxin, transform);
         return;
      }
      if ((data->type == MESHGEN_SPHERE_SEC) ||
          (data->type == MESHGEN_CYL) ||
          (data->type == MESHGEN_PLANE)) {
         meshgen_sphereSection(data, transform, ndxin);
         return;
      }
      if (data->type == MESHGEN_NORM) {
         meshgen_norm(data, ndxin);
         return;
      }
      if (data->type == MESHGEN_LINEARFILL) {
         meshgen_linearfill(transform->logical, ndxin);
         return;
      }
      if (data->type == MESHGEN_TRANSFINITEFILL) {
         meshgen_transfinite(transform->logical, ndxin);
         return;
      }   
   }
   meshgen_setlogical(transform->logical,&i1,&i2,&i3);
   data->len = ((abs(ndxin->in[i1][1] - ndxin->in[i1][0]) + 1)/
                      abs(ndxin->in[i1][2]));
   if (data->type == MESHGEN_POINTS) {
      int nval = (data->npoints / data->ncoord);
      if ( ((data->len - 1) % (nval - 1)) != 0 ) {
         sprintf(msg,"Number of points %i does not conform to number of mesh points %i",data->npoints / data->ncoord, data->len);
         ctlwarning(me,msg);
      }
   }
   data->x    = ALLOT(double, 6 * data->len);
   data->y    = data->x    + data->len;
   data->z    = data->y    + data->len;
   data->mask = data->z    + data->len;
   data->r    = data->mask + data->len;
   data->t    = data->r    + data->len;
   if (transform->ifratio) {
      factor = transform->ratio;
      transform->ratio = ratioeval( factor, transform->ifratio, data->len);
   }
   if (ndims == 2) {
      for (j = ndxin->in[i2][0]; j <= ndxin->in[i2][1]; j += ndxin->in[i2][2]) {
         data->id1 = ip[i1] * ndxin->in[i1][0] + ip[i2] * j;
         data->id2 = ip[i1] * ndxin->in[i1][1] + ip[i2] * j;
         data->id3 = ndxin->in[i1][2] * ip[i1];
         data->i1  = j;
         meshgen_apply1d(data, transform, ublk, data->id1, data->id2, data->id3);
      }
   } else {
      for (k = ndxin->in[i3][0]; k <= ndxin->in[i3][1]; k += ndxin->in[i3][2]) {
         for (j = ndxin->in[i2][0]; j <= ndxin->in[i2][1]; j += ndxin->in[i2][2]) {
            data->id1 = ip[i1] * ndxin->in[i1][0] + ip[i2] * j + ip[i3] * k;
            data->id2 = ip[i1] * ndxin->in[i1][1] + ip[i2] * j + ip[i3] * k;
            data->id3 = ndxin->in[i1][2] * ip[i1];
            data->i1  = j;
            data->i2  = k;
            meshgen_apply1d(data, transform, ublk, data->id1, data->id2, data->id3);
         }
      }
   } 
   FREEMEM(data->x);
 } 
static void meshgen_apply1d( MeshGen_t *data, MeshGenTransform_t *transform, 
                      int ublk, int id1, int id2, int id3) {
   int i;
   int j;
   int id;
   int i1, i2, i3;
   int reduce;
   j = 0;
   i1 = MIN(id1,id2);
   i2 = MAX(id1,id2);
   i3 = abs(id3);
   reduce = 1;
   if (data->type == MESHGEN_ENDS)    reduce = 0;
   if (data->between == 1) reduce = 0;
   if ((data->type == MESHGEN_SPLINE) && (data->spline.indvar[0] == '\0')) reduce = 0;
  
   if (ifcom) {
      meshgen_pack(data, data->len, ublk, id1, id2, id3, reduce );
   } else {
      id = id1;
      for (i = i1; i <= i2; i += i3) {
         if (ndims == 2) {
            if (coordinate_type == MESHGEN_COORDS) {
               data->x[j] = domains[ublk].x[id];
               data->y[j] = domains[ublk].y[id];
            } else {
               data->x[j] = domains[ublk].xdot[id];
               data->y[j] = domains[ublk].ydot[id];
            } 
         } else {
            if (coordinate_type == MESHGEN_COORDS) {
               data->x[j] = domains[ublk].x[id];
               data->y[j] = domains[ublk].y[id];
               data->z[j] = domains[ublk].z[id];
            } else {
               data->x[j] = domains[ublk].xdot[id];
               data->y[j] = domains[ublk].ydot[id];
               data->z[j] = domains[ublk].zdot[id];
            } 
         } 
         j++;
         id += id3;
      }
   }
   if (data->between == 1) { 
      meshgen_fillbetween(data, transform);
   } else if (data->type == MESHGEN_SPLINE) { 
      meshgen_spline(data, transform);
   } else if (data->type == MESHGEN_FUNC) {
      meshgen_func(data, transform);
   } else if (data->type == MESHGEN_POINTS) {
      meshgen_pnts(data, transform);
   } else if (data->type == MESHGEN_TABLE) {
   } else if (data->type == MESHGEN_ENDS) {
      meshgen_fillends(data, transform);
   } else if (data->type == MESHGEN_ENDS_TO) {
      meshgen_fillends(data, transform);
   } else if (data->type == MESHGEN_ENDS_FROM) {
      meshgen_fillends(data, transform);
   } else if (data->type == MESHGEN_PRESET) {
      if (ndims == 2) {
         data->coord[0] = data->x[0];
         data->coord[1] = data->y[0];
         data->coord[2] = data->x[data->len - 1];
         data->coord[3] = data->y[data->len - 1];
      } else {
         data->coord[0] = data->x[0];
         data->coord[1] = data->y[0];
         data->coord[2] = data->z[0];
         data->coord[3] = data->x[data->len - 1];
         data->coord[4] = data->y[data->len - 1];
         data->coord[5] = data->z[data->len - 1];
      } 
      meshgen_fillends(data, transform);
   }
   if (ifcom) {
      meshgen_unpack(data, ublk, id1, id2, id3);
   } else {
      j = 0;
      id = id1;
      for (i = i1; i <= i2; i += i3) {
         if (ndims == 2) {
            if (coordinate_type == MESHGEN_COORDS) {
               domains[ublk].x[id] = data->x[j];
               domains[ublk].y[id] = data->y[j];
               domains[ublk].node[id] = 1;
            } else {
               domains[ublk].xdot[id] = data->x[j];
               domains[ublk].ydot[id] = data->y[j];
            } 
         } else {
            if (coordinate_type == MESHGEN_COORDS) {
               domains[ublk].x[id] = data->x[j];
               domains[ublk].y[id] = data->y[j];
               domains[ublk].z[id] = data->z[j];
               domains[ublk].node[id] = 1;
            } else {
               domains[ublk].xdot[id] = data->x[j];
               domains[ublk].ydot[id] = data->y[j];
               domains[ublk].zdot[id] = data->z[j];
            }
         } 
         j++;
         id += id3;
      }
   }
}
static void meshgen_fillends( MeshGen_t *data, MeshGenTransform_t *transform) {
   int i;
   int ifrt;
   double cfact;
   double cfact1, cfact2, cfact3;
   double dist;
   double dist0;
   double f1, f2;
   double coord[6];
   double *p1, *p2, *p3;
   ifrt = meshgen_setptr(data->label, data, &p1, &p2, &p3);
   if (ifrt > 0) {
      Transform_xyz2rt(data->x, data->y, data->z, data->r, data->t, 
	                data->len, NULL);
   }
   coord[0] = data->coord[0];
   coord[1] = data->coord[1];
   coord[2] = data->coord[2];
   coord[3] = data->coord[3];
   coord[4] = data->coord[4];
   coord[5] = data->coord[5];
   if (data->type == MESHGEN_ENDS_TO) {
      coord[data->ncoord    ] = coord[0];
      coord[data->ncoord + 1] = coord[1];
      coord[data->ncoord + 2] = coord[2];
      if (data->ncoord >= 1) coord[0] = p1[0];
      if (data->ncoord >= 2) coord[1] = p2[0];
      if (data->ncoord == 3) coord[2] = p3[0];
   } else if (data->type == MESHGEN_ENDS_FROM) {
      if (data->ncoord >= 1) coord[data->ncoord    ] = p1[data->len - 1];
      if (data->ncoord >= 2) coord[data->ncoord + 1] = p2[data->len - 1];
      if (data->ncoord >= 3) coord[data->ncoord + 2] = p3[data->len - 1];
   } 
   if (data->ifdel) {
      if (data->ncoord == 1) {
         for (i = 0; i < data->len; i++) {
            p1[i] += coord[0];
         }
      } else if (data->ncoord == 2) {
         for (i = 0; i < data->len; i++) {
            p1[i] += coord[0];
            p2[i] += coord[1];
         }
      } else if (data->ncoord == 3) {
         for (i = 0; i < data->len; i++) {
            p1[i] += coord[0];
            p2[i] += coord[1];
            p3[i] += coord[2];
         }
      } 
      if (ifrt) {
         Transform_rt2xyz(data->x, data->y, data->z, data->r, data->t, 
	                data->len, NULL);
      }
      return;
   }
   if (data->ncoord == 1) {
      cfact1 = (coord[1] - coord[0]) / 
                              (ratiosum(transform->ratio, data->len) + ptiny);
      p1[0] = coord[0];
      for (i = 1; i < data->len - 1; i++) {
         p1[i] = p1[i-1] + cfact1;
         cfact1 = cfact1 * transform->ratio;
      }
      p1[data->len - 1] = coord[1];
   } else if (data->ncoord == 2) {
      cfact1 = (coord[2] - coord[0]) / 
                (ratiosum(transform->ratio, data->len) + ptiny);
      cfact2 = (coord[3] - coord[1]) / 
                (ratiosum(transform->ratio, data->len) + ptiny);
      p1[0] = coord[0];
      p2[0] = coord[1];
      for (i = 1; i < data->len - 1; i++) {
         p1[i] = p1[i-1] + cfact1;  
         p2[i] = p2[i-1] + cfact2;  
         cfact1 = cfact1 * transform->ratio;
         cfact2 = cfact2 * transform->ratio;
      }
      p1[data->len - 1] = coord[2];
      p2[data->len - 1] = coord[3];
   } else if (data->ncoord == 3) {
      cfact1 = (coord[3] - coord[0]) / 
                (ratiosum(transform->ratio, data->len) + ptiny);
      cfact2 = (coord[4] - coord[1]) / 
                (ratiosum(transform->ratio, data->len) + ptiny);
      cfact3 = (coord[5] - coord[2]) / 
                (ratiosum(transform->ratio, data->len) + ptiny);
      p1[0] = coord[0];
      p2[0] = coord[1];
      p3[0] = coord[2];
      for (i = 1; i < data->len - 1; i++) {
         p1[i] = p1[i-1] + cfact1;  
         p2[i] = p2[i-1] + cfact2;  
         p3[i] = p3[i-1] + cfact3;  
         cfact1 = cfact1 * transform->ratio;
         cfact2 = cfact2 * transform->ratio;
         cfact3 = cfact3 * transform->ratio;
      }
      p1[data->len - 1] = coord[3];
      p2[data->len - 1] = coord[4];
      p3[data->len - 1] = coord[5];
   } 
   if (ifrt > 0) {
      Transform_rt2xyz(data->x, data->y, data->z, data->r, data->t, 
                     data->len, NULL);
   }
}
static void meshgen_add(MeshGen_t *newmg, MeshGen_t **list) {
   MeshGen_t *local;
   local = *list;
   if (local != NULL) {
      while (local->next != NULL) local = local->next;
      local->next = newmg;
   } else {
      *list = newmg;
   } 
   newmg->next = NULL;
}
static void meshgen_free(MeshGen_t *mgin) {
   MeshGen_t *tmp;
   while (mgin != NULL) {
      tmp = mgin->next; 
      if (mgin->type == MESHGEN_FUNC) {
         FREEMEM(mgin->func);
      }
      if (mgin->type == MESHGEN_POINTS) {
         FREEMEM(mgin->points);
      }
      if (mgin->between == 1) {
         if (mgin[1].type == MESHGEN_FUNC) {
            FREEMEM(mgin[1].func);
         }
         if (mgin[1].type == MESHGEN_POINTS) {
               FREEMEM(mgin[1].points);
         }
      } 
      FREEMEM(mgin);
      mgin = tmp;
   }
   mgin = NULL;
}
static void meshgen_calcarc(double *arc, double *x, double *y, double *z,
                     int offset, int imin, int imax, int ip) {
   double arcmax;
   double dx, dy, dz;
   double *xp, *yp, *zp;
   int i,j;
   int id;
   xp = x + offset;    
   yp = y + offset;    
   zp = z + offset;    
   arcmax = 0.;
   j = 1;
   arc[0] = 0;
   if (ndims == 2) {
      for (i = imin + 1; i <= imax; i++) {
         id = i * ip;
         dx = xp[id] - xp[id - ip]; 
         dy = yp[id] - yp[id - ip]; 
         arcmax += sqrt(dx * dx + dy * dy);
         arc[j++] = arcmax;
      }
   } else {
      for (i = imin + 1; i <= imax; i++) {
         id = i * ip;
         dx = xp[id] - xp[id - ip]; 
         dy = yp[id] - yp[id - ip]; 
         dz = zp[id] - zp[id - ip]; 
         arcmax += sqrt(dx * dx + dy * dy + dz * dz);
         arc[j++] = arcmax;
      }
   }
   j = 1;
   for (i = imin + 1; i <= imax; i++ ) {
      arc[j] = arc[j] / (arcmax + ptiny);
      j++;
   }
}
static int meshgen_setptr(char *label, MeshGen_t *data, double **p1, double **p2, 
                                 double **p3) {
   int ifrt = 0;
   if (!strcmp(label,"x")) {
      *p1 = data->x;
   } else if (!strcmp(label,"y")) {
      *p1 = data->y;
   } else if (!strcmp(label,"z")) {
      *p1 = data->z;
   } else if (!strcmp(label,"r")) {
      ifrt = 1;
      *p1 = data->r;
   } else if (!strcmp(label,"t")) {
      ifrt = 2;
      *p1 = data->t;
   } else if (!strcmp(label,"xy")) {
      *p1 = data->x;
      *p2 = data->y;
   } else if (!strcmp(label,"yx")) {
      *p1 = data->y;
      *p2 = data->x;
   } else if (!strcmp(label,"xz")) {
      *p1 = data->x;
      *p2 = data->z;
   } else if (!strcmp(label,"zx")) {
      *p1 = data->z;
      *p2 = data->x;
   } else if (!strcmp(label,"yz")) {
      *p1 = data->y;
      *p2 = data->z;
   } else if (!strcmp(label,"zy")) {
      *p1 = data->z;
      *p2 = data->y;
   } else if (!strcmp(label,"rt")) {
      ifrt = 3;
      *p1 = data->r;
      *p2 = data->t;
   } else if (!strcmp(label,"tr")) {
      ifrt = 3;
      *p1 = data->t;
      *p2 = data->r;
   } else if (!strcmp(label,"xyz")) {
      *p1 = data->x;
      *p2 = data->y;
      *p3 = data->z;
   } else if (!strcmp(label,"yzx")) {
      *p1 = data->y;
      *p2 = data->z;
      *p3 = data->x;
   } else if (!strcmp(label,"zxy")) {
      *p1 = data->z;
      *p2 = data->x;
      *p3 = data->y;
   } else if (!strcmp(label,"xzy")) {
      *p1 = data->x;
      *p2 = data->z;
      *p3 = data->y;
   } else if (!strcmp(label,"zyx")) {
      *p1 = data->z;
      *p2 = data->y;
      *p3 = data->x;
   } else if (!strcmp(label,"yxz")) {
      *p1 = data->y;
      *p2 = data->x;
      *p3 = data->z;
   } 
   return(ifrt);
}
void meshgen_setlogical(int logical, int *i1, int *i2, int *i3) {
   if (logical == 0) {
      *i1 = 0;
      *i2 = 1;
      *i3 = 2;
   } else if (logical == 1) {
      *i1 = 1;
      *i2 = 0;
      *i3 = 2;
   } else if (logical == 2) {
      *i1 = 2;
      *i2 = 0;
      *i3 = 1;
   } else if (logical == 3) {
      *i1 = 0;
      *i2 = 1;
      *i3 = 2;
   } else if (logical == 4) {
      *i1 = 1;
      *i2 = 2;
      *i3 = 0;
   } else if (logical == 5) {
      *i1 = 0;
      *i2 = 2;
      *i3 = 1;
   } else if (logical == 6) {
      *i1 = 0;
      *i2 = 1;
      *i3 = 2;
   } 
}
static void meshgen_trans(MeshGen_t *data, NodeWindow_t *ndxin, 
                       MeshGenTransform_t *transform) {
   char *me = "meshgen_trans";
   char msg[MAXLINE];
   char name[MAXLINE];
   int i,j,k;
   int j2, k2;
   int i1, i2, i3;
   int id1, id2, id3;
   int ic,n;
   int ifrt;
   int ublka;
   int ublkb;
   int lena, lenb;
   int ip;
   int ipa[3];
   int ipb[3];
   int ina[3][3];
   int inb[3][3];
   double *p[3];
   double *q[3];
   MeshGen_t *data2;
   ina[0][0] = ndxin->in[0][0];
   ina[1][0] = ndxin->in[1][0];
   ina[2][0] = ndxin->in[2][0];
   ina[0][1] = ndxin->in[0][1];
   ina[1][1] = ndxin->in[1][1];
   ina[2][1] = ndxin->in[2][1];
   ina[0][2] = ndxin->in[0][2];
   ina[1][2] = ndxin->in[1][2];
   ina[2][2] = ndxin->in[2][2];
   inb[0][0] = data->trans_ndx->in[0][0];
   inb[1][0] = data->trans_ndx->in[1][0];
   inb[2][0] = data->trans_ndx->in[2][0];
   inb[0][1] = data->trans_ndx->in[0][1];
   inb[1][1] = data->trans_ndx->in[1][1];
   inb[2][1] = data->trans_ndx->in[2][1];
   inb[0][2] = data->trans_ndx->in[0][2];
   inb[1][2] = data->trans_ndx->in[1][2];
   inb[2][2] = data->trans_ndx->in[2][2];
   ublka  = ndxin->ublk;
   ublkb  = data->trans_ndx->ublk;
   meshgen_setlogical(transform->logical,&i1,&i2,&i3);
   data2 = MALLOT(MeshGen_t, 1);
   meshgen_init(data2);
   data->len    = (abs(ina[i1][1] - ina[i1][0]) + 1) / abs(ina[i1][2]); 
   data2->len   = (abs(inb[i1][1] - inb[i1][0]) + 1) / abs(inb[i1][2]); 
   if ((data->len != data2->len) && (data2->len != 1)) {
      mkpalab(name,"trans",ublkb,inb,data->trans_ndx->rank,0,"");
      sprintf(msg,"Logical limits in %s command do not match.",name);
      ctlerror(me,msg);
   }
   if (data->trans_ndx->rank > 1) {
      lena    = (abs(ina[i2][1] - ina[i2][0]) + 1) / abs(ina[i2][2]); 
      lenb    = (abs(inb[i2][1] - inb[i2][0]) + 1) / abs(inb[i2][2]); 
      if (lena != lenb) {
         mkpalab(name,"trans",ublkb,inb,data->trans_ndx->rank,0,"");
         sprintf(msg,"Logical limits in %s command do not match.",name);
         ctlerror(me,msg);
      }
   }
   if (data->trans_ndx->rank > 2) {
      lena    = (abs(ina[i3][1] - ina[i3][0]) + 1) / abs(ina[i3][2]); 
      lenb    = (abs(inb[i3][1] - inb[i3][0]) + 1) / abs(inb[i3][2]); 
      if (lena != lenb) {
         mkpalab(name,"trans",ublkb,inb,data->trans_ndx->rank,0,"");
         sprintf(msg,"Logical limits in %s command do not match.",name);
         ctlerror(me,msg);
      }
   }
   data2->x    = ALLOT(double, 6*data->len);
   data2->y    = data2->x    + data->len;
   data2->z    = data2->y    + data->len;
   data2->mask = data2->z    + data->len;
   data2->r    = data2->mask + data->len;
   data2->t    = data2->r    + data->len;
   ipa[0] = 1;
   ipa[1] = umap[ublka].jp;
   ipa[2] = umap[ublka].kp;
   ipb[0] = 1;
   ipb[1] = umap[ublkb].jp;
   ipb[2] = umap[ublkb].kp;
   data->x    = ALLOT(double, 6*data->len);
   data->y    = data->x    + data->len;
   data->z    = data->y    + data->len;
   data->mask = data->z    + data->len;
   data->r    = data->mask + data->len;
   data->t    = data->r    + data->len;
   if (ndims == 2) {
      j2 = inb[i2][0];
      for (j = ina[i2][0]; j <= ina[i2][1]; j += ina[i2][2]) {
         if (ifcom) {
            id1 = ipb[i1] * inb[i1][0] + ipb[i2] * j2;
            id2 = ipb[i1] * inb[i1][1] + ipb[i2] * j2;
            id3 = ipb[i1] * inb[i1][2];
            meshgen_pack(data2, data->len, ublkb, id1, id2, id3,1);
         } else {		 
	    ic = 0;
            for (i = inb[i1][0]; i <= inb[i1][1]; i += inb[i1][2]) {
               ip = ipb[i1] * i + ipb[i2] * j2;
	       if (coordinate_type == MESHGEN_COORDS) {
	          data2->x[ic] = domains[ublkb].x[ip];
	          data2->y[ic] = domains[ublkb].y[ip];
	       } else {
	          data2->x[ic] = domains[ublkb].xdot[ip];
	          data2->y[ic] = domains[ublkb].ydot[ip];
	       } 
	       ic++;
	    }
         } 
	 if (data2->len != data->len) {
	    for (i = 1; i < data->len; i++) {
	       data2->x[i] = data2->x[0];
	       data2->y[i] = data2->y[0];
	    }
	 }
         ifrt = meshgen_setptr(data->label, data, &p[0], &p[1], &p[2]);
         ifrt = meshgen_setptr(data->label, data2, &q[0], &q[1], &q[2]);
         if (ifrt) {
            Transform_xyz2rt(data2->x, data2->y, data2->z, data2->r, data2->t, 
	                      data2->len, NULL);
         }
         if (ifcom) {
            id1 = ipa[i1] * ina[i1][0] + ipa[i2] * j;
            id2 = ipa[i1] * ina[i1][1] + ipa[i2] * j;
            id3 = ipa[i1] * ina[i1][2];
            meshgen_pack(data, data->len, ublka, id1, id2, id3,1);
	 } else {
	    ic = 0;
            for (i = ina[i1][0]; i <= ina[i1][1]; i += ina[i1][2]) {
               ip = ipa[i1] * i + ipa[i2] * j;
	       if (coordinate_type == MESHGEN_COORDS) {
	          data->x[ic] = domains[ublka].x[ip];
	          data->y[ic] = domains[ublka].y[ip];
	       } else {
	          data->x[ic] = domains[ublka].xdot[ip];
	          data->y[ic] = domains[ublka].ydot[ip];
	       } 
	       ic++;
	    }
	 }
	 ic = 0;
         for (i = ina[i1][0]; i <= ina[i1][1]; i += ina[i1][2]) {
	    for (n = 0; n < data->ncoord; n++) {
	       p[n][ic] = q[n][ic];
	    }
	    ic++;
	 }
         if (ifrt) {
            Transform_rt2xyz(data->x, data->y, data->z, data->r, data->t, 
	                   data->len, NULL);
         }
         if (ifcom) {
            id1 = ipa[i1] * ina[i1][0] + ipa[i2] * j;
            id2 = ipa[i1] * ina[i1][1] + ipa[i2] * j;
            id3 = ipa[i1] * ina[i1][2];
            meshgen_unpack(data, ublka, id1, id2, id3);
	 } else {
	    ic = 0;
            for (i = ina[i1][0]; i <= ina[i1][1]; i += ina[i1][2]) {
               ip = ipa[i1] * i + ipa[i2] * j;
	       if (coordinate_type == MESHGEN_COORDS) {
	          domains[ublka].x[ip] = data->x[ic];
	          domains[ublka].y[ip] = data->y[ic];
	          domains[ublka].node[ip] = 1;
	       } else {
	          domains[ublka].xdot[ip] = data->x[ic];
	          domains[ublka].ydot[ip] = data->y[ic];
	       } 
	       ic++;
	    }
	 }
        j2 += inb[i2][2];
      }
   } else {
      k2 = inb[i3][0];
      for (k = ina[i3][0]; k <= ina[i3][1]; k += ina[i3][2]) {
         j2 = inb[i2][0];
         for (j = ina[i2][0]; j <= ina[i2][1]; j += ina[i2][2]) {
	    if (ifcom) {
               id1 = ipb[i1] * inb[i1][0] + ipb[i2] * j2 + ipb[i3] * k2;
               id2 = ipb[i1] * inb[i1][1] + ipb[i2] * j2 + ipb[i3] * k2;
               id3 = ipb[i1] * inb[i1][2];
               meshgen_pack(data2, data->len, ublkb, id1, id2, id3,1);
            } else {		 
	       ic = 0;
               for (i = inb[i1][0]; i <= inb[i1][1]; i += inb[i1][2]) {
                  ip = ipb[i1] * i + ipb[i2] * j2 + ipb[i3] * k2;
	          if (coordinate_type == MESHGEN_COORDS) {
	             data2->x[ic] = domains[ublkb].x[ip];
	             data2->y[ic] = domains[ublkb].y[ip];
	             data2->z[ic] = domains[ublkb].z[ip];
	          } else {
	             data2->x[ic] = domains[ublkb].xdot[ip];
	             data2->y[ic] = domains[ublkb].ydot[ip];
	             data2->z[ic] = domains[ublkb].zdot[ip];
	          } 
	          ic++;
	       }
	    }
	    if (data2->len != data->len) {
	       for (i = 1; i < data->len; i++) {
	          data2->x[i] = data2->x[0];
	          data2->y[i] = data2->y[0];
	          data2->z[i] = data2->z[0];
	       }
	    }
            ifrt = meshgen_setptr(data->label, data, &p[0], &p[1], &p[2]);
            ifrt = meshgen_setptr(data->label, data2, &q[0], &q[1], &q[2]);
            if (ifrt) {
               Transform_xyz2rt(data2->x, data2->y, data2->z, data2->r, data2->t, 
	                         data2->len, NULL);
            }
            if (ifcom) {
               id1 = ipa[i1] * ina[i1][0] + ipa[i2] * j + ipa[i3] * k;
               id2 = ipa[i1] * ina[i1][1] + ipa[i2] * j + ipa[i3] * k;
               id3 = ipa[i1] * ina[i1][2];
               meshgen_unpack(data, ublka, id1, id2, id3);
	    } else {
	       ic = 0;
               for (i = ina[i1][0]; i <= ina[i1][1]; i += ina[i1][2]) {
                  ip = ipa[i1] * i + ipa[i2] * j + ipa[i3] * k;
	          if (coordinate_type == MESHGEN_COORDS) {
	             data->x[ic] = domains[ublka].x[ip];
	             data->y[ic] = domains[ublka].y[ip];
	             data->z[ic] = domains[ublka].z[ip];
	          } else {
	             data->x[ic] = domains[ublka].xdot[ip];
	             data->y[ic] = domains[ublka].ydot[ip];
	             data->z[ic] = domains[ublka].zdot[ip];
	          } 
	          ic++;
	       }
	    }
	    ic = 0;
            for (i = ina[i1][0]; i <= ina[i1][1]; i += ina[i1][2]) {
	       for (n = 0; n < data->ncoord; n++) {
	          p[n][ic] = q[n][ic];
	       }
	       ic++;
	    }
            if (ifrt) {
               Transform_rt2xyz(data->x, data->y, data->z, data->r, data->t, 
	                      data->len, NULL);
            }
            if (ifcom) {
               id1 = ipa[i1] * ina[i1][0] + ipa[i2] * j + ipa[i3] * k;
               id2 = ipa[i1] * ina[i1][1] + ipa[i2] * j + ipa[i3] * k;
               id3 = ipa[i1] * ina[i1][2];
               meshgen_unpack(data, ublka, id1, id2, id3);
            } else {
	       ic = 0;
               for (i = ina[i1][0]; i <= ina[i1][1]; i += ina[i1][2]) {
                  ip = ipa[i1] * i + ipa[i2] * j + ipa[i3] * k;
	          if (coordinate_type == MESHGEN_COORDS) {
	             domains[ublka].x[ip] = data->x[ic];
	             domains[ublka].y[ip] = data->y[ic];
	             domains[ublka].z[ip] = data->z[ic];
	             domains[ublka].node[ip] = 1;
	          } else {
	             domains[ublka].xdot[ip] = data->x[ic];
	             domains[ublka].ydot[ip] = data->y[ic];
	             domains[ublka].zdot[ip] = data->z[ic];
	          } 
	          ic++;
	       }
	    }
            j2 += inb[i2][2];
         }
         k2 += inb[i3][2];
      } 
   } 
   NodeWindow_freendx(ndxin);
   NodeWindow_free(data->trans_ndx);
   FREEMEM(data->x);
   FREEMEM(data2->x);
   FREEMEM(data2);
}
static void meshgen_spline(MeshGen_t *data, MeshGenTransform_t *transform) {
   char *me = "meshgen_spline";
   char msg[MAXLINE];
   int i;
   int ifrt;
   int ifindvar;
   double cfact;
   double ind;
   double dep;
   double *p1, *p2, *p3;
   double *pind;
   ifindvar = 0;
   if (data->spline.indvar[0] != '\0') {
     ifindvar = 1;
     ifrt = meshgen_setptr(data->spline.indvar, data, &pind, &p2, &p3);
   }
   ifrt = meshgen_setptr(data->label, data, &p1, &p2, &p3);
   if ((ifrt) || (!strcmp(data->spline.indvar,"r")) || (!strcmp(data->spline.indvar,"t"))) {
      Transform_xyz2rt(data->x, data->y, data->z, data->r, data->t, 
                     data->len, NULL);
   }
   if (data->ncoord == 1) {
      ind = data->spline.ind[0];
      if (ifindvar) ind = pind[0];
      spline_eval(ind,&dep,data->spline.ptr);
      if (data->ifdel) {
         p1[0] += dep;
      } else {
         p1[0] = dep;
      }
      if (data->ifdel) {
         for (i = 1; i < data->len - 1; i++) {
            ind = data->spline.ind[0];
            if (ifindvar) ind = pind[i];
            spline_eval(ind,&dep,data->spline.ptr);
            p1[i] += dep;
         } 
      } else {
	 if (ifindvar == 0) {
            cfact = (data->spline.ind[1] - data->spline.ind[0]) /
                    (ratiosum(transform->ratio, data->len) + ptiny);
	 } else {
            cfact = 0;
	 }
         for (i = 1; i < data->len - 1; i++) {
            ind += cfact;
            if (ifindvar) ind = pind[i];
            spline_eval(ind,&dep,data->spline.ptr);
            p1[i] = dep;
            cfact = cfact * transform->ratio;
         }
      }
      ind = data->spline.ind[1];
      if (ifindvar) ind = pind[data->len - 1];
      spline_eval(ind,&dep,data->spline.ptr);
      if (data->ifdel) {
         p1[data->len - 1] += dep;
      } else {
         p1[data->len - 1] = dep;
      }
   } else if (data->ncoord == 2) {
      if (!strcmp(data->label,"rt")) {
         sprintf(msg,"Only x, y, or z coordinates may be filled in pairs.");
         ctlerror(me,msg);
      }
      if (ifindvar == 0) {
         cfact = (data->spline.ind[1] - data->spline.ind[0]) /
                    (ratiosum(transform->ratio, data->len) + ptiny);
      } else {
         cfact = 0;
      } 
      ind = data->spline.ind[0];
      if (ifindvar) ind = pind[0];
      ind = data->spline.ind[0];
      if (ifindvar) ind = pind[0];
      spline_getxy(&p1[0], &p2[0], 1, ind, ind, 0, 0, data->spline.ptr);
      for (i = 1; i < data->len - 1; i++) {
         ind += cfact;
         if (ifindvar) ind = pind[i];
         spline_getxy(&p1[i], &p2[i], 1, ind, ind, 0, 0, data->spline.ptr);
         cfact = cfact * transform->ratio;
      }
      ind = data->spline.ind[1];
      if (ifindvar) ind = pind[data->len - 1];
      spline_getxy(&p1[data->len - 1], &p2[data->len - 1], 1, ind, 
                     ind, 0, 0, data->spline.ptr);
   } 
   if (ifrt) {
      Transform_rt2xyz(data->x, data->y, data->z, data->r, data->t, 
              data->len, NULL);
   }
}
static void meshgen_pack(MeshGen_t *data, int len, int ublk, int id1, int id2, int id3,
                   int reduce) {
   int i1,i2,i3;
   int i,j,k;
   int id,ip;
   int n;
   int iblk, gblk;
   int count;
   i1 = MIN(id1,id2);
   i2 = MAX(id1,id2);
   i3 = abs(id3);
   for (i = 0; i < len; i++) {
      data->mask[i] = 0.;
      data->x[i] = 0;
      data->y[i] = 0;
   }
   if (ndims == 3) {
      for (i = 0; i < len; i++) {
         data->z[i] = 0;
      }
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      gblk = domains[iblk].gblk;
      if (gmap[gblk].ublk != ublk) continue;
      if (ndims == 2) {
         count = 0;
	 id = id1;
         for (n = i1; n <= i2; n += i3) {
            NDXEXT2D(id,i,j,umap[ublk]);
	    if ((i >= gmap[gblk].imin) && (i <= gmap[gblk].imax) &&
	        (j >= gmap[gblk].jmin) && (j <= gmap[gblk].jmax)) {
	        i = i - gmap[gblk].imin + NPNL;
	        j = j - gmap[gblk].jmin + NPNL;
	        ip = i + j * domains[iblk].jp;
	        if (coordinate_type == MESHGEN_COORDS) {
	           data->x[count]     = domains[iblk].x[ip];
	           data->y[count]     = domains[iblk].y[ip];
	        } else {
	           data->x[count]     = domains[iblk].xdot[ip];
	           data->y[count]     = domains[iblk].ydot[ip];
	        } 
	        data->mask[count] = 1.0;
	    }
	    count++;
	    id += id3;
         }
      } else {
         count = 0;
	 id = id1;
         for (n = i1; n <= i2; n += i3) {
            NDXEXT3D(id,i,j,k,umap[ublk]);
	    if ((i >= gmap[gblk].imin) && (i <= gmap[gblk].imax) &&
	        (j >= gmap[gblk].jmin) && (j <= gmap[gblk].jmax) &&
	        (k >= gmap[gblk].kmin) && (k <= gmap[gblk].kmax)) {
	        i = i - gmap[gblk].imin + NPNL;
	        j = j - gmap[gblk].jmin + NPNL;
	        k = k - gmap[gblk].kmin + NPNL;
	        ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
	        if (coordinate_type == MESHGEN_COORDS) {
	           data->x[count]     = domains[iblk].x[ip];
	           data->y[count]     = domains[iblk].y[ip];
	           data->z[count]     = domains[iblk].z[ip];
	        } else {
	           data->x[count]     = domains[iblk].xdot[ip];
	           data->y[count]     = domains[iblk].ydot[ip];
	           data->z[count]     = domains[iblk].zdot[ip];
	        } 
	        data->mask[count] = 1.0;
	    }
	    id += id3;
	    count++;
         }
      }
   }
   if ((ifparallel) && (reduce)) {
      comreduce(data->x, 4*len, COM_SUM, COM_ALL, COM_DOUBLE);	 
      if (ndims == 2) {
         for (i = 0; i < len; i++) {
            if (data->mask[i] > 0.5) {
               data->x[i] = data->x[i] / data->mask[i];
               data->y[i] = data->y[i] / data->mask[i];
            }
         }
      } else {
         for (i = 0; i < len; i++) {
            if (data->mask[i] > 0.5) {
               data->x[i] = data->x[i] / data->mask[i];
               data->y[i] = data->y[i] / data->mask[i];
               data->z[i] = data->z[i] / data->mask[i];
            }
         }
      } 
   }
   if (data->between == 1) {
      double mx, my, mz;
      for (i = 0; i < len; i++) {
         if (data->mask[i] > 0.5) break;
      }
      if (i < len) {
         mx = data->x[i];
         my = data->y[i];
         if (ndims == 3) mz = data->z[i];
         for (i = 0; i < len; i++) {
            data->x[i] = mx;
            data->y[i] = my;
            if (ndims == 3) data->z[i] = mz;
         }
      } else {
         data->notlocal = 1;
      } 
   }
   return;
}

static void meshgen_unpack(MeshGen_t *data, int ublk, int id1, int id2, int id3) {
   int i1,i2,i3;
   int i,j,k;
   int id,ip;
   int n;
   int iblk, gblk;
   int count;
   i1 = MIN(id1,id2);
   i2 = MAX(id1,id2);
   i3 = abs(id3);
   for (iblk = 0; iblk < nblk; iblk++) {
      gblk = domains[iblk].gblk;
      if (gmap[gblk].ublk != ublk) continue;
      if (ndims == 2) {
         count = 0;
         id = id1;
         for (n = i1; n <= i2; n += i3) {
            NDXEXT2D(id,i,j,umap[ublk]);
            if ((i >= gmap[gblk].imin) && (i <= gmap[gblk].imax) &&
	        (j >= gmap[gblk].jmin) && (j <= gmap[gblk].jmax)) {
	        i = i - gmap[gblk].imin + NPNL;
	        j = j - gmap[gblk].jmin + NPNL;
	        ip = i + j * domains[iblk].jp;
	        if (coordinate_type == MESHGEN_COORDS) {
	           domains[iblk].x[ip]    = data->x[count];
	           domains[iblk].y[ip]    = data->y[count];
	           domains[iblk].node[ip] = 1;
	        } else {
	           domains[iblk].xdot[ip] = data->x[count];
	           domains[iblk].ydot[ip] = data->y[count];
	        } 
	    }
	    count++;
	    id += id3;
         }
      } else {
         count = 0;
	 id = id1;
         for (n = i1; n <= i2; n += i3) {
            NDXEXT3D(id,i,j,k,umap[ublk]);
	    if ((i >= gmap[gblk].imin) && (i <= gmap[gblk].imax) &&
	        (j >= gmap[gblk].jmin) && (j <= gmap[gblk].jmax) &&
	        (k >= gmap[gblk].kmin) && (k <= gmap[gblk].kmax)) {
	        i = i - gmap[gblk].imin + NPNL;
	        j = j - gmap[gblk].jmin + NPNL;
	        k = k - gmap[gblk].kmin + NPNL;
	        ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
	        if (coordinate_type == MESHGEN_COORDS) {
	           domains[iblk].x[ip]    = data->x[count];
	           domains[iblk].y[ip]    = data->y[count];
	           domains[iblk].z[ip]    = data->z[count];
	           domains[iblk].node[ip] = 1;
	        } else {
	           domains[iblk].xdot[ip] = data->x[count];
	           domains[iblk].ydot[ip] = data->y[count];
	           domains[iblk].zdot[ip] = data->z[count];
	        } 
	    }
	    id += id3;
	    count++;
         }
      }
   }
   data->notlocal = 0;
}
static void meshgen_func(MeshGen_t *data, MeshGenTransform_t *transform) {
   char msg[MAXLINE];
   int i;
   int ifrt;
   int cflag;
   double val;
   double *p1, *p2, *p3;
   ifrt = meshgen_setptr(data->label, data, &p1, &p2, &p3);
   if (ifrt) {
      Transform_xyz2rt(data->x, data->y, data->z, data->r, data->t, 
                     data->len, NULL);
   }
   ps = NULL;
   symflag = 0;
   for (i = 0; i < data->len; i++) {
      sprintf(msg,"%.14g",data->x[i]);
      gpdef0(0,"meshx",msg);
      sprintf(msg,"%.14g",data->y[i]);
      gpdef0(0,"meshy",msg);
      sprintf(msg,"%.14g",data->z[i]);
      gpdef0(0,"meshz",msg);
      sprintf(msg,"%.14g",data->r[i]);
      gpdef0(0,"meshr",msg);
      sprintf(msg,"%.14g",data->t[i]);
      gpdef0(0,"mesht",msg);
      line = data->func;
      ps   = line;
      if (data->ifdel) {
         p1[i] += getf(&cflag);
      } else if (data->scaleflag) {
         val = getf(&cflag);
         p1[i] *= val; 
      } else {
         p1[i] = getf(&cflag);
      } 
   }
   symflag = 0;
   line = lnbuf;
   ps   = line;
   if (ifrt) {
      Transform_rt2xyz(data->x, data->y, data->z, data->r, data->t, 
              data->len, NULL);
   }
}
static void meshgen_pnts(MeshGen_t *data, MeshGenTransform_t *transform) {
   char msg[MAXLINE];
   int i,j,k;
   int ifrt;
   int n;
   double  f1, f2;
   double *p1, *p2, *p3;
   ifrt = meshgen_setptr(data->label, data, &p1, &p2, &p3);
   if (ifrt) {
      Transform_xyz2rt(data->x, data->y, data->z, data->r, data->t, 
                     data->len, NULL);
   }
   if (data->ncoord == 1) {
      k = 0;
      j = 0;
      n = (data->len - 1) / (data->npoints - 1);
      for (i = 0; i < data->len - 1; i++) {
         f2 = (double)k / (double)(n);
         f1 = 1. - f2;
         if (data->ifdel) {
            p1[i] += f1 * data->points[j] + f2 * data->points[j+1];
         } else {
            p1[i]  = f1 * data->points[j] + f2 * data->points[j+1];
         } 
         k++;
         if (k == n) {
            k = 0;
            j = j + 1;
         }
      }
      if (data->ifdel) {
         p1[i] += data->points[j];
      } else {
         p1[i]  = data->points[j];
      } 
   } else if (data->ncoord == 2) {
      k = 0;
      j = 0;
      n = (data->len - 1) / ((data->npoints / 2) - 1);
      for (i = 0; i < data->len - 1; i++) {
         f2 = (double)k / (double)(n);
         f1 = 1. - f2;
         if (data->ifdel) {
            p1[i] += f1 * data->points[j]   + f2 * data->points[j+2];
            p2[i] += f1 * data->points[j+1] + f2 * data->points[j+3];
         } else {
            p1[i]  = f1 * data->points[j]   + f2 * data->points[j+2];
            p2[i]  = f1 * data->points[j+1] + f2 * data->points[j+3];
         } 
         k++;
         if (k == n) {
            k = 0;
            j = j + 2;
         }
      }
      if (data->ifdel) {
         p1[i] += data->points[j++];
         p2[i] += data->points[j++];
      } else {
         p1[i]  = data->points[j++];
         p2[i]  = data->points[j++];
      } 
   } else if (data->ncoord == 3) {
      k = 0;
      j = 0;
      n = (data->len - 1) / ((data->npoints / 3) - 1);
      for (i = 0; i < data->len - 1; i++) {
         f2 = (double)k / (double)(n);
         f1 = 1. - f2;
         if (data->ifdel) {
            p1[i] += f1 * data->points[j]   + f2 * data->points[j+3];
            p2[i] += f1 * data->points[j+1] + f2 * data->points[j+4];
            p3[i] += f1 * data->points[j+2] + f2 * data->points[j+5];
         } else {
            p1[i]  = f1 * data->points[j]   + f2 * data->points[j+3];
            p2[i]  = f1 * data->points[j+1] + f2 * data->points[j+4];
            p3[i]  = f1 * data->points[j+2] + f2 * data->points[j+5];
         } 
         k++;
         if (k == n) {
            k = 0;
            j = j + 3;
         }
      }
      if (data->ifdel) {
         p1[i] += data->points[j++];
         p2[i] += data->points[j++];
         p3[i] += data->points[j++];
      } else {
         p1[i]  = data->points[j++];
         p2[i]  = data->points[j++];
         p3[i]  = data->points[j++];
      } 
   } 
   if (ifrt) {
      Transform_rt2xyz(data->x, data->y, data->z, data->r, data->t, 
              data->len, NULL);
   }
}
static void  meshgen_norm(MeshGen_t *data, NodeWindow_t *ndxin) {
   char *me = "meshgen_norm";
   char msg[MAXLINE];
   int i,n;
   int ibnd;
   int iblk;
   int len;
   int type;
   int ifrt;
   int ip[3];
   int *ndx;
   double *normx;
   double *normy;
   double *normz;
   double *p1, *p2, *p3;
   double *n1, *n2, *n3;
   Extents_t ext;
   MeshGen_t *mydata;
   CPYEXT(ext,(*ndxin));
   type = extents_gettype(ext);
   if (type != FACE) {
      sprintf(msg,"Normal offsets can only be done on lines or planes.");
      ctlwarning(me,msg);
      return;
   }
   ifrt  = meshgen_setptr(data->label, data, &p1, &p2, &p3);
   if (ifrt) {
      sprintf(msg,"Normal offsets only work with xyz coordinate specifiers.");
      ctlwarning(me,msg);
      return;
   }
   if (ifcom) swapcoords();
   mydata = MALLOT(MeshGen_t,1);
   meshgen_init(mydata);
   for (iblk = 0; iblk < nblk; iblk++) {
      len = NodeWindow_fastndx(ndxin, domains[iblk].gblk, NDX_REAL, NDX_NODAL);
      if (len == 0) continue;
      for (ibnd = 0; ibnd < domains[iblk].nbnd; ibnd++) {
         len = COM_LEN_ALLN_R(domains[iblk].bnd[ibnd]);
         ndx = COM_NDX_ALLN_R(domains[iblk].bnd[ibnd]);
         for (i = 0; i < len; i++) {
            domains[iblk].node[ndx[i]] = 1;
         }
      }
      n = 0;
      if (ext.imin != ext.imax) ip[n++] = 1;
      if (ext.jmin != ext.jmax) ip[n++] = domains[iblk].jp;
      if (ext.kmin != ext.kmax) ip[n++] = domains[iblk].kp;
      normx = MALLOT(double, len);
      normy = MALLOT(double, len);
      normz = MALLOT(double, len);
      ndx = ndxin->ndx;
      data->x = domains[iblk].x;
      data->y = domains[iblk].y;
      data->z = domains[iblk].z;
      mydata->x = normx;
      mydata->y = normy;
      mydata->z = normz;
      ifrt  = meshgen_setptr(data->label, data, &p1, &p2, &p3);
      ifrt += meshgen_setptr(data->label, mydata, &n1, &n2, &n3);
      if (ndims == 2) {
         for (i = 0; i < len; i++) {
             int    nodem, nodep;
             int    jp,jm,j0;
             double dx, xp, x0, xm;
             double dy, yp, y0, ym;
	     double nx, ny;
	     double denom, norm;
             nodep = domains[iblk].node[ndx[i] + ip[0]];
             nodem = domains[iblk].node[ndx[i] - ip[0]];
	     jp = ndx[i] + ip[0];
	     j0 = ndx[i];
	     jm = ndx[i] - ip[0];
	     if (nodep == 0) {
	        jp = ndx[i];
	        j0 = ndx[i] - ip[0];
	        jm = ndx[i] - 2*ip[0];
	     } else if (nodem == 0) {
	        jp = ndx[i] + 2*ip[0];
	        j0 = ndx[i] + ip[0];
	        jm = ndx[i];
	     } 
             xp = domains[iblk].x[jp];
             x0 = domains[iblk].x[j0];
             xm = domains[iblk].x[jm];
             yp = domains[iblk].y[jp];
             y0 = domains[iblk].y[jm];
             ym = domains[iblk].y[j0];
             dx = (xm + xp - 2 * x0)*(nodem - nodep) + 0.5 * (xp - xm);
             dy = (ym + yp - 2 * y0)*(nodem - nodep) + 0.5 * (yp - ym);
	     if (fabs(dx) < xcut) dx = 0;
	     if (fabs(dy) < xcut) dy = 0;
	     norm = 1.0 / sqrt (dx * dx + dy * dy + ptiny);
             nx = -dy*norm;
             ny =  dx*norm;
	     normx[i] = nx;
	     normy[i] = ny;
         }
      } else {
         for (i = 0; i < len; i++) {
         }
      }
      if (data->ncoord == 1) {
         for (i = 0; i < len; i++) {
            p1[ndx[i]] += n1[i] * data->coord[0];
         }
      } else if (data->ncoord == 2) {
         for (i = 0; i < len; i++) {
            p1[ndx[i]] += n1[i] * data->coord[0];
            p2[ndx[i]] += n2[i] * data->coord[0];
         }
      } else if (data->ncoord == 3) {
         for (i = 0; i < len; i++) {
            p1[ndx[i]] += n1[i] * data->coord[0];
            p2[ndx[i]] += n2[i] * data->coord[0];
            p3[ndx[i]] += n3[i] * data->coord[0];
         }
      } 
      FREEMEM(normx);
      FREEMEM(normy);
      FREEMEM(normz);
      NodeWindow_freendx(ndxin);
      for (ibnd = 0; ibnd < domains[iblk].nbnd; ibnd++) {
         len = COM_LEN_ALLN_R(domains[iblk].bnd[ibnd]);
         ndx = COM_NDX_ALLN_R(domains[iblk].bnd[ibnd]);
         for (i = 0; i < len; i++) {
            domains[iblk].node[ndx[i]] = 0;
         }
      }
   }
   FREEMEM(mydata);
}

static void meshgen_sphereSection(MeshGen_t *data, 
                                  MeshGenTransform_t *transform, 
                                  NodeWindow_t *ndxin) {
   int ip, i,j,k;
   int ublk;
   int iblk;
   int len;
   int deli, delj, delk;
   int offi, offj, offk;
   double mag;
   double s, t, x, y, z;
   MeshGenSphericalSection_t *sps = &data->sphereSection;
   Extents_t ext, uext, gext, ext3;
   ublk = ndxin->ublk;
   uext.imin = MIN(ndxin->in[0][0], ndxin->in[0][1]);
   uext.jmin = MIN(ndxin->in[1][0], ndxin->in[1][1]);
   uext.kmin = MIN(ndxin->in[2][0], ndxin->in[2][1]);
   uext.imax = MAX(ndxin->in[0][0], ndxin->in[0][1]);
   uext.jmax = MAX(ndxin->in[1][0], ndxin->in[1][1]);
   uext.kmax = MAX(ndxin->in[2][0], ndxin->in[2][1]);
   deli = uext.imax - uext.imin;
   delj = uext.jmax - uext.jmin;
   delk = uext.kmax - uext.kmin;
   if (deli == 0) deli = 1;
   if (delj == 0) delj = 1;
   if (delk == 0) delk = 1;
   for (iblk = 0; iblk < nblk; iblk++) {
      int gblk = domains[iblk].gblk;
      if (gmap[gblk].ublk != ublk) continue;
      CPYEXT(gext,gmap[gblk]);
      len = extents_overlap(&uext, &gext, &ext3);
      if (len > 0) {
         TRSEXT(ext, ext3, gext);
         if (ndims == 2) {
            offi = uext.imin - umap[ublk].imin + gmap[gblk].imin - NPNL;
            offj = uext.jmin - umap[ublk].jmin + gmap[gblk].jmin - NPNL;
            for (j = ext.jmin; j <= ext.jmax; j++) {
               for (i = ext.imin; i <= ext.imax; i++) {
                  ip = i + j * domains[iblk].jp;
                  if (transform->logical == 0) {
                     s = ((double)(j - ext.jmin + offj)) / 
                         ((double) (delj));
                  } else if (transform->logical == 1) {
                     s = ((double)(i - ext.imin + offi)) / 
                          ((double) (deli));
                  } 
                  meshgen_sphereSection_getxyz(data, s, t, &x, &y, &z);
                  domains[iblk].x[ip] =  x;
                  domains[iblk].y[ip] =  y;
                  domains[iblk].node[ip] =  1;
               }
            }
         } else {
            offi = uext.imin - umap[ublk].imin + gmap[gblk].imin - NPNL;
            offj = uext.jmin - umap[ublk].jmin + gmap[gblk].jmin - NPNL;
            offk = uext.kmin - umap[ublk].kmin + gmap[gblk].kmin - NPNL;
            for (k = ext.kmin; k <= ext.kmax; k++) {
               for (j = ext.jmin; j <= ext.jmax; j++) {
                  for (i = ext.imin; i <= ext.imax; i++) {
                     ip = i + j * domains[iblk].jp + k * domains[iblk].kp;
                     if (transform->logical == 0) {
                        s = ((double)(j - ext.jmin + offj)) / 
                            ((double) (delj));
                        t = ((double)(k - ext.kmin + offk)) / 
                            ((double) (delk));
                     } else if (transform->logical == 1) {
                        s = ((double)(i - ext.imin + offi)) / 
                            ((double) (deli));
                        t = ((double)(k - ext.kmin + offk)) / 
                            ((double) (delk));
                     } else if (transform->logical == 2) {
                        s = ((double)(i - ext.imin + offi)) / 
                            ((double) (deli));
                        t = ((double)(j - ext.jmin + offj)) / 
                            ((double) (delj));
                     } 
                     meshgen_sphereSection_getxyz(data, s, t, &x, &y, &z);
                     domains[iblk].x[ip] =  x;
                     domains[iblk].y[ip] =  y;
                     domains[iblk].z[ip] =  z;
                     domains[iblk].node[ip] =  1;
                  }
               }
            }
         } 
      }
   }
}
static void meshgen_sphereSection_getxyz(MeshGen_t *data, double s, double t, 
                                  double *mx, double *my, double *mz) {
   double mag;
   double sign, dot;
   double x, y, z;
   double v12[3];
   double v23[3];
   double v34[3];
   double v41[3];
   double vc1[3];
   double vc2[3];
   MeshGenSphericalSection_t *sps = &data->sphereSection;
   if (ndims == 2) {
      if (data->type == MESHGEN_SPHERE_SEC) {
         x = sps->v1[0] * sin(sps->t12 * (1 - s)) +
             sps->v2[0] * sin(sps->t12 *  s);
         y = sps->v1[1] * sin(sps->t12 * (1 - s)) +
             sps->v2[1] * sin(sps->t12 *  s);
         mag = sqrt ( x * x + y * y) + ptiny;
         x =  (x * sps->rad * sps->insin12) / mag;
         y =  (y * sps->rad * sps->insin12) / mag;
      }  else  {
         x = (1 - s) * sps->v1[0] + (  s  ) * sps->v2[0];
         y = (1 - s) * sps->v1[1] + (  s  ) * sps->v2[1];
      } 
   } else {
      if (data->type == MESHGEN_SPHERE_SEC) {
         v12[0] = sps->insin12 * (sin(sps->t12 * (1 - s)) * sps->v1[0] +
                                  sin(sps->t12 * s)       * sps->v2[0]);
         v12[1] = sps->insin12 * (sin(sps->t12 * (1 - s)) * sps->v1[1] +
                                  sin(sps->t12 * s)       * sps->v2[1]);
         v12[2] = sps->insin12 * (sin(sps->t12 * (1 - s)) * sps->v1[2] +
                                  sin(sps->t12 * s)       * sps->v2[2]);
         if (fabs(sps->t12) < 1e-10) {
            v12[0] = sps->v1[0];
            v12[1] = sps->v1[1];
            v12[2] = sps->v1[1];
         }
         v23[0] = sps->insin23 * (sin(sps->t23 * (1 - t)) * sps->v2[0] +
                                  sin(sps->t23 * t)       * sps->v3[0]);
         v23[1] = sps->insin23 * (sin(sps->t23 * (1 - t)) * sps->v2[1] +
                                  sin(sps->t23 * t)       * sps->v3[1]);
         v23[2] = sps->insin23 * (sin(sps->t23 * (1 - t)) * sps->v2[2] +
                                  sin(sps->t23 * t)       * sps->v3[2]);
         if (fabs(sps->t23) < 1e-10) {
            v23[0] = sps->v2[0];
            v23[1] = sps->v2[1];
            v23[2] = sps->v2[1];
         }
         v34[0] = sps->insin34 * (sin(sps->t34 * (1 - s)) * sps->v4[0] +
                                  sin(sps->t34 * s)       * sps->v3[0]);
         v34[1] = sps->insin34 * (sin(sps->t34 * (1 - s)) * sps->v4[1] +
                                  sin(sps->t34 * s)       * sps->v3[1]);
         v34[2] = sps->insin34 * (sin(sps->t34 * (1 - s)) * sps->v4[2] +
                                  sin(sps->t34 * s)       * sps->v3[2]);
         if (fabs(sps->t34) < 1e-10) {
            v34[0] = sps->v3[0];
            v34[1] = sps->v3[1];
            v34[2] = sps->v3[1];
         }
         v41[0] = sps->insin41 * (sin(sps->t41 * (1 - t)) * sps->v1[0] +
                                  sin(sps->t41 * t)       * sps->v4[0]);
         v41[1] = sps->insin41 * (sin(sps->t41 * (1 - t)) * sps->v1[1] +
                                  sin(sps->t41 * t)       * sps->v4[1]);
         v41[2] = sps->insin41 * (sin(sps->t41 * (1 - t)) * sps->v1[2] +
                                  sin(sps->t41 * t)       * sps->v4[2]);
         if (fabs(sps->t41) < 1e-10) {
            v41[0] = sps->v1[0];
            v41[1] = sps->v1[1];
            v41[2] = sps->v1[1];
         }
         CROSSPROD(vc1[0], vc1[1], vc1[2], 
                   v12[0], v12[1], v12[2], 
                   v34[0], v34[1], v34[2]);
         CROSSPROD(vc2[0], vc2[1], vc2[2], 
                   v23[0], v23[1], v23[2], 
                   v41[0], v41[1], v41[2]);
         CROSSPROD(x     , y     , z     , 
                   vc1[0], vc1[1], vc1[2], 
                   vc2[0], vc2[1], vc2[2]);
         dot = x * sps->vave[0] + y * sps->vave[1] + z * sps->vave[2];
         sign = 1;
         if (dot < 0) sign = -1;
         mag = sqrt ( x * x + y * y + z * z) + ptiny;
         mag = sign * sps->rad / mag;
         x =  mag * x;
         y =  mag * y;
         z =  mag * z;
      } else if (data->type == MESHGEN_CYL) {
         x = sps->insin12 * (sin(sps->t12 * (1 - s)) * sps->v1[0] +
                             sin(sps->t12 * s)       * sps->v2[0]);
         y = sps->insin12 * (sin(sps->t12 * (1 - s)) * sps->v1[1] +
                             sin(sps->t12 * s)       * sps->v2[1]);
         z = sps->insin12 * (sin(sps->t12 * (1 - s)) * sps->v1[2] +
                             sin(sps->t12 * s)       * sps->v2[2]);
         mag = sqrt ( x * x + y * y + z * z) + ptiny;
         mag = sps->rad / mag;
         x =  mag * x;
         y =  mag * y;
         z =  mag * z;
      } else {
         x = (1 - s)*(1 - t) * sps->v1[0] + 
             (  s  )*(1 - t) * sps->v2[0] + 
             (  s  )*(  t  ) * sps->v3[0] + 
             (1 - s)*(  t  ) * sps->v4[0];
         y = (1 - s)*(1 - t) * sps->v1[1] + 
             (  s  )*(1 - t) * sps->v2[1] + 
             (  s  )*(  t  ) * sps->v3[1] + 
             (1 - s)*(  t  ) * sps->v4[1];
         z = (1 - s)*(1 - t) * sps->v1[2] + 
             (  s  )*(1 - t) * sps->v2[2] + 
             (  s  )*(  t  ) * sps->v3[2] + 
             (1 - s)*(  t  ) * sps->v4[2];
      } 
   } 
   *mx = x;
   *my = y;
   *mz = z;
}
static void meshgen_fillbetween(MeshGen_t *data, MeshGenTransform_t *transform) {
   int len_save;
   int ncoord_save;
   int deli, delj, delk;
   int i;
   double s, t;
   double x, y, z;
   MeshGen_t *data1, *data2;
   data1 =  data;
   data2 = &data[1];
   if (data->notlocal == 1) return;
   len_save = data->len;
   data->len = 1;
   if (data1->type == MESHGEN_SPLINE) {
      ncoord_save = data1->ncoord;
      data1->ncoord = 2;
      if (!strcmp(data1->spline.indvar,"t")) {
         strcpy(data1->label,"r");
         data1->ncoord = 1;
      } else if (!strcmp(data1->spline.indvar,"x")) {
         strcpy(data1->label,"y");
         data1->ncoord = 1;
      } else if (!strcmp(data1->spline.indvar,"y")) {
         strcpy(data1->label,"x");
         data1->ncoord = 1;
      }
      meshgen_spline(data1, transform) ;
      data1->ncoord = ncoord_save;
   } else if ((data1->type == MESHGEN_SPHERE_SEC) ||
              (data1->type == MESHGEN_CYL)        ||
              (data1->type == MESHGEN_PLANE)  ) {
      deli = data1->ext.imax - data1->ext.imin;
      delj = data1->ext.jmax - data1->ext.jmin;
      delk = data1->ext.kmax - data1->ext.kmin;
      if (deli == 0) deli = 1;
      if (delj == 0) delj = 1;
      if (delk == 0) delk = 1;
      if (transform->logical == 0) {
         s = ((double)(data1->i1 - data1->ext.jmin)) / 
              ((double) (delj));
         t = ((double)(data1->i2 - data1->ext.kmin)) / 
                            ((double) (delk));
      } else if (transform->logical == 1) {
         s = ((double)(data1->i1 - data1->ext.imin)) / 
                            ((double) (deli));
         t = ((double)(data1->i2 - data1->ext.kmin)) / 
                            ((double) (delk));
      } else if (transform->logical == 2) {
         s = ((double)(data1->i1 - data1->ext.imin)) / 
                            ((double) (deli));
         t = ((double)(data1->i2 - data1->ext.jmin)) / 
                            ((double) (delj));
      } 
      meshgen_sphereSection_getxyz(data1, s, t, &x, &y, &z);
      data1->x[0] = x;
      data1->y[0] = y;
      if (ndims == 3) data1->z[0] = z;
   } else if (data1->type == MESHGEN_FUNC) {
      meshgen_func(data1,transform) ;
   } else if (data1->type == MESHGEN_TABLE) {
   } 
   data->len =  len_save;
   data2->x = &data1->x[data1->len - 1];
   data2->y = &data1->y[data1->len - 1];
   data2->z = &data1->z[data1->len - 1];
   data2->r = &data1->r[data1->len - 1];
   data2->t = &data1->t[data1->len - 1];
   data2->len = 1;
   if (data2->type == MESHGEN_SPLINE) {
      ncoord_save = data2->ncoord;
      data2->ncoord = 2;
      if (!strcmp(data2->spline.indvar,"t")) {
         strcpy(data2->label,"r");
         data2->ncoord = 1;
      } else if (!strcmp(data2->spline.indvar,"x")) {
         strcpy(data2->label,"y");
         data2->ncoord = 1;
      } else if (!strcmp(data2->spline.indvar,"y")) {
         strcpy(data2->label,"x");
         data2->ncoord = 1;
      }
      meshgen_spline(data2, transform) ;
      data2->ncoord = ncoord_save;
   } else if ((data2->type == MESHGEN_SPHERE_SEC) ||
              (data2->type == MESHGEN_CYL)        || 
              (data2->type == MESHGEN_PLANE)  ) {
      deli = data1->ext.imax - data1->ext.imin;
      delj = data1->ext.jmax - data1->ext.jmin;
      delk = data1->ext.kmax - data1->ext.kmin;
      if (deli == 0) deli = 1;
      if (delj == 0) delj = 1;
      if (delk == 0) delk = 1;
      if (transform->logical == 0) {
         s = ((double)(data1->i1 - data1->ext.jmin)) / 
              ((double) (delj));
         t = ((double)(data1->i2 - data1->ext.kmin)) / 
                            ((double) (delk));
      } else if (transform->logical == 1) {
         s = ((double)(data1->i1 - data1->ext.imin)) / 
                            ((double) (deli));
         t = ((double)(data1->i2 - data1->ext.kmin)) / 
                            ((double) (delk));
      } else if (transform->logical == 2) {
         s = ((double)(data1->i1 - data1->ext.imin)) / 
                            ((double) (deli));
         t = ((double)(data1->i2 - data1->ext.jmin)) / 
                            ((double) (delj));
      } 
      meshgen_sphereSection_getxyz(data2, s, t, &x, &y, &z);
      data2->x[0] = x;
      data2->y[0] = y;
      if (ndims == 3) data2->z[0] = z;
   } else if (data2->type == MESHGEN_FUNC) {
      meshgen_func(data2,transform) ;
   } else if (data2->type == MESHGEN_TABLE) {
 ;    } 
   i = 0;
   data1->coord[i++] = data1->x[0];
   data1->coord[i++] = data1->y[0];
   if (ndims == 3) data1->coord[i++] = data1->z[0];
   data1->coord[i++] = data1->x[data1->len - 1];
   data1->coord[i++] = data1->y[data1->len - 1];
   if (ndims == 3) data1->coord[i++] = data1->z[data1->len - 1];
   ncoord_save = data1->ncoord;
   data1->ncoord = ndims;
   if (ndims == 2) strcpy(data1->label,"xy");
   if (ndims == 3) strcpy(data1->label,"xyz");
   meshgen_fillends( data1, transform) ;
   data1->ncoord = ncoord_save;
}
static void  meshgen_sphereSection_init(MeshGenSphericalSection_t *sps) {
   double norm;
   double dot;
   if (ndims == 2) { 
      norm = sqrt (sps->v1[0] * sps->v1[0] +
                   sps->v1[1] * sps->v1[1] ) +
                   ptiny;
      sps->v1[0] = sps->v1[0] / norm;
      sps->v1[1] = sps->v1[1] / norm;
      norm = sqrt (sps->v2[0] * sps->v2[0] +
                   sps->v2[1] * sps->v2[1] ) +
                   ptiny;
      sps->v2[0] = sps->v2[0] / norm;
      sps->v2[1] = sps->v2[1] / norm;
      dot = sps->v1[0] * sps->v2[0] + sps->v1[1] * sps->v2[1];
      sps->t12 = acos(dot);
      sps->insin12 = 1 / ( sin(sps->t12) + ptiny);
   } else {
      norm = sqrt (sps->v1[0] * sps->v1[0] +
                   sps->v1[1] * sps->v1[1] +
                   sps->v1[2] * sps->v1[2] ) +
		   ptiny;
      sps->v1[0] = sps->v1[0] / norm;
      sps->v1[1] = sps->v1[1] / norm;
      sps->v1[2] = sps->v1[2] / norm;
      norm = sqrt (sps->v2[0] * sps->v2[0] +
                   sps->v2[1] * sps->v2[1] +
                   sps->v2[2] * sps->v2[2] ) +
		   ptiny;
      sps->v2[0] = sps->v2[0] / norm;
      sps->v2[1] = sps->v2[1] / norm;
      sps->v2[2] = sps->v2[2] / norm;
      norm = sqrt (sps->v3[0] * sps->v3[0] +
                   sps->v3[1] * sps->v3[1] +
                   sps->v3[2] * sps->v3[2] ) +
		   ptiny;
      sps->v3[0] = sps->v3[0] / norm;
      sps->v3[1] = sps->v3[1] / norm;
      sps->v3[2] = sps->v3[2] / norm;
      norm = sqrt (sps->v4[0] * sps->v4[0] +
                   sps->v4[1] * sps->v4[1] +
                   sps->v4[2] * sps->v4[2] ) +
		   ptiny;
      sps->v4[0] = sps->v4[0] / norm;
      sps->v4[1] = sps->v4[1] / norm;
      sps->v4[2] = sps->v4[2] / norm;
      dot = sps->v1[0] * sps->v2[0] + 
            sps->v1[1] * sps->v2[1] +
            sps->v1[2] * sps->v2[2];
      sps->t12 = acos(dot);
      sps->insin12 = 1 / ( sin(sps->t12) + ptiny);
      dot = sps->v2[0] * sps->v3[0] + 
            sps->v2[1] * sps->v3[1] +
            sps->v2[2] * sps->v3[2];
      sps->t23 = acos(dot);
      sps->insin23 = 1 / ( sin(sps->t23) + ptiny);
      dot = sps->v3[0] * sps->v4[0] + 
            sps->v3[1] * sps->v4[1] +
            sps->v3[2] * sps->v4[2];
      sps->t34 = acos(dot);
      sps->insin34 = 1 / ( sin(sps->t34) + ptiny);
      dot = sps->v4[0] * sps->v1[0] + 
            sps->v4[1] * sps->v1[1] +
            sps->v4[2] * sps->v1[2];
      sps->t41 = acos(dot);
      sps->insin41 = 1 / ( sin(sps->t41) + ptiny);
      sps->vave[0] = 0.25 * (sps->v1[0] + sps->v2[0] +
                             sps->v3[0] + sps->v4[0]);
      sps->vave[1] = 0.25 * (sps->v1[1] + sps->v2[1] +
                             sps->v3[1] + sps->v4[1]);
      sps->vave[2] = 0.25 * (sps->v1[2] + sps->v2[2] +
                             sps->v3[2] + sps->v4[2]);
   }
}
static void meshgen_bc(int *ondx, int *offset, double *nx, double *ny,
                double *nz, int *olen, int mode, Domain_t *domain) {
   int ibnd;
   int i, j, k;
   int inp,inm;
   int *ndx;
   int *node = domain->node;
   int len;
   double dx, dy, dz;
   double norm;
   double dot;
   double *x = domain->x;
   double *y = domain->y;
   double *z = domain->z;
   for (ibnd = 0; ibnd < domain->nbnd; ibnd++) {
      len = COM_LEN_2NC_R(domain->bnd[ibnd]);
      ndx = COM_NDX_2NC_R(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         node[ndx[i]] = 2;
      }
   }
   ndx = ondx;
   len = 0;
   if ((ndims == 2) && (mode == 0)) {
      for (j = domain->jmin - 1; j <= domain->jmax + 1; j++) {
         for (i = domain->imin - 1; i <= domain->imax + 1; i++) {
            int ip = i + domain->jp * j;
            if (((i < domain->imin) || (i > domain->imax)) ||
                ((j < domain->jmin) || (j > domain->jmax))) {
               if (node[ip] == 0) {
                  int offi = 0;
                  int offj = 0;
                  ndx[len] = ip;
                  if (i < domain->imin) {
                     if (node[ip + 1] >= 1) offi = 1;
                  }
                  if (i > domain->imax) {
                     if (node[ip - 1] >= 1) offi = -1;
                  }
                  if (j < domain->jmin) {
                     if (node[ip + domain->jp] >= 1) offj = domain->jp;
                  }
                  if (j > domain->jmax) {
                     if (node[ip - domain->jp] >= 1) offj = -domain->jp;
                  }
                  if ((offi != 0)  && (offj != 0)) {
                     if ((node[ip + offi] == 2) && (node[ip + offj] == 2)) {
                        offi = 0;
                        offj = 0;
                     } 
                  } 
                  offset[len] = offi + offj;
                  len++;
               }
            }
         }
      }
   } else if ((ndims == 3) && (mode == 0)) {
      for (k = domain->kmin - 1; k <= domain->kmax + 1; k++) {
         for (j = domain->jmin - 1; j <= domain->jmax + 1; j++) {
            for (i = domain->imin - 1; i <= domain->imax + 1; i++) {
               int ip = i + domain->jp * j + domain->kp * k;
               if (((i < domain->imin) || (i > domain->imax)) ||
                   ((j < domain->jmin) || (j > domain->jmax)) ||
                   ((k < domain->kmin) || (k > domain->kmax))) {
                  if (node[ip] == 0) {
                     int offi = 0;
                     int offj = 0;
                     int offk = 0;
                     ndx[len] = ip;
                     if (i < domain->imin) {
                        if (node[ip + 1] >= 1) offi = 1;
                     }
                     if (i > domain->imax) {
                        if (node[ip - 1] >= 1) offi = -1;
                     }
                     if (j < domain->jmin) {
                        if (node[ip + domain->jp] >= 1) offj = domain->jp;
                     }
                     if (j > domain->jmax) {
                        if (node[ip - domain->jp] >= 1) offj = -domain->jp;
                     }
                     if (k < domain->kmin) {
                        if (node[ip + domain->kp] >= 1) offk = domain->kp;
                     }
                     if (k > domain->kmax) {
                        if (node[ip - domain->kp] >= 1) offk = -domain->kp;
                     }
                     if ((offi != 0)  && (offj != 0) && (offk == 0)) {
                        if ((node[ip + offi] == 2) && (node[ip + offj] == 2)) {
                           offi = 0;
                           offj = 0;
                        }
                     }
                     if ((offi != 0)  && (offj == 0) && (offk != 0)) {
                        if ((node[ip + offi] == 2) && (node[ip + offk] == 2)) {
                           offi = 0;
                           offk = 0;
                        }
                     }
                     if ((offi == 0)  && (offj != 0) && (offk != 0)) {
                        if ((node[ip + offj] == 2) && (node[ip + offk] == 2)) {
                           offj = 0;
                           offk = 0;
                        }
                     }
                     if ((offi != 0)  && (offj != 0) && (offk != 0)) {
                        if ((node[ip + offi] == 2) && (node[ip + offj] == 2) &&
                            (node[ip + offk] == 2)) {
                           offi = 0;
                           offj = 0;
                           offk = 0;
                        }
                     }
                     offset[len] = offi + offj + offk;
                     len++;
                  }
               }
            }
         }
      }
   } 
   if (mode == 0) *olen = len;
   if (mode == 1) len   = *olen;
   if (ndims == 2) {
      for (i = 0; i < len; i++) {
         int ip = ndx[i] ;
         int ic = ndx[i] + offset[i];
         int im = ndx[i] + 2 * offset[i];
	 if ((node[im] != 2) && (abs(offset[i]) == 1)) {
            inp =  ic + domain->jp;
            inm =  ic - domain->jp;
            if ((mode == 0) && ((node[inm] == 0) || (node[inp] == 0)))  {
               dx =  0.;
               dy =  0.;
            } else {
               dx =  (y[inp] - y[inm]);
               dy =  (x[inm] - x[inp]);
            } 
	 } else if ((node[im] != 2) && (abs(offset[i]) == domain->jp)) {
            inp =  ic + 1;
            inm =  ic - 1;
            if ((mode == 0) && ((node[inm] == 0) || (node[inp] == 0)))  {
               dx =  0.;
               dy =  0.;
            } else {
               dx =  (y[inp] - y[inm]);
               dy =  (x[inm] - x[inp]);
            } 
	 } else {
            int im = ndx[i] + 2 * offset[i];
            dx = (x[ic] - x[im]);
            dy = (y[ic] - y[im]);
	 } 
         norm = sqrt(dx * dx + dy * dy);
         nx[i] = dx / (norm + ptiny);
         ny[i] = dy / (norm + ptiny);
      }
   } else {
      for (i = 0; i < len; i++) {
         int ip = ndx[i];
         int ic = ndx[i] + offset[i];
         int im = ndx[i] + 2 * offset[i];
	 if ((node[im] != 2) && (abs(offset[i]) == 1)) {
            double dx1 = x[ic + domain->jp] - x[ic - domain->jp];
            double dy1 = y[ic + domain->jp] - y[ic - domain->jp];
            double dz1 = z[ic + domain->jp] - z[ic - domain->jp];
            double dx2 = x[ic + domain->kp] - x[ic - domain->kp];
            double dy2 = y[ic + domain->kp] - y[ic - domain->kp];
            double dz2 = z[ic + domain->kp] - z[ic - domain->kp];
            inm = ic - domain->jp;
            inp = ic + domain->jp;
            if ((mode == 0) && ((node[inm] == 0) || (node[inp] == 0)))  {
               dx1 = 0;
               dy1 = 0;
               dz1 = 0;
            }
            inm = ic - domain->kp;
            inp = ic + domain->kp;
            if ((mode == 0) && ((node[inm] == 0) || (node[inp] == 0)))  {
               dx2 = 0;
               dy2 = 0;
               dz2 = 0;
            }
            dx = dy1 * dz2 - dz1 * dy2;
            dy = dx2 * dz1 - dx1 * dz2;
            dz = dx1 * dy2 - dx2 * dy1;
	 } else if ((node[im] != 2) && (abs(offset[i]) == domain->jp)) {
            double dx1 = x[ic + 1         ] - x[ic - 1         ];
            double dy1 = y[ic + 1         ] - y[ic - 1         ];
            double dz1 = z[ic + 1         ] - z[ic - 1         ];
            double dx2 = x[ic + domain->kp] - x[ic - domain->kp];
            double dy2 = y[ic + domain->kp] - y[ic - domain->kp];
            double dz2 = z[ic + domain->kp] - z[ic - domain->kp];
            inm = ic - 1;
            inp = ic + 1;
            if ((mode == 0) && ((node[inm] == 0) || (node[inp] == 0)))  {
               dx1 = 0;
               dy1 = 0;
               dz1 = 0;
            }
            inm = ic - domain->kp;
            inp = ic + domain->kp;
            if ((mode == 0) && ((node[inm] == 0) || (node[inp] == 0)))  {
               dx2 = 0;
               dy2 = 0;
               dz2 = 0;
            }
            dx = dy1 * dz2 - dz1 * dy2;
            dy = dx2 * dz1 - dx1 * dz2;
            dz = dx1 * dy2 - dx2 * dy1;
	 } else if ((node[im] != 2) && (abs(offset[i]) == domain->kp)) {
            double dx1 = x[ic + 1         ] - x[ic - 1         ];
            double dy1 = y[ic + 1         ] - y[ic - 1         ];
            double dz1 = z[ic + 1         ] - z[ic - 1         ];
            double dx2 = x[ic + domain->jp] - x[ic - domain->jp];
            double dy2 = y[ic + domain->jp] - y[ic - domain->jp];
            double dz2 = z[ic + domain->jp] - z[ic - domain->jp];
            inm = ic - 1;
            inp = ic + 1;
            if ((mode == 0) && ((node[inm] == 0) || (node[inp] == 0)))  {
               dx1 = 0;
               dy1 = 0;
               dz1 = 0;
            }
            inm = ic - domain->jp;
            inp = ic + domain->jp;
            if ((mode == 0) && ((node[inm] == 0) || (node[inp] == 0)))  {
               dx2 = 0;
               dy2 = 0;
               dz2 = 0;
            }
            dx = dy1 * dz2 - dz1 * dy2;
            dy = dx2 * dz1 - dx1 * dz2;
            dz = dx1 * dy2 - dx2 * dy1;
         } else {
            dx = (x[ic] - x[im]);
            dy = (y[ic] - y[im]);
            dz = (z[ic] - z[im]);
         }
         norm = sqrt(dx * dx + dy * dy + dz * dz);
         nx[i] = dx / (norm + ptiny);
         ny[i] = dy / (norm + ptiny);
         nz[i] = dz / (norm + ptiny);
      }
   }
   for (ibnd = 0; ibnd < domain->nbnd; ibnd++) {
      len = COM_LEN_2NC_R(domain->bnd[ibnd]);
      ndx = COM_NDX_2NC_R(domain->bnd[ibnd]);
      for (i = 0; i < len; i++) {
         node[ndx[i]] = 0;
      }
   }
}
static void meshgen_applybc(int *ndx, int *offset, double *nx, double *ny,
                     double *nz, int len, Domain_t *domain) {
   int i;
   double dx, dy, dz;
   double dot;
   double *x = domain->x;
   double *y = domain->y;
   double *z = domain->z;
   double *delx = domain->delx;
   double *dely = domain->dely;
   double *delz = domain->delz;
   if (ndims == 2) {
      for (i = 0; i < len; i++) {
         int ip = ndx[i];
         int ic = ndx[i] + offset[i];
         int im = ndx[i] + 2 * offset[i];
         dx = (x[ic] - x[im]);
         dy = (y[ic] - y[im]);
         dot = 2 * (nx[i] * dx + ny[i] * dy);
         x[ip] = x[ic] + dx - dot * nx[i];
         y[ip] = y[ic] + dy - dot * ny[i];
         dot = nx[i] * delx[ic] + ny[i] * dely[ic];
         delx[ic] = delx[ic] - dot * nx[i];
         dely[ic] = dely[ic] - dot * ny[i];
      }
   } else {
      for (i = 0; i < len; i++) {
         int ip = ndx[i];
         int ic = ndx[i] + offset[i];
         int im = ndx[i] + 2 * offset[i];
         dx = (x[ic] - x[im]);
         dy = (y[ic] - y[im]);
         dz = (z[ic] - z[im]);
         dot = 2 * (nx[i] * dx + ny[i] * dy + nz[i] * dz);
         x[ip] = x[ic] + dx - dot * nx[i];
         y[ip] = y[ic] + dy - dot * ny[i];
         z[ip] = z[ic] + dz - dot * nz[i];
         dot = nx[i] * delx[ic] + ny[i] * dely[ic] + nz[i] * delz[ic];
         delx[ic] = delx[ic] - dot * nx[i];
         dely[ic] = dely[ic] - dot * ny[i];
         delz[ic] = delz[ic] - dot * nz[i];
      }
   }
}
static int meshgen_packsurfs(NodeWindow_t *ndxin, MeshGenPackSurf_t **lfin) {
   int is, ip, id;
   int len;
   int iblk, gblk;
   int ns;
   int len1, len2, len3;
   int ii, jj, kk;
   int i, j, k;
   MeshGenPackSurf_t *lf;
   Extents_t exts[27];
   Extents_t ext, gext;
   Extents_t ext1, ext2;
   CPYEXT(ext,(*ndxin));
   if (ndims == 2) {
      SETEXT(exts[0],ext.imin,ext.imin,ext.jmin,ext.jmax,ext.kmin,ext.kmin);
      SETEXT(exts[1],ext.imax,ext.imax,ext.jmin,ext.jmax,ext.kmin,ext.kmin);
      SETEXT(exts[2],ext.imin,ext.imax,ext.jmin,ext.jmin,ext.kmin,ext.kmin);
      SETEXT(exts[3],ext.imin,ext.imax,ext.jmax,ext.jmax,ext.kmin,ext.kmin);      
      ns = 4;
   } else {
      SETEXT(exts[0],ext.imin,ext.imin,ext.jmin,ext.jmax,ext.kmin,ext.kmax);
      SETEXT(exts[1],ext.imax,ext.imax,ext.jmin,ext.jmax,ext.kmin,ext.kmax);
      SETEXT(exts[2],ext.imin,ext.imax,ext.jmin,ext.jmin,ext.kmin,ext.kmax);
      SETEXT(exts[3],ext.imin,ext.imax,ext.jmax,ext.jmax,ext.kmin,ext.kmax);
      SETEXT(exts[4],ext.imin,ext.imax,ext.jmin,ext.jmax,ext.kmin,ext.kmin);
      SETEXT(exts[5],ext.imin,ext.imax,ext.jmin,ext.jmax,ext.kmax,ext.kmax);      
      ns = 6;
   } 
   lf = MALLOT(MeshGenPackSurf_t, ns);
   for (is = 0; is < ns; is++) {
      len = LENEXT(exts[is]);
      CPYEXT(lf[is].ext, exts[is]);
      lf[is].x = MALLOT(double, len * 4);
      lf[is].y = lf[is].x + len;
      lf[is].z = lf[is].y + len;
      lf[is].m = lf[is].z + len;
      lf[is].len = len;
      for (i = 0; i < len; i++) {
         lf[is].x[i] = 0.;
         lf[is].y[i] = 0.;
         lf[is].z[i] = 0.;
         lf[is].m[i] = 0.;
      }
      len1 = exts[is].imax - exts[is].imin;
      len2 = exts[is].jmax - exts[is].jmin;
      len3 = exts[is].kmax - exts[is].kmin;
      if (len1 == 0) lf[is].ip = 0;
      if (len2 == 0) lf[is].jp = 0;
      if (len3 == 0) lf[is].kp = 0;
      if (ndims == 2) {
         if (len1 > 0) lf[is].ip = 1;
         if (len2 > 0) lf[is].jp = 1;
      } else {
         if ((len1 > 0) && (len2 > 0)) {
            lf[is].ip = 1;
            lf[is].jp = len1 + 1;
         } else if ((len1 > 0) && (len3 > 0)) {
            lf[is].ip = 1;
            lf[is].kp = len1 + 1;
         } else if ((len2 > 0) && (len3 > 0)) {
            lf[is].jp = 1;
            lf[is].kp = len2 + 1;
         } else if (len1 > 0) {
            lf[is].ip = 1;
         } else if (len2 > 0) {
            lf[is].jp = 1;
         } else if (len3 > 0) {
            lf[is].kp = 1;
         }
      } 
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      gblk = domains[iblk].gblk;
      if (gmap[gblk].ublk != ndxin->ublk) continue;
      CPYEXT(gext, gmap[gblk]);
      for (is = 0; is < ns; is++) {
         len = extents_overlap(&exts[is], &gext, &ext1);
         TRSEXT(ext2, ext1, gext);
         if (ndims == 3) {
            for (k = ext1.kmin; k <= ext1.kmax; k++) {
               for (j = ext1.jmin; j <= ext1.jmax; j++) {
                  for (i = ext1.imin; i <= ext1.imax; i++) {
                     ii = i - exts[is].imin;
                     jj = j - exts[is].jmin;
                     kk = k - exts[is].kmin;
                     id = ii * lf[is].ip + jj * lf[is].jp + kk * lf[is].kp;
                     ii = i - gext.imin + NPNL;
                     jj = j - gext.jmin + NPNL;
                     kk = k - gext.kmin + NPNL;
                     ip = ii + jj * domains[iblk].jp + kk * domains[iblk].kp;
                     if (coordinate_type == MESHGEN_COORDS) { 
                        lf[is].x[id] += domains[iblk].x[ip];
                        lf[is].y[id] += domains[iblk].y[ip];
                        lf[is].z[id] += domains[iblk].z[ip];
                     } else {
                        lf[is].x[id] += domains[iblk].xdot[ip];
                        lf[is].y[id] += domains[iblk].ydot[ip];
                        lf[is].z[id] += domains[iblk].zdot[ip];
                     } 
                     lf[is].m[id] = lf[is].m[id] + 1.0; 
                  }
               }
            }
         } else {
            for (j = ext1.jmin; j <= ext1.jmax; j++) {
               for (i = ext1.imin; i <= ext1.imax; i++) {
                  ii = i - exts[is].imin;
                  jj = j - exts[is].jmin;
                  id = ii * lf[is].ip + jj * lf[is].jp;
                  ii = i - gext.imin + NPNL;
                  jj = j - gext.jmin + NPNL;
                  ip = ii + jj * domains[iblk].jp; 
                  if (coordinate_type == MESHGEN_COORDS) { 
                     lf[is].x[id] += domains[iblk].x[ip];
                     lf[is].y[id] += domains[iblk].y[ip];
                  } else {
                     lf[is].x[id] += domains[iblk].xdot[ip];
                     lf[is].y[id] += domains[iblk].ydot[ip];
                  } 
                  lf[is].m[id] = lf[is].m[id] + 1.0; 
               }
            }
         } 
      }
   }
   if (ifparallel) {
      for (is = 0; is < ns; is++) {
         comreduce(lf[is].x, 4 * lf[is].len, COM_SUM, COM_ALL, COM_DOUBLE);
      }
   }
   for (is = 0; is < ns; is++) {
      for (i = 0; i < lf[is].len; i++) {
         if (lf[is].m[i] > 0.5) {
            lf[is].x[i] = lf[is].x[i] / lf[is].m[i];
            lf[is].y[i] = lf[is].y[i] / lf[is].m[i];
            if (ndims == 3) lf[is].z[i] = lf[is].z[i] / lf[is].m[i];
         }
      }
   }
   *lfin = lf;
   return(ns);
}
static void meshgen_freesurfs(MeshGenPackSurf_t **lfin, int ns) {
   int is;
   MeshGenPackSurf_t *lf;
   lf = *lfin;
   for (is = 0; is < ns; is++) {
      FREEMEM(lf[is].x);
   }
   FREEMEM(lf);
}
void meshgen_linearfill(int logical, NodeWindow_t *ndxin) {
   int i, j, k;
   int ii, jj, kk;
   int ip;
   int iblk, gblk;
   int ns;
   int len;
   int ipim, ipip, ipjm, ipjp, ipkm, ipkp;
   int ipim_jm, ipim_jp, ipim_km, ipim_kp;
   int ipip_jm, ipip_jp, ipip_km, ipip_kp;
   int ipjm_km, ipjm_kp, ipjp_km, ipjp_kp;
   double di, dj, dk;
   double xn, yn, zn;
   double u, v, w;
   double ifac, jfac, kfac;
   double ijfac, jkfac, ikfac;
   double ijkfac;
   double xc[8];
   double yc[8];
   double zc[8];
   MeshGenPackSurf_t *lf = NULL;
   Extents_t ext, gext, ext1, extm;
   ns = meshgen_packsurfs(ndxin, &lf) ;
   if (ns == 0) return;
   CPYEXT(ext, (*ndxin));
   CPYEXT(extm, (*ndxin));
   extm.imin = 0;
   extm.jmin = 0;
   extm.kmin = 0;
   extm.imax = ext.imax - ext.imin;
   extm.jmax = ext.jmax - ext.jmin;
   extm.kmax = ext.kmax - ext.kmin;
   ifac = 1.;
   jfac = 1.;
   kfac = 1.;
   if (ndims == 2) {            
      if (logical == 0) jfac = 0;
      if (logical == 1) ifac = 0;
      di = (double)(extm.imax);
      dj = (double)(extm.jmax);
      if (extm.imax == 0) {
         di = 0.;
      } else {
         di = 1 / di;
      } 
      if (extm.jmax == 0) {
         dj = 0.;
      } else {
         dj = 1 / dj;
      } 
      xc[0] = lf[0].x[0];  
      yc[0] = lf[0].y[0];
      xc[1] = lf[1].x[0];  
      yc[1] = lf[1].y[0];
      ip = extm.imax * lf[0].ip + extm.jmax * lf[0].jp;
      xc[2] = lf[0].x[ip];  
      yc[2] = lf[0].y[ip];
      ip = extm.imax * lf[1].ip + extm.jmax * lf[1].jp;
      xc[3] = lf[1].x[ip];  
      yc[3] = lf[1].y[ip];
   } else {
      if (logical == 0) {
         jfac = 0;
         kfac = 0;
      }
      if (logical == 1) {
         ifac = 0;
         kfac = 0;
      }
      if (logical == 2) {
         ifac = 0;
         jfac = 0;
      }
      if (logical == 3) kfac = 0;
      if (logical == 4) ifac = 0;
      if (logical == 5) jfac = 0;
      di = (double)(extm.imax);
      dj = (double)(extm.jmax);
      dk = (double)(extm.kmax);
      if (extm.imax == 0) {
         di = 0.;
      } else {
         di = 1 / di;
      } 
      if (extm.jmax == 0) {
         dj = 0.;
      } else {
         dj = 1 / dj;
      } 
      if (extm.kmax == 0) {
         dk = 0.;
      } else {
         dk = 1 / dk;
      } 
      xc[0] = lf[0].x[0];  
      yc[0] = lf[0].y[0];
      zc[0] = lf[0].z[0];
      xc[1] = lf[1].x[0];  
      yc[1] = lf[1].y[0];
      zc[1] = lf[1].z[0];
      ip = extm.jmax * lf[0].jp;
      xc[2] = lf[0].x[ip];  
      yc[2] = lf[0].y[ip];
      zc[2] = lf[0].z[ip];
      ip = extm.jmax * lf[1].jp;
      xc[3] = lf[1].x[ip];  
      yc[3] = lf[1].y[ip];
      zc[3] = lf[1].z[ip];
      ip = extm.kmax * lf[0].kp;
      xc[4] = lf[0].x[ip];  
      yc[4] = lf[0].y[ip];
      zc[4] = lf[0].z[ip];
      ip = extm.kmax * lf[1].kp;
      xc[5] = lf[1].x[ip];  
      yc[5] = lf[1].y[ip];
      zc[5] = lf[1].z[ip];
      ip = extm.jmax * lf[0].jp + extm.kmax * lf[0].kp;
      xc[6] = lf[0].x[ip];  
      yc[6] = lf[0].y[ip];
      zc[6] = lf[0].z[ip];
      ip = extm.jmax * lf[1].jp + extm.kmax * lf[1].kp;
      xc[7] = lf[1].x[ip];  
      yc[7] = lf[1].y[ip];
      zc[7] = lf[1].z[ip];
   }
   ijfac = ifac * jfac;
   jkfac = jfac * kfac;
   ikfac = ifac * kfac;
   ijkfac = ijfac * kfac;
   for (iblk = 0; iblk < nblk ; iblk++) {
      gblk = domains[iblk].gblk;
      if (gmap[gblk].ublk != ndxin->ublk) continue;
      CPYEXT(gext, gmap[gblk]);
      len = extents_overlap(&ext, &gext, &ext1);
      if (len > 0) {
         if (ndims == 3) {
            for (k = ext1.kmin; k <= ext1.kmax; k++) {
               for (j = ext1.jmin; j <= ext1.jmax; j++) {
                  for (i = ext1.imin; i <= ext1.imax; i++) {
                     ii = i - ext.imin;
                     jj = j - ext.jmin;
                     kk = k - ext.kmin;
                     ipim    = ii * lf[0].ip + jj * lf[0].jp + kk * lf[0].kp;
                     ipim_jm =  extm.jmin * lf[0].jp +        kk * lf[0].kp;
                     ipim_jp =  extm.jmax * lf[0].jp +        kk * lf[0].kp;
                     ipim_km =         jj * lf[0].jp + extm.kmin * lf[0].kp;
                     ipim_kp =         jj * lf[0].jp + extm.kmax * lf[0].kp;
                     ipip    = ii * lf[1].ip + jj * lf[1].jp + kk * lf[1].kp;
                     ipip_jm =  extm.jmin * lf[1].jp +        kk * lf[1].kp;
                     ipip_jp =  extm.jmax * lf[1].jp +        kk * lf[1].kp;
                     ipip_km =         jj * lf[1].jp + extm.kmin * lf[1].kp;
                     ipip_kp =         jj * lf[1].jp + extm.kmax * lf[1].kp;
                     ipjm    = ii * lf[2].ip + jj * lf[2].jp + kk * lf[2].kp;
                     ipjm_km =         ii * lf[2].ip + extm.kmin * lf[2].kp;
                     ipjm_kp =         ii * lf[2].ip + extm.kmax * lf[2].kp;
                     ipjp    = ii * lf[3].ip + jj * lf[3].jp + kk * lf[3].kp;
                     ipjp_km =         ii * lf[3].ip + extm.kmin * lf[3].kp;
                     ipjp_kp =         ii * lf[3].ip + extm.kmax * lf[3].kp;
                     ipkm    = ii * lf[4].ip + jj * lf[4].jp + kk * lf[4].kp;
                     ipkp    = ii * lf[5].ip + jj * lf[5].jp + kk * lf[5].kp;
                     ii = i - gext.imin + NPNL;
                     jj = j - gext.jmin + NPNL;
                     kk = k - gext.kmin + NPNL;
                     ip = ii + jj * domains[iblk].jp + kk * domains[iblk].kp;
                     u = (i - ext.imin) * di;
                     v = (j - ext.jmin) * dj;
                     w = (k - ext.kmin) * dk;
		     xn =  (1 - u) * (1 - v) * (1 - w) * xc[0] * ijkfac +
		           (  u  ) * (1 - v) * (1 - w) * xc[1] * ijkfac +
		           (1 - u) * (  v  ) * (1 - w) * xc[2] * ijkfac +
		           (  u  ) * (  v  ) * (1 - w) * xc[3] * ijkfac +
		           (1 - u) * (1 - v) * (  w  ) * xc[4] * ijkfac +
		           (  u  ) * (1 - v) * (  w  ) * xc[5] * ijkfac +
		           (1 - u) * (  v  ) * (  w  ) * xc[6] * ijkfac +
		           (  u  ) * (  v  ) * (  w  ) * xc[7] * ijkfac +
		          -(1 - u) * (  v  ) *           lf[0].x[ipim_jp] * ijfac +
		          -(1 - u) * (1 - v) *           lf[0].x[ipim_jm] * ijfac +
		          -(  u  ) * (  v  ) *           lf[1].x[ipip_jp] * ijfac +
		          -(  u  ) * (1 - v) *           lf[1].x[ipip_jm] * ijfac +
		          -(1 - u)           * (1 - w) * lf[0].x[ipim_km] * ikfac +
		          -(1 - u)           * (  w  ) * lf[0].x[ipim_kp] * ikfac +
		          -(  u  )           * (1 - w) * lf[1].x[ipip_km] * ikfac +
		          -(  u  )           * (  w  ) * lf[1].x[ipip_kp] * ikfac +
		          -          (1 - v) * (1 - w) * lf[2].x[ipjm_km] * jkfac +
		          -          (1 - v) * (  w  ) * lf[2].x[ipjm_kp] * jkfac +
		          -          (  v  ) * (1 - w) * lf[3].x[ipjp_km] * jkfac +
		          -          (  v  ) * (  w  ) * lf[3].x[ipjp_kp] * jkfac +
		           (1 - u)                     * lf[0].x[ipim] * ifac +
		           (  u  )                     * lf[1].x[ipip] * ifac +
		                     (1 - v)           * lf[2].x[ipjm] * jfac +
		                     (  v  )           * lf[3].x[ipjp] * jfac +
		                               (1 - w) * lf[4].x[ipkm] * kfac +
		                               (  w  ) * lf[5].x[ipkp] * kfac ;
		     yn =  (1 - u) * (1 - v) * (1 - w) * yc[0] * ijkfac +
		           (  u  ) * (1 - v) * (1 - w) * yc[1] * ijkfac +
		           (1 - u) * (  v  ) * (1 - w) * yc[2] * ijkfac +
		           (  u  ) * (  v  ) * (1 - w) * yc[3] * ijkfac +
		           (1 - u) * (1 - v) * (  w  ) * yc[4] * ijkfac +
		           (  u  ) * (1 - v) * (  w  ) * yc[5] * ijkfac +
		           (1 - u) * (  v  ) * (  w  ) * yc[6] * ijkfac +
		           (  u  ) * (  v  ) * (  w  ) * yc[7] * ijkfac +
		          -(1 - u) * (  v  ) *           lf[0].y[ipim_jp] * ijfac +
		          -(1 - u) * (1 - v) *           lf[0].y[ipim_jm] * ijfac +
		          -(  u  ) * (  v  ) *           lf[1].y[ipip_jp] * ijfac +
		          -(  u  ) * (1 - v) *           lf[1].y[ipip_jm] * ijfac +
		          -(1 - u)           * (1 - w) * lf[0].y[ipim_km] * ikfac +
		          -(1 - u)           * (  w  ) * lf[0].y[ipim_kp] * ikfac +
		          -(  u  )           * (1 - w) * lf[1].y[ipip_km] * ikfac +
		          -(  u  )           * (  w  ) * lf[1].y[ipip_kp] * ikfac +
		          -          (1 - v) * (1 - w) * lf[2].y[ipjm_km] * jkfac +
		          -          (1 - v) * (  w  ) * lf[2].y[ipjm_kp] * jkfac +
		          -          (  v  ) * (1 - w) * lf[3].y[ipjp_km] * jkfac +
		          -          (  v  ) * (  w  ) * lf[3].y[ipjp_kp] * jkfac +
		           (1 - u)                     * lf[0].y[ipim] * ifac +
		           (  u  )                     * lf[1].y[ipip] * ifac +
		                     (1 - v)           * lf[2].y[ipjm] * jfac +
		                     (  v  )           * lf[3].y[ipjp] * jfac +
		                               (1 - w) * lf[4].y[ipkm] * kfac +
		                               (  w  ) * lf[5].y[ipkp] * kfac ;
		     zn =  (1 - u) * (1 - v) * (1 - w) * zc[0] * ijkfac +
		           (  u  ) * (1 - v) * (1 - w) * zc[1] * ijkfac +
		           (1 - u) * (  v  ) * (1 - w) * zc[2] * ijkfac +
		           (  u  ) * (  v  ) * (1 - w) * zc[3] * ijkfac +
		           (1 - u) * (1 - v) * (  w  ) * zc[4] * ijkfac +
		           (  u  ) * (1 - v) * (  w  ) * zc[5] * ijkfac +
		           (1 - u) * (  v  ) * (  w  ) * zc[6] * ijkfac +
		           (  u  ) * (  v  ) * (  w  ) * zc[7] * ijkfac +
		          -(1 - u) * (  v  ) *           lf[0].z[ipim_jp] * ijfac +
		          -(1 - u) * (1 - v) *           lf[0].z[ipim_jm] * ijfac +
		          -(  u  ) * (  v  ) *           lf[1].z[ipip_jp] * ijfac +
		          -(  u  ) * (1 - v) *           lf[1].z[ipip_jm] * ijfac +
		          -(1 - u)           * (1 - w) * lf[0].z[ipim_km] * ikfac +
		          -(1 - u)           * (  w  ) * lf[0].z[ipim_kp] * ikfac +
		          -(  u  )           * (1 - w) * lf[1].z[ipip_km] * ikfac +
		          -(  u  )           * (  w  ) * lf[1].z[ipip_kp] * ikfac +
		          -          (1 - v) * (1 - w) * lf[2].z[ipjm_km] * jkfac +
		          -          (1 - v) * (  w  ) * lf[2].z[ipjm_kp] * jkfac +
		          -          (  v  ) * (1 - w) * lf[3].z[ipjp_km] * jkfac +
		          -          (  v  ) * (  w  ) * lf[3].z[ipjp_kp] * jkfac +
		           (1 - u)                     * lf[0].z[ipim] * ifac +
		           (  u  )                     * lf[1].z[ipip] * ifac +
		                     (1 - v)           * lf[2].z[ipjm] * jfac +
		                     (  v  )           * lf[3].z[ipjp] * jfac +
		                               (1 - w) * lf[4].z[ipkm] * kfac +
		                               (  w  ) * lf[5].z[ipkp] * kfac ;
                     if (coordinate_type == MESHGEN_COORDS) { 
		        domains[iblk].x[ip] = xn;
		        domains[iblk].y[ip] = yn;
		        domains[iblk].z[ip] = zn;
 		        domains[iblk].node[ip] = 1;
                     } else {
		        domains[iblk].xdot[ip] = xn;
		        domains[iblk].ydot[ip] = yn;
		        domains[iblk].zdot[ip] = zn;
                     } 
                  }
               }
            }
         } else {
            for (j = ext1.jmin; j <= ext1.jmax; j++) {
               for (i = ext1.imin; i <= ext1.imax; i++) {
                  ii = i - ext.imin;
                  jj = j - ext.jmin;
                  ipim = ii * lf[0].ip + jj * lf[0].jp;
                  ipip = ii * lf[1].ip + jj * lf[1].jp;
                  ipjm = ii * lf[2].ip + jj * lf[2].jp;
                  ipjp = ii * lf[3].ip + jj * lf[3].jp;
                  ii = i - gext.imin + NPNL;
                  jj = j - gext.jmin + NPNL;
                  ip = ii + jj * domains[iblk].jp;
                  u = (i - ext.imin) * di;
                  v = (j - ext.jmin) * dj;
		  xn = -(1 - u) * (1 - v) * xc[0] * ijfac +
		       -(  u  ) * (1 - v) * xc[1] * ijfac +
		       -(1 - u) * (  v  ) * xc[2] * ijfac +
		       -(  u  ) * (  v  ) * xc[3] * ijfac +
		        (1 - u) *           lf[0].x[ipim] * ifac + 
		        (  u  ) *           lf[1].x[ipip] * ifac +
		                  (1 - v) * lf[2].x[ipjm] * jfac +
		                  (  v  ) * lf[3].x[ipjp] * jfac;
		  yn = -(1 - u) * (1 - v) * yc[0] * ijfac +
		       -(  u  ) * (1 - v) * yc[1] * ijfac +
		       -(1 - u) * (  v  ) * yc[2] * ijfac +
		       -(  u  ) * (  v  ) * yc[3] * ijfac +
		        (1 - u) *           lf[0].y[ipim] * ifac + 
		        (  u  ) *           lf[1].y[ipip] * ifac +
		                  (1 - v) * lf[2].y[ipjm] * jfac +
		                  (  v  ) * lf[3].y[ipjp] * jfac;
                  if (coordinate_type == MESHGEN_COORDS) { 
		     domains[iblk].x[ip] = xn;
		     domains[iblk].y[ip] = yn;
		     domains[iblk].node[ip] = 1;
                  } else {
		     domains[iblk].xdot[ip] = xn;
		     domains[iblk].ydot[ip] = yn;
                  } 
               }
            }
         } 
      }
   }
   meshgen_freesurfs(&lf, ns);
}
static void meshgen_transfinite(int logical, NodeWindow_t *ndxin) {
   int i,j,k;
   int ii, jj, kk;  
   int ip, jp, kp;
   int ns;
   int len;
   int offset;
   int iblk, gblk;
   int iter;
   int ipim, ipip, ipjm, ipjp, ipkm, ipkp;
   int ipim_jm, ipim_jp, ipim_km, ipim_kp;
   int ipip_jm, ipip_jp, ipip_km, ipip_kp;
   int ipjm_km, ipjm_kp, ipjp_km, ipjp_kp;
   double ifac, jfac, kfac;
   double ijfac, jkfac, ikfac;
   double ijkfac;
   double xc[8];
   double yc[8];
   double zc[8];
   double r, s, t;
   double err;
   double b11, b12, b13; 
   double b21, b22, b23; 
   double b31, b32, b33; 
   double rp, sp, tp;
   double rm, sm, tm;
   double rp1, rp2, rp3, rp4;
   double sp1, sp2, sp3, sp4;
   double tp1, tp2, tp3, tp4;
   double recip_determ;
   double xn, yn, zn;
   double *r1, *s1, *t1;
   double *r2, *s2, *t2;
   double *r3, *s3, *t3;
   double *r4, *s4, *t4;
   double *x, *y, *z;
   MeshGenPackSurf_t *lf = NULL;
   Extents_t ext, gext, ext1, extm;
   ns = meshgen_packsurfs(ndxin, &lf) ;
   if (ns == 0) return;
   len = ndxin->imax - ndxin->imin + 1;
   r1 = MALLOT(double,len);
   r2 = MALLOT(double,len);
   if (ndims == 3) {
      r3 = MALLOT(double,len);
      r4 = MALLOT(double,len);
   }
   len = ndxin->jmax - ndxin->jmin + 1;
   s1 = MALLOT(double,len);
   s2 = MALLOT(double,len);
   if (ndims == 3) {
      s3 = MALLOT(double,len);
      s4 = MALLOT(double,len);
   }
   if (ndims == 3) {
      len = ndxin->kmax - ndxin->kmin + 1;
      t1 = MALLOT(double,len);
      t2 = MALLOT(double,len);
      t3 = MALLOT(double,len);
      t4 = MALLOT(double,len);
   }
   CPYEXT(ext, (*ndxin));
   CPYEXT(extm, (*ndxin));
   extm.imin = 0;
   extm.jmin = 0;
   extm.kmin = 0;
   extm.imax = ext.imax - ext.imin;
   extm.jmax = ext.jmax - ext.jmin;
   extm.kmax = ext.kmax - ext.kmin;
   ifac = 1;
   jfac = 1;
   kfac = 1;
   if (ndims == 2) {
      meshgen_calcarc(r1, lf[0].x, lf[0].y, lf[0].z, 0, 0, extm.jmax, lf[0].jp);
      meshgen_calcarc(r2, lf[1].x, lf[1].y, lf[1].z, 0, 0, extm.jmax, lf[1].jp);
      meshgen_calcarc(s1, lf[2].x, lf[2].y, lf[2].z, 0, 0, extm.imax, lf[2].ip);
      meshgen_calcarc(s2, lf[3].x, lf[3].y, lf[3].z, 0, 0, extm.imax, lf[3].ip);
      if (logical == 0) jfac = 0;
      if (logical == 1) ifac = 0;
      xc[0] = lf[0].x[0];  
      yc[0] = lf[0].y[0];
      xc[1] = lf[1].x[0];  
      yc[1] = lf[1].y[0];
      ip = extm.imax * lf[0].ip + extm.jmax * lf[0].jp;
      xc[2] = lf[0].x[ip];  
      yc[2] = lf[0].y[ip];
      ip = extm.imax * lf[1].ip + extm.jmax * lf[1].jp;
      xc[3] = lf[1].x[ip];  
      yc[3] = lf[1].y[ip];
   } else {
      offset = 0;
      meshgen_calcarc(s1, lf[0].x, lf[0].y, lf[0].z, offset, 0, extm.jmax, lf[0].jp);
      offset = 0;
      meshgen_calcarc(s2, lf[1].x, lf[1].y, lf[1].z, offset, 0, extm.jmax, lf[1].jp);
      offset = extm.kmax * lf[0].kp;
      meshgen_calcarc(s3, lf[0].x, lf[0].y, lf[0].z, offset, 0, extm.jmax, lf[0].jp);
      offset = extm.kmax * lf[1].kp;
      meshgen_calcarc(s4, lf[1].x, lf[1].y, lf[1].z, offset, 0, extm.jmax, lf[1].jp);
      offset = 0;
      meshgen_calcarc(r1, lf[2].x, lf[2].y, lf[2].z, offset, 0, extm.imax, lf[2].ip);
      offset = 0;
      meshgen_calcarc(r2, lf[3].x, lf[3].y, lf[3].z, offset, 0, extm.imax, lf[3].ip);
      offset = extm.kmax * lf[2].kp;
      meshgen_calcarc(r3, lf[2].x, lf[2].y, lf[2].z, offset, 0, extm.imax, lf[2].ip);
      offset = extm.kmax * lf[3].kp;
      meshgen_calcarc(r4, lf[3].x, lf[3].y, lf[3].z, offset, 0, extm.imax, lf[3].ip);
      offset = 0;
      meshgen_calcarc(t1, lf[0].x, lf[0].y, lf[0].z, offset, 0, extm.kmax, lf[0].kp);
      offset = 0;
      meshgen_calcarc(t2, lf[1].x, lf[1].y, lf[1].z, offset, 0, extm.kmax, lf[1].kp);
      offset = extm.jmax * lf[0].jp;
      meshgen_calcarc(t3, lf[0].x, lf[0].y, lf[0].z, offset, 0, extm.kmax, lf[0].kp);
      offset = extm.jmax * lf[1].jp;
      meshgen_calcarc(t4, lf[1].x, lf[1].y, lf[1].z, offset, 0, extm.kmax, lf[1].kp);
      if (logical == 0) {
         jfac = 0;
         kfac = 0;
      }
      if (logical == 1) {
         ifac = 0;
         kfac = 0;
      }
      if (logical == 2) {
         ifac = 0;
         jfac = 0;
      } 
      if (logical == 3) kfac = 0;
      if (logical == 4) ifac = 0;
      if (logical == 5) jfac = 0;
      xc[0] = lf[0].x[0];  
      yc[0] = lf[0].y[0];
      zc[0] = lf[0].z[0];
      xc[1] = lf[1].x[0];  
      yc[1] = lf[1].y[0];
      zc[1] = lf[1].z[0];
      ip = extm.jmax * lf[0].jp;
      xc[2] = lf[0].x[ip];  
      yc[2] = lf[0].y[ip];
      zc[2] = lf[0].z[ip];
      ip = extm.jmax * lf[1].jp;
      xc[3] = lf[1].x[ip];  
      yc[3] = lf[1].y[ip];
      zc[3] = lf[1].z[ip];
      ip = extm.kmax * lf[0].kp;
      xc[4] = lf[0].x[ip];  
      yc[4] = lf[0].y[ip];
      zc[4] = lf[0].z[ip];
      ip = extm.kmax * lf[1].kp;
      xc[5] = lf[1].x[ip];  
      yc[5] = lf[1].y[ip];
      zc[5] = lf[1].z[ip];
      ip = extm.jmax * lf[0].jp + extm.kmax * lf[0].kp;
      xc[6] = lf[0].x[ip];  
      yc[6] = lf[0].y[ip];
      zc[6] = lf[0].z[ip];
      ip = extm.jmax * lf[1].jp + extm.kmax * lf[1].kp;
      xc[7] = lf[1].x[ip];  
      yc[7] = lf[1].y[ip];
      zc[7] = lf[1].z[ip];
   } 
   ijfac = ifac * jfac;
   jkfac = jfac * kfac;
   ikfac = ifac * kfac;
   ijkfac = ijfac * kfac;
   for (iblk = 0; iblk < nblk ; iblk++) {
      gblk = domains[iblk].gblk;
      if (gmap[gblk].ublk != ndxin->ublk) continue;
      CPYEXT(gext, gmap[gblk]);
      len = extents_overlap(&ext, &gext, &ext1);
      if (len > 0) {
         if (ndims == 2) {
            for (j = ext1.jmin; j <= ext1.jmax; j++) {
               rp1 = r1[j - ext.jmin];
               rp2 = r2[j - ext.jmin];
               for (i = ext1.imin; i <= ext1.imax; i++) {
                  sp1 = s1[i - ext.imin];
                  sp2 = s2[i - ext.imin];
                  s = (rp1 * (sp2 - sp1) + sp1) / 
                       (1 - (sp2 - sp1) * (rp2 - rp1) + ptiny);
                  s = MAX(0.0,s);
                  s = MIN(1.0,s);
                  r = (sp1 * (rp2 - rp1) + rp1) / 
                       (1 - (sp2 - sp1) * (rp2 - rp1) + ptiny);
                  r = MAX(0.0,r);
                  r = MIN(1.0,r);
                  ii = i - ext.imin;
                  jj = j - ext.jmin;
                  ipim = ii * lf[0].ip + jj * lf[0].jp;
                  ipip = ii * lf[1].ip + jj * lf[1].jp;
                  ipjm = ii * lf[2].ip + jj * lf[2].jp;
                  ipjp = ii * lf[3].ip + jj * lf[3].jp;
                  xn = -(1 - s) * (1 - r) * xc[0] * ijfac +
                       -(  s  ) * (1 - r) * xc[1] * ijfac +
                       -(1 - s) * (  r  ) * xc[2] * ijfac +
                       -(  s  ) * (  r  ) * xc[3] * ijfac +
                        (1 - s) *          lf[0].x[ipim] * ifac +
                        (  s  ) *          lf[1].x[ipip] * ifac +
                        (1 - r) *          lf[2].x[ipjm] * jfac +
                        (  r  ) *          lf[3].x[ipjp] * jfac ;
                  yn = -(1 - s) * (1 - r) * yc[0] * ijfac +
                       -(  s  ) * (1 - r) * yc[1] * ijfac +
                       -(1 - s) * (  r  ) * yc[2] * ijfac + 
                       -(  s  ) * (  r  ) * yc[3] * ijfac + 
                        (1 - s) *          lf[0].y[ipim] * ifac +
                        (  s  ) *          lf[1].y[ipip] * ifac +
                        (1 - r) *          lf[2].y[ipjm] * jfac +
                        (  r  ) *          lf[3].y[ipjp] * jfac;
                  ii = i - gext.imin + NPNL;
                  jj = j - gext.jmin + NPNL;
                  ip = ii + domains[iblk].jp * jj;
                  domains[iblk].x[ip] = xn;
                  domains[iblk].y[ip] = yn;
                  domains[iblk].node[ip] = 1;
               }
            }
         } else {
            for (k = ext1.kmin; k <= ext1.kmax; k++) {
               tp1 = t1[k - ext1.kmin];
               tp2 = t2[k - ext1.kmin];
               tp3 = t3[k - ext1.kmin];
               tp4 = t4[k - ext1.kmin];
               for (j = ext1.jmin; j <= ext1.jmax; j++) {
                  sp1 = s1[j - ext1.jmin];
                  sp2 = s2[j - ext1.jmin];
                  sp3 = s3[j - ext1.jmin];
                  sp4 = s4[j - ext1.jmin];
                  for (i = ext1.imin; i <= ext1.imax; i++) {
                     rp1 = r1[i - ext1.imin];
                     rp2 = r2[i - ext1.imin];
                     rp3 = r3[i - ext1.imin];
                     rp4 = r4[i - ext1.imin];
                     b11 = (1. - (sp1 - sp3) * (tp1 - tp3));
                     b12 = ((tp1 - tp3) * (rp1 - rp3) - (rp1 - rp2));
                     b13 = ((rp1 - rp2) * (sp1 - sp3) - (rp1 - rp3));
                     b21 = ((tp1 - tp2) * (sp1 - sp3) - (sp1 - sp2));
                     b22 = (1. - (rp1 - rp3) * (tp1 - tp2));
                     b23 = ((sp1 - sp2) * (rp1 - rp3) - (sp1 - sp3));
                     b31 = ((sp1 - sp2) * (tp1 - tp3) - (tp1 - tp2));
                     b32 = ((tp1 - tp3) - (tp1 - tp2) * (rp1 - rp2));
                     b33 = (1 - (rp1 - rp2) * (sp1 - sp2));
                     recip_determ = 1.0 / (b11 + (rp1 - rp2) * b21 + (rp1 - rp3) * b31 + ptiny);
                     r = recip_determ * ( b11 * rp1 + b12 * sp1 + b13 * tp1);
                     s = recip_determ * ( b21 * rp1 + b22 * sp1 + b23 * tp1);
                     t = recip_determ * ( b31 * rp1 + b32 * sp1 + b33 * tp1);
                     r = MAX(r,0.0);
                     s = MAX(s,0.0);
                     t = MAX(t,0.0);
                     r = MIN(r,1.0);
                     s = MIN(s,1.0);
                     t = MIN(t,1.0);
                     for (iter = 0; iter < 10; iter++) {
                        rp = r;
                        sp = s;
                        tp = t;
                        rm  = rp1 + sp * tp * (rp1 - rp2 - rp3 + rp4);
                        sm  = sp1 + rp * tp * (sp1 - sp2 - sp3 + sp4);
                        tm  = tp1 + rp * sp * (tp1 - tp2 - tp3 + tp4);
                        r = recip_determ * ( b11 * rm + b12 * sm + b13 * tm);
                        s = recip_determ * ( b21 * rm + b22 * sm + b23 * tm);
                        t = recip_determ * ( b31 * rm + b32 * sm + b33 * tm);
                        r = MAX(r,0.0);
                        s = MAX(s,0.0);
                        t = MAX(t,0.0);
                        r = MIN(r,1.0);
                        s = MIN(s,1.0);
                        t = MIN(t,1.0);
                        err = (r - rp) * (r - rp) + (s - sp) * (s - sp) +
                              (t - tp) * (t - tp);
                        if (err < 1.e-6) break;
                     }
                     ii = i - ext.imin;
                     jj = j - ext.jmin;
                     kk = k - ext.kmin;
                     ipim    = ii * lf[0].ip + jj * lf[0].jp + kk * lf[0].kp;
                     ipim_jm =  extm.jmin * lf[0].jp +        kk * lf[0].kp;
                     ipim_jp =  extm.jmax * lf[0].jp +        kk * lf[0].kp;
                     ipim_km =         jj * lf[0].jp + extm.kmin * lf[0].kp;
                     ipim_kp =         jj * lf[0].jp + extm.kmax * lf[0].kp;
                     ipip    = ii * lf[1].ip + jj * lf[1].jp + kk * lf[1].kp;   
                     ipip_jm =  extm.jmin * lf[1].jp +        kk * lf[1].kp;
                     ipip_jp =  extm.jmax * lf[1].jp +        kk * lf[1].kp;
                     ipip_km =         jj * lf[1].jp + extm.kmin * lf[1].kp;
                     ipip_kp =         jj * lf[1].jp + extm.kmax * lf[1].kp;
                     ipjm    = ii * lf[2].ip + jj * lf[2].jp + kk * lf[2].kp;   
                     ipjm_km =         ii * lf[2].ip + extm.kmin * lf[2].kp;    
                     ipjm_kp =         ii * lf[2].ip + extm.kmax * lf[2].kp;    
                     ipjp    = ii * lf[3].ip + jj * lf[3].jp + kk * lf[3].kp;
                     ipjp_km =         ii * lf[3].ip + extm.kmin * lf[3].kp;
                     ipjp_kp =         ii * lf[3].ip + extm.kmax * lf[3].kp;
                     ipkm    = ii * lf[4].ip + jj * lf[4].jp + kk * lf[4].kp;
                     ipkp    = ii * lf[5].ip + jj * lf[5].jp + kk * lf[5].kp;
                     ii = i - gext.imin + NPNL;
                     jj = j - gext.jmin + NPNL;
                     kk = k - gext.kmin + NPNL;
                     ip = ii + jj * domains[iblk].jp + kk * domains[iblk].kp;   
		     xn =  (1 - r) * (1 - s) * (1 - t) * xc[0] * ijkfac +
		           (  r  ) * (1 - s) * (1 - t) * xc[1] * ijkfac +
		           (1 - r) * (  s  ) * (1 - t) * xc[2] * ijkfac +
		           (  r  ) * (  s  ) * (1 - t) * xc[3] * ijkfac +
		           (1 - r) * (1 - s) * (  t  ) * xc[4] * ijkfac +
		           (  r  ) * (1 - s) * (  t  ) * xc[5] * ijkfac +
		           (1 - r) * (  s  ) * (  t  ) * xc[6] * ijkfac +
		           (  r  ) * (  s  ) * (  t  ) * xc[7] * ijkfac +
		          -(1 - r) * (  s  ) *           lf[0].x[ipim_jp] * ijfac +
		          -(1 - r) * (1 - s) *           lf[0].x[ipim_jm] * ijfac +
		          -(  r  ) * (  s  ) *           lf[1].x[ipip_jp] * ijfac +
		          -(  r  ) * (1 - s) *           lf[1].x[ipip_jm] * ijfac +
		          -(1 - r)           * (1 - t) * lf[0].x[ipim_km] * ikfac +
		          -(1 - r)           * (  t  ) * lf[0].x[ipim_kp] * ikfac +
		          -(  r  )           * (1 - t) * lf[1].x[ipip_km] * ikfac +
		          -(  r  )           * (  t  ) * lf[1].x[ipip_kp] * ikfac +
		          -          (1 - s) * (1 - t) * lf[2].x[ipjm_km] * jkfac +
		          -          (1 - s) * (  t  ) * lf[2].x[ipjm_kp] * jkfac +
		          -          (  s  ) * (1 - t) * lf[3].x[ipjp_km] * jkfac +
		          -          (  s  ) * (  t  ) * lf[3].x[ipjp_kp] * jkfac +
		           (1 - r)                     * lf[0].x[ipim] * ifac +
		           (  r  )                     * lf[1].x[ipip] * ifac +
		                     (1 - s)           * lf[2].x[ipjm] * jfac +
		                     (  s  )           * lf[3].x[ipjp] * jfac +
		                               (1 - t) * lf[4].x[ipkm] * kfac +
		                               (  t  ) * lf[5].x[ipkp] * kfac ;
		     yn =  (1 - r) * (1 - s) * (1 - t) * yc[0] * ijkfac +
		           (  r  ) * (1 - s) * (1 - t) * yc[1] * ijkfac +
		           (1 - r) * (  s  ) * (1 - t) * yc[2] * ijkfac +
		           (  r  ) * (  s  ) * (1 - t) * yc[3] * ijkfac +
		           (1 - r) * (1 - s) * (  t  ) * yc[4] * ijkfac +
		           (  r  ) * (1 - s) * (  t  ) * yc[5] * ijkfac +
		           (1 - r) * (  s  ) * (  t  ) * yc[6] * ijkfac +
		           (  r  ) * (  s  ) * (  t  ) * yc[7] * ijkfac +
		          -(1 - r) * (  s  ) *           lf[0].y[ipim_jp] * ijfac +
		          -(1 - r) * (1 - s) *           lf[0].y[ipim_jm] * ijfac +
		          -(  r  ) * (  s  ) *           lf[1].y[ipip_jp] * ijfac +
		          -(  r  ) * (1 - s) *           lf[1].y[ipip_jm] * ijfac +
		          -(1 - r)           * (1 - t) * lf[0].y[ipim_km] * ikfac +
		          -(1 - r)           * (  t  ) * lf[0].y[ipim_kp] * ikfac +
		          -(  r  )           * (1 - t) * lf[1].y[ipip_km] * ikfac +
		          -(  r  )           * (  t  ) * lf[1].y[ipip_kp] * ikfac +
		          -          (1 - s) * (1 - t) * lf[2].y[ipjm_km] * jkfac +
		          -          (1 - s) * (  t  ) * lf[2].y[ipjm_kp] * jkfac +
		          -          (  s  ) * (1 - t) * lf[3].y[ipjp_km] * jkfac +
		          -          (  s  ) * (  t  ) * lf[3].y[ipjp_kp] * jkfac +
		           (1 - r)                     * lf[0].y[ipim] * ifac +
		           (  r  )                     * lf[1].y[ipip] * ifac +
		                     (1 - s)           * lf[2].y[ipjm] * jfac +
		                     (  s  )           * lf[3].y[ipjp] * jfac +
		                               (1 - t) * lf[4].y[ipkm] * kfac +
		                               (  t  ) * lf[5].y[ipkp] * kfac ;
		     zn =  (1 - r) * (1 - s) * (1 - t) * zc[0] * ijkfac +
		           (  r  ) * (1 - s) * (1 - t) * zc[1] * ijkfac +
		           (1 - r) * (  s  ) * (1 - t) * zc[2] * ijkfac +
		           (  r  ) * (  s  ) * (1 - t) * zc[3] * ijkfac +
		           (1 - r) * (1 - s) * (  t  ) * zc[4] * ijkfac +
		           (  r  ) * (1 - s) * (  t  ) * zc[5] * ijkfac +
		           (1 - r) * (  s  ) * (  t  ) * zc[6] * ijkfac +
		           (  r  ) * (  s  ) * (  t  ) * zc[7] * ijkfac +
		          -(1 - r) * (  s  ) *           lf[0].z[ipim_jp] * ijfac +
		          -(1 - r) * (1 - s) *           lf[0].z[ipim_jm] * ijfac +
		          -(  r  ) * (  s  ) *           lf[1].z[ipip_jp] * ijfac +
		          -(  r  ) * (1 - s) *           lf[1].z[ipip_jm] * ijfac +
		          -(1 - r)           * (1 - t) * lf[0].z[ipim_km] * ikfac +
		          -(1 - r)           * (  t  ) * lf[0].z[ipim_kp] * ikfac +
		          -(  r  )           * (1 - t) * lf[1].z[ipip_km] * ikfac +
		          -(  r  )           * (  t  ) * lf[1].z[ipip_kp] * ikfac +
		          -          (1 - s) * (1 - t) * lf[2].z[ipjm_km] * jkfac +
		          -          (1 - s) * (  t  ) * lf[2].z[ipjm_kp] * jkfac +
		          -          (  s  ) * (1 - t) * lf[3].z[ipjp_km] * jkfac +
		          -          (  s  ) * (  t  ) * lf[3].z[ipjp_kp] * jkfac +
		           (1 - r)                     * lf[0].z[ipim] * ifac +
		           (  r  )                     * lf[1].z[ipip] * ifac +
		                     (1 - s)           * lf[2].z[ipjm] * jfac +
		                     (  s  )           * lf[3].z[ipjp] * jfac +
		                               (1 - t) * lf[4].z[ipkm] * kfac +
		                               (  t  ) * lf[5].z[ipkp] * kfac ;
                     domains[iblk].x[ip] = xn;
                     domains[iblk].y[ip] = yn;
                     domains[iblk].z[ip] = zn;
                     domains[iblk].node[ip] = 1;
                  }
               }
            }
         }
      }
   }
   FREEMEM(r1);
   FREEMEM(s1);
   FREEMEM(r2);
   FREEMEM(s2);
   if (ndims == 3) {
      FREEMEM(r3);
      FREEMEM(r4);
      FREEMEM(s3);
      FREEMEM(s4);
      FREEMEM(t1);
      FREEMEM(t2);
      FREEMEM(t3);
      FREEMEM(t3);
      FREEMEM(t4);
   }
   meshgen_freesurfs(&lf, ns);
}
static void meshgen_sphereSection_parse(MeshGen_t *data, int intype) {
   char *me = "meshgen_sphereSection_parse";
   char op[MAXLINE];
   int index;
   int j, cflag;
   double sphere_half2d[2][4] = {0, 1, 1, 1,
                                 1, 1, 1, 0 };
   double sphere_full2d[3][4] = {-1, 0, -1, 1,
                                 -1, 1,  1, 1,
                                  1, 1,  1, 0};
   double sphere_oct3d[3][12] = { 
            0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1,       
            1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 
            0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1 };
   double sphere_quad3d[4][12] = { 
            0, 1, -1, 1, 1, -1, 1, 1, 1, 0, 1, 1, 
            1, 1, -1, 1, 0, -1, 1, 0, 1, 1, 1, 1,
            0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1,
            0, 0, -1, 1, 0, -1, 1, 1, -1, 0, 1, -1};
   double sphere_half3d[5][12] = { 
            0, 1, -1, 1, 1, -1, 1, 1, 1, 0, 1, 1,
            1, 1, -1, 1, -1, -1, 1, -1, 1, 1, 1, 1,
            0, 1, 1, 1, 1 , 1, 1, -1, 1, 0, -1, 1, 
            0, -1, -1,  1, -1, -1, 1,  1, -1, 0, 1, -1,
            0, -1, 1, 1, -1, 1, 1, -1, -1, 0, -1, -1};
   double sphere_full3d[6][12] = { 
           -1, 1, -1, 1, 1, -1, 1, 1, 1, -1, 1, 1,
            1, 1, -1, 1, -1, -1, 1, -1, 1, 1, 1, 1,
           -1, 1, 1, 1, 1, 1, 1, -1, 1, -1, -1, 1,
           -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1,
           -1, -1, 1, 1, -1, 1, 1, -1, -1, -1, -1, -1,
           -1, -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1};         
   double cyl_quad3d[2][6] = {0, 1, 0, 1, 1, 0,
                              1, 1, 0, 1, 0, 0};
   double cyl_half3d[3][6] = {0,  1,  0,  1,  1,  0,
                              1,  1,  0,  1, -1,  0,
                              1, -1,  0,  0, -1,  0};
   double cyl_full3d[4][6] = {-1,  1,  0,  1,  1,  0,
                               1,  1,  0,  1, -1,  0,
                               1, -1,  0, -1, -1,  0,
                              -1, -1,  0, -1,  1,  0};
   double **sphere_ptr;
   data->sphereSection.v1[0] = 0.;
   data->sphereSection.v1[1] = 0.;
   data->sphereSection.v1[2] = 0.;
   data->sphereSection.v2[0] = 0.;
   data->sphereSection.v2[1] = 0.;
   data->sphereSection.v2[2] = 0.;
   data->sphereSection.v3[0] = 0.;
   data->sphereSection.v3[1] = 0.;
   data->sphereSection.v3[2] = 0.;
   data->sphereSection.v4[0] = 0.;
   data->sphereSection.v4[1] = 0.;
   data->sphereSection.v4[2] = 0.;
   if (intype == MESHGEN_SPHERE_SEC) {
      geta(op);
      data->sphereSection.rad = getf(&cflag);
      index = -1;
      geta(op); 
      if (!strcmp(op,"oct")) {
         index = geti(&cflag);
         if ((index < 1) || (index > 3) || (ndims == 2)) {
            ctlerror(me,"Bad argument to oct option in sphere_section");
         }
         index--;
         j = 0;
         data->sphereSection.v1[0] = sphere_oct3d[index][j++];
         data->sphereSection.v1[1] = sphere_oct3d[index][j++];
         data->sphereSection.v1[2] = sphere_oct3d[index][j++];
         data->sphereSection.v2[0] = sphere_oct3d[index][j++];
         data->sphereSection.v2[1] = sphere_oct3d[index][j++];
         data->sphereSection.v2[2] = sphere_oct3d[index][j++];
         data->sphereSection.v3[0] = sphere_oct3d[index][j++];
         data->sphereSection.v3[1] = sphere_oct3d[index][j++];
         data->sphereSection.v3[2] = sphere_oct3d[index][j++];
         data->sphereSection.v4[0] = sphere_oct3d[index][j++];
         data->sphereSection.v4[1] = sphere_oct3d[index][j++];
         data->sphereSection.v4[2] = sphere_oct3d[index][j++];
      } else if (!strcmp(op,"quad")) {
         index = geti(&cflag);
         if ((index < 1) || (index > 4) || (ndims == 2)) {
            ctlerror(me,"Bad argument to quad option in sphere_section");
         }
         index--;
         j = 0;
         data->sphereSection.v1[0] = sphere_quad3d[index][j++];
         data->sphereSection.v1[1] = sphere_quad3d[index][j++];
         data->sphereSection.v1[2] = sphere_quad3d[index][j++];
         data->sphereSection.v2[0] = sphere_quad3d[index][j++];
         data->sphereSection.v2[1] = sphere_quad3d[index][j++];
         data->sphereSection.v2[2] = sphere_quad3d[index][j++];
         data->sphereSection.v3[0] = sphere_quad3d[index][j++];
         data->sphereSection.v3[1] = sphere_quad3d[index][j++];
         data->sphereSection.v3[2] = sphere_quad3d[index][j++];
         data->sphereSection.v4[0] = sphere_quad3d[index][j++];
         data->sphereSection.v4[1] = sphere_quad3d[index][j++];
         data->sphereSection.v4[2] = sphere_quad3d[index][j++];
      } else if (!strcmp(op,"half")) {
         index = geti(&cflag);
         if ((index < 1) || (index > 5)) {
            ctlerror(me,"Bad argument to half option in sphere_section");
         }
         index--;
         j = 0;
         if (ndims == 3) {
            data->sphereSection.v1[0] = sphere_half3d[index][j++];
            data->sphereSection.v1[1] = sphere_half3d[index][j++];
            data->sphereSection.v1[2] = sphere_half3d[index][j++];
            data->sphereSection.v2[0] = sphere_half3d[index][j++];
            data->sphereSection.v2[1] = sphere_half3d[index][j++];
            data->sphereSection.v2[2] = sphere_half3d[index][j++];
            data->sphereSection.v3[0] = sphere_half3d[index][j++];
            data->sphereSection.v3[1] = sphere_half3d[index][j++];
            data->sphereSection.v3[2] = sphere_half3d[index][j++];
            data->sphereSection.v4[0] = sphere_half3d[index][j++];
            data->sphereSection.v4[1] = sphere_half3d[index][j++];
            data->sphereSection.v4[2] = sphere_half3d[index][j++];
         } else {
            data->sphereSection.v1[0] = sphere_half2d[index][j++];
            data->sphereSection.v1[1] = sphere_half2d[index][j++];
            data->sphereSection.v2[0] = sphere_half2d[index][j++];
            data->sphereSection.v2[1] = sphere_half2d[index][j++];  
         } 
      } else if (!strcmp(op,"full")) {
         index = geti(&cflag);
         if ((index < 1) || (index > 6)) {
            ctlerror(me,"Bad argument to full option in sphere_section");
         }
         index--;
         j = 0;
         if (ndims == 3) {
            data->sphereSection.v1[0] = sphere_full3d[index][j++];
            data->sphereSection.v1[1] = sphere_full3d[index][j++];
            data->sphereSection.v1[2] = sphere_full3d[index][j++];
            data->sphereSection.v2[0] = sphere_full3d[index][j++];
            data->sphereSection.v2[1] = sphere_full3d[index][j++];
            data->sphereSection.v2[2] = sphere_full3d[index][j++];
            data->sphereSection.v3[0] = sphere_full3d[index][j++];
            data->sphereSection.v3[1] = sphere_full3d[index][j++];
            data->sphereSection.v3[2] = sphere_full3d[index][j++];
            data->sphereSection.v4[0] = sphere_full3d[index][j++];
            data->sphereSection.v4[1] = sphere_full3d[index][j++];
            data->sphereSection.v4[2] = sphere_full3d[index][j++];
         } else {
            data->sphereSection.v1[0] = sphere_full2d[index][j++];
            data->sphereSection.v1[1] = sphere_full2d[index][j++];
            data->sphereSection.v2[0] = sphere_full2d[index][j++];
            data->sphereSection.v2[1] = sphere_full2d[index][j++];  
         } 
      } else if (!strcmp(op,"v1")) {
         if (ndims == 2) {
            data->sphereSection.v1[0] = getf(&cflag);
            data->sphereSection.v1[1] = getf(&cflag);
            geta(op);
            data->sphereSection.v2[0] = getf(&cflag);
            data->sphereSection.v2[1] = getf(&cflag);
         } else {
            data->sphereSection.v1[0] = getf(&cflag);
            data->sphereSection.v1[1] = getf(&cflag);
            data->sphereSection.v1[2] = getf(&cflag);
            geta(op);
            data->sphereSection.v2[0] = getf(&cflag);
            data->sphereSection.v2[1] = getf(&cflag);
            data->sphereSection.v2[2] = getf(&cflag);
            geta(op);
            data->sphereSection.v3[0] = getf(&cflag);
            data->sphereSection.v3[1] = getf(&cflag);
            data->sphereSection.v3[2] = getf(&cflag);
            geta(op);
            data->sphereSection.v4[0] = getf(&cflag);
            data->sphereSection.v4[1] = getf(&cflag);
            data->sphereSection.v4[2] = getf(&cflag);
         } 
      } 
   } else if (intype == MESHGEN_CYL) {
      geta(op);
      data->sphereSection.rad = getf(&cflag);
      index = -1;
      geta(op); 
      if (!strcmp(op,"quad")) {
         index = geti(&cflag);
         if ((index < 1) || (index > 2)) {
            ctlerror(me,"Bad argument to quad option in cyl_section");
         }
         index--;
         j = 0;
         data->sphereSection.v1[0] = cyl_quad3d[index][j++];
         data->sphereSection.v1[1] = cyl_quad3d[index][j++];
         data->sphereSection.v1[2] = cyl_quad3d[index][j++];
         data->sphereSection.v2[0] = cyl_quad3d[index][j++];
         data->sphereSection.v2[1] = cyl_quad3d[index][j++];
         data->sphereSection.v2[2] = cyl_quad3d[index][j++];
      } else if (!strcmp(op,"half")) {
         index = geti(&cflag);
         if ((index < 1) || (index > 3)) {
            ctlerror(me,"Bad argument to half option in cyl_section");
         }
         index--;
         j = 0;
         data->sphereSection.v1[0] = cyl_half3d[index][j++];
         data->sphereSection.v1[1] = cyl_half3d[index][j++];
         data->sphereSection.v1[2] = cyl_half3d[index][j++];
         data->sphereSection.v2[0] = cyl_half3d[index][j++];
         data->sphereSection.v2[1] = cyl_half3d[index][j++];
         data->sphereSection.v2[2] = cyl_half3d[index][j++];
      } else if (!strcmp(op,"full")) {
         index = geti(&cflag);
         if ((index < 1) || (index > 4)) {
            ctlerror(me,"Bad argument to full option in cyl_section");
         }
         index--;
         j = 0;
         data->sphereSection.v1[0] = cyl_full3d[index][j++];
         data->sphereSection.v1[1] = cyl_full3d[index][j++];
         data->sphereSection.v1[2] = cyl_full3d[index][j++];
         data->sphereSection.v2[0] = cyl_full3d[index][j++];
         data->sphereSection.v2[1] = cyl_full3d[index][j++];
         data->sphereSection.v2[2] = cyl_full3d[index][j++];
      } else if (!strcmp(op,"v1")) {
         if (ndims == 2) {
            data->sphereSection.v1[0] = getf(&cflag);
            data->sphereSection.v1[1] = getf(&cflag);
            geta(op);
            data->sphereSection.v2[0] = getf(&cflag);
            data->sphereSection.v2[1] = getf(&cflag);
         } else {
            data->sphereSection.v1[0] = getf(&cflag);
            data->sphereSection.v1[1] = getf(&cflag);
            data->sphereSection.v1[2] = getf(&cflag);
            geta(op);
            data->sphereSection.v2[0] = getf(&cflag);
            data->sphereSection.v2[1] = getf(&cflag);
            data->sphereSection.v2[2] = getf(&cflag);
         } 
      } 
   } else if (intype == MESHGEN_PLANE) {
      geta(op);
      if (ndims == 2) {
         data->sphereSection.v1[0] = getf(&cflag);
         data->sphereSection.v1[1] = getf(&cflag);
         geta(op);
         data->sphereSection.v2[0] = getf(&cflag);
         data->sphereSection.v2[1] = getf(&cflag);
      } else {
         data->sphereSection.v1[0] = getf(&cflag);
         data->sphereSection.v1[1] = getf(&cflag);
         data->sphereSection.v1[2] = getf(&cflag);
         geta(op);
         data->sphereSection.v2[0] = getf(&cflag);
         data->sphereSection.v2[1] = getf(&cflag);
         data->sphereSection.v2[2] = getf(&cflag);
         geta(op);
         data->sphereSection.v3[0] = getf(&cflag);
         data->sphereSection.v3[1] = getf(&cflag);
         data->sphereSection.v3[2] = getf(&cflag);
         geta(op);
         data->sphereSection.v4[0] = getf(&cflag);
         data->sphereSection.v4[1] = getf(&cflag);
         data->sphereSection.v4[2] = getf(&cflag);
      } 
   } 
   if (intype != MESHGEN_PLANE) {
      meshgen_sphereSection_init(&data->sphereSection); 
   }
}
