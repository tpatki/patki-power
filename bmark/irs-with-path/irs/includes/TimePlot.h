#ifndef TimePlot_H
#define TimePlot_H

/* RGST_START */

#include "FreqMesg.h"
#include "CycleMesg.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- TIME PLOT EDIT DATA STRUCTURES
-
- TimePlotCurve_t and TimePlot_t hold the time plot edit data.  This data is gathered
- while the program runs and is written to and read from the silo restart
- file.
-
- TimePlot_t is instantiated by the global var *tpdata which is declared
- in irs.h.   tpdata[] is therefore a global array of time plot data
- structures.
-
- TimePlotCurve_t is only instantiated from the *tp_curs reference in TimePlot_t.
- There is no global var of type TimePlotCurve_t
-
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char *name;                  /* Unique name for this time plot curve */

   char *eval_string;           /* String to be evaluated which generates the data
                                   for the curves */
   int   num_vals;              /* The evaluation string may generate multiple values
                                   -- each value will be a separate curve.
                                   This is how many it generates.  This
                                   is also the size of the tpc_labels and tpc_data
                                   arrays since we need a label and data for each
                                   curve */

   char **labels;               /* RGST_LEN num_vals */
                                /* Curve labels */

   double **data;               /* RGST_LEN num_vals alloc_data_pts */
                                /* Curve data -- the actual data which forms the curve */

   int  *alloc_data_pts;        /* RGST_LEN num_vals */
                                /* The allocated size of the tpc_data arrays */

} TimePlotCurve_t;

typedef struct {

   char        *name;           /* Unique name for this time plot */

                                /* NOTE: The edits are done on either a
                                   time frequency or a cycle frequency.
                                   2 of the following 4 fields will hold
                                   data and the other 2 will be NULL */

   char        *fq_name;        /* Unique name of time frequency data
                                   structure for this time plot */

   FreqMesg_t  *fq_dat;         /* RGST_LEN 1 */
                                /* Pointer to time frequency data
                                   structure for this time plot */

   char        *cyc_name;       /* Unique name of the cycle frequency data
                                   structure for this time plot */

   CycleMesg_t *cyc_dat;        /* RGST_LEN 1 */
                                /* Pointer to cycle frequency data structure
                                   for this time plot */

   TimePlotCurve_t  **tp_curs;  /* RGST_LEN num_tp_curs */
                                /* Array of time plot curve pointers */

   char        **tp_curs_names; /* RGST_LEN num_tp_curs */
                                /* Names of each time plot curve */

   int num_data_pts;            /* Current number of entries stored in
                                   each time plot in the above tpc_data[]
                                   array */

   int max_data_pts;            /* max num of pts on each time plot in the
                                   above tpc_data[] arrays.  This is derived
                                   using the begin, end, and delta times
                                   from the timeplot command */

   int alloc_data_pts;          /* Actual number of pts allocated in the
                                   above tpc_data[] array.  This will be
                                   <= data_pts_max.  If data_pts_max is very
                                   large (due to a very small time step
                                   like .001), then this will be set
                                   to a value smaller than data_pts_max.
                                   This is because, it is very probable
                                   that each cycle will span many time
                                   steps, so there is no way that data_pts_max
                                   values will every be saved--and the
                                   space would just be wasted. */

   int inc_data_pts;            /* As data in the tpc_data arrays grows,
                                   the arrays will be incremented in steps
                                   of this size */

   int num_tp_curs;             /* Num of entries in the above tp_curs[] array */

} TimePlot_t;


/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#ifdef SILO
struct DBfile ;
extern int TimePlotCurve_post_read(struct DBfile *idbid, TimePlotCurve_t *ptr, char *field_name);
extern int TimePlot_post_read(struct DBfile *idbid, TimePlot_t *ptr, char *field_name);
extern int TimePlot_write(struct DBfile *idbid, TimePlot_t *ptr, char *field_name);
#endif

extern TimePlotCurve_t * TimePlotCurve_construct(int num);
extern TimePlotCurve_t * TimePlotCurve_create(char *sym, int tpc_num);
extern TimePlotCurve_t * TimePlotCurve_destruct(TimePlotCurve_t *ptr);
extern TimePlotCurve_t * free_TimePlotCurve_t(TimePlotCurve_t *tp);
extern TimePlot_t * TimePlot_construct(int num);
extern TimePlot_t * TimePlot_destruct(TimePlot_t *ptr);
extern TimePlot_t * free_TimePlot_t (TimePlot_t *tp) ;
extern int TimePlotCurve_init(TimePlotCurve_t *ptr);
extern int TimePlotCurve_setup_attrs(void);
extern int TimePlot_init(TimePlot_t *ptr);
extern int TimePlot_setup_attrs(void);
extern void TimePlot_expand(TimePlot_t *tp);
extern void printtimeplot(TimePlot_t *tp);
extern void printtpcurve(TimePlotCurve_t *tpc);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
        /*----------------------------------------------------------------------
        - time plot parms 
        -
        - These global scalar vars are used in conjuction with the global array
        - tpdata[] 
        ----------------------------------------------------------------------*/
extern int ntp ;		/* Current num of time plot data structures */
extern int maxtpdata ;		/* Maximum num of time plot data structures.  
				   This is therefore the number of entries
				   allocated for the global array tpdata[]. 
				   As of 09/10/97, this is set to 20 in
				   parminit.c */
extern int itp ;		/* This is used as an index into the time 
				   plot array tpdata[] */

extern int maxtplot;		/* Max number of tplot lines within a */
				/* timeplot or cycleplot loop */

extern int maxtimeplot ;

	/*-----------------------------------------------------------------------
	- time plot structure
	-----------------------------------------------------------------------*/
extern TimePlot_t **tpdata ;    /* Array of ptrs to time plot data structs */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
