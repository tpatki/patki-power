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
int rgst_obj_is_ptr_array (RGST_Object_t *ro)
{
  if (  (ro->array_size_type == FIELD_OFFSET) 
     || (ro->array_size_type == GLOBAL_VAR)
     || (ro->array_size_type == ABSOLUTE_VALUE) ) { return(TRUE); }
  else                                            { return(FALSE); }
}
