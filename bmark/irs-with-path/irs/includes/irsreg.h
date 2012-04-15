#ifndef IRSREG_H
#define IRSREG_H

#include "Region.h"

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/

extern int OpacTypesIn_Kp(int number, int form);
extern int OpacTypesIn_Kr(int number, int form);

extern int eos_init(int ifgen);
extern int eosin(void);
extern int eosin0(int number, int form);
extern int maxmin(void);
extern int opacin(void);
extern void regcnst(int ir, double region_value, double *za, Domain_t *domain);
extern void regndx(Domain_t *domain);

#endif

/*******************************************************************************
* GLOBALS
*******************************************************************************/
extern int nspecies;	/* declared in species.c  Also used Species.c */

        /*----------------------------------------------------------------------
        - region parms 
        ----------------------------------------------------------------------*/
extern int nreg ;
extern int nregplus1 ;
extern int nregx ;
extern int nregxplus1 ;
extern int ngroupx ;
extern int current_region ;              /* HH_INIT 0 */
extern int current_eos ;                 /* HH_INIT 0 */

/*******************************************************************************
* END OF FILE
*******************************************************************************/

