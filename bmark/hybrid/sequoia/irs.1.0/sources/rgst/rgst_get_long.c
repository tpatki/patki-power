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
long rgst_get_long(
  char *name)  
{
  char *me = "rgst_get_long"; 
  char msg[128];
  RGST_Object_t *ro;
  long my_long;
  if (name == NULL) { 
    ctlerror(me,"name passed into routine is NULL");
  }
  if ((ro = hash_lookup_obj(name, rgst_objs_hash_tbl)) == NULL) {
    sprintf(msg,"Object '%s' is not in the objects registry",name);
    ctlerror(me,msg);
  }
  if ( (ro->nptrs == 0) && (ro->ndims == 0) ) {
    if      (ro->datatype == R_INT)           my_long = (long)(*((int *)          ro->obj));
    else if (ro->datatype == R_UNSIGNED_INT)  my_long = (long)(*((unsigned int *) ro->obj));
    else if (ro->datatype == R_LONG)          my_long = (long)(*((long *)         ro->obj));
    else if (ro->datatype == R_UNSIGNED_LONG) my_long = (long)(*((unsigned long *)ro->obj));
    else {
      sprintf(msg,"Object '%s' is of type '%s' which cannot be converted to long",
                   name,rgst_datatype_strs[ro->datatype]);
      ctlerror(me,msg);
    }
  } 
  else {
    sprintf(msg,"Object '%s' cannot be converted to long because it is a ptr"
                "or an array",
                name);
    ctlerror(me,msg);
  }
  return(my_long);
}
