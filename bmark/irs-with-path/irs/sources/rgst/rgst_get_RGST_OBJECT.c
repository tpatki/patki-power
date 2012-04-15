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
RGST_Object_t *rgst_get_RGST_Object_t(
  char *name) 
{
  char *me = "rgst_get_RGST_Object_t";
  char  msg[256];
  RGST_Object_t *rgst_obj;
  if ((rgst_obj = hash_lookup_obj(name, rgst_objs_hash_tbl)) == NULL) {
    sprintf(msg,"Object '%s' is not in the objects registry",name);
    ctlnotice(me,msg);
  }
  return(rgst_obj); 
}
