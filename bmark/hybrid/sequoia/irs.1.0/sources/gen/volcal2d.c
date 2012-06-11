#include "irs.h"
#include "irsgen.h"
#include "FunctionTimer.h"
void volcal2d( double  *vol, double *area, double *x, double *y,
               Domain_t *domain )
{
   char *me = "volcal2d";
   int i ;
   double a1, a2, r1, r2;
   double third = 0.3333333333333333 ;
   double *x1, *x2, *x3, *x4 ;
   double *y1, *y2, *y3, *y4 ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   NDSET2D(x,x1,x2,x3,x4) ;
   NDSET2D(y,y1,y2,y3,y4) ;
   if ( ifplane == 0 ) {
      for ( i = domain->fpz ; i <= domain->lpz ; i++ ) {
         a1 = 0.5 * ( ( x2[i] - x1[i] ) * ( y4[i] - y1[i] )
                    - ( y2[i] - y1[i] ) * ( x4[i] - x1[i] ) ) ;
         r1 = third * ( y1[i] + y2[i] + y4[i] ) ;
         a2 = 0.5 * ( ( x4[i] - x3[i] ) * ( y2[i] - y3[i] )
                    - ( y4[i] - y3[i] ) * ( x2[i] - x3[i] ) ) ;
         r2 = third * ( y4[i] + y2[i] + y3[i] ) ;
         vol[i]  = r1 * a1 + r2 * a2 ;
         area[i] = a1 + a2 ;
      }
      myflops += 26.0 * ( domain->lpz - domain->fpz + 1 ) ;
   } else {
      for ( i = domain->fpz ; i <= domain->lpz ; i++ ) {
         a1 = 0.5 * ( ( x2[i] - x1[i] ) * ( y4[i] - y1[i] )
                    - ( y2[i] - y1[i] ) * ( x4[i] - x1[i] ) ) ;
         a2 = 0.5 * ( ( x4[i] - x3[i] ) * ( y2[i] - y3[i] )
                    - ( y4[i] - y3[i] ) * ( x2[i] - x3[i] ) ) ;
         vol[i]  = a1 + a2 ;
         area[i] = a1 + a2 ;
      }
      myflops += 18.0 * ( domain->lpz - domain->fpz + 1 ) ;
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
