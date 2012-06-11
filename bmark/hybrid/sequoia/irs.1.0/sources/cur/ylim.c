#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int ylim( void )
{
   char *me = "ylim";
   int cflag ;
   double y ;
   char op[MAXWORD], msg[128];
   y = getf(&cflag) ;
   if (cflag)
      {
      geta(op) ;
      if (strcmp(op,"de")) {
         sprintf(msg,"'%s' found after ylim instead of expected 'de'",op);
         ctlnotice(me,msg);
      }
      ylimfg = 0 ;
   }
   else {
      ylimfg = 1 ;
      ymn = y ;
      ymx = getf(&cflag) ;
   }
   return(0);
}
