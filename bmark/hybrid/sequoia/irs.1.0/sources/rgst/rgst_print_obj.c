#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "Command.h"
#include "Hash.h"
#include "Rgst.h"
#include "irsrgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
static void print_ctype_object (
  RGST_Object_t *ro, 	   
  long        dim_nelms,
  long        ptr_nelms,
  long        lo_ndx,
  long        hi_ndx)
{
  char *me = "print_ctype_object";
  int  nptrs;
  long nelms;
  RGST_CTypeDef_t *td;
  HashElm_t      *hash_elm = NULL;
  hash_elm = hash_lookup_elm(ro->usertype, rgst_types_hash_tbl);
  if (hash_elm == NULL) {
    ctlerror(me,"Programmer error: usertype is not in registry");
  }
  td = (RGST_CTypeDef_t *)hash_elm->obj;
  nptrs = ro->nptrs + td->nptrs;
  if (nptrs == 0) {
    rgst_print_0_ptr_array (td->type, NULL, ro->obj, dim_nelms, lo_ndx, hi_ndx);
  }
  else if (nptrs == 1) {
    rgst_print_1_ptr_array (td->type, NULL, ro->obj, dim_nelms, ptr_nelms, lo_ndx, hi_ndx);
  }
  else if (nptrs == 2) {
    if (dim_nelms > -1) nelms = dim_nelms;
    else                nelms = ptr_nelms;
    rgst_print_2_ptr_array(td->type, NULL, ro->obj, nelms);
  }
  else { 
    ctlerror(me,"Programmer Error - npts > 2");
  }
}  
int rgst_print_obj (
  RGST_Object_t *rgst_obj,
  long        dim_nelms,
  long        ptr_nelms,
  long        nelms,
  long        lo_ndx,
  long        hi_ndx)
{
  char *me = "rgst_print_obj";
  char my_type_str[128];
  rgst_create_typedef_name_str(NUM_RGST_Datatype_t,
    rgst_obj->usertype, rgst_obj->nptrs, rgst_obj->ndims, rgst_obj->dims, 
    my_type_str);
  printf("\nRegistry print of %s '%s'\n%20s",my_type_str, rgst_obj->name, "");
  if      (rgst_obj->datatype == R_CTYPE_TYPEDEF)  {
    print_ctype_object (rgst_obj, dim_nelms, ptr_nelms, lo_ndx, hi_ndx); 
  }
  else if (rgst_obj->datatype == R_ENUM_TYPEDEF)  {
    ctlnotice(me,"Shawn not done yet with print of enum typedefs");
  }
  else if  (  (rgst_obj->datatype == R_STRUCT) 
           || (rgst_obj->datatype == R_STRUCT_TYPEDEF) ) {
    rgst_print_structs (rgst_obj, dim_nelms, ptr_nelms, lo_ndx, hi_ndx); 
  }
  else if (  (rgst_obj->datatype == R_CHAR)
          || (rgst_obj->datatype == R_UNSIGNED_CHAR) 
          || (rgst_obj->datatype == R_SHORT) 
          || (rgst_obj->datatype == R_UNSIGNED_SHORT) 
          || (rgst_obj->datatype == R_INT) 
          || (rgst_obj->datatype == R_UNSIGNED_INT) 
          || (rgst_obj->datatype == R_LONG) 
          || (rgst_obj->datatype == R_UNSIGNED_LONG) 
          || (rgst_obj->datatype == R_LONG_INT) 
          || (rgst_obj->datatype == R_UNSIGNED_LONG_INT) 
          || (rgst_obj->datatype == R_LONG_LONG) 
          || (rgst_obj->datatype == R_UNSIGNED_LONG_LONG) 
          || (rgst_obj->datatype == R_LONG_LONG_INT) 
          || (rgst_obj->datatype == R_UNSIGNED_LONG_LONG_INT) 
          || (rgst_obj->datatype == R_FLOAT) 
          || (rgst_obj->datatype == R_DOUBLE) 
          || (rgst_obj->datatype == R_VOID) ) {
    if (rgst_obj->nptrs == 0)  { 
      rgst_print_0_ptr_array (rgst_obj->datatype, NULL, rgst_obj->obj, dim_nelms, lo_ndx, hi_ndx);
    }
    else if (rgst_obj->nptrs == 1) {
      rgst_print_1_ptr_array (rgst_obj->datatype, NULL, rgst_obj->obj, dim_nelms, ptr_nelms, lo_ndx, hi_ndx);
    }
    else if (rgst_obj->nptrs == 2) {
      rgst_print_2_ptr_array (rgst_obj->datatype, NULL, rgst_obj->obj, nelms);
    }
    else {
      ctlerror(me,"PROGRAMMER ERROR: nptrs > 2");
    }
  }
  else if (rgst_obj->datatype == R_FUNCTION) {
    rgst_print_function((Command_t *)(rgst_obj->obj));
  }  
  else {
    ctlerror(me,"PROGRAMMER ERROR rgst_obj->datatype is bad");
  }
  return(0);
}
