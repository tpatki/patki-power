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
int rgst_add_enum_td_defn (
  RGST_EnumTypeDef_t in_ed)      
{
  char *me = "rgst_add_enum_td_defn";
  char msg[256];
  RGST_EnumTypeDef_t *ed = NULL;
  if ((ed = ALLOT(RGST_EnumTypeDef_t, 1)) == NULL) ctlerror(me,gv_errmsg_memory);
  memcpy(ed, &in_ed, sizeof(RGST_EnumTypeDef_t));
  ed->attributes = AttrArray_construct(1);
  if (hash_lookup_obj(ed->name, rgst_types_hash_tbl) != NULL) {
    sprintf(msg,"attempt to add '%s' twice to the registry types table",
            ed->name);
    ctlerror(me,msg);
  }
  hash_add(ed->name,rgst_datatype_strs[R_ENUM_TYPEDEF],ed,rgst_types_hash_tbl); 
  return(0);
}
