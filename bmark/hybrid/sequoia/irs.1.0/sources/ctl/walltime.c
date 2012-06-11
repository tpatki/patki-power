#include "irs.h"
#include "irscom.h"
#include "irsctl.h"
#include "irssys.h"
#include "FunctionTimer.h"
#include "AEStackElm.h"
int walltime( void ) 
{
   char *me = "walltime";
   double runtime;
   runtime = getruntime();
   if (ifparallel) {
      comreduce(&runtime, 1 , COM_MAX, COM_ALL, COM_DOUBLE);
   }
   ctloutput(me,"walltime",R_DOUBLE,runtime);
   return(0);
}
