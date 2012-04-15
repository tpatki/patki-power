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
unsigned char * rgst_get_struct_array_elm_ptr (
  RGST_Object_t         *ro,        
  RGST_StructTypeDef_t *sd,        
  long                 dim_nelms, 
  long                 ptr_nelms,  
  long                 ndx)       
{
  char *me = "rgst_get_struct_array_elm_ptr";
  unsigned char *ptr, *ptr2, **ptrptr;
  if (ro->nptrs == 0) {
    ptr = ((unsigned char *)ro->obj) + (ndx * sd->struct_size);
  }
  else if (ro->nptrs == 1) {
    if (ptr_nelms > -1) {
      ptr2 = *((unsigned char **)ro->obj);
      if (ptr2 == NULL) return(NULL);
      ptr = ptr2 + (ndx * sd->struct_size);
    }
    else {
      ptrptr = ((unsigned char **)ro->obj);
      if (ptrptr == NULL) return(NULL);
      ptrptr += ndx * sizeof(unsigned char **);
      ptr = *ptrptr;
    }
  }
  else if (ro->nptrs == 2) {
    ptrptr = *((unsigned char ***)ro->obj);
    if (ptrptr == NULL) return(NULL);
    ptr2 = *ptrptr;
    if (ptr2 == NULL) return(NULL);
    if (ptr_nelms > -1) {
      ptr = ptr2 + (ndx * sd->struct_size);
    }
    else {
      ptr = ptr2 + (ndx * sd->struct_size);
    }
    ctlnotice(me,"Shawn not sure here yet--further testing adviseable");
  }
  else {
    ctlerror(me,"PROGRAMMER ERROR: nptrs > 2");
  }
  return(ptr);
}
