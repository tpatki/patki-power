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
void rgst_print_field (
  unsigned char       *sptr,    
  RGST_StructTypeDef_t *sd,	
  unsigned char       *ptr,	
  RGST_Field_t          *fd,      
  long                lo_ndx,   
  long                hi_ndx)	
{
  int j, *ptr_nelms_array;
  char *me = "rgst_print_field";
  char msg[128], msg2[128];
  long i, dim_nelms, ptr_nelms;
  ptr_nelms       = rgst_get_field_array_size (sptr, sd, fd);
  ptr_nelms_array = rgst_get_field_array_sizes(sptr, sd, fd);
  dim_nelms = 1;
  for (j=0; j<fd->ndims; j++) {
    dim_nelms = dim_nelms * fd->dims[j];
  }
  strcpy(msg,fd->name);
  if ((ptr_nelms > 1) || (dim_nelms > 1)) {
    if (lo_ndx == -1) {
      strcat(msg,"[0-");
    }
    else {
      sprintf(msg2,"[%d-",(int)lo_ndx);
      strcat(msg,msg2);
    }
    if (hi_ndx == -1) {
      if (ptr_nelms > 1) sprintf(msg2,"%d]",(int)ptr_nelms-1);
      else               sprintf(msg2,"%d]",(int)dim_nelms-1);
    }
    else {
      sprintf(msg2,"%d]",(int)hi_ndx);
    }
    strcat(msg,msg2);
  }
  printf("%-20s",msg);
  if      (fd->nptrs == 0) {
    rgst_print_0_ptr_array (fd->type, fd->td_name, ptr, dim_nelms, lo_ndx, hi_ndx);
  }
  else if (fd->nptrs == 1) {
    if (ptr_nelms_array == NULL) {
      if (ptr_nelms != -1) dim_nelms = -1;
      rgst_print_1_ptr_array(fd->type, fd->td_name, ptr, dim_nelms, ptr_nelms, lo_ndx, hi_ndx);
    }
    else {
      printf("\n");
      for (i=0; i<dim_nelms; i++) {
        sprintf(msg,"%s[%d]",fd->name,(int)i);
	printf("%-20s",msg);
        rgst_print_1_ptr_array(fd->type, fd->td_name,  &(((void **)ptr)[i]), -1, ptr_nelms_array[i], lo_ndx, hi_ndx);
      }
    }
  }
  else if (fd->nptrs == 2) {
    rgst_print_2_ptr_array(fd->type, NULL, (void ***)ptr, ptr_nelms); 
  }
  else {
    ctlerror(me,"Programmer Error - npts > 2");
  }
}
