#include <stdio.h>		
#include <signal.h>
#include <limits.h>             
#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "CycleMesg.hh"
#include "FreqMesg.hh"
#include "TimePlot.hh"
int fqcyc (
    int fcflag)	
{
  char *me = "fqcyc";
  char msg[512],  vname[64];
  int  i, cflag, ntplot;
  double tempdbl;
  TimePlotCurve_t    *tpc = NULL, **tpc_array = NULL;
  char *err_maxtimeplot = "\n\t maxtimeplot of %d exceeded"
                      "\n\t This should be >= the total number of"
                      "\n\t timeplot ... endmsg, and"
                      "\n\t do 0.0 25.0 1.0 ... endmsg"
                      "\n\t loops in the deck"
                      "\n\t This can be increased by 'set maxtimeplot 999'"
                      "\n\t Set 999 to whatever limit is necessary";
  char *err_maxcycleplot = "\n\t maxcycleplot of %d exceeded"
                      "\n\t This should be >= the total number of"
                      "\n\t cycleplot ... endmsg"
                      "\n\t loops in the deck"
                      "\n\t This can be increased by 'set maxcycleplot 999'"
                      "\n\t Set 999 to whatever limit is necessary";
  char *err_maxtpdata  = "\n\t maxtpdata of %d exceeded"
                      "\n\t This should be >= the total number of"
                      "\n\t timeplot ... endmsg, and"
                      "\n\t do 0.0 25.0 1.0 ... endmsg and "
                      "\n\t cycleplot ... endmsg"
                      "\n\t loops in the deck"
                      "\n\t This can be increased by 'set maxtpdata 999'"
                      "\n\t Set 999 to whatever limit is necessary";
  char *err_maxtplot = "\n\t maxtplot of %d exceeded"
                      "\n\t This should be >= the largest number pf 'tplot'"
                      "\n\t lines within a single timeplot or cycleplot loop"
                      "\n\t This can be increased by 'set maxtplot 999'"
                      "\n\t Set 999 to whatever limit is necessary";
  if (( fcflag == 1 ) || ( fcflag == 2 )) {
    if ( nfq >= maxtimeplot ) {
      sprintf(msg,err_maxtimeplot,maxtimeplot);
      ctlerror(me,msg);
    }
    fq[nfq].t1 = getf(&cflag);
      if (lfchk() == 1) {
      fq[nfq].t2 = plarge;
      fq[nfq].dt = plarge;
    }
    else {
      fq[nfq].t2 = getf(&cflag);
      if (lfchk() == 1) {
        fq[nfq].dt = plarge;
        sprintf(msg,
          "\n\tTime step unspecified on following line:"
          "\n\t%s"
          "\tDefaulting time step to %e",
          line,fq[nfq].dt);
        ctlnotice(me,msg);
      }
      else {
        fq[nfq].dt = getf(&cflag);	
      }
    }
    ifcomfg = 0 ;
    ifexp   = 0 ;
#ifndef NDEBUG
    if  (fq[nfq].t1 < 0) {
      sprintf(msg,
        "\n\tTime begin of %f on following line is bad--it must be >= 0"
        "\n\t%s",
        fq[nfq].t1,line);
      ctlnotice(me,msg);
      return(1);
    }
    if (fq[nfq].t1 > fq[nfq].t2) {
      sprintf(msg,
        "\n\tTime begin of %f is > time end of %f on following line--"
        "\n\tTime begin must be less than time end"
        "\n\t%s",
        fq[nfq].t1,fq[nfq].t2,line);
      ctlnotice(me,msg);
      return(1);
    }
    if (fq[nfq].dt <= 0) {
      sprintf(msg,
        "\n\tTime step of %f on following line is bad--it must be > 0"
        "\n\t%s",
        fq[nfq].dt,line);
      ctlnotice(me,msg);
      return(1);
    }
#endif
    fq[nfq].nextTime = fq[nfq].t1;
    sprintf(msg,"time_freq_%03d",nfq);
    fq[nfq].name = strsave(msg);
    if ( fcflag == 2 ) {
      if ( ntp >= maxtpdata ) {
        sprintf(msg,err_maxtpdata,maxtpdata);
        ctlerror(me,msg);
      }
      fqtp[nfq] = ntp ;
      if (tpdata[ntp] != NULL) {
          sprintf(msg,"PROGRAMMER ERROR - tpdata[%d] already exists",ntp);
        ctlerror(me,msg);
      }
      tpdata[ntp] = TimePlot_construct(1);
      sprintf(msg,"tp_%03d",ntp);
      tpdata[ntp]->name = strsave(msg);
      tpdata[ntp]->fq_name      = strsave(fq[nfq].name);
      tpdata[ntp]->fq_dat       = &fq[nfq];
      tpdata[ntp]->cyc_name     = NULL;
      tpdata[ntp]->cyc_dat      = NULL;
      tpdata[ntp]->num_data_pts = 0;
      tempdbl = (((fq[nfq].t2 - fq[nfq].t1) / (fq[nfq].dt)) + 10);
      if (tempdbl >= (double)INT_MAX) {
        sprintf(msg,"\n\tTime frequency of %f to %f by %12.10f"
                    "\n\tresults in %e entries."
                    "\n\tTrimming the max number of entries to %d",
                    fq[nfq].t1,fq[nfq].t2,fq[nfq].dt,
                    tempdbl,INT_MAX);
        ctlnotice(me,msg);
        tpdata[ntp]->max_data_pts = INT_MAX;
      }
      else {
        tpdata[ntp]->max_data_pts = (int)tempdbl;
      }
      tpdata[ntp]->inc_data_pts  = NTIMES_INCREMENT;
      tpdata[ntp]->alloc_data_pts = 0;
      tpdata[ntp]->tp_curs       = NULL;
      tpdata[ntp]->tp_curs_names = NULL;
      tpdata[ntp]->num_tp_curs   = 0;
      rgst_add(tpdata[ntp]->name,"TimePlot_t",tpdata[ntp],NULL);
      ntp++;
    }
    rgst_add(fq[nfq].name,"FreqMesg_t",&(fq[nfq]),NULL);
    nfq++;
  }
  else if ((fcflag == 0 ) || (fcflag == 3)) {
    if (ncyc >= maxcycleplot) {
       sprintf(msg,err_maxcycleplot,maxcycleplot);
       ctlerror(me,msg);
    }
    cyc[ncyc].c1 = geti(&cflag) ;
    if (lfchk() == 1) {
      cyc[ncyc].c2 = 10000000;
      cyc[ncyc].dc = 10000000;
    }
    else {
      cyc[ncyc].c2 = geti(&cflag) ;
      if (lfchk() == 1) {
        cyc[ncyc].dc = (cyc[ncyc].c2 - cyc[ncyc].c1) / 10;
        sprintf(msg,
          "\n\tCycle step unspecified on following line:"
          "\n\t%s"
          "\tDefaulting cycle step to %d",
          line,cyc[ncyc].dc);
        ctlnotice(me,msg);
      }
      else {
        cyc[ncyc].dc = geti(&cflag) ;
      }
    }
    ifcomfg = 0 ;
    ifexp   = 0 ;
#ifndef NDEBUG
    if  (cyc[ncyc].c1 < 0) {
      sprintf(msg,
        "\n\tCycle begin of %d on following line is bad--it must be >= 0"
        "\n\t%s",
        cyc[ncyc].c1,line);
      ctlnotice(me,msg);
      return(1);
    }
    if (cyc[ncyc].c1 > cyc[ncyc].c2) {
      sprintf(msg,
        "\n\tCycle begin of %d is > cycle end of %d on following line--"
        "\n\tCycle begin must be less than time end"
        "\n\t%s",
        cyc[ncyc].c1,cyc[ncyc].c2,line);
      ctlnotice(me,msg);
      return(1);
    }
    if (cyc[ncyc].dc <= 0) {
      sprintf(msg,
        "\n\tCycle step of %d on following line is bad--it must be > 0"
        "\n\t%s",
        cyc[ncyc].dc,line);
      ctlnotice(me,msg);
      return(1);
    }
#endif
    cyc[ncyc].nextCycle = cyc[ncyc].c1;
    sprintf(msg,"cycle_freq_%03d",ncyc);
    cyc[ncyc].name = strsave(msg);
    if ( fcflag == 3 ) {
      if ( ntp >= maxtpdata ) {
        sprintf(msg,err_maxtpdata,maxtpdata);
        ctlerror(me,msg);
      }
      cyctp[ncyc] = ntp;
      if (tpdata[ntp] != NULL) {
        sprintf(msg,"PROGRAMMER ERROR - tpdata[%d] already exists",ntp);
        ctlerror(me,msg);
      }
      tpdata[ntp] = TimePlot_construct(1);
      sprintf(msg,"tp_%03d",ntp);
      tpdata[ntp]->name = strsave(msg);
      tpdata[ntp]->fq_name      = NULL;
      tpdata[ntp]->fq_dat       = NULL;
      tpdata[ntp]->cyc_name     = strsave(cyc[ncyc].name);
      tpdata[ntp]->cyc_dat      = &cyc[ncyc];
      tpdata[ntp]->num_data_pts = 0;
      tempdbl =((((double)cyc[ncyc].c2 - (double)cyc[ncyc].c1) /
                 ((double)cyc[ncyc].dc)) + (double)10);
      if (tempdbl >= (double)INT_MAX) {
        sprintf(msg,"\n\tCycle frequency of %d to %d by %d"
                    "\n\t results in %e entries"
                    "\n\tTrimming the max number of entries to %d",
                    cyc[ncyc].c1,cyc[ncyc].c2,cyc[ncyc].dc,
                    tempdbl,INT_MAX);
        ctlnotice(me,msg);
        tpdata[ntp]->max_data_pts = INT_MAX;
      }
      else {
        tpdata[ntp]->max_data_pts = (int)tempdbl;
      }
      tpdata[ntp]->inc_data_pts  = NTIMES_INCREMENT;
      tpdata[ntp]->alloc_data_pts = 0;
      tpdata[ntp]->tp_curs       = NULL;
      tpdata[ntp]->tp_curs_names = NULL;
      tpdata[ntp]->num_tp_curs   = 0;
      rgst_add(tpdata[ntp]->name,"TimePlot_t",tpdata[ntp],NULL);
      ntp++;
    }
    rgst_add(cyc[ncyc].name,"CycleMesg_t",&(cyc[ncyc]),NULL);
    ncyc++;
  }
  else  {
    ctlerror(me,"logic error: fcflag must be between 0 and 2");
  }
  if ((fcflag == 1) || (fcflag == 2)) {
    fq[nfq-1].msglen = lineop_grab(&fq[nfq-1].msg, "endmsg",NULL);
  } else {
    cyc[ncyc-1].msglen = lineop_grab(&cyc[ncyc-1].msg, "endmsg",NULL);
  }
  tpc_array = ALLOT(TimePlotCurve_t *, maxtplot);
  if ((fcflag == 2) || (fcflag == 3)) {
    ifexp = 0;
    if (fcflag == 2) {
      line = fq[nfq-1].msg ;
    } else {
      line = cyc[ncyc-1].msg ;
    }
    ps         = line ;
    symflag    = 0 ;
    if (genmd != 0) 
      ctlerror(me,"time plots must come AFTER gen command in input deck");
    tpc_array[0] = TimePlotCurve_create("time",ntp-1);
    ntplot       = 1;
    geta(sym);
    while (strcmp(sym,"endmsg") != 0) {
      if (strcmp(sym,"tplot") != 0) {
        geta(sym);
      }
      else { 
        geta(sym);
        strcpy(vname,sym);
        if (strcmp(vname,"time") == 0) {
          ctlwarning(me,"time cannot be edited");
        }
        else {
          tpc = TimePlotCurve_create(vname,ntp-1);
          tpc_array[ntplot] = tpc;
          if (ntplot++ >= maxtplot) {
            sprintf(msg,err_maxtplot,maxtplot);
            ctlerror(me,msg);
          }
        }
      }         
    }           
    tpdata[ntp-1]->num_tp_curs   = ntplot;
    tpdata[ntp-1]->tp_curs       = ALLOT(TimePlotCurve_t *, ntplot);
    tpdata[ntp-1]->tp_curs_names = ALLOT(char *,            ntplot);
    for (i=0 ; i<ntplot ; i++) { 
      tpdata[ntp-1]->tp_curs[i]       = tpc_array[i];
      tpdata[ntp-1]->tp_curs_names[i] = strsave(tpc_array[i]->name);
    }
    ifexp = 1;
  }
  hash_optimize_all();
  line    = lnbuf;
  ps      = NULL;
  symflag = 0;
  ifcomfg = 1;
  ifexp   = 1;
  FREEMEM(tpc_array);
  return(0);
}
