#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int xlim( void )
{
   char *me = "xlim";
   int cflag ;
   double x ;
   char op[MAXWORD], msg[128];
   x = getf(&cflag) ;
   if (cflag) {
      geta(op) ;
      if (strcmp(op,"de")) {
         sprintf(msg,"'%s' found after xlim instead of expected 'de'",op);
         ctlnotice(me,msg);
      }
      xlimfg = 0 ;
   }
   else {
      xlimfg = 1 ;
      xmn = x ;
      xmx = getf(&cflag) ;
   }
   return(0);
}
