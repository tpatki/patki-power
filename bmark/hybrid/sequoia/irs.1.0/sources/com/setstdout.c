#include "irs.h"
#include "FunctionTimer.h" 
#include "irscom.h"
#include "irsdmp.h"
int setstdout(int id) {

   char soutname[MAXLINE * 2];
   char fullname[MAXLINE * 2];

   if (myid != id) {

      if (child_io_off == TRUE) {

         freopen("/dev/null","a",stdout);

      } else {

         if (child_io_todir == TRUE) {

            sprintf(soutname,"%s/%s-%04i-out",child_outpath,pbnm,myid);
            strcpy(fullname,soutname);
            freopen(fullname,"a",stdout);
      
         } else {

            sprintf(soutname,"%s-%04i-out",pbnm,myid);
            strcpy(fullname,outpath);
            strcat(fullname,soutname);
            freopen(fullname,"a",stdout);
         }
      }
   }

   return(0); 
}

