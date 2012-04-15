#include "irs.h"
#include "irsreg.h"
#include "irslag.h"
#include "FunctionTimer.h"
#define SUM4S(v,a,b,c,d) (v[a[i]] + v[a[i]] + v[a[i]] + v[a[i]])
#define SUM4(a,b,c,d) (a[i] + b[i] + c[i] + d[i])
void LengthScale( Domain_t *domain, double *x, double *y, double *z, 
                  double *length )
{
   char *me = "LengthScale";
   int i;
   int ir;
   double *x1,*x2,*x3,*x4,*x5,*x6,*x7,*x8 ;
   double *y1,*y2,*y3,*y4,*y5,*y6,*y7,*y8 ;
   double *z1,*z2,*z3,*z4,*z5,*z6,*z7,*z8 ;
   double dx, dy, dz, ileg, jleg, kleg;
   double onedi, onedj, onedk;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   onedi = 1. ;
   onedj = 1. ;
   onedk = 1. ;
   if (domain->imax == domain->imin+1)  onedi = 0. ;
   if (domain->jmax == domain->jmin+1)  onedj = 0. ;
   if (domain->kmax == domain->kmin+1)  onedk = 0. ;
   if (ndims == 2) {
         NDSET2D(x,x1,x2,x3,x4) ;
         NDSET2D(y,y1,y2,y3,y4) ;
         for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
            dx   = x2[i] + x3[i] - x4[i] - x1[i] ;
            dy   = y2[i] + y3[i] - y4[i] - y1[i] ;
            jleg = onedi * (dx*dx + dy*dy) ;
            dx   = x1[i] + x2[i] - x3[i] - x4[i] ;
            dy   = y1[i] + y2[i] - y3[i] - y4[i] ;
            ileg = onedj * (dx*dx + dy*dy) ;
            length[i] = 0.25 * (ileg + jleg) / 
	                           (domain->area[i]*domain->area[i] + ptiny) ;
         }
      myflops += 28.0 * ( domain->lrz - domain->frz + 1 ) ;
   } else {
         NDSET3D(x,x1,x2,x3,x4,x5,x6,x7,x8) ;
         NDSET3D(y,y1,y2,y3,y4,y5,y6,y7,y8) ;
         NDSET3D(z,z1,z2,z3,z4,z5,z6,z7,z8) ;
         for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
            dx = 0.25 * (SUM4(x1,x2,x6,x5) - SUM4(x4,x3,x7,x8)) ;
            dy = 0.25 * (SUM4(y1,y2,y6,y5) - SUM4(y4,y3,y7,y8)) ;
            dz = 0.25 * (SUM4(z1,z2,z6,z5) - SUM4(z4,z3,z7,z8)) ;
            ileg = (dx*dx + dy*dy + dz*dz) ;
            dx = 0.25 * (SUM4(x2,x3,x7,x6) - SUM4(x1,x4,x8,x5)) ;
            dy = 0.25 * (SUM4(y2,y3,y7,y6) - SUM4(y1,y4,y8,y5)) ;
            dz = 0.25 * (SUM4(z2,z3,z7,z6) - SUM4(z1,z4,z8,z5)) ;
            jleg = (dx*dx + dy*dy + dz*dz) ;
            dx = 0.25 * (SUM4(x5,x6,x7,x8) - SUM4(x1,x2,x3,x4)) ;
            dy = 0.25 * (SUM4(y5,y6,y7,y8) - SUM4(y1,y2,y3,y4)) ;
            dz = 0.25 * (SUM4(z5,z6,z7,z8) - SUM4(z1,z2,z3,z4)) ;
            kleg = (dx*dx + dy*dy + dz*dz) ;
            length[i] = ( ileg*jleg*onedk + onedi*jleg*kleg + ileg*onedj*kleg )
                      / ( domain->vol[i] * domain->vol[i] + ptiny ) ;
         }
      myflops += 101.0 * ( domain->lrz - domain->frz + 1 ) ;
   }
   for (ir = 1; ir <= nreg; ir++) {
      int *ndx    = domain->rndxmix[ir];
      int *grdndx = domain->rgrdmix[ir];
      int len     = domain->rlenmix[ir];
      for (i = 0; i < len; i++) {
         domain->invLengthSqr[ndx[i]] = domain->invLengthSqr[grdndx[i]];
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
#undef SUM4
