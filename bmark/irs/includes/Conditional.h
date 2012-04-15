#ifndef Conditional_H
#define Conditional_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct Conditional_s {

   int   id;
   int   once;
   int   active;
   int   expression_len;
   int   msg_len;

   char *expression;           /* RGST_LEN expression_len */
   char *msg;                  /* RGST_LEN msg_len */

   struct Conditional_s *next;
   
} Conditional_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
struct DBfile ;
extern void conditionals_rdsilo(struct DBfile *idbid);
extern void conditionals_wtsilo(struct DBfile *idbid);
#endif

extern Conditional_t * Conditional_construct(int num);
extern int Conditional_init(Conditional_t *ptr);
extern int Conditional_setup_attrs(void);
extern void conditionals_add(Conditional_t *cond);
extern void conditionals_free(void);
extern int conditionals_atexit(void);
extern int conditionals_check(void);
extern int conditionals_del(int num);
extern int conditionals_endif(void);
extern int conditionals_eval(void);
extern int conditionals_if(void);
extern int conditionals_input(int mode);
extern int conditionals_redo(int num);
extern int conditionals_show(int num, char * *msgout, int *msglen);

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

#endif
/*******************************************************************************
*                              END OF FILE
*******************************************************************************/
