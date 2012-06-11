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
unsigned char * rgst_get_field_array_elm_ptr (
  unsigned char  *fp,	     
  RGST_Field_t     *fd,	     
  long            dim_nelms, 
  long            ptr_nelms, 
  long            ndx)	     
{
  char *me = "rgst_get_field_array_elm_ptr";
  unsigned char *ptr, *ptr2, **ptrptr;
  long type_size;
  RGST_StructTypeDef_t *sd = NULL;
  if ((fd->type == R_STRUCT) || (fd->type == R_STRUCT_TYPEDEF)) {
    if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(fd->td_name,R_STRUCT_TYPEDEF,NULL)) == NULL) {
      return(NULL);
    }
    type_size = sd->struct_size;
  }
  else {
    type_size = fd->type_size;
  }
  if (fd->nptrs == 0) {
    ptr = fp + (ndx * type_size);
  }
  else if (fd->nptrs == 1) {
    if (ptr_nelms > -1) {
      ptr2 = *((unsigned char **)fp);
      if (ptr2 == NULL) return(NULL);
      ptr = ptr2 + (ndx * type_size);
    }
    else {
      ptrptr = ((unsigned char **)fp);
      if (ptrptr == NULL) return(NULL);
      ptrptr += ndx * sizeof(unsigned char **);
      ptr = *ptrptr;
    }
  }
  else if (fd->nptrs == 2) {
    ptrptr = *((unsigned char ***)fp);
    if (ptrptr == NULL) return(NULL);
    ptr2 = *ptrptr;
    if (ptr2 == NULL) return(NULL);
    if (ptr_nelms > -1) {
      ptr = ptr2 + (ndx * type_size);
    }
    else {
      ptr = ptr2 + (ndx * type_size);
    }
    ctlnotice(me,"Shawn not sure here yet--further testing adviseable");
  }
  else {
    ctlerror(me,"PROGRAMMER ERROR: nptrs > 2");
  }
  return(ptr);
}
