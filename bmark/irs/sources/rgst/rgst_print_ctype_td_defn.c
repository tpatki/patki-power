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
void rgst_print_ctype_td_defn(
  RGST_CTypeDef_t *cd)      
{
  char buff[128];
  rgst_create_typedef_name_str 
    (cd->type, NULL, cd->nptrs, cd->ndims, cd->dims, buff);
  printf("CTYPE typedef '%s' is '%s' which is %d bytes\n",
         cd->name, buff, (int)(cd->type_size));
}
