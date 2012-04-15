#include <stdio.h>
#include <string.h>
#include "irs.h"
#include "irs.h"
#include "irsrgst.h"
#include "Command.h"
#include "Hash.h"
#include "Rgst.h"
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
void rgst_print_function(
  Command_t *cp)            
{
  printf("Function name is '%s' with %d arguments\n",
          cp->name,cp->arg);
}
