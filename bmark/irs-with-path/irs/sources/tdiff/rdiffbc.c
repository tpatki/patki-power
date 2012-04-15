#include "irs.h"
#include "irscom.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rdiffbc( RadiationData_t *rblk,   DiffusionData_t *tblk,   Domain_t *domain )
{
   if ( domain->nbc > 0 ) {
      if ( ndims == 2 ) {
         rdiffbc2(rblk,tblk,domain) ;
      } else {
         rdiffbc3(rblk,tblk,domain) ;
      }
   }      
}
