#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "irs.h"
#include "irs.h"
#include "Hash.h"
#include "Rgst.h"
#include "irsrgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
int rgst_extract_array_ndxs(
  char *str,            
  long *lo_ndx,         
  long *hi_ndx)         
{
  char *me = "rgst_extract_array_ndxs";
  char msg[256];
  char *ptr, *endptr;
  long my_lo_ndx, my_hi_ndx;
  *lo_ndx = *hi_ndx = my_lo_ndx = my_hi_ndx = -1;
  if ((ptr = strchr(str,'[')) == NULL)  {
    if ((ptr = strchr(str,'(')) == NULL)  {
      return(0);
    }
  }
  if ((strchr(ptr,')')) == NULL) {
    if ((strchr(ptr,']')) == NULL) {
      sprintf(msg,"Trailing ')'  or ']' in '%s' missing",str);
      ctlnotice(me,msg);
      return(-1);
    }
  }
  ptr++;
  my_lo_ndx = strtol(ptr, &endptr, 10); 
  if ((ptr == endptr) || (my_lo_ndx == LONG_MIN) || (my_lo_ndx == LONG_MAX)) { 
    sprintf(msg,"Did not find valid number after '[' or '(' in '%s'",str);
    ctlnotice(me,msg);
    return(-1);
  }
  while ((!isdigit(*endptr)) && (*endptr != '\0')) endptr++;
  if (isdigit(*endptr)) {
    my_hi_ndx = strtol(endptr, NULL, 10);
    if ((my_hi_ndx == LONG_MIN) || (my_hi_ndx == LONG_MAX)) {
      sprintf(msg,"Did not find valid number starting at '%s'",endptr);
      ctlnotice(me,msg);
      return(-1);
    } 
  }
  ptr--;
  while (*ptr != '\0') {
    *ptr = '\0';
    ptr++;
  }
  if (my_hi_ndx == -1) my_hi_ndx = my_lo_ndx;
  *lo_ndx = my_lo_ndx;
  *hi_ndx = my_hi_ndx;
  return(0);
}
