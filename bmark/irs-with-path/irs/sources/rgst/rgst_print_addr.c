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
int rgst_print_addr (
  long addr,            
  char *type)           
{
  char *me = "rgst_print_addr";
  char msg[256];
  int  i, dims[3];
  long dim_nelms, ptr_nelms, nelms;
  void *ptr;
  HashElm_t *hash_elm = NULL;
  RGST_Object_t   *ro;
  RGST_Datatype_t dt;
  ptr = (void *)addr;
  hash_elm = hash_lookup_elm(type, rgst_types_hash_tbl);
  if (hash_elm == NULL) {
    sprintf(msg,"Type '%s' is not in the registry",type);
    ctlnotice(me,msg);
    return(-1);
  }
  for (i=0; i<NUM_RGST_Datatype_t; i++) {
    if (strcmp(hash_elm->type, rgst_datatype_strs[i]) == 0) {
      dt = (RGST_Datatype_t) i;
      break;
    }
  }
  if (i >= NUM_RGST_Datatype_t)
    ctlerror(me,"Programmer Error - hash_elm->type is bad");
  sprintf(msg,"memory address '%ld'",(long)ptr);
  dims[0] = dims[1] = dims[2] = 0;
  ro = RGST_Object_create(msg, type, dt, 0, 0, dims, ptr, 
                          NUM_ARRAY_SIZE_ENUM,-1,-1,NULL,-1);
  dim_nelms =  1;
  ptr_nelms = -1;
  nelms     =  1;
  rgst_print_obj(ro, dim_nelms, ptr_nelms, nelms, 0, 0);
  RGST_Object_destruct(ro);
  return(0);
}
