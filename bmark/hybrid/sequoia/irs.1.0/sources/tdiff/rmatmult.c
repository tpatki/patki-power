#include "irs.h"
#include "irstdiff.h"
#include "irscom.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rmatmult( Domain_t *domain,   RadiationData_t *rblk,
               double   *x,      double *y     )
{
   if ( ndims == 2 ) {
      rmatmult2(domain,rblk,x,y) ;
   } else {
      rmatmult3(domain,rblk,x,y) ;
   }
}
