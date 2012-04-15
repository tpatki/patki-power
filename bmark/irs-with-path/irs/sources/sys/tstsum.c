#include <time.h>
#include "mach.h" 
#include "irs.h" 
#include "irssys.h"
int  tstsum(
	    int	     *flag,	   int	    test,	  int	   n,
	    int	     *zbit )
{
#ifdef STKLIB
         int j ;
         int izero = 0 ;
         int ione  = 1 ;
         qjeq1(zbit,&izero,flag,&test,&n,&ione,&izero) ;
         j = lvsum(zbit,&izero,&n) ;
#else
         register int i, j ;
         j = 0 ;
         for ( i = 0 ; i < n ; i++ )
            if (flag[i] == test)  j++ ;
#endif
   return( j ) ;
}
