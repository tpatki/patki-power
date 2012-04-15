





#include <stddef.h>               
#include "irs.h"
#include "irssys.h"
#include "irscom.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "irsobjects.h"

#include "BlockMapping.h"
#include "Command.h"
#include "FunctionTimer.h"
#include "Hash.h"

#define HUGENUM         1.0e300
#define WALL_SEC_CUTOFF 1.0e-60
#define CPU_SEC_CUTOFF  1.0e-60

#define NOT_FOUND_FLAG   0
#define GLOBAL_FLAG      1
#define DOMAIN_FLAG      2

#define NAME_FLAG        0
#define MFLOPS_FLAG      1
#define FLOPS_FLAG       2
#define CPU_SECS_FLAG    3
#define WALL_SECS_FLAG   4
#define CNTR_FLAG        5

#define DEFAULT_SORT_FIELD_KEY WALL_SECS_FLAG
#define DEFAULT_MAX_FIELD_KEY  WALL_SECS_FLAG



typedef struct Analysis_s {

  char   *name;            

  double *flops,           
         *cpu_secs,        
         *wall_secs,       
	 *cntr;
  int    *gblks;

  int    len,              
         nlen;             
                           

  double tot_flops,        
         tot_cpu_secs,
         tot_wall_secs,
	 tot_cntr;

  double min_flops    [2], 
         min_cpu_secs [2], 
         min_wall_secs[2], 
         min_mflops   [2], 
         min_cntr     [2], 
                           
         max_flops    [2], 
         max_cpu_secs [2],
         max_wall_secs[2],
         max_mflops   [2],
	 max_cntr     [2];

} Analysis_t;


static char *DASH114 = "=================================================="
                       "==================================================="
                       "=============";
static char *DASH80  = "----------------------------------------"
                       "----------------------------------------";
static char *DASH25  = "-------------------------";
static char *DASH12  = "------------";
static char *DASH10  = "----------";
static char *DASH4   = "----";

static char * WALL_SEC_MSG = 
"A Note on Wall Seconds and CPU Seconds Gathering under Threads.\n\n"
"  The 'clock' routine is used to obtain CPU clocks which is converted to CPU\n"
"  seconds.\n\n"
"  The 'times' routine is used to obtain elapsed wall seconds.\n\n"
"  In a threaded code, the way these two system routines return the data is\n"
"  a bit inconsistent -- but it is logical.\n\n"
"    - 'clock' sums up the clocks used by all processors in a threaded\n"
"       section of code.  Since the man page for 'clock' states\n\n"
"      \"Reports central processing unit (CPU) time used\"\n\n"
"      This implies counting the CPU time spent on all processors.\n\n"
"    - 'times' returns elapsed wall time, which is not summed across threads.\n\n"
"   Keep this in mind when reading the Aggregate Wall Seconds and CPU Seconds\n"
"   for a threaded code.\n\n"
"   In many cases for a threaded global routine, the CPU Seconds will be\n"
"   greather than the Wall seconds by a factor equal to the number of threads.\n\n"
"   Refer to HTML documentation for further info on this.\n\n";

static char * AGGREGATE_MSG = 
"  Aggregate\n\n"
"    Num Calls ........... Number of times routine was called.\n"
"                          For (G)lobal routines, summed across all MPI processes\n"
"                          For (T)hreaded routines, summed across all MPI\n"
"                          processes and threads.\n\n"
"    Wall Secs ........... Wall Seconds spent in routine.\n"
"                          For (G)lobal and (T)hreaded routines, summed across\n"
"                          all MPI processes.  See above note on the gathering\n"
"                          of wall seconds.\n\n"
"    CPU Secs ............ CPU Seconds spent in routine.\n"
"                          For (G)lobal routines, summed across all MPI Processes\n"
"                          For (T)hreaded routines, summed across all MPI\n"
"                          processes and threads.  See above note on the\n"
"                          gathering of cpu seconds.\n\n"
"    FLOPS ............... Number of FLOPS executed by this routine and all \n"
"                          routines called by it.\n\n"
"    MFLOP / Wall Secs ... Aggregate FLOPS / Wall Secs of single MPI Process \n"
"                          which had the MAX wall seconds\n\n"
"    Processor or Domain . Not Applicable.\n\n";

static char * AVERAGE_MSG = 
"  Average\n\n"
"    Each of these averages is simply the Aggregate as defined above divided\n"
"    by either the number of MPI processes or threads.\n\n"
"    For (G)lobal routines, divide by number of MPI processes which called\n"
"    the routine.\n\n"
"    For (T)hreaded routines, divide by number of threads across all MPI\n"
"    processes which called the routine.\n\n"
"    Num Calls ........... Aggregate Num Calls / Num Of Processes or Threads\n"
"    Wall Secs ........... Aggregate Wall Secs / Num Of Processes or Threads\n"
"    CPU Secs ............ Aggregate CPU Secs  / Num Of Processes or Threads\n"
"    FLOPS ............... Aggregate FLOPS     / Num Of Processes or Threads\n"
"    MFLOP / Wall Secs ... Aggregate MFLOPS    / Num Of Processes or Threads\n"
"    Processor or Domain . Not Applicable.\n\n";

static char *MAX_MIN_MSG = 
"  Max & Min Rows\n\n"
"    These rows report the max and min of one of the following values:\n"
"    wall seconds, cpu seconds, flops, mflops, num calls. \n\n"
"    For (G)lobal routines, this refers to the two MPI processs which had the \n"
"    max and min values.  This is denoted as \"Proc 2\" for example.\n\n"
"    For (T)hreaded routines, this refers to the two threads across all MPI\n"
"    processes which had the max and min values.  This is denoted as \n"
"    \"Thread 378\" for example.  \n\n"
"    In many codes, threading is done over Blocks or Domains.  So \"Thread 378\"\n"
"    refers to \"Domain 378\".\n\n"
"    Num Calls ........... Min/Max num of times routine was called\n"
"    Wall Secs ........... Min/Max wall secs spent in routine\n"
"    CPU Secs ............ Min/Max cpu secs spent in routine\n"
"    FLOPS ............... Min/Max flops generated by routine\n"
"    MFLOP / Wall Secs ... Min/Max MFLOPS executed by routine\n"
"    Processor or Domain . For (G)lobal routines, MPI Process ID.\n"
"                          For (T)hreaded routines, Thread (Domain, Block, or \n"
"                          other chunk of threaded code).\n\n";

