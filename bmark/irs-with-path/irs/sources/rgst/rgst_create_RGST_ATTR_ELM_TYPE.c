#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
RGST_AttributeElem_t *rgst_create_RGST_AttributeElem_t(
  char         *name,	  
  ATTR_Assoc_t    assoc,    
  RGST_Datatype_t datatype, 
  void          *v_ptr,   
  RGST_Field_t    *fld_ptr) 
{
  char *me = "rgst_create_RGST_AttributeElem_t";
  RGST_AttributeElem_t *elm;
  if ((elm = ALLOT(RGST_AttributeElem_t, 1)) == NULL) ctlerror(me,gv_errmsg_memory);
  elm->name                         = strsave(name);
  elm->assoc                        = assoc;
  elm->rgst_datatype                = NUM_RGST_Datatype_t;
  elm->rgst_ctype_defn              = NULL;
  elm->rgst_enum_defn               = NULL;
  elm->rgst_struct_defn             = NULL;
  elm->rgst_field                   = NULL;
  elm->rgst_obj                     = NULL;
  elm->next                         = NULL;
  elm->prev                         = NULL;
  switch (elm->assoc) {
    case A_TYPE:
      elm->rgst_datatype = datatype;
      if ((datatype == R_STRUCT) || (datatype == R_STRUCT_TYPEDEF)) {
        elm->rgst_struct_defn = (RGST_StructTypeDef_t *)v_ptr;
      }
      else if (datatype == R_CTYPE_TYPEDEF) {
        elm->rgst_ctype_defn = (RGST_CTypeDef_t *)v_ptr;
      }
      else if (datatype == R_ENUM_TYPEDEF) {
        elm->rgst_enum_defn = (RGST_EnumTypeDef_t *)v_ptr;
      }
      else  {
        ctlerror(me,logic_err);
      }
      break;
    case A_FIELD:
      elm->rgst_datatype    = datatype;
      elm->rgst_struct_defn = (RGST_StructTypeDef_t *)v_ptr;
      elm->rgst_field       = fld_ptr;
      break;
    case A_OBJECT:
      elm->rgst_obj = (RGST_Object_t *)v_ptr;
      break;
    default:
      ctlerror(me,"Programmer error: assoc is invalid");
  }
  return(elm);
}  
