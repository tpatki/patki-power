#include "irs.h"
#include "irsgen.h"
#include "FunctionTimer.h"
#define NDPTRSET(v,v0,v1,v2,v3,v4,v5,v6,v7)  \
   v0 = v ;   \
   v1 = v0 + 1 ;  \
   v2 = v0 + domain->jp ; \
   v3 = v1 + domain->jp ; \
   v4 = v0 + domain->kp ; \
   v5 = v1 + domain->kp ; \
   v6 = v2 + domain->kp ; \
   v7 = v3 + domain->kp ;
#define SUM8(a1,a2,a3,a4,a5,a6,a7,a8) \
 (a1[i] + a2[i] + a3[i] + a4[i] + a5[i] + a6[i] + a7[i] + a8[i])
#define VOLPYRAMID(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4) \
  dx1 = x1[i] + x2[i] - x3[i] - x4[i] ; \
  dy1 = y1[i] + y2[i] - y3[i] - y4[i] ; \
  dz1 = z1[i] + z2[i] - z3[i] - z4[i] ; \
  dx2 = x2[i] + x3[i] - x4[i] - x1[i] ; \
  dy2 = y2[i] + y3[i] - y4[i] - y1[i] ; \
  dz2 = z2[i] + z3[i] - z4[i] - z1[i] ; \
  dx3 = x4c - (x1[i] + x2[i] + x3[i] + x4[i]) ; \
  dy3 = y4c - (y1[i] + y2[i] + y3[i] + y4[i]) ; \
  dz3 = z4c - (z1[i] + z2[i] + z3[i] + z4[i]) ; \
  ax  = dy1*dz2 - dz1*dy2 ; \
  ay  = dz1*dx2 - dx1*dz2 ; \
  az  = dx1*dy2 - dy1*dx2 ; \
  va += ax*dx3 + ay*dy3 + az*dz3
void volcal3d( double *vol, double *x, double *y, double *z, Domain_t *domain )
{
  char *me = "volcal3d";
  int i ;
  double *x0,*x1,*x2,*x3,*x4,*x5,*x6,*x7,*x8 ;
  double *y0,*y1,*y2,*y3,*y4,*y5,*y6,*y7,*y8 ;
  double *z0,*z1,*z2,*z3,*z4,*z5,*z6,*z7,*z8 ;
  double dx1,dy1,dz1 ;
  double dx2,dy2,dz2 ;
  double dx3,dy3,dz3 ;
  double ax,ay,az,va ;
  double x4c,y4c,z4c ;
  double vnormc = 0.0208333333333333;             
  double x71, y71, z71, x72, y72, z72, x74, y74, z74 ;
  double x60, y60, z60, x50, y50, z50, x30, y30, z30 ;
  double xps, yps, zps, cyz, czx, cxy;
  double vnormq = 0.083333333333333333;             
  double myflops = 0.0 ;
  FT_INITIALIZE(me, domain->hash)
  if (!ifvol72) {
    NDSET3D(x,x1,x2,x3,x4,x5,x6,x7,x8) ;
    NDSET3D(y,y1,y2,y3,y4,y5,y6,y7,y8) ;
    NDSET3D(z,z1,z2,z3,z4,z5,z6,z7,z8) ;
    for ( i = domain->fpz ; i <= domain->lpz ; i++ ) {
      x4c = 0.5 * SUM8(x1,x2,x3,x4,x5,x6,x7,x8) ;
      y4c = 0.5 * SUM8(y1,y2,y3,y4,y5,y6,y7,y8) ;
      z4c = 0.5 * SUM8(z1,z2,z3,z4,z5,z6,z7,z8) ;  
      va = 0.0 ;
      VOLPYRAMID(x1,y1,z1,x5,y5,z5,x6,y6,z6,x2,y2,z2) ;
      VOLPYRAMID(x3,y3,z3,x7,y7,z7,x8,y8,z8,x4,y4,z4) ;
      VOLPYRAMID(x1,y1,z1,x4,y4,z4,x8,y8,z8,x5,y5,z5) ;
      VOLPYRAMID(x2,y2,z2,x6,y6,z6,x7,y7,z7,x3,y3,z3) ;
      VOLPYRAMID(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4) ;
      VOLPYRAMID(x5,y5,z5,x8,y8,z8,x7,y7,z7,x6,y6,z6) ; 
      vol[i] = vnormc * va ;
    }
    myflops +=  295.0 * ( domain->lpz - domain->fpz + 1 ) ;
  } else {
    NDPTRSET(x,x0,x1,x2,x3,x4,x5,x6,x7) ;
    NDPTRSET(y,y0,y1,y2,y3,y4,y5,y6,y7) ;
    NDPTRSET(z,z0,z1,z2,z3,z4,z5,z6,z7) ;
    for ( i = domain->fpz ; i <= domain->lpz ; i++ ) {
      x71 = x7[i] - x1[i] ;
      x72 = x7[i] - x2[i] ;
      x74 = x7[i] - x4[i] ;
      x30 = x3[i] - x0[i] ;
      x50 = x5[i] - x0[i] ;
      x60 = x6[i] - x0[i] ;
      y71 = y7[i] - y1[i] ;
      y72 = y7[i] - y2[i] ;
      y74 = y7[i] - y4[i] ;
      y30 = y3[i] - y0[i] ;
      y50 = y5[i] - y0[i] ;
      y60 = y6[i] - y0[i] ;
      z71 = z7[i] - z1[i] ;
      z72 = z7[i] - z2[i] ;
      z74 = z7[i] - z4[i] ;
      z30 = z3[i] - z0[i] ;
      z50 = z5[i] - z0[i] ;
      z60 = z6[i] - z0[i] ;
      xps = x71 + x60 ;
      yps = y71 + y60 ;
      zps = z71 + z60 ;
      cyz = y72 * z30 - z72 * y30 ;
      czx = z72 * x30 - x72 * z30 ;
      cxy = x72 * y30 - y72 * x30 ;
      vol[i] = xps * cyz + yps * czx + zps * cxy ;
      xps = x72 + x50 ;
      yps = y72 + y50 ;
      zps = z72 + z50 ;
      cyz = y74 * z60 - z74 * y60 ;
      czx = z74 * x60 - x74 * z60 ;
      cxy = x74 * y60 - y74 * x60 ;
      vol[i] += xps * cyz + yps * czx + zps * cxy ;
      xps = x74 + x30 ;
      yps = y74 + y30 ;
      zps = z74 + z30 ;
      cyz = y71 * z50 - z71 * y50 ;
      czx = z71 * x50 - x71 * z50 ;
      cxy = x71 * y50 - y71 * x50 ;
      vol[i] += xps * cyz + yps * czx + zps * cxy ;
      vol[i] *= vnormq ;
    }
    myflops +=   72.0 * ( domain->lpz - domain->fpz + 1 ) ;
  }
  FT_FINALIZE(me, domain->hash, myflops)
}
#undef NDPTRSET
