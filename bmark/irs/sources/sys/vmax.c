#include <time.h>
#include "mach.h" 
#include "irs.h" 
#include "irssys.h"
double vmax(
	    int	     *ndxmax,	   double   *v,		  int	   n )
{
#ifdef STKLIB
   int ione = 1 ;
   double vmax ;
   qvmax( &vmax, ndxmax, v, &n, &ione) ;
   *ndxmax = *ndxmax - 1 ;
   return(vmax) ;
#else
   register int i,ndx ;
   register double vmax ;
   vmax = v[0] ;
   ndx = 0 ;
   for ( i = 1 ; i < n ; i++ )
      if (v[i] > vmax)
         {
         vmax = v[i] ;
         ndx = i ;
         }
   *ndxmax = ndx ;
   return(vmax) ;
#endif
}
