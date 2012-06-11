#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Hash.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int rgst_add (
  char *name,           
  char *type,           
  void *ptr,            
  char *array_size_var) 
{
  char *me = "rgst_add";
  char msg[256], msg1[256], type_str[128];
  int  i, j, nptrs, myndims, dims[3];
  ARRAY_SIZE_ENUM array_size_type;
  RGST_Datatype_t datatype;
  RGST_Object_t   *rgst_obj, *array_size_obj;
  HashElm_t *hash_elm;
  if ((name == NULL) || (name[0] == '\0')) 
    ctlerror(me,"name field is null");
  if ((type == NULL) || (type[0] == '\0')) 
    ctlerror(me,"type field is null");
  sprintf(msg,"\n\tError adding object '%s' of type '%s'\n\t",name,type);
  if (ptr == NULL)  {
    strcat(msg,"object ptr is null");
    ctlerror(me,msg);
  }
  memset(type_str,'\0',128);
  strncpy(type_str,type,127);
  rgst_get_dims_of_type(type_str,&nptrs,&myndims,&dims[0]);
  if (strncmp(type_str,"struct ",7) == 0) {
    strcpy(msg1,&type_str[7]);
    strcpy(type_str,msg1);
  }
  hash_elm = hash_lookup_elm(type_str, rgst_types_hash_tbl);
  if (hash_elm == NULL) {
    sprintf(msg1,"Registry type '%s' is not in the registry types table",type_str);
    strcat (msg,msg1);
    ctlerror(me,msg);
  }
  for (i=0; i<NUM_RGST_Datatype_t; i++) {
    if (strcmp(hash_elm->type, rgst_datatype_strs[i]) == 0) {
      datatype = (RGST_Datatype_t) i;
      break;
    }
  }
  if (i >= NUM_RGST_Datatype_t) 
    ctlerror(me,"Programmer Error - hash_elm->type is bad");
  if ((rgst_obj = hash_lookup_obj(name, rgst_objs_hash_tbl)) != NULL) {
    sprintf(msg1,"\n\tAn object named '%s' of type '%s'"
                 "\n\talready exists in the registry",
                 name,
                 rgst_obj->datatype == R_STRUCT_TYPEDEF ? rgst_obj->usertype : rgst_datatype_strs[rgst_obj->datatype]);
    strcat(msg,msg1);
    ctlwarning(me,msg);
    return(-1);
  }
  if (hash_lookup_elm(name, rgst_types_hash_tbl) != NULL) {
    sprintf(msg1,"\n\tObject '%s' will not be added because '%s' is already"
                 "\n\tthe name of a registry type",
                 name,name);
    strcat(msg,msg1);
    ctlwarning(me,msg);
  }
  if (array_size_var != NULL) {
    if ( (nptrs == 0) || (myndims != 0) ){
      sprintf(msg,"\n\tObject '%s' of type '%s' refers to object '%s'"
                  "\n\tas the size of the array pointed to.  For this to work"
                  "\n\tthis object must have at least 1 ptr (asterisk), and no"
		  "\n\tdimensions, but this object %d ptrs and %d dimensions",
                  name,type,array_size_var,nptrs,myndims);
      ctlerror(me,msg);
    }
    array_size_obj = (RGST_Object_t *) hash_lookup_obj(array_size_var, rgst_objs_hash_tbl);
    if (array_size_obj  == NULL) {
      sprintf(msg,"\n\tObject '%s' refers to '%s' as its array size"
                  "\n\tBut '%s' is not an object in the registry",
                  name,array_size_var,array_size_var);
      ctlerror(me,msg);
    }
    if (  (  (strcmp(array_size_obj->usertype, "int") == 0) 
          || (strcmp(array_size_obj->usertype,"long") == 0) ) 
       && (array_size_obj->nptrs == 0)
       && (array_size_obj->ndims == 0) ) {
      ; 
    }
    else {
      sprintf(msg,"\n\tObject '%s' refers to '%s' as its array size"
                  "\n\tBut '%s' is not a simple int or long object",
                  name,array_size_var,array_size_var);
      ctlerror(me,msg);
    }
  }
  if (datatype == R_VOID) {
    if (nptrs == 0) {
      sprintf(msg,"\n\tObject '%s' of type 'void' is invalid"
                  "\n\tObjects may be of type 'void *' but not simply 'void'",
		  name);
      ctlerror(me,msg);
    }
    if ( (nptrs == 1) && (array_size_var != NULL) ) {
      sprintf(msg,"\n\tObject '%s' of type 'void *' refers to '%s'"
                  "\n\tas its array size.  This is invalid, since"
		  "\n\tan array of type 'void' is meaningless"
		  "\n\tIf you want an array full of void ptrs try"
		  "\n\tdeclaring it as 'void **' not 'void *'",
		  name,array_size_var);
      ctlerror(me,msg);
    }
  }
  if ( (nptrs > 1) && (myndims > 0) ) {
    sprintf(msg,"\n\tObject '%s' of type '%s'"
                "\n\tis bad.  An object with two ptrs (**) may not"
                "\n\talso be an array",
                name,type);
    ctlerror(me,msg);
  }
  array_size_type = NUM_ARRAY_SIZE_ENUM;
  if (array_size_var != NULL) array_size_type = GLOBAL_VAR;
  rgst_obj = RGST_Object_create(name, type_str, datatype, nptrs,
                                myndims, dims, ptr, 
                                array_size_type,-1,-1,array_size_var,-1);
  hash_add(name,type_str,rgst_obj,rgst_objs_hash_tbl);
  return(0);
}
