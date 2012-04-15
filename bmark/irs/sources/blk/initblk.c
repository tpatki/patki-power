#include "irs.h"
#include "irsgen.h"
#include "irsblk.h"
void initblk( int iblk, Domain_t *domain ) {
  double dummy;
  domain_allot(domain, domain->imax - domain->imin + 1,
                       domain->jmax - domain->jmin + 1,
		       domain->kmax - domain->kmin + 1);
  domain_setpa(domain);
 ; }
