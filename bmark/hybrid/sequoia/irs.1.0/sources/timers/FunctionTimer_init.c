#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "FunctionTimer.h"
void FunctionTimer_init(FunctionTimer_t *ptr)
{
  int i;
  memset(ptr->name,'\0',FT_NAMELEN);
  ptr->cntr      	       = 0.0;
  ptr->cpu_secs      	       = 0.0;
  ptr->top_cpu_secs  	       = 0.0;
  ptr->wall_secs     	       = 0.0;
  ptr->top_wall_secs 	       = 0.0;
  ptr->flops    	       = 0.0;
  ptr->agg_flops               = 0.0;
  ptr->agg_flops_start         = 0.0;
  ptr->times_start   	       = 0.0;
  ptr->times_stop    	       = 0.0;
  ptr->clock_start   	       = 0.0;
  ptr->clock_stop    	       = 0.0;
  ptr->clock_rolls_start       = 0;
  ptr->clock_rolls_stop        = 0;
  ptr->level    	       = 0;
  ptr->setflag  	       = FINALIZED;
  ptr->agg_thr_flops_start     = NULL;
  ptr->agg_thr_flops_start_len = 0;
}
