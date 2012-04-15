#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "Rgst.h"
#include "irsrgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE  1
#endif
int * rgst_get_field_array_sizes(
  unsigned char        *sptr,    
  RGST_StructTypeDef_t *sd,      
  RGST_Field_t         *fd)      
{
  unsigned char *ptr;
  RGST_Field_t    *array_size_fd;
  int *sizes = NULL;
  if      (fd->array_size_type == FIELD_OFFSET) {
    array_size_fd  = &(sd->fields[fd->array_size_field]);
    ptr            = sptr + array_size_fd->offset;
    if (array_size_fd->ndims > 0)  {
      if (array_size_fd->nptrs == 0) {
	sizes = (int *)ptr;
      }
    }
  }
  return(sizes);
}