static Analysis_t *FunctionTimer_analysis2(char *name);
static Analysis_t *Analysis_destruct(Analysis_t *ptr);
static Analysis_t *Analysis_construct(int num);
static int         Analysis_init(Analysis_t *ptr);
static void        Analysis_print(FILE *fp, Analysis_t *ptr, int key_field);



int FunctionTimer_setup_attrs(void)
{
  char *me = "FunctionTimer_setup_attrs";
  static int first_time_thru = TRUE;

  char *fields[15] = {"name",      "cntr",
                      "cpu_secs",  "top_cpu_secs",
		      "wall_secs", "top_wall_secs",
		      "flops",     
		      "agg_flops", "top_agg_flops",
                      "level",
                      NULL};
  char *attrs[2]  = {"dump", NULL};

  
  if (RGST_ADD_MULT_FIELD_ATTRS("FunctionTimer_t",fields,attrs) != 0)
     ctlerror(me,gv_errmsg_rgst_add_mult_attrs);

  
  if (first_time_thru == TRUE) {
    inst_c("FunctionTimer_init",     FunctionTimer_init,      zargse, 0, symtab);
    inst_c("FunctionTimer_construct",(int (*)())(FunctionTimer_construct), zargse, 0, symtab);
    first_time_thru = FALSE;
  }

  return(0);
}



int printtimer(void)
{

  char *me = "printtimer";
  char str[STRLEN], tmpstr[STRLEN], msg[1024];
  int i, domain_num;
  Domain_t *domain;
  FILE *myfp = NULL;

  int cpu_sort   = FALSE;
  int wall_sort  = FALSE;
  int flops_sort = FALSE;

  
#ifndef FUNCTION_TIMERS
  return(0);
#endif
  if (ft_timersflag == FALSE) { return(0); }

  
  if (myid == 0) { myfp = fpout; }
  else           { myfp = stdout; }

  
  memset(str,'\0',STRLEN);
  while (ctlflag != iflf) {

    geta(tmpstr);

    if      (strcmp(tmpstr,"cpu")   == 0) { cpu_sort   = TRUE; }
    else if (strcmp(tmpstr,"wall")  == 0) { wall_sort  = TRUE; }
    else if (strcmp(tmpstr,"flops") == 0) { flops_sort = TRUE; }
    else {
      if (strlen(str) != 0) { strcat(str," "); }
      strcat(str,tmpstr);
    }
  }

  
  if (strcmp(str,"") == 0) {

    FunctionTimer_print(stdout, wall_sort, cpu_sort, flops_sort, gv_hash_tbl);
  }
  
  else if (isdigit(str[0])) {

    domain_num = (int)strtol(str, NULL, 10);

    if (domain_num >= nblk) {

      sprintf(msg,"\n\t'%d' is invalid local domain number"
                  "\n\tLocal domains '%d' through '%d' exist",
                  domain_num,0,nblk-1);
      ctlnotice(me,msg);
    }
    else {

      domain = &(domains[domain_num]);

      FunctionTimer_print(stdout, wall_sort, cpu_sort, flops_sort, domain->hash);
    }
  }
  
  else if (strcmp(str,"all") == 0) { 

    fprintf(myfp,"%s\n",DASH114);

    FunctionTimer_print(myfp, wall_sort, cpu_sort, flops_sort, gv_hash_tbl);

    for (i=0; i<nblk; i++) {
      FunctionTimer_print(myfp, wall_sort, cpu_sort, flops_sort, (&domains[i])->hash);
    }

    fprintf(myfp,"%s\n",DASH114);
  }
  
  else {

    sprintf(msg,"\n\t'prti' prints function timers\n\t"
                "\n\tUsage:\n\t"
                "\n\tprti         prints global function timers, alphabetical order"
                "\n\tprti cpu     prints global function timers, sorted by CPU usage"
                "\n\tprti flops   prints global function timers, sorted by FLOPS "
                "\n\tprti 1       prints local domain 1 function timers, alphabetical order"
                "\n\tprti 1 cpu   prints local domain 1 function timers, sorted by CPU usage"
                "\n\tprti 1 flops prints local domain 1 function timers, sorted by FLOPS"
                "\n\tprti all     prints all timers just to the hsp file"
                "\n\tprti help    prints this help message");
    ctlnotice(me,msg);
  }

  return(0);
}



#ifdef SILO
void FunctionTimer_wtsilo( DBfile *idbid, HashTable_t *my_hash_tbl )
{
   char *me = "FunctionTimer_wtsilo";
   char cdir[128], tdir[128];
   int numelm, i;
   FunctionTimer_t **fts = NULL;
   HashElm_t **hashelm ;

   
#ifndef FUNCTION_TIMERS
   return;
#endif
   if (ft_timersflag == FALSE) { return; }

   
   if (DBGetDir(idbid, cdir) != 0) ctlerror(me,gv_errmsg_DBGetDir);

   sprintf(tdir,"%s/FunctionTimer",cdir);

   
   hashelm = hash_get_elm_list( &numelm, "FunctionTimer_t", my_hash_tbl ) ;

   if (numelm > 0) {

     fts = ALLOT(FunctionTimer_t *, numelm);

     if (fts == NULL) { ctlerror(me,gv_errmsg_memory); }

     for (i=0 ; i<numelm ; i++) {
       fts[i] = (FunctionTimer_t *) hashelm[i]->obj ;
       if (fts[i] == NULL) { ctlerror(me,logic_err); }

       
     }

     rgst_write_struct_array(idbid,tdir,"FunctionTimer_t",(void **)fts,numelm);

     FREEMEM(fts);
   }

   FREEMEM(hashelm);

   
   if (DBSetDir(idbid, cdir) != 0) ctlerror(me,gv_errmsg_DBSetDir);
}
#endif



