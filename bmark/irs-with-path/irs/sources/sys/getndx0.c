#include <time.h>
#include "mach.h" 
#include "irs.h" 
#include "irssys.h"
int  getndx0(
	    int	     *ndx,	   int	    *flag,	  int	   ioff,
	    int	     test,	   int	    n,		  int	   *zbit )
{
#ifdef STKLIB
      int izero = 0 ;
      int ione  = 1 ;
      int i,j ;
      flag += ioff ;
      n = n - ioff + 1 ;
      qjeq1(zbit,&izero,flag,&test,&n,&ione,&izero) ;
      j = qztoil(ndx,&ione,&ione,zbit,&izero,&n,&izero,&ione) ;
      ioff-- ;
      for ( i = 0 ; i < j ; i++ )  ndx[i] = ndx[i]  + ioff ;
      return(j) ;
#else
         register int i,j ;
         j = 0 ;
         for ( i = ioff ; i <= n ; i++ )
            if ( flag[i] == test )
               ndx[j++] = i ;
         return(j) ;
#endif
}
