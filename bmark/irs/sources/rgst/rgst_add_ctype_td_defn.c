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
int rgst_add_ctype_td_defn (
  RGST_CTypeDef_t in_cd)      
{
  char *me = "rgst_add_ctype_td_defn";
  char msg[256];
  RGST_CTypeDef_t *cd = NULL;
  if ((cd = ALLOT(RGST_CTypeDef_t, 1)) == NULL) 
    ctlerror(me,gv_errmsg_memory);
  memcpy(cd, &in_cd, sizeof(RGST_CTypeDef_t));
  cd->attributes = AttrArray_construct(1);
  if (hash_lookup_obj(cd->name, rgst_types_hash_tbl) != NULL) {
    sprintf(msg,"attempt to add '%s' twice to the registry types table",
            cd->name);
    ctlerror(me,msg);
  }
  hash_add(cd->name,rgst_datatype_strs[R_CTYPE_TYPEDEF],cd,rgst_types_hash_tbl);
  return(0);
}
