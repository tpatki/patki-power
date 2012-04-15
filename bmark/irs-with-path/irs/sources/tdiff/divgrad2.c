#include "irsdefs.h"
#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void divgrad2( double *x,    double *y,   Domain_t *domain, double *a1,
               double *b0,   double *b1,  double      *bm1,    double *phi,
               double *flmt, double umin, double      fscl  )
{
   char *me = "divgrad2";
   int i ;
   double *r1, *r2, *r3, *r4 ;
   double *z1, *z2, *z3, *z4 ;
   double *p1, *p2, *p3, *p4 ;
   double s1r, s2r, s3r, s4r ;
   double s1z, s2z, s3z, s4z ;
   double ar1, ar2, ar3, ar4 ;
   double w1,  w2,  norm, sdr, sdz, dz, dr ;
   double *t, *b, *rr, *l ;
   double *rc, *zc ;
   double armin ;
   double rp, ry, third, rb1, rb2, rb3, rb4 ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   armin = xcut * xcut ;
   rc = MALLOT(double,domain->nnalls) ;
   zc = MALLOT(double,domain->nnalls) ;
   for ( i = 0 ; i < domain->nnalls ; i++ ) {
      zc[i] = 0.0 ;
      rc[i] = 0.0 ;
   }
   NDSET2D(y,r1,r2,r3,r4)
   NDSET2D(x,z1,z2,z3,z4)
   for ( i = domain->fpz ; i <= domain->lpz ; i++ ) {
      rc[i] = 0.25 * ( r1[i] + r2[i] + r3[i] + r4[i] ) ;
      zc[i] = 0.25 * ( z1[i] + z2[i] + z3[i] + z4[i] ) ;
   }
   myflops += 8.0 *( domain->lpz - domain->fpz + 1 ) ;
   for ( i = 0 ; i < domain->nnalls ; i++ ) {
      a1[i]    = 0.0 ;
      b0[i]    = 0.0 ;
      b1[i]    = 0.0 ;
      bm1[i+1] = 0.0 ;
      flmt[i]  = 0.0 ;
   }
   ZNSET2D(rc,r1,r2,r3,r4)
   ZNSET2D(zc,z1,z2,z3,z4)
   ZNSET2D(phi,p1,p2,p3,p4) ;
   t  = a1 ;
   b  = a1 - domain->jp ;
   rr = b0 ;
   l  = b0 - 1 ;
   if ( ifplane == 1 ) {
      rp = 1.0 ;
      ry = 0.0 ;
   } else {
      rp = 0.0 ;
      ry = 1.0 ;
   }
   third = ry / 3.0 ;
   fscl *= 4.0 ;
   for ( i = domain->frn ; i <= domain->lpn ; i++ ) {
      s1r = r2[i] - r1[i] ;
      s2r = r3[i] - r2[i] ;
      s3r = r4[i] - r3[i] ;
      s4r = r1[i] - r4[i] ;
      s1z = z2[i] - z1[i] ;
      s2z = z3[i] - z2[i] ;
      s3z = z4[i] - z3[i] ;
      s4z = z1[i] - z4[i] ;   
      rb1 = rp + third * ( r4[i] + r1[i] + r2[i] ) ;
      rb2 = rp + third * ( r1[i] + r2[i] + r3[i] ) ;
      rb3 = rp + third * ( r2[i] + r3[i] + r4[i] ) ;
      rb4 = rp + third * ( r3[i] + r4[i] + r1[i] ) ;  
      ar1 = s4z * s1r - s4r * s1z ;
      ar2 = s1z * s2r - s1r * s2z ;
      ar3 = s2z * s3r - s2r * s3z ;
      ar4 = s3z * s4r - s3r * s4z ;   
      w1 = ar1 ;
      if ( ar3 < ar1   )  w1 = ar3 ;
      if ( w1  < armin )  w1 = 0.0 ;
      w2 = ar2 ;
      if ( ar4 < ar2   )  w2 = ar4 ;
      if ( w2  < armin )  w2 = 0.0 ;  
      norm = 0.5 / (w1 + w2 + ptiny) ;
      w1  *= norm ;
      w2  *= norm ;                   
      ar1 = w1 / ( fabs(ar1) + ptiny ) ;
      ar2 = w2 / ( fabs(ar2) + ptiny ) ;
      ar3 = w1 / ( fabs(ar3) + ptiny ) ;
      ar4 = w2 / ( fabs(ar4) + ptiny ) ; 
      sdr = r2[i] - r4[i] ;
      sdz = z2[i] - z4[i] ;           
      dr   = s4r * p2[i] + s1r * p4[i] - sdr * p1[i] ; 
      dz   = s4z * p2[i] + s1z * p4[i] - sdz * p1[i] ;
      norm = sqrt( dr * dr + dz * dz ) ;   
      flmt[i] += ar1 * norm ;         
      dr = s2r*p4[i] + s3r*p2[i] + sdr*p3[i] ;
      dz = s2z*p4[i] + s3z*p2[i] + sdz*p3[i] ;
      norm = sqrt(dr*dr + dz*dz) ;
      flmt[i] += ar3 * norm ;         
      ar1 *= rb1 ;
      ar3 *= rb3 ;                    
      b[i]   += ( sdr * s1r + sdz * s1z ) * ar1 ;
      t[i]   -= ( s3r * sdr + s3z * sdz ) * ar3 ;
      l[i]   -= ( s2r * sdr + s2z * sdz ) * ar3 ;
      rr[i]  += ( s4r * sdr + s4z * sdz ) * ar1 ;
      b1[i]  -= ( s1r * s4r + s1z * s4z ) * ar1 ;
      b1[i]  -= ( s2r * s3r + s2z * s3z ) * ar3 ; 
      sdr = r3[i] - r1[i] ;
      sdz = z3[i] - z1[i] ;              
      dr   = s1r * p3[i] + s2r * p1[i] - sdr * p2[i] ;
      dz   = s1z * p3[i] + s2z * p1[i] - sdz * p2[i] ;
      norm = sqrt( dr * dr + dz * dz ) ;
      flmt[i] += ar2 * norm ;         
      dr   = s3r * p1[i] + s4r * p3[i] + sdr * p4[i] ;
      dz   = s3z * p1[i] + s4z * p3[i] + sdz * p4[i] ;
      norm = sqrt( dr * dr + dz * dz ) ;
      flmt[i] += ar4 * norm ;         
      flmt[i] = fscl * flmt[i] / ( p1[i] + p2[i] + p3[i] + p4[i] + umin ) ;
      ar2 *= rb2 ;
      ar4 *= rb4 ;                   
      b[i]   -= ( s3r * sdr + s3z * sdz ) * ar4 ;
      t[i]   += ( s1r * sdr + s1z * sdz ) * ar2 ;
      l[i]   -= ( s4r * sdr + s4z * sdz ) * ar4 ;
      rr[i]  += ( s2r * sdr + s2z * sdz ) * ar2 ;
      bm1[i] -= ( s1r * s2r + s1z * s2z ) * ar2 ;
      bm1[i] -= ( s3r * s4r + s3z * s4z ) * ar4 ;  
   }
   myflops += 222.0 * ( domain->lpn - domain->frn + 1 ) ;
   FREEMEM(rc) ;
   FREEMEM(zc) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
