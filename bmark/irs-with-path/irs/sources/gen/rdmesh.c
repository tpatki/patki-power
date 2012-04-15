#include "irs.h"
#include "irsgen.h"
int rdmesh( void )
{
   char *me = "rdmesh";
   int error = 0;
   char op[MAXLINE];
   char msg[MAXLINE];
   geta(op);
   if (!strcmp("truegrid",op)) {
      error = rdtruegrid();
   } else if (!strcmp("silo",op)) {

#ifdef SILO
      error = rdsilogrid();
#endif

   } else {
      sprintf(msg,"Input Mesh Format - %s not supported.\n",op);
      ctlnotice(me,msg);
      error = 1;
   }
   return(error);
}
