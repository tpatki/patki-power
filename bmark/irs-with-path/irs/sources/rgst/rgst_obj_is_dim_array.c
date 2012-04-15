#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int rgst_obj_is_dim_array (RGST_Object_t *ro)
{
  if (ro->ndims > 0) { return (TRUE); }
  else               { return(FALSE); }
}
