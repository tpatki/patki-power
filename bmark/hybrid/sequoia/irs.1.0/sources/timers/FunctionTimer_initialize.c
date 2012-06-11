#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "FunctionTimer.h"
int debug_switch = FALSE;
void FunctionTimer_initialize (
   char        *name,  
   HashTable_t *ht)    
{
   char *me = "FunctionTimer_initialize";
   char errmsg[256];
   int i ;
   FunctionTimer_t *ft = NULL ;
   if (ft_timersflag == FALSE) { return; }
   if ( (name == NULL)  || (ht == NULL) ) {
      sprintf(errmsg,"%s:m name or ht is NULL",me);
      FunctionTimer_error(me,errmsg);
   }
   ft = FunctionTimer_lookup(name, ht);
   if (ft == NULL) {
      ft = FunctionTimer_construct(1);
      if (strlen(name) >= (FT_NAMELEN + 4)) {
	sprintf(errmsg,"Function name '%s' is too long, shorten it to %d chars\n",
                name,FT_NAMELEN-5);
        FunctionTimer_error(me,errmsg);
      }
      sprintf (ft->name, "FTS_%s", name);
      hash_add(ft->name, "FunctionTimer_t", ft, ht);
   }
   if (ft->setflag == INITIALIZED) {
      fprintf(stderr,"%s: FunctionTimer %s was initialized but not finalized\n",
              me, name ) ;
   }
   FunctionTimer_clock(TIMER_START, ft);
   ft->setflag = INITIALIZED ;
   ft->cntr++;
   if (ht == ft_global_ht) {
      ft_global_timer_level++;
      ft->level = ft_global_timer_level;
      ft->agg_flops_start = ft_flops;
      if (ft_num_thread_ht > ft->agg_thr_flops_start_len) {
	if (ft->agg_thr_flops_start_len == 0) {
          ft->agg_thr_flops_start = ALLOT(double,ft_num_thread_ht);
        }
	else {
          ft->agg_thr_flops_start = REALLOT(ft->agg_thr_flops_start,double,ft_num_thread_ht);
        }
	ft->agg_thr_flops_start_len = ft_num_thread_ht;
      }
      for (i=0; i<ft_num_thread_ht; i++)    {
        ft_thread_timer_level[i]   = ft_global_timer_level;
        ft->agg_thr_flops_start[i] = ft_thread_flops[i];
      }
   }
   else {
     for (i=0; i < ft_num_thread_ht; i++) {
       if (ht == ft_thread_ht[i]) { break; }
     }
     if (i < ft_num_thread_ht) { 
       ft_thread_timer_level[i]++;
       ft->level = ft_thread_timer_level[i];
       ft->agg_flops_start = ft_thread_flops[i];
     }
   }
}
