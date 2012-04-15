#include "irs.h"
#include "irsbndry.h"
int bcin0(int len, int *ndx,int ibc, char *op, Domain_t *domain) {
   int error,i1,j1,k1,i2,j2,k2,n1,n2,stride ;
   double dx1,dy1,dz1,dx2,dy2,dz2,nx,ny,nz,norm ;
   double nm[3];
   char mesg[MAXLINE];
   error = 0 ;
   domain->bc[ibc].type = 1  ;
   domain->bc[ibc].id = -1  ;
   domain->bc[ibc].nx   = 0. ;
   domain->bc[ibc].ny   = 0. ;
   domain->bc[ibc].nz   = 0. ;
   domain->bc[ibc].rtype = OPEN ;
   if (!strcmp(op,"xvcnst")) {
      domain->bc[ibc].type = XVCNST ;
      domain->bc[ibc].nx   = 1. ;
   } else if (!strcmp(op,"yvcnst")) {
      domain->bc[ibc].type = YVCNST ;
      domain->bc[ibc].ny   = 1. ;
   } else if (!strcmp(op,"zvcnst")) {
      domain->bc[ibc].type = ZVCNST ;
      domain->bc[ibc].nz   = 1. ;
   } else if (!strcmp(op,"fixed")) {
      domain->bc[ibc].type = FIXED ;
      domain->bc[ibc].nx   = 1. ;
      domain->bc[ibc].ny   = 1. ;
      domain->bc[ibc].nz   = 1. ;
   } else if (!strcmp(op,"free")) {
      domain->bc[ibc].type  = FREE ;
      domain->bc[ibc].rtype = OPEN ;
   } else if (!strcmp(op,"wall")) {
      domain->bc[ibc].type = WALL ;
   } else if (!strcmp(op,"plane")) {
      domain->bc[ibc].type = PLANE ;
   } else if (!strcmp(op,"cylinder")) {
      domain->bc[ibc].type = CYLINDER ;
      domain->bc[ibc].nx=1.0;
      domain->bc[ibc].ny=1.0;
      domain->bc[ibc].nz=0.0;
   } else if (!strcmp(op,"xcylinder")) {
      domain->bc[ibc].type = CYLINDER ;
      domain->bc[ibc].nx=0.0;
      domain->bc[ibc].ny=1.0;
      domain->bc[ibc].nz=1.0;
   } else if (!strcmp(op,"ycylinder")) {
      domain->bc[ibc].type = CYLINDER ;
      domain->bc[ibc].nx=1.0;
      domain->bc[ibc].ny=0.0;
      domain->bc[ibc].nz=1.0;
   } else if (!strcmp(op,"zcylinder")) {
      domain->bc[ibc].type = CYLINDER ;
      domain->bc[ibc].nx=1.0;
      domain->bc[ibc].ny=1.0;
      domain->bc[ibc].nz=0.0;
   } else if (!strcmp(op,"sphere")) {
      domain->bc[ibc].type = SPHERE ;
   } else if (!strcmp(op,"cone")) {
      domain->bc[ibc].type = CONE ;
   } else if (!strcmp(op,"line")) {
      domain->bc[ibc].type = LINE ;
   } else {
      sprintf(mesg,"Boundary Condition %s is not recognized\n",op);
      ctlwarning("bcin0",mesg);
   }
   domain->bc[ibc].ndx = ndx ;
   domain->bc[ibc].len = len ;
   stride = 0 ;
   if (ndims == 2) {
      n1 = ndx[0] ;
      n2 = ndx[len-1] ;
      j1 = n1 / domain->jp ;
      i1 = n1 - j1 * domain->jp ;
      j2 = n2 / domain->jp ;
      i2 = n2 - j2 * domain->jp ;
      if ((i1 == i2) & (j1 != j2)) stride = 1 ; 
      if ((i1 != i2) & (j1 == j2)) stride = domain->jp ; 
      if (domain->bc[ibc].type == CONE) {
         nx = -(domain->y[n2] - domain->y[n1]) ;
         ny =  (domain->x[n2] - domain->x[n1]) ;
         norm = 1.0 / sqrt(nx*nx + ny*ny + ptiny) ;
         domain->bc[ibc].nx = norm*nx ;
         domain->bc[ibc].ny = norm*ny ;
         domain->bc[ibc].nz = 0. ;
      }
      if (domain->bc[ibc].type == LINE) {
         if ( bcnorm(nm,len,ndx,domain) == 0) {
            domain->bc[ibc].nx = nm[0];
            domain->bc[ibc].ny = nm[1];
            domain->bc[ibc].nz = 0. ;
         } else {
            sprintf(mesg,"Boundary condition %i has ill-defined norm.\n",ibc);
            ctlwarning("bcin0",mesg);
         }
      }
      if ( (domain->bc[ibc].type == WALL)  |
           (domain->bc[ibc].type == PLANE) ) {
         if ( bcnorm(nm,len,ndx,domain) == 0) {
            domain->bc[ibc].nx = nm[0];
            domain->bc[ibc].ny = nm[1];
            domain->bc[ibc].nz = 0.;
         } else {
            sprintf(mesg,"Boundary condition %i has ill-defined norm.\n",ibc);
            ctlwarning("bcin0",mesg);
         } 
      }
   }
   if (ndims == 3) {
      n1 = ndx[0] ;
      n2 = ndx[len-1] ;
      k1 = n1 / domain->kp ;
      j1 = (n1 - k1 * domain->kp) / domain->jp ;
      i1 =  n1 - k1 * domain->kp - j1 * domain->jp ;
      k2 = n2 / domain->kp ;
      j2 = (n2 - k2 * domain->kp) / domain->jp ;
      i2 =  n2 - k2 * domain->kp - j2 * domain->jp ;
      if ((i1 == i2) & (j1 != j2) & (k1 != k2)) stride = 1 ; 
      if ((i1 != i2) & (j1 == j2) & (k1 != k2)) stride = domain->jp ; 
      if ((i1 != i2) & (j1 != j2) & (k1 == k2)) stride = domain->kp ;
      if (domain->bc[ibc].type == CONE) {
         n1 = k1 * domain->kp + j1 * domain->jp + i1 ;
         n2 = k2 * domain->kp + j2 * domain->jp + i2 ;
         dx1 = domain->x[n1] ;
         dy1 = domain->y[n1] ;
         dx1 = sqrt(dx1*dx1 + dy1*dy1) ;
         dz1 = domain->z[n1] ;
         dx2 = domain->x[n2] ;
         dy2 = domain->y[n2] ;
         dx2 = sqrt(dx2*dx2 + dy2*dy2) ;
         dz2 = domain->z[n2] ;
         nx = -(dz2 - dz1) ;
         ny = 0. ;
         nz =  (dx2 - dx1) ;
         norm = 1./sqrt(nx*nx + ny*ny + nz*nz + ptiny) ;
         domain->bc[ibc].nx = norm*nx ;
         domain->bc[ibc].ny = norm*ny ;
         domain->bc[ibc].nz = norm*nz ;
      }
      if (domain->bc[ibc].type == LINE) {
         if ( bcnorm(nm,len,ndx,domain) == 0) {
            domain->bc[ibc].nx = nm[0];
            domain->bc[ibc].ny = nm[1];
            domain->bc[ibc].nz = nm[2];
         } else {
            sprintf(mesg,"Boundary condition %i has ill-defined norm.\n",ibc);
            ctlwarning("bcin0",mesg);
         } 
      }
      if ( (domain->bc[ibc].type == WALL)  |
           (domain->bc[ibc].type == PLANE) ) {
         if ( bcnorm(nm,len,ndx,domain) == 0) {
            domain->bc[ibc].nx = nm[0];
            domain->bc[ibc].ny = nm[1];
            domain->bc[ibc].nz = nm[2];
         } else {
            sprintf(mesg,"Boundary condition %i has ill-defined norm.\n",ibc);
            ctlwarning("bcin0",mesg);
         } 
      }
   }
   domain->bc[ibc].pn = stride ;
   return(error) ;
}
