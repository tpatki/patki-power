#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void resetio( void )
{
   iomrkflag = 0 ;
   if (iomrkrset == 0) iomrkps = ps ;
   line = iomrkstr ;
   ps = line ;
   iomrkrset = 1 ;
   symflag = 0 ;
}
