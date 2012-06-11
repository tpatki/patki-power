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
void rgst_print_struct (
  unsigned char *sptr,          
  RGST_StructTypeDef_t *sd)      
{
  int i;
  unsigned char *offset;        
  RGST_Field_t    *fd;            
  if (sptr == NULL) return;
  for (i=0; i<sd->num_fields; i++) {
    fd = &(sd->fields[i]);
    offset = sptr + (fd->offset);
    rgst_print_field (sptr, sd, offset, fd, -1, -1);
  }
}
