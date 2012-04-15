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
int rgst_check_ndxs(
  long nelms,
  long lo_ndx,
  long hi_ndx,
  long *ret_lo_ndx, 
  long *ret_hi_ndx)
{
  char *me = "rgst_check_ndxs";
  char msg[256];
  int  return_val = 0;
  if (lo_ndx < 0) {
    *ret_lo_ndx = 0;
  }
  else {
    if (lo_ndx >= nelms) {
      sprintf(msg,"\n\tArray subrange low index of %d is bad"
                  "\n\tArray has elements numbered 0 - %d",
                  (int)lo_ndx, (int)nelms-1);
      printf("\n");
      ctlnotice(me,msg);
      *ret_lo_ndx = nelms-1;
      return_val  = -1;
    }
    else {
      *ret_lo_ndx = lo_ndx;
    }
  }
  if (hi_ndx < 0) {
    *ret_hi_ndx = nelms-1;
  }
  else {
    if (hi_ndx >= nelms) {
      sprintf(msg,"\n\tArray subrange high index of %d is bad"
                  "\n\tArray has elements numbered 0 - %d",
                  (int)hi_ndx, (int)nelms-1);
      printf("\n");
      ctlnotice(me,msg);
      *ret_hi_ndx = nelms-1;
      return_val  = -1;
    }
    *ret_hi_ndx = hi_ndx;
  }
  return(return_val);
}
