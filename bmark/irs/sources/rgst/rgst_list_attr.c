#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
RGST_AttributeElem_t *rgst_list_attr(
  ATTR_Assoc_t assoc,       
  char       *attr_name)  
{
  char *me = "rgst_list_attr";
  char msg[128];
  RGST_Attribute_t *attr;
  if ((attr = rgst_get_t(attr_name,RGST_Attribute_t_STR)) == NULL) 
    return(NULL);
  if      (assoc == A_OBJECT) return(attr->obj_head);
  else if (assoc == A_TYPE)   return(attr->type_head);
  else if (assoc == A_FIELD)  return(attr->field_head);
  else                        ctlerror(me,logic_err);
  return(NULL);
}
