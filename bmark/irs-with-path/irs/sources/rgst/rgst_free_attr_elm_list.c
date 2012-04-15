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
RGST_AttributeElem_t *rgst_free_attr_elm_list (RGST_AttributeElem_t *ptr)
{
  RGST_AttributeElem_t *next_ptr;
  while (ptr != NULL) {
    next_ptr = ptr->next;
    FREEMEM(ptr->name);
    FREEMEM(ptr);
    ptr = next_ptr;
  }
  return(NULL);
}
