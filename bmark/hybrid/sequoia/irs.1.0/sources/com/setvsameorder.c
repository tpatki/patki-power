#include "irs.h"
#include "irscom.h"
#include "FunctionTimer.h" 
#include "Tagorder.h"
void setvsameorder(void)
{
   int iblk;
   int ibc;
   int id;
   int count;
   for (id = 0; id < vsame_max_id; id++) {
      if ( vsame_order[id].len > 0 ) {
         FREEMEM(vsame_order[id].blk);
         FREEMEM(vsame_order[id].tag);
      }
      vsame_order[id].len = 0;
   }
   count = 0;
   for (id = 1; id <= vsame_max_id; id++) {
      count = 0;
      for (iblk=0;iblk<nblk;iblk++) {
         for (ibc=0;ibc<domains[iblk].nbc;ibc++) {
            if (domains[iblk].bc[ibc].id == id) {
               count++;
            }
         }
      }
      vsame_order[id-1].len = count;
      vsame_order[id-1].blk = ALLOT(int,count);
      vsame_order[id-1].tag = ALLOT(int,count);
      count = 0;
      for (iblk=0;iblk<nblk;iblk++) {
         for (ibc=0;ibc<domains[iblk].nbc;ibc++) {
            if (domains[iblk].bc[ibc].id == id) {
               vsame_order[id-1].blk[count] = iblk;
               vsame_order[id-1].tag[count] = ibc;
               count++;
            }
         }
      }
   }
}
