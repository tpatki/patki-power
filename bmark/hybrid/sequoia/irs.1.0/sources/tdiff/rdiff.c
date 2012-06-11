#include "irs.h"
#include "irscom.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
#include "Source.h"
void rdiff( RadiationData_t *rblk, RadiationData_t *cblk, 
	    DiffusionData_t *tblk, Domain_t *domains,
            double dtrad, double radtime, double depositionFraction )
{
   char *me = "rdiff";
   int iblk, comerr ;
   int my_nblk = nblk ;
   double myflops = 0.0;
   FT_INITIALIZE(me, gv_hash_tbl)
   comerr = 0 ;
   radinit( tblk ) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      rdiffsrc( &tblk[iblk], &domains[iblk], radtime ) ;
      SourceNew_radtemperature(tblk[iblk].phi, domains[iblk].trad, 
                               domains[iblk].den, "SourceRadiationTemperature",
                               radtime, &domains[iblk], _SourceEdit_);
   }
   comerr += rbndcom(RBNDCOM3,COM_RECV,0);
   comerr += rbndcom(RBNDCOM3,COM_SEND,0);
   comerr += rbndcom(RBNDCOM3,COM_WAIT_RECV,0);
   comerr += rbndcom(RBNDCOM3,COM_WAIT_SEND,0);
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
 ; 
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      rdiffset( &domains[iblk], dtrad ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     double umin = tfloor * tfloor * tfloor * tfloor ;
     double fscl = 1.0 / ( rflx + ptiny ) ;
     FluxLimiterDriver( domains[iblk].x, domains[iblk].y, domains[iblk].z,
		        tblk[iblk].phi, tblk[iblk].flmt, fscl, umin,
		        &domains[iblk] ) ;
   }
   comerr += rbndcom(RBNDCOM4,COM_RECV,0);
   comerr += rbndcom(RBNDCOM4,COM_SEND,0);
   comerr += rbndcom(RBNDCOM4,COM_WAIT_RECV,0);
   comerr += rbndcom(RBNDCOM4,COM_WAIT_SEND,0);
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      DiffCoef( &rblk[iblk], &tblk[iblk], &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      diagonal( &rblk[iblk], &tblk[iblk], &domains[iblk], dtrad,
                depositionFraction ) ;
   }
   MatrixSolveDriver( rblk, cblk, tblk, domains, &rdifit, &rdifeps ) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      retransfer( dtrad, depositionFraction, &tblk[iblk], &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      setpz1( domains[iblk].trad, 0.0, &domains[iblk] ) ;
      setpz2( domains[iblk].trad, 0.0, &domains[iblk] ) ;
      setpz1( domains[iblk].erad, 0.0, &domains[iblk] ) ;
      setpz2( domains[iblk].erad, 0.0, &domains[iblk] ) ;
   }
   FT_FINALIZE(me, gv_hash_tbl, myflops)
}
