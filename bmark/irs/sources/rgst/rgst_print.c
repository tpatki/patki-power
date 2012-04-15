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
int rgst_print (
  char *name,	
  long lo_ndx,	
  long hi_ndx)  
{
  long dim_nelms, ptr_nelms, nelms, my_lo_ndx, my_hi_ndx;
  RGST_Object_t *rgst_obj = NULL;
  if ((rgst_obj = rgst_get_RGST_Object_t(name)) == NULL) return(-1);
  rgst_get_nelms_in_rgst_obj(rgst_obj, &dim_nelms, &ptr_nelms, &nelms);
  if (rgst_check_ndxs(nelms,lo_ndx,hi_ndx,&my_lo_ndx,&my_hi_ndx) != 0) 
    return(-1);
  rgst_print_obj(rgst_obj, dim_nelms, ptr_nelms, nelms, my_lo_ndx, my_hi_ndx);
  return(0);
}
