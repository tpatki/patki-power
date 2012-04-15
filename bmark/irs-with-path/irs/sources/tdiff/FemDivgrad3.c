#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
typedef enum { _Tet_, _Prism_, _Hex_ } FEMTYPE_t ;
static void BuildFemMatrix( RadiationData_t *rblk, double gradX[8], double gradY[8],
                            double gradZ[8], double hgv[8][4], double dualVolume,
                            int index, Domain_t *domain, FEMTYPE_t elementType ) ;
#define HEXSET8(v,v1,v2,v3,v4,v5,v6,v7,v8)  \
   v1 = v  - 1 - jp - kp ; \
   v2 = v      - jp - kp ; \
   v3 = v           - kp ; \
   v4 = v  - 1      - kp ; \
   v5 = v  - 1 - jp      ; \
   v6 = v      - jp      ; \
   v7 = v                ; \
   v8 = v  - 1           ;            
void FemDivgrad3Interior( RadiationData_t *rblk,   
			  double *xc,   double *yc,   double *zc,
			  double *volc, Domain_t *domain,
			  int kMin,     int kMax,     int jMin,
			  int jMax,     int iMin,     int iMax )
{
   int i, j, iIndex, jIndex, kIndex ;
   int jp = domain->jp ;
   int kp = domain->kp ;
   double gradX[8], gradY[8], gradZ[8] ;
   double xDual[8], yDual[8], zDual[8] ;
   double hgv[8][4] ;
   double sq8 = 1.0 / sqrt( 8.0 ) ;
   double *volm = volc - kp - jp - 1   ;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8 ;
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8 ;
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8 ;
   HEXSET8(xc,x1,x2,x3,x4,x5,x6,x7,x8) ;
   HEXSET8(yc,y1,y2,y3,y4,y5,y6,y7,y8) ;
   HEXSET8(zc,z1,z2,z3,z4,z5,z6,z7,z8) ;
   hgv[0][0] =  sq8 ; hgv[0][1] =  sq8 ; hgv[0][2] =  sq8 ; hgv[0][3] = -sq8 ;
   hgv[1][0] = -sq8 ; hgv[1][1] =  sq8 ; hgv[1][2] = -sq8 ; hgv[1][3] =  sq8 ;
   hgv[2][0] =  sq8 ; hgv[2][1] = -sq8 ; hgv[2][2] = -sq8 ; hgv[2][3] = -sq8 ;
   hgv[3][0] = -sq8 ; hgv[3][1] = -sq8 ; hgv[3][2] =  sq8 ; hgv[3][3] =  sq8 ;
   hgv[4][0] =  sq8 ; hgv[4][1] = -sq8 ; hgv[4][2] = -sq8 ; hgv[4][3] =  sq8 ;
   hgv[5][0] = -sq8 ; hgv[5][1] = -sq8 ; hgv[5][2] =  sq8 ; hgv[5][3] = -sq8 ;
   hgv[6][0] =  sq8 ; hgv[6][1] =  sq8 ; hgv[6][2] =  sq8 ; hgv[6][3] =  sq8 ;
   hgv[7][0] = -sq8 ; hgv[7][1] =  sq8 ; hgv[7][2] = -sq8 ; hgv[7][3] = -sq8 ;
   for ( kIndex = kMin ; kIndex < kMax ; kIndex++ ) {
      for ( jIndex = jMin ; jIndex < jMax ; jIndex++ ) {
         for ( iIndex = iMin ; iIndex < iMax ; iIndex++ ) {
	    i = iIndex + jIndex * jp + kIndex * kp ;
	    xDual[0] = x1[i] ;
	    xDual[1] = x2[i] ;
	    xDual[2] = x3[i] ;
	    xDual[3] = x4[i] ;
	    xDual[4] = x5[i] ;
	    xDual[5] = x6[i] ;
	    xDual[6] = x7[i] ;
	    xDual[7] = x8[i] ;
	    yDual[0] = y1[i] ;
	    yDual[1] = y2[i] ;
	    yDual[2] = y3[i] ;
	    yDual[3] = y4[i] ;
	    yDual[4] = y5[i] ;
	    yDual[5] = y6[i] ;
	    yDual[6] = y7[i] ;
	    yDual[7] = y8[i] ;
	    zDual[0] = z1[i] ;
	    zDual[1] = z2[i] ;
	    zDual[2] = z3[i] ;
	    zDual[3] = z4[i] ;
	    zDual[4] = z5[i] ;
	    zDual[5] = z6[i] ;
	    zDual[6] = z7[i] ;
	    zDual[7] = z8[i] ;
   	    FemHexahedron( xDual, yDual, zDual, gradX, gradY, gradZ ) ;
            BuildFemMatrix( rblk, gradX, gradY, gradZ, hgv, volm[i], i,
                            domain, _Hex_ ) ;
	 }
      }
   }
}
void FemDivgrad3Boundary( RadiationData_t *rblk,  
			  double *xc,   double *yc,   double *zc,
			  double *volc, Domain_t *domain, 
			  int *regConList, int regConListLength )
{
   int i, j, iIndex ;
   int jp = domain->jp ;
   int kp = domain->kp ;
   double gradX[8], gradY[8], gradZ[8] ;
   double xDual[8], yDual[8], zDual[8] ;
   double hgv[8][4] ;
   double sq8 = 1.0 / sqrt( 8.0 ) ;
   double *volm = volc - kp - jp - 1   ;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8 ;
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8 ;
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8 ;
   HEXSET8(xc,x1,x2,x3,x4,x5,x6,x7,x8)  ;
   HEXSET8(yc,y1,y2,y3,y4,y5,y6,y7,y8)  ;
   HEXSET8(zc,z1,z2,z3,z4,z5,z6,z7,z8)  ;
   hgv[0][0] =  sq8 ; hgv[0][1] =  sq8 ; hgv[0][2] =  sq8 ; hgv[0][3] = -sq8 ;
   hgv[1][0] = -sq8 ; hgv[1][1] =  sq8 ; hgv[1][2] = -sq8 ; hgv[1][3] =  sq8 ;
   hgv[2][0] =  sq8 ; hgv[2][1] = -sq8 ; hgv[2][2] = -sq8 ; hgv[2][3] = -sq8 ;
   hgv[3][0] = -sq8 ; hgv[3][1] = -sq8 ; hgv[3][2] =  sq8 ; hgv[3][3] =  sq8 ;
   hgv[4][0] =  sq8 ; hgv[4][1] = -sq8 ; hgv[4][2] = -sq8 ; hgv[4][3] =  sq8 ;
   hgv[5][0] = -sq8 ; hgv[5][1] = -sq8 ; hgv[5][2] =  sq8 ; hgv[5][3] = -sq8 ;
   hgv[6][0] =  sq8 ; hgv[6][1] =  sq8 ; hgv[6][2] =  sq8 ; hgv[6][3] =  sq8 ;
   hgv[7][0] = -sq8 ; hgv[7][1] =  sq8 ; hgv[7][2] = -sq8 ; hgv[7][3] = -sq8 ;
   for ( iIndex = 0 ; iIndex < regConListLength ; iIndex++ ) {
      i = regConList[iIndex] ;
      xDual[0] = x1[i] ;
      xDual[1] = x2[i] ;
      xDual[2] = x3[i] ;
      xDual[3] = x4[i] ;
      xDual[4] = x5[i] ;
      xDual[5] = x6[i] ;
      xDual[6] = x7[i] ;
      xDual[7] = x8[i] ;
      yDual[0] = y1[i] ;
      yDual[1] = y2[i] ;
      yDual[2] = y3[i] ;
      yDual[3] = y4[i] ;
      yDual[4] = y5[i] ;
      yDual[5] = y6[i] ;
      yDual[6] = y7[i] ;
      yDual[7] = y8[i] ;
      zDual[0] = z1[i] ;
      zDual[1] = z2[i] ;
      zDual[2] = z3[i] ;
      zDual[3] = z4[i] ;
      zDual[4] = z5[i] ;
      zDual[5] = z6[i] ;
      zDual[6] = z7[i] ;
      zDual[7] = z8[i] ;
      FemHexahedron( xDual, yDual, zDual, gradX, gradY, gradZ ) ;
      BuildFemMatrix( rblk, gradX, gradY, gradZ, hgv, volm[i], i,
                      domain, _Hex_ ) ;
   }
}
static void BuildFemMatrix( RadiationData_t *rblk, double gradX[8], double gradY[8],
                            double gradZ[8], double hgv[8][4], double dualVolume,
                            int index, Domain_t *domain, FEMTYPE_t elementType )
{
   char *me = "BuildFemMatrix" ;
   int elementIndex, i, j, k ;
   int jp = domain->jp ;
   int kp = domain->kp ;
   double hgvt[4][8], hgc[8][8] ;
   double hourGlassMultiplier, myflops = 0.0 ;
   double *dbl = rblk->dbl  ;
   double *dbc = rblk->dbc  ;
   double *dbr = rblk->dbr  ;
   double *dcl = rblk->dcl  ;
   double *dcc = rblk->dcc  ;
   double *dcr = rblk->dcr  ;
   double *dfl = rblk->dfl  ;
   double *dfc = rblk->dfc  ;
   double *dfr = rblk->dfr  ;
   double *cbl = rblk->cbl  ;
   double *cbc = rblk->cbc  ;
   double *cbr = rblk->cbr  ;
   double *ccl = rblk->ccl  ;
   double *ccc = rblk->ccc  ;
   double *ccr = rblk->ccr  ;
   double *cfl = rblk->cfl  ;
   double *cfc = rblk->cfc  ;
   double *cfr = rblk->cfr  ;
   double *ubl = rblk->ubl  ;
   double *ubc = rblk->ubc  ;
   double *ubr = rblk->ubr  ;
   double *ucl = rblk->ucl  ;
   double *ucc = rblk->ucc  ;
   double *ucr = rblk->ucr  ;
   double *ufl = rblk->ufl  ;
   double *ufc = rblk->ufc  ;
   double *ufr = rblk->ufr  ;
   FT_INITIALIZE(me, domain->hash)
   if ( elementType == _Tet_ ) {
      hourGlassMultiplier = 0.0 ;
   }
   if ( elementType == _Prism_ ) {
      hourGlassMultiplier = 3.0 *
          ( gradX[0] * gradX[6] + gradY[0] * gradY[6] + gradZ[0] * gradZ[6] +
            gradX[1] * gradX[7] + gradY[1] * gradY[7] + gradZ[1] * gradZ[7] +
            gradX[2] * gradX[4] + gradY[2] * gradY[4] + gradZ[2] * gradZ[4] +
            gradX[3] * gradX[5] + gradY[3] * gradY[5] + gradZ[3] * gradZ[5] ) ;
      myflops += 23.0 ;
   }
   if ( elementType == _Hex_ ) {
      hourGlassMultiplier =
          ( gradX[0] * gradX[6] + gradY[0] * gradY[6] + gradZ[0] * gradZ[6] +
            gradX[1] * gradX[7] + gradY[1] * gradY[7] + gradZ[1] * gradZ[7] +
            gradX[2] * gradX[4] + gradY[2] * gradY[4] + gradZ[2] * gradZ[4] +
            gradX[3] * gradX[5] + gradY[3] * gradY[5] + gradZ[3] * gradZ[5] ) ;
      myflops += 23.0 ;
   }
   for ( i = 0 ; i < 8 ; i++ ) {
      for ( j = 0 ; j < 4 ; j++ ) {
	 hgvt[j][i] = hgv[i][j] ;
      }
      for ( j = 0 ; j < 8 ; j++ ) {
	 hgc[i][j] = 0.0 ;
      }
   }
   if ( (elementType == _Prism_) || (elementType == _Hex_) ) {
      for ( i = 0 ; i < 8 ; i++ ) {
         for ( j = (i+1) ; j < 8 ; j++ ) {
            for ( k = 0 ; k < 4 ; k++ ) {
	       hgc[i][j] += hgv[i][k] * hgvt[k][j] ;
	    }
         }
      }
      myflops += 224.0 ;
   }
   elementIndex = index - 1 - jp - kp ;
   ccr[elementIndex] -= dualVolume * 
	  ( gradX[0] * gradX[1] + gradY[0] * gradY[1] + gradZ[0] * gradZ[1] -
	    hgc[0][1] * hourGlassMultiplier ) ;
   cfr[elementIndex] -= dualVolume *
	  ( gradX[0] * gradX[2] + gradY[0] * gradY[2] + gradZ[0] * gradZ[2] -
	    hgc[0][2] * hourGlassMultiplier ) ;
   cfc[elementIndex] -= dualVolume *
	  ( gradX[0] * gradX[3] + gradY[0] * gradY[3] + gradZ[0] * gradZ[3] -
	    hgc[0][3] * hourGlassMultiplier ) ;
   ucc[elementIndex] -= dualVolume *
	  ( gradX[0] * gradX[4] + gradY[0] * gradY[4] + gradZ[0] * gradZ[4] -
	    hgc[0][4] * hourGlassMultiplier ) ;
   ucr[elementIndex] -= dualVolume *
	  ( gradX[0] * gradX[5] + gradY[0] * gradY[5] + gradZ[0] * gradZ[5] -
	    hgc[0][5] * hourGlassMultiplier ) ;
   ufr[elementIndex] -= dualVolume *
	  ( gradX[0] * gradX[6] + gradY[0] * gradY[6] + gradZ[0] * gradZ[6] -
	    hgc[0][6] * hourGlassMultiplier ) ;
   ufc[elementIndex] -= dualVolume *
	  ( gradX[0] * gradX[7] + gradY[0] * gradY[7] + gradZ[0] * gradZ[7] -
	    hgc[0][7] * hourGlassMultiplier ) ;
   elementIndex = index - jp - kp ;
   cfc[elementIndex] -= dualVolume *
	  ( gradX[1] * gradX[2] + gradY[1] * gradY[2] + gradZ[1] * gradZ[2] -
	    hgc[1][2] * hourGlassMultiplier ) ;
   cfl[elementIndex] -= dualVolume *
	  ( gradX[1] * gradX[3] + gradY[1] * gradY[3] + gradZ[1] * gradZ[3] -
	    hgc[1][3] * hourGlassMultiplier ) ;
   ucl[elementIndex] -= dualVolume *
	  ( gradX[1] * gradX[4] + gradY[1] * gradY[4] + gradZ[1] * gradZ[4] -
	    hgc[1][4] * hourGlassMultiplier ) ;
   ucc[elementIndex] -= dualVolume *
	  ( gradX[1] * gradX[5] + gradY[1] * gradY[5] + gradZ[1] * gradZ[5] -
	    hgc[1][5] * hourGlassMultiplier ) ;
   ufc[elementIndex] -= dualVolume *
	  ( gradX[1] * gradX[6] + gradY[1] * gradY[6] + gradZ[1] * gradZ[6] -
	    hgc[1][6] * hourGlassMultiplier ) ;
   ufl[elementIndex] -= dualVolume *
	  ( gradX[1] * gradX[7] + gradY[1] * gradY[7] + gradZ[1] * gradZ[7] -
	    hgc[1][7] * hourGlassMultiplier ) ;
   elementIndex = index - kp ;
   ccl[elementIndex] -= dualVolume *
	  ( gradX[2] * gradX[3] + gradY[2] * gradY[3] + gradZ[2] * gradZ[3] -
	    hgc[2][3] * hourGlassMultiplier ) ;
   ubl[elementIndex] -= dualVolume *
	  ( gradX[2] * gradX[4] + gradY[2] * gradY[4] + gradZ[2] * gradZ[4] -
	    hgc[2][4] * hourGlassMultiplier ) ;
   ubc[elementIndex] -= dualVolume *
	  ( gradX[2] * gradX[5] + gradY[2] * gradY[5] + gradZ[2] * gradZ[5] -
	    hgc[2][5] * hourGlassMultiplier ) ;
   ucc[elementIndex] -= dualVolume *
	  ( gradX[2] * gradX[6] + gradY[2] * gradY[6] + gradZ[2] * gradZ[6] -
	    hgc[2][6] * hourGlassMultiplier ) ;
   ucl[elementIndex] -= dualVolume *
	  ( gradX[2] * gradX[7] + gradY[2] * gradY[7] + gradZ[2] * gradZ[7] -
	    hgc[2][7] * hourGlassMultiplier ) ;
   elementIndex = index - 1 - kp ;
   ubc[elementIndex] -= dualVolume *
	  ( gradX[3] * gradX[4] + gradY[3] * gradY[4] + gradZ[3] * gradZ[4] -
	    hgc[3][4] * hourGlassMultiplier ) ;
   ubr[elementIndex] -= dualVolume *
	  ( gradX[3] * gradX[5] + gradY[3] * gradY[5] + gradZ[3] * gradZ[5] -
	    hgc[3][5] * hourGlassMultiplier ) ;
   ucr[elementIndex] -= dualVolume *
	  ( gradX[3] * gradX[6] + gradY[3] * gradY[6] + gradZ[3] * gradZ[6] -
	    hgc[3][6] * hourGlassMultiplier ) ;
   ucc[elementIndex] -= dualVolume *
	  ( gradX[3] * gradX[7] + gradY[3] * gradY[7] + gradZ[3] * gradZ[7] -
	    hgc[3][7] * hourGlassMultiplier ) ;
   elementIndex = index - 1 - jp ;
   ccr[elementIndex] -= dualVolume *
	  ( gradX[4] * gradX[5] + gradY[4] * gradY[5] + gradZ[4] * gradZ[5] -
	    hgc[4][5] * hourGlassMultiplier ) ;
   cfr[elementIndex] -= dualVolume *
	  ( gradX[4] * gradX[6] + gradY[4] * gradY[6] + gradZ[4] * gradZ[6] -
	    hgc[4][6] * hourGlassMultiplier ) ;
   cfc[elementIndex] -= dualVolume *
	  ( gradX[4] * gradX[7] + gradY[4] * gradY[7] + gradZ[4] * gradZ[7] -
	    hgc[4][7] * hourGlassMultiplier ) ;
   elementIndex = index - jp ;
   cfc[elementIndex] -= dualVolume *
	  ( gradX[5] * gradX[6] + gradY[5] * gradY[6] + gradZ[5] * gradZ[6] -
	    hgc[5][6] * hourGlassMultiplier ) ;
   cfl[elementIndex] -= dualVolume *
	  ( gradX[5] * gradX[7] + gradY[5] * gradY[7] + gradZ[5] * gradZ[7] -
	    hgc[5][7] * hourGlassMultiplier ) ;
   elementIndex = index ;
   ccl[elementIndex] -= dualVolume *
	  ( gradX[6] * gradX[7] + gradY[6] * gradY[7] + gradZ[6] * gradZ[7] -
	    hgc[6][7] * hourGlassMultiplier ) ;
   myflops += 252.0 ;
   FT_FINALIZE(me, domain->hash, myflops)
}
