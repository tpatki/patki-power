#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int rgst_split_type_n_fld (
  char *type_n_fld,  
  char *type,        
  char *field)       
{
  char *me = "rgst_split_type_n_fld";
  char *ptr;
  if ((ptr = strchr(type_n_fld, ':')) == NULL)
    return(-1);
  strncpy(type, type_n_fld, (ptr - type_n_fld));
  type[ptr - type_n_fld] = '\0';
  ptr++;
  strcpy(field, ptr);
  return(0);
}
