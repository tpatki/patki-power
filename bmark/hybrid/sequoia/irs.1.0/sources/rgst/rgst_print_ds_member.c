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
int rgst_print_ds_member (
  char *str)           
{
  char *me = "rgst_print_ds_member";
  char name[128], msg[256], label[256];
  int  err;
  long i, ndx, lo_ndx, hi_ndx;
  long my_lo_ndx, my_hi_ndx;
  long dim_nelms, ptr_nelms;
  long nelms;
  unsigned char *ucptr;		   
  char *fldptr;                    
  RGST_Object_t *ro = NULL;
  RGST_StructTypeDef_t *sd = NULL;
  if ((fldptr = strchr(str,'.')) == NULL)
    ctlerror(me,"PROGRAMER ERROR: '.' not found in string");
  ndx = (long)fldptr - (long)str;
  memset (name,'\0',128);
  strncpy(name, str, ndx);
  fldptr++;
  if (rgst_extract_array_ndxs(&name[0], &lo_ndx, &hi_ndx) != 0) {
    return(-1);
  }
  if ((ro = rgst_get_RGST_Object_t(name)) == NULL) return(-1);
  if ((ro->datatype != R_STRUCT) && (ro->datatype != R_STRUCT_TYPEDEF)) {
    sprintf(msg,"\n\tObject '%s' is not a structure, it is a '%s'"
                "\n\tCan't print field of a non-structure object",
                name,rgst_datatype_strs[ro->datatype]);
    ctlnotice(me,msg);
    return(-1);
  }
  if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(ro->usertype,R_STRUCT_TYPEDEF,NULL)) == NULL) 
    return(-1);
  rgst_get_nelms_in_rgst_obj(ro, &dim_nelms, &ptr_nelms, &nelms);
  if (rgst_check_ndxs (nelms,lo_ndx,hi_ndx,&my_lo_ndx,&my_hi_ndx) != 0)
    return(-1);
  err = 0;
  for (i=my_lo_ndx; i<=my_hi_ndx; i++) {
    sprintf(label,"\n%s[%d].",name,(int)i);
    ucptr = rgst_get_struct_array_elm_ptr(ro, sd, dim_nelms, ptr_nelms, i);
    err += rgst_print_addr_member(ucptr, ro->usertype, fldptr, label);
  }
  return(err);
}
