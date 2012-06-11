#include <signal.h>
#include "irs.h"
#include "irsctl.h"
int  geti( int *cflag )
{
   int isgood ;
   nxtsym(1) ;
   while ( sym[0] == '$' ) {
      symflag = 0 ;
      nxtsym(1) ;
   }
   isgood = 0 ;
   if ((sym[0] == '-') || (sym[0] == '+')) isgood = 1 ;
   if (('0' <= sym[0]) && (sym[0] <= '9')) isgood = 1 ;
   if (isalpha(sym[0]) || (!strcmp(sym, "*")) || (sym[0] == '$')) {
      *cflag = 1 ;
      return(0)  ;
   } else if (isgood == 0) {
      *cflag  = 1 ;
      symflag = 1 ;
      return(0) ;
   } else {
      *cflag  = 0 ;
      symflag = 0 ;
      return(atoi(sym)+iplusmin) ;
   }
}
