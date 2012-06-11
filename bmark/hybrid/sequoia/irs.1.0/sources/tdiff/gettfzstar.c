#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void gettfzstar( double *cden, double *czstar, double *tmat, double *abar,
                 double *zbar, int *ndx, int n, Domain_t *domain )
{
   char *me = "gettfzstar";
   int i ;
   double z    ;
   double z23  ;
   double tev  ;
   double s    ;
   double tsc  ;
   double tf   ;
   double tf7  ;
   double rho  ;
   double tfay ;
   double tfby ;
   double tfcy ;
   double rcy  ;
   double r    ;
   double q1   ;
   double q    ;
   double x    ;
   double zsc  ;
   double twothirds = 2.0 / 3.0 ;
   double alfa =  2.6752506  ;
   double beta =  0.33120023 ;
   double b0   = -1.762999   ;
   double b1   =  1.4317567  ;
   double b2   =  0.31546338 ;
   double a1   =  0.003323467;
   double a2   =  0.97183224 ;
   double a3   =  9.26148e-5 ;
   double a4   =  3.1016524  ;
   double c1   = -0.36666667 ;
   double c2   =  0.98333333 ;
   double myflops = 0.0;   
   FT_INITIALIZE(me, domain->hash)  
   s = 1000.0 ;
   for ( i = 0 ; i < n ; i++ ) {
      z   = MAX( zbar[i], 1.0 ) ;
      z23 = pow( zbar[i], twothirds ) ;
      z23 = MAX( z23, 1.0 ) ;
      tev  = MAX( tmat[ndx[i]], tfloor ) ;
      tev *= s ;
      tsc = tev / ( z23 * z23 ) ;
      tf  = tsc / ( 1.0 + tsc ) ;
      tf7 = tf  * tf  * tf ;
      tf7 = tf7 * tf7 * tf ;
      tfay = a1 * pow( tsc, a2 ) + a3 * pow( tsc, a4 ) ;
      tfby = -exp( b0 + b1 * tf + b2 * tf7 ) ;
      tfcy  = c1 * tf + c2 ;
      rcy = 1.0 / ( tfcy + ptiny ) ;
      rho = MAX( cden[i], 1.0e-6 ) ;
      r   = rho * z / ( z23 * z23 * z23 * abar[i] + ptiny ) ;
      q1 = tfay * pow( r, tfby ) ;
      q = pow( (pow(q1,tfcy) + pow(r,tfcy)), rcy ) ;
      x = alfa * pow( q, beta ) ;
      x = 2.0 * x * x ;
      zsc = x / ( 1.0 + x + sqrt( 1.0 + 2.0 * x ) ) ; 
      czstar[i] = z * zsc ;
   }
   myflops += 192.0 * n ;
   FT_FINALIZE(me, domain->hash, myflops)
}
