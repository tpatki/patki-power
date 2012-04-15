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
RGST_Attribute_t *rgst_free_RGST_Attribute_t(RGST_Attribute_t * ptr)
{
  RGST_AttributeElem_t *elm_ptr, *next_elm_ptr;
  FREEMEM(ptr->attr_name);
  elm_ptr = ptr->obj_head;
  while (elm_ptr != NULL) {
    next_elm_ptr = elm_ptr->next;
    rgst_free_RGST_AttributeElem_t(elm_ptr);
    elm_ptr = next_elm_ptr;
  }
  elm_ptr = ptr->type_head;
  while (elm_ptr != NULL) {
    next_elm_ptr = elm_ptr->next;
    rgst_free_RGST_AttributeElem_t(elm_ptr);
    elm_ptr = next_elm_ptr;
  }
  elm_ptr = ptr->field_head;
  while (elm_ptr != NULL) {
    next_elm_ptr = elm_ptr->next;
    rgst_free_RGST_AttributeElem_t(elm_ptr);
    elm_ptr = next_elm_ptr;
  }
  hash_tbl_free(ptr->table, FALSE);
  FREEMEM(ptr);  
  return(NULL);
}
