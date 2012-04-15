#include "irs.h"
#include "irsctl.h"
#include "AEStackElm.h"
int eval( void ) 
{
   char *me = "eval";
   char op[MAXWORD];
   int cflag;
   double my_dbl;
   if (output_dest == TO_STACK) {
      my_dbl = getf(&cflag);
      ctloutput(me,NULL,R_DOUBLE,my_dbl);
   } else {
      geta(op);
      ctlmsg(op);
   }
   return(0);
}
