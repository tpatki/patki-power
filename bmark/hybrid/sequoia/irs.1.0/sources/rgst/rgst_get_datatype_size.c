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
size_t rgst_get_datatype_size(
  RGST_Datatype_t type, 
  char *struct_name)  
{
  char *me = "rgst_get_datatype_size";
  size_t size;
  RGST_StructTypeDef_t *sd;
  if ((type >= R_CHAR) && (type <= R_DOUBLE)) {
    size = (size_t)rgst_datatype_sizes[type];
  }
  else if ((type == R_STRUCT) || (type == R_STRUCT_TYPEDEF)) {
    sd = rgst_get_RGST_StructTypeDef_t(struct_name);
    if (sd == NULL) ctlerror(me,logic_err);
    size = (size_t)sd->struct_size;
  }       
  else {
    ctlerror(me,gv_errmsg_not_done);
  }
  return(size);
}
