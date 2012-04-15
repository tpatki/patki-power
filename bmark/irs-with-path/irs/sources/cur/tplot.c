#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int  tplot( void )
{
   char *me = "tplot";
   int error, i ;
   error = 0 ;
   i = getnxcn() ;
   if (i < 0) return(1) ;
   ifcuron[i] = 1 ;
   ifcurbd[i] = 0 ;
   ifcurst[i] = 0 ;
   error = getcur(i,1) ;
   return(error) ;
}
