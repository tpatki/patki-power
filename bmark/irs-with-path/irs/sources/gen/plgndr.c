#include "irs.h"
#include "irsgen.h"
void plgndr( int l, int m, double *xmu, double *plg, int n )
   {
   int i, ll,  j ;
   double pmm, fact, somx2, pmmp1, pll, mu ;   
   i = 0 ;
   for ( j = 0 ; j < n ; j++ )
     {
     if ( fabs(xmu[j]) > 1. ) 
       {
	 i = 1 ;
       }
     }
   if ( (m < 0) || (m > l) || i ) 
     { 
     PRINT(stdout, "ERROR: bad argument to plgndr\n") ;
     if (fpout != NULL) {
        PRINT( fpout, "ERROR: bad argument to plgndr\n") ;
     }
     }
   for ( j = 0 ; j < n ; j++ )
     {
     mu = xmu[j] ;
     pmm = 1. ;
     if (m > 0)
       {
       somx2 = sqrt((1.-mu)*(1.+mu)) ;
       fact = 1. ;
       for ( i = 1 ; i <= m ; i++ )
	 {
	   pmm *= -fact*somx2 ;
	   fact += 2. ;
	 }
       }
     if (l == m)
       {
       plg[j] = pmm ;
       }
     else
       {
       pmmp1 = mu*(2*m+1.)*pmm ;
       if ( l == (m+1) )
	 {
	   plg[j] = pmmp1 ;
	 }
       else
	 {
	   for ( ll = m+2 ; ll <= l ; ll++ )
	     {
	       pll = (mu*(2*ll-1)*pmmp1-(ll+m-1)*pmm)/(ll-m) ;
	       pmm = pmmp1 ;
	       pmmp1 = pll ;
	     }
	   plg[j] = pll ;
	 }
       }
   }
 }
