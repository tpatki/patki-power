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
int rgst_del(char *name)      
{
  char *me = "rgst_del";
  char  msg[256], **attrs;
  int   i, num_attrs;
  RGST_Object_t *ro;
  if ((ro = hash_lookup_obj(name, rgst_objs_hash_tbl)) == NULL) {
    sprintf(msg,"Attempt to delete object '%s' which is not in the registry",name);
    ctlnotice(me,msg);
    return(-1);
  }
  else {
    num_attrs = ro->attributes->num_attrs;
    attrs = ALLOT(char *, num_attrs);
    for (i=0; i<num_attrs; i++) {
      attrs[i] = strsave(ro->attributes->attrs[i]->attr_name);
    }
    if (ro->attributes != NULL) {
      for (i=0; i<num_attrs; i++) {
        rgst_del_attr(A_OBJECT, ro->name, attrs[i]); 
      }
    }
    for (i=0; i<num_attrs; i++) { FREEMEM(attrs[i]); }
    FREEMEM(attrs);
    hash_del(name,rgst_objs_hash_tbl);
    RGST_Object_destruct(ro);
    return(0);
  }
}
