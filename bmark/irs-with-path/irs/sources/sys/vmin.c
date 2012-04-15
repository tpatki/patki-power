#include <time.h>
#include "mach.h" 
#include "irs.h" 
#include "irssys.h"
double  vmin(
	    int	     *ndxmin,	   double   *v,		  int	   n )
{
#ifdef STKLIB
   int ione = 1 ;
   double vmin ;
   qvmin( &vmin, ndxmin, v, &n, &ione) ;
   *ndxmin = *ndxmin - 1 ;
   return(vmin) ;
#else
   register int i,ndx ;
   register double vmin ;
   vmin = v[0] ;
   ndx = 0 ;
   for ( i = 1 ; i < n ; i++ )
      if (v[i] < vmin)
         {
         vmin = v[i] ;
         ndx = i ;
         }
   *ndxmin = ndx ;
   return(vmin) ;
#endif
}
