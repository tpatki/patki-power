#ifndef AEStackElm_H
#define AEStackElm_H

#include "Rgst.h"

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

#define RGST_Attribute_t_STR      "RGST_Attribute_t"

#define GETCOMMA() \
  { char msym[MAXWORD]; \
    char mmsg[MAXLINE]; \
    peekc(msym); \
    if (msym[0] == ',') geta(msym); \
  }

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/
typedef struct AEStackElm_s {

   char *          routine; /* Name of routine which placed item on the stack */
   RGST_Datatype_t type;    /* R_INT, R_DOUBLE,  R_INT_ARRAY, R_DOUBLE_ARRAY,
                               or R_CHAR if this is a marker created by
                               ae_stack_mark */
   int             nval;    /* Count of number of values placed on stack
                               for a given routine.  First item is 1.  Can be
                               used to see if there are more items for the
                               previous function still on the stack waiting
                               to be popped. */
   int             i_value; /* if type is R_INT */
   int            *i_array; /* if type is R_INT_ARRAY */
   double          d_value; /* if type is R_DOUBLE */
   double         *d_array; /* if type is R_DOUBLE_ARRAY */
   int             len;     /* length of i_array or d_array arrays */

   char           *label;   /* if data has a label, it will be stored here
                               if type is R_CHAR (ie ae_stack_mark) then the
                               name of the function placing items on the stack
                               will be stored here */
   
   struct AEStackElm_s      *next, /* Links to next and prev items in linked list */
                            *prev; /* that forms the stack */

} AEStackElm_t; 

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
AEStackElm_t * AEStackElm_construct(int num);
AEStackElm_t * AEStackElm_destruct(AEStackElm_t *ptr);
AEStackElm_t * AEStack_pop(void);
AEStackElm_t * ae_stack_pop(void);

int      AEStackElm_init(AEStackElm_t *ptr);
int      AEStack_push(AEStackElm_t *ptr);
int      ae_stack_num_vals(char *routine);
int      ae_stack_pop_int(void);
int      ae_stack_push(char *routine, char *label, RGST_Datatype_t type, ...);
void     ae_stack_empty_check(void);
double   ae_stack_pop_dbl(void);

int    * ae_stack_pop_int_array(void);
double * ae_stack_pop_dbl_array(void);

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
AEStackElm_t *gv_ae_stack_bottom =  NULL ;
AEStackElm_t *gv_ae_stack_top =  NULL ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/

