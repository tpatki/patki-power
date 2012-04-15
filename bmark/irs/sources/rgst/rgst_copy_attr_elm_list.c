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
RGST_AttributeElem_t *rgst_copy_attr_elm_list (RGST_AttributeElem_t *elm_list)
{
  char *me = "rgst_copy_attr_elm_list";
  RGST_AttributeElem_t *new_list_head = NULL, *new_elm      = NULL, 
                     *elm_ptr       = NULL, *prev_new_elm = NULL;
  if (elm_list != NULL) {
    elm_ptr = elm_list;
    while (elm_ptr != NULL) {
      if ((new_elm = ALLOT(RGST_AttributeElem_t, 1)) == NULL) 
        ctlerror(me,gv_errmsg_memory);
       new_elm->name                    = strsave(elm_ptr->name);
       new_elm->assoc                   = elm_ptr->assoc;
       new_elm->rgst_datatype           = elm_ptr->rgst_datatype;
       new_elm->rgst_ctype_defn         = elm_ptr->rgst_ctype_defn;
       new_elm->rgst_enum_defn          = elm_ptr->rgst_enum_defn;
       new_elm->rgst_struct_defn        = elm_ptr->rgst_struct_defn;
       new_elm->rgst_field              = elm_ptr->rgst_field;
       new_elm->rgst_obj                = elm_ptr->rgst_obj;
       new_elm->next                    = NULL;
       new_elm->prev                    = prev_new_elm;
       if (prev_new_elm != NULL) prev_new_elm->next = new_elm;
       if (new_list_head == NULL) new_list_head = new_elm;
       prev_new_elm = new_elm;
       elm_ptr = elm_ptr->next;
    }
  }
  return(new_list_head);
}
