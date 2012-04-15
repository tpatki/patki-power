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
void *rgst_get_t(
  char *name,      
  char *type)      
{
  RGST_Object_t *ro;
  char type_str[128];
  int  i, nptrs, myndims, dims[3];
  strncpy(type_str,type,127);
  if ((ro = hash_lookup_obj(name, rgst_objs_hash_tbl)) == NULL) {
    return(NULL);
  }
  rgst_get_dims_of_type(type_str,&nptrs,&myndims,&dims[0]);
  if (    (strcmp(ro->usertype,type_str) != 0) 
       || (ro->nptrs != nptrs)
       || (ro->ndims != myndims) ) {
    return(NULL);
  }
  for (i=0; i<myndims; i++) {
    if (ro->dims[i] != dims[i]) { 
      return(NULL); 
    }
  }
  return(ro->obj);
}
