#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#define HEXSET8(v,v1,v2,v3,v4,v5,v6,v7,v8) \
   v7 = v       ;   \
   v8 = v  - 1  ;   \
   v6 = v  - jp ;   \
   v5 = v6 - 1  ;   \
   v1 = v5 - kp ;   \
   v2 = v6 - kp ;   \
   v3 = v7 - kp ;   \
   v4 = v8 - kp ;
void FluxLimiterPert3d( double *flmt, double *phi, double *xc, double *yc,
                        double *zc, double *volc, Domain_t *domain,
                        double fscl, double umin, int kMin, int  kMax, int jMin,
			int jMax,    int iMin,    int iMax )
{
   char *me = "FluxLimiterPert3d" ;
   int i, ibc, n, iIndex, jIndex, kIndex ;
   int *ndx ;
   int jp = domain->jp ;
   int kp = domain->kp ;
   double dxi, dxj, dxk, dyi, dyj, dyk, dzi, dzj, dzk ;
   double b11, b12, b13, b21, b22, b23, b31, b32, b33 ;
   double ux,  uy,  uz,  u2,  u3,  u4,  w,   voli ;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8 ;
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8 ;
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8 ;
   double *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8 ;
   double *volm ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   volm = volc - kp - jp - 1 ;
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
   HEXSET8(phi,p1,p2,p3,p4,p5,p6,p7,p8) ;
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
	    w    = 0.25 / ( volm[i] + ptiny ) ;
	    if ( (volm[i] < volcut) || (domain->node[i] == 0) ) {
	       w = 0.0 ; 
	    }
	    b11 = dyj * dzk - dzj * dyk ;
	    b21 = dyk * dzi - dyi * dzk ;
	    b31 = dyi * dzj - dzi * dyj ;
	    b12 = dxk * dzj - dxj * dzk ;
	    b22 = dxi * dzk - dxk * dzi ;
	    b32 = dxj * dzi - dxi * dzj ;
	    b13 = dxj * dyk - dxk * dyj ;
	    b23 = dxk * dyi - dxi * dyk ;
	    b33 = dxi * dyj - dxj * dyi ;
	    u2 = p2[i] + p3[i] - p4[i] - p1[i] + p6[i] + p7[i] - p8[i] - p5[i] ;
	    u3 = p3[i] + p4[i] - p1[i] - p2[i] + p7[i] + p8[i] - p5[i] - p6[i] ;
	    u4 = p5[i] + p6[i] + p7[i] + p8[i] - p1[i] - p2[i] - p3[i] - p4[i] ;
	    ux = 0.25 * ( b11 * u2 + b21 * u3 + b31 * u4 ) ;
	    uy = 0.25 * ( b12 * u2 + b22 * u3 + b32 * u4 ) ;
	    uz = 0.25 * ( b13 * u2 + b23 * u3 + b33 * u4 ) ;
	    voli = 4.0 * w ;
	    flmt[i] = sqrt( ux * ux + uy * uy + uz * uz ) * voli ;
	    flmt[i] = 8.0 * fscl * flmt[i]
	            / ( p1[i] + p2[i] + p3[i] + p4[i]
                      + p5[i] + p6[i] + p7[i] + p8[i] + umin ) ;
	 }
      }
   }
   myflops += 168.0 * ( iMax - iMin ) * ( jMax - jMin ) * ( kMax - kMin ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void FluxLimiterPert3Bnd( double *flmt, double *phi, double *xc, double *yc,
                          double *zc, double *volc, Domain_t *domain,
                          double fscl, double umin, int *regConList,
                          int regConListLength )
{
   char *me = "FluxLimiterPert3Bnd" ;
   int i, ibc, n, iIndex ;
   int *ndx ;
   int jp = domain->jp ;
   int kp = domain->kp ;
   double dxi, dxj, dxk, dyi, dyj, dyk, dzi, dzj, dzk ;
   double b11, b12, b13, b21, b22, b23, b31, b32, b33 ;
   double ux,  uy,  uz,  u2,  u3,  u4,  w,   voli ;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8 ;
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8 ;
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8 ;
   double *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8 ;
   double *volm ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   volm = volc - kp - jp - 1 ;
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
   HEXSET8(phi,p1,p2,p3,p4,p5,p6,p7,p8) ;
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
      w    = 0.25 / ( volm[i] + ptiny ) ;
      if ( (volm[i] < volcut) || (domain->node[i] == 0) ) {
         w = 0.0 ; 
      }
      b11 = dyj * dzk - dzj * dyk ;
      b21 = dyk * dzi - dyi * dzk ;
      b31 = dyi * dzj - dzi * dyj ;
      b12 = dxk * dzj - dxj * dzk ;
      b22 = dxi * dzk - dxk * dzi ;
      b32 = dxj * dzi - dxi * dzj ;
      b13 = dxj * dyk - dxk * dyj ;
      b23 = dxk * dyi - dxi * dyk ;
      b33 = dxi * dyj - dxj * dyi ;
      u2 = p2[i] + p3[i] - p4[i] - p1[i] + p6[i] + p7[i] - p8[i] - p5[i] ;
      u3 = p3[i] + p4[i] - p1[i] - p2[i] + p7[i] + p8[i] - p5[i] - p6[i] ;
      u4 = p5[i] + p6[i] + p7[i] + p8[i] - p1[i] - p2[i] - p3[i] - p4[i] ;
      ux = 0.25 * ( b11 * u2 + b21 * u3 + b31 * u4 ) ;
      uy = 0.25 * ( b12 * u2 + b22 * u3 + b32 * u4 ) ;
      uz = 0.25 * ( b13 * u2 + b23 * u3 + b33 * u4 ) ;
      voli = 4.0 * w ;
      flmt[i] = sqrt( ux * ux + uy * uy + uz * uz ) * voli ;
      flmt[i] = 8.0 * fscl * flmt[i]
              / ( p1[i] + p2[i] + p3[i] + p4[i]
                + p5[i] + p6[i] + p7[i] + p8[i] + umin ) ;
   }
   myflops += 168.0 * regConListLength ;
   FT_FINALIZE(me, domain->hash, myflops) 
}
double FluxLimiterTetrahedron( double x[4], double y[4], double z[4],
			       double variable[4], double umin )
{
  int i ;
  double dSdX, dSdY, dSdZ ;
  double dTdX, dTdY, dTdZ ;
  double dUdX, dUdY, dUdZ ;
  double gradX[4], gradY[4], gradZ[4] ;
  double fluxLimiter ;
  double sum       = umin ;
  double gradientX = 0.0  ;
  double gradientY = 0.0  ;
  double gradientZ = 0.0  ;
  double dPhi1Ds =  1.0 ;
  double dPhi1Dt =  0.0 ;
  double dPhi1Du =  0.0 ;
  double dPhi2Ds =  0.0 ;
  double dPhi2Dt =  1.0 ;
  double dPhi2Du =  0.0 ;
  double dPhi3Ds =  0.0 ;
  double dPhi3Dt =  0.0 ;
  double dPhi3Du =  1.0 ;
  double dPhi4Ds = -1.0 ;
  double dPhi4Dt = -1.0 ;
  double dPhi4Du = -1.0 ;
  double dXdS    = x[0] - x[3] ;
  double dXdT    = x[1] - x[3] ;
  double dXdU    = x[2] - x[3] ;
  double dYdS    = y[0] - y[3] ;
  double dYdT    = y[1] - y[3] ;
  double dYdU    = y[2] - y[3] ;
  double dZdS    = z[0] - z[3] ;
  double dZdT    = z[1] - z[3] ;
  double dZdU    = z[2] - z[3] ;
  double jacobian = dXdS * ( dYdT * dZdU - dYdU * dZdT ) +
                    dYdS * ( dZdT * dXdU - dZdU * dXdT ) +
                    dZdS * ( dXdT * dYdU - dXdU * dYdT ) ;
  jacobian = 1.0 / jacobian ;
  dSdX = jacobian * ( dYdT * dZdU - dYdU * dZdT ) ;
  dSdY = jacobian * ( dZdT * dXdU - dZdU * dXdT ) ;
  dSdZ = jacobian * ( dXdT * dYdU - dXdU * dYdT ) ;
  dTdX = jacobian * ( dYdU * dZdS - dYdS * dZdU ) ;
  dTdY = jacobian * ( dZdU * dXdS - dZdS * dXdU ) ;
  dTdZ = jacobian * ( dXdU * dYdS - dXdS * dYdU ) ;
  dUdX = jacobian * ( dYdS * dZdT - dYdT * dZdS ) ;
  dUdY = jacobian * ( dZdS * dXdT - dZdT * dXdS ) ;
  dUdZ = jacobian * ( dXdS * dYdT - dXdT * dYdS ) ;
  gradX[0] = dPhi1Ds * dSdX + dPhi1Dt * dTdX + dPhi1Du * dUdX ;
  gradY[0] = dPhi1Ds * dSdY + dPhi1Dt * dTdY + dPhi1Du * dUdY ;
  gradZ[0] = dPhi1Ds * dSdZ + dPhi1Dt * dTdZ + dPhi1Du * dUdZ ;
  gradX[1] = dPhi2Ds * dSdX + dPhi2Dt * dTdX + dPhi2Du * dUdX ;
  gradY[1] = dPhi2Ds * dSdY + dPhi2Dt * dTdY + dPhi2Du * dUdY ;
  gradZ[1] = dPhi2Ds * dSdZ + dPhi2Dt * dTdZ + dPhi2Du * dUdZ ;
  gradX[2] = dPhi3Ds * dSdX + dPhi3Dt * dTdX + dPhi3Du * dUdX ;
  gradY[2] = dPhi3Ds * dSdY + dPhi3Dt * dTdY + dPhi3Du * dUdY ;
  gradZ[2] = dPhi3Ds * dSdZ + dPhi3Dt * dTdZ + dPhi3Du * dUdZ ;
  gradX[3] = dPhi4Ds * dSdX + dPhi4Dt * dTdX + dPhi4Du * dUdX ;
  gradY[3] = dPhi4Ds * dSdY + dPhi4Dt * dTdY + dPhi4Du * dUdY ;
  gradZ[3] = dPhi4Ds * dSdZ + dPhi4Dt * dTdZ + dPhi4Du * dUdZ ;
  for ( i = 0 ; i < 4 ; i++ ) {
    sum       += variable[i] ;
    gradientX += variable[i] * gradX[i] ;
    gradientY += variable[i] * gradY[i] ;
    gradientZ += variable[i] * gradZ[i] ;
  }
  fluxLimiter = sqrt( gradientX * gradientX + gradientY * gradientY +
		      gradientZ * gradientZ ) / sum ;
  return( fluxLimiter ) ;
}
double FluxLimiterPrism( double x[6],        double y[6],     double z[6],
			 double variable[6], double umin )
{
  int i ;
  double fluxLimiter ;
  double half = 0.5, third = 1.0 / 3.0, zero = 0.0 ;
  double gradX[6], gradY[6], gradZ[6] ;
  double sum       = umin ;
  double gradientX = 0.0  ;
  double gradientY = 0.0  ;
  double gradientZ = 0.0  ;
  double dSdX, dSdY, dSdZ ;
  double dTdX, dTdY, dTdZ ;
  double dUdX, dUdY, dUdZ ;
  double dPhi1Ds = -half  ;
  double dPhi1Dt = -half  ;
  double dPhi1Du = -third ;
  double dPhi2Ds =  half  ;
  double dPhi2Dt =  zero  ;
  double dPhi2Du = -third ;
  double dPhi3Ds =  zero  ;
  double dPhi3Dt =  half  ;
  double dPhi3Du = -third ;
  double dPhi4Ds = -half  ;
  double dPhi4Dt = -half  ;
  double dPhi4Du =  third ;
  double dPhi5Ds =  half  ;
  double dPhi5Dt =  zero  ;
  double dPhi5Du =  third ;
  double dPhi6Ds =  zero  ;
  double dPhi6Dt =  half  ;
  double dPhi6Du =  third ;
  double dXdS    =  half  * ( x[1] - x[0] + x[4] - x[3] ) ;
  double dXdT    =  half  * ( x[2] - x[0] + x[5] - x[3] ) ;
  double dXdU    =  third * ( x[5] - x[2] + x[4] - x[1] + x[3] - x[0] ) ;
  double dYdS    =  half  * ( y[1] - y[0] + y[4] - y[3] ) ;
  double dYdT    =  half  * ( y[2] - y[0] + y[5] - y[3] ) ;
  double dYdU    =  third * ( y[5] - y[2] + y[4] - y[1] + y[3] - y[0] ) ;
  double dZdS    =  half  * ( z[1] - z[0] + z[4] - z[3] ) ;
  double dZdT    =  half  * ( z[2] - z[0] + z[5] - z[3] ) ;
  double dZdU    =  third * ( z[5] - z[2] + z[4] - z[1] + z[3] - z[0] ) ;
  double jacobian = dXdS * ( dYdT * dZdU - dYdU * dZdT ) +
                    dYdS * ( dZdT * dXdU - dZdU * dXdT ) +
                    dZdS * ( dXdT * dYdU - dXdU * dYdT ) ;
  jacobian = 1.0 / jacobian ;
  dSdX     = jacobian * ( dYdT * dZdU - dYdU * dZdT ) ;
  dSdY     = jacobian * ( dZdT * dXdU - dZdU * dXdT ) ;
  dSdZ     = jacobian * ( dXdT * dYdU - dXdU * dYdT ) ;
  dTdX     = jacobian * ( dYdU * dZdS - dYdS * dZdU ) ;
  dTdY     = jacobian * ( dZdU * dXdS - dZdS * dXdU ) ;
  dTdZ     = jacobian * ( dXdU * dYdS - dXdS * dYdU ) ;
  dUdX     = jacobian * ( dYdS * dZdT - dYdT * dZdS ) ;
  dUdY     = jacobian * ( dZdS * dXdT - dZdT * dXdS ) ;
  dUdZ     = jacobian * ( dXdS * dYdT - dXdT * dYdS ) ;
  gradX[0] = dPhi1Ds * dSdX + dPhi1Dt * dTdX + dPhi1Du * dUdX ;
  gradY[0] = dPhi1Ds * dSdY + dPhi1Dt * dTdY + dPhi1Du * dUdY ;
  gradZ[0] = dPhi1Ds * dSdZ + dPhi1Dt * dTdZ + dPhi1Du * dUdZ ;
  gradX[1] = dPhi2Ds * dSdX + dPhi2Dt * dTdX + dPhi2Du * dUdX ;
  gradY[1] = dPhi2Ds * dSdY + dPhi2Dt * dTdY + dPhi2Du * dUdY ;
  gradZ[1] = dPhi2Ds * dSdZ + dPhi2Dt * dTdZ + dPhi2Du * dUdZ ;
  gradX[2] = dPhi3Ds * dSdX + dPhi3Dt * dTdX + dPhi3Du * dUdX ;
  gradY[2] = dPhi3Ds * dSdY + dPhi3Dt * dTdY + dPhi3Du * dUdY ;
  gradZ[2] = dPhi3Ds * dSdZ + dPhi3Dt * dTdZ + dPhi3Du * dUdZ ;
  gradX[3] = dPhi4Ds * dSdX + dPhi4Dt * dTdX + dPhi4Du * dUdX ;
  gradY[3] = dPhi4Ds * dSdY + dPhi4Dt * dTdY + dPhi4Du * dUdY ;
  gradZ[3] = dPhi4Ds * dSdZ + dPhi4Dt * dTdZ + dPhi4Du * dUdZ ;
  gradX[4] = dPhi5Ds * dSdX + dPhi5Dt * dTdX + dPhi5Du * dUdX ;
  gradY[4] = dPhi5Ds * dSdY + dPhi5Dt * dTdY + dPhi5Du * dUdY ;
  gradZ[4] = dPhi5Ds * dSdZ + dPhi5Dt * dTdZ + dPhi5Du * dUdZ ;
  gradX[5] = dPhi6Ds * dSdX + dPhi6Dt * dTdX + dPhi6Du * dUdX ;
  gradY[5] = dPhi6Ds * dSdY + dPhi6Dt * dTdY + dPhi6Du * dUdY ;
  gradZ[5] = dPhi6Ds * dSdZ + dPhi6Dt * dTdZ + dPhi6Du * dUdZ ;
  for ( i = 0 ; i < 6 ; i++ ) {
    sum       += variable[i] ;
    gradientX += variable[i] * gradX[i] ;
    gradientY += variable[i] * gradY[i] ;
    gradientZ += variable[i] * gradZ[i] ;
  }
  fluxLimiter = sqrt( gradientX * gradientX + gradientY * gradientY +
		      gradientZ * gradientZ ) / sum ;
  return( fluxLimiter ) ;
}
