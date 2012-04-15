#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int rgst_num_with_attr(
  ATTR_Assoc_t assoc,       
  char       *attr_name)  
{
  char *me = "rgst_num_with_attr";
  RGST_Attribute_t     *attr;
  RGST_AttributeElem_t *attr_elm;
  int  num = 0;
#ifndef NDEBUG
  if ((assoc != A_OBJECT) && (assoc != A_TYPE) && (assoc != A_FIELD))
    ctlerror(me,"assoc argument is invalid");
#endif
  if ((attr = rgst_get_t(attr_name,RGST_Attribute_t_STR)) != NULL)  {
    if      (assoc == A_OBJECT) attr_elm = attr->obj_head;
    else if (assoc == A_TYPE)   attr_elm = attr->type_head;
    else if (assoc == A_FIELD)  attr_elm = attr->field_head;
    else                        ctlerror(me,logic_err);
    while (attr_elm != NULL) {
      num++;
      attr_elm = attr_elm->next;
    }     
  }
  return(num);
}
