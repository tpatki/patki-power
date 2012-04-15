#ifndef  FunctionTimer_H
#define  FunctionTimer_H

#ifdef TFLOPS
#include <nx.h>
#endif

#include <time.h>
#include <sys/times.h>
#include <stdio.h>

#include "irsdefs.h"
#include "Hash.h"

/*------------------------------------------------------------------------------
- MPI stuff
------------------------------------------------------------------------------*/

        /*----------------------------------------------------------------------
        - If compiling with mpi, then include the mpi header file
        - otherwise define some mpi stuff so that the code will compile properly 
        - even without the mpi library.
        ----------------------------------------------------------------------*/
#ifdef COMMPI

#define __MPIO_INCLUDE
#include <mpi.h>
#undef __MPIO_INCLUDE

#else

typedef int MPI_Status ;
typedef int MPI_Request ;
typedef int MPI_Op ;
typedef int MPI_Datatype ;
typedef int MPI_Comm ;
typedef int MPI_Group ;

extern  MPI_Request  MPI_REQUEST_NULL ;
extern  MPI_Datatype MPI_DOUBLE ;
extern  MPI_Datatype MPI_CHAR;
extern  MPI_Datatype MPI_INT ;
extern  MPI_Comm     MPI_COMM_WORLD ;
extern  MPI_Op       MPI_SUM  ;
extern  MPI_Op       MPI_MIN  ;
extern  MPI_Op       MPI_MAX  ;

#define MPI_UNDEFINED -32766
#define MPI_SUCCESS     0

#define NO_MPI  -999    /* define return value for failure to find MPI */
                        /* can't be valid return value in mpi.h */

#endif                           

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/
#define STRLEN 256

#define TIMER_START     0
#define TIMER_STOP      1

#define FINALIZED       0
#define INITIALIZED     1

#ifndef FREEMEM
#define FREEMEM(iptr) if (iptr != NULL) { free(iptr); iptr = NULL; }
#endif

#ifndef ALLOT
#define ALLOT(a,b)  (a *) calloc(b,sizeof(a))
#endif

#ifndef REALLOT
#define REALLOT(a,b,c)  (b *) realloc(a,(c)*sizeof(b))
#endif

#define ALL_CNTRS       0
#define TOTAL_CNTR      1

        /*-----------------------------------------------------------------------
        - Timers can be compiled in only if -DFUNCTION_TIMERS is specified
        -----------------------------------------------------------------------*/
#ifdef FUNCTION_TIMERS 
#define FT_INITIALIZE(m_name, m_ht)        FunctionTimer_initialize(m_name, m_ht);
#define FT_FINALIZE(m_name, m_ht, m_flops) FunctionTimer_finalize(m_name, m_ht, m_flops);
#else
#define FT_INITIALIZE(m_name, m_ht)        
#define FT_FINALIZE(m_name, m_ht, m_flops)
#endif

/*------------------------------------------------------------------------------
- STRUCTURES
------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
- Enumerated Types
-
- One for each mpi routine for which wrappers have been written
-----------------------------------------------------------------------------*/
typedef enum {
   MPI_Abort_cntr,      MPI_Allgather_cntr, MPI_Allgatherv_cntr, 
   MPI_Allreduce_cntr,
   MPI_Barrier_cntr,    MPI_Bcast_cntr,     MPI_Comm_create_cntr, 
   MPI_Comm_group_cntr, MPI_Comm_rank_cntr, MPI_Comm_size_cntr,  
   MPI_Finalize_cntr,   MPI_Gather_cntr,    MPI_Gatherv_cntr,
   MPI_Group_incl_cntr, MPI_Init_cntr,
   MPI_Irecv_cntr,      MPI_Isend_cntr,     MPI_Recv_cntr,       
   MPI_Reduce_cntr,     MPI_Send_cntr,      MPI_Waitall_cntr,     
   MPI_Waitany_cntr,    MPI_Wait_cntr,      MPI_Wtick_cntr,      
   MPI_Wtime_cntr,      MPI_Total_cntr,
   MPI_num_routines 
}  MPI_ROUTINES_t;

/* RGST_START */

#define FT_NAMELEN		128

typedef struct FunctionTimer_s {

   char   name[FT_NAMELEN];             /* name of timer - should be function name also */

   double cntr;                         /* number of times this timer was started */
   double cpu_secs;
   double wall_secs;

   double flops;                        /* flops just for this routine */
   double agg_flops;                    /* flops for this routine and all */
                                        /* routines called underneath this routine */
   double agg_flops_start;              /* used to calculate above agg_flops */

   double *agg_thr_flops_start;         /* RGST_LEN agg_thr_flops_start_len */
                                        /* used to calculate above agg_flops */
   int     agg_thr_flops_start_len;     /* length of above array */

   double top_cpu_secs;
   double top_wall_secs;
   double top_agg_flops;

   double times_start;         		/* wall times when timer starts */
   double times_stop;          		/* wall times when timer stops */

   double clock_start;	       		/* cpu clocks when timer starts */ 
   double clock_stop;          		/* cpu clocks when timer stops */

   int clock_rolls_start;  		/* Number of clock rolls when timer started */
   int clock_rolls_stop;   		/* number of clock rolls when timer stopped */

   int level;
   int setflag;

} FunctionTimer_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
struct DBfile ;
extern void FunctionTimer_rdsilo        (struct DBfile *idbid, HashTable_t *my_hash_tbl);
extern void FunctionTimer_wtsilo        (struct DBfile *idbid, HashTable_t *my_hash_tbl);
#endif

