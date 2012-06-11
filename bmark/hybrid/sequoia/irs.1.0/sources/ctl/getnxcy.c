#include <signal.h>
#include "irs.h"
#include "irsctl.h"
#include "Conditional.h"
#include "CycleMesg.h"
int  getnxcy(void)
{
  int i;
  int ncond;
  int nxcy = cstop;
  ncond = conditionals_check();
  if (ncond > 0) {
     nxcy = cycle + 1;
  }
  for (i=0 ; i<ncyc ; i++) {
    if (cyc[i].nextCycle <= nxcy) { nxcy = cyc[i].nextCycle; } 
  }
  return(nxcy) ;
}
