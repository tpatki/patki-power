#include "irs.h"
#include "irstdiff.h"
#include "irscom.h"
#include "DiffusionData.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void ElectronConduction( RadiationData_t *rblk, RadiationData_t *cblk,
                         DiffusionData_t *tblk, Domain_t *domains,
			 double dtrad, double radtime )
{
   char *me = "ElectronConduction" ;
   int i, iblk, comerr ;
   int my_nblk = nblk ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, gv_hash_tbl)
   comerr = 0 ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     CopyArrayDouble( tblk[iblk].phi, domains[iblk].tmat, domains[iblk].namix ) ;
   }
   comerr += rbndcom(RBNDCOM3,COM_RECV,0) ;
   comerr += rbndcom(RBNDCOM3,COM_SEND,0) ;
   comerr += rbndcom(RBNDCOM3,COM_WAIT_RECV,0) ;
   comerr += rbndcom(RBNDCOM3,COM_WAIT_SEND,0) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
 ; 
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int iStride = 1                   ;
      int jStride = domains[iblk].jp    ;
      double *t52 = MALLOT( double, domains[iblk].namix ) ;
      double *kl  = tblk[iblk].diffcl ;
      double *kr  = tblk[iblk].diffcr ;
      double *kf  = tblk[iblk].diffcf ;
      double *kb  = tblk[iblk].diffcb ;
      MatterWainwright( t52, tblk[iblk].phi,  iStride, &domains[iblk] ) ;
      ElectronConductionCoef( kl, t52, &domains[iblk] ) ;
      MatterWainwright( t52, tblk[iblk].phi, -iStride, &domains[iblk] ) ;
      ElectronConductionCoef( kr, t52, &domains[iblk] ) ;
      MatterWainwright( t52, tblk[iblk].phi,  jStride, &domains[iblk] ) ;
      ElectronConductionCoef( kb, t52, &domains[iblk] ) ;
      MatterWainwright( t52, tblk[iblk].phi, -jStride, &domains[iblk] ) ;
      ElectronConductionCoef( kf, t52, &domains[iblk] ) ;
      FREEMEM(t52) ;
   }
   if ( ndims == 3 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         int kStride = domains[iblk].kp ;
         double *t52 = MALLOT( double, domains[iblk].namix ) ;
         double *kd  = tblk[iblk].diffcd ;
         double *ku  = tblk[iblk].diffcu ;
         MatterWainwright( t52, tblk[iblk].phi,  kStride, &domains[iblk] ) ;
         ElectronConductionCoef( kd, t52, &domains[iblk] ) ;
         MatterWainwright( t52, tblk[iblk].phi, -kStride, &domains[iblk] ) ;
         ElectronConductionCoef( ku, t52, &domains[iblk] ) ;
         FREEMEM(t52) ;
      }
   }
   comerr += rbndcom(RBNDCOM4,COM_RECV,0) ;
   comerr += rbndcom(RBNDCOM4,COM_SEND,0) ;
   comerr += rbndcom(RBNDCOM4,COM_WAIT_RECV,0) ;
   comerr += rbndcom(RBNDCOM4,COM_WAIT_SEND,0) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      DiffCoef( &rblk[iblk], &tblk[iblk], &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     MatterDiagonal( &rblk[iblk], &tblk[iblk], domains[iblk].dedt,
		     &domains[iblk], dtrad ) ;
   }
   MatrixSolveDriver( rblk, cblk, tblk, domains, &edifit, &rdifeps ) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     MatterUpdateTemperature( dtrad, tblk[iblk].phi, tblk[iblk].diffcl,
			      domains[iblk].emat, domains[iblk].tmat,
			      domains[iblk].dedt, &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      setpz1( domains[iblk].tmat, 0.0, &domains[iblk] ) ;
      setpz2( domains[iblk].tmat, 0.0, &domains[iblk] ) ;
   }
   FT_FINALIZE(me, gv_hash_tbl, myflops)
}
void IonConduction( RadiationData_t *rblk, RadiationData_t *cblk,
                    DiffusionData_t *tblk, Domain_t *domains,
		    double dtrad, double radtime )
{
   char *me = "IonConduction" ;
   int i, iblk, comerr ;
   int my_nblk = nblk ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, gv_hash_tbl)
   comerr = 0 ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     CopyArrayDouble( tblk[iblk].phi, domains[iblk].tion, domains[iblk].namix ) ;
   }
   comerr += rbndcom(RBNDCOM3,COM_RECV,0) ;
   comerr += rbndcom(RBNDCOM3,COM_SEND,0) ;
   comerr += rbndcom(RBNDCOM3,COM_WAIT_RECV,0) ;
   comerr += rbndcom(RBNDCOM3,COM_WAIT_SEND,0) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
 ; 
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      int iStride = 1                   ;
      int jStride = domains[iblk].jp    ;
      double *t52 = MALLOT( double, domains[iblk].namix ) ;
      double *kl  = tblk[iblk].diffcl ;
      double *kr  = tblk[iblk].diffcr ;
      double *kf  = tblk[iblk].diffcf ;
      double *kb  = tblk[iblk].diffcb ;
      MatterWainwright( t52, tblk[iblk].phi,  iStride, &domains[iblk] ) ;
      IonConductionCoef( kl, t52, &domains[iblk] ) ;
      MatterWainwright( t52, tblk[iblk].phi, -iStride, &domains[iblk] ) ;
      IonConductionCoef( kr, t52, &domains[iblk] ) ;
      MatterWainwright( t52, tblk[iblk].phi,  jStride, &domains[iblk] ) ;
      IonConductionCoef( kb, t52, &domains[iblk] ) ;
      MatterWainwright( t52, tblk[iblk].phi, -jStride, &domains[iblk] ) ;
      IonConductionCoef( kf, t52, &domains[iblk] ) ;
      FREEMEM(t52) ;
   }
   if ( ndims == 3 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         int kStride = domains[iblk].kp ;
         double *t52 = MALLOT( double, domains[iblk].namix ) ;
         double *kd  = tblk[iblk].diffcd ;
         double *ku  = tblk[iblk].diffcu ;
         MatterWainwright( t52, tblk[iblk].phi,  kStride, &domains[iblk] ) ;
         IonConductionCoef( kd, t52, &domains[iblk] ) ;
         MatterWainwright( t52, tblk[iblk].phi, -kStride, &domains[iblk] ) ;
         IonConductionCoef( ku, t52, &domains[iblk] ) ;
         FREEMEM(t52) ;
      }
   }
   comerr += rbndcom(RBNDCOM4,COM_RECV,0) ;
   comerr += rbndcom(RBNDCOM4,COM_SEND,0) ;
   comerr += rbndcom(RBNDCOM4,COM_WAIT_RECV,0) ;
   comerr += rbndcom(RBNDCOM4,COM_WAIT_SEND,0) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      DiffCoef( &rblk[iblk], &tblk[iblk], &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     MatterDiagonal( &rblk[iblk], &tblk[iblk], domains[iblk].deidt,
		     &domains[iblk], dtrad ) ;
   }
   MatrixSolveDriver( rblk, cblk, tblk, domains, &idifit, &rdifeps ) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     MatterUpdateTemperature( dtrad, tblk[iblk].phi, tblk[iblk].diffcl,
			      domains[iblk].eion, domains[iblk].tion,
			      domains[iblk].deidt, &domains[iblk] ) ;
   }
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      setpz1( domains[iblk].tion, 0.0, &domains[iblk] ) ;
      setpz2( domains[iblk].tion, 0.0, &domains[iblk] ) ;
   }
   FT_FINALIZE(me, gv_hash_tbl, myflops)
}
void CopyArrayDouble( double *copyArray, double *array, int length )
{
   int i ;
   for ( i = 0 ; i < length ; i++ ) {
      copyArray[i] = array[i] ;
   }
}
