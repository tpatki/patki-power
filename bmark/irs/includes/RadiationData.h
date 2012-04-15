#ifndef RadiationData_H
#define RadiationData_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {
   double *dbl ;
   double *dbc ;
   double *dbr ;
   double *dcl ;
   double *dcc ;
   double *dcr ;
   double *dfl ;
   double *dfc ;
   double *dfr ;
   double *cbl ;
   double *cbc ;
   double *cbr ;
   double *ccl ;
   double *ccc ;
   double *ccr ;
   double *cfl ;
   double *cfc ;
   double *cfr ;
   double *ubl ;
   double *ubc ;
   double *ubr ;
   double *ucl ;
   double *ucc ;
   double *ucr ;
   double *ufl ;
   double *ufc ;
   double *ufr ;
} RadiationData_t ;



/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern RadiationData_t newMatrix(int size, int dimensionality, int jp, int kp);
extern void CopyMatrix(RadiationData_t *copyMatrix, RadiationData_t *originalMatrix, int size, int dimensionality);


#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
/*
 Define radiation coupling matrix structure *rblk
 Define CG preconditioning matrix structure *cblk
*/
extern RadiationData_t *rblk    ; /* HH_INIT NULL */
extern RadiationData_t *rblkbak ; /* HH_INIT NULL */
extern RadiationData_t *cblk ;    /* HH_INIT NULL */
extern RadiationData_t *pblk ;    /* HH_INIT NULL */


/*******************************************************************************
* END OF FILE
*******************************************************************************/
