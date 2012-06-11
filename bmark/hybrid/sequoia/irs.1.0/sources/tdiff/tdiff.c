#include "irs.h"
#include "irsgen.h"
#include "irsbndry.h"
#include "irscom.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "SpeciesFraction.h"
void tdiff( double dtrad, double radtime, double depositionFraction )
{
   char *me = "tdiff";
   char *bufname = "RBNDCOM";
   int comerr = 0;
   int iblk ;
   int my_nblk = nblk ;
   double fraction ;
   double myflops = 0.0;
   FT_INITIALIZE(me, gv_hash_tbl) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     ChemPotCalc( domains[iblk].den, domains[iblk].tmat, &domains[iblk] ) ;
   }
      RadiationAllocate( &rblk, &rblkbak, &cblk, &tblk, (ifedif + ifidif) ) ;
      comerr += rbndcom(RBNDCOM2,COM_RECV,0);
      comerr += rbndcom(RBNDCOM2,COM_SEND,0);
      comerr += rbndcom(RBNDCOM2,COM_WAIT_RECV,0);
      comerr += rbndcom(RBNDCOM2,COM_WAIT_SEND,0);
      if ( ndims == 2 ) {
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
  	    volcal2d( domains[iblk].vol, domains[iblk].area,
		      domains[iblk].x  , domains[iblk].y,
		      &domains[iblk] ) ;
	 }
      }
      if ( ndims == 3 ) {
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
	    volcal3d( domains[iblk].vol, domains[iblk].x, domains[iblk].y,
		      domains[iblk].z, &domains[iblk] ) ;
	 }
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
	 int length = domains[iblk].namix ;
         DivgradDriver( domains[iblk].x, domains[iblk].y, domains[iblk].z,
		        &domains[iblk], &rblk[iblk] ) ;
         if ( (ifedif + ifidif) > 0 ) {
 	    CopyMatrix( &rblkbak[iblk], &rblk[iblk], length, ndims ) ;
	 }
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         refzq( domains[iblk].vol, &domains[iblk] ) ;
      }
      if ( (ifidif > 0) && (iftion == 1) ) {
         tblkinit( tblk ) ;
         IonConduction( rblk, cblk, tblk, domains, dtrad, radtime ) ;
#include "pardo.h"
         for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
            CopyMatrix( &rblk[iblk], &rblkbak[iblk], 
                        domains[iblk].namix, ndims ) ;
	 }
      }
      if ( ifedif > 0 ) {
         tblkinit( tblk ) ;
         ElectronConduction( rblk, cblk, tblk, domains, dtrad, radtime ) ;
#include "pardo.h"
	 for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
            CopyMatrix( &rblk[iblk], &rblkbak[iblk], 
                        domains[iblk].namix, ndims ) ;
	 }
      }
      if ( ngroup == 1 ) {
         tblkinit( tblk ) ;
         rdiff( rblk, cblk, tblk, domains, dtrad, radtime, depositionFraction ) ;
      }
      RadiationFree( rblk, rblkbak, cblk, tblk, (ifedif + ifidif) ) ;
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         setpz1( domains[iblk].vol, 0.0, &domains[iblk] ) ;
         setpz2( domains[iblk].vol, 0.0, &domains[iblk] ) ;
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         setpz1( domains[iblk].den, 0.0, &domains[iblk] ) ;
         setpz2( domains[iblk].den, 0.0, &domains[iblk] ) ;
      }
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         int i;
         int n;
         int *ndx;
         n   = domains[iblk].rlen[0] ;
         ndx = domains[iblk].rndx[0] ;
         for ( i = 0 ; i < n ; i++ )  {
            domains[iblk].ireg[ndx[i]] = 0 ;
         }
      }
   FT_FINALIZE(me, gv_hash_tbl, myflops) ;
}
