#include <signal.h>
#include "irs.h"
#include "irsctl.h"
#include "Conditional.h"
#include "CycleMesg.h"
#include "FreqMesg.h"
int printmsg( int msgtype, int msgnum )
{
   char lnout[200], msg2[128];
   int l1, l2, l, error, cflag, msglen, count, termfg ;
   char *msg ;
   error = 0 ;
   if ( msgtype == 0 ) {
      sprintf( msg2, "cyc %d %d %d",
               cyc[msgnum].c1, cyc[msgnum].c2, cyc[msgnum].dc ) ;
      ctlmsg(msg2) ;
      msg    = cyc[msgnum].msg ;
      msglen = cyc[msgnum].msglen ;
   }
   if ( msgtype == 1 ) {
      sprintf( msg2, "do %e %e %e",
               fq[msgnum].t1, fq[msgnum].t2, fq[msgnum].dt ) ;
      ctlmsg(msg2) ;
      msg    = fq[msgnum].msg ;
      msglen = fq[msgnum].msglen ;
   }
   if ( msgtype == 2 ) {
      sprintf( msg2, "timeplot %e %e %e",
               fq[msgnum].t1, fq[msgnum].t2, fq[msgnum].dt ) ;
      ctlmsg(msg2) ;
      msg    = fq[msgnum].msg ;
      msglen = fq[msgnum].msglen;
   }
   if ( msgtype == 4 ) {
      error = conditionals_show(msgnum, &msg, &msglen);
      if (error != 0) return(-1);
   }
   msglen -= 17 ;
   if ( lfchk() == 1 ) {
      l1 =   1 ;
      l2 = 300 ;
   } else {
      l1 = geti(&cflag) ;
      l2 = geti(&cflag) ;
   }
   if ( l1 <   1 )  l1 =   1 ;
   if ( l2 > 300 )  l2 = 300 ;
   count  = 0 ;
   termfg = 0 ;
   for ( l = 1 ; l < l1 ; l++ ) {
      termfg = lnadv(lnout,msg,msglen,&count) ;
      if (termfg) {
         break ;
      }
   }
   for ( l = l1 ; l <= l2 ; l++ ) {
      termfg = lnadv(lnout,msg,msglen,&count) ;
      if (termfg) {
         break ;
      } else {
        sprintf(msg2,"%d %s",l,lnout) ;
        ctlmsg(msg2);
      }
   }
   return(error) ;
}
