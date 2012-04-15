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
void *rgst_get_td_defn(
  char          *name,   
  RGST_Datatype_t in_dt,   
  RGST_Datatype_t *out_dt) 
{
  char *me = "rgst_get_td_defn";
  char msg[256];
  HashElm_t *hash_elm = NULL;
  int  error = FALSE;
  if (out_dt != NULL) *out_dt = NUM_RGST_Datatype_t;
  hash_elm = hash_lookup_elm(name,rgst_types_hash_tbl);    
  if (hash_elm == NULL) {
    sprintf(msg,"\n\tType '%s' is not a type definition known by the registry",name);
    ctlwarning(me,msg); 
    return(NULL);
  }
  if (    (strcmp(hash_elm->type,rgst_datatype_strs[R_STRUCT]) == 0)  
       || (strcmp(hash_elm->type,rgst_datatype_strs[R_STRUCT_TYPEDEF]) == 0) ) {
    if (out_dt != NULL) *out_dt = R_STRUCT_TYPEDEF;  
    if (in_dt != NUM_RGST_Datatype_t) {
      if ((in_dt != R_STRUCT) && (in_dt != R_STRUCT_TYPEDEF)) error = TRUE;
    }
  }
  else if (strcmp(hash_elm->type,rgst_datatype_strs[R_CTYPE_TYPEDEF]) == 0) {
    if (out_dt != NULL) *out_dt = R_CTYPE_TYPEDEF; 
    if ((in_dt != NUM_RGST_Datatype_t) && (in_dt != R_CTYPE_TYPEDEF)) error = TRUE;
  }
  else if (strcmp(hash_elm->type,rgst_datatype_strs[R_ENUM_TYPEDEF]) == 0) {
    if (out_dt != NULL) *out_dt = R_ENUM_TYPEDEF; 
    if ((in_dt != NUM_RGST_Datatype_t) && (in_dt != R_ENUM_TYPEDEF)) error = TRUE;
  }
  else {
    sprintf(msg,"'%s' is not a type definition, it is a '%s'",
                name,hash_elm->type);
    ctlwarning(me,msg);
    return(NULL);
  }
  if (error == TRUE) {
    sprintf(msg,"Expected '%s' to be of type '%s' but it is type '%s'",
                name,rgst_datatype_strs[in_dt],hash_elm->type);
    ctlwarning(me,msg);
    return(NULL);
  }
  return(hash_elm->obj);
}
