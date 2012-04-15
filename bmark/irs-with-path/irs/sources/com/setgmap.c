#include "irs.h"
#include "BlockMapping.h"
#include "BndMapping.h"
#include "Extents.h"
#include "FunctionTimer.h" 
#include "irscom.h"
void setgmap(int ublk, Extents_t ext) {
   gmap[gnblk].ublk=ublk;
   gmap[gnblk].lblk=gnblk;
   gmap[gnblk].gblk=gnblk;
   gmap[gnblk].proc=myid;
   gmap[gnblk].imax=ext.imax;
   gmap[gnblk].jmax=ext.jmax;
   gmap[gnblk].kmax=ext.kmax;
   gmap[gnblk].imin=ext.imin;
   gmap[gnblk].jmin=ext.jmin;
   gmap[gnblk].kmin=ext.kmin;
   STREXT(gmap[gnblk],gmap[gnblk].jp,gmap[gnblk].kp);
   if (ndims == 2) {
      gmap[gnblk].kp =0;
   }
   if (gmap[gnblk].nbnd < 0) {
      gmap[gnblk].bnd = ALLOT(BndMapping_t,nbndx);
      gmap[gnblk].nbnd = 0;
   }
   gnblk++;
}
