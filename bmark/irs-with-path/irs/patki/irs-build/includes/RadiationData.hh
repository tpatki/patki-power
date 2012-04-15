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
RadiationData_t newMatrix(int size, int dimensionality, int jp, int kp);
void CopyMatrix(RadiationData_t *copyMatrix, RadiationData_t *originalMatrix, int size, int dimensionality);


#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/
/*
 Define radiation coupling matrix structure *rblk
 Define CG preconditioning matrix structure *cblk
*/
RadiationData_t *rblk     =  NULL ;
RadiationData_t *rblkbak  =  NULL ;
RadiationData_t *cblk  =  NULL ;
RadiationData_t *pblk  =  NULL ;


/*******************************************************************************
* END OF FILE
*******************************************************************************/
