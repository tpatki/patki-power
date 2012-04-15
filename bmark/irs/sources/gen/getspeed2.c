#include "irs.h"
#include "irsgen.h"
#include "FunctionTimer.h"
void getspeed2( double *speed2,	Domain_t *domain )
{
   char *me = "getspeed2";
   int i ;
   double *xv1,*xv2,*xv3,*xv4,*xv5,*xv6,*xv7,*xv8 ;
   double *yv1,*yv2,*yv3,*yv4,*yv5,*yv6,*yv7,*yv8 ;
   double *zv1,*zv2,*zv3,*zv4,*zv5,*zv6,*zv7,*zv8 ;
   double move, c43, c49, c109 ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
      speed2[i] = domain->cs2[i] ;
   }

   if ( ngroup > 0 ) {
     c49 = 4.0 * sbc / 9.0 ;
      for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
         speed2[i] = speed2[i] + c49 * domain->erad[i]
                   / ( domain->den[i] + ptiny ) ;
      }
      myflops += 7.0 * ( domain->lrz - domain->frz + 1 ) ;
   }
   if (ndims == 2) {
      NDSET2D(domain->xdot,xv1,xv2,xv3,xv4) ;
      NDSET2D(domain->ydot,yv1,yv2,yv3,yv4) ;
      for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
         move = fabs(xv1[i]) + fabs(xv2[i]) + fabs(xv3[i]) + fabs(xv4[i])
              + fabs(yv1[i]) + fabs(yv2[i]) + fabs(yv3[i]) + fabs(yv4[i]) ;
         if (move < ucut) speed2[i] = 0.0 ;
      }
      myflops += 7.*(domain->lrz-domain->frz+1) ;
   }
   if (ndims == 3) {
      NDSET3D(domain->xdot,xv1,xv2,xv3,xv4,xv5,xv6,xv7,xv8) ;
      NDSET3D(domain->ydot,yv1,yv2,yv3,yv4,yv5,yv6,yv7,yv8) ;
      NDSET3D(domain->zdot,zv1,zv2,zv3,zv4,zv5,zv6,zv7,zv8) ;
      for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
         move = fabs(xv1[i]) + fabs(xv2[i]) + fabs(xv3[i]) + fabs(xv4[i])
              + fabs(xv5[i]) + fabs(xv6[i]) + fabs(xv7[i]) + fabs(xv8[i]) 
              + fabs(yv1[i]) + fabs(yv2[i]) + fabs(yv3[i]) + fabs(yv4[i])
              + fabs(yv5[i]) + fabs(yv6[i]) + fabs(yv7[i]) + fabs(yv8[i]) 
              + fabs(zv1[i]) + fabs(zv2[i]) + fabs(zv3[i]) + fabs(zv4[i])
              + fabs(zv5[i]) + fabs(zv6[i]) + fabs(zv7[i]) + fabs(zv8[i]) ;
         if (move < ucut) speed2[i] = 0.0 ;
      }
      myflops += 23.*(domain->lrz-domain->frz+1) ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