#ifdef SILO
void FunctionTimer_rdsilo( DBfile *idbid, HashTable_t *my_hash_tbl)
{
   char *me = "FunctionTimer_rdsilo";
   char cdir[128], tdir[128];
   int i, nfts;
   FunctionTimer_t **fts, *ftp;

   
#ifndef FUNCTION_TIMERS
   return;
#endif
   if (ft_timersflag == FALSE) { return; }

   
   if (DBGetDir(idbid, cdir) != 0) ctlerror(me,gv_errmsg_DBGetDir);

   sprintf(tdir,"%s/FunctionTimer",cdir);

   
   fts = (FunctionTimer_t **)rgst_read_struct_array(
	  idbid, tdir, "FunctionTimer_t", &nfts);

   
   for (i=0; i<nfts; i++) {

      

     ftp = (FunctionTimer_t *) hash_lookup_obj(fts[i]->name, my_hash_tbl);

     if (ftp == NULL) {

       hash_add(fts[i]->name, "FunctionTimer_t", fts[i], my_hash_tbl);
     }
     else {

        ftp->cntr		+= fts[i]->cntr;

        ftp->cpu_secs		+= fts[i]->cpu_secs;
        ftp->top_cpu_secs	+= fts[i]->top_cpu_secs;

        ftp->wall_secs		+= fts[i]->wall_secs;
        ftp->top_wall_secs	+= fts[i]->top_wall_secs;
	
        ftp->flops		+= fts[i]->flops;
        ftp->agg_flops		+= fts[i]->agg_flops;

        FREEMEM(fts[i]);
     }
   }

   FREEMEM(fts);

   
   if (DBSetDir(idbid, cdir) != 0) ctlerror(me,gv_errmsg_DBSetDir);
}
#endif



int timers_stdout(void)
{
  
  timers_print(stdout);
  return(0);
}

int timers_file(void)
{
  char *me = "timers_file";
  char fn[64], msg[128];
  FILE *fp = NULL;

  static int first_time_thru = TRUE;

  sprintf(fn,"%s.tmr",pbnm);
  
  if (myid == 0) {
    if (first_time_thru == TRUE) { 
      fp = fopen(fn,"w"); 
      first_time_thru = FALSE; 
    }
    else { 
      fp = fopen(fn,"a"); 
      if (fp == NULL) {
        fp = fopen(fn,"w"); 
      }
    }

    if (fp == NULL) {
      sprintf(msg,"fopen of file '%s' failed",fn);
      ctlwarning(me,msg);
      return(0);
    }
  }
  
  timers_print(fp);	 

  if (myid == 0)  {
    fclose(fp);
  }

  return(0);
}

int timers_print(FILE *fp)
{
  char str[STRLEN], tmpstr[STRLEN];
  int sort_field_key = -1;
  int max_field_key  = -1;
  int gotone;

  memset(str,'\0',STRLEN);

  gotone = 1;

  if (lfchk() > 0) gotone = 0;

  while (gotone) {

    peekc(tmpstr);

    
    if (sort_field_key == -1) {

      if      (strcmp(tmpstr,"name") == 0)      { sort_field_key = NAME_FLAG;      }
      else if (strcmp(tmpstr,"mflops") == 0)    { sort_field_key = MFLOPS_FLAG;    }
      else if (strcmp(tmpstr,"flops") == 0)     { sort_field_key = FLOPS_FLAG;     }
      else if (strcmp(tmpstr,"cpu_secs") == 0)  { sort_field_key = CPU_SECS_FLAG;  }
      else if (strcmp(tmpstr,"wall_secs") == 0) { sort_field_key = WALL_SECS_FLAG; }
      else if (strcmp(tmpstr,"num_calls") == 0) { sort_field_key = CNTR_FLAG;      }
    }


    
    if      (strcmp(tmpstr,"name") == 0)      {  }
    else if (strcmp(tmpstr,"mflops") == 0)    { max_field_key = MFLOPS_FLAG;    }
    else if (strcmp(tmpstr,"flops") == 0)     { max_field_key = FLOPS_FLAG;     }
    else if (strcmp(tmpstr,"cpu_secs") == 0)  { max_field_key = CPU_SECS_FLAG;  }
    else if (strcmp(tmpstr,"wall_secs") == 0) { max_field_key = WALL_SECS_FLAG; }
    else if (strcmp(tmpstr,"num_calls") == 0) { max_field_key = CNTR_FLAG;      }
    else { gotone = 0; }

    if (gotone) geta(tmpstr);

    if (lfchk() > 0) gotone = 0;
  }

  if (sort_field_key == -1) { sort_field_key = DEFAULT_SORT_FIELD_KEY; }
  if (max_field_key  == -1) { max_field_key  = DEFAULT_MAX_FIELD_KEY;  }

  FunctionTimer_cpuse(fp,sort_field_key,max_field_key);

  return(0);
}



