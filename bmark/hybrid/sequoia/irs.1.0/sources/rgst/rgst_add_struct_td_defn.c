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
int rgst_add_struct_td_defn (
  RGST_Datatype_t datatype,     
  char *          name,         
  RGST_Field_t    fields[],     
  int             num_fields,   
  size_t          struct_size)  
{
  char *me = "rgst_add_struct_td_defn";
  char msg[256];
  RGST_StructTypeDef_t *sd = NULL;
  int i, ierr;
  if ( (datatype != R_STRUCT) && (datatype != R_STRUCT_TYPEDEF) ) 
    ctlerror(me,"datatape is bad -- it must be R_STRUCT or R_STRUCT_TYPEDEF");
  if ( (name == NULL) || (strcmp(name,"") == 0) ) 
    ctlerror(me,"Name was not specified"); 
  if (num_fields <= 0) 
    ctlerror(me,"Num of fields must be > 0");
  sd = hash_lookup_obj(name, rgst_types_hash_tbl);
  if (sd != NULL) {
    ierr = 0;
    if (struct_size != sd->struct_size) ierr++;
    if (num_fields  != sd->num_fields)  ierr++;
    if (ierr == 0) {
      for (i=0; i<num_fields; i++) {
        if (strcmp(fields[i].name, sd->fields[i].name) != 0) ierr++;
      }
    }
    if (ierr == 0) {
      return(0);
    }
    else {
      sprintf(msg,"'%s' defined twice with different definitions\n",name);
      ctlerror(me,msg);
      return(-1);
    }
  }
  if ((sd = ALLOT(RGST_StructTypeDef_t, 1)) == NULL) 
    ctlerror(me,gv_errmsg_memory);
  if ((sd->fields = ALLOT(RGST_Field_t, num_fields)) == NULL)
    ctlerror(me,gv_errmsg_memory); 
  strncpy(sd->name,name,R_MAXSTR);
  sd->struct_size = struct_size;
  sd->num_fields  = num_fields;
  sd->attributes  = AttrArray_construct(1);
  for (i=0; i<num_fields; i++) {
    memcpy(&(sd->fields[i]),&(fields[i]),sizeof(RGST_Field_t));
    sd->fields[i].attributes = AttrArray_construct(1);
  }
  rgst_verify_struct_td_defn(name, sd, struct_size);
  hash_add(name,rgst_datatype_strs[datatype],sd,rgst_types_hash_tbl); 
  return(0);
}
