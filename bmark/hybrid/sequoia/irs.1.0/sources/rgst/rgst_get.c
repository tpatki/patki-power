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
void *rgst_get(char *name)      
{
  char *me = "rgst_get";
  char  msg[256];
  RGST_Object_t *rgst_obj;  
  if ((rgst_obj = hash_lookup_obj(name, rgst_objs_hash_tbl)) == NULL) {
    sprintf(msg,"Object '%s' is not in the objects registry",name);
    ctlwarning(me,msg);
    return(NULL);
  }
  return(rgst_obj->obj); 
}