void FunctionTimer_cpuse(

  FILE *fp,                   
  int  sort_field_key,        
  int  max_field_key)         
{
  char *me = "FunctionTimer_cpuse";
  int i, j, ndx, numelm_g, numelm_t, numelm_tot, aasize;
  int *my_nblks   = NULL;  
  int *my_gblks   = NULL;  
  int *my_nnodes  = NULL;  
  int *my_nnalls  = NULL;  
  int *my_nzones  = NULL;  
  int *my_nrzones = NULL;  

  HashElm_t  **hashelm_g      = NULL;
  HashElm_t  **hashelm_t      = NULL;
  Analysis_t **analysis_array = NULL;
  Analysis_t *analysis_ptr    = NULL;

  char tstr[FT_NAMELEN];

  static int first_time_thru = TRUE;

  
  if ((sort_field_key < NAME_FLAG) || (sort_field_key > CNTR_FLAG)) {
    ctlerror(me,logic_err);
  }

  if ((max_field_key < MFLOPS_FLAG) || (max_field_key > CNTR_FLAG)) {
    ctlerror(me,logic_err);
  }

  if (myid == 0) {
    if (fp == NULL) {
      ctlerror(me,"null file pointer");
    }
  }

  
  mpi_reset_cntrs(cycle);

  
  my_nblks   = ALLOT(int, num_procs);
  my_gblks   = ALLOT(int, gnblk);
  my_nnodes  = ALLOT(int, gnblk);
  my_nnalls  = ALLOT(int, gnblk);
  my_nzones  = ALLOT(int, gnblk);
  my_nrzones = ALLOT(int, gnblk);
  
  my_nblks[0] = nblk;

  for (i=0; i<nblk; i++) {
    my_gblks [i] = domains[i].gblk;
    my_nnodes[i] = domains[i].nnodes;
    my_nnalls[i] = domains[i].nnalls;
    my_nzones[i] = domains[i].nzones;
  }

  commpigather (my_nblks,  1,              COM_ONE, COM_INT);
  commpigatherv(my_gblks,  nblk, my_nblks, COM_ONE, COM_INT);
  commpigatherv(my_nnodes, nblk, my_nblks, COM_ONE, COM_INT);
  commpigatherv(my_nnalls, nblk, my_nblks, COM_ONE, COM_INT);
  commpigatherv(my_nzones, nblk, my_nblks, COM_ONE, COM_INT);

  for (i=0; i<gnblk; i++) {

    if (ndims == 3) {

      my_nrzones[i] = (gmap[i].imax - gmap[i].imin) *
                      (gmap[i].jmax - gmap[i].jmin) *
                      (gmap[i].kmax - gmap[i].kmin);
    }
    else {

      my_nrzones[i] = (gmap[i].imax - gmap[i].imin) *
                      (gmap[i].jmax - gmap[i].jmin);
    }
  }

  
  if (myid == 0) {

    if (first_time_thru == TRUE) {

      fprintf(fp,"%s\n",DASH114);

      fprintf(fp,"Domain Distribution Across Processors\n");
      fprintf(fp,"Proc   Domains\n");

      ndx = 0;

      for (i=0; i<num_procs; i++) {

        fprintf(fp,"%4d   ",i);

        for (j=0; j<my_nblks[i]; j++) {

          if (j > 0) {  fprintf(fp,"       "); }

          fprintf(fp,"%4d - %d total zones (nnalls), %d real zones\n",
                  my_gblks[ndx], my_nnalls[ndx], my_nrzones[ndx]);
          ndx++;
        }
      }

      fprintf(fp,"\n");
    }  
  }

  FREEMEM(my_nblks);
  FREEMEM(my_gblks);
  FREEMEM(my_nnodes);
  FREEMEM(my_nnalls);
  FREEMEM(my_nzones);
  FREEMEM(my_nrzones);

  
  if (myid == 0) {

    if (first_time_thru == TRUE) {

      fprintf(fp,"\n%s\n",DASH80);	 
      fprintf(fp,"%s\n",WALL_SEC_MSG);

      fprintf(fp,"\n%s\n",DASH80);	 
      fprintf(fp,"Definitions\n\n");
      fprintf(fp,"%s\n",AGGREGATE_MSG);
      fprintf(fp,"%s\n",AVERAGE_MSG);
      fprintf(fp,"%s\n",MAX_MIN_MSG);

      fprintf(fp,"\n%s\n",DASH80);	 
      fprintf(fp,"Function Timers Analysis Across Processors\n");
      fprintf(fp,"Num of MPI Processes : %d\n",num_procs);
      fprintf(fp,"Num of Domains       : %d\n",gnblk);

      fprintf(fp,"Threading            : ");
      if (ifthreads == TRUE) { fprintf(fp,"ON\n"); }
      else                   { fprintf(fp,"OFF\n"); }

    }
  }

  
  if (myid == 0) {

    numelm_g =  numelm_t = 0;

    if (ft_global_ht != NULL) {
      hashelm_g = hash_get_elm_list(&numelm_g, "FunctionTimer_t", ft_global_ht);
      hash_sort_array(hashelm_g, numelm_g);
    }

    if ((domains != NULL) && (domains[0].hash != NULL)) {
      hashelm_t = hash_get_elm_list(&numelm_t, "FunctionTimer_t", domains[0].hash);
      hash_sort_array(hashelm_t, numelm_t);
    }

    numelm_tot = numelm_g + numelm_t;

    if (numelm_tot > 0) {
      analysis_array = ALLOT(Analysis_t *, numelm_tot);
    }

  }

  
  aasize = 0;

  if (ifparallel) { combcast(&numelm_g,1,COM_INT,0); }

  for (i=0; i<numelm_g; i++) {

    if (myid == 0)  { strcpy(tstr,&(hashelm_g[i]->name[4])); }

    if (ifparallel) { combcast(tstr,FT_NAMELEN,COM_CHAR,0); }

    analysis_ptr =  FunctionTimer_analysis2(tstr);

    if (myid == 0) {

      if (analysis_ptr != NULL) { 
	analysis_array[aasize] = analysis_ptr; 
        aasize++;
	
      }
    }
  }

  if (ifparallel) { combcast(&numelm_t,1,COM_INT,0); }

  for (i=0; i<numelm_t; i++) {

    if (myid == 0)  { strcpy(tstr,&(hashelm_t[i]->name[4])); }

    if (ifparallel) { combcast(tstr,FT_NAMELEN,COM_CHAR,0); }

    analysis_ptr =  FunctionTimer_analysis2(tstr);

    if (myid == 0) {

      if (analysis_ptr != NULL) { 
	analysis_array[aasize] = analysis_ptr; 
	
        aasize++;
      }
    }
  }



  
  if (myid == 0) {

   fprintf(fp,"Sorted by ");

   if      (sort_field_key == NAME_FLAG)  {
     ; 
     fprintf(fp,"Routine Name\n\n");
   }
   else if (sort_field_key == MFLOPS_FLAG)  {
     sort_ptr_array((void **)analysis_array, aasize, offsetof(Analysis_t, max_mflops[0]));
     fprintf(fp,"Max Mflops\n\n");
   }
   else if (sort_field_key == FLOPS_FLAG)  {
     sort_ptr_array((void **)analysis_array, aasize, offsetof(Analysis_t, tot_flops));
     fprintf(fp,"Aggregate Flops\n\n");
   }
   else if (sort_field_key == CPU_SECS_FLAG)  {
     sort_ptr_array((void **)analysis_array, aasize, offsetof(Analysis_t, max_cpu_secs[0]));
     fprintf(fp,"Max CPU Seconds\n\n");
   }
   else if (sort_field_key == WALL_SECS_FLAG)  {
     sort_ptr_array((void **)analysis_array, aasize, offsetof(Analysis_t, max_wall_secs[0]));
     fprintf(fp,"Max Wall Seconds\n\n");
   }
   else if (sort_field_key == CNTR_FLAG)  {
     sort_ptr_array((void **)analysis_array, aasize, offsetof(Analysis_t, max_cntr[0]));
     fprintf(fp,"Max Number Calls\n\n");
   }

   fprintf(fp,"%25s %10s %12s %12s %12s %12s %12s %12s\n",
           "","","PROCESSOR","MFLOP /","","","","");
   fprintf(fp,"%25s %10s %12s %12s %12s %12s %12s %12s\n",
           "ROUTINE","","OR DOMAIN","WALL SEC","FLOPS","CPU SECS","WALL SECS","NUM CALLS");
   fprintf(fp,"%25s %10s %12s %12s %12s %12s %12s %12s\n",
           DASH25,DASH10,DASH12,DASH12,DASH12,DASH12,DASH12,DASH12);

   for (i=0; i<aasize; i++) {
     Analysis_print(fp, analysis_array[i], max_field_key);
     Analysis_destruct(analysis_array[i]);
   }

   FREEMEM(analysis_array);

  }
  
  if (myid == 0) { FREEMEM(hashelm_g); }

  if (myid == 0) {
    fprintf(fp,"\n%s\n",DASH114);
  }

  first_time_thru = FALSE;
}



