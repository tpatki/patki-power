#include "irs.h"
#include "irsgenrd.hh"
int deck( void )
{
   char mynewcmd[MAXWORD] ;
   geta(mynewcmd) ;
   newfile(mynewcmd,1) ;
   return(0);
}
