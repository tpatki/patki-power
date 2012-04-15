#include <signal.h>
#include "irs.h"
#include "irsctl.h"
#include "Gparm.h"
int  gpdef0(
	    int	     gptype,	   char	    *newsym,	  char	   *newval )
{
   char *me = "gpdef0";
   int error,igp,ifmatch ;
   error = 0 ;
   ifmatch = 0 ;
   for ( igp = 1 ; igp <= ngparm ; igp++ )
      {
      if (!strcmp(gparm[igp].sym,newsym))
         {
         strcpy(gparm[igp].val,newval) ;
         ifmatch = 1 ;
         break ;
         }
      }
   if (ifmatch == 0)
      {
      ngparm++ ;
      if ( ngparm > ngparmx ) {
         error = 1 ;
         ctlwarning(me,"too many gen parms; increase ngparmx") ;
      }
      else
         {
         strcpy(gparm[ngparm].sym, "   ") ;
         strcpy(gparm[ngparm].val, "   ") ;
         strcpy(gparm[ngparm].sym,newsym) ;
         strcpy(gparm[ngparm].val,newval) ;
         gparm[ngparm].type = gptype ;
         }
      }
   return(error) ;
}