int FunctionTimer_global_gather(

  char    *name,          
  double **flops_out,     
  double **cpu_secs_out,  
  double **wall_secs_out, 
  double **cntr_out)      
{
  double *flops = NULL, *cpu_secs = NULL, *wall_secs = NULL, *cntr = NULL;
  FunctionTimer_t *ft;

  
  flops     = ALLOT(double, num_procs);
  cpu_secs  = ALLOT(double, num_procs);
  wall_secs = ALLOT(double, num_procs);
  cntr      = ALLOT(double, num_procs);

  
  ft = FunctionTimer_lookup(name, ft_global_ht);

  if (ft != NULL) {
    flops    [0] = ft->agg_flops;
    cpu_secs [0] = ft->cpu_secs;
    wall_secs[0] = ft->wall_secs;
    cntr     [0] = ft->cntr;
  }
  else {
    flops    [0] = -1.0;
    cpu_secs [0] =  0.0;
    wall_secs[0] =  0.0;
    cntr     [0] =  0.0;
  }

  commpigather(flops,     1, COM_ONE, COM_DOUBLE);
  commpigather(cpu_secs,  1, COM_ONE, COM_DOUBLE);
  commpigather(wall_secs, 1, COM_ONE, COM_DOUBLE);
  commpigather(cntr,      1, COM_ONE, COM_DOUBLE);

  
  *flops_out     = flops;
  *cpu_secs_out  = cpu_secs;
  *wall_secs_out = wall_secs;
  *cntr_out      = cntr;

  return(0);
}


int FunctionTimer_thread_gather(

  char    *name,          
  double **flops_out,     
  double **cpu_secs_out,  
  double **wall_secs_out, 
  double **cntr_out,      
  int    **gblks_out)     
{
  double *flops = NULL, *cpu_secs = NULL, *wall_secs = NULL, *cntr = NULL;
  int    *gblks = NULL, *nblks    = NULL;
  int i;
  FunctionTimer_t *ft;

  
  flops     = ALLOT(double, gnblk);
  cpu_secs  = ALLOT(double, gnblk);
  wall_secs = ALLOT(double, gnblk);
  cntr      = ALLOT(double, gnblk);
  gblks     = ALLOT(int,    gnblk);
  nblks     = ALLOT(int,    num_procs);

  
  for (i=0; i<nblk; i++) {

    ft = FunctionTimer_lookup(name,domains[i].hash);

    if (ft != NULL) {

      flops    [i] = ft->agg_flops;
      cpu_secs [i] = ft->cpu_secs;
      wall_secs[i] = ft->wall_secs;
      cntr     [i] = ft->cntr;
      gblks    [i] = domains[i].gblk;
    }
    else {
      flops    [i] = -1.0;
      cpu_secs [i] =  0.0;
      wall_secs[i] =  0.0;
      cntr     [i] =  0.0;
      gblks    [i] = domains[i].gblk;
    }
  }

  
  nblks[0] = nblk;
  commpigather (nblks, 1, COM_ONE, COM_INT);

  commpigatherv(flops,     nblk, nblks, COM_ONE, COM_DOUBLE);
  commpigatherv(cpu_secs,  nblk, nblks, COM_ONE, COM_DOUBLE);
  commpigatherv(wall_secs, nblk, nblks, COM_ONE, COM_DOUBLE);
  commpigatherv(cntr,      nblk, nblks, COM_ONE, COM_DOUBLE);
  commpigatherv(gblks,     nblk, nblks, COM_ONE, COM_INT);

  
  *flops_out     = flops;
  *cpu_secs_out  = cpu_secs;
  *wall_secs_out = wall_secs;
  *cntr_out      = cntr;
  *gblks_out     = gblks;

  FREEMEM(nblks);

  return(0);
}



