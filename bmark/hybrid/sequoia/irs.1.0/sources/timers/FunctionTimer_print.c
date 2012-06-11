#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "FunctionTimer.h"
#define DASH35 "----------------------------------"
#define DASH20 "-------------------"
#define DASH15 "---------------"
#define DASH12 "------------"
#define DASH10 "----------"
#define DASH3  "---"
static void sort_timers_by_cpu_secs  (FunctionTimer_t *fts[], int num_fts);
static void sort_timers_by_wall_secs (FunctionTimer_t *fts[], int num_fts);
static void sort_timers_by_flops     (FunctionTimer_t *fts[], int num_fts);
void FunctionTimer_print(
  FILE        *fp,         
  int         wall_sort,   
  int         cpu_sort,    
  int         flops_sort,  
  HashTable_t *ht)
{
  char *me = "FunctionTimer_print";
  char errmsg[128], tmsg[64], msg1[64], msg2[64];
  int i, numelm;
  int my_threadNum = -1;
  double mflops, cpu_secs, flops_sum, cpu_secs_sum, wall_secs_sum;
  HashElm_t **hashelm ;
  char **varlist ;
  FunctionTimer_t **fts = NULL;
  if (ft_timersflag == FALSE) { return; }
  if (ht == ft_global_ht) { 
    sprintf(msg1,"GLOBAL SUMS ACROSS ALL RUNS");
    sprintf(msg2,"GLOBAL SUMS SINCE LAST RESTART");
    sprintf(tmsg,"GLOBAL FUNCTIONS");
  }
  else {
    for (my_threadNum=0; my_threadNum < ft_num_thread_ht; my_threadNum++) {
      if (ht == ft_thread_ht[my_threadNum]) { break; }
    }
    if (my_threadNum >= ft_num_thread_ht) {
      sprintf(errmsg,"%s: Hash table was not specifed by calling FunctionTimer_setup",me);
      FunctionTimer_error(me,errmsg);
    }
    sprintf(msg1,"THREAD %d SUMS ACROSS ALL RUNS",my_threadNum);
    sprintf(msg2,"THREAD %d SUMS SINCE LAST RESTART",my_threadNum);
    sprintf(tmsg,"THREAD %d FUNCTIONS",my_threadNum);
  }
  fprintf(fp,"\n");
  fprintf(fp,"%-35s %12s %12s %12s %12s %3s\n",
          "","MFLOPS /","","", "",""); 
  fprintf(fp,"%-35s %12s %12s %12s %12s %3s\n",
          tmsg,"CPU SEC","FLOPS","CPU SECS", "WALL SECS","TOP"); 
  fprintf(fp,"%-35s %12s %12s %12s %12s %3s\n",
          DASH35,DASH12,DASH12,DASH12,DASH12,DASH3);
  hashelm = hash_get_elm_list(&numelm, "FunctionTimer_t", ht);
  hash_sort_array(hashelm, numelm);
  fts = ALLOT(FunctionTimer_t *, numelm);
  for (i=0; i<numelm; i++) {
    fts[i] = (FunctionTimer_t *) hashelm[i]->obj ;
    if (fts[i] == NULL) {
      sprintf(errmsg,"%s: programmer errror",me);
      FunctionTimer_error(me,errmsg);
    }    
  }
  FREEMEM(hashelm);
  if      (cpu_sort   == TRUE) { sort_timers_by_cpu_secs  (fts, numelm); }
  else if (wall_sort  == TRUE) { sort_timers_by_wall_secs (fts, numelm); }
  else if (flops_sort == TRUE) { sort_timers_by_flops     (fts, numelm); }
  flops_sum = cpu_secs_sum = wall_secs_sum = 0;
  for (i=0; i<numelm; i++) {
    memset(tmsg,'\0',5);
    if (fts[i]->top_cpu_secs > 0.0) {
      flops_sum     += fts[i]->top_agg_flops;
      cpu_secs_sum  += fts[i]->top_cpu_secs;
      wall_secs_sum += fts[i]->top_wall_secs;
      strcpy(tmsg,"TOP"); 
    }
    if (fts[i]->agg_flops > 0) {
      if (fts[i]->cpu_secs == 0.0) 
        { mflops = 0.0; }
      else 
        { mflops = ( 1.0e-6 * fts[i]->agg_flops ) / (fts[i]->cpu_secs); }
      fprintf(fp,"%-35s %12e %12e %12e %12e %3s\n",
              &(fts[i]->name[4]), mflops, fts[i]->agg_flops, 
              fts[i]->cpu_secs, fts[i]->wall_secs, tmsg);
    }
    else {
      fprintf(fp,"%-35s %12s %12e %12e %12e %3s\n",
              &(fts[i]->name[4]), "", fts[i]->agg_flops,
	      fts[i]->cpu_secs, fts[i]->wall_secs, tmsg); 
    }
  }
  fprintf(fp,"\n");
  if (ht == ft_global_ht) {
    if (ft_cpu_secs == 0.0) 
      { mflops = 0.0; }
    else                     
      { mflops = (1.0e-6 * ft_flops) / ft_cpu_secs; }
    fprintf(fp,"%-35s %12e %12e %12e %12e %3s\n",
            msg2,mflops,ft_flops,ft_cpu_secs,ft_wall_secs,"");
  }
  else {
    if (ft_thread_cpu_secs[my_threadNum] == 0.0) 
      { mflops = 0.0; }
    else                     
      { mflops = (1.0e-6 * ft_thread_flops[my_threadNum]) / ft_thread_cpu_secs[my_threadNum]; }
    fprintf(fp,"%-35s %12e %12e %12e %12e %3s\n",
          msg2, mflops, ft_thread_flops[my_threadNum],
	  ft_thread_cpu_secs[my_threadNum], ft_thread_wall_secs[my_threadNum], "");
  }
  if (cpu_secs_sum == 0.0) 
    { mflops = 0.0; }
  else                     
    { mflops = ( 1.0e-6 * flops_sum )  / cpu_secs_sum; }
  fprintf(fp,"%-35s %12e %12e %12e %12e %3s\n\n",
          msg1,mflops,flops_sum,cpu_secs_sum,wall_secs_sum,"");
  FREEMEM(fts);
}
static void sort_timers_by_cpu_secs(
  FunctionTimer_t *fts[],        
  int num_fts)                   
{
  register int i, j, l=1;
  register FunctionTimer_t *ptr;
  for (i=l; i<num_fts; i++) {
    ptr = fts[i];
    for ( j=i-l;
          ((j>=0) && (fts[j]->cpu_secs < ptr->cpu_secs));
          j--) {
      fts[j+l] = fts[j];
    }
    fts[j+l] = ptr;
  }
}
static void sort_timers_by_wall_secs(
  FunctionTimer_t *fts[],        
  int num_fts)                   
{
  register int i, j, l=1;
  register FunctionTimer_t *ptr;
  for (i=l; i<num_fts; i++) {
    ptr = fts[i];
    for ( j=i-l;
          ((j>=0) && (fts[j]->wall_secs < ptr->wall_secs));
          j--) {
      fts[j+l] = fts[j];
    }
    fts[j+l] = ptr;
  }
}
static void sort_timers_by_flops(
  FunctionTimer_t *fts[],        
  int num_fts)                   
{
  register int i, j, l=1;
  register FunctionTimer_t *ptr;
  for (i=l; i<num_fts; i++) {
    ptr = fts[i];
    for ( j=i-l;
          ((j>=0) && (fts[j]->flops < ptr->flops));
          j--) {
      fts[j+l] = fts[j];
    }
    fts[j+l] = ptr;
  }
}
