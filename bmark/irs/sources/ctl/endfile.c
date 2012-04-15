#include <signal.h>
#include "irs.h"
#include "irsctl.h"
int endfile( void )
{
   if (lastfile != 0) {
      fclose(fpin) ;
      fpin = fpold[--lastfile] ;
      if (lastfile == 0) lastfile = -1;
   }
   return(0);
}