static Analysis_t *FunctionTimer_analysis2(

  char *name)       
{
  char *me = "FunctionTimer_analysis2";
  char tstr[64], msg[256];

  double tmflops;

  int *flags = NULL;    

  int i, global_flag, domain_flag;

  FunctionTimer_t *ft = NULL;
  Analysis_t      *ptr = NULL;

  
#ifndef FUNCTION_TIMERS
  return (NULL);
#endif
  if (ft_timersflag == FALSE) { return (NULL); }

  
  flags = ALLOT(int, num_procs);

  flags[0] = NOT_FOUND_FLAG;

  ft = FunctionTimer_lookup(name, ft_global_ht);

  if (ft != NULL) {
    flags[0] = GLOBAL_FLAG;
  }
  else {
    for (i=0; i<nblk; i++) {
      ft = FunctionTimer_lookup(name,domains[i].hash);
      if (ft != NULL) {
         flags[0] = DOMAIN_FLAG;
         break;
      }
    }
  }

  
  commpigather(flags, 1, COM_ALL, COM_INT); 

  
  for (i=0; i<num_procs; i++) {
    if (flags[i] != NOT_FOUND_FLAG) break;
  }

  if (i >= num_procs) {
    fprintf(stderr,"%s:%d DEBUG function %s not timed\n",me,myid,name);
    FREEMEM(flags);
    return(NULL);
  }

  
  global_flag = domain_flag = FALSE;

  for (i=0; i<num_procs; i++) {
    if (flags[i] == GLOBAL_FLAG) global_flag = TRUE; 
    if (flags[i] == DOMAIN_FLAG) domain_flag = TRUE; 
  }

  FREEMEM(flags);

  if ((global_flag == TRUE) && (domain_flag == TRUE)) {
    sprintf(msg,"\n\tBypassing analysis of function '%s'"
                "\n\tIt is a global function on some processors and a domain"
                "\n\tfunction on other processors",name);
    ctlnotice(me,msg);
    return(NULL);
  }

  
  ptr = Analysis_construct(1);

  memset (tstr,(int)'\0',32);
  strncpy(tstr,name,21);
  if (global_flag == TRUE) { strcat(tstr," (G)"); }
  else                     { strcat(tstr," (T)"); }

  ptr->name = strsave(tstr);

  
  if (global_flag == TRUE) {

    
    ptr->flops     = ALLOT(double, num_procs);
    ptr->cpu_secs  = ALLOT(double, num_procs);
    ptr->wall_secs = ALLOT(double, num_procs);
    ptr->cntr      = ALLOT(double, num_procs);

    ptr->len  = num_procs;
    ptr->nlen = num_procs;  

    FunctionTimer_global_gather(name,
                                &(ptr->flops),     &(ptr->cpu_secs), 
				&(ptr->wall_secs), &(ptr->cntr));

    
    if (myid != 0) {

      ptr = Analysis_destruct(ptr);
    }
    else {

      
      for (i=0; i<ptr->len; i++) {

        
        if (ptr->flops[i] < 0) {

          ptr->nlen--;
        }
        else {

          
          ptr->tot_flops += ptr->flops[i];

          if (ptr->flops[i] > ptr->max_flops[0]) {

            ptr->max_flops[0] = ptr->flops[i];
            ptr->max_flops[1] = i;
          }

          if (ptr->flops[i] < ptr->min_flops[0]) {

            ptr->min_flops[0] = ptr->flops[i];
            ptr->min_flops[1] = i;
          }

          
          ptr->tot_cntr += ptr->cntr[i];

          if (ptr->cntr[i] > ptr->max_cntr[0]) {

            ptr->max_cntr[0] = ptr->cntr[i];
            ptr->max_cntr[1] = i;
          }

          if (ptr->cntr[i] < ptr->min_cntr[0]) {

            ptr->min_cntr[0] = ptr->cntr[i];
            ptr->min_cntr[1] = i;
          }

          
          if (ptr->cpu_secs[i] > CPU_SEC_CUTOFF) {

            ptr->tot_cpu_secs += ptr->cpu_secs[i];

            if (ptr->cpu_secs[i] > ptr->max_cpu_secs[0]) {

              ptr->max_cpu_secs[0] = ptr->cpu_secs[i];
              ptr->max_cpu_secs[1] = i;
            }

            if (ptr->cpu_secs[i] < ptr->min_cpu_secs[0]) {

              ptr->min_cpu_secs[0] = ptr->cpu_secs[i];
              ptr->min_cpu_secs[1] = i;
            }
          }

          if (ptr->wall_secs[i] > WALL_SEC_CUTOFF) {

            ptr->tot_wall_secs += ptr->wall_secs[i];

            if (ptr->wall_secs[i] > ptr->max_wall_secs[0]) {

              ptr->max_wall_secs[0] = ptr->wall_secs[i];
              ptr->max_wall_secs[1] = i;
            }

            if (ptr->wall_secs[i] < ptr->min_wall_secs[0]) {

              ptr->min_wall_secs[0] = ptr->wall_secs[i];
              ptr->min_wall_secs[1] = i;
            }

            tmflops = (1.0e-6 * ptr->flops[i]) / ptr->wall_secs[i];

            if (tmflops > ptr->max_mflops[0]) {

              ptr->max_mflops[0] = tmflops;
              ptr->max_mflops[1] = i;
            }

            if (tmflops < ptr->min_mflops[0]) {

              ptr->min_mflops[0] = tmflops;
              ptr->min_mflops[1] = i;
            }
  
          } 
        }   
      }     
    }       
  }         

  
  else if (domain_flag == TRUE) {

    
    ptr->flops     = ALLOT(double, gnblk);
    ptr->cpu_secs  = ALLOT(double, gnblk);
    ptr->wall_secs = ALLOT(double, gnblk);
    ptr->gblks     = ALLOT(int,    gnblk);

    ptr->len  = gnblk;
    ptr->nlen = gnblk;         

    FunctionTimer_thread_gather(name,
                                &(ptr->flops),     &(ptr->cpu_secs),
                                &(ptr->wall_secs), &(ptr->cntr),
				&(ptr->gblks));

    
    if (myid != 0) {

      ptr = Analysis_destruct(ptr);
    }
    else {

      
      for (i=0; i<gnblk; i++) {

        if (ptr->flops[i] < 0) {

          ptr->nlen--;
        }
        else {

          
          ptr->tot_flops += ptr->flops[i];

          if (ptr->flops[i] > ptr->max_flops[0]) {

            ptr->max_flops[0] = ptr->flops[i];
            ptr->max_flops[1] = i;
          }

          if (ptr->flops[i] < ptr->min_flops[0]) {

            ptr->min_flops[0] = ptr->flops[i];
            ptr->min_flops[1] = i;
          }

          
          ptr->tot_cntr += ptr->cntr[i];

          if (ptr->cntr[i] > ptr->max_cntr[0]) {

            ptr->max_cntr[0] = ptr->cntr[i];
            ptr->max_cntr[1] = i;
          }

          if (ptr->cntr[i] < ptr->min_cntr[0]) {

            ptr->min_cntr[0] = ptr->cntr[i];
            ptr->min_cntr[1] = i;
          }

          
          if (ptr->cpu_secs[i] > CPU_SEC_CUTOFF) {

            ptr->tot_cpu_secs += ptr->cpu_secs[i];

            if (ptr->cpu_secs[i] > ptr->max_cpu_secs[0]) {

              ptr->max_cpu_secs[0] = ptr->cpu_secs[i];
              ptr->max_cpu_secs[1] = i;
            }

            if (ptr->cpu_secs[i] < ptr->min_cpu_secs[0]) {

              ptr->min_cpu_secs[0] = ptr->cpu_secs[i];
              ptr->min_cpu_secs[1] = i;
            }
          }

          if (ptr->wall_secs[i] > WALL_SEC_CUTOFF) {

            ptr->tot_wall_secs += ptr->wall_secs[i];

            if (ptr->wall_secs[i] > ptr->max_wall_secs[0]) {

              ptr->max_wall_secs[0] = ptr->wall_secs[i];
              ptr->max_wall_secs[1] = i;
            }

            if (ptr->wall_secs[i] < ptr->min_wall_secs[0]) {

              ptr->min_wall_secs[0] = ptr->wall_secs[i];
              ptr->min_wall_secs[1] = i;
            }

            tmflops = (1.0e-6 * ptr->flops[i]) / ptr->wall_secs[i];

            if (tmflops > ptr->max_mflops[0]) {

              ptr->max_mflops[0] = tmflops;
              ptr->max_mflops[1] = i;
            }

            if (tmflops < ptr->min_mflops[0]) {

              ptr->min_mflops[0] = tmflops;
              ptr->min_mflops[1] = i;
            }

          } 
        }   
      }     
    }       
  }         
  else {

    ctlerror(me,logic_err);
    ptr = Analysis_destruct(ptr);
    return(NULL);
  }

  return(ptr);
}



