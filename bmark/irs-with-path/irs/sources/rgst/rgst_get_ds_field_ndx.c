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
int rgst_get_ds_field_ndx(
  RGST_StructTypeDef_t *sd,       
  char                *fld_name) 
{
  char *me = "rgst_get_ds_field_ndx";
  char msg[256], str1[256];
  int i, *intptr;
  HashElm_t *hash_elm;
  memset(str1,'\0',256);
  strcpy(str1,sd->name);
  strcat(str1,fld_name);
  hash_elm = hash_lookup_elm(str1, rgst_field_ndx_hash_tbl);
  if (hash_elm != NULL) {
    intptr = (int *)hash_elm->obj;  
    return(*intptr);
  }
  for (i=0; i<sd->num_fields; i++) {
    if (strcmp(sd->fields[i].name,fld_name) == 0) { break; }
  }
  if (i >= sd->num_fields) {
    sprintf(msg,"\n\tStructure '%s' does not contain field '%s'",
                sd->name,fld_name);
    ctlnotice(me,msg);
    return(-1);
  }
  intptr = ALLOT(int, 1);
  *intptr = i;
  hash_add(str1, NULL, intptr ,rgst_field_ndx_hash_tbl);
  return(i);
}
