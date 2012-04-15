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
void rgst_create_typedef_name_str(
  RGST_Datatype_t type,     
  char        *type_name, 
  int         nptrs,      
  int         ndims,      
  int         dims[3],    
  char        *buff)      
{
  int  i;
  char str[128];
  buff[0] = '\0'; 
  if (type < NUM_RGST_Datatype_t) {
    strcat(buff,rgst_datatype_strs[type]);
  }
  if (type_name != NULL) {
    sprintf(str," %s ",type_name);
    strcat(buff,str);
  }
  for (i=0; i<nptrs; i++) {
    strcat(buff," *");
  }
  if (ndims > 0) {
    strcat(buff," [");
    for (i=0; i<ndims; i++) {
      sprintf(str,"%d",dims[i]);
      strcat(buff,str);
      if (i != ndims-1) strcat(buff,",");
    }
    strcat(buff,"]");
  }
}
