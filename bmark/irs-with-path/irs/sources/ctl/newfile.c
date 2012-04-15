#include <signal.h>
#include "irs.h"
#include "irsctl.h"
int  newfile( char     *filename , int errflag)
{
   int error ;
   FILE *fpsave ;
   char *me = "newfile";
   char msg[128]; 
   error = 0 ;
   fpsave = fpin ;
   fpin = fopen(filename,"r") ;
   if (fpin == NULL) {
      if (errflag == 1) {
         sprintf(msg,"can't open file %s",filename);
         ctlnotice(me,msg);
      }
      error = 1 ;
      fpin = fpsave ;
   } else {
      fpold[++lastfile] = fpin ;
      ps = NULL ;
   }
   return(error) ;
}