static void Analysis_print(

  FILE       *fp,            
  Analysis_t *ptr,           
  int         key_field)     
{
  char *me = "Analysis_print";
  char tstr[64], tname[32];
  int ndx, global_flag;
  double my_agg_mflops;

  
  
  

  
  if ((ptr->tot_flops > 0) || (ptr->tot_wall_secs > WALL_SEC_CUTOFF)) { ; }
  else                                                                { return; }

  
  my_agg_mflops = (1.0e-6 * ptr->tot_flops) / ptr->max_wall_secs[0];

  my_agg_mflops    = MAX(my_agg_mflops,         0.0);

  

  
  global_flag = FALSE;
  if (strstr(ptr->name,"(G)") != NULL) { global_flag = TRUE; }

  
  fprintf(fp,"%-25s %10s %12s %e %e %e %e %e\n",
             ptr->name,"Aggregate","N/A",
             my_agg_mflops,
             ptr->tot_flops,
             ptr->tot_cpu_secs,               
             ptr->tot_wall_secs,              
	     ptr->tot_cntr);

  fprintf(fp,"%-25s %10s %12s %e %e %e %e %e\n",
             ptr->name,"Average","N/A",
             my_agg_mflops      / ptr->nlen,
             ptr->tot_flops     / ptr->nlen,
             ptr->tot_cpu_secs  / ptr->nlen,  
             ptr->tot_wall_secs / ptr->nlen,  
	     ptr->tot_cntr      / ptr->nlen);

  
  if      (key_field == MFLOPS_FLAG) {

    ndx = (int)ptr->max_mflops[1];

    if (ndx < 0) {
      fprintf(fp,"-%25s %10s %12s %12s %12s %12s %12s %12s\n",
              ptr->name,"Mflops Max","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-25s %10s %12s %e %e %e %e %e\n",
              ptr->name,"Mflops Max",tstr,
              ptr->max_mflops[0],
              ptr->flops[ndx],
              ptr->cpu_secs[ndx],
              ptr->wall_secs[ndx],
	      ptr->cntr[ndx]);
    }

    ndx = (int)ptr->min_mflops[1];

    if (ndx < 0) {
      fprintf(fp,"%-25s %10s %12s %12s %12s %12s %12s %12s\n",
              ptr->name,"Mflops Min","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-25s %10s %12s %e %e %e %e %e\n",
              ptr->name,"Mflops Min",tstr,
              ptr->min_mflops[0],
              ptr->flops[ndx],
              ptr->cpu_secs[ndx],
              ptr->wall_secs[ndx],
	      ptr->cntr[ndx]);
    }

  }

  
  else if (key_field == WALL_SECS_FLAG) {

    ndx = (int)ptr->max_wall_secs[1];

    memset(tname,(int)'\0',32);
    strncpy(tname,ptr->name,22);

    if (ndx < 0) {
      fprintf(fp,"%-22s %13s %12s %12s %12s %12s %12s %12s\n",
              tname,"Wall Secs Max","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-22s %13s %12s %e %e %e %e %e\n",
              tname,"Wall Secs Max",tstr,
              (1.0e-6 * ptr->flops[ndx]) / ptr->wall_secs[ndx],
              ptr->flops[ndx],
              ptr->cpu_secs[ndx],
              ptr->wall_secs[ndx],
	      ptr->cntr[ndx]);
    }

    ndx = (int)ptr->min_wall_secs[1];

    if (ndx < 0) {
      fprintf(fp,"%-22s %13s %12s %12s %12s %12s %12s %12s\n",
              tname,"Wall Secs Min","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-22s %13s %12s %e %e %e %e %e\n",
              tname,"Wall Secs Min",tstr,
              (1.0e-6 * ptr->flops[ndx]) / ptr->wall_secs[ndx],
              ptr->flops[ndx],
              ptr->cpu_secs[ndx],
              ptr->wall_secs[ndx],
	      ptr->cntr[ndx]);
    }
  }
  
   else if (key_field == CPU_SECS_FLAG) {

    ndx = (int)ptr->max_cpu_secs[1];

    memset(tname,(int)'\0',32);
    strncpy(tname,ptr->name,23);

    if (ndx < 0) {
      fprintf(fp,"%-23s %12s %12s %12s %12s %12s %12s %12s\n",
               tname,"CPU Secs Max","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-23s %12s %12s %e %e %e %e %e\n",
              tname,"CPU Secs Max",tstr,
              (1.0e-6 * ptr->flops[ndx]) / ptr->wall_secs[ndx],
              ptr->flops[ndx],
              ptr->cpu_secs[ndx],
              ptr->wall_secs[ndx],
	      ptr->cntr[ndx]);
    }

    ndx = (int)ptr->min_cpu_secs[1];

    if (ndx < 0) {
      fprintf(fp,"%-23s %12s %12s %12s %12s %12s %12s %12s\n",
              tname,"CPU Secs Min","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-23s %12s %12s %e %e %e %e %e\n",
              tname,"CPU Secs Min",tstr,
              (1.0e-6 * ptr->flops[ndx]) / ptr->wall_secs[ndx],
              ptr->flops[ndx],
              ptr->cpu_secs[ndx],
              ptr->wall_secs[ndx],
	      ptr->cntr[ndx]);
    }

  }
  
  else if (key_field == FLOPS_FLAG) {

    ndx = (int)ptr->max_flops[1];

    if (ndx < 0) {
      fprintf(fp,"%-25s %10s %12s %12s %12s %12s %12s %12s\n",
              ptr->name,"Flops Max","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-25s %10s %12s %e %e %e %e %e\n",
              ptr->name,"Flops Max",tstr,
              (1.0e-6 * ptr->flops[ndx]) / ptr->wall_secs[ndx],
              ptr->flops[ndx],
              ptr->cpu_secs[ndx],
              ptr->wall_secs[ndx],
	      ptr->cntr[ndx]);
    }

    ndx = (int)ptr->min_flops[1];

    if (ndx < 0) {
      fprintf(fp,"%-25s %10s %12s %12s %12s %12s %12s %12s\n",
              ptr->name,"Flops Min","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-25s %10s %12s %e %e %e %e %e\n",
              ptr->name,"Flops Min",tstr,
              (1.0e-6 * ptr->flops[ndx]) / ptr->wall_secs[ndx],
              ptr->flops[ndx],
              ptr->cpu_secs[ndx],
              ptr->wall_secs[ndx],
	      ptr->cntr[ndx]);
    }
  }
  
  else if (key_field == CNTR_FLAG) {

    ndx = (int)ptr->max_cntr[1];

    memset(tname,(int)'\0',32);
    strncpy(tname,ptr->name,22);

    if (ndx < 0) {
      fprintf(fp,"%-22s %13s %12s %12s %12s %12s %12s %12s\n",
              tname,"Num Calls Max","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-22s %13s %12s %e %e %e %e %e\n",
              tname,"Num Calls Max",tstr,
	      ptr->wall_secs[ndx] > WALL_SEC_CUTOFF ? (1.0e-6 * ptr->flops[ndx]) / ptr->wall_secs[ndx] : 0.0,
              ptr->flops    [ndx],
              ptr->cpu_secs [ndx] > CPU_SEC_CUTOFF  ? ptr->cpu_secs [ndx] : 0,
              ptr->wall_secs[ndx] > WALL_SEC_CUTOFF ? ptr->wall_secs[ndx] : 0,
	      ptr->cntr[ndx]);
    }

    ndx = (int)ptr->min_flops[1];

    if (ndx < 0) {
      fprintf(fp,"%-22s %13s %12s %12s %12s %12s %12s %12s\n",
              tname,"Num Calls Min","N/A",DASH4,DASH4,DASH4,DASH4,DASH4);
    }
    else {
      if (global_flag == TRUE) { sprintf(tstr,"Proc %4d",ndx); }
      else                     { sprintf(tstr,"Thread %4d",ndx); }
      fprintf(fp,"%-22s %13s %12s %e %e %e %e %e\n",
              tname,"Num Calls Min",tstr,
	      ptr->wall_secs[ndx] > WALL_SEC_CUTOFF ? (1.0e-6 * ptr->flops[ndx]) / ptr->wall_secs[ndx] : 0.0,
              ptr->flops[ndx],
              ptr->cpu_secs [ndx] > CPU_SEC_CUTOFF  ? ptr->cpu_secs [ndx] : 0,
              ptr->wall_secs[ndx] > WALL_SEC_CUTOFF ? ptr->wall_secs[ndx] : 0,
	      ptr->cntr[ndx]);
    }

  }
  
  else {
    ctlerror(me,logic_err);
  }

  fprintf(fp,"\n");

  return;
}



