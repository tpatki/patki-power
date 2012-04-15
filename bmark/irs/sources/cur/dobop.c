#include "irs.h"
#include "cgl.h"
#include "irscur.h"
void dobop(
	    char     *chop,	   double   *x,		  double   *y,
	    double   *xa,	   double   *ya,	  double   *xb,
	    double   *yb,	   int	    n,		  int	   bop )
{
   int i ;
   if (bop == 1)
      {
      strcpy(chop,"prod") ;
      for ( i = 0 ; i < n ; i++ )
	 {
         y[i] = ya[i]*yb[i] ;
         x[i] = xa[i] ;
         }
      }
   else if (bop == 2)
      {
      strcpy(chop,"div") ;
      for ( i = 0 ; i < n ; i++ )
	 {
         y[i] = ya[i]/yb[i] ;
         x[i] = xa[i] ;
         }
      }
   else if (bop == 3)
      {
      strcpy(chop,"sum") ;
      for ( i = 0 ; i < n ; i++ )
	 {
         y[i] = ya[i] + yb[i] ;
         x[i] = xa[i] ;
         }
      }
   else if (bop == 4)
      {
      strcpy(chop,"dif") ;
      for ( i = 0 ; i < n ; i++ )
	 {
         y[i] = ya[i] - yb[i] ;
         x[i] = xa[i] ;
         }
      }
}
