#include "irsdefs.h"
#include "irs.h"
#include "irstdiff.h"
#include "DiffusionData.h"
#include "ProblemArray.h"
#include "RadiationData.hh"
void RadiationAllocate( RadiationData_t **rblk, RadiationData_t **rblkbak,
                        RadiationData_t **cblk, DiffusionData_t **tblk,
			int needRblkBak)
{
   int iblk ;
   int my_nblk = nblk ;
   RadiationData_t *rblklocal, *rblkbaklocal, *cblklocal ;
   DiffusionData_t *tblklocal ;
   rblklocal = ALLOT( RadiationData_t, nblk ) ;
   for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
      rblklocal[iblk] = newMatrix( domains[iblk].namix, ndims,
	 		           domains[iblk].jp, domains[iblk].kp ) ;
   }
   if ( needRblkBak > 0 ) {
      rblkbaklocal = ALLOT( RadiationData_t, nblk ) ;
      for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
         rblkbaklocal[iblk] = newMatrix( domains[iblk].namix, ndims,
                                         domains[iblk].jp, domains[iblk].kp ) ;
      }
      *rblkbak = rblkbaklocal ;
   }
   if ( solver != 1 ) {
      cblklocal = ALLOT( RadiationData_t, nblk ) ;
      for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
         cblklocal[iblk] = newMatrix( domains[iblk].namix, ndims, 
			              domains[iblk].jp, domains[iblk].kp) ;
      }
      *cblk    = cblklocal ;
   }
   tblklocal = ALLOT( DiffusionData_t, nblk ) ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     int len = domains[iblk].namix;
      tblklocal[iblk].phi    = MALLOT(double,len) ;
      tblklocal[iblk].dphi   = MALLOT(double,len) ;
      tblklocal[iblk].adphi  = MALLOT(double,len) ;
      tblklocal[iblk].rhs    = MALLOT(double,len) ;
      tblklocal[iblk].esrc   = MALLOT(double,len) ;
      tblklocal[iblk].flmt   = MALLOT(double,len) ;
      tblklocal[iblk].phim   = MALLOT(double,len) ;
      tblklocal[iblk].xplnk  = MALLOT(double,len) ;
      tblklocal[iblk].alpha  = MALLOT(double,len) ;
      tblklocal[iblk].diffcl = MALLOT(double,len) ;
      tblklocal[iblk].diffcr = MALLOT(double,len) ;
      tblklocal[iblk].diffcb = MALLOT(double,len) ;
      tblklocal[iblk].diffcf = MALLOT(double,len) ;
      ProblemArray_add("phi",   tblklocal[iblk].phi, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("dphi",  tblklocal[iblk].dphi, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("adphi", tblklocal[iblk].adphi, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("rhs",   tblklocal[iblk].rhs, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("esrc",  tblklocal[iblk].esrc, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("flmt",  tblklocal[iblk].flmt, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("phim",  tblklocal[iblk].phim, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("xplnk", tblklocal[iblk].xplnk, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("alpha", tblklocal[iblk].alpha, len, 
		       R_DOUBLE , domains[iblk].hash);
      ProblemArray_add("diffCoefL", tblklocal[iblk].diffcl, len,
		       R_DOUBLE,  domains[iblk].hash);
      ProblemArray_add("diffCoefR", tblklocal[iblk].diffcr, len,
		       R_DOUBLE,  domains[iblk].hash);
      ProblemArray_add("diffCoefB", tblklocal[iblk].diffcb, len,
		       R_DOUBLE,  domains[iblk].hash);
      ProblemArray_add("diffCoefF", tblklocal[iblk].diffcf, len,
		       R_DOUBLE,  domains[iblk].hash);
   }
   if ( iftion == 1 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
	int len = domains[iblk].namix;
	tblklocal[iblk].kie   = MALLOT(double, len);
	tblklocal[iblk].beta  = MALLOT(double, len);
	tblklocal[iblk].gamma = MALLOT(double, len);
	tblklocal[iblk].rcm3t = MALLOT(double, len);
	ProblemArray_add("kie", tblklocal[iblk].kie, len,
			 R_DOUBLE, domains[iblk].hash);
	ProblemArray_add("beta", tblklocal[iblk].beta, len,
			 R_DOUBLE, domains[iblk].hash);
	ProblemArray_add("gamma", tblklocal[iblk].gamma, len,
			 R_DOUBLE, domains[iblk].hash);
	ProblemArray_add("rcm3t", tblklocal[iblk].rcm3t, len,
			 R_DOUBLE, domains[iblk].hash);
      }
   }
   if ( ndims == 3 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
	int len = domains[iblk].namix;
         tblklocal[iblk].diffcd = MALLOT(double, len);
         tblklocal[iblk].diffcu = MALLOT(double, len);
	 ProblemArray_add("diffCoefD", tblklocal[iblk].diffcd, len,
			  R_DOUBLE, domains[iblk].hash);
	 ProblemArray_add("diffCoefU", tblklocal[iblk].diffcu, len, 
			  R_DOUBLE, domains[iblk].hash);
      }
   }
   *rblk    = rblklocal ;
   *tblk    = tblklocal ;
}
void RadiationFree( RadiationData_t *rblk, RadiationData_t *rblkbak,
                    RadiationData_t *cblk, DiffusionData_t *tblk,
		    int needRblkBak)
{
   int iblk;
   int my_nblk = nblk ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      freeMatrix( &rblk[iblk], ndims ) ;
   }
   FREEMEM( rblk ) ;
   if ( needRblkBak > 0 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         freeMatrix( &rblkbak[iblk], ndims ) ;
      }
      FREEMEM( rblkbak ) ;
   }
   if ( solver != 1 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         freeMatrix( &cblk[iblk], ndims ) ;
      }
      FREEMEM( cblk ) ;
   }
   radfree( tblk ) ;
   FREEMEM( tblk ) ;
}
