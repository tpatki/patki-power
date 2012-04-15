#include <stdlib.h>
#include <stdio.h>             	
#include "Hash.h"
#include "FunctionTimer.h"
void FunctionTimer_error (
  char proc_name[],     
  char msg[])           
{
  fprintf(stderr,"------- Function Timers Library Error ---------\n");
  fprintf(stderr,"Procedure: %s\n",proc_name);
  fprintf(stderr,"%s\n",msg);
  fprintf(stderr,"------- Function Timers Library Error ---------\n");
  exit(EXIT_FAILURE);
}
void FunctionTimer_warning (
  char proc_name[],     
  char msg[])           
{
  fprintf(stderr,"------- Function Timers Library Warning ---------\n");
  fprintf(stderr,"Procedure: %s\n",proc_name);
  fprintf(stderr,"%s\n",msg);
  fprintf(stderr,"------- Function Timers Library Warning ---------\n");
}
