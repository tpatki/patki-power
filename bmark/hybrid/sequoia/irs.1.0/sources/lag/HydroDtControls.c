#include "irs.h"
#include "irssys.h"
#include "irsreg.h"
#include "irslag.h"
#include "irsbndry.h"
#include "irsgen.h"
#include "FunctionTimer.h"
#include "TimeStepControl.h"
void HydroDtControls( Domain_t *domain )
{
   char *me = "HydroDtControls";
   int i, ir, dtndx ;
   double dtc,mydtj,adot,dtv ;
   double *crate,*jrate,*speed2,*vrate,*vrate2 ;
   double prmin, prinv ;
   double *invLengthSqr = domain->invLengthSqr ;
   double *den          = domain->den          ;
   TimeStepControl_t *tsc;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   crate  = ALLOT(double, domain->nnalls) ;
   jrate  = ALLOT(double, domain->nnalls) ;
   speed2 = ALLOT(double, domain->nnalls) ;

   getspeed2( speed2, domain ) ;
   LengthScale( domain, domain->x, domain->y, domain->z, invLengthSqr ) ;
   for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
      crate[i] = invLengthSqr[i] * speed2[i] ;
   }
   myflops += 1.0 * ( domain->lrz - domain->frz + 1 ) ;
   setphony( crate, 0.0, domain ) ;
   dtc = fcrnt / (sqrt(vmax(&dtndx,crate,domain->nnalls)) + ptiny) ;
   tsc        = TimeStepControl_find("TSC_Courant",domain->hash) ;
   tsc->value = dtc ;
   if (ndims == 2) NDXEXT2D( dtndx, tsc->i, tsc->j, (*domain) ) ;
   if (ndims == 3) NDXEXT3D( dtndx, tsc->i, tsc->j, tsc->k, (*domain) ) ;
   if (ndims == 2) {
      double *x1,*x2,*x3,*x4 ;
      double *y1,*y2,*y3,*y4 ;
      double *xv1,*xv2,*xv3,*xv4 ;
      double *yv1,*yv2,*yv3,*yv4 ;
      NDSET2D(domain->x,x1,x2,x3,x4) ;
      NDSET2D(domain->y,y1,y2,y3,y4) ;
      NDSET2D(domain->xdot,xv1,xv2,xv3,xv4) ;
      NDSET2D(domain->ydot,yv1,yv2,yv3,yv4) ;
      for ( i = domain->frz ; i <= domain->lrz ; i++ ) {
         adot = 0.5 * deltatSubcycle * ( (x2 [i] - x4 [i]) * (yv3[i] - yv1[i])
                                       + (xv2[i] - xv4[i]) * (y3 [i] - y1 [i])
                                       - (yv2[i] - yv4[i]) * (x3 [i] - x1 [i])
                                       - (y2 [i] - y4 [i]) * (xv3[i] - xv1[i]) ) ;
         jrate[i] = fabs(adot) / (domain->area[i] + ptiny) ;
      }
      myflops += 27.0 * ( domain->lrz - domain->frz + 1 ) ;
      setphony( jrate, 0.0, domain ) ;
      mydtj = dtjfc / (vmax(&dtndx,jrate,domain->nnalls) + ptiny) ;
      tsc        = TimeStepControl_find("TSC_Area",domain->hash);
      tsc->value = mydtj ;
      NDXEXT2D( dtndx, tsc->i, tsc->j, (*domain) ) ;
   }



   FREEMEM(crate);
   FREEMEM(jrate);
   FREEMEM(speed2);

   FT_FINALIZE(me, domain->hash, myflops)
}
