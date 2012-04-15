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
static void copy_char_array (char *array, long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_unsigned_char_array (unsigned char *array, long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_strs (char **strs, long nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_int_array (int *array, long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_unsigned_int_array (unsigned int *array, long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_long_array (long *array, long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_unsigned_long_array (unsigned long *array, long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copyfloat_array (float *array, long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_double_array (double *array, long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void * copy_0_ptr_array (
  RGST_Datatype_t dt,             
  void          *ptr,           
  long          nelms)          
{
  void *copy_ptr = NULL;
  if (ptr != NULL) {
    copy_ptr = calloc(nelms, rgst_datatype_sizes[dt]);
    memcpy(copy_ptr, ptr, nelms * rgst_datatype_sizes[dt]);
  }
  return(copy_ptr);
}
static void * copy_1_ptr_array (
  RGST_Datatype_t dt,             
  void          *ptr,           
  long          dim_nelms,      
  long          ptr_nelms)      
{
  char *me = "copy_1_ptr_array";
  char *errmsg1 = "\n\tProgrammer Error : "
                  "\n\tEither dim_nelms or ptr_nelms is to be used"
                  "\n\tOne must be -1 and the other must be 0 or greater";
  long i;
  void *myptr, *copy_ptr = NULL;
  if (dim_nelms == -1) { 
    if (ptr_nelms < 0) ctlerror(me,errmsg1);
  }
  else if (ptr_nelms == -1) {
    if (dim_nelms < 0) ctlerror(me,errmsg1);
  }   
  else {
    ctlerror(me,errmsg1);
  }
  if (dim_nelms > -1) {
    if   (dt == R_CHAR) {
      copy_strs((char **)ptr, dim_nelms);
    }
    else {
      ctlnotice("shawn","shawn not done yet");
      for (i=0; i<dim_nelms; i++)  {
        myptr = (void *)((void **)ptr)[i];
        copy_0_ptr_array(dt, myptr, 1);
        printf("%20s","");
      }
    }
  }
  else {
    ctlnotice("shawn","shawn not done yet");
    myptr = (void *)(*(void **)ptr);
    copy_ptr = copy_0_ptr_array(dt, myptr, ptr_nelms);
  }
  return(copy_ptr);
}
static void copy_2_ptr_array (
  RGST_Datatype_t dt,             
  void ***ptr,
  long  nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_ctype_array (
  RGST_Object_t *ro,         
  long        dim_nelms,
  long        ptr_nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_enum_array (
  RGST_Object_t *ro,         
  long        dim_nelms,
  long        ptr_nelms)
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_field (
  unsigned char       *sptr,    
  RGST_StructTypeDef_t *sd,      
  unsigned char       *ptr,     
  RGST_Field_t          *fd)      
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_struct (
  unsigned char *sptr,          
  RGST_StructTypeDef_t *sd)      
{ ctlnotice("shawn","shawn not done yet"); }
static void copy_structs (
  RGST_Object_t *ro,              
  long        dim_nelms,
  long        ptr_nelms)
{ ctlnotice("shawn","shawn not done yet"); }
void *rgst_copy(
  char *name)     
{
  char *me = "rgst_copy";
  char msg[256], my_type_str[128];
  RGST_Object_t *rgst_obj = NULL;
  long dim_nelms, ptr_nelms, nelms;
  void *copy_ptr;
  if ((rgst_obj = rgst_get_RGST_Object_t(name)) == NULL) return(NULL);
  rgst_get_nelms_in_rgst_obj(rgst_obj, &dim_nelms, &ptr_nelms, &nelms);
  rgst_create_typedef_name_str(NUM_RGST_Datatype_t,
    rgst_obj->usertype, rgst_obj->nptrs, rgst_obj->ndims, rgst_obj->dims,
    my_type_str);
  if      (rgst_obj->datatype == R_CTYPE_TYPEDEF)  {
    copy_ctype_array (rgst_obj, dim_nelms, ptr_nelms);
  }
  else if (rgst_obj->datatype == R_ENUM_TYPEDEF)  {      
    copy_enum_array (rgst_obj, dim_nelms, ptr_nelms);
  }
  else if  (  (rgst_obj->datatype == R_STRUCT)
           || (rgst_obj->datatype == R_STRUCT_TYPEDEF) ) {
    copy_structs (rgst_obj, dim_nelms, ptr_nelms);
  }
  else if (  (rgst_obj->datatype == R_CHAR)
          || (rgst_obj->datatype == R_UNSIGNED_CHAR)
          || (rgst_obj->datatype == R_SHORT)
          || (rgst_obj->datatype == R_UNSIGNED_SHORT)
          || (rgst_obj->datatype == R_SHORT_INT)
          || (rgst_obj->datatype == R_UNSIGNED_SHORT_INT)
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
          || (rgst_obj->datatype == R_DOUBLE) ) {
    if (rgst_obj->nptrs == 0)  {
      copy_ptr = copy_0_ptr_array (rgst_obj->datatype, rgst_obj->obj, dim_nelms);
    }
    else if (rgst_obj->nptrs == 1) {
      copy_ptr = copy_1_ptr_array (rgst_obj->datatype, rgst_obj->obj, dim_nelms, ptr_nelms);
    }
    else if (rgst_obj->nptrs == 2) {
      copy_2_ptr_array (rgst_obj->datatype, rgst_obj->obj, nelms);
    }
    else {
      ctlerror(me,"PROGRAMMER ERROR: nptrs > 2");
    }
  }   
  else {
    sprintf(msg,"Can't copy %s '%s'",my_type_str,name);
    ctlerror(me,msg);
  }
  return(copy_ptr);
}
