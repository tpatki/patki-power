#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"
#include "FunctionTimer.h"
int FunctionTimer_ht_setup (
  HashTable_t *ht,            
  char        *type)          
{
  char *me = "FunctionTimer_ht_setup";
  char errmsg[128];
  if (ft_timersflag == FALSE) { return(0); }
  if (strcmp(type,"global") == 0) {
    if (ft_global_ht == NULL) {
      ft_global_ht = ht;
    }
    else {
      sprintf(errmsg,"%s: Attempt to add a second global function timer hash table",me);
      FunctionTimer_error(me,errmsg);
    }
  }
  else if (strcmp(type,"threaded") == 0) {
     if (ft_num_thread_ht >= ft_num_allocated_ht) {
       if (ft_num_allocated_ht == 0) { 
	 ft_num_allocated_ht   = ft_num_thread_ht + 4;
         ft_thread_ht          = ALLOT(HashTable_t *, ft_num_allocated_ht);
	 ft_thread_timer_level = ALLOT(int,           ft_num_allocated_ht);
         ft_thread_flops       = ALLOT(double,        ft_num_allocated_ht);
         ft_thread_cpu_secs    = ALLOT(double,        ft_num_allocated_ht);
         ft_thread_wall_secs   = ALLOT(double,        ft_num_allocated_ht);
       }
       else {
         ft_num_allocated_ht   =  ft_num_thread_ht + 4;
         ft_thread_ht          = REALLOT(ft_thread_ht,          HashTable_t *, ft_num_allocated_ht);
	 ft_thread_timer_level = REALLOT(ft_thread_timer_level, int,           ft_num_allocated_ht);
         ft_thread_flops       = REALLOT(ft_thread_flops,       double,        ft_num_allocated_ht);
         ft_thread_cpu_secs    = REALLOT(ft_thread_cpu_secs,    double,        ft_num_allocated_ht);
         ft_thread_wall_secs   = REALLOT(ft_thread_wall_secs,   double,        ft_num_allocated_ht);
       }
     }
    ft_thread_ht         [ft_num_thread_ht] = ht;
    ft_thread_timer_level[ft_num_thread_ht] = 0;
    ft_thread_flops      [ft_num_thread_ht] = 0.0;
    ft_thread_cpu_secs   [ft_num_thread_ht] = 0.0;
    ft_thread_wall_secs  [ft_num_thread_ht] = 0.0;
    ft_num_thread_ht++;
  }
  else {
    sprintf(errmsg,"%s: type '%s' is invalid",me,type);
    FunctionTimer_error(me,errmsg);
  }
  return(0);
}
int FunctionTimer_ht_remove (
  HashTable_t *ht,
  char        *type)
{
  char *me = "FunctionTimer_ht_remove";
  char errmsg[128];
  int i, ii;
  if (ft_timersflag == FALSE) { return(0); }
  if (strcmp(type,"global") == 0) {
    if (ft_global_ht != ht) {
      sprintf(errmsg,"%s: global function timer hash table to be removed doesn't match",me);
      FunctionTimer_error(me,errmsg);
    } 
    ft_global_ht = NULL;
    ft_cpu_secs = 0;
    ft_wall_secs = 0;
    ft_flops = 0;
    ft_global_timer_level = 0;
  }
  else if (strcmp(type,"threaded") == 0) {
    for (i=0; i<ft_num_thread_ht; i++) {
      if (ht == ft_thread_ht[i]) { break; }
    }
    if (i >= ft_num_thread_ht) {
      sprintf(errmsg,"%s trhead function timer hash table is not in list",me);
      FunctionTimer_error(me,errmsg);
    }
    for (ii=i; ii<ft_num_thread_ht-1; ii++) {
      ft_thread_ht         [ii]	= ft_thread_ht         [ii + 1];
      ft_thread_timer_level[ii]	= ft_thread_timer_level[ii + 1];
      ft_thread_flops      [ii]	= ft_thread_flops      [ii + 1];
      ft_thread_cpu_secs   [ii]	= ft_thread_cpu_secs   [ii + 1];
      ft_thread_wall_secs  [ii]	= ft_thread_wall_secs  [ii + 1];
    }
    ft_num_thread_ht--;
  }
  return(0);
}
void FunctionTimer_ht_update (HashTable_t *old_ht, HashTable_t *new_ht)
{
  int i;
  if (old_ht == ft_global_ht) {
    ft_global_ht = new_ht;
  }
  else {
    for (i=0; i<ft_num_thread_ht; i++) {
       if (ft_thread_ht[i] == old_ht) {
         ft_thread_ht[i] = new_ht;
       }
    }
  }	 
}
