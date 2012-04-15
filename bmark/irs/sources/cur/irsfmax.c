#include "irs.h"
#include "cgl.h"
#include "irscur.h"
double irsfmax( double *x, int n )
{
   int i ;
   double big ;
   big = x[0] ;
   for ( i = 1 ; i < n ; i++ ) {
      if (x[i] > big)  big = x[i] ;
   }
   return(big) ;
}
