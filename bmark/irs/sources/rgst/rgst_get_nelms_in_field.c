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
int rgst_get_nelms_in_field (
  unsigned char       *sp,  
  RGST_StructTypeDef_t *sd,  
  RGST_Field_t          *fd,  
  long *ret_dim_nelms,	    
  long *ret_ptr_nelms,	    
  long *ret_nelms)	    
{
  char *me = "rgst_get_nelms_in_field";
  int i;
  long dim_nelms, ptr_nelms, nelms;
  dim_nelms = ptr_nelms = -1;
  ptr_nelms = rgst_get_field_array_size(sp, sd, fd);
  if (ptr_nelms > -1) {
    nelms = ptr_nelms;
  }
  else {
    dim_nelms = 1;
    for (i=0; i<fd->ndims; i++) dim_nelms = dim_nelms * fd->dims[i];
    nelms = dim_nelms;
  }
  if (ret_dim_nelms != NULL) *ret_dim_nelms = dim_nelms;
  if (ret_ptr_nelms != NULL) *ret_ptr_nelms = ptr_nelms;
  if (ret_nelms     != NULL) *ret_nelms     = nelms;
  return(0);
}
