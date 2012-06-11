#include "irs.h"
#include "cgl.h"
#include "irscur.h"
#define max2(a,b)  ((a) > (b) ? (a) : (b))
#define min2(a,b)  ((a) < (b) ? (a) : (b))
int  setcur0(
	    int	     cc,	   double   *x,		  double   *y,
	    int	     n,		   char	    *xlab,	  char	   *ylab )
{
   int error, i ;
   error = 0 ;
   ifcuron[cc] = 1 ;
   ifcurbd[cc] = 0 ;
   ifcurst[cc] = 0 ;
   strcpy(p1d[2*cc  ].namelab,ylab) ;
   strcpy(p1d[2*cc+1].namelab,xlab) ;
   p1d[2*cc  ].palen = n ;
   p1d[2*cc+1].palen = n ;
   p1d[2*cc  ].fpa = ALLOT(double,n) ;
   p1d[2*cc+1].fpa = ALLOT(double,n) ;
   for ( i = 0 ; i < n ; i++ )
      {
      p1d[2*cc  ].fpa[i] = y[i] ;
      p1d[2*cc+1].fpa[i] = x[i] ;
      }
   ncur++ ;
   p1d[2*cc  ].min = irsfmin(p1d[2*cc  ].fpa,p1d[2*cc  ].palen) ;
   p1d[2*cc  ].max = irsfmax(p1d[2*cc  ].fpa,p1d[2*cc  ].palen) ;
   p1d[2*cc+1].min = irsfmin(p1d[2*cc+1].fpa,p1d[2*cc+1].palen) ;
   p1d[2*cc+1].max = irsfmax(p1d[2*cc+1].fpa,p1d[2*cc+1].palen) ;
   if (ncur == 1)
      {
      cxmn = p1d[2*cc+1].min ;
      cxmx = p1d[2*cc+1].max ;
      cymn = p1d[2*cc  ].min   ;
      cymx = p1d[2*cc  ].max   ;
      }
   else
      {
      cxmn = min2(cxmn,p1d[2*cc+1].min) ;
      cxmx = max2(cxmx,p1d[2*cc+1].max) ;
      cymn = min2(cymn,p1d[2*cc].min  ) ;
      cymx = max2(cymx,p1d[2*cc].max  ) ;
      }
   return(error) ;
}
#undef max2
#undef min2
