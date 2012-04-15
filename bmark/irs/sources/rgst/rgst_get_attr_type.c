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
RGST_Attribute_t *rgst_get_attr_type(char *attr_name)
{
  char *me = "rgst_get_attr_type";
  char msg[256];
  RGST_Attribute_t *attr = NULL;
  RGST_Object_t    *ro = NULL;
  if (rgst_check_for_obj(attr_name) == TRUE) {
    ro = rgst_get_RGST_Object_t(attr_name);
    if (strcmp(ro->usertype, RGST_Attribute_t_STR) != 0) {
      sprintf(msg,"\n\tExpected registered object '%s' to be type '%s' "
                  "\n\tbut it is type '%s'",
                  attr_name,RGST_Attribute_t_STR,ro->usertype);
      ctlwarning(me,msg);
      return (NULL);
    }
    else {
      attr = (RGST_Attribute_t *)ro->obj;
    }
  }
  if (attr == NULL) {
    if ((attr = ALLOT(RGST_Attribute_t, 1)) == NULL) ctlerror(me,gv_errmsg_memory);
    attr->attr_name  = strsave(attr_name);
    attr->obj_head   = NULL;
    attr->type_head  = NULL;
    attr->field_head = NULL;
    sprintf(msg,"attribute_%s_ht",attr_name);
    if ((hash_tbl_create_n_rgst(&(attr->table),3,msg)) != 0) {
      attr = rgst_free_RGST_Attribute_t(attr);
    }
    if (attr != NULL) {
      rgst_add(attr_name,RGST_Attribute_t_STR,attr,NULL);
    }
  }
  return(attr);
}
