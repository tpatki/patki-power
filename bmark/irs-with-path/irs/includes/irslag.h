#ifndef IRSLAG_H
#define IRSLAG_H

#include "State.h"
#include "Domain.h"

/*******************************************************************************
* DEFINES
*******************************************************************************/

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/

extern int update(double dt, int ifcalcdt);
extern int xirs(int ncycle, double ntime);
extern void CalcDtSource(Domain_t *domain);
extern void CalcDtTemp(Domain_t *domain);
extern void DtTempInitialize(void);
extern void HydroDtControls(Domain_t *domain);
extern void InitCycle(void);
extern void LengthScale(Domain_t *domain, double *x, double *y, double *z, double *length);
extern void PostSubcycle(double timestep, double sub_timestep);
extern void PreSubcycle(void);
extern void getnm2d0(double *nmass, Domain_t *domain);
extern void getnm3d(double *nmass, Domain_t *domain);
extern void updateblk(Domain_t *domain, int ifcalcdt, double dt);


#endif
/*******************************************************************************
* GLOBAL VARS
*******************************************************************************/

extern int ndtg  ;
extern int ndtgx ;
extern int subcycle ;
extern int maxsubcycles ;
extern int sourcesubcycle ;
extern double dtg ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
