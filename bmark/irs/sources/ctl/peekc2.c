#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void peekc2( char     *s )
{
   nxtsym(0) ;
   if (symflag == 1) strcpy(s,sym) ;
   else              strcpy(s,"*") ;
   return;
}
