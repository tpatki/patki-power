#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void endout( void )
{
   if (fpout != NULL) {
     fclose(fpout) ;
   }
   return ;
}
