#include <signal.h>
#include "irs.h"
#include "irslag.h"
#include "CycleMesg.h"
int step( void )
{
   int ncycle, cflag ;
   double ntime ;
   ncycle = geti(&cflag) ;
   ntime  = getf(&cflag) ;
   signal(SIGINT,setirup) ;
   xirs(ncycle,ntime) ;
   signal(SIGINT,SIG_DFL) ;
   printtc() ;
   return(0);
}
