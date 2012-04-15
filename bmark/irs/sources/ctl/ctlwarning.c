#include <stdio.h>              
#include "irs.h"
#include "irsctl.h"   
void ctlwarning (
   char proc_name[],     
   char msg[])           
{
   char *me = "ctlwarning";
   char hiliteon[9] = "\000", hiliteoff[5] = "\000";
   if (ifhilite) {
     strcpy(hiliteon, INVSTXT YELOTXT);
     strcpy(hiliteoff, NRMLTXT);
   }
   PRINT(stdout,WARN_LINE, hiliteon, hiliteoff);
   PRINT(stdout,PROC_LINE,proc_name);
   PRINT(stdout,MSG_LINE,msg);
   if ((ps != NULL) && (fpin != stdin)) {
      PRINT(stdout,MSG2_LINE,"*ps currently is",ps);
   }
   if ((line != NULL) && (fpin != stdin) && (line[0] != '\0') && (line[0] != '\n')) {
      PRINT(stdout,MSG2_LINE,"line currently is",line);
   }
   PRINT(stdout,DASH_LINE);
   fflush(stdout);
   if (fpout != NULL) {
      PRINT(fpout,WARN_LINE, "", "");
      PRINT(stdout,"+++ Cycle = %d   Time = %e \n", cycle, ttime) ;
      PRINT(fpout,PROC_LINE,proc_name);
      PRINT(fpout,MSG_LINE,msg);
      PRINT(fpout,DASH_LINE);
      fflush(fpout);
   }
}
