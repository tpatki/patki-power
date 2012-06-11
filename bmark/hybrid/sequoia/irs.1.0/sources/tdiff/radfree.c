#include "irs.h"
#include "irstdiff.h"
#include "ProblemArray.h"
#include "DiffusionData.h"
void radfree( DiffusionData_t *tblk )
{
   int iblk ;
   int my_nblk = nblk ;
#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
      FREEMEM( tblk[iblk].phi    ) ;
      FREEMEM( tblk[iblk].dphi   ) ;
      FREEMEM( tblk[iblk].adphi  ) ;
      FREEMEM( tblk[iblk].rhs    ) ;
      FREEMEM( tblk[iblk].esrc   ) ;
      FREEMEM( tblk[iblk].flmt   ) ;
      FREEMEM( tblk[iblk].phim   ) ;
      FREEMEM( tblk[iblk].xplnk  ) ;
      FREEMEM( tblk[iblk].alpha  ) ;
      FREEMEM( tblk[iblk].diffcl ) ;
      FREEMEM( tblk[iblk].diffcr ) ;
      FREEMEM( tblk[iblk].diffcb ) ;
      FREEMEM( tblk[iblk].diffcf ) ;
      ProblemArray_del("phi", domains[iblk].hash);
      ProblemArray_del("dphi", domains[iblk].hash);
      ProblemArray_del("adphi", domains[iblk].hash);
      ProblemArray_del("rhs", domains[iblk].hash);
      ProblemArray_del("esrc", domains[iblk].hash);
      ProblemArray_del("flmt", domains[iblk].hash);
      ProblemArray_del("phim", domains[iblk].hash);
      ProblemArray_del("xplnk", domains[iblk].hash);
      ProblemArray_del("alpha", domains[iblk].hash);
      ProblemArray_del("diffCoefL", domains[iblk].hash);
      ProblemArray_del("diffCoefR", domains[iblk].hash);
      ProblemArray_del("diffCoefB", domains[iblk].hash);
      ProblemArray_del("diffCoefF", domains[iblk].hash);
   }
   if ( ndims == 3 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         FREEMEM( tblk[iblk].diffcd ) ;
         FREEMEM( tblk[iblk].diffcu ) ;
 	 ProblemArray_del("diffCoefD", domains[iblk].hash);
	 ProblemArray_del("diffCoefU", domains[iblk].hash);
     }
   }
   if ( iftion == 1 ) {
#include "pardo.h"
      for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
         FREEMEM( tblk[iblk].kie   ) ;
         FREEMEM( tblk[iblk].beta  ) ;
         FREEMEM( tblk[iblk].gamma ) ;
         FREEMEM( tblk[iblk].rcm3t ) ;
 	 ProblemArray_del("kie", domains[iblk].hash);
	 ProblemArray_del("beta", domains[iblk].hash);
	 ProblemArray_del("gamma", domains[iblk].hash);
	 ProblemArray_del("rcm3t", domains[iblk].hash);
      }
   }
}
