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
char **rgst_list_vars_with_attr(
  char *attr_name,      
  int  *num_vars)       
{
  char *me = "rgst_list_vars_with_attr";
  char **varlist = NULL;
  int  numvars = 0, numvars_2 = 0;
  RGST_AttributeElem_t *elm_ptr;
  numvars_2 = RGST_NUM_OBJECTS_WITH_ATTR(attr_name);
  if (numvars_2 > 0)  {
    varlist = ALLOT(char *, numvars_2); 
    elm_ptr = RGST_LIST_OBJECTS_WITH_ATTR(attr_name);
    while (elm_ptr != NULL) {
      varlist[numvars] = strsave(elm_ptr->name);
      numvars++;
      elm_ptr = elm_ptr->next;
    }
  }
  *num_vars = numvars;
  return(varlist);
}
