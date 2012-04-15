#include "irs.h"
#include "cgl.h"
#include "irscur.hh"
int curgetxy(
	    int	     mode )
{
   int cn,cflag ;
   double val ;
   cn = geti(&cflag) ;
   val = getf(&cflag) ;
   curgetxy0(cn,val,mode) ;
   return(0);
}
