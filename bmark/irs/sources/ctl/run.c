#include <signal.h>
#include "irs.h"
#include "irslag.h"
#include "irsctl.h"
int run( void )
{
   char *me = "run";
   char message[MAXLINE] ;
   int termfg, lasttermfg, nxcy ;
   double nxtm ;
   signal(SIGINT,setirup) ;
   termfg     = TERMFLG_READY ;
   lasttermfg = TERMFLG_READY ;
   while ( TRUE ) {
      termfg = domsg() ;
      if ( termfg == TERMFLG_READY ) {
         nxtm = getnxtm() ;
         nxcy = getnxcy() ;
         termfg = xirs(nxcy, nxtm) ;
      }
      if ( ttime >= tstop ) {
         ctlmsg("Stop time reached");
         printtc() ;
         if ( TERMFLG_TSTOP > termfg ) termfg = TERMFLG_TSTOP ;
         break;
      } else if ( cycle >= cstop ) {
         ctlmsg("Stop cycle reached");
         printtc() ;
         if ( TERMFLG_CSTOP > termfg ) termfg = TERMFLG_CSTOP ;
         break;
      }
      if (termfg != TERMFLG_READY)
         break;
   }
   lasttermfg = domsg() ;
   if ( lasttermfg > termfg ) termfg = lasttermfg ;
   signal(SIGINT,SIG_DFL) ;
   return(termfg) ;
}
