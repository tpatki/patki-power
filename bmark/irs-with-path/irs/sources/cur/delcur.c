#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int delcur( void )
{
   char *me = "delcur";
   int cn,cflag ;
   char op[MAXWORD],msg[128];
   cn = geti(&cflag) ;
   if (cflag)
      {
      geta(op) ;
      if (strcmp(op,"all"))
         {
         sprintf(msg,"'%s' found after delcur instead of expected 'all'",op);
         ctlnotice(me,msg);
         }
      cn = -1 ;
      }
   delcur0(cn) ;
   return(0);
}
