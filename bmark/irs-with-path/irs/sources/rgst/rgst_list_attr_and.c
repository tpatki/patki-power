#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "Rgst.h"
#include "irsrgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
RGST_AttributeElem_t *rgst_list_attr_and(
  ATTR_Assoc_t assoc, 
  char *attr_name,  
  ...)              
{
  char *me = "rgst_list_attr_and";
  char msg[128], *attr_name_2;
  va_list ap;
  RGST_Attribute_t *attr;
  RGST_AttributeElem_t *new_elm_list_head, *elm_ptr, *t_ptr;
  if ((attr = rgst_get_t(attr_name,RGST_Attribute_t_STR)) == NULL)
    return(NULL);
  if      (assoc == A_OBJECT) new_elm_list_head = rgst_copy_attr_elm_list(attr->obj_head);
  else if (assoc == A_TYPE)   new_elm_list_head = rgst_copy_attr_elm_list(attr->type_head);
  else if (assoc == A_FIELD)  new_elm_list_head = rgst_copy_attr_elm_list(attr->field_head);
  else                        ctlerror(me,logic_err);
  if (new_elm_list_head == NULL)
    return(NULL);
  va_start(ap, attr_name);
  attr_name_2 = va_arg(ap,char *);
  while (attr_name_2 != NULL) {
    if ((attr = rgst_get_t(attr_name_2,RGST_Attribute_t_STR)) == NULL) {
      rgst_free_attr_elm_list(new_elm_list_head);
      va_end(ap);
      return(NULL);
    }
    elm_ptr = new_elm_list_head;
    while (elm_ptr != NULL) {
      if (hash_lookup_elm(elm_ptr->name, attr->table) == NULL) {
        t_ptr   = elm_ptr;
        elm_ptr = elm_ptr->next;
        if (t_ptr == new_elm_list_head) new_elm_list_head = t_ptr->next;
        if (t_ptr->prev != NULL) t_ptr->prev->next = t_ptr->next;
        if (t_ptr->next != NULL) t_ptr->next->prev = t_ptr->prev;
        FREEMEM(t_ptr->name);
        FREEMEM(t_ptr);
      }
      else {
        elm_ptr = elm_ptr->next;
      }
    }
    attr_name_2 = va_arg(ap,char *);
  }
  va_end(ap);
  return(new_elm_list_head);
}
