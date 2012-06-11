#include <signal.h>
#include "irs.h"
#include "irsrgst.h"
#include "irsctl.h"
#include "Conditional.h"
#include "CycleMesg.h"
#include "Hash.h"
#include "TimePlot.h"
#define TRASHLEN 1024
int redofq(void)
{
  char *me = "redofq";
  char trash[TRASHLEN];
  int nfqsave, ncycsave, ntpsave, i, j, icur;
  int error = 0, msgnum, msgtype;
  if (getfq(&msgtype,&msgnum) != 0) return(1);
  if ( msgtype == 0 ) {
    ncycsave = ncyc   ;
    ncyc     = msgnum ;
    if (cyc[msgnum].msg != NULL)  {
      FREEMEM(cyc[msgnum].msg) ;
    }
    if (cyc[msgnum].name != NULL) {
      rgst_del(cyc[msgnum].name);
      FREEMEM (cyc[msgnum].name);
    }
    fqcyc(msgtype)  ;
    ncyc = ncycsave ;
  }
  if ( msgtype == 1 ) {
    nfqsave = nfq    ;
    nfq     = msgnum ;
    if (fq[msgnum].msg != NULL) {
      FREEMEM(fq[msgnum].msg) ;
    }
    if (fq[msgnum].name != NULL) {
      rgst_del(fq[msgnum].name);
      FREEMEM (fq[msgnum].name);
    }
    fqcyc(msgtype) ;
    nfq = nfqsave  ;
  }
  if ( msgtype == 2 ) {
    nfqsave = nfq;
    nfq     = msgnum;
    ntpsave = ntp;
    ntp     = fqtp[msgnum];
    rgst_del(fq[msgnum].name);
    if (fq[msgnum].name != NULL) FREEMEM(fq[msgnum].name);
    if (fq[msgnum].msg  != NULL) FREEMEM(fq[msgnum].msg) ;
    i = fqtp[msgnum] ;
    for ( icur = 0 ; icur < tpdata[i]->num_tp_curs ; icur++) {
      rgst_del(tpdata[i]->tp_curs[icur]->name);
      tpdata[i]->tp_curs[icur] = TimePlotCurve_destruct(tpdata[i]->tp_curs[icur]);    }
    rgst_del(tpdata[i]->name);
    tpdata[i] = TimePlot_destruct(tpdata[i]);
    while (fqcyc(msgtype) != 0) {
      if (ctlflag != iflf) get_words_at_prompt(trash,TRASHLEN);
      ctlnotice(me,"\n\ttry again -- reenter the new timeplot message"
                   "\n\tDo not enter 'timeplot' before the message");
    }
    ntp = ntpsave;
    nfq = nfqsave;
  }
  if ( msgtype == 3 ) {
    ncycsave = ncyc;
    ncyc     = msgnum;
    ntpsave  = ntp;
    ntp      = cyctp[msgnum];
    rgst_del(cyc[msgnum].name);
    if (cyc[msgnum].name != NULL) FREEMEM(cyc[msgnum].name);
    if (cyc[msgnum].msg  != NULL) FREEMEM(cyc[msgnum].msg) ;
    i = cyctp[msgnum] ;
    for ( icur = 0 ; icur < tpdata[i]->num_tp_curs ; icur++) {
      rgst_del(tpdata[i]->tp_curs[icur]->name);
      tpdata[i]->tp_curs[icur] = TimePlotCurve_destruct(tpdata[i]->tp_curs[icur]);    }
    rgst_del(tpdata[i]->name);
    tpdata[i] = TimePlot_destruct(tpdata[i]);
    while (fqcyc(msgtype) != 0) {
      if (ctlflag != iflf) get_words_at_prompt(trash,TRASHLEN);
      ctlnotice(me,"\n\ttry again -- reenter the new timeplot message"
                   "\n\tDo not enter 'timeplot' before the message");
    }
    ntp  = ntpsave;
    ncyc = ncycsave;
  }
  if ( msgtype == 4 ) {
     error = conditionals_redo(msgnum);
  }
  return(error);
}
