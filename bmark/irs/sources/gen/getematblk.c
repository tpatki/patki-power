#include "irs.h"
#include "irsreg.h"
#include "irsgen.h"
#include "irseos.h"
#include "irstdiff.h"
void getematblk( int flag, Domain_t *domain )
{
   double *den    = domain->den    ;
   double *emat   = domain->emat   ;
   double *eion   = domain->eion   ;
   double *e_cold = domain->e_cold ;
   double *tmat   = domain->tmat   ;
   double *tion   = domain->tion   ;
   double *dedt   = domain->dedt   ;
   double *deidt  = domain->deidt  ;
   RegionTableAllocate( domain, reg, nreg ) ;
   RegionTableInitialize( domain, reg, nreg, domain->specfrac ) ;
   getemat( emat, eion, e_cold, dedt, deidt, den, tmat, tion, deltat,
	    flag, domain ) ;
   RegionTableFree(domain, reg, nreg) ;
}
