#include <signal.h>
#include "irs.h"
#include "irsctl.h"
void initget( void )
{
   lineop_init_readline();
   lnbuf = MALLOT(char, MAXLINE);
   memset(lnbuf,'\0',MAXLINE);
   line = lnbuf;
   strcpy(delim, " ,[]{}():;$%\n\r\t");
   strcpy(nospace,",[]{}();:%") ;
   lastfile = 0;
   ifecho = 1 ;
   iflf = 1 ;
   ifcomfg = 1 ;
   ifexp = 1 ;
   iomrkflag = 0 ;
   *sym = '\0';
   ps = NULL;
   symflag = 0;
   fpin = stdin;
   fpold[lastfile] = fpin;
}
