#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int rgst_check_attr_name(
  char *attr_name,  
  char *obj_name)   
{
  char *me = "rgst_check_attr_name";
  char msg[256];
  if (strstr(attr_name," ") != NULL) {
    sprintf(msg,"\n\tAttribute '%s' for object or structure %s' rejected."
                "\n\tSpaces not currently allowed within attributes",
                attr_name,obj_name);
    ctlnotice(me,msg);
    return(-1);
  }
  return(0);
}
