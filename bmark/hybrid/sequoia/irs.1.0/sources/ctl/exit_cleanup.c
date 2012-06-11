#include <stdio.h>			
#include <stdlib.h>			
#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"                    
int exit_cleanup (void) 
{
   if (ifmpi) { MPI_Finalize_Wrapper(); }
   return(0);
}
