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

int update(double dt, int ifcalcdt);
int xirs(int ncycle, double ntime);
void CalcDtSource(Domain_t *domain);
void CalcDtTemp(Domain_t *domain);
void DtTempInitialize(void);
void HydroDtControls(Domain_t *domain);
void InitCycle(void);
void LengthScale(Domain_t *domain, double *x, double *y, double *z, double *length);
void PostSubcycle(double timestep, double sub_timestep);
void PreSubcycle(void);
void getnm2d0(double *nmass, Domain_t *domain);
void getnm3d(double *nmass, Domain_t *domain);
void updateblk(Domain_t *domain, int ifcalcdt, double dt);


#endif
/*******************************************************************************
* GLOBAL VARS
*******************************************************************************/

int ndtg  ;
int ndtgx ;
int subcycle ;
int maxsubcycles ;
int sourcesubcycle ;
double dtg ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
