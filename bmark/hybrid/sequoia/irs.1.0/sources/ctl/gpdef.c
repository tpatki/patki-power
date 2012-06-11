#include <signal.h>
#include "irs.h"
#include "irsctl.h"
int  gpdef( int	     gptype ) {
   int error ;
   char newsym[MAXWORD] ;
   char newval[MAXWORD] ;
   error = 0 ;
   ifparm = 0 ;
   geta(newsym) ;
   geta(newval) ;
   if (newval[0] == '{') {
      parmsym();
      strcpy(newval,sym);
   }
   ifparm = 1 ;
   error = gpdef0(gptype,newsym,newval) ;
   return(error) ;
}
