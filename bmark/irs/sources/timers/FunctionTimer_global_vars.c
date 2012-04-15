#include <stdio.h>
#include <stdlib.h>
#include "Hash.h"
#include "FunctionTimer.h"
char *ft_out_of_memory = "ERROR - out of memory";
double ft_maxclock = 0.0;	
double ft_minclock = 0.0;	
double ft_clock_last = 0.0;	
int    ft_clock_rolls = 0;	
int ft_timersflag = TRUE;	        
int ft_running_with_threads = FALSE;    
int ft_num_thread_ht      = 0;          
int ft_num_allocated_ht   = 0;
int ft_global_timer_level = 0;
double ft_cpu_secs        = 0.0;    
double ft_wall_secs       = 0.0;    
double ft_flops           = 0.0;
HashTable_t *  ft_global_ht = NULL;
HashTable_t ** ft_thread_ht;	
int *    ft_thread_timer_level;	
double * ft_thread_flops;       
double * ft_thread_cpu_secs;
double * ft_thread_wall_secs;                                                                    
