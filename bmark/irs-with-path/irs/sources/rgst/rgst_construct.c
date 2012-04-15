#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Hash.h"
#include "Command.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
void *rgst_construct(
  RGST_Datatype_t type,  
  char *struct_name,   
  int   num)           
{
  char *me = "rgst_construct";
  char *not_done = "shawn not done yet";
  char  msg[256], routine_name[128];
  int   i;
  long  long_ptr_addr;
  size_t size;
  RGST_StructTypeDef_t  *sd = NULL;     
  void     *ptr = NULL;                 
  Command_t *cp = NULL;
  void  *struct_ptr;   
  if ((type < 0) || (type >= NUM_RGST_Datatype_t)) ctlerror(me,logic_err);
  if (num < 1) ctlerror(me,logic_err);
  if ((type >= R_CHAR) && (type <= R_DOUBLE)) {
    size = (size_t)rgst_datatype_sizes[type];
    ptr = ALLOT(unsigned char, (size * num));
  }
  else if ((type == R_STRUCT) || (type == R_STRUCT_TYPEDEF)) {
    cp = build_proc_name(struct_name,"construct",routine_name);
    if (cp != NULL) {
      ptr = (void *)((*cp->proc))(num);
      if (ptr == NULL) {
        sprintf(msg,"'%s' construction routine retuned null ptr",routine_name);
        ctlerror(me,msg);
      }
    }
    else {
      size = rgst_get_datatype_size(type, struct_name);
      ptr = ALLOT(unsigned char, (size * num));
      for (i=0; i<num; i++) {
        long_ptr_addr = (long)ptr + (i * size);
        struct_ptr = (void *)long_ptr_addr;
        if (rgst_init_struct(struct_name, struct_ptr) != 0)
          ctlerror(me,logic_err);
      }
    }
  }
  else {
    ctlerror(me,gv_errmsg_not_done);
  }
  return(ptr);
}
