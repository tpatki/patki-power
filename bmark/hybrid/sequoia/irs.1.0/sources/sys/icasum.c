#include "irs.h"
#include "irssys.h"
double icasum( double *v, int n,  double *pflops )
{
   register int i ;
   register double sum ;
   sum = 0.0 ;
   for ( i = 0 ; i < n ; i++ ) {
      sum += fabs( v[i] ) ;
   }
   *pflops += 5.0 * n ;
   return( sum ) ;
}
