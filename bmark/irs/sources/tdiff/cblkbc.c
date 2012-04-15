#include "irs.h"
#include "irstdiff.h"
#include "RadiationData.h"
void cblkbc( RadiationData_t *cblk, Domain_t *domain )
{
   setpz1(cblk->ccc,0.0,domain) ;
   setpz2(cblk->ccc,0.0,domain) ;
   if ( domain->nbc > 0 )
   {
      if ( ndims == 2 )
      {
         cblkbc2(cblk,domain) ;
      }
      else
      {
         cblkbc3(cblk,domain) ;
      }
   }      
}
