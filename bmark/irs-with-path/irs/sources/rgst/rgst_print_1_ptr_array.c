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
static void print_strs (char **strs, long lo_ndx, long hi_ndx)
{
  long i;
  char printed_a_line_yet = FALSE;
  if (hi_ndx < lo_ndx) printf("\n");
  for (i=lo_ndx; i<=hi_ndx; i++) {
    if (strs[i] != NULL) {
      if (printed_a_line_yet == TRUE) printf("%20s",""); 
      printf("%s\n",strs[i]);
      printed_a_line_yet = TRUE;
    }
  }
  if (printed_a_line_yet == FALSE) printf("\n");
}
void rgst_print_1_ptr_array (
  RGST_Datatype_t dt,             
  char          *dt_name,       
  void          *ptr,           
  long          dim_nelms,      
  long          ptr_nelms,      
  long          lo_ndx,         
  long          hi_ndx)         
{
  char *me = "rgst_print_1_ptr_array";
  char *errmsg1 = "\n\tProgrammer Error : "
                  "\n\tEither dim_nelms or ptr_nelms is to be used"
                  "\n\tOne must be -1 and the other must be 0 or greater";
  long i;
  long my_lo_ndx, my_hi_ndx;
  void *myptr;
  if (dim_nelms == -1) {
    if (ptr_nelms < 0) { ctlerror(me,errmsg1); }
  }
  else if (ptr_nelms == -1) {
    if (dim_nelms < 0) { ctlerror(me,errmsg1); }
  }
  else {
    ctlerror(me,errmsg1);
  }
  if (dim_nelms > -1) {
    if (rgst_check_ndxs (dim_nelms,lo_ndx,hi_ndx,&my_lo_ndx,&my_hi_ndx) != 0)
      return;
    if   (dt == R_CHAR) {
      print_strs((char **)ptr, my_lo_ndx, my_hi_ndx);
    }
    else {
      for (i=my_lo_ndx; i<=my_hi_ndx; i++)  {
        myptr = (void *)((void **)ptr)[i];
        rgst_print_0_ptr_array(dt, dt_name, myptr, 1, -1, -1);
      }
    }
  }
  else {
    if (rgst_check_ndxs (ptr_nelms,lo_ndx,hi_ndx,&my_lo_ndx,&my_hi_ndx) != 0)
      return;
    myptr = (void *)(*(void **)ptr);
    rgst_print_0_ptr_array(dt, dt_name, myptr, ptr_nelms, lo_ndx, hi_ndx);
  }
}
