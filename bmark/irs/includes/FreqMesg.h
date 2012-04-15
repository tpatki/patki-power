#ifndef FreqMesg_H
#define FreqMesg_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {
   char   *name;        /* unique name for this time frequency data struct */
   int    fqtp;
   double t1;           /* start time   */
   double t2;           /* stop time    */
   double dt;           /* time step (aka delta time) */
   double nextTime;     /* next time at which to take action */
   char   *msg;
   int    msglen;

} FreqMesg_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern void printtimefreq(FreqMesg_t *fq);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
- time frequency arrays
------------------------------------------------------------------------------*/
extern int nfq ;
extern FreqMesg_t *fq;   /* Array of size nfqx of time frequencies */
extern int *fqtp;        /* Array of size nfqx of ints.
                            If a frequency is used to generate a versus-time
                            edit, then this index will be 0 or greater and
                            is used to index into the fq[] array.  If the
                            frequency is used for purposes other than versus-
                            time edits (time plots), then the index will
                            be set to -1 */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
