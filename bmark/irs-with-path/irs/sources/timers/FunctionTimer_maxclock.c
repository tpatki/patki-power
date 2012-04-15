#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Hash.h"
#include "FunctionTimer.h"
void FunctionTimer_maxclock(double *max, double *min)
{
   int i ;
   clock_t cnow, clast ;
   clast = (clock_t)( pow( 2.0, (8.0 * sizeof(clast) - 1.0) ) - 1.0 ) ;
   cnow  = clast ;
   while ( cnow >= clast ) {
      clast = cnow ;
      cnow++ ;
      if ( cnow < 0 ) break ;
   }
   *min = (double)cnow;
   *max = (double)clast;
}
