#ifndef BiQuadradic_H
#define BiQuadradic_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   int neos ;
   int nt ;
   int nr ;
   double *tgrid ;
   double *rgrid ;
   int ntab ;
   double *ftab ;

} BiQuadradic_t ;


/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern void tabin(BiQuadradic_t *xtab, char *tabname, char *fldname, char *sclname, int num);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
extern BiQuadradic_t *ptab ;	/* HH_INIT NULL */
extern BiQuadradic_t *etab ;	/* HH_INIT NULL */
extern BiQuadradic_t *ktab ;	/* HH_INIT NULL */
extern BiQuadradic_t *stab ;	/* HH_INIT NULL */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
