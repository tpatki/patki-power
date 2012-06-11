#include <stdio.h>              
#include "irs.h"
#include "irsctl.h"	
void ctlnotice (
   char proc_name[], 	
   char msg[]) 		
{
   if (ifhilite) {
      PRINT(stdout,UNDRTXT YELOTXT "NOTICE:" NRMLTXT " [%s] %s\n",proc_name,msg);
   } else {
      PRINT(stdout,"NOTICE: [%s] %s\n",proc_name,msg);
   }
   fflush(stdout);
   if (fpout != NULL) {
      PRINT(fpout,"NOTICE: [%s] %s\n",proc_name,msg);
      fflush(fpout);
   }
}
