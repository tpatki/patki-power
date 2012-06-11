#ifndef DiffusionData_H
#define DiffusionData_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

  double *phi    ;
  double *dphi   ;
  double *adphi  ;
  double *rhs    ;
  double *esrc   ;
  double *flmt   ;
  double *phim   ;
  double *xplnk  ;
  double *kie    ;
  double *alpha  ;
  double *beta   ;
  double *gamma  ;
  double *rcm3t  ;
  double *diffcl ;
  double *diffcr ;
  double *diffcb ;
  double *diffcf ;
  double *diffcd ;
  double *diffcu ;

} DiffusionData_t ;

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/* tdiff Radiation flux/data structures */

extern DiffusionData_t *tblk ;


/*******************************************************************************
* END OF FILE
*******************************************************************************/
