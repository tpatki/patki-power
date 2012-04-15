#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int  setcur(
	    double   *x,	   double   *y,		  int	   n,
	    char     *xlab,	   char	    *ylab )
{
   int error, cc ;
   error = 0 ;
   cc = getnxcn() ;
   if (cc < 0) return(1) ;
   error = setcur0(cc,x,y,n,xlab,ylab) ;
   return(error) ;
}
