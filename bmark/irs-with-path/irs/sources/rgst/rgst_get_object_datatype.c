#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
RGST_Datatype_t rgst_get_object_datatype (char *name)
{
  RGST_Object_t *rgst_obj;
  if ((rgst_obj = rgst_get_RGST_Object_t(name)) == NULL) {
    return(NUM_RGST_Datatype_t);
  }
  return(rgst_obj->datatype); 
}
