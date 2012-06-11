#include <signal.h>
#include "irs.h"
#include "irsctl.h"
int  ifnotin( char *d, char *ps )
{
   int fg ;
   fg = 1 ;
   while (*d != '\0') {
      if (*(d++) == *ps) {
         fg = 0 ;
         break ;
      }
   }
   if (*ps == '\0') {
      fg = 0 ;
   }
   return(fg) ;
}
