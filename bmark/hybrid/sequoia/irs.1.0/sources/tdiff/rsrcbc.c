#include "irs.h"
#include "irscom.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rsrcbc( RadiationData_t *rblk,   DiffusionData_t *tblk,   Domain_t *domain )
{
   if ( ndims == 2 ) {
      if ( domain->nsrc > 0 ) rsrcbc2(rblk,tblk,domain) ;
      RadiationSourceBC_2d( rblk, tblk, domain);
   } else {
      if ( domain->nsrc > 0 ) rsrcbc3(rblk,tblk,domain) ;
      RadiationSourceBC_3d( rblk, tblk, domain);
   }
}
