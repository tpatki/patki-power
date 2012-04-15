#include "irs.h"
#include "cgl.h"
#include "irscur.h"
double irsfmin( double *x, int n )
{
   int i ;
   double small ;
   small = x[0] ;
   for ( i = 1 ; i < n ; i++ ) {
      if (x[i] < small)  small = x[i] ;
   }
   return(small) ;
}
