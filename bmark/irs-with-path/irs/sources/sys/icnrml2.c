#include <time.h>
#include "mach.h"
#include "irs.h"
#include "irssys.h"
   double icnrml2(double *v,int n)
   {
   register int i ;
   register double sum ;
   sum = 0. ;
   for ( i = 0 ; i < n ; i++ )
     sum += v[i]*v[i] ;
   return(sum) ;
   }
