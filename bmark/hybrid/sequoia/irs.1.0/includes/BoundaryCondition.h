#ifndef BoundaryCondition_H
#define BoundaryCondition_H

/* RGST_START */

#include "irsdefs.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char   ndxName[MAXLINE]; /* name of ndxlist */

   int    type  ;           /* type of boundary condition */
   int    rtype ;           /* radiation boundary type */
   int    mode  ;
   int    *ndx  ;           /* RGST_LEN len */
                            /* index list of boundary nodes */
   int    len   ;           /* length of index list */
   int   *zonelist;         /* RGST_LEN lenZonelist */
                            /* list of boundary zones */
   int    lenZonelist;      /* length of zonelist*/

   int    pn    ;           /* offset to phony nodes */
   int    rz    ;           /* offset to real zones */
   int    pz    ;           /* offset to phony zones */

   double nx    ;           /* x normal */
   double ny    ;           /* y normal */
   double nz    ;           /* z normal */

   int    id    ;       /* vsame id */
   int    ngrp  ;       /* number of groups for vsame summing */
   int    lgrp  ;       /* length of each group */

}  BoundaryCondition_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
struct Domain_s ;

extern int  BoundaryCondition_init(BoundaryCondition_t *ptr);
extern int  BoundaryCondition_setup_attrs(void);
extern void BoundaryCondition_merge(struct Domain_s *domain);

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
