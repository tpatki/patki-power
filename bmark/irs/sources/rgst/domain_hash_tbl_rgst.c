#include <stdlib.h>                     
#include "irs.h"
#include "irsctl.h"
#include "Hash.h"
#include "Rgst.h"
#include "irsrgst.h"
int domain_hash_tbl_rgst(
  Domain_t *domain)             
{
  char *me = "domain_hash_tbl_rgst";
  char msg[128];
  if (domain->hash == NULL) {
    return(0);
  }
  sprintf(msg,"domain_%d_hash_tbl",domain->gblk);
  hash_tbl_rgst(&(domain->hash), msg);
  return(0);
}