extern void mpi_reset_cntrs	(int cycle);
extern int  timers_file         (void);
extern int  timers_stdout       (void);
extern int  timers_print        (FILE *fp);
extern int test_clockroll       (int rolls, HashTable_t *);

extern void FunctionTimer_maxclock      (double *max, double *min);
extern void FunctionTimer_clock		(int flag,  FunctionTimer_t *fts);
extern void FunctionTimer_initialize	(char *name,  HashTable_t *ht);
extern void FunctionTimer_finalize	(char *name,  HashTable_t *ht, double flops);
extern void FunctionTimer_free		(HashTable_t *ht);
extern void FunctionTimer_print		(FILE *fp, int wall_sort, int cpu_sort, int flops_sort, HashTable_t *ht);
extern void FunctionTimer_out           (FILE *fp, char *fn_name, char *label, int indent, double frac);
extern void FunctionTimer_cpuse         (FILE *fp, int sort_field_flag, int max_field_flag);
extern void FunctionTimer_error         (char proc_name[], char msg[]);
extern void FunctionTimer_init	        (FunctionTimer_t *ptr);
extern void FunctionTimer_warning       (char proc_name[], char msg[]);
extern void FunctionTimer_ht_update     (HashTable_t *old_ht, HashTable_t *new_ht);

extern int  FunctionTimer_ht_setup	(HashTable_t *ht,  char *type);
extern int  FunctionTimer_ht_remove	(HashTable_t *ht,  char *type);
extern int  FunctionTimer_setup_attrs(void);

extern int  FunctionTimer_global_gather (char *name, double **flops, double **cpu_secs, double **wall_secs, double **cntr);
extern int  FunctionTimer_thread_gather (char *name, double **flops, double **cpu_secs, double **wall_secs, double **cntr,  int **gblks);

extern FunctionTimer_t *FunctionTimer_construct	(int num);
extern FunctionTimer_t *FunctionTimer_lookup	(char *name,  HashTable_t *ht);

extern int 	MPI_Init_Wrapper	(int *argc, char ***argv);
extern int 	MPI_Abort_Wrapper	(MPI_Comm comm, int errorcode);
extern int 	MPI_Barrier_Wrapper	(MPI_Comm comm);
extern int 	MPI_Finalize_Wrapper	(void);
extern int 	MPI_Comm_group_Wrapper	(MPI_Comm comm, MPI_Group *group);
extern int 	MPI_Group_incl_Wrapper	(MPI_Group group, int n, int *ranks, MPI_Group *newgroup);
extern int 	MPI_Comm_create_Wrapper	(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm);
extern int 	MPI_Gather_Wrapper	(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);
extern int 	MPI_Gatherv_Wrapper	(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int *recvcount, int *recvdisp, MPI_Datatype recvtype, int root, MPI_Comm comm);
extern int 	MPI_Allgather_Wrapper	(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm);
extern int 	MPI_Allgatherv_Wrapper	(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int *recvcount, int *recvdisp, MPI_Datatype recvtype, MPI_Comm comm);
extern int 	MPI_Bcast_Wrapper	(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm );
extern int 	MPI_Send_Wrapper	(void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
extern int 	MPI_Recv_Wrapper	(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
extern int 	MPI_Isend_Wrapper	(void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request);
extern int 	MPI_Irecv_Wrapper	(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request);
extern int 	MPI_Wait_Wrapper	(MPI_Request *request, MPI_Status *status);
extern int 	MPI_Waitall_Wrapper	(int count, MPI_Request *array_of_requests, MPI_Status *array_of_status);
extern int 	MPI_Waitany_Wrapper	(int count, MPI_Request *array_of_requests, int *index, MPI_Status *status);
extern int 	MPI_Comm_size_Wrapper	(MPI_Comm comm, int *size);
extern int 	MPI_Comm_rank_Wrapper	(MPI_Comm comm, int *rank);
extern int 	MPI_Allreduce_Wrapper	(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
extern int 	MPI_Reduce_Wrapper	(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
extern double 	MPI_Wtime_Wrapper	(void);
extern double 	MPI_Wtick_Wrapper	(void);


#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

#ifdef SILO
struct DBfile ;
extern void FunctionTimer_wtglobals   (struct DBfile *idbid);
extern void FunctionTimer_rdglobals   (struct DBfile *idbid);
#endif

extern double ft_maxclock;      /* max value of clock_t type */
extern double ft_minclock;	/* min value of clock_t type */

extern int debug_switch;

extern int ft_timersflag;	/* Set to FALSE to not use timers */

extern char *	ft_mpi_routine_names[MPI_num_routines];
extern int    	ft_mpi_cntrs        [MPI_num_routines];

extern HashTable_t *	ft_global_ht;
extern HashTable_t **	ft_thread_ht; /* Will be allocated to table of 
                                         ft_num_allocated_ht ptrs at run time */
 
extern int 	ft_num_thread_ht; 
extern int      ft_num_allocated_ht;
extern int 	ft_global_timer_level; 

extern int      ft_running_with_threads;

extern int *	ft_thread_timer_level;	/* These 4 arrays will be allocated to */
extern double * ft_thread_flops;        /* ft_num_allocated_ht at run time */
extern double * ft_thread_cpu_secs;
extern double * ft_thread_wall_secs;
  
extern double 	ft_cpu_secs;    
extern double 	ft_wall_secs;   
extern double 	ft_flops;        

extern double   ft_clock_last;	/* last clock() time, used to detect processor clock rollover */
extern int      ft_clock_rolls;	/* number of times clock() has rolled over */ 

extern char *	ft_out_of_memory;



/*******************************************************************************
* END OF FILE
*******************************************************************************/
