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
int rgst_add_attr(
  ATTR_Assoc_t assoc, 
  ...)              
{
  char *me = "rgst_add_attr";
  char msg[128], type_n_fld_name[128];
  int i, fld_ndx, error = FALSE;
  va_list ap;
  RGST_Datatype_t data_type;
  char                 *name       = NULL,
                       *type_name  = NULL,
                       *fld_name   = NULL,
                       *attr_name  = NULL;
  void                 *td         = NULL;
  RGST_Object_t        *ro         = NULL;
  RGST_Attribute_t     *attr       = NULL;
  RGST_AttributeElem_t *elm        = NULL;
  RGST_StructTypeDef_t *sd         = NULL;
  RGST_EnumTypeDef_t   *ed         = NULL;
  RGST_CTypeDef_t      *cd         = NULL;
  RGST_Field_t         *fd         = NULL;
  AttrArray_t         *attributes = NULL;
  if ((assoc < 0) || (assoc >= NUM_ATTR_Assoc_t))
    ctlerror(me,logic_err);
  va_start(ap, assoc);
  name = va_arg(ap, char *);
  if (assoc == A_FIELD) {
    type_name = name;
    fld_name  = va_arg(ap, char *);
    sprintf(type_n_fld_name,"%s:%s",type_name,fld_name);
    name = type_n_fld_name;
  }
  attr_name = va_arg(ap, char *);
  va_end(ap);
  if (rgst_check_attr_name(attr_name, name) != 0)
    return(-1);
  if ((attr = rgst_get_attr_type(attr_name)) == NULL)
    return(-1);
  switch (assoc) {
   case A_OBJECT :
    if ((ro = rgst_get_RGST_Object_t(name)) == NULL) {
      sprintf(msg,"\n\tObject '%s' is not in the registry",name);
      ctlwarning(me,msg);
      return(-1);
    }
    if (AttrArray_search(attr_name,ro->attributes) != NULL) {
      return(0);
    }
    if ((hash_lookup_elm(name, attr->table)) != NULL) {
      ctlerror(me,logic_err);
      return(-1);
    }
    elm = rgst_create_RGST_AttributeElem_t(name,A_OBJECT,(RGST_Datatype_t)0,ro,NULL);
    if (elm == NULL)
      return(-1);
    hash_add(name,"object attribute",elm,attr->table);
    elm->next = attr->obj_head;
    if (attr->obj_head != NULL) {
      attr->obj_head->prev = elm;
    }
    attr->obj_head = elm;
    AttrArray_add(attr,ro->attributes);
    break;
   case A_TYPE :
    td = rgst_get_td_defn(name,NUM_RGST_Datatype_t, &data_type);
    if (td == NULL) return(-1);
    switch (data_type) {
     case R_STRUCT:
     case R_STRUCT_TYPEDEF:
      sd         = (RGST_StructTypeDef_t *)td;
      attributes = sd->attributes;
      break;
     case R_CTYPE_TYPEDEF:
      cd         = (RGST_CTypeDef_t *)td;
      attributes = cd->attributes;
      break;
     case R_ENUM_TYPEDEF:
      ed         = (RGST_EnumTypeDef_t *)td;
      attributes = ed->attributes;
      break;
     default:
      sprintf(msg,"\n\t'%s' is not a type definition known by the registry",
                   name);
      ctlwarning(me,msg);
      return(-1);
    }
    if (AttrArray_search(attr_name,attributes) != NULL) {
      return(0);
    }
    if ((hash_lookup_elm(name, attr->table)) != NULL) {
      ctlerror(me,logic_err);
      return(-1);
    }
    elm = rgst_create_RGST_AttributeElem_t(name,A_TYPE,data_type,td,NULL);
    if (elm == NULL)
      return(-1);
    hash_add(name,"type attribute",elm,attr->table);
    elm->next = attr->type_head;
    if (attr->type_head != NULL) {
      attr->type_head->prev = elm;
    }
    attr->type_head = elm;
    AttrArray_add(attr, attributes);
    break;
   case A_FIELD :
    sd = (RGST_StructTypeDef_t *)rgst_get_td_defn(type_name,R_STRUCT_TYPEDEF, &data_type);
    if (sd == NULL)
      return(-1);
    if ((fld_ndx = rgst_get_ds_field_ndx(sd, fld_name)) < 0)
      return(-1);
    fd = &(sd->fields[fld_ndx]);
    if (AttrArray_search(attr_name,fd->attributes) != NULL) {
      return(0);
    }
    if ((hash_lookup_elm(name, attr->table)) != NULL) {
      ctlerror(me,logic_err);
      return(-1);
    }
    elm = rgst_create_RGST_AttributeElem_t(name,A_FIELD,data_type,sd,fd);
    if (elm == NULL)
      return(-1);
    hash_add(name,"field attribute",elm,attr->table);
    elm->next = attr->field_head;
    if (attr->field_head != NULL) {
      attr->field_head->prev = elm;
    }
    attr->field_head = elm;
    AttrArray_add(attr, fd->attributes);
    break;
   default : ctlerror(me,logic_err);
  }
  return(0);
}
int rgst_add_attrs(
  ATTR_Assoc_t assoc, 
  ...)              
{
  char *me = "rgst_add_attrs";
  char *name = NULL, *field = NULL, *attr = NULL;
  va_list ap;
  if ((assoc < 0) || (assoc >= NUM_ATTR_Assoc_t))
    ctlerror(me,logic_err);
  va_start(ap, assoc);
  name = va_arg(ap, char *);
  if (assoc == A_FIELD) {
    field  = va_arg(ap, char *);
  }
  attr = va_arg(ap, char *);
  while (attr != NULL) {
    switch (assoc) {
      case A_OBJECT: 
      case A_TYPE:   rgst_add_attr(assoc, name,         attr); break;
      case A_FIELD:  rgst_add_attr(assoc, name, field , attr); break;
      default:       ctlerror(me,logic_err);
    }
    attr = va_arg(ap, char *);
  }
  va_end(ap);
  return(0);
}
int rgst_add_mult_attrs(
  ATTR_Assoc_t assoc, 
  ...)              
{
  char *me = "rgst_add_mult_attrs";
  char *type = NULL, **things, **attrs;
  int i, j;
  va_list ap;
  if ((assoc < 0) || (assoc >= NUM_ATTR_Assoc_t))
    ctlerror(me,logic_err);
  va_start(ap, assoc);
  if (assoc == A_FIELD) {
    type = va_arg(ap, char *);
  }
  things = va_arg(ap, char **);
  attrs  = va_arg(ap, char **);
  va_end(ap);
  for (i=0; things[i] != NULL; i++) {
    for (j=0; attrs[j] != NULL; j++) {
      switch (assoc) {
        case A_OBJECT: 
        case A_TYPE:   rgst_add_attr(assoc,       things[i], attrs[j]); break;
        case A_FIELD:  rgst_add_attr(assoc, type, things[i], attrs[j]); break;
        default:       ctlerror(me,logic_err);
      }
    }
  }
  return(0);
}
int rgst_add_attrs_to_fields(
  char *type,       
  ...)	            
{
  char *me = "rgst_add_attrs_to_fields";
  char msg[128];
  char *attr;
  int  i;
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
      rgst_add_attr(A_FIELD, type, sd->fields[i].name, attr);
    }
    attr = va_arg(ap, char *);
  }
  va_end(ap);
  return(0);
}
