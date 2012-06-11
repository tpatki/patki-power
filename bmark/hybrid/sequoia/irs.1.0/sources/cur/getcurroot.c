#include "irs.h"
#include "cgl.h"
#include "irscur.h"
void getcurroot(
	    double   *ret,	   int	    *nret,	  double   *x,
	    double   *y,	   int	    n,		  double   yval,
	    double   xmin,	   double   xmax )
{
   int i,j,iset ;
   double xroot,dy,dxdy ;
   j = 0 ;
   for ( i = 1 ; i < n ; i++ )
      {
      iset = 0 ;
      if ((y[i-1] <= yval) && (yval < y[i])) iset = 1 ;
      if ((y[i-1] >= yval) && (yval > y[i])) iset = 1 ;
      if (iset == 0) continue ;
      dy = y[i] - y[i-1] ;
      if (fabs(dy) < ptiny) dy = ptiny ;
      dxdy = (x[i] - x[i-1])/dy ;
      xroot = x[i-1] + dxdy*(yval - y[i-1]) ;
      if (xroot < xmin) continue ;
      if (xroot > xmax) continue ;
      ret[j] = xroot ;
      j++ ;
      }
   nret[0] = j ;
}
