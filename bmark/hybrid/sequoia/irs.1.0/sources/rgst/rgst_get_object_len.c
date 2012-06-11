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
long rgst_get_object_len(char *name)	
{
  char *me = "rgst_get_object_len";
  char msg[256];
  RGST_Object_t *ro;
  long len;
  if (rgst_check_for_obj(name)  != TRUE) {
    sprintf(msg,"'%s' is not a registry object",name);
    ctlnotice(me,msg);
    return(-1);
  }
  if ((ro = rgst_get_RGST_Object_t(name)) == NULL) {
    ctlerror(me,logic_err);
  }
  len = rgst_get_ro_len(ro);                                                                                                
  return(len);
}
long rgst_get_ro_len(RGST_Object_t *ro)      
{
  char *me = "rgst_get_ro_len";
  char msg[256];
  long len, i;
  if (ro->ndims > 0) {
    if (ro->nptrs != 0) {
      sprintf(msg,"\n\tRegistry object '%s' has %d ptrs and %d dims"
                  "\n\tCan't return the length of this object",
                  ro->name,ro->nptrs,ro->ndims);
      ctlwarning(me,msg);
      return(-1);
    }
    len = 1;
    for (i=0; i<ro->ndims; i++) {
      len = len * ro->dims[i];
    }
  }
  else {
    if      (ro->nptrs == 0) {
      len = 1;
    }
    else if (ro->nptrs == 1) {
      if      (ro->array_size_type == GLOBAL_VAR) {
        len = rgst_get_long(ro->array_size_global_var);
      }
      else if (ro->array_size_type == ABSOLUTE_VALUE) {
        len = ro->array_size_absolute_val;
      }
      else {
        len = 1;
      }
    }
    else {
      sprintf(msg,"\n\tRegistry object '%s' has %d ptrs"
                  "\n\tCan't return the length of this object",
                  ro->name,ro->nptrs);
      ctlwarning(me,msg);
      return(-1);
    }
  }
  return(len);
}
