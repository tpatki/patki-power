#ifndef IRSREG_H
#define IRSREG_H

#include "Region.h"

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/

int OpacTypesIn_Kp(int number, int form);
int OpacTypesIn_Kr(int number, int form);

int eos_init(int ifgen);
int eosin(void);
int eosin0(int number, int form);
int maxmin(void);
int opacin(void);
void regcnst(int ir, double region_value, double *za, Domain_t *domain);
void regndx(Domain_t *domain);

#endif

/*******************************************************************************
* GLOBALS
*******************************************************************************/
int nspecies;	/* declared in species.c  Also used Species.c */

        /*----------------------------------------------------------------------
        - region parms 
        ----------------------------------------------------------------------*/
int nreg ;
int nregplus1 ;
int nregx ;
int nregxplus1 ;
int ngroupx ;
int current_region  =  0 ;
int current_eos  =  0 ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/

