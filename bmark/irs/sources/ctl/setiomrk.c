#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void setiomrk(
	    char     *string,	   int	    nlen )
{
   char *me = "setiomrk";
   char msg[256];
   int i;
   iomrkrset = 0 ;
   iomrkflag = 1 ;
   iomrkstr  = string ;
   iomrkstr[0] = '\0' ;
   iomrkps = NULL ;
   if (ps != NULL ) {
     memset(string,'\0',nlen);     
     strncpy(string,ps,nlen) ;
   }      
   else {
     sprintf(msg,"got ps = NULL line = '%s'\n",line);
     for (i=0; i<strlen(msg); i++) { 
       if (msg[i] == '\n') { msg[i] = ' '; } 
     }
     ctlnotice(me,msg);
   }
}
