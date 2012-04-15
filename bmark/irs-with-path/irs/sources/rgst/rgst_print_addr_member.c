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
int rgst_print_addr_member (
  void          *sp,            
  char          *usertype,      
  char          *str,           
  char          *in_label)	
{
  char *me = "rgst_print_addr_member";
  char fld_name[128], msg[256], label[256];
  void *fp;
  long dim_nelms, ptr_nelms, nelms, ndx, array_size;
  long i, lo_ndx, hi_ndx, my_lo_ndx, my_hi_ndx;
  int  err;
  char *next_fld_str_ptr;
  ARRAY_SIZE_ENUM array_size_type;
  RGST_StructTypeDef_t *sd = NULL;
  RGST_Object_t *ro = NULL;
  RGST_Field_t *fd = NULL;
  unsigned char *ptr;
  memset (fld_name,'\0',128);
  if ((next_fld_str_ptr = strchr(str,'.')) == NULL)  {
    strncpy(fld_name,str,127);
  }
  else {
    ndx = (long)next_fld_str_ptr - (long)str;
    strncpy(fld_name, str, ndx);
    next_fld_str_ptr++;
  }
  if (rgst_extract_array_ndxs(&fld_name[0], &lo_ndx, &hi_ndx) != 0) { 
    return(-1);
  }
  if ((fp = rgst_get_field_addr(sp, usertype, fld_name, &fd)) == NULL) {
    return(-1); 
  }
  if (next_fld_str_ptr != NULL) {
    if ((fd->type == R_STRUCT) || (fd->type == R_STRUCT_TYPEDEF)) {
      if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(usertype,R_STRUCT_TYPEDEF,NULL)) == NULL) 
        return(-1);
      if (rgst_get_nelms_in_field(sp,sd,fd,&dim_nelms,&ptr_nelms, &nelms) != 0)
        return(-1);
      if (rgst_check_ndxs (nelms, lo_ndx, hi_ndx, &my_lo_ndx, &my_hi_ndx) != 0)
        return(-1);
      err = 0;
      for (i=my_lo_ndx; i<=my_hi_ndx; i++) {
	sprintf(label,"%s%s[%d].",in_label,fld_name,(int)i);
	ptr = rgst_get_field_array_elm_ptr(fp, fd, dim_nelms, ptr_nelms, i);
	if (ptr != NULL) {
          err += rgst_print_addr_member(ptr,fd->td_name,next_fld_str_ptr,label);
        }
      }
      return(err);
    }
    else {
      sprintf(msg,"Field '%s' is not a structure, it is a '%s'"
                  "Cannot print field '%s' of a non-structure",
                  fld_name,rgst_datatype_strs[fd->type],next_fld_str_ptr);
      ctlnotice(me,msg);
    }
  }
  else {
    if ((fd->type == R_STRUCT) || (fd->type == R_STRUCT_TYPEDEF)) {
      if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(fd->td_name,R_STRUCT_TYPEDEF,NULL)) == NULL) 
        return(-1);
      if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(usertype,R_STRUCT_TYPEDEF,NULL)) == NULL) 
        return(-1);
      array_size = rgst_get_field_array_size(sp, sd, fd);
      array_size_type = NUM_ARRAY_SIZE_ENUM;
      if (array_size != -1) {
        array_size_type = ABSOLUTE_VALUE;
      }
      ro = RGST_Object_create(fd->name, fd->td_name, fd->type, 
                              fd->nptrs, fd->ndims, fd->dims, fp, 
                              array_size_type, -1, -1, NULL, array_size);
      rgst_get_nelms_in_rgst_obj(ro, &dim_nelms, &ptr_nelms, &nelms);
      printf("%s",in_label);
      rgst_print_structs(ro, dim_nelms, ptr_nelms, lo_ndx, hi_ndx);
      RGST_Object_destruct(ro);
    }
    else {
      if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(usertype,R_STRUCT_TYPEDEF,NULL)) == NULL) 
        return(-1);
      printf("%s",in_label);
      rgst_print_field(sp, sd, fp, fd, lo_ndx, hi_ndx);
    }
  }
  return(0);
}
