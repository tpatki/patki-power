#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Hash.h"
#include "FunctionTimer.h"
#ifndef CLK_TCK
#define CLK_TCK CLOCKS_PER_SEC
#endif
void FunctionTimer_finalize(
   char        *name,
   HashTable_t *ht,
   double       flops )
{
   char *me = "FunctionTimer_finalize";
   char errmsg[128];
   int i;
   double cpu_secs, wall_secs, tdbl, num_rolls, clock_diff;
   FunctionTimer_t *ft = NULL ;
   double ptiny = 1.0e-80;
   if (ft_timersflag == FALSE) { return; }
   ft = FunctionTimer_lookup(name, ht);
   if ( (ft == NULL) || (ft->setflag == FINALIZED) ) {
      sprintf(errmsg, "%s: Attempted to finalize FunctionTimer '%s'\n"
		      "which was never initialized", 
                      me, name);
      FunctionTimer_error(me,errmsg);
   }
   FunctionTimer_clock(TIMER_STOP, ft);
   ft->flops   += flops ;
   ft->setflag  = FINALIZED ;
   wall_secs  = ((ft->times_stop - ft->times_start) / CLK_TCK)  + ptiny;
   if (ft->clock_rolls_start == ft->clock_rolls_stop) {
     if (ft->clock_stop >= ft->clock_start) {
       cpu_secs = ((ft->clock_stop - ft->clock_start) / CLOCKS_PER_SEC) + ptiny; 
     }
     else {
       FunctionTimer_warning(me,"Programmer messed up clock rollover logic!");
       cpu_secs = 0.0;
     }
   }
   else {
     clock_diff  = ft_maxclock - ft->clock_start;
     clock_diff += 1;
     clock_diff += ft->clock_stop - ft_minclock;
     clock_diff += ((ft->clock_rolls_stop - ft->clock_rolls_start) - 1) * 
                   ((ft_maxclock - ft_minclock) + 1);
     cpu_secs = (clock_diff / CLOCKS_PER_SEC) + ptiny;
   }
   ft->cpu_secs  += cpu_secs;
   ft->wall_secs += wall_secs;
   if (ht == ft_global_ht) {
      tdbl = ft->agg_flops;
      ft_flops += flops;
      ft->agg_flops += ft_flops - ft->agg_flops_start;
      ft_global_timer_level--;
      if (ft_num_thread_ht > ft->agg_thr_flops_start_len) {
	if (ft->agg_thr_flops_start_len == 0) {
          ft->agg_thr_flops_start = ALLOT(double,ft_num_thread_ht);
        }
	else {
          ft->agg_thr_flops_start = REALLOT(ft->agg_thr_flops_start,double,ft_num_thread_ht);
        }
	for (i=ft->agg_thr_flops_start_len; i<ft_num_thread_ht; i++) {
          ft->agg_thr_flops_start[i] = 0.0;
        }
	ft->agg_thr_flops_start_len = ft_num_thread_ht;
      }
      for (i=0; i < ft_num_thread_ht; i++)  {
        ft_thread_timer_level[i]--;
        ft->agg_flops += ft_thread_flops[i] - ft->agg_thr_flops_start[i];
      }
      if (ft_global_timer_level == 0) {
        for (i=0; i<ft_num_thread_ht; i++) {
          ft_flops += ft_thread_flops[i] - ft->agg_thr_flops_start[i];
        }
        ft_cpu_secs       += cpu_secs;
	ft_wall_secs      += wall_secs;
        ft->top_cpu_secs  += cpu_secs;
	ft->top_wall_secs += wall_secs;
        ft->top_agg_flops += ft->agg_flops - tdbl;
      }
   }
   else {
     for (i=0; i < ft_num_thread_ht; i++) {
       if (ht == ft_thread_ht[i]) { break; }
     }
     if (i < ft_num_thread_ht) {
       ft_thread_flops[i] += flops;
       ft->agg_flops += ft_thread_flops[i] - ft->agg_flops_start; 
       ft_thread_timer_level[i]--;
       if (ft_thread_timer_level[i] == ft_global_timer_level) {
         ft_thread_cpu_secs [i] += cpu_secs;
         ft_thread_wall_secs[i] += wall_secs;  
         ft->top_cpu_secs   += cpu_secs;
         ft->top_wall_secs  += wall_secs;
	 ft->top_agg_flops  += ft_thread_flops[i] - ft->agg_flops_start;
       }
     }
   }
}
