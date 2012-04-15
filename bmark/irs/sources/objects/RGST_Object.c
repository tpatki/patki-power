#include <stdarg.h>
#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Rgst.h"
int RGST_Object_init(RGST_Object_t *ptr)
{
  int i;
  ptr->name = NULL;
  ptr->usertype = NULL;
  ptr->datatype = NUM_RGST_Datatype_t;
  ptr->nptrs = 0;
  ptr->ndims = 0;
  ptr->obj = NULL;
  ptr->array_size_type = NUM_ARRAY_SIZE_ENUM;
  ptr->array_size_field = -1;
  ptr->array_size_field_offset = -1;
  ptr->array_size_absolute_val = -1;
  ptr->attributes = NULL;
  for (i=0; i<3; i++) { ptr->dims[i] = 0; } 
  memset(ptr->array_size_global_var, '\0', R_MAXSTR_PLUS1);
  return(0);
}
RGST_Object_t *RGST_Object_construct(int num)
{
  char *me = "RGST_Object_construct";
  int i;
  RGST_Object_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(RGST_Object_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    RGST_Object_init(&(ptr[i]));   
  }
  return(ptr);
}
RGST_Object_t *RGST_Object_destruct(RGST_Object_t *ptr)
{
  char *me = "RGST_Object_destruct";
  if (ptr == NULL) {
    ctlnotice(me,"Attempt to destroy null pointer");
  }
  else {
    AttrArray_destruct(ptr->attributes);
    FREEMEM(ptr->name);
    FREEMEM(ptr->usertype);
    FREEMEM(ptr);
  }
  return (RGST_Object_t *)(NULL);
}
RGST_Object_t *RGST_Object_create(
  char            *name,               
  char            *type_str,           
  RGST_Datatype_t  datatype,          
  int              nptrs,              
  int              ndims,             
  int              dims[3],        
  void            *obj,        
  ARRAY_SIZE_ENUM  array_size_type,
  int              array_size_field,
  long             array_size_field_offset,
  char            *array_size_global_var,
  long             array_size_absolute_val)
{
  char *me = "RGST_Object_create";
  RGST_Object_t *ro;
  ro = RGST_Object_construct(1);
  ro->name                    = strsave(name);
  ro->usertype                = strsave(type_str);
  ro->datatype                = datatype;
  ro->nptrs                   = nptrs;
  ro->ndims                   = ndims;
  ro->dims[0]                 = dims[0];
  ro->dims[1]                 = dims[1];
  ro->dims[2]                 = dims[2];
  ro->obj                     = obj;
  ro->array_size_type         = array_size_type;
  ro->array_size_field        = array_size_field;
  ro->array_size_field_offset = array_size_field_offset;
  ro->array_size_absolute_val = array_size_absolute_val;
  ro->attributes              = AttrArray_construct(1);
  if (array_size_global_var != NULL) {
    strncpy(ro->array_size_global_var,array_size_global_var,R_MAXSTR);
  }
  return(ro);
}
