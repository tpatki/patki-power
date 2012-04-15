#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "FunctionTimer.h"
#define MSG_LEN       256
#define TRUNC_LEN     39
static int last_indent = 9999;
void FunctionTimer_out(
  FILE        *fp,          
  char        *name,        
  char        *label,       
  int          indent,      
  double       frac)        
{
  char *me = "FunctionTimer_out";
  char msg[MSG_LEN];
  char *output_name = NULL;
  int i;
  double ftime, mflops, temp_cpu_secs;
  FunctionTimer_t *ft;
  double cpu_secs  = 0.0;
  double wall_secs = 0.0;
  double agg_flops = 0.0;
  int global_ht_flag = FALSE;
  int thread_ht_flag = FALSE;
  double ptiny = 1.0e-80;
  if (ft_timersflag == FALSE) { return; }
  ft = FunctionTimer_lookup(name, ft_global_ht);
  if (ft != NULL) {
    global_ht_flag = TRUE;
    agg_flops += ft->agg_flops;
    cpu_secs  += ft->cpu_secs;
    wall_secs += ft->wall_secs;
  }
  temp_cpu_secs = 0.0;
  for (i=0; i<ft_num_thread_ht; i++) {
    if ( (ft_thread_ht[i]->tbl == NULL) || (ft_thread_ht[i]->size == 0) ) {
      ft = NULL;
    }
    else {
      ft = FunctionTimer_lookup(name, ft_thread_ht[i]);
    }
    if (ft != NULL)   {
      thread_ht_flag = TRUE;
      agg_flops += ft->agg_flops;
      if (ft_running_with_threads == TRUE) {
        wall_secs += ft->wall_secs;
        if (ft->cpu_secs > temp_cpu_secs) { 
          temp_cpu_secs = ft->cpu_secs;
        }
      }
      else {
        cpu_secs  += ft->cpu_secs;
        wall_secs += ft->wall_secs;
      }
    }
  }
  cpu_secs += temp_cpu_secs; 
  if ((global_ht_flag == TRUE) || (thread_ht_flag == TRUE)) {
    memset(msg,'\0',MSG_LEN);
    if     ((global_ht_flag == TRUE) && 
            (thread_ht_flag == TRUE))  { sprintf(msg,"(GD)"); }
    else if (global_ht_flag == TRUE)   { sprintf(msg,"(G) "); }
    else if (thread_ht_flag == TRUE)   { sprintf(msg,"(D) "); }
    else                               { sprintf(msg,"    "); }
    for (i=0; i<indent; i++)  {
      strcat(msg,"   ");
    }
    if (label != NULL) { output_name = label; }
    else               { output_name = name;  }
    strcat(msg,output_name);
    msg[TRUNC_LEN] = '\0';
    ftime  = frac * cpu_secs;
    mflops = 1.0e-6 * agg_flops / ( cpu_secs + ptiny ) ;
    if (indent < last_indent) { fprintf(fp,"\n"); }
    last_indent = indent;
    if (ftime > 1.0e-6) {
      fprintf(fp,"%-39s %e %e %e %e %e\n",
              msg,ftime,mflops,agg_flops,cpu_secs,wall_secs);
    }
  }
}
