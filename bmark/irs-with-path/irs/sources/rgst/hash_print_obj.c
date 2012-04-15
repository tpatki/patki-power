#include <stdio.h>                      
#include <stdlib.h>                     
#include <string.h>                     
#include "irs.h"
#include "irsrgst.h"
#include "FreqMesg.h"
#include "Hash.h"
#include "Rgst.h"
#include "TimePlot.h"
void hash_print_obj(
  HashElm_t *ptr)	
{
  char *me = "hash_print_obj";
  char msg[128];
  if      (RGST_QUERY_OBJECT_ATTR(ptr->name, "int_parm")    == TRUE) { ; } 
  else if (RGST_QUERY_OBJECT_ATTR(ptr->name, "double_parm") == TRUE) { ; } 
  else if (RGST_QUERY_OBJECT_ATTR(ptr->name, "char_parm")   == TRUE) { ; } 
  else if (strcmp(ptr->type,"tp_curve")   == 0) { printtpcurve  (ptr->obj); }
  else if (strcmp(ptr->type,"time_plot")  == 0) { printtimeplot (ptr->obj); }
  else if (strcmp(ptr->type,"time_freq")  == 0) { printtimefreq (ptr->obj); }
  else if (strcmp(ptr->type,"cycle_freq") == 0) { printcyclefreq(ptr->obj); }
}
