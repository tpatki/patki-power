#include "irs.h"
#include "irsgen.h"
double ratioeval( double factor, int type, int n )
{
   char *me = "ratioeval" ;
   char msg[128] ;
   int i ;
   double rfactor, fn, rnm1, rn, rm1, rp, ratio ;
   ratio = 1 ;
   if ( type == 0 ) {
      return( ratio ) ;
   }
   if ( type == 1 ) {
      return( factor ) ;
   }
   fn = (double)(n-1) ;
   rfactor = 1.0 / factor ;
   if ( fabs( rfactor - fn ) < 0.001 ) {
      return( ratio ) ;
   }
   if ( rfactor > fn ) {
      ratio = pow( rfactor, 1.0 / fn ) ;
   } else {
      ratio = 1.0 - factor ;
   }
   for ( i = 0 ; i < 100 ; i++ ) {
      rnm1 = pow( ratio, fn - 1.0 ) ;
      rn  = ratio * rnm1 ;
      rm1 = ratio - 1.0  ;
      rp  = ( rfactor * rm1 - rn + 1.0 )
          / ( fn * rnm1 - ( rn - 1.0 ) / rm1 ) ;
      ratio += rp ;
      if ( fabs( rp / ratio ) < 1.0e-5 ) {
         break ;
      }
   }
   if ( type == 3 ) {
      ratio = 1.0 / ratio ;
   }
   if ( i <= 98 ) {
      return( ratio ) ;
   } else {
      rp = fabs( rp / ratio ) ;
      sprintf(msg,"Ratio failed to converge: eps = %e; using ratio = 1.", rp ) ;
      ctlwarning(me,msg);
      return( 1.0 ) ;
   }
}
