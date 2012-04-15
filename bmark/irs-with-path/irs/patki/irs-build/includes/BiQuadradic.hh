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
void tabin(BiQuadradic_t *xtab, char *tabname, char *fldname, char *sclname, int num);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
BiQuadradic_t *ptab  =  NULL ;
BiQuadradic_t *etab  =  NULL ;
BiQuadradic_t *ktab  =  NULL ;
BiQuadradic_t *stab  =  NULL ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
