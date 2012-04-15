#include "irs.h"
#include "irssys.h"
double icsum( double *v, int n, double *pflops )
{
   register int i ;
   register double sum ;
   sum = 0.0 ;
   for ( i = 0 ; i < n ; i++ ) {
      sum += v[i] ;
   }
   *pflops += 1.0 * n ;
   return( sum ) ;
}
