#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "Rgst.h"
#include "irsrgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int rgst_check_for_td_defn(char *name) 
{
  if (hash_lookup_elm(name, rgst_types_hash_tbl) == NULL) return(FALSE);
  else                                                    return(TRUE);
}
