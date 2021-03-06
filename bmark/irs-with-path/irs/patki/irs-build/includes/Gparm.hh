#ifndef Gparm_H
#define Gparm_H

/* RGST_START */

#include "irsdefs.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char sym[MAXWORD] ;
   char val[20] ;
   int type ;

} Gparm_t ;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
int      ngparm ;
int      ngparmx ;
Gparm_t *gparm ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
