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
void rgst_print_ptrs (
  void **ptrs,
  long nelms)
{
  long i;
  if (nelms == 0)  printf("\n");
  for (i=0; i<nelms; i++) {
    printf("%ld ",(long)(ptrs[i]));
    if      (i == nelms-1)   printf("\n");
    else if ((i+1) % 5 == 0) printf("\n%20s","");
  }
}
