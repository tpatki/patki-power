
#include <stdio.h>
#include <stdlib.h>
#include "irs.h"
#include "Hash.h"
#include "FunctionTimer.h"

/*
 ***********************************************************************
 *  file:    trace_prepend.c
 *  authors: Terry Jones (LLNL) & Robert Blackmore (IBM)
 *  notes:   Please see README.tracing
 ***********************************************************************
 */

#ifdef TERRY_TRACE

#include <values.h>

char *ctl_file = "/dev/systrctl";
int  ctlfd;
int  loop_count=0, mytraceid, iam_leadtask=0, leadtask;

static int find_leadtask(int);

void trace_finalize(void)
{

   if (terry_trace_flag == FALSE) { return; }

   TRCHKGT(EXITING_IRS_MAIN,cycle,IRS_MAIN_cntr,0,0,0);

   STOP_TRACING(iam_leadtask);

   HALT_TRACING(iam_leadtask);

}

void trace_init(char *opts_buffer)
{
   char *me = "trace_init";

   if (terry_trace_flag == FALSE) { return; }

  /*
   ********************************************************************
   *  The following initializes some variables we'll need later
   *	  each layer will need to do these lines as one-time housekeeping
   ********************************************************************
   */

    MPI_Comm_rank(MPI_COMM_WORLD, &mytraceid);
    leadtask = find_leadtask(mytraceid);
    if(leadtask == myid ) { iam_leadtask=1; }

  /*
   ********************************************************************
   *  The following is some more one-time housekeeping for tracing
   ********************************************************************
   */

    ZAP_OLD_TRACE(iam_leadtask);

    INIT_TRACING(iam_leadtask);

    START_TRACING(iam_leadtask);

    MPI_Barrier(MPI_COMM_WORLD);  

    IRS_MAIN_cntr++;

    TRCHKGT(ENTERING_IRS_MAIN,cycle,IRS_MAIN_cntr,0,0,0);
}

static int find_leadtask(int mytask)
{
    char *common_tasks;
    char *child,*tmp,*save_str=NULL;
    int lead_task,common,i,count;
  
    tmp=getenv("MP_COMMON_TASKS");
    if(tmp!=NULL)  {
       lead_task= MAXINT;
       common_tasks = malloc(strlen(tmp) +1 );
       if(common_tasks == NULL){
          printf("Cannot malloc\n");
          exit(1);
       }
       strcpy(common_tasks,tmp);
       tmp= strtok_r(common_tasks,":",&save_str);
       if(tmp)
          count = atoi(tmp);
       else
          count = 0;
       for(i=0;i<count;i++) {
          tmp = strtok_r(NULL,":",&save_str);
          if(tmp) {
             common = atoi(tmp);
             if(common < lead_task)
                lead_task = common;
          }
       }
    } else {
       lead_task = mytask;
    }
    if(mytask < lead_task)
          lead_task = mytask;
    return lead_task;
}
#endif
