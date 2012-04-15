#include "irs.h"
#include "FunctionTimer.h" 
#include "irscom.h"
void swapcoords(void)
{
   int iblk;
   int gblk;
   for (iblk = 0; iblk < nblk; iblk++) {
      gblk = domains[iblk].gblk;
      varcomset(domains[iblk].x,-1,"x",COM_DOUBLE,COM_LAYER2NC,COM_NOOP,gblk);
      varcomset(domains[iblk].y,-1,"y",COM_DOUBLE,COM_LAYER2NC,COM_NOOP,gblk);
      if (ndims == 3) {
         varcomset(domains[iblk].z,-1,"z",COM_DOUBLE,COM_LAYER2NC,COM_NOOP,gblk);
      }
   }
   varcom(COM_SET_SIZE);
   varcom(COM_SEND_RECV);
}
