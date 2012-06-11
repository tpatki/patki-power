#include "irsdefs.h"
#include "irs.h"
#include "irstdiff.h"
#include "irsgen.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void DivgradDriver(double *x, double *y, double *z,
		   Domain_t *domain, RadiationData_t *rblk )
{
   char *me = "DivgradDriver";
   int i, j ;
   int count, elementIndex;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8 ;
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8 ;
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8 ;
   double *xc, *yc, *zc, *volc ;
   double gradX[8], gradY[8], gradZ[8];
   double xDual[8], yDual[8], zDual[8], phiDual[8];
   int imin[7] ;
   int imax[7] ;
   int jmin[7] ;
   int jmax[7] ;
   int jp   = domain->jp ;
   int kmin[7] ;
   int kmax[7] ;
   int kp   = domain->kp ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   if ( ndims == 2 ) {
      NDSET2D(x,x1,x2,x3,x4) ;
      NDSET2D(y,y1,y2,y3,y4) ;
   }
   if ( ndims == 3 ) {
      NDSET3D(x,x1,x2,x3,x4,x5,x6,x7,x8) ;
      NDSET3D(y,y1,y2,y3,y4,y5,y6,y7,y8) ;
      NDSET3D(z,z1,z2,z3,z4,z5,z6,z7,z8) ;
   }
   xc = MALLOT(double,domain->nnalls) ;
   yc = MALLOT(double,domain->nnalls) ;
   for ( i = 0 ; i < domain->nnalls ; i++ ) {
    xc[i] = 0.0 ;
    yc[i] = 0.0 ;
   }
   if ( ndims == 2 ) {
      int fpz = domain->fpz ;
      int lpz = domain->lpz ;
      for ( i = fpz ; i <= lpz ; i++ ) {
         yc[i] = 0.25 * ( y1[i] + y2[i] + y3[i] + y4[i] ) ;
         xc[i] = 0.25 * ( x1[i] + x2[i] + x3[i] + x4[i] ) ;
      }
      myflops += 8.0 * ( lpz - fpz + 1 ) ;
   }
   if ( ndims == 3 ) {
      int fpz = domain->fpz ;
      int lpz = domain->lpz ;
      zc = MALLOT(double,domain->nnalls) ;
      for ( i = 0 ; i < domain->nnalls ; i++ ) {
         zc[i] = 0.0 ;
      }
      for ( i = fpz ; i <= lpz ; i++ ) {
         xc[i] = 0.125 * ( x1[i] + x2[i] + x3[i] + x4[i] +
	  	           x5[i] + x6[i] + x7[i] + x8[i] ) ;
         yc[i] = 0.125 * ( y1[i] + y2[i] + y3[i] + y4[i] +
		           y5[i] + y6[i] + y7[i] + y8[i] ) ;
         zc[i] = 0.125 * ( z1[i] + z2[i] + z3[i] + z4[i] +
		           z5[i] + z6[i] + z7[i] + z8[i] ) ;
      }
      myflops += 24.0 * ( lpz - fpz + 1 ) ;
      volc = ALLOT(double,domain->nnalls) ;
      volcal3d( volc, xc, yc, zc, domain ) ;
   }

 {       imin[6] = domain->imin     ;
      imax[6] = domain->imax + 1 ;
      jmin[6] = domain->jmin     ;
      jmax[6] = domain->jmax + 1 ;
      kmin[6] = domain->kmin     ;
      kmax[6] = domain->kmax + 1 ;
   }
   if ( ndims == 2 ) {
      divgradpert2d( xc, yc, domain, rblk,
                     imin[6], imax[6], jmin[6], jmax[6] ) ;
   }
   if ( ndims == 3 ) {
      if ( ifdivgrad == 0 ) {
         FemDivgrad3Interior( rblk, xc, yc, zc, volc, 
			      domain, kmin[6], kmax[6], 
			      jmin[6], jmax[6], imin[6], imax[6] ) ;
      }
      if ( ifdivgrad == 1 ) {
         divgradpert3d( rblk, xc, yc, zc, volc,
                        imin[6], imax[6], jmin[6], jmax[6], kmin[6], kmax[6],
                        domain ) ;
      }
   }

   FREEMEM(xc) ;
   FREEMEM(yc) ;
   if ( ndims == 3 ) {
      FREEMEM(zc)   ;
      FREEMEM(volc) ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
