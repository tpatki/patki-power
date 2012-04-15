#include "irs.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void rdiffbc3( RadiationData_t *rblk,   DiffusionData_t *tblk,   Domain_t *domain )
{
  char *me = "rdiffbc3";
  int i, ibc, n, stride ;
  int *ndx ;
  int *zonelist;
  double *cbclc, *cbccl, *cbccc, *cbcch, *cbchc, *cbdlc, *cbdcl, *cbdch, *cbdhc;
  double *cc  = rblk->ccc;
  double *rhs = tblk->rhs;
  double *dbl = rblk->dbl;
  double *dbc = rblk->dbc;
  double *dbr = rblk->dbr;
  double *dcl = rblk->dcl;
  double *dcc = rblk->dcc;
  double *dcr = rblk->dcr;
  double *dfl = rblk->dfl;
  double *dfc = rblk->dfc;
  double *dfr = rblk->dfr;
  double *cbl = rblk->cbl;
  double *cbc = rblk->cbc;
  double *cbr = rblk->cbr;
  double *ccl = rblk->ccl;
  double *ccc = rblk->ccc;
  double *ccr = ccl + 1 ;
  double *cfl = cbr + domain->jp - 1 ;   
  double *cfc = cbc + domain->jp ;   
  double *cfr = cbl + domain->jp + 1 ;   
  double *ubl = dfr + domain->kp - domain->jp - 1 ;
  double *ubc = dfc + domain->kp - domain->jp ;
  double *ubr = dfl + domain->kp - domain->jp + 1 ;
  double *ucl = dcr + domain->kp - 1 ;
  double *ucc = dcc + domain->kp ;
  double *ucr = dcl + domain->kp + 1 ;
  double *ufl = dbr + domain->kp + domain->jp - 1 ;
  double *ufc = dbc + domain->kp + domain->jp ;
  double *ufr = dbl + domain->kp + domain->jp + 1 ;
  double phiBoundary = tfloor*tfloor;
  double myflops = 1;
  FT_INITIALIZE(me, domain->hash)
  phiBoundary = phiBoundary * phiBoundary;
  for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
    n           = domain->bc[ibc].lenZonelist ;
    zonelist    = domain->bc[ibc].zonelist ;
    stride      = domain->bc[ibc].pn  ;
    if ( stride == -1 ) {
      cbclc = ubl;
      cbccl = ucl;
      cbccc = ufl;
      cbcch = cbl;
      cbchc = ccl;
      cbdlc = cfl;
      cbdcl = dbl;
      cbdch = dcl;
      cbdhc = dfl;
    }
    if ( stride == 1 ) { 
      cbclc = ubr ;
      cbccl = ucr ;
      cbccc = ufr ;
      cbcch = cbr ;
      cbchc = ccr ;
      cbdlc = cfr ;
      cbdcl = dbr ;
      cbdch = dcr ;
      cbdhc = dfr ;
    }
    if ( stride == -domain->jp ) {
      cbclc = ubl;
      cbccl = ubc;
      cbccc = ubr;
      cbcch = cbl;
      cbchc = cbc;
      cbdlc = cbr;
      cbdcl = dbl;
      cbdch = dbc;
      cbdhc = dbr;
    }
    if ( stride == domain->jp ) {
      cbclc = ufl ;
      cbccl = ufc ;
      cbccc = ufr ;
      cbcch = cfl ;
      cbchc = cfc ;
      cbdlc = cfr ;
      cbdcl = dfl ;
      cbdch = dfc ;
      cbdhc = dfr ;
    }
    if ( stride == -domain->kp ) {
      cbclc = dbl;                 ;
      cbccl = dbc;
      cbccc = dbr;
      cbcch = dcl;
      cbchc = dcc;
      cbdlc = dcr;
      cbdcl = dfl;
      cbdch = dfc;
      cbdhc = dfr;
    }
    if ( stride == domain->kp ) {
      cbclc = ubl ;
      cbccl = ubc ;
      cbccc = ubr ;
      cbcch = ucl ;
      cbchc = ucc ;
      cbdlc = ucr ;
      cbdcl = ufl ;
      cbdch = ufc ;
      cbdhc = ufr ;
    }
    if ( domain->bc[ibc].rtype == OPEN ) {
      for ( i = 0 ; i < n ; i++ ) {
	double correction = cbclc[zonelist[i]] + 
	  cbccl[zonelist[i]] + cbccc[zonelist[i]] +
	    cbcch[zonelist[i]] + cbchc[zonelist[i]] +
	      cbdlc[zonelist[i]] + cbdcl[zonelist[i]] + 
		cbdch[zonelist[i]] + cbdhc[zonelist[i]] ;
	rhs[zonelist[i]] -= phiBoundary * correction;
	cc[zonelist[i]]    -=  correction;
      }
      myflops += 11.0 * n ;
    }	 
    for ( i = 0 ; i < n ; i++ ) {
      cbclc[zonelist[i]] = 0.0 ;
      cbccl[zonelist[i]] = 0.0 ;
      cbccc[zonelist[i]] = 0.0 ;
      cbcch[zonelist[i]] = 0.0 ;
      cbchc[zonelist[i]] = 0.0 ;
      cbdlc[zonelist[i]] = 0.0 ;
      cbdcl[zonelist[i]] = 0.0 ;
      cbdch[zonelist[i]] = 0.0 ;
      cbdhc[zonelist[i]] = 0.0 ;
    }
  }
   FT_FINALIZE(me, domain->hash, myflops)
}
