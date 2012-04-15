#ifndef State_H
#define State_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

  double  timeStep ;
  double  currentTime ;

  /* nodal positions */
  double *x ;
  double *y ;
  double *z ;

  /* nodal velocities */
  double *xdot ;
  double *ydot ;
  double *zdot ;

  /* scalar fields */
  double *den  ;
  double *emat ;
  double *eion ;
  double *erad ;
  double *tmat ;
  double *tion ;
  double *trad ;

  /* zonal strength */
  double *sxx ;
  double *sxy ;
  double *sxz ;
  double *syy ;
  double *syz ;
  double *szz ;

  double *eps ;

} State_t ;

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
