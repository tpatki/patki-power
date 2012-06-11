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
RGST_AttributeElem_t *rgst_free_RGST_AttributeElem_t(RGST_AttributeElem_t * ptr)
{
  FREEMEM(ptr->name);
  FREEMEM(ptr);
  return(NULL);
}
