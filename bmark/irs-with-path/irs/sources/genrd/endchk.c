#include "irs.h"
#include "irsctl.h"
#include "irsgenrd.h"
extern int pccsflag;
extern int pccsoff;
int endchk( char *newcmd )
{
    if ((!strcmp(newcmd, "end"))||(!strcmp(newcmd, "quit"))) {
       return( TERMFLG_EXIT );
    } else if (!strcmp(newcmd, "run")) {
       if ((pccsflag) && (pccsoff)) {
          PRINT(stdout, "%s in production controller mode\n",codename);
          pccsoff = 0;
       }
       return( TERMFLG_RUN );
    } else if (!strcmp(newcmd, "endmsg")) {
       return( TERMFLG_CHECK );
    } else {
       return( TERMFLG_READY );
    }
}
