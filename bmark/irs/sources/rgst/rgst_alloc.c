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
void *rgst_alloc(
  char *name,     
  char *type)     
{
  char *me = "rgst_alloc";
  char msg[256];
  HashElm_t          *hash_elm_rt;    
  RGST_StructTypeDef_t    *struct_td_defn; 
  RGST_BasicCTypeDef_t *basic_c_defn;   
  void *ptr = NULL;                       
  size_t my_size;                         
  if (type == NULL)
    ctlerror(me,"type field is null");
  if ((hash_elm_rt = hash_lookup_elm(type, rgst_types_hash_tbl)) == 0) {
    sprintf(msg,"Type '%s' is not in the types registry",type);
    ctlerror(me,msg);
  }
  if (  (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_CHAR])                   == 0) 
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_UNSIGNED_CHAR])          == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_SHORT])                  == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_UNSIGNED_SHORT])         == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_SHORT_INT])              == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_UNSIGNED_SHORT_INT])     == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_INT])                    == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_UNSIGNED_INT])           == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_LONG])                   == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_UNSIGNED_LONG])          == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_LONG_INT])               == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_UNSIGNED_LONG_INT])      == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_LONG_LONG])              == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_UNSIGNED_LONG_LONG])     == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_LONG_LONG_INT])          == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_UNSIGNED_LONG_LONG_INT]) == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_FLOAT])                  == 0)
     || (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_DOUBLE])                 == 0)) {
    basic_c_defn = (RGST_BasicCTypeDef_t *)hash_elm_rt->obj;
    my_size = basic_c_defn->type_size;
  }
  else if (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_VOID]) == 0) {
    ctlerror(me,"shawn not done yet");
  }
  else if (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_STRUCT]) == 0) {
    ctlerror(me,"shawn not done yet");
  }
  else if (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_CTYPE_TYPEDEF]) == 0) {
    ctlerror(me,"shawn not done yet");
  }
  else if (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_ENUM_TYPEDEF]) == 0) {
    ctlerror(me,"shawn not done yet");
  }
  else if (strcmp(hash_elm_rt->type, rgst_datatype_strs[R_STRUCT_TYPEDEF]) == 0) {
    struct_td_defn = (RGST_StructTypeDef_t *) hash_elm_rt->obj;
    my_size = struct_td_defn->struct_size;
  }
  else {
    ctlerror(me,"Programmer error - bad type string");
  }
  ptr = calloc(1, my_size);
  if (name != NULL) rgst_add (name, type, ptr, NULL);
  return(ptr);
}
