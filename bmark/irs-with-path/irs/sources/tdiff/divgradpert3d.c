#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
#define HEXSET8(v,v1,v2,v3,v4,v5,v6,v7,v8)  \
   v7 = v ;         \
   v8 = v  -  1 ;   \
   v6 = v  - jp ;   \
   v5 = v6 -  1 ;   \
   v1 = v5 - kp ;   \
   v2 = v6 - kp ;   \
   v3 = v7 - kp ;   \
   v4 = v8 - kp ;
void divgradpert3d( RadiationData_t *rblk, double *xc, double *yc, double *zc,
                    double *volc, int iMin, int iMax, int jMin, int jMax,
                                  int kMin, int kMax, Domain_t *domain )
{
   char *me = "divgradpert3d" ;
   int i, ibc, n, iIndex, jIndex, kIndex ;
   int *ndx ;
   int jp = domain->jp ;
   int kp = domain->kp ;
   double a11, a12, a13, a22, a23, a33 ;
   double g11, g12, g13, g22, g23, g33 ;
   double dxi, dxj, dxk, dyi, dyj, dyk, dzi, dzj, dzk ;
   double w, myflops = 0.0 ;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8 ;
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8 ;
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8 ;
   double *m21 = rblk->ccl - kp - jp     ;
   double *m31 = rblk->cbl - kp          ;
   double *m32 = rblk->cbc - kp          ;
   double *m41 = rblk->cbc - kp      - 1 ;
   double *m42 = rblk->cbr - kp      - 1 ;
   double *m43 = rblk->ccl - kp          ;
   double *m51 = rblk->dcc      - jp - 1 ;
   double *m52 = rblk->dcr      - jp - 1 ;
   double *m54 = rblk->dfc      - jp - 1 ;
   double *m61 = rblk->dcl      - jp     ;
   double *m62 = rblk->dcc      - jp     ;
   double *m63 = rblk->dfc      - jp     ;
   double *m65 = rblk->ccl      - jp     ;
   double *m72 = rblk->dbc               ;
   double *m73 = rblk->dcc               ;
   double *m74 = rblk->dcl               ;
   double *m75 = rblk->cbl               ;
   double *m76 = rblk->cbc               ;
   double *m81 = rblk->dbc           - 1 ;
   double *m83 = rblk->dcr           - 1 ;
   double *m84 = rblk->dcc           - 1 ;
   double *m85 = rblk->cbc           - 1 ;
   double *m86 = rblk->cbr           - 1 ;
   double *m87 = rblk->ccl               ;
   double *volm = volc - kp - jp - 1 ;
   FT_INITIALIZE(me, domain->hash)
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
      if ( domain->bc[ibc].rtype == POLE ) {
         n   = domain->bc[ibc].len ;
         ndx = domain->bc[ibc].ndx ;
         for ( i = 0 ; i < n ; i++ ) {
	    volm[ndx[i]] = 0.0 ;
	 }
      }
   }
   HEXSET8(xc,x1,x2,x3,x4,x5,x6,x7,x8) ;
   HEXSET8(yc,y1,y2,y3,y4,y5,y6,y7,y8) ;
   HEXSET8(zc,z1,z2,z3,z4,z5,z6,z7,z8) ;
   for ( kIndex = kMin ; kIndex < kMax ; kIndex++ ) {
      for ( jIndex = jMin ; jIndex < jMax ; jIndex++ ) {
         for ( iIndex = iMin ; iIndex < iMax ; iIndex++ ) {
	    i = iIndex + jIndex * jp + kIndex * kp ;
	    dxi = x2[i] + x3[i] + x6[i] + x7[i] - x1[i] - x4[i] - x5[i] - x8[i] ;
	    dyi = y2[i] + y3[i] + y6[i] + y7[i] - y1[i] - y4[i] - y5[i] - y8[i] ;
	    dzi = z2[i] + z3[i] + z6[i] + z7[i] - z1[i] - z4[i] - z5[i] - z8[i] ;
	    dxj = x3[i] + x4[i] + x7[i] + x8[i] - x1[i] - x2[i] - x5[i] - x6[i] ;
	    dyj = y3[i] + y4[i] + y7[i] + y8[i] - y1[i] - y2[i] - y5[i] - y6[i] ;
	    dzj = z3[i] + z4[i] + z7[i] + z8[i] - z1[i] - z2[i] - z5[i] - z6[i] ;
	    dxk = x5[i] + x6[i] + x7[i] + x8[i] - x1[i] - x2[i] - x3[i] - x4[i] ;
	    dyk = y5[i] + y6[i] + y7[i] + y8[i] - y1[i] - y2[i] - y3[i] - y4[i] ;
	    dzk = z5[i] + z6[i] + z7[i] + z8[i] - z1[i] - z2[i] - z3[i] - z4[i] ;
	    dxi *= 0.25 ;
	    dyi *= 0.25 ;
	    dzi *= 0.25 ;
	    dxj *= 0.25 ;
	    dyj *= 0.25 ;
	    dzj *= 0.25 ;
	    dxk *= 0.25 ;
	    dyk *= 0.25 ;
	    dzk *= 0.25 ;
	    g11 = dxi * dxi + dyi * dyi + dzi * dzi ;
	    g12 = dxi * dxj + dyi * dyj + dzi * dzj ;
	    g13 = dxi * dxk + dyi * dyk + dzi * dzk ;
	    g22 = dxj * dxj + dyj * dyj + dzj * dzj ;
	    g23 = dxj * dxk + dyj * dyk + dzj * dzk ;
	    g33 = dxk * dxk + dyk * dyk + dzk * dzk ;
	    a11 = g22 * g33 - g23 * g23 ;
	    a22 = g11 * g33 - g13 * g13 ;
	    a33 = g11 * g22 - g12 * g12 ;
	    a12 = g23 * g13 - g12 * g33 ;
	    a13 = g12 * g23 - g22 * g13 ;
	    a23 = g13 * g12 - g11 * g23 ;
	    w   = 0.25 / ( volm[i] + ptiny ) ;
	    if ( (volm[i] < volcut) || (domain->node[i] == 0) ) {
	       w = 0.0 ; 
	    }
  	    m21[i] +=  w * a11 ;
	    m31[i] +=  w * a12 ;
	    m32[i] +=  w * a22 ;
	    m41[i] +=  w * a22 ;
	    m42[i] += -w * a12 ;
	    m43[i] +=  w * a11 ;
	    m51[i] +=  w * a33 ;
	    m52[i] += -w * a13 ;
	    m54[i] += -w * a23 ;
	    m61[i] +=  w * a13 ;
	    m62[i] +=  w * a33 ;
	    m63[i] += -w * a23 ;
	    m65[i] +=  w * a11 ;
	    m72[i] +=  w * a23 ;
	    m73[i] +=  w * a33 ;
	    m74[i] +=  w * a13 ;
	    m75[i] +=  w * a12 ;
	    m76[i] +=  w * a22 ;
	    m81[i] +=  w * a23 ;
	    m83[i] += -w * a13 ;
	    m84[i] +=  w * a33 ;
	    m85[i] +=  w * a22 ;
	    m86[i] += -w * a12 ;
	    m87[i] +=  w * a11 ;
	 }
      }
   }
   myflops += 179.0 * ( iMax - iMin ) * ( jMax - jMin ) * ( kMax - kMin ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void divgradpert3bnd( RadiationData_t *rblk, double *xc, double *yc, double *zc,
                      double *volc, int *regConList, int regConListLength,
		      Domain_t *domain )
{
   char *me = "divgradpert3bnd" ;
   int i, iIndex, ibc, n ;
   int *ndx ;
   int jp = domain->jp ;
   int kp = domain->kp ;
   double a11, a12, a13, a22, a23, a33 ;
   double g11, g12, g13, g22, g23, g33 ;
   double dxi, dxj, dxk, dyi, dyj, dyk, dzi, dzj, dzk ;
   double w, myflops = 0.0 ;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8 ;
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8 ;
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8 ;
   double *m21 = rblk->ccl - kp - jp     ;
   double *m31 = rblk->cbl - kp          ;
   double *m32 = rblk->cbc - kp          ;
   double *m41 = rblk->cbc - kp      - 1 ;
   double *m42 = rblk->cbr - kp      - 1 ;
   double *m43 = rblk->ccl - kp          ;
   double *m51 = rblk->dcc      - jp - 1 ;
   double *m52 = rblk->dcr      - jp - 1 ;
   double *m54 = rblk->dfc      - jp - 1 ;
   double *m61 = rblk->dcl      - jp     ;
   double *m62 = rblk->dcc      - jp     ;
   double *m63 = rblk->dfc      - jp     ;
   double *m65 = rblk->ccl      - jp     ;
   double *m72 = rblk->dbc               ;
   double *m73 = rblk->dcc               ;
   double *m74 = rblk->dcl               ;
   double *m75 = rblk->cbl               ;
   double *m76 = rblk->cbc               ;
   double *m81 = rblk->dbc           - 1 ;
   double *m83 = rblk->dcr           - 1 ;
   double *m84 = rblk->dcc           - 1 ;
   double *m85 = rblk->cbc           - 1 ;
   double *m86 = rblk->cbr           - 1 ;
   double *m87 = rblk->ccl               ;
   double *volm = volc - kp - jp - 1 ;
   FT_INITIALIZE(me, domain->hash)
   for ( ibc = 0 ; ibc < domain->nbc ; ibc++ ) {
      if ( domain->bc[ibc].rtype == POLE ) {
         n   = domain->bc[ibc].len ;
         ndx = domain->bc[ibc].ndx ;
         for ( i = 0 ; i < n ; i++ ) {
	    volm[ndx[i]] = 0.0 ;
	 }
      }
   }
   HEXSET8(xc,x1,x2,x3,x4,x5,x6,x7,x8)  ;
   HEXSET8(yc,y1,y2,y3,y4,y5,y6,y7,y8)  ;
   HEXSET8(zc,z1,z2,z3,z4,z5,z6,z7,z8)  ;
   for ( iIndex = 0 ; iIndex < regConListLength ; iIndex++ ) {
      i = regConList[iIndex] ;
      dxi = x2[i] + x3[i] + x6[i] + x7[i] - x1[i] - x4[i] - x5[i] - x8[i] ;
      dyi = y2[i] + y3[i] + y6[i] + y7[i] - y1[i] - y4[i] - y5[i] - y8[i] ;
      dzi = z2[i] + z3[i] + z6[i] + z7[i] - z1[i] - z4[i] - z5[i] - z8[i] ;
      dxj = x3[i] + x4[i] + x7[i] + x8[i] - x1[i] - x2[i] - x5[i] - x6[i] ;
      dyj = y3[i] + y4[i] + y7[i] + y8[i] - y1[i] - y2[i] - y5[i] - y6[i] ;
      dzj = z3[i] + z4[i] + z7[i] + z8[i] - z1[i] - z2[i] - z5[i] - z6[i] ;
      dxk = x5[i] + x6[i] + x7[i] + x8[i] - x1[i] - x2[i] - x3[i] - x4[i] ;
      dyk = y5[i] + y6[i] + y7[i] + y8[i] - y1[i] - y2[i] - y3[i] - y4[i] ;
      dzk = z5[i] + z6[i] + z7[i] + z8[i] - z1[i] - z2[i] - z3[i] - z4[i] ;
      dxi *= 0.25 ;
      dyi *= 0.25 ;
      dzi *= 0.25 ;
      dxj *= 0.25 ;
      dyj *= 0.25 ;
      dzj *= 0.25 ;
      dxk *= 0.25 ;
      dyk *= 0.25 ;
      dzk *= 0.25 ;
      g11 = dxi * dxi + dyi * dyi + dzi * dzi ;
      g12 = dxi * dxj + dyi * dyj + dzi * dzj ;
      g13 = dxi * dxk + dyi * dyk + dzi * dzk ;
      g22 = dxj * dxj + dyj * dyj + dzj * dzj ;
      g23 = dxj * dxk + dyj * dyk + dzj * dzk ;
      g33 = dxk * dxk + dyk * dyk + dzk * dzk ;
      a11 = g22 * g33 - g23 * g23 ;
      a22 = g11 * g33 - g13 * g13 ;
      a33 = g11 * g22 - g12 * g12 ;
      a12 = g23 * g13 - g12 * g33 ;
      a13 = g12 * g23 - g22 * g13 ;
      a23 = g13 * g12 - g11 * g23 ;
      w   = 0.25 / ( volm[i] + ptiny ) ;
      if ( (volm[i] < volcut) || (domain->node[i] == 0) ) {
	  w = 0.0 ; 
      }
      m21[i] +=  w * a11 ;
      m31[i] +=  w * a12 ;
      m32[i] +=  w * a22 ;
      m41[i] +=  w * a22 ;
      m42[i] += -w * a12 ;
      m43[i] +=  w * a11 ;
      m51[i] +=  w * a33 ;
      m52[i] += -w * a13 ;
      m54[i] += -w * a23 ;
      m61[i] +=  w * a13 ;
      m62[i] +=  w * a33 ;
      m63[i] += -w * a23 ;
      m65[i] +=  w * a11 ;
      m72[i] +=  w * a23 ;
      m73[i] +=  w * a33 ;
      m74[i] +=  w * a13 ;
      m75[i] +=  w * a12 ;
      m76[i] +=  w * a22 ;
      m81[i] +=  w * a23 ;
      m83[i] += -w * a13 ;
      m84[i] +=  w * a33 ;
      m85[i] +=  w * a22 ;
      m86[i] += -w * a12 ;
      m87[i] +=  w * a11 ;
   }
   myflops += 179.0 * regConListLength ;
   FT_FINALIZE(me, domain->hash, myflops)
}
