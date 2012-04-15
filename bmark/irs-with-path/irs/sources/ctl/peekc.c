#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void peekc(
	    char     *s )
{
   nxtsym(1);
   while (sym[0] == '$') {symflag = 0 ; nxtsym(1) ;}
   memset(s,'\0',10);
   strcpy(s, sym);
}
