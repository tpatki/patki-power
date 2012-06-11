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
int rgst_query_attr(
  ATTR_Assoc_t assoc, 
  ...)              
{
  char *me = "rgst_query_attr";
  char msg[128], type_n_fld_name[128];
  va_list ap;
  char *fld_name         = NULL,
       *attr_name        = NULL,
       *name             = NULL;
  RGST_Attribute_t *attr   = NULL;
#ifndef NDEBUG
  if ((assoc < 0) || (assoc >= NUM_ATTR_Assoc_t)) ctlerror(me,logic_err);
#endif
  va_start(ap, assoc);
  name = va_arg(ap, char *);
  if (assoc == A_FIELD) {
    fld_name = va_arg(ap, char *);
    sprintf(type_n_fld_name,"%s:%s",name,fld_name);
    name = type_n_fld_name;
  }
  attr_name = va_arg(ap, char *);
  if (attr_name == NULL) {
    sprintf(msg,"No attributes given in query of '%s'",name);
    ctlwarning(me,msg);
    return(FALSE);
  }
  while(attr_name != NULL) {
    if ((attr = rgst_get_t(attr_name,RGST_Attribute_t_STR)) == NULL)
      return(FALSE);
    if (hash_lookup_elm(name,attr->table) == NULL)
      return(FALSE);
    attr_name = va_arg(ap, char *);
  }
  va_end(ap);
  return(TRUE);
}
