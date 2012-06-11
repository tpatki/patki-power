#include <signal.h>
#include "irs.h"
#include "irsctl.h"
#include "CycleMesg.h"
#include "TimePlot.h"
int getfq(
  int *msgtype,    
  int *msgnum)     
{
  char *me = "getfq";
  char msgop[16], msg[128];
  int  cflag, i, count;
  int num_timeplots, num_cycleplots;
  int *fqlst ;
  geta(msgop) ;
  if         (!strcmp(msgop,"cyc"))        *msgtype = 0;
  else if (  (!strcmp(msgop,"freq"))
          || (!strcmp(msgop,"do")))        *msgtype = 1;
  else if (  (!strcmp(msgop,"tp"))
          || (!strcmp(msgop,"timeplot")))  *msgtype = 2;
  else if (  (!strcmp(msgop,"cp"))
          || (!strcmp(msgop,"cycleplot"))) *msgtype = 3;
  else if (  (!strcmp(msgop,"when"))
          || (!strcmp(msgop,"once"))
          || (!strcmp(msgop,"atexit")))    *msgtype = 4;
  else {
     sprintf (msg, "redomsg %s -- unknown message type", msgop ) ;
     ctlnotice(me,msg) ;
     return(-1) ;
  }
  *msgnum = geti(&cflag) ;
  (*msgnum)--;
  if (*msgtype == 0) {
    if (*msgnum >= ncyc) {
      sprintf(msg, "redomsg cyc %d invalid -- only %d cyc messages",*msgnum,ncyc);
      ctlnotice(me,msg) ;
      return(-1) ;
    }
  }
  if (*msgtype == 1) {
    fqlst = ALLOT(int,maxtimeplot) ;
    count = 1 ;
    for ( i = 0 ; i < nfq ; i++ ) {
      if ( fqtp[i] == -1 ) {
        fqlst[count] = i ;
        count++ ;
      }
    }
    count-- ;
    if (*msgnum > count) {
      sprintf(msg,"redomsg freq %d invalid -- only %d freq messages",*msgnum,count);
      ctlnotice(me,msg) ;
      return(-1) ;
    }
    *msgnum = fqlst[*msgnum] ;
    FREEMEM(fqlst) ;
  }
  num_timeplots = 0;
  if (*msgtype == 2) {
    for ( i = 0 ; i < nfq ; i++ ) {
      if (fqtp[i] >= 0) num_timeplots++;
      if ( fqtp[i] == *msgnum ) {
        *msgnum = i;
        break;
      }
    }
    if (i == nfq) {
      sprintf(msg,"\n\tredomsg timeplot or tp %d invalid"
                  "\n\tonly %d timeplot messages (numbered 0 - %d)",
                   *msgnum,num_timeplots,num_timeplots-1);
      ctlnotice(me,msg);
      return(-1);
    }
  }
  num_cycleplots = 0;
  if (*msgtype == 3) {
    for ( i = 0 ; i < ncyc ; i++ ) {
      if (cyctp[i] >= 0) num_cycleplots++;
      if ( cyctp[i] == *msgnum ) {
        *msgnum = i ;
        break ;
      }
    }
    if (i == ncyc) {
      sprintf(msg,"\n\tredomsg cycleplot or cp %d invalid"
                  "\n\tonly %d timeplot messages (numbered 0-%d)",
                   *msgnum,num_cycleplots,num_cycleplots-1);
      ctlnotice(me,msg);
      return(-1);
    }
  }
  return(0);
}
