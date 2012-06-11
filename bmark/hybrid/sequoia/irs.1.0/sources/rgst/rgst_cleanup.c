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
int rgst_cleanup(void)
{
  char *me = "rgst_cleanup";
  int num_elms, i, j;
  HashElm_t      **elms      = NULL;
  RGST_Object_t         *ro        = NULL;
  RGST_StructTypeDef_t *struct_td = NULL;
  RGST_EnumTypeDef_t   *enum_td   = NULL;
  RGST_CTypeDef_t  *ctype_td  = NULL;
  RGST_Attribute_t      *attr      = NULL;
  elms = hash_get_elm_list(&num_elms, NULL, rgst_objs_hash_tbl);
  for (i=0; i<num_elms; i++) {
    ro = (RGST_Object_t *)elms[i]->obj;
    if (strcmp(elms[i]->type,RGST_Attribute_t_STR) == 0) {
      attr = (RGST_Attribute_t *)ro->obj;
      rgst_free_RGST_Attribute_t(attr);
    }  
    RGST_Object_destruct(ro);
  }
  rgst_objs_hash_tbl = hash_tbl_free(rgst_objs_hash_tbl, FALSE);
  free(elms);
  elms = hash_get_elm_list(&num_elms, NULL, rgst_types_hash_tbl);
  for (i=0; i<num_elms; i++) {
    if (  (strcmp(elms[i]->type, rgst_datatype_strs[R_CHAR])                   == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_UNSIGNED_CHAR])          == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_SHORT])                  == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_UNSIGNED_SHORT])         == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_SHORT_INT])              == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_UNSIGNED_SHORT_INT])     == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_INT])                    == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_UNSIGNED_INT])           == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_LONG])                   == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_UNSIGNED_LONG])          == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_LONG_INT])               == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_UNSIGNED_LONG_INT])      == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_LONG_LONG])              == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_UNSIGNED_LONG_LONG])     == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_LONG_LONG_INT])          == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_UNSIGNED_LONG_LONG_INT]) == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_FLOAT])                  == 0)
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_DOUBLE])                 == 0) 
       || (strcmp(elms[i]->type, rgst_datatype_strs[R_VOID])                   == 0) 
       ) {
      FREEMEM(elms[i]->obj);
    }
    else if (  (strcmp(elms[i]->type,rgst_datatype_strs[R_STRUCT_TYPEDEF]) == 0) 
            || (strcmp(elms[i]->type,rgst_datatype_strs[R_STRUCT]) == 0) ) {
      struct_td = (RGST_StructTypeDef_t *)(elms[i]->obj);
      for (j=0; j<struct_td->num_fields; j++) {
        AttrArray_destruct(struct_td->fields[j].attributes);
      }
      AttrArray_destruct(struct_td->attributes);
      FREEMEM(struct_td->fields);
      FREEMEM(struct_td);
    }
    else if (strcmp(elms[i]->type,rgst_datatype_strs[R_ENUM_TYPEDEF]) == 0) {
      enum_td = (RGST_EnumTypeDef_t *)(elms[i]->obj);
      AttrArray_destruct(enum_td->attributes);
      FREEMEM(enum_td);
    }
    else if (strcmp(elms[i]->type,rgst_datatype_strs[R_CTYPE_TYPEDEF]) == 0) {
      ctype_td = (RGST_CTypeDef_t *)(elms[i]->obj);
      AttrArray_destruct(ctype_td->attributes);
      FREEMEM(ctype_td);
    }
    else if (strcmp(elms[i]->type,rgst_datatype_strs[R_FUNCTION]) == 0) {
      FREEMEM(elms[i]->obj);
    }
    else {
      ctlerror(me,"don't know how to delete this registry type yet");
    }
  }
  rgst_types_hash_tbl = hash_tbl_free(rgst_types_hash_tbl, FALSE);
  rgst_field_ndx_hash_tbl = hash_tbl_free(rgst_field_ndx_hash_tbl, TRUE); 
  free(elms);
  return(0);
}
