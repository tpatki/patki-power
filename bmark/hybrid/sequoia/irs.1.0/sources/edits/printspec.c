#include "irs.h"
#include "irsedits.h"
void printspec( 
	    char     *lab,	   double   *field,	  int	   i0,
	    int	     j0,	   int	    n,		  Domain_t *domain )
{
   int i,igrid ;
   igrid = j0*domain->jp + i0 ;
   printf("%s(%d:%d,%d) = ",lab,i0,i0+n-1,j0) ;
   for ( i = 0 ; i < n ; i++ ) printf("%e ",field[igrid+i]) ;
   printf("\n") ;
}
