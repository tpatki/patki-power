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
void rgst_verify_struct_td_defn(
  char *name,                  
  RGST_StructTypeDef_t *sd,    
  int struct_size)             
{
  char *me = "rgst_verify_struct_td_defn";
  int  i, j;
  char msg[256];
  HashElm_t *hash_elm;
  for (i=0; i<sd->num_fields; i++) {
    if (debugflag == TRUE)
      printf("\n  checking field '%s'",sd->fields[i].name);
    if (  (sd->fields[i].type == R_STRUCT) 
       || (sd->fields[i].type == R_CTYPE_TYPEDEF)
       || (sd->fields[i].type == R_ENUM_TYPEDEF)
       || (sd->fields[i].type == R_STRUCT_TYPEDEF) ) {
      if (sd->fields[i].td_name[0] == '\0') { 
        ctlerror(me,"td_name (name of typedef) is null");
      }
      hash_elm = hash_lookup_elm(sd->fields[i].td_name,rgst_types_hash_tbl);
      if (hash_elm == NULL) {
        if (  (strncmp(sd->fields[i].td_name,name,strlen(name) - 2) == 0) 
           || (    (strcmp(name,"AttrArray_t") == 0) 
                && (strcmp(sd->fields[i].td_name,"RGST_Attribute_s") == 0)
              )
           ) {
          ; 
        }
        else {
          sprintf(msg,"\n\tStructure '%s' -- field '%s'\n\tof type '%s' is bad."
                      "\n\tRegistry does not know of type '%s'",
                      name,
                      sd->fields[i].name,
                      sd->fields[i].td_name,
                      sd->fields[i].td_name);
          ctlnotice(me,msg); 
        }
      } 
      else {						       
        if (strcmp(hash_elm->type,rgst_datatype_strs[sd->fields[i].type]) != 0) {
          ctlerror(me,"Programmer error: sd->fields[i].type != hash_elm->type");
        }
      }
    }
    else {
      if (sd->fields[i].td_name[0] != '\0') {
        ctlerror(me,"td_name (name of typedef) should be null");
      }
    } 
    for (j=0; j<sd->fields[i].ndims; j++) {
      if (sd->fields[i].dims[j] < 1) 
        ctlerror(me,"dimension must be 1 or greater");
    }
  }
}
