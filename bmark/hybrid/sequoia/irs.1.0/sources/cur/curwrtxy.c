#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int curwrtxy(
	    int	     mode )
{
   int cn,cflag ;
   double val,val0 ;
   char outfile[20] ;
   geta(outfile) ;
   val0 = getf(&cflag) ;
   cn = geti(&cflag) ;
   val = getf(&cflag) ;
   curwrtxy0(outfile,val0,cn,val,mode) ;
   return(0);
}
