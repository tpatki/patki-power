#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
void comsummary(double* timeproc)
{
   char *me = "comsummary";	  
   char msg[256];
   int j;
   int routine;
   int lentimedata;
   double *timedata;
   double totaltime;
   double totalphystime;
   double totalcomtime;
   double maxcomtime;
   double avecomtime;
   double mincomtime;
   if (combuf == NULL) {
     ctlnotice(me,"combuf is not allocated, leaving routine");
     return;
   }	  
   lentimedata = NCOMROUTINES+6;
   timedata = ALLOT(double,lentimedata);
   totaltime = timeproc[myid];
   totalcomtime = 0.;
   j = 0;
   for (routine = 1; routine <= NCOMROUTINES; routine++) {
      timedata[j] = 
                      (combuf[routine].comtimer[COM_SET_SIZE_DOUBLE] +
                       combuf[routine].comtimer[COM_SET_SIZE_INT] +
                       combuf[routine].comtimer[COM_SEND] +
                       combuf[routine].comtimer[COM_WAIT_SEND] +
                       combuf[routine].comtimer[COM_RECV] +
                       combuf[routine].comtimer[COM_COLLECT] +
                       combuf[routine].comtimer[COM_WAIT_RECV]);
      totalcomtime += timedata[j];
      j++;
   }
   timedata[j++] = com_barrier_time;
   timedata[j++] = com_brdcst_time;
   timedata[j++] = com_reduce_time;
   totalcomtime += com_barrier_time + com_brdcst_time + com_reduce_time;
   timedata[j++] = com_finish_time;
   timedata[j++] = totalcomtime;
   timedata[j++] = timeproc[myid];
   maxcomtime = totalcomtime/(ptiny + timeproc[myid]);
   avecomtime = totalcomtime/(ptiny + timeproc[myid]);
   mincomtime = totalcomtime/(ptiny + timeproc[myid]);
   sprintf(msg,"\n\tNODE %i Total Communications Time: %e\n\tNODE %i Spent %f percent of its time in communications",
           myid,totalcomtime,myid,100.*totalcomtime/(ptiny + com_finish_time));
   ctlmsg(msg);
   comreduce(timedata,lentimedata,COM_SUM,COM_ONE,COM_DOUBLE);
   comreduce(&maxcomtime,1,COM_MAX,COM_ONE,COM_DOUBLE);
   comreduce(&avecomtime,1,COM_SUM,COM_ONE,COM_DOUBLE);
   comreduce(&mincomtime,1,COM_MIN,COM_ONE,COM_DOUBLE);
   avecomtime = avecomtime/(num_procs);
   if (myid == 0) {
      totalphystime = timedata[lentimedata-1]+ptiny;
      totalcomtime = timedata[lentimedata-2];
      totaltime = timedata[lentimedata-3]+ptiny;
      j = 0;
      ctlmsg("             %% of phys time   %% of total time");
      for (routine = 1; routine <= NCOMROUTINES; routine++) {
         sprintf(msg," %10s: %10.6f %%      %10.6f %%",
                 combuf[routine].bufname,
                 100.*timedata[j]/totalphystime > 999 ? 999. : 100.*timedata[j]/totalphystime,
                 100.*timedata[j]/totaltime     > 999 ? 999. : 100.*timedata[j]/totaltime);
         ctlmsg(msg);
         j++;
      }
      sprintf(msg," %10s: %10.6f %%      %10.6f %%",
                  "barrier",
                  100.*timedata[j]/totalphystime > 999 ? 999. : 100.*timedata[j]/totalphystime,
                  100.*timedata[j]/totaltime     > 999 ? 999. : 100.*timedata[j]/totaltime);
      ctlmsg(msg);
      j++;
      sprintf(msg," %10s: %10.6f %%      %10.6f %%",
                  "brdcst",
                  100.*timedata[j]/totalphystime > 999 ? 999. : 100.*timedata[j]/totalphystime,
                  100.*timedata[j]/totaltime     > 999 ? 999. : 100.*timedata[j]/totaltime);
      ctlmsg(msg);
      j++;
      sprintf(msg," %10s: %10.6f %%      %10.6f %%",
                  "reduce",
                  100.*timedata[j]/totalphystime > 999 ? 999. : 100.*timedata[j]/totalphystime,
                  100.*timedata[j]/totaltime     > 999 ? 999. : 100.*timedata[j]/totaltime);
      ctlmsg(msg);
      j++;
      sprintf(msg,"Communications  Min: %6.3f%% Ave: %6.3f%% Max: %6.3f%%.",
                  100.*mincomtime > 999 ? 999. : 100.*mincomtime,
                  100.*avecomtime > 999 ? 999. : 100.*avecomtime,
                  100.*maxcomtime > 999 ? 999. : 100.*maxcomtime);
      ctlmsg(msg);
      sprintf(msg,"Communications averaged %10.6f%% of physics time.",
                  100.*totalcomtime/totalphystime > 999 ? 999. : 100.*totalcomtime/totalphystime);
      ctlmsg(msg);
      sprintf(msg,"Communications averaged %10.6f%% of total time.",
                   100.*totalcomtime/totaltime > 999 ? 999. : 100.*totalcomtime/totaltime);
      ctlmsg(msg);
   }   
   FREEMEM(timedata);
}
