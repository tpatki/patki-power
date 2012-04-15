#include <signal.h>
#include "irs.h"
#include "irsctl.h"
int showfq( void )
{
  char *me = "showfq";
  int error, msgnum, msgtype;
  if (getfq(&msgtype,&msgnum) != 0) return(1);
  error = printmsg(msgtype,msgnum) ;
  return(error);
}
