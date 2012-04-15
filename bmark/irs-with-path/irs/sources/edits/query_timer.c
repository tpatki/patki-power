#include <ctype.h>
#include "irs.h"
#include "irscom.h"
#include "irsedits.h"
#include "BlockMapping.h"
#include "FunctionTimer.h"
#include "AEStackElm.h"
#define HUGENUM         1.0e300
typedef struct query_s {
  double *flops;
  double *wall_secs;
  double *cpu_secs;
  double *cntr;
  int    *gblks; 
  int    len;
} query_t;
typedef enum { 
  FLOPS, CPU_SECS, WALL_SECS, CNTR, CPU_MFLOPS, WALL_MFLOPS, NUM_WHAT_T
} WHAT_T;
typedef enum { 
  MINIMUM, MAXIMUM, AVERAGE, AGGREGATE, NUM_HOW_T
} HOW_T;
static char *what_strs[NUM_WHAT_T] = {
  "flops", "cpu sec", "wall sec", 
  "mflops-csec", "mflops-wsec"
};
static char *how_strs[NUM_HOW_T] = {
  "min", "max", "avg", "agg"
};
int query_timer(void)
{
  char *me = "query_timer";
  char op[MAXLINE], msg[256], name[128], label[256];
  int i,j;
  int what_flag[NUM_WHAT_T];
  int how_flag [NUM_HOW_T];
  int thread_ht_flag   = FALSE;
  int global_ht_flag   = FALSE;
  int *flags;
  double data[NUM_WHAT_T][NUM_HOW_T];
  double *flops, *cpu_secs, *wall_secs, *cntr, *cpu_mflops, *wall_mflops;
  FunctionTimer_t *ft = NULL ;
  query_t *last_data = NULL, *this_data = NULL;
  for (i=0; i<NUM_WHAT_T; i++) { what_flag[i] = FALSE; }
  for (i=0; i<NUM_HOW_T;  i++) { how_flag [i] = FALSE; }
  memset(name,'\0',128);
  memset(label,'\0',256);
  if (geta_leftparen() != 0) { return(-1); }
  geta(op);
  strncpy(name,op,127);
  strcpy (label,name);
  ft = FunctionTimer_lookup(name, ft_global_ht);
  flags = ALLOT(int, num_procs);
  if (ft == NULL) { flags[0] = FALSE; }
  else            { flags[0] = TRUE;  }
  commpigather(flags, 1, COM_ALL, COM_INT);
  for (i=0; i<num_procs; i++) {
    if (flags[i] == TRUE) {
      global_ht_flag = TRUE;
      break;
    }
  }
  if (global_ht_flag == FALSE) {
    for (i=0; i<ft_num_thread_ht; i++) {
      if ( (ft_thread_ht[i]->tbl == NULL) || (ft_thread_ht[i]->size == 0) ) {
        ft = NULL;
      }
      else {
        ft = FunctionTimer_lookup(name, ft_thread_ht[i]);
      }
      if (ft != NULL) { break; }
    }
    if (ft == NULL) { flags[0] = FALSE; }
    else            { flags[0] = TRUE;  }
    commpigather(flags, 1, COM_ALL, COM_INT);
    for (i=0; i<num_procs; i++) {
      if (flags[i] == TRUE) {
        thread_ht_flag = TRUE;
        break;
      }
    }
  }
  FREEMEM(flags);
  memset(op,'\0',MAXLINE);
  peekc (op);
  while (op[0] != ')') {
    geta(op);
    if (strcmp(op,",") != 0) {
      strcat(label,"_");
      strcat(label,op);
    }
    for (i=0; i<strlen(op); i++) { if (isupper(op[i])) op[i] = tolower(op[i]); }
    if      (strcmp(op,",")           == 0) { ;           }
    else if (strcmp(op,"cpu_secs")    == 0) { what_flag[CPU_SECS]    = TRUE; }
    else if (strcmp(op,"wall_secs")   == 0) { what_flag[WALL_SECS]   = TRUE; }
    else if (strcmp(op,"cntr")        == 0) { what_flag[CNTR]        = TRUE; }
    else if (strcmp(op,"flops")       == 0) { what_flag[FLOPS]       = TRUE; }
    else if (strcmp(op,"cpu_mflops")  == 0) { what_flag[CPU_MFLOPS]  = TRUE; }
    else if (strcmp(op,"wall_mflops") == 0) { what_flag[WALL_MFLOPS] = TRUE; }
    else if (strcmp(op,"min")         == 0) { how_flag [MINIMUM]     = TRUE; }
    else if (strcmp(op,"max")         == 0) { how_flag [MAXIMUM]     = TRUE; }
    else if (strcmp(op,"avg")         == 0) { how_flag [AVERAGE]     = TRUE; }
    else if (strcmp(op,"agg")         == 0) { how_flag [AGGREGATE]   = TRUE; }
    else if (strcmp(op,"all")         == 0) {
      for (i=0; i<NUM_WHAT_T; i++) { what_flag[i] = TRUE; }
      for (i=0; i<NUM_HOW_T;  i++) { how_flag [i] = TRUE; }
    }
    else {
      sprintf(msg,"'%s' is bad argument to %s edit",op,me);
      ctlnotice(me,msg);
    }
    memset(op,'\0',MAXLINE);
    peekc (op);
  }
  geta_rightparen();
  for (i=0; i<NUM_WHAT_T; i++) {
    if (what_flag[i] == TRUE) { break; }
  }
  if (i >= NUM_WHAT_T) { what_flag[WALL_SECS] = TRUE; }
  for (i=0; i<NUM_HOW_T; i++) {
    if (how_flag[i] == TRUE) { break; }
  }
  if (i >= NUM_HOW_T) { how_flag[MAXIMUM] = TRUE; }
  this_data = ALLOT(query_t, 1);
  if (global_ht_flag == TRUE) {
    this_data->len   = num_procs;
    this_data->gblks = NULL;
    FunctionTimer_global_gather(name,
      &(this_data->flops),     &(this_data->cpu_secs),
      &(this_data->wall_secs), &(this_data->cntr));
  }
  else if (thread_ht_flag == TRUE) {
    this_data->len = gnblk;
    FunctionTimer_thread_gather(name,
      &(this_data->flops),     &(this_data->cpu_secs),
      &(this_data->wall_secs), &(this_data->cntr),
      &(this_data->gblks));
    FREEMEM(this_data->gblks);
  }
  else {
    this_data->len       = MAX(num_procs, gnblk);
    this_data->gblks     = NULL;
    this_data->flops     = ALLOT(double,this_data->len);
    this_data->cpu_secs  = ALLOT(double,this_data->len);
    this_data->wall_secs = ALLOT(double,this_data->len);
    this_data->cntr      = ALLOT(double,this_data->len);
    for (i=0; i<this_data->len; i++) {
      this_data->flops    [0] = 0.0;
      this_data->cpu_secs [0] = 0.0;
      this_data->wall_secs[0] = 0.0;
      this_data->cntr     [0] = 0.0;
    }
  }
  last_data = (query_t *)hash_lookup_obj(label,gv_hash_tbl);
  if (last_data == NULL) {
    last_data            = ALLOT(query_t, 1);
    last_data->len       = this_data->len;
    last_data->flops     = ALLOT(double,last_data->len);
    last_data->cpu_secs  = ALLOT(double,last_data->len);
    last_data->wall_secs = ALLOT(double,last_data->len);
    last_data->cntr      = ALLOT(double,last_data->len);
    for (i=0; i<last_data->len; i++) {
      last_data->flops    [0] = 0.0;
      last_data->cpu_secs [0] = 0.0;
      last_data->wall_secs[0] = 0.0;
      last_data->cntr     [0] = 0.0;
    }
  }
  else {
    hash_del(label,gv_hash_tbl);                     
  }
  hash_add(label,"query_t",this_data,gv_hash_tbl); 
  if (last_data->len < this_data->len) {
    ctlwarning(me,logic_err);
    return(-1);
  }
  flops       = ALLOT(double, this_data->len);
  cpu_secs    = ALLOT(double, this_data->len);
  wall_secs   = ALLOT(double, this_data->len);
  cntr        = ALLOT(double, this_data->len);
  cpu_mflops  = ALLOT(double, this_data->len);
  wall_mflops = ALLOT(double, this_data->len);
  for (i=0; i<this_data->len; i++) {
    flops    [i] = this_data->flops[i]     - last_data->flops[i];
    cpu_secs [i] = this_data->cpu_secs[i]  - last_data->cpu_secs[i];  
    wall_secs[i] = this_data->wall_secs[i] - last_data->wall_secs[i];  
    cntr     [i] = this_data->cntr[i]      - last_data->cntr[i];  
  }
  FREEMEM(last_data->flops);            
  FREEMEM(last_data->cpu_secs);
  FREEMEM(last_data->wall_secs);
  FREEMEM(last_data->cntr);
  FREEMEM(last_data);
  for (i=0; i<NUM_WHAT_T; i++) {
    data[i][AGGREGATE] = 0.0;
    data[i][MINIMUM]   = HUGENUM;
    data[i][MAXIMUM]   = HUGENUM * -1.0;
  }
  for (i=0; i<this_data->len; i++) {
    cpu_mflops[i]  = (cpu_secs[i]  == 0) ? 0 : (1.0e-6 * flops[i]) / cpu_secs [i];
    wall_mflops[i] = (wall_secs[i] == 0) ? 0 : (1.0e-6 * flops[i]) / wall_secs[i];
    data[FLOPS]      [AGGREGATE] += flops      [i];
    data[CPU_SECS]   [AGGREGATE] += cpu_secs   [i];
    data[WALL_SECS]  [AGGREGATE] += wall_secs  [i];
    data[CNTR]       [AGGREGATE] += cntr       [i];
    data[CPU_MFLOPS] [AGGREGATE] += cpu_mflops [i];
    data[WALL_MFLOPS][AGGREGATE] += wall_mflops[i];
    data[FLOPS]      [MINIMUM] = MIN(data[FLOPS]      [MINIMUM], flops      [i]);
    data[CPU_SECS]   [MINIMUM] = MIN(data[CPU_SECS]   [MINIMUM], cpu_secs   [i]);
    data[WALL_SECS]  [MINIMUM] = MIN(data[WALL_SECS]  [MINIMUM], wall_secs  [i]);
    data[CNTR]       [MINIMUM] = MIN(data[CNTR]       [MINIMUM], cntr       [i]);
    data[CPU_MFLOPS] [MINIMUM] = MIN(data[CPU_MFLOPS] [MINIMUM], cpu_mflops [i]);
    data[WALL_MFLOPS][MINIMUM] = MIN(data[WALL_MFLOPS][MINIMUM], wall_mflops[i]);
    data[FLOPS]      [MAXIMUM] = MAX(data[FLOPS]      [MAXIMUM], flops      [i]);
    data[CPU_SECS]   [MAXIMUM] = MAX(data[CPU_SECS]   [MAXIMUM], cpu_secs   [i]);
    data[WALL_SECS]  [MAXIMUM] = MAX(data[WALL_SECS]  [MAXIMUM], wall_secs  [i]);
    data[CNTR]       [MAXIMUM] = MAX(data[CNTR]       [MAXIMUM], cntr       [i]);
    data[CPU_MFLOPS] [MAXIMUM] = MAX(data[CPU_MFLOPS] [MAXIMUM], cpu_mflops [i]);
    data[WALL_MFLOPS][MAXIMUM] = MAX(data[WALL_MFLOPS][MAXIMUM], wall_mflops[i]);
  }
  data[FLOPS]      [AVERAGE] = data[FLOPS]      [AGGREGATE] / this_data->len;
  data[CPU_SECS]   [AVERAGE] = data[CPU_SECS]   [AGGREGATE] / this_data->len;
  data[WALL_SECS]  [AVERAGE] = data[WALL_SECS]  [AGGREGATE] / this_data->len;
  data[CNTR]       [AVERAGE] = data[CNTR]       [AGGREGATE] / this_data->len;
  data[CPU_MFLOPS] [AVERAGE] = data[CPU_MFLOPS] [AGGREGATE] / this_data->len;
  data[WALL_MFLOPS][AVERAGE] = data[WALL_MFLOPS][AGGREGATE] / this_data->len;
  data[CPU_MFLOPS] [AGGREGATE] = (data[CPU_SECS] [MAXIMUM] == 0) ? 
    0 : (1.0e-6 * data[FLOPS][AGGREGATE]) / data[CPU_SECS] [MAXIMUM];
  data[WALL_MFLOPS][AGGREGATE] = (data[WALL_SECS][MAXIMUM] == 0) ? 
    0 : (1.0e-6 * data[FLOPS][AGGREGATE]) / data[WALL_SECS][MAXIMUM];
  FREEMEM(flops);
  FREEMEM(cpu_secs);
  FREEMEM(wall_secs);
  FREEMEM(cntr);
  FREEMEM(cpu_mflops);
  FREEMEM(wall_mflops);
  for (i=0; i<NUM_WHAT_T; i++) {
    if (what_flag[i] == TRUE) {
      for (j=0; j<NUM_HOW_T; j++) {
        if (how_flag[j] == TRUE) {
          sprintf(label,"%s %s %s",name,how_strs[j],what_strs[i]);
          ctloutput(me,label,R_DOUBLE,data[i][j]); 
        }
      }
    }
  }
  return(0);
}
