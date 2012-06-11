#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
void comcleanup(void) {
   char *me = "comcleanup";
   char msg[256];
   int iblk,i;
   double totaltime;
   double maxtotaltime;
   double mintotaltime;
   double zones;
   double mspzc;
   double mspzc_ave;
   double mspzc_dave;
   double avetime;
   double davetime;
   double resolution;
   double *timeproc;
   double *dtimeproc;
   if (combuf == NULL) {
     ctlnotice(me,"combuf is not allocated, leaving routine");
     return;
   }
   com_finish_time = MPI_Wtime_Wrapper() - com_start_time;
   if (fpout != NULL) {
      PRINT(fpout,"NODE %i: Total time %e seconds.\n",myid,com_finish_time);
   }
   totaltime = com_physics_time;
   if (fpout != NULL) {
      PRINT(fpout,"NODE %i: Total physics time %e seconds.\n",myid,totaltime);
   }
   zones=0.0;
   for (iblk=0;iblk<nblk;iblk++) {
      if (ndims==3) {
         zones += 1.0*(domains[iblk].imax-domains[iblk].imin)*
                  (domains[iblk].jmax-domains[iblk].jmin)*
                  (domains[iblk].kmax-domains[iblk].kmin);
      } else {
         zones += 1.0*(domains[iblk].imax-domains[iblk].imin)*
                  (domains[iblk].jmax-domains[iblk].jmin);
      }
   }
   if ((zones > 0 ) && (delcyc > 0)) {
      mspzc = (1.0E6*totaltime)/zones/((double)delcyc);
   } else {
      mspzc = 0.0;
   }
   if (fpout != NULL) {
      PRINT(fpout,"NODE %i: Microseconds/zone/cycle = %e.\n",myid,mspzc);
      PRINT(fpout,"NODE %i: Total zones %e.\n",myid,zones);
   }
   timeproc=ALLOT(double,num_procs);
   dtimeproc=ALLOT(double,num_procs);
   for (i=0;i<num_procs;i++) {
      timeproc[i]=0.0;
   }
   timeproc[myid]=totaltime;
   maxtotaltime=totaltime;
   mintotaltime=totaltime;


   if (ifcomsummary == TRUE) {
      comsummary(timeproc);
   }


   comreduce(&zones,1,COM_SUM,COM_ONE,COM_DOUBLE);
   comreduce(&maxtotaltime,1,COM_MAX,COM_ONE,COM_DOUBLE);
   comreduce(&mintotaltime,1,COM_MIN,COM_ONE,COM_DOUBLE);
   comreduce(timeproc,num_procs,COM_SUM,COM_ONE,COM_DOUBLE);
   if (myid==0) {
      avetime=0.0;
      davetime=0.0;
      for (i=0;i<num_procs;i++) {
         avetime+=timeproc[i];
      }
      if (num_procs>0) avetime=avetime/num_procs;
      for (i=0;i<num_procs;i++) {
         davetime+=(avetime-timeproc[i])*(avetime-timeproc[i]);
      }
      if (num_procs>0) davetime=davetime/num_procs;
      if (num_procs>1) {
         davetime=sqrt(davetime/(num_procs-1));
      } else {
         davetime=0.0;
      }
      if (delcyc>0) {
         mspzc = (1.0E6*maxtotaltime)/zones/((double)delcyc);
         mspzc_ave = (1.0E6*avetime)/zones/((double)delcyc);
         mspzc_dave = (1.0E6*davetime)/zones/((double)delcyc);
      } else {
         mspzc = 0.0;
         mspzc_ave = 0.0;
         mspzc_dave = 0.0;
      }
      resolution=MPI_Wtick_Wrapper();
      sprintf(msg,"Total zones %e.",zones); 
      ctlmsg(msg);
      sprintf(msg,"Average physics time %e +/- %e seconds.",avetime,davetime); 
      ctlmsg(msg);
      sprintf(msg,"Timer resolution %e seconds.",resolution); 
      ctlmsg(msg);
      sprintf(msg,"Min physics time %e seconds.",mintotaltime); 
      ctlmsg(msg);
      sprintf(msg,"Max physics time %e seconds.",maxtotaltime); 
      ctlmsg(msg);
      sprintf(msg,"Overall Microseconds/zone/cycle %e.",mspzc); 
      ctlmsg(msg);
      sprintf(msg,"Average Microseconds/zone/cycle %e +/- %e.",mspzc_ave,mspzc_dave); 
      ctlmsg(msg);
   }
   FREEMEM(timeproc);
   FREEMEM(dtimeproc);
   if (myid!=0) {
      fclose(stdout);
   }
}
