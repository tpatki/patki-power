#include "irs.h"
#include "irslag.h"
#include "irsctl.h"
#include "TimeStepControl.h"
int printtc( void )
{
   char msg[256];
   if (ndims == 2) {
      sprintf(msg,"time = %e cycle = %d subcycle = %d dt%s:%d(%d,%d) = %e",
                   ttime, cycle, subcycle, dtcon, dtb,
                   dti-NPNL+1, dtj-NPNL+1, deltat) ;
      ctlmsg(msg);
   }
   if (ndims == 3) {
      sprintf(msg,"time = %e cycle = %d subcycle = %d dt%s:%d(%d,%d,%d) = %e",
                   ttime, cycle, subcycle, dtcon, dtb,
                   dti-NPNL+1, dtj-NPNL+1, dtk-NPNL+1, deltat) ;
      ctlmsg(msg);
   }
   return(0);
}
