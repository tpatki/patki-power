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
void * rgst_get_field_addr(
  void *obj_ptr,    
  char *type_name,  
  char *fld_name,   
  RGST_Field_t **fd)  
{
  int   ndx;
  RGST_StructTypeDef_t *sd = NULL;
  void *fld_ptr;
  long obj_address, fld_address;
  if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(type_name,R_STRUCT_TYPEDEF,NULL)) == NULL) { 
    return(NULL); 
  }
  if ((ndx = rgst_get_ds_field_ndx(sd, fld_name)) < 0) { 
    return(NULL); 
  }
  obj_address = (long)obj_ptr;
  fld_address = obj_address + sd->fields[ndx].offset;
  fld_ptr     = (void *)fld_address;
  if (fd != NULL) *fd = &(sd->fields[ndx]);
  return(fld_ptr);
}
