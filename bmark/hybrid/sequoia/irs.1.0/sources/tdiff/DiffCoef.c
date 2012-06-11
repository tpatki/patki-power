#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "irsdefs.h"
#include "DiffusionData.hh"
#include "FunctionTimer.h"
#include "RadiationData.h"
static void DiffCoef_2D( RadiationData_t *rblk, DiffusionData_t *tblk,
                         Domain_t *domain ) ;
static void DiffCoef_3D( RadiationData_t *rblk, DiffusionData_t *tblk,
                         Domain_t *domain ) ;
void DiffCoef( RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain )
{
   if ( ndims == 2 ) {
      DiffCoef_2D( rblk, tblk, domain ) ;
   } else {
      DiffCoef_3D( rblk, tblk, domain ) ;
   }
}
static void DiffCoef_2D( RadiationData_t *rblk, DiffusionData_t *tblk,
                         Domain_t *domain )
{
   char *me = "DiffCoef_2D" ;
   int i, ii, jj, ibc ;
   int jp   = domain->jp   ;
   int imin = domain->imin ;
   int imax = domain->imax ;
   int jmin = domain->jmin ;
   int jmax = domain->jmax ;
   int *ndx, *iregmi, *iregmj ;
   double *cpi,    *cpj   ;
   double *cpimj,  *cpjmi ;
   double *dwi,    *dwj   ;
   double *dwimi,  *dwjmj ;
   double *wgti,  *wgtj   ;
   double *krl, *krr, *krb, *krf ;
   double *x1, *x2, *x3, *x4 ;
   double *y1, *y2, *y3, *y4 ;
   double *rflmtp ;
   double *rcbrm ;
   double du, dv ;
   double kave, ku, kl, fthd, flmtx, wsum, weight, s ;
   double myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash) 
   fthd = 3.0 * rdifmiln ;
   cpi   = MALLOT(double,domain->nnalls) ;
   cpj   = MALLOT(double,domain->nnalls) ;
   dwi   = MALLOT(double,domain->nnalls) ;
   dwj   = MALLOT(double,domain->nnalls) ;
   dwimi = dwi - 1 ;
   dwjmj = dwj - domain->jp ;
   iregmi = domain->ireg - 1 ;
   iregmj = domain->ireg - domain->jp ;
   rcbrm = rblk->cbr - 1 ;
   krl = tblk->diffcl ;
   krr = tblk->diffcr - 1 ;
   krb = tblk->diffcb ;
   krf = tblk->diffcf - domain->jp ;
   NDSET2D(domain->x,x1,x2,x3,x4) ;
   NDSET2D(domain->y,y1,y2,y3,y4) ;
   for ( jj = jmin - 1 ; jj <= jmax ; jj++ ) {
      for ( ii = imin - 1 ; ii <= imax ; ii++ ) {
         i = ii + jj * jp ;
         du = x2[i] + x3[i] - x4[i] - x1[i] ;
         dv = y2[i] + y3[i] - y4[i] - y1[i] ;
         dwi[i] = domain->area[i] / ( sqrt( du * du + dv * dv ) + ptiny ) ;
         du = x1[i] + x2[i] - x3[i] - x4[i] ;
         dv = y1[i] + y2[i] - y3[i] - y4[i] ;
         dwj[i] = domain->area[i] / ( sqrt( du * du + dv * dv ) + ptiny ) ;
      }
   }
   myflops += 36.0 * ( imax - imin + 2 ) * ( jmax - jmin + 2 ) ;

   rflmtp = tblk->flmt + domain->jp ;

   for ( jj = jmin - 1 ; jj <= jmax ; jj++ ) {
      for ( ii = imin ; ii <= imax ; ii++ ) {
         i    = ii + jj * jp ;
         ku   = krr[i] * dwimi[i] ;
         kl   = krl[i] * dwi[i]   ;
         kave = ku + kl ;
         wsum = dwi[i] + dwimi[i] ;
         if ( iregmi[i] == 0 ) {
            kave *= ( 1.0 + fthd / ( kl + ptiny ) ) ;
         } else if ( domain->ireg[i] == 0 ) {
            kave *= ( 1.0 + fthd / ( ku + ptiny ) ) ;
         }
         flmtx = 0.5 * ( tblk->flmt[i] + rflmtp[i] ) * wsum ;
         kave += flmtx ;
         cpi[i] = wsum / ( kave + ptiny ) ;
      }
   }
   myflops += 13.0 * ( imax - imin + 1 ) * ( jmax - jmin + 2 ) ;
   rflmtp = tblk->flmt + 1 ;

   for ( jj = jmin ; jj <= jmax ; jj++ ) {
      for ( ii = imin - 1 ; ii <= imax ; ii++ ) {
         i    = ii + jj * jp ;
         ku   = krf[i] * dwjmj[i] ;
         kl   = krb[i] * dwj[i]   ;
         kave = ku + kl ;
         wsum = dwj[i] + dwjmj[i] ;
         if ( iregmj[i] == 0 ) {
            kave *= ( 1.0 + fthd / ( kl + ptiny ) ) ;
         } else if ( domain->ireg[i] == 0 ) {
            kave *= ( 1.0 + fthd / ( ku + ptiny ) ) ;
         }
         flmtx = 0.5 * ( tblk->flmt[i] + rflmtp[i] ) * wsum ;
         kave += flmtx ;
         cpj[i] = wsum / ( kave + ptiny ) ;
      }
   }
   myflops += 13.0 * ( imax - imin + 2 ) * ( jmax - jmin + 1 ) ;
      for ( jj = jmin ; jj <= jmax ; jj++ ) {
         for ( ii = imin ; ii <= imax ; ii++ ) {
            i = ii + jj * jp ;
            rblk->ccl[i] *= cpi[i] ;
            rblk->cbc[i] *= cpj[i] ;
            s = 0.25 * ( 1.0 / ( cpi[i]    + ptiny )
                       + 1.0 / ( cpi[i-jp] + ptiny )
                       + 1.0 / ( cpj[i]    + ptiny )
                       + 1.0 / ( cpj[i-1]  + ptiny ) ) ;
            s = 1.0 / ( s + ptiny ) ;
            s = MAX( s, 0.0 ) ;
            rblk->cbl [i] *= s ;
            rcbrm[i]      *= s ;
         }
      }
      myflops += 33.0 *  ( imax - imin + 1 ) * ( jmax - jmin + 1 ) ;
   FREEMEM(cpi) ;
   FREEMEM(cpj) ;
   FREEMEM(dwi) ;
   FREEMEM(dwj) ;

   FT_FINALIZE(me, domain->hash, myflops)
}
static void DiffCoef_3D( RadiationData_t *rblk, DiffusionData_t *tblk, Domain_t *domain )
{
   char *me = "DiffCoef_3D" ;
   int i, ii, jj, kk, ibc ;
   int jp   = domain->jp   ;
   int kp   = domain->kp   ;
   int imin = domain->imin ;
   int imax = domain->imax ;
   int jmin = domain->jmin ;
   int jmax = domain->jmax ;
   int kmin = domain->kmin ;
   int kmax = domain->kmax ;
   int *iregmi, *iregmj, *iregmk ;
   double *cpi,   *cpj,   *cpk   ;
   double *dwi,   *dwj,   *dwk   ;
   double *dwimi, *dwjmj, *dwkmk ;
   double *wgti,  *wgtj,  *wgtk  ;
   double *krl, *krr, *krb, *krf, *krd, *kru ;
   double *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8 ;
   double *y1, *y2, *y3, *y4, *y5, *y6, *y7, *y8 ;
   double *z1, *z2, *z3, *z4, *z5, *z6, *z7, *z8 ;
   double *flmt1, *flmt2, *flmt3, *flmt4 ;
   double *rcbrm, *rdcrm, *rdfcm ;
   double xa, ya, za, xb, yb, zb, xc, yc, zc, area ;
   double kave, ku, kl, fthd, flmtx, wsum, weight, s ;
   double twelfth = 1.0 / 12.0, myflops = 0.0 ;
   FT_INITIALIZE(me, domain->hash)
   fthd = 3.0 * rdifmiln ;
   cpi   = MALLOT(double,domain->nnalls) ;
   cpj   = MALLOT(double,domain->nnalls) ;
   cpk   = MALLOT(double,domain->nnalls) ;
   dwi   = MALLOT(double,domain->nnalls) ;
   dwj   = MALLOT(double,domain->nnalls) ;
   dwk   = MALLOT(double,domain->nnalls) ;
   dwimi = dwi - 1  ;
   dwjmj = dwj - jp ;
   dwkmk = dwk - kp ;
   krl = tblk->diffcl      ;
   krr = tblk->diffcr - 1  ;
   krb = tblk->diffcb      ;
   krf = tblk->diffcf - jp ;
   krd = tblk->diffcd      ;
   kru = tblk->diffcu - kp ;
   iregmi = domain->ireg - 1  ;
   iregmj = domain->ireg - jp ;
   iregmk = domain->ireg - kp ;
   rcbrm = rblk->cbr - 1  ;
   rdcrm = rblk->dcr - 1  ;
   rdfcm = rblk->dfc - jp ;
   NDSET3D(domain->x,x1,x2,x3,x4,x5,x6,x7,x8) ;
   NDSET3D(domain->y,y1,y2,y3,y4,y5,y6,y7,y8) ;
   NDSET3D(domain->z,z1,z2,z3,z4,z5,z6,z7,z8) ;
   for ( kk = kmin - 1 ; kk <= kmax ; kk++ ) {
      for ( jj = jmin - 1 ; jj <= jmax ; jj++ ) {
	 for ( ii = imin - 1 ; ii <= imax ; ii++ ) {
	    i = ii + jj * jp + kk * kp ;
            xa = x1[i] + x4[i] + x5[i] + x8[i] - x2[i] - x3[i] - x6[i] - x7[i] ;
            ya = y1[i] + y4[i] + y5[i] + y8[i] - y2[i] - y3[i] - y6[i] - y7[i] ;
            za = z1[i] + z4[i] + z5[i] + z8[i] - z2[i] - z3[i] - z6[i] - z7[i] ;
            xb = x1[i] + x2[i] + x3[i] + x4[i] - x5[i] - x6[i] - x7[i] - x8[i] ;
            yb = y1[i] + y2[i] + y3[i] + y4[i] - y5[i] - y6[i] - y7[i] - y8[i] ;
            zb = z1[i] + z2[i] + z3[i] + z4[i] - z5[i] - z6[i] - z7[i] - z8[i] ;
            CROSSPROD(xc,yc,zc,xa,ya,za,xb,yb,zb) ;
            area = sqrt( xc * xc + yc * yc + zc * zc ) ;
            if ( area <= 0.0 ) {
               dwi[i] = 0.0 ;
            } else {
               dwi[i] = 8.0 * domain->vol[i] / ( area + ptiny ) ;
            }
            xa = x1[i] + x2[i] + x3[i] + x4[i] - x5[i] - x6[i] - x7[i] - x8[i] ;
            ya = y1[i] + y2[i] + y3[i] + y4[i] - y5[i] - y6[i] - y7[i] - y8[i] ;
            za = z1[i] + z2[i] + z3[i] + z4[i] - z5[i] - z6[i] - z7[i] - z8[i] ;
            xb = x3[i] + x4[i] + x7[i] + x8[i] - x1[i] - x2[i] - x5[i] - x6[i] ;
            yb = y3[i] + y4[i] + y7[i] + y8[i] - y1[i] - y2[i] - y5[i] - y6[i] ;
            zb = z3[i] + z4[i] + z7[i] + z8[i] - z1[i] - z2[i] - z5[i] - z6[i] ;
            CROSSPROD(xc,yc,zc,xa,ya,za,xb,yb,zb) ;
            area = sqrt( xc * xc + yc * yc + zc * zc ) ;
            if ( area <= 0.0 ) {
               dwj[i] = 0.0 ;
            } else {
               dwj[i] = 8.0 * domain->vol[i] / ( area + ptiny ) ;
            }
            xa = x3[i] + x4[i] + x7[i] + x8[i] - x1[i] - x2[i] - x5[i] - x6[i] ;
            ya = y3[i] + y4[i] + y7[i] + y8[i] - y1[i] - y2[i] - y5[i] - y6[i] ;
            za = z3[i] + z4[i] + z7[i] + z8[i] - z1[i] - z2[i] - z5[i] - z6[i] ;
            xb = x1[i] + x4[i] + x5[i] + x8[i] - x2[i] - x3[i] - x6[i] - x7[i] ;
            yb = y1[i] + y4[i] + y5[i] + y8[i] - y2[i] - y3[i] - y6[i] - y7[i] ;
            zb = z1[i] + z4[i] + z5[i] + z8[i] - z2[i] - z3[i] - z6[i] - z7[i] ;
            CROSSPROD(xc,yc,zc,xa,ya,za,xb,yb,zb) ;
            area = sqrt( xc * xc + yc * yc + zc * zc ) ;
            if ( area <= 0.0 ) {
               dwk[i] = 0.0 ;
            } else {
               dwk[i] = 8.0 * domain->vol[i] / ( area + ptiny ) ;
            }
	 }
      }
   }
   myflops += 198.0 * ( imax - imin + 2 ) * ( jmax - jmin + 2 )
                    * ( kmax - kmin + 2 ) ;

   flmt1 = tblk->flmt      ;
   flmt2 = tblk->flmt + jp ;
   flmt3 = flmt1      + kp ;
   flmt4 = flmt2      + kp ;

   for ( kk = kmin - 1 ; kk <= kmax ; kk++ ) {
      for ( jj = jmin - 1 ; jj <= jmax ; jj++ ) {
	 for ( ii = imin ; ii <= imax ; ii++ ) {
	    i    = ii + jj * jp + kk * kp ;
            ku   = krr[i] * dwimi[i] ;
            kl   = krl[i] * dwi[i]   ;
            kave = ku + kl ;
            wsum = dwi[i] + dwimi[i] ;
            if ( iregmi[i] == 0 ) {
               kave *= ( 1.0 + fthd / ( kl + ptiny ) ) ;
            } else if ( domain->ireg[i] == 0 ) {
               kave *= ( 1.0 + fthd / ( ku + ptiny ) ) ;
            }
            flmtx  = 0.25  * ( flmt1[i] + flmt2[i] + flmt3[i] + flmt4[i] ) ;
            flmtx *= wsum ;
            cpi[i] = wsum / ( kave + flmtx + ptiny ) ;
	 }
      }
   }
   myflops += 15.0 * ( imax - imin + 1 ) * ( jmax - jmin + 2 )
                   * ( kmax - kmin + 2 ) ;
   flmt1 = tblk->flmt      ;
   flmt2 = tblk->flmt + 1  ;
   flmt3 = flmt1      + kp ;
   flmt4 = flmt2      + kp ;

   for ( kk = kmin - 1 ; kk <= kmax ; kk++ ) {
      for ( jj = jmin ; jj <= jmax ; jj++ ) {
	 for ( ii = imin - 1 ; ii <= imax ; ii++ ) {
	    i    = ii + jj * jp + kk * kp ;
            ku   = krf[i] * dwjmj[i] ;
            kl   = krb[i] * dwj[i]   ;
            kave = ku + kl ;
            wsum = dwj[i] + dwjmj[i] ;
            if ( iregmj[i] == 0 ) {
               kave *= ( 1.0 + fthd / ( kl + ptiny ) ) ;
            } else if ( domain->ireg[i] == 0 )  {
               kave *= ( 1.0 + fthd / ( ku + ptiny ) ) ;
            }
            flmtx  = 0.25  * ( flmt1[i] + flmt2[i] + flmt3[i] + flmt4[i] ) ;
            flmtx *= wsum ;
            cpj[i] = wsum / ( kave + flmtx + ptiny ) ;
	 }
      }
   }
   myflops += 15.0 * ( imax - imin + 2 ) * ( jmax - jmin + 1 )
                   * ( kmax - kmin + 2 ) ;
   flmt1 = tblk->flmt      ;
   flmt2 = tblk->flmt + 1  ;
   flmt3 = flmt1      + jp ;
   flmt4 = flmt2      + jp ;

   for ( kk = kmin ; kk <= kmax ; kk++ ) {
      for ( jj = jmin - 1 ; jj <= jmax ; jj++ ) {
	 for ( ii = imin - 1 ; ii <= imax ; ii++ ) {
	    i    = ii + jj * jp + kk * kp ;
            ku   = kru[i]* dwkmk[i] ;
            kl   = krd[i]* dwk[i]   ;
            kave = ku + kl ;
            if ( iregmk[i] == 0 ) {
               kave *= ( 1.0 + fthd / ( kl + ptiny ) ) ;
            } else if ( domain->ireg[i] == 0 ) {
               kave *= ( 1.0 + fthd / ( ku + ptiny ) ) ;
            }
            flmtx = 0.25  * ( flmt1[i] + flmt2[i] + flmt3[i] + flmt4[i] ) ;
            flmtx = flmtx * ( dwk[i] + dwkmk[i] ) ;
            cpk[i] = ( dwk[i] + dwkmk[i] ) / ( kave + flmtx + ptiny ) ;
	 }
      }
   }
   myflops += 16.0 * ( imax - imin + 2 ) * ( jmax - jmin + 2 )
                   * ( kmax - kmin + 1 ) ;
      for ( kk = kmin ; kk <= kmax ; kk++ ) {
         for ( jj = jmin ; jj <= jmax ; jj++ ) {
	    for ( ii = imin ; ii <= imax ; ii++ ) {
	       i = ii + jj * jp + kk * kp ;
               rblk->ccl[i] *= cpi[i] ;
               rblk->cbc[i] *= cpj[i] ;
               rblk->dcc[i] *= cpk[i] ;
               s = 0.25 * ( 1.0 / ( cpi[i]    + ptiny )
                          + 1.0 / ( cpi[i-jp] + ptiny )
                          + 1.0 / ( cpj[i]    + ptiny )
                          + 1.0 / ( cpj[i-1]  + ptiny ) ) ;
               s = 1.0 / ( s + ptiny ) ;
               s = MAX( s, 0.0 ) ;
               rblk->cbl [i] *= s ;
               rcbrm[i]      *= s ;
               s = 0.25 * ( 1.0 / ( cpi[i]    + ptiny )
                          + 1.0 / ( cpi[i-kp] + ptiny )
                          + 1.0 / ( cpk[i]    + ptiny )
                          + 1.0 / ( cpk[i-1]  + ptiny ) ) ;
               s = 1.0 / ( s + ptiny ) ;
               s = MAX( s, 0.0 ) ;
               rblk->dcl [i] *= s ;
               rdcrm[i]      *= s ;
               s = 0.25 * ( 1.0 / ( cpj[i]    + ptiny )
                          + 1.0 / ( cpj[i-kp] + ptiny )
                          + 1.0 / ( cpk[i]    + ptiny )
                          + 1.0 / ( cpk[i-jp] + ptiny ) ) ;
               s = 1.0 / ( s + ptiny ) ;
               s = MAX( s, 0.0 ) ;
               rblk->dbc [i] *= s ;
               rdfcm[i]      *= s ;
               s = twelfth * ( 1.0 / ( cpi[i]       + ptiny )
		             + 1.0 / ( cpi[i-jp]    + ptiny )
		             + 1.0 / ( cpi[i-kp]    + ptiny )
		             + 1.0 / ( cpi[i-jp-kp] + ptiny )
		             + 1.0 / ( cpj[i]       + ptiny )
		             + 1.0 / ( cpj[i-1]     + ptiny )
		             + 1.0 / ( cpj[i-kp]    + ptiny )
		             + 1.0 / ( cpj[i-1-kp]  + ptiny )
		             + 1.0 / ( cpk[i]       + ptiny )
		             + 1.0 / ( cpk[i-1]     + ptiny )
		             + 1.0 / ( cpk[i-jp]    + ptiny )
		             + 1.0 / ( cpk[i-1-jp]  + ptiny ) ) ;
               s = 1.0 / ( s + ptiny ) ;
               s = MAX( s, 0.0 ) ;
               rblk->dbl[i]      *= s ;
               rblk->dbr[i-1]    *= s ;
               rblk->dfl[i-jp]   *= s ;
               rblk->dfr[i-jp-1] *= s ;
	    }
         }

      myflops += 177.0 * ( imax - imin + 1 ) * ( jmax - jmin + 1 )
                       * ( kmax - kmin + 1 ) ;
   } 
   FREEMEM(cpi) ;
   FREEMEM(cpj) ;
   FREEMEM(cpk) ;
   FREEMEM(dwi) ;
   FREEMEM(dwj) ;
   FREEMEM(dwk) ;

   FT_FINALIZE(me, domain->hash, myflops) 
}
