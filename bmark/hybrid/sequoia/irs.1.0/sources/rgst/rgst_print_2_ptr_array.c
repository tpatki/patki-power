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
void rgst_print_2_ptr_array (
  RGST_Datatype_t dt,             
  char *dt_name,                
  void ***ptr,
  long  nelms)
{
  long i;
  void **ptr2d, *ptr1d;
  if (dt != R_CHAR) { rgst_print_ptrs((void **)ptr, 1); }
  ptr2d = *ptr;
  if (ptr2d == NULL) return;
  if (dt != R_CHAR) {  printf("%20s",""); }
  if (nelms < 1) printf("\n");
  for (i=0; i<nelms; i++) {
    ptr1d = ptr2d[i];
    rgst_print_1_ptr_array(dt, dt_name, &ptr1d, 1, -1, -1, -1);
    if (i != (nelms-1)) printf("%20s","");
  }
}
