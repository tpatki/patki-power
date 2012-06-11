#include "irs.h"
#include "irssys.h"
double icdot( double *v1, double *v2, int n, double *pflops )
{
   register int i ;
   register double sum ;
   sum = 0.0 ;
   for ( i = 0 ; i < n ; i++ ) {
      sum += v1[i] * v2[i] ;
   }
   *pflops += 2.0 * n ;
   return( sum ) ;
}
