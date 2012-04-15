#ifndef CycleMesg_H
#define CycleMesg_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {
   char *name;          /* unique name for this cycle frequency data struct */
   int  cyctp;
   int  c1;             /* stop cycle */
   int  c2;             /* stop cycle */
   int  dc;             /* cycle step (aka delta cycle) */
   int  nextCycle;      /* next cycle at which to take action */
   char *msg;
   int  msglen;

} CycleMesg_t ;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern void printcyclefreq(CycleMesg_t *fq);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern int ncyc ;
extern int maxcycleplot ;
extern CycleMesg_t *cyc; /* Array of size ncycx of cycle frequencies */
extern int *cyctp;       /* Array of size ncycx of ints.
                            If a frequency is used to generate a versus-time
                            edit, then this index will be 0 or greater and
                            is used to index into the cyc[] array.  If the
                            frequency is used for purposes other than versus-
                            time edits (time plots), then the index will
                            be set to -1 */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
