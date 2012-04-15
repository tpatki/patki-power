#include <stdio.h>              
#include "irs.h"      
#include "irsctl.h"	
void userexitfn (fn_ptr) 
  int (*fn_ptr) (); 	
{
  if (fn_ptr != NULL) user_exit_fn = fn_ptr;
}
