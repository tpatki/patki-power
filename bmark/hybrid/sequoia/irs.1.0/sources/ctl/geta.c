#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void geta(char *s)	
{
   nxtsym(1);
   while (sym[0] == '$') {symflag = 0 ; nxtsym(1) ;}
   strcpy(s, sym);
   symflag = 0;
   return ;
}
