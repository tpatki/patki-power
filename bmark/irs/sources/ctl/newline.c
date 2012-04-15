#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void newline( void )
{
   if (iflf) {
      ps      = NULL ;
      symflag = 0 ;
   }
}
