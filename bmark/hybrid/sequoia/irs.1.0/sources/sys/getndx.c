#include <time.h>
#include "mach.h" 
#include "irs.h" 
#include "irssys.h"
int  getndx(
	    int	     *ndx,	   int	    *flag,	  int	   test,
	    int	     n,		   int	    *zbit )
{
#ifdef STKLIB
         int i,j ;
         int ione = 1 ;
         int izero = 0 ;
         j = qztoil(ndx,&ione,&ione,zbit,&izero,&n,&izero,&ione) ;
         for ( i = 0 ; i < j ; i++ )  ndx[i] = ndx[i] - 1 ;
         return(j) ;
#else
         register int i,j ;
         j = 0 ;
         for ( i = 0 ; i < n ; i++ )
            if ( flag[i] == test )
               ndx[j++] = i ;
         return(j) ;
#endif
}
