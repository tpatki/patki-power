#include "irs.h"
#include "irsbndry.h"
int bcnorm(double *norm, int len, int *ndx, Domain_t *domain)
{
   int i;
   int error;
   int isline;
   int imax, imin, jmax, jmin, kmax, kmin;
   int xdeg, ydeg, zdeg, ndeg;
   double xmax, xmin, ymax, ymin, zmax, zmin;
   double dx1, dy1, dz1;
   double dx2, dy2, dz2;
   double dx3, dy3, dz3;
   double dot;
   double rnorm;
   error = 0;
   xmax = -plarge;
   ymax = -plarge;
   zmax = -plarge;
   xmin =  plarge;
   ymin =  plarge;
   zmin =  plarge;
   if (ndims == 3) {
      for ( i = 0 ; i < len ; i++ ) {
         if (domain->x[ndx[i]] > xmax) {
            xmax = domain->x[ndx[i]];
            imax = ndx[i];
         }
         if (domain->y[ndx[i]] > ymax) {
            ymax = domain->y[ndx[i]];
            jmax = ndx[i];
         }
         if (domain->z[ndx[i]] > zmax) {
            zmax = domain->z[ndx[i]];
            kmax = ndx[i];
         }
         if (domain->x[ndx[i]] < xmin) {
            xmin = domain->x[ndx[i]];
            imin = ndx[i];
         }
         if (domain->y[ndx[i]] < ymin) {
            ymin = domain->y[ndx[i]];
            jmin = ndx[i];
         }
         if (domain->z[ndx[i]] < zmin) {
            zmin = domain->z[ndx[i]];
            kmin = ndx[i];
         }
      }
   } else {
      for ( i = 0 ; i < len ; i++ ) {
         if (domain->x[ndx[i]] > xmax) {
            xmax = domain->x[ndx[i]];
            imax = ndx[i];
         }
         if (domain->y[ndx[i]] > ymax) {
            ymax = domain->y[ndx[i]];
            jmax = ndx[i];
         }
         if (domain->x[ndx[i]] < xmin) {
            xmin = domain->x[ndx[i]];
            imin = ndx[i];
         }
         if (domain->y[ndx[i]] < ymin) {
            ymin = domain->y[ndx[i]];
            jmin = ndx[i];
         }
      }
   }
   xdeg = 0 ;
   ydeg = 0 ;
   zdeg = 0 ;
   if ( fabs(xmax - xmin) < xcut ) xdeg = 1;
   if ( fabs(ymax - ymin) < xcut ) ydeg = 1;
   if ( (ndims == 3) && (fabs(zmax - zmin) < xcut) ) zdeg = 1;
   ndeg = xdeg + ydeg + zdeg ;
   norm[0] = 0.0 ;
   norm[1] = 0.0 ;
   norm[2] = 0.0 ;
   if ( ndims == 2 ) {
      if ( ndeg == 0 ) {
         norm[0] =  domain->y[imax] - domain->y[imin];
         norm[1] = -domain->x[imax] + domain->x[imin];
         rnorm   = 1.0 / sqrt( norm[0] * norm[0] + norm[1] * norm[1] ) ;
         norm[0] *= rnorm ;
         norm[1] *= rnorm ;
      } else if ( ndeg == 1 ) {
         if (xdeg) norm[0] = 1.0 ;
         if (ydeg) norm[1] = 1.0 ;
      } else {
         error = 1 ;
      }
   }
   if ( ndims == 3 ) {
      if ( ndeg == 0 ) {
         isline = 0 ;
         if ( (imax == jmax) && (imax == kmax) && 
              (imin == jmin) && (jmin == kmin)) {
            isline = 1;
            for (i = 0; i < len; i++) {
               dx1 = domain->x[imin] - domain->x[ndx[i]]; 
               dy1 = domain->y[imin] - domain->y[ndx[i]]; 
               dz1 = domain->z[imin] - domain->z[ndx[i]]; 
               dx2 = domain->x[imax] - domain->x[ndx[i]]; 
               dy2 = domain->y[imax] - domain->y[ndx[i]]; 
               dz2 = domain->z[imax] - domain->z[ndx[i]]; 
               rnorm = 1.0   / sqrt( dx1*dx1 + dy1*dy1 + dz1*dz1 ) ;
               rnorm = rnorm / sqrt( dx2*dx2 + dy2*dy2 + dz2*dz2 ) ;
               dot   = rnorm * ( dx1*dx2 + dy1*dy2 + dz1*dz2 ) ;
               if ( fabs(dot) < 0.999 ) {
                  imin = ndx[i]; 
                  isline = 0;
                  break;
               }
            }
         }
         if (isline) {
            norm[0] = domain->x[imax] - domain->x[imin];
            norm[1] = domain->y[imax] - domain->y[imin];
            norm[2] = domain->z[imax] - domain->z[imin];
         } else {
            dx1   = domain->x[imax] - domain->x[imin];
            dy1   = domain->y[imax] - domain->y[imin];
            dz1   = domain->z[imax] - domain->z[imin];
            rnorm = 1.0 / sqrt( dx1*dx1 + dy1*dy1 + dz1*dz1 + ptiny ) ;
            dx1  *= rnorm;
            dy1  *= rnorm;
            dz1  *= rnorm;
            dx2   = domain->x[jmax] - domain->x[jmin];
            dy2   = domain->y[jmax] - domain->y[jmin];
            dz2   = domain->z[jmax] - domain->z[jmin];
            rnorm = 1.0 / sqrt( dx2*dx2 + dy2*dy2 + dz2*dz2 + ptiny ) ;
            dx2  *= rnorm;
            dy2  *= rnorm;
            dz2  *= rnorm;
            dx3   = domain->x[kmax] - domain->x[kmin];
            dy3   = domain->y[kmax] - domain->y[kmin];
            dz3   = domain->z[kmax] - domain->z[kmin];
            rnorm = 1.0 / sqrt( dx3*dx3 + dy3*dy3 + dz3*dz3 + ptiny ) ;
            dx3  *= rnorm;
            dy3  *= rnorm;
            dz3  *= rnorm;
            if ( fabs(dx1*dx2 + dy1*dy2 + dz1*dz2) < 0.999 ) {
               norm[0] = dy1*dz2 - dz1*dy2 ;
               norm[1] = dz1*dx2 - dx1*dz2 ;
               norm[2] = dx1*dy2 - dy1*dx2 ;
            } else if ( fabs(dx1*dx3 + dy1*dy3 + dz1*dz3) < 0.999 ) {
               norm[0] = dy1*dz3 - dz1*dy3 ;
               norm[1] = dz1*dx3 - dx1*dz3 ;
               norm[2] = dx1*dy3 - dy1*dx3 ;
            } else if ( fabs(dx3*dx2 + dy3*dy2 + dz3*dz2) < 0.999 ) {
               norm[0] = dy2*dz3 - dz2*dy3 ;
               norm[1] = dz2*dx3 - dx2*dz3 ;
               norm[2] = dx2*dy3 - dy2*dx3 ;
            } else {
               error = 1;
               return(error);
            }
         }
         rnorm = 1.0 / sqrt (norm[0]*norm[0] + norm[1]*norm[1] + 
                             norm[2]*norm[2] + ptiny ) ;
         norm[0] *= rnorm;
         norm[1] *= rnorm;
         norm[2] *= rnorm;
      } else if (ndeg == 1) {
         if (xdeg) norm[0] = 1.0 ;
         if (ydeg) norm[1] = 1.0 ;
         if (zdeg) norm[2] = 1.0 ;
      } else if (ndeg == 2) {
         if ((xdeg) && (ydeg)) norm[2] = 1.0 ;
         if ((xdeg) && (zdeg)) norm[1] = 1.0 ;
         if ((ydeg) && (zdeg)) norm[0] = 1.0 ;
      }  else {
         error = 1;
      } 
   }
   return(error);
}
