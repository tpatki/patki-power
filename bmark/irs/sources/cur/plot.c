#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int  plot( void )
{
   int error, i ;
   error = 0 ;
   i = getnxcn() ;
   if (i < 0 ) return(-1) ;
   ifcuron[i] = 1 ;
   ifcurbd[i] = 0 ;
   ifcurst[i] = 0 ;
   error = getcur(i,0) ;
   return(error) ;
}
