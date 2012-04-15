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
long rgst_get_field_array_size(
  unsigned char         *sptr,    
  RGST_StructTypeDef_t  *sd,      
  RGST_Field_t          *fd)      
{
  char *me = "rgst_get_field_array_size";
  unsigned char *ptr;
  char *str;
  RGST_Field_t	*array_size_fd;
  long size = -1;
  if      (fd->array_size_type == FIELD_OFFSET) {
    array_size_fd  = &(sd->fields[fd->array_size_field]);
    ptr            = sptr + array_size_fd->offset;
    if (array_size_fd->ndims == 0) {
      if (array_size_fd->nptrs == 0) {
        if      (array_size_fd->type == R_INT)  size = (long)(*(int  *)ptr);
        else if (array_size_fd->type == R_LONG) size = (long)(*(long *)ptr);
      }
      else if (array_size_fd->nptrs == 1) {
        if      (array_size_fd->type == R_INT)  size = (long)(**(int  **)ptr);
        else if (array_size_fd->type == R_LONG) size = (long)(**(long **)ptr);
      }
    }
  }
  else if (fd->array_size_type == GLOBAL_VAR) {
    size = rgst_get_long(fd->array_size_global_var);
  }
  else if (fd->array_size_type == ABSOLUTE_VALUE) {
    size = fd->array_size_absolute_val;
  }
  else {
    if (fd->type == R_CHAR) {
      if ((fd->nptrs == 1) && (fd->ndims == 0)) {
        ptr =sptr + fd->offset;
        str = *(char **)ptr;
        if (str != NULL) 
            size = strlen(str) + 1;
      }
    }
  }
  return(size);
}