static int Analysis_init(Analysis_t *ptr)
{
  ptr->flops = ptr->wall_secs = ptr->cpu_secs = NULL;
  ptr->gblks = NULL;

  ptr->len       = ptr->nlen          = 0;

  ptr->tot_flops = ptr->tot_wall_secs = ptr->tot_cpu_secs = 0.0;

  ptr->min_flops   [0] = ptr->min_wall_secs[0] = HUGENUM;
  ptr->min_cpu_secs[0] = ptr->min_mflops   [0] = HUGENUM;

  ptr->max_flops   [0] = ptr->max_wall_secs[0] = HUGENUM * -1.0;
  ptr->max_cpu_secs[0] = ptr->max_mflops   [0] = HUGENUM * -1.0;

  ptr->min_flops   [1] = ptr->min_wall_secs[1] = -1;
  ptr->min_cpu_secs[1] = ptr->min_mflops   [1] = -1;
  ptr->max_flops   [1] = ptr->max_wall_secs[1] = -1;
  ptr->max_cpu_secs[1] = ptr->max_mflops   [1] = -1;

  return(0);
}



static Analysis_t *Analysis_construct(int num)
{
  char *me = "Analysis_construct";
  int i;
  Analysis_t *ptr;
 
  if (num < 1) ctlerror(me,logic_err);
 
  ptr = ALLOT(Analysis_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
 
  for (i=0; i<num; i++) {
    Analysis_init(&(ptr[i]));
  }
 
  return(ptr);
}


static Analysis_t *Analysis_destruct(Analysis_t *ptr)
{
  char *me = "Analysis_destruct";
 
  if (ptr == NULL) {
    ctlnotice(me,"Attempt to destroy null pointer");
  }
  else {
    FREEMEM(ptr->name);
    FREEMEM(ptr->flops);
    FREEMEM(ptr->cpu_secs);
    FREEMEM(ptr->wall_secs);
    FREEMEM(ptr->gblks);
    FREEMEM(ptr);
  }

  return (Analysis_t *)(NULL);
}


