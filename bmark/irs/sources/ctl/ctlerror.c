#include <stdio.h>              	
#include <unistd.h>			
#include "irs.h"		
#include "irsctl.h"
#include "FunctionTimer.h"
#include "irscom.h"
void ctlerror (
   char proc_name[],     
   char msg[])           
{
   char *me = "ctlerror";
   char hiliteon[9] = "\000", hiliteoff[5] = "\000";
   if (ctlerror_already_called == TRUE) return;
   ctlerror_already_called = TRUE; 
   if (myid != 0) {
      PRINT(stdout,"NODE %d: Error\n",myid);
   }
   if (ifhilite) {
      strcpy(hiliteon, INVSTXT RED_TXT);
      strcpy(hiliteoff, NRMLTXT);
   }
   PRINT(stdout,ERROR_LINE, hiliteon, hiliteoff);
   PRINT(stdout,"+++ Cycle = %d   Time = %e \n", cycle, ttime) ;
   PRINT(stdout,PROC_LINE,proc_name);
   PRINT(stdout,MSG_LINE,msg);
   PRINT(stdout,DASH_LINE);
   fflush(stdout);
   if ((ifparallel) && (myid != 0)) { 
      PRINT(stderr,ERROR_LINE, "", "");
      PRINT(stderr,"+++ Cycle = %d   Time = %e \n", cycle, ttime) ;
      PRINT(stderr,PROC_LINE,proc_name);
      PRINT(stderr,MSG_LINE,msg);
      PRINT(stderr,DASH_LINE);
      fflush(stderr);
   }
   if (fpout != NULL) {
      PRINT(fpout,ERROR_LINE, "", "");
      PRINT(fpout,PROC_LINE,proc_name);
      PRINT(fpout,MSG_LINE,msg);
      PRINT(fpout,DASH_LINE);
      fflush(fpout);
   }
   if (noerrflag == TRUE) return; 
   if (user_exit_fn != NULL) (*user_exit_fn)();
   if (ifparallel) MPI_Abort_Wrapper(MPI_COMM_WORLD,-1);
   if (coredumpflag == TRUE) abort();
   else                      exit(EXIT_FAILURE);
}
