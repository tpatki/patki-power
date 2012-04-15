#ifndef IRSEOS_H
#define IRSEOS_H

#include "Region.h"

/*******************************************************************************
* DEFINES
*******************************************************************************/

#define T0     coef[31]

#define THERMO_NULL(eos)   \
   eos.p       = NULL ;     \
   eos.dpdr    = NULL ;     \
   eos.dpde    = NULL ;     \
   eos.dpdt    = NULL ;     \
   eos.pion    = NULL ;     \
   eos.dpidr   = NULL ;     \
   eos.dpidei  = NULL ;     \
   eos.dpidti  = NULL ;     \
   eos.dtdr    = NULL ;     \
   eos.dtde    = NULL ;     \
   eos.dtidr   = NULL ;     \
   eos.dtidei  = NULL ;     \
   eos.dtedei  = NULL ;     \
   eos.drdp    = NULL ;     \
   eos.drde    = NULL ;     \
   eos.drdt    = NULL ;     \
   eos.drdti   = NULL ;     \
   eos.dedp    = NULL ;     \
   eos.dedr    = NULL ;     \
   eos.dedt    = NULL ;     \
   eos.dedti   = NULL ;     \
   eos.dedt_v  = NULL ;     \
   eos.deidp   = NULL ;     \
   eos.deidr   = NULL ;     \
   eos.deidti  = NULL ;     \
   eos.deidte  = NULL ;     \
   eos.deidt_v = NULL ;     \
   eos.den     = NULL ;     \
   eos.emat    = NULL ;     \
   eos.tmat    = NULL ;     \
   eos.eion    = NULL ;     \
   eos.tion    = NULL ;     \
   eos.p_cold  = NULL ;     \
   eos.e_cold  = NULL ;     \
   eos.cs      = NULL ;     \
   eos.cs2     = NULL ;     \
   eos.work3   = NULL ;     \
   eos.work1   = NULL ;     \
   eos.work2   = NULL ;     \
   eos.abar    = NULL ;     \
   eos.zbar    = NULL ;     \
   eos.zstar   = NULL ;     \
   eos.tdedte  = NULL ;     \
   eos.tdedti  = NULL ;     \
   eos.tdedp   = NULL ;     \
   eos.tdeidte = NULL ;     \
   eos.tdeidti = NULL ;     \
   eos.tdeidp  = NULL ;     \
   eos.tdrdte  = NULL ;     \
   eos.tdrdti  = NULL ;     \
   eos.tdrdp   = NULL ;     \
   eos.dtlast  = NULL ;     \
   eos.delast  = NULL ;     \
   eos.deilast = NULL ;     \
   eos.drlast  = NULL ;


/*******************************************************************************
* PROTOTYPES
*******************************************************************************/


#include "Thermo.h"
#include "SpeciesFraction.h"

extern void DensityEnergyMin(double *den, double *emat, double *eion, int *ndx, int len, double DensityMin, double EnergyMin, Domain_t *domain);
extern void EosDriver(double eostime, double eosdeltat);
extern void calc_dtdr_form(double *cdtdr, double *cecold, double *cmu, double *cmu_m, double rho0, double dtdex, double etamax, double etamin, int n, int ir, int ieos, double *pflops);
extern void eosfm5(Thermo_t deos, int *ndx, int n, double rho0, double etamin, double etamax, double *coef, int ir, int ieos, int multieos, Domain_t *domain);
extern void etaminchk(double *den, double *p, double *cs2, int *ndx, int n, double rho0, double etamin, Domain_t *domain);
extern void getemat(double *emat, double *eion, double *e_cold, double *dedt, double *deidt, double *den, double *tmat, double *tion, double timestep, int ifgen, Domain_t *domain);
extern void getematnomix(double *emat, double *eion, double *e_cold, double *dedt, double *deidt, double *den, double *tmat, double *tion, double *abar, double *zbar, int *ndx, int len, int ifgen, Domain_t *domain, int ir, int ieos);
extern void geteos(double *p, double *pion, double *p_cold, double *cs2, double *dedt, double *deidt, double *den, double *emat, double *eion, double *e_cold, double *tmat, double *tion, double *work3, double *work1, double *work2, double teos, double dt, Domain_t *domain, SpeciesFraction_t *specfrac, int ifsource, int ifzstar);
extern void geteosnomix(Thermo_t deos, Thermo_t weos, double *fe, double *fi, double *csave, int *wcnvg, double teos, double dt, Domain_t *domain, int ir, int multieos, SpeciesFraction_t *specfrac);
extern void geteosx(Thermo_t ceos, Thermo_t weos, double *fe, double *fi, double *csave, int *wcnvg, double teos, double dt, int *ndx, int len, int ir, int ieos, DATABASETYPE_t dbeos, Domain_t *domain, SpeciesFraction_t *specfrac);
extern void pminchk(double *p, double *pion, double *p_cold, double *cs2, int *ndx, int n, double pmin, int pminmd, int ir, Domain_t *domain);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

extern double c2fail ; /* HH_INIT 1.0 */

extern int if_eos_mix_zeq ;

/*******************************************************************************
* END OF FILE
*******************************************************************************/
