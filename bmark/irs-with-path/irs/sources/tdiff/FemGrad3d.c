#include <math.h>
#include "irs.h"
#include "irstdiff.h"
void FemHexahedron( double x[8],     double y[8],     double z[8],
		    double gradX[8], double gradY[8], double gradZ[8] )
{
  double dSdX, dSdY, dSdZ;
  double dTdX, dTdY, dTdZ;
  double dUdX, dUdY, dUdZ;
  double dPhi1Ds = -0.25 ;
  double dPhi1Dt = -0.25 ;
  double dPhi1Du = -0.25 ;
  double dPhi2Ds =  0.25 ;
  double dPhi2Dt = -0.25 ;
  double dPhi2Du = -0.25 ;
  double dPhi3Ds =  0.25 ;
  double dPhi3Dt =  0.25 ;
  double dPhi3Du = -0.25 ;
  double dPhi4Ds = -0.25 ;
  double dPhi4Dt =  0.25 ;
  double dPhi4Du = -0.25 ;
  double dPhi5Ds = -0.25 ;
  double dPhi5Dt = -0.25 ;
  double dPhi5Du =  0.25 ;
  double dPhi6Ds =  0.25 ;
  double dPhi6Dt = -0.25 ;
  double dPhi6Du =  0.25 ;
  double dPhi7Ds =  0.25 ;
  double dPhi7Dt =  0.25 ;
  double dPhi7Du =  0.25 ;
  double dPhi8Ds = -0.25 ;
  double dPhi8Dt =  0.25 ;
  double dPhi8Du =  0.25 ;
  double dXdS    = 0.25 * (x[6] - x[7] + x[5] - x[4] + x[2] - x[3] + x[1] - x[0]) ;
  double dXdT    = 0.25 * (x[7] - x[4] + x[6] - x[5] + x[3] - x[0] + x[2] - x[1]) ;
  double dXdU    = 0.25 * (x[7] - x[3] + x[6] - x[2] + x[5] - x[1] + x[4] - x[0]) ;
  double dYdS    = 0.25 * (y[6] - y[7] + y[5] - y[4] + y[2] - y[3] + y[1] - y[0]) ;
  double dYdT    = 0.25 * (y[7] - y[4] + y[6] - y[5] + y[3] - y[0] + y[2] - y[1]) ;
  double dYdU    = 0.25 * (y[7] - y[3] + y[6] - y[2] + y[5] - y[1] + y[4] - y[0]) ;
  double dZdS    = 0.25 * (z[6] - z[7] + z[5] - z[4] + z[2] - z[3] + z[1] - z[0]) ;
  double dZdT    = 0.25 * (z[7] - z[4] + z[6] - z[5] + z[3] - z[0] + z[2] - z[1]) ;
  double dZdU    = 0.25 * (z[7] - z[3] + z[6] - z[2] + z[5] - z[1] + z[4] - z[0]) ;
  double jacobian = dXdS * ( dYdT * dZdU - dYdU * dZdT ) +
                    dYdS * ( dZdT * dXdU - dZdU * dXdT ) +
                    dZdS * ( dXdT * dYdU - dXdU * dYdT ) ;
  jacobian = 1.0 / jacobian;
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
  gradX[4] = dPhi5Ds * dSdX + dPhi5Dt * dTdX + dPhi5Du * dUdX ;
  gradY[4] = dPhi5Ds * dSdY + dPhi5Dt * dTdY + dPhi5Du * dUdY ;
  gradZ[4] = dPhi5Ds * dSdZ + dPhi5Dt * dTdZ + dPhi5Du * dUdZ ;
  gradX[5] = dPhi6Ds * dSdX + dPhi6Dt * dTdX + dPhi6Du * dUdX ;
  gradY[5] = dPhi6Ds * dSdY + dPhi6Dt * dTdY + dPhi6Du * dUdY ;
  gradZ[5] = dPhi6Ds * dSdZ + dPhi6Dt * dTdZ + dPhi6Du * dUdZ ;
  gradX[6] = dPhi7Ds * dSdX + dPhi7Dt * dTdX + dPhi7Du * dUdX ;
  gradY[6] = dPhi7Ds * dSdY + dPhi7Dt * dTdY + dPhi7Du * dUdY ;
  gradZ[6] = dPhi7Ds * dSdZ + dPhi7Dt * dTdZ + dPhi7Du * dUdZ ;
  gradX[7] = dPhi8Ds * dSdX + dPhi8Dt * dTdX + dPhi8Du * dUdX ;
  gradY[7] = dPhi8Ds * dSdY + dPhi8Dt * dTdY + dPhi8Du * dUdY ;
  gradZ[7] = dPhi8Ds * dSdZ + dPhi8Dt * dTdZ + dPhi8Du * dUdZ ;
}
void FemTetrahedron( double x[4],     double y[4],     double z[4],
		     double gradX[4], double gradY[4], double gradZ[4] )
{
  double dSdX, dSdY, dSdZ ;
  double dTdX, dTdY, dTdZ ;
  double dUdX, dUdY, dUdZ ;
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
}
void TetVolume( double x[4], double y[4], double z[4], double *VolumeTet )
{
   double sixth = 1.0 / 6.0 ;
   double dx01 = x[1] - x[0] ;
   double dx02 = x[2] - x[0] ;
   double dx03 = x[3] - x[0] ;
   double dy01 = y[1] - y[0] ;
   double dy02 = y[2] - y[0] ;
   double dy03 = y[3] - y[0] ;
   double dz01 = z[1] - z[0] ;
   double dz02 = z[2] - z[0] ;
   double dz03 = z[3] - z[0] ;
   *VolumeTet = sixth * ( dx01 * ( dy02 * dz03 - dy03 * dz02 ) -
                          dx02 * ( dy01 * dz03 - dy03 * dz01 ) +
                          dx03 * ( dy01 * dz02 - dy02 * dz01 ) ) ;
}
void FemPrism( double x[6],     double y[6],     double z[6],
	       double gradX[6], double gradY[6], double gradZ[6] )
{
  double half = 0.5, third = 1.0 / 3.0, zero = 0.0 ;
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
}
void ResortPrism( double a[6], double b[6], double c[6],
		  double d[6], int indexlist[6] )
{
   int i, j, k, faceNumber ;
   int oldIndexlist[6], faceCount[6] ;
   double *reSortThis[4], temp[6] ;
   int face0[4] = {0, 1, 2, 3} ;
   int face1[4] = {0, 1, 4, 5} ;
   int face2[4] = {0, 3, 4, 7} ;
   int face3[4] = {4, 5, 6, 7} ;
   int face4[4] = {1, 2, 5, 6} ;
   int face5[4] = {2, 3, 6, 7} ;
   int node[8][3] = {0, 1, 2,
	 	     0, 1, 4,
		     0, 4, 5,
		     0, 2, 5,
		     1, 2, 3,
		     1, 3, 4,
		     3, 4, 5,
		     2, 3, 5} ;
   for ( i = 0 ; i < 6 ; i++ ) {
      oldIndexlist[i] = indexlist[i] ;
      faceCount[i]    = 0 ;
   }
   for ( i = 0 ; i < 6 ; i++ ) {
      int index = indexlist[i] ;
      faceNumber = node[index][0] ;
      faceCount[faceNumber]++ ;
      faceNumber = node[index][1] ;
      faceCount[faceNumber]++ ;
      faceNumber = node[index][2] ;
      faceCount[faceNumber]++ ;
   }
   if ( faceCount[0] == 4 ) {
      if        ( faceCount[1] == 4 ) {
         indexlist[0] = 0 ;
         indexlist[1] = 3 ;
         indexlist[2] = 4 ;
         indexlist[3] = 1 ;
         indexlist[4] = 2 ;
         indexlist[5] = 5 ;
      } else if ( faceCount[2] == 4 ) {
         indexlist[0] = 0 ;
         indexlist[1] = 4 ;
         indexlist[2] = 1 ;
         indexlist[3] = 3 ;
         indexlist[4] = 7 ;
         indexlist[5] = 2 ;
      } else if ( faceCount[4] == 4 ) {
         indexlist[0] = 1 ;
         indexlist[1] = 5 ;
         indexlist[2] = 0 ;
         indexlist[3] = 2 ;
         indexlist[4] = 6 ;
         indexlist[5] = 3 ;
      } else if ( faceCount[5] == 4 ) {
         indexlist[0] = 2 ;
         indexlist[1] = 6 ;
         indexlist[2] = 1 ;
         indexlist[3] = 3 ;
         indexlist[4] = 7 ;
         indexlist[5] = 0 ;
      }
   } else if ( faceCount[1] == 4 ) {
      if        ( faceCount[2] == 4 ) {
         indexlist[0] = 0 ;
         indexlist[1] = 3 ;
         indexlist[2] = 1 ;
         indexlist[3] = 4 ;
         indexlist[4] = 7 ;
         indexlist[5] = 5 ;
      } else if ( faceCount[3] == 4 ) {
         indexlist[0] = 4 ;
         indexlist[1] = 7 ;
         indexlist[2] = 0 ;
         indexlist[3] = 5 ;
         indexlist[4] = 6 ;
         indexlist[5] = 1 ;
      } else if ( faceCount[4] == 4 ) {
         indexlist[0] = 1 ;
         indexlist[1] = 0 ;
         indexlist[2] = 2 ;
         indexlist[3] = 5 ;
         indexlist[4] = 4 ;
         indexlist[5] = 6 ;
      }
   } else if ( faceCount[2] == 4 ) {
      if        ( faceCount[3] == 4 ) {
         indexlist[0] = 4 ;
         indexlist[1] = 0 ;
         indexlist[2] = 5 ;
         indexlist[3] = 7 ;
         indexlist[4] = 3 ;
         indexlist[5] = 6 ;
      } else if ( faceCount[5] == 4 ) {
         indexlist[0] = 3 ;
         indexlist[1] = 2 ;
         indexlist[2] = 0 ;
         indexlist[3] = 7 ;
         indexlist[4] = 6 ;
         indexlist[5] = 4 ;
      }
   } else if ( faceCount[3] == 4 ) {
      if        ( faceCount[4] == 4 ) {
         indexlist[0] = 5 ;
         indexlist[1] = 4 ;
         indexlist[2] = 1 ;
         indexlist[3] = 6 ;
         indexlist[4] = 7 ;
         indexlist[5] = 2 ;
      } else if ( faceCount[5] == 4 ) {
         indexlist[0] = 6 ;
         indexlist[1] = 5 ;
         indexlist[2] = 2 ;
         indexlist[3] = 7 ;
         indexlist[4] = 4 ;
         indexlist[5] = 3 ;
      }
   } else if ( faceCount[4] == 4 ) {
      indexlist[0] = 2 ;
      indexlist[1] = 1 ;
      indexlist[2] = 3 ;
      indexlist[3] = 6 ;
      indexlist[4] = 5 ;
      indexlist[5] = 7 ;
   }
   reSortThis[0] = a ;
   reSortThis[1] = b ;
   reSortThis[2] = c ;
   reSortThis[3] = d ;
   for ( j = 0 ; j < 4 ; j++ ) {
      for ( i = 0 ; i < 6 ; i++ ) {
         temp[i] = reSortThis[j][i] ;
      }
      for ( i = 0 ; i < 6 ; i++ ) {
         for ( k = 0 ; k < 6 ; k++ ) {
	    if ( oldIndexlist[i] == indexlist[k] ) {
	       reSortThis[j][k] = temp[i] ;
	       break ;
	    }
	 }
      }
   }
}
void PrismVolume( double x[4], double y[4], double z[4], double *VolumePrism )
{
   double xt[4], yt[4], zt[4] ;
   double partialVolume, sixth = 1.0 / 6.0 ;
   double xc    = sixth * ( x[0] + x[1] + x[2] + x[3] + x[4] + x[5] ) ;
   double yc    = sixth * ( y[0] + y[1] + y[2] + y[3] + y[4] + y[5] ) ;
   double zc    = sixth * ( z[0] + z[1] + z[2] + z[3] + z[4] + z[5] ) ;
   double x0134 = 0.25  * ( x[0] + x[1] + x[3] + x[4] ) ;
   double y0134 = 0.25  * ( y[0] + y[1] + y[3] + y[4] ) ;
   double z0134 = 0.25  * ( z[0] + z[1] + z[3] + z[4] ) ;
   double x0235 = 0.25  * ( x[0] + x[2] + x[3] + x[5] ) ;
   double y0235 = 0.25  * ( y[0] + y[2] + y[3] + y[5] ) ;
   double z0235 = 0.25  * ( z[0] + z[2] + z[3] + z[5] ) ;
   double x1245 = 0.25  * ( x[1] + x[2] + x[4] + x[5] ) ;
   double y1245 = 0.25  * ( y[1] + y[2] + y[4] + y[5] ) ;
   double z1245 = 0.25  * ( z[1] + z[2] + z[4] + z[5] ) ;
   *VolumePrism = 0.0 ;
   xt[0] = xc ; yt[0] = yc ; zt[0] = zc ;
   xt[1] = x[0] ; yt[1] = y[0] ; zt[1] = z[0] ;
   xt[2] = x[1] ; yt[2] = y[1] ; zt[2] = z[1] ;
   xt[3] = x[2] ; yt[3] = y[2] ; zt[3] = z[2] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[4] ; yt[1] = y[4] ; zt[1] = z[4] ;
   xt[2] = x[3] ; yt[2] = y[3] ; zt[2] = z[3] ;
   xt[3] = x[5] ; yt[3] = y[5] ; zt[3] = z[5] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[3] = x0235 ; yt[3] = y0235 ; zt[3] = z0235 ;
   xt[1] = x[0] ; yt[1] = y[0] ; zt[1] = z[0] ;
   xt[2] = x[2] ; yt[2] = y[2] ; zt[2] = z[2] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[2] ; yt[1] = y[2] ; zt[1] = z[2] ;
   xt[2] = x[5] ; yt[2] = y[5] ; zt[2] = z[5] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[5] ; yt[1] = y[5] ; zt[1] = z[5] ;
   xt[2] = x[3] ; yt[2] = y[3] ; zt[2] = z[3] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[3] ; yt[1] = y[3] ; zt[1] = z[3] ;
   xt[2] = x[0] ; yt[2] = y[0] ; zt[2] = z[0] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[3] = x1245 ; yt[3] = y1245 ; zt[3] = z1245 ;
   xt[1] = x[2] ; yt[1] = y[2] ; zt[1] = z[2] ;
   xt[2] = x[1] ; yt[2] = y[1] ; zt[2] = z[1] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[5] ; yt[1] = y[5] ; zt[1] = z[5] ;
   xt[2] = x[2] ; yt[2] = y[2] ; zt[2] = z[2] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[4] ; yt[1] = y[4] ; zt[1] = z[4] ;
   xt[2] = x[5] ; yt[2] = y[5] ; zt[2] = z[5] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[1] ; yt[1] = y[1] ; zt[1] = z[1] ;
   xt[2] = x[4] ; yt[2] = y[4] ; zt[2] = z[4] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[3] = x0134 ; yt[3] = y0134 ; zt[3] = z0134 ;
   xt[1] = x[1] ; yt[1] = y[1] ; zt[1] = z[1] ;
   xt[2] = x[0] ; yt[2] = y[0] ; zt[2] = z[0] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[0] ; yt[1] = y[0] ; zt[1] = z[0] ;
   xt[2] = x[3] ; yt[2] = y[3] ; zt[2] = z[3] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[3] ; yt[1] = y[3] ; zt[1] = z[3] ;
   xt[2] = x[4] ; yt[2] = y[4] ; zt[2] = z[4] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
   xt[1] = x[4] ; yt[1] = y[4] ; zt[1] = z[4] ;
   xt[2] = x[1] ; yt[2] = y[1] ; zt[2] = z[1] ;
   TetVolume( xt, yt, zt, &partialVolume ) ;
   *VolumePrism += partialVolume ;
}
