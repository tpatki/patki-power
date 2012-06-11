#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void unsetio( void )
{
   if (iomrkrset == 1)
      {
      line = lnbuf ;
      ps = iomrkps ;
      }
   iomrkflag = 0 ;
}
