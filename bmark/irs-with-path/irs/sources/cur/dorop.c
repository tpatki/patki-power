#include "irs.h"
#include "cgl.h"
#include "irscur.h"
#define ROPSUM  1
#define ROPSUMV 2
#define ROPSUMM 3
#define ROPAVE  4
#define ROPAVEV 5
#define ROPAVEM 6
#define ROPMAX  7
#define ROPMIN  8
void dorop( double *result, double *field, int *ndx, int n, int roptype )
{
   int i,wgttype,ifave ;
   double *wgt,wsum,rsum,rmax,rmin ;
   if ( roptype < ROPMAX) {
      if ((roptype == ROPAVE ) | (roptype == ROPSUM )) wgttype = 0 ;
      if ((roptype == ROPAVEV) | (roptype == ROPSUMV)) wgttype = 1 ;
      if ((roptype == ROPAVEM) | (roptype == ROPSUMM)) wgttype = 2 ;
      ifave = 0 ;
      if ((roptype == ROPAVE ) 
        | (roptype == ROPAVEV)
        | (roptype == ROPAVEM)) ifave = 1 ;
      wgt = ALLOT(double,n) ;
      if (wgttype == 0) { 
	 for ( i = 0 ; i < n ; i++ ) {
	    wgt[i] = 1. ;
         }
      } else if (wgttype == 1) { 
	 for ( i = 0 ; i < n ; i++ ) {
	    wgt[i] =  domains[blknum].vol[ndx[i]] ;
         }
      } else if (wgttype == 2) { 
 	 for ( i = 0 ; i < n ; i++ ) {
	    wgt[i] = domains[blknum].zmass[ndx[i]] ;
         }
      }
      wsum = 1. ;
      if (ifave)  {
         wsum = 0. ;
         for ( i = 0 ; i < n ; i++ ) {
            wsum += wgt[i] ;
         }
      }
      for ( i = 0 ; i < n ; i++ ) {
         wgt[i] *= field[ndx[i]] ;
      }
      rsum = 0. ;
      for ( i = 0 ; i < n ; i++ ) {
         rsum += wgt[i] ;
      }
      result[0] = rsum / wsum ;
      FREEMEM(wgt) ;
   }
   if ( roptype == ROPMAX) {
      rmax = field[ndx[0]] ;
      for ( i = 1 ; i < n ; i++ ) {
         if (field[ndx[i]] > rmax) {
            rmax = field[ndx[i]] ;
         }
      }
      result[0] = rmax ;
   }
   if ( roptype == ROPMIN) {
      rmin = field[ndx[0]] ;
      for ( i = 1 ; i < n ; i++ ) {
         if (field[ndx[i]] < rmin) {
            rmin = field[ndx[i]] ;
         }
      }
      result[0] = rmin ;
   }
}
#undef ROPSUM
#undef ROPSUMV
#undef ROPSUMM
#undef ROPAVE
#undef ROPAVEV
#undef ROPAVEM
#undef ROPMAX
#undef ROPMIN
