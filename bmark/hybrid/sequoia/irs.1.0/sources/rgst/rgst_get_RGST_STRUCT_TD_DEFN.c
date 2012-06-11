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
RGST_StructTypeDef_t *rgst_get_RGST_StructTypeDef_t(
  char *name)    
{
  char *me = "rgst_get_RGST_StructTypeDef_t";
  char msg[256];
  HashElm_t *hash_elm = NULL;
  hash_elm = hash_lookup_elm(name,rgst_types_hash_tbl);    
  if (hash_elm == NULL) {
    sprintf(msg,"Type '%s' is not defined in the registry",name);
    ctlwarning(me,msg); 
    return(NULL);
  }
  if (  (strcmp(hash_elm->type,rgst_datatype_strs[R_STRUCT])         != 0) 
     && (strcmp(hash_elm->type,rgst_datatype_strs[R_STRUCT_TYPEDEF]) != 0)) {
    sprintf(msg,"Type '%s' is not a structure, it is a '%s'",
                name,hash_elm->type);
    ctlwarning(me,msg);
    return(NULL);
  }
  return((RGST_StructTypeDef_t *)hash_elm->obj);
}
