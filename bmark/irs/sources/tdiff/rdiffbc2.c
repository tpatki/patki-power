#include "irs.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rdiffbc2( RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain )
{
   char *me = "rdiffbc2";
   int i, ibc, n, stride ;
   int *ndx ;
   double *cc, *cbcc, *cbch, *cbcl, *cbll, *cblh, *pbcc, *pbch, *pbcl, *rhsbc;
   double myflops = 1;
   FT_INITIALIZE(me, domain->hash)
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
      n      = domain->bc[ibc].len ;
      ndx    = domain->bc[ibc].ndx ;
      stride = domain->bc[ibc].pn  ;
      if ( domain->bc[ibc].rtype == OPEN ) {
         if ( stride == -1 ) {
            cc    = rblk->ccc           ;
            cbcl  = rblk->cbl           ;
            cbcc  = rblk->ccl           ;
            cbch  = rblk->cbr + domain->jp - 1 ;
            cbll  = rblk->cbr       - 1 ;
            cblh  = rblk->cbl + domain->jp     ;
            pbcl  = tblk->phi - domain->jp - 1 ;
            pbcc  = tblk->phi       - 1 ;
            pbch  = tblk->phi + domain->jp - 1 ;
            rhsbc = tblk->rhs           ;
         }
         if ( stride == 1 ) {
            cc    = rblk->ccc       - 1 ;
            cbcl  = rblk->cbr       - 1 ;
            cbcc  = rblk->ccl           ;
            cbch  = rblk->cbl + domain->jp     ;
            cbll  = rblk->cbl           ;
            cblh  = rblk->cbr + domain->jp - 1 ;
            pbcl  = tblk->phi - domain->jp     ;
            pbcc  = tblk->phi           ;
            pbch  = tblk->phi + domain->jp     ;
            rhsbc = tblk->rhs       - 1 ;
         }
         if ( stride == -domain->jp ) {
            cc    = rblk->ccc           ;
            cbcl  = rblk->cbl           ;
            cbcc  = rblk->cbc           ;
            cbch  = rblk->cbr           ;
            cbll  = rblk->cbr       - 1 ;
            cblh  = rblk->cbl       + 1 ;
            pbcl  = tblk->phi - domain->jp - 1 ;
            pbcc  = tblk->phi - domain->jp     ;
            pbch  = tblk->phi - domain->jp + 1 ;
            rhsbc = tblk->rhs           ;
         }
         if ( stride ==  domain->jp ) {
            cc    = rblk->ccc - domain->jp     ;
            cbcl  = rblk->cbr       - 1 ;
            cbcc  = rblk->cbc           ;
            cbch  = rblk->cbl       + 1 ;
            cbll  = rblk->cbl           ;
            cblh  = rblk->cbr           ;
            pbcl  = tblk->phi       - 1 ;
            pbcc  = tblk->phi           ;
            pbch  = tblk->phi       + 1 ;
            rhsbc = tblk->rhs - domain->jp     ;
         }
         for ( i = 0 ; i < n ; i++ ) {
            rhsbc[ndx[i]] -= cbcc[ndx[i]] * pbcc[ndx[i]] +
                             cbcl[ndx[i]] * pbcl[ndx[i]] +
                             cbch[ndx[i]] * pbch[ndx[i]] ;
            cc[ndx[i]]    -= cbcc[ndx[i]] +
                             cbcl[ndx[i]] +
                             cbch[ndx[i]] ;
         }
	 myflops += 9.0 * n ;
         for ( i = 0 ; i < n ; i++ ) {
            cbcl[ndx[i]] = 0.0 ;
            cbcc[ndx[i]] = 0.0 ;
            cbch[ndx[i]] = 0.0 ;
            cbll[ndx[i]] = 0.0 ;
            cblh[ndx[i]] = 0.0 ;
         }
      }
      if ( (domain->bc[ibc].rtype == CLOSED) || (domain->bc[ibc].rtype == POLE) ) {
         if ( stride == -1 ) {
            cbcl  = rblk->cbl           ;
            cbcc  = rblk->ccl           ;
            cbch  = rblk->cbr + domain->jp - 1 ;
            cbll  = rblk->cbr       - 1 ;
            cblh  = rblk->cbl + domain->jp     ;
         }
         if ( stride == 1 ) {
            cbcl  = rblk->cbr       - 1 ;
            cbcc  = rblk->ccl           ;
            cbch  = rblk->cbl + domain->jp     ;
            cbll  = rblk->cbl           ;
            cblh  = rblk->cbr + domain->jp - 1 ;
         }
         if ( stride == -domain->jp ) {
            cbcl  = rblk->cbl           ;
            cbcc  = rblk->cbc           ;
            cbch  = rblk->cbr           ;
            cbll  = rblk->cbr       - 1 ;
            cblh  = rblk->cbl       + 1 ;
         }
         if ( stride ==  domain->jp ) {
            cbcl  = rblk->cbr       - 1 ;
            cbcc  = rblk->cbc           ;
            cbch  = rblk->cbl       + 1 ;
            cbll  = rblk->cbl           ;
            cblh  = rblk->cbr           ;
         }
         for ( i = 0 ; i < n ; i++ ) {
            cbcl[ndx[i]] = 0.0 ;
            cbcc[ndx[i]] = 0.0 ;
            cbch[ndx[i]] = 0.0 ;
            cbll[ndx[i]] = 0.0 ;
            cblh[ndx[i]] = 0.0 ;
         }
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
