#include "irs.h"
#include "irsgen.h"
double ratiosum( double ratio, int n )
{
   int i ;
   double x, t ;
   t = 1.0 ;
   x = 0.0 ;
   for ( i = 1 ; i < n ; i++ ) {
      x += t ;
      t *= ratio ;
   }
   return( x ) ;
}
