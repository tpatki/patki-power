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
int rgst_print_type (
  char *name)           
{
  char *me = "rgst_print_type";
  char msg[128];
  int i;
  HashElm_t          *hash_elm = NULL;
  RGST_EnumTypeDef_t      *ed       = NULL;
  RGST_BasicCTypeDef_t *ct       = NULL;
  hash_elm = hash_lookup_elm(name, rgst_types_hash_tbl);
  if (hash_elm == NULL) {
    sprintf(msg,"Type '%s' is not in the registry",name);
    ctlnotice(me,msg);
    return(-1);
  }
  if (  (strcmp(hash_elm->type, rgst_datatype_strs[R_CHAR])                   == 0) 
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_UNSIGNED_CHAR])          == 0) 
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_SHORT])                  == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_UNSIGNED_SHORT])         == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_SHORT_INT])              == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_UNSIGNED_SHORT_INT])     == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_INT])                    == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_UNSIGNED_INT])           == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_LONG])                   == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_UNSIGNED_LONG])          == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_LONG_INT])               == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_UNSIGNED_LONG_INT])      == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_LONG_LONG])              == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_UNSIGNED_LONG_LONG])     == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_LONG_LONG_INT])          == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_UNSIGNED_LONG_LONG_INT]) == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_FLOAT])                  == 0) 
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_DOUBLE])                 == 0)
     || (strcmp(hash_elm->type, rgst_datatype_strs[R_VOID])                   == 0)) {
    ct = (RGST_BasicCTypeDef_t *)hash_elm->obj;
    printf("User type '%s' is the basic c type '%s'\n",
           name, rgst_datatype_strs[ct->type]);
  }
  else if (  (strcmp(hash_elm->type, rgst_datatype_strs[R_STRUCT]) == 0) 
          || (strcmp(hash_elm->type, rgst_datatype_strs[R_STRUCT_TYPEDEF]) == 0) ) {
    rgst_print_struct_td_defn((RGST_StructTypeDef_t *)hash_elm->obj);
  }
  else if (strcmp(hash_elm->type, rgst_datatype_strs[R_CTYPE_TYPEDEF]) == 0) {
    rgst_print_ctype_td_defn((RGST_CTypeDef_t *)hash_elm->obj);
  }
  else if (strcmp(hash_elm->type, rgst_datatype_strs[R_ENUM_TYPEDEF]) == 0) {
    ed = (RGST_EnumTypeDef_t *)hash_elm->obj;
    printf("User type '%s' is an enumerated type with %d entries\n",
            ed->name,ed->num_entries);
    for (i=0; i<ed->num_entries; i++) {
      printf("\ttype %d = %s\n",i,ed->entry_strings[i]);         
    }
  }
  else {
    ctlnotice(me,"PROGRAMMER ERROR: HashElm_t is invalid");
  }
  return(0);
}
