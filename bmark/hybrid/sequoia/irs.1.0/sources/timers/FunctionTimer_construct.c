#include <stdio.h>
#include <stdlib.h>
#include "Hash.h"
#include "FunctionTimer.h"
FunctionTimer_t *FunctionTimer_construct(int num)
{
  char *me = "FunctionTimer_construct";
  char errmsg[128];
  int i;
  FunctionTimer_t *ptr;
  if (num < 1) { 
    sprintf(errmsg,"%s: num < 1",me);
    FunctionTimer_error(me,errmsg);
  }
  ptr = ALLOT(FunctionTimer_t, num);
  if (ptr == NULL) { FunctionTimer_error(me,ft_out_of_memory); }
  for (i=0; i<num; i++) {
    FunctionTimer_init(&(ptr[i]));
  }
  return(ptr);
}
