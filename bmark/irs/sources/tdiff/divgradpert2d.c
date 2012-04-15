#include "irsdefs.h"
#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "RadiationData.h"
void divgradpert2d( double *zc,   double *rc,    Domain_t *domain,
                    RadiationData_t *rblk,
		    int imin, int imax, int jmin, int jmax)
{
   char *me = "divgradpert2d";
   int i, iIndex, jIndex ;
   double *r1, *r2, *r3, *r4 ;
   double *z1, *z2, *z3, *z4 ;
   double dzdk, drdk, dzdl, drdl, rj   ;
   double c12, c14, c13 ;
   double rp, ry, rbar ;
   double *t  = rblk->ccl;
   double *b  = rblk->ccl - domain->jp;
   double *rr = rblk->cbc;
   double *l  = rblk->cbc - 1;
   double *b1 = rblk->cbl;
   double *bm1= rblk->cbr - 1;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ZNSET2D(rc,r1,r2,r3,r4)  ;
   ZNSET2D(zc,z1,z2,z3,z4)  ;
   if ( ifplane == 1 ) {
      rp = 1.0 ;
      ry = 0.0 ;
   } else {
      rp = 0.0 ;
      ry = 1.0 ;
   }
   for (iIndex = imin ; iIndex < imax ; iIndex++){
     for (jIndex = jmin ; jIndex < jmax ; jIndex++){
       i = iIndex + jIndex * domain->jp;
       dzdk = 0.5 * ( z1[i] + z2[i] - z3[i] - z4[i] ) ;
       drdk = 0.5 * ( r1[i] + r2[i] - r3[i] - r4[i] ) ;
       dzdl = 0.5 * ( z2[i] + z3[i] - z4[i] - z1[i] ) ;
       drdl = 0.5 * ( r2[i] + r3[i] - r4[i] - r1[i] ) ;
       rj = 1.0 / ( fabs(dzdk * drdl - dzdl * drdk) + ptiny) ;
       rbar = rp + ry * domain->y[i] ;
       rj   = 0.5 * rj * rbar ;                             
       c12  = rj * ( dzdk * dzdk + drdk * drdk ) ;
       c14  = rj * ( dzdl * dzdl + drdl * drdl ) ;
       c13  = rj * ( dzdk * dzdl + drdk * drdl ) ;          
       b[i]   += c14 ;
       t[i]   += c14 ;
       l[i]   += c12 ;
       rr[i]  += c12 ; 
       b1[i]  = -c13 ;   
       bm1[i] =  c13 ;                                      
     }
   }
   myflops += 49.0 * (imax - imin) * (jmax - jmin);
   FT_FINALIZE(me, domain->hash, myflops)
}
void divgradpert2bnd( double *zc,   double *rc,    Domain_t *domain,
		      RadiationData_t *rblk,
		      int *nodelist, int numNodes)
{
   char *me = "divgradpert2bnd";
   int i, index;
   double *r1, *r2, *r3, *r4 ;
   double *z1, *z2, *z3, *z4 ;
   double dzdk, drdk, dzdl, drdl, rj   ;
   double c12, c14, c13 ;
   double rp, ry, rbar ;
   double *t  = rblk->ccl;
   double *b  = rblk->ccl - domain->jp;
   double *rr = rblk->cbc;
   double *l  = rblk->cbc - 1;
   double *b1 = rblk->cbl;
   double *bm1= rblk->cbr - 1;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ZNSET2D(rc,r1,r2,r3,r4)  ;
   ZNSET2D(zc,z1,z2,z3,z4)  ;
   if ( ifplane == 1 ) {
      rp = 1.0 ;
      ry = 0.0 ;
   } else {
      rp = 0.0 ;
      ry = 1.0 ;
   }
   for (index = 0 ; index < numNodes ; index++){
       i = nodelist[index];
       dzdk = 0.5 * ( z1[i] + z2[i] - z3[i] - z4[i] ) ;
       drdk = 0.5 * ( r1[i] + r2[i] - r3[i] - r4[i] ) ;
       dzdl = 0.5 * ( z2[i] + z3[i] - z4[i] - z1[i] ) ;
       drdl = 0.5 * ( r2[i] + r3[i] - r4[i] - r1[i] ) ;
       rj = 1.0 / ( fabs(dzdk * drdl - dzdl * drdk) + ptiny) ;
       rbar = rp + ry * domain->y[i] ;
       rj   = 0.5 * rj * rbar ;                             
       c12  = rj * ( dzdk * dzdk + drdk * drdk ) ;
       c14  = rj * ( dzdl * dzdl + drdl * drdl ) ;
       c13  = rj * ( dzdk * dzdl + drdk * drdl ) ;          
       b[i]   += c14 ;
       t[i]   += c14 ;
       l[i]   += c12 ;
       rr[i]  += c12 ; 
       b1[i]  = -c13 ;   
       bm1[i] =  c13 ;                                      
   }
   myflops += 49.0 * numNodes;
   FT_FINALIZE(me, domain->hash, myflops)
}
