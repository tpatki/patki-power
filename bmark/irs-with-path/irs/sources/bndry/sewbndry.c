#include "irs.h"
#include "irsbndry.h"
#include "irscom.h"
#include "FunctionTimer.h"
void sewbndry(void)
{
   int iblk;
   int gblk;
   for (iblk = 0; iblk < nblk; iblk++) {
      gblk = domains[iblk].gblk;
      varcomset(domains[iblk].x,-1,"x",COM_DOUBLE,COM_LAYER1N,COM_OVR,gblk);
      varcomset(domains[iblk].y,-1,"y",COM_DOUBLE,COM_LAYER1N,COM_OVR,gblk);
      if (ndims == 3) {
         varcomset(domains[iblk].z,-1,"z",COM_DOUBLE,COM_LAYER1N,COM_OVR,gblk);
      }
   }
   varcom(COM_SET_SIZE);
   varcom(COM_SEND_RECV);
}
