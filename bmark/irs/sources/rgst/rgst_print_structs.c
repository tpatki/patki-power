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
void rgst_print_structs (
  RGST_Object_t *ro, 	        
  long        dim_nelms, 
  long        ptr_nelms,
  long        lo_ndx,
  long        hi_ndx) 
{
  char *me = "rgst_print_structs";
  char *errmsg1 = "\n\tProgrammer Error : "
                  "\n\tEither dim_nelms or ptr_nelms is to be used"
		  "\n\tOne must be -1 and the other must be 0 or greater";
  long i, my_lo_ndx, my_hi_ndx, nelms;
  RGST_StructTypeDef_t *sd = NULL;
  unsigned char *ptr;
  if (ro->obj == NULL) return;
  if (dim_nelms > -1) {
    if (ptr_nelms != -1) ctlerror(me,errmsg1);
    nelms = dim_nelms;
  }
  else if (ptr_nelms > -1) {
    if (dim_nelms != -1) ctlerror(me,errmsg1);
    nelms = ptr_nelms;
  }
  else {
    ctlerror(me,errmsg1);
  }
  if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(ro->usertype,R_STRUCT_TYPEDEF,NULL)) == NULL) 
    return;
  if (rgst_check_ndxs (nelms, lo_ndx, hi_ndx, &my_lo_ndx, &my_hi_ndx) != 0)
    return;
  printf("%s is composed of %d '%s' structures\n",
         ro->name,(int)nelms,ro->usertype);
  for (i=my_lo_ndx; i<=my_hi_ndx; i++) {
    printf("\nStruct %d\n",(int)i);
    ptr = rgst_get_struct_array_elm_ptr(ro, sd, dim_nelms, ptr_nelms, i);
    rgst_print_struct(ptr, sd);
  }
}
