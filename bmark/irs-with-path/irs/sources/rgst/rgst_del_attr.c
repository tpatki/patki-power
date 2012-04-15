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
#define NAMELEN 128
int rgst_del_attr(
  ATTR_Assoc_t assoc, 
  ...)              
{
  char *me = "rgst_del_attr";
  char msg[256],      type_n_fld_name[NAMELEN], fld_name[NAMELEN],
       name[NAMELEN], attr_name[NAMELEN],       type_name[NAMELEN];
  int i, fld_ndx, error = FALSE;
  va_list ap;
  RGST_Datatype_t data_type;
  char                  *nameptr      = NULL,
                        *fld_nameptr  = NULL,
                        *attr_nameptr = NULL;
  void                  *td           = NULL;
  RGST_Object_t         *ro           = NULL;
  RGST_Attribute_t      *attr         = NULL;
  RGST_AttributeElem_t  *elm          = NULL;
  RGST_StructTypeDef_t  *sd           = NULL;
  RGST_EnumTypeDef_t    *ed           = NULL;
  RGST_CTypeDef_t       *cd           = NULL;
  RGST_Field_t          *fd           = NULL;
  AttrArray_t           *attributes   = NULL;
  if ((assoc < 0) || (assoc >= NUM_ATTR_Assoc_t))
    ctlerror(me,logic_err);
  memset(name,           '\0',NAMELEN);
  memset(type_name,      '\0',NAMELEN);
  memset(attr_name,      '\0',NAMELEN);
  memset(fld_name,       '\0',NAMELEN);
  memset(type_n_fld_name,'\0',NAMELEN);
  va_start(ap, assoc);
  nameptr = va_arg(ap, char *);
  strncpy(name,nameptr,NAMELEN-1);
  if (assoc == A_FIELD) {
    strcpy(type_name, name);
    fld_nameptr  = va_arg(ap, char *);
    strncpy(fld_name,fld_nameptr,NAMELEN-1);
    sprintf(type_n_fld_name,"%s:%s",type_name,fld_name);
    strcpy(name,type_n_fld_name);
  }
  attr_nameptr = va_arg(ap, char *);
  strcpy(attr_name,attr_nameptr);
  va_end(ap);
  if ((attr = rgst_get_attr_type(attr_name)) != NULL) {
    elm = (RGST_AttributeElem_t *)hash_lookup_obj(name,attr->table);
    hash_del(name,attr->table);
    if (elm != NULL) {
      if ((assoc == A_OBJECT) && (attr->obj_head   == elm)) attr->obj_head   = elm->next;
      if ((assoc == A_TYPE)   && (attr->type_head  == elm)) attr->type_head  = elm->next;
      if ((assoc == A_FIELD)  && (attr->field_head == elm)) attr->field_head = elm->next;
      if (elm->prev != NULL) elm->prev->next = elm->next;
      if (elm->next != NULL) elm->next->prev = elm->prev;
      elm = rgst_free_RGST_AttributeElem_t(elm);
    }
  }
  if (assoc == A_OBJECT) {
    if ((ro = rgst_get_RGST_Object_t(name)) != NULL) {
      AttrArray_del(attr_name, ro->attributes);
    }
  }
  else if (assoc == A_TYPE) {
    if ((td = rgst_get_td_defn(name,NUM_RGST_Datatype_t, &data_type)) != NULL) {
      switch (data_type) {
        case R_STRUCT:
        case R_STRUCT_TYPEDEF: sd = (RGST_StructTypeDef_t *)td;
                               AttrArray_del(attr_name,sd->attributes);
                               break;
        case R_CTYPE_TYPEDEF:  cd = (RGST_CTypeDef_t *)td;
                               AttrArray_del(attr_name,cd->attributes);
                               break;
        case R_ENUM_TYPEDEF:   ed = (RGST_EnumTypeDef_t *)td;
                               AttrArray_del(attr_name,ed->attributes);
                               break;
        default:               ctlerror(me,logic_err);
      }
    }
  }
  else if (assoc == A_FIELD) {
    if ((sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(type_name,R_STRUCT_TYPEDEF, &data_type)) != NULL) {
      if ((fld_ndx = rgst_get_ds_field_ndx(sd, fld_name)) < 0)
        return(-1);
      fd = &(sd->fields[fld_ndx]);
      AttrArray_del(attr_name,fd->attributes);
    }
  }
  return(0);
}
int rgst_del_attrs_from_fields(
  char *type,        
   ...)              
{
  char *me = "rgst_add_attrs_to_fields";
  char msg[128];
  char *attr;
  int i;
  RGST_Datatype_t data_type;
  RGST_StructTypeDef_t *sd = NULL;
  va_list ap;
  sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(type, NUM_RGST_Datatype_t, &data_type);
  if ((data_type != R_STRUCT) && (data_type != R_STRUCT_TYPEDEF)) {
    sprintf(msg,"Invalid call: '%s' is not a structure",type);
    ctlerror(me,msg);
  }
  va_start(ap, type);
  attr = va_arg(ap, char *);
  while (attr != NULL) {
    for (i=0; i<sd->num_fields; i++) {
      rgst_del_attr(A_FIELD, type, sd->fields[i].name, attr);
    }
    attr = va_arg(ap, char *);
  }
  va_end(ap);
  return(0);
}
#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "irsrgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
void rgst_del_attr_all(
  char *attr_name)      
{
  char *me = "rgst_del_attr_all";
  char type[128], field[128];
  RGST_Attribute_t *attr;
  if ((attr = rgst_get_t(attr_name,RGST_Attribute_t_STR)) == NULL)
    return;
  while (attr->obj_head != NULL)
    RGST_DEL_OBJECT_ATTR(attr->obj_head->name, attr_name);
  while (attr->type_head != NULL)
    RGST_DEL_TYPE_ATTR(attr->type_head->name, attr_name);
  while (attr->field_head != NULL) {
    memset(type,'\0',128);
    memset(field,'\0',128);
    if (rgst_split_type_n_fld(attr->field_head->name, type, field) != 0)
      ctlerror(me,logic_err);
    RGST_DEL_FIELD_ATTR(type, field, attr_name);
  }
}
