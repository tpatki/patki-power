#include "irs.h"
#include "irsparm.h"
int ndset( void )
{
   char *me = "ndset";
   if (genmd != -1) {
      ctlnotice(me,"Can't xeq doneset -- memory already allocated") ;
      return(0) ;
   }
   genmd = 1 ;
   parmsanity();
   memexp() ; 
   return(0);
}
