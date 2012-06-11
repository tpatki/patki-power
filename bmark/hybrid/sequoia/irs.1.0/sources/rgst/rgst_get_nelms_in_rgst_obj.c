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
int rgst_get_nelms_in_rgst_obj (
  RGST_Object_t *ro,	    
  long *ret_dim_nelms,	    
  long *ret_ptr_nelms,	    
  long *ret_nelms)	    
{
  char *me = "rgst_get_nelms_in_rgst_obj";
  int i;
  long dim_nelms, ptr_nelms, nelms;
  dim_nelms = ptr_nelms = -1;
  if (ro->array_size_type == FIELD_OFFSET) {
    ctlerror(me,"Shawn hasn't coded this logic yet");
  }
  else if (ro->array_size_type == GLOBAL_VAR) {
    ptr_nelms = rgst_get_long(ro->array_size_global_var);
    nelms     = ptr_nelms;
  }
  else if (ro->array_size_type == ABSOLUTE_VALUE) {
    ptr_nelms = ro->array_size_absolute_val;
    nelms     = ptr_nelms;
  }
  else {
    dim_nelms = 1;
    for (i=0; i<ro->ndims; i++) {
      dim_nelms = dim_nelms * ro->dims[i];
    }
    nelms = dim_nelms;
  }
  *ret_dim_nelms = dim_nelms;
  *ret_ptr_nelms = ptr_nelms;
  *ret_nelms     = nelms;
  return(0);
}
