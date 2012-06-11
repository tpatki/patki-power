#include "irsdefs.h"
#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void FluxLimiterPert2d( double *zc,   double *rc,    Domain_t *domain,
			double *phi, double *flmt, double umin, double fscl,
			int imin, int imax, int jmin, int jmax)
{
   char *me = "FluxLimiterPert2d";
   int i, iIndex, jIndex ;
   double *r1, *r2, *r3, *r4 ;
   double *z1, *z2, *z3, *z4 ;
   double *p1, *p2, *p3, *p4 ;
   double dzdk, drdk, dzdl, drdl, rj   ;
   double dpdk, dpdl, dpdz, dpdr, rbar ;
   double rp, ry ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ZNSET2D(rc,r1,r2,r3,r4)  ;
   ZNSET2D(zc,z1,z2,z3,z4)  ;
   ZNSET2D(phi,p1,p2,p3,p4) ;
   if ( ifplane == 1 ) {
      rp = 1.0 ;
      ry = 0.0 ;
   } else {
      rp = 0.0 ;
      ry = 1.0 ;
   }
   fscl  *= 4.0 ;
   for (iIndex = imin ; iIndex <= imax ; iIndex++){
     for (jIndex = jmin ; jIndex <= jmax ; jIndex++){
       i = iIndex + jIndex * domain->jp;
       dzdk = 0.5 * ( z1[i] + z2[i] - z3[i] - z4[i] ) ;
       drdk = 0.5 * ( r1[i] + r2[i] - r3[i] - r4[i] ) ;
       dzdl = 0.5 * ( z2[i] + z3[i] - z4[i] - z1[i] ) ;
       drdl = 0.5 * ( r2[i] + r3[i] - r4[i] - r1[i] ) ;
       dpdk = 0.5 * ( p1[i] + p2[i] - p3[i] - p4[i]) ;
       dpdl = 0.5 * ( p2[i] + p3[i] - p4[i] - p1[i]) ;      
       rj = 1.0 / ( fabs(dzdk * drdl - dzdl * drdk) + ptiny) ;
       dpdz = rj * ( dpdk * drdl - dpdl * drdk ) ;
       dpdr = rj * ( dpdl * dzdk - dpdk * dzdl ) ;          
       flmt[i] = fscl * sqrt( dpdz *dpdz + dpdr * dpdr )
	 / ( p1[i] + p2[i] + p3[i] + p4[i] + umin ) ; 
     }
   }
   myflops += 81.0 * ( domain->lrn - domain->frn + 1 ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
void FluxLimiterPert2Bnd(double *zc,   double *rc,    Domain_t *domain,
                    double *phi, double *flmt, double umin, double fscl,
		    int *nodelist, int numNodes)
{
   char *me = "FluxLimiterPert2Bnd";
   int i, index;
   double *r1, *r2, *r3, *r4 ;
   double *z1, *z2, *z3, *z4 ;
   double *p1, *p2, *p3, *p4 ;
   double dzdk, drdk, dzdl, drdl, rj   ;
   double dpdk, dpdl, dpdz, dpdr, rbar ;
   double rp, ry ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   ZNSET2D(rc,r1,r2,r3,r4)  ;
   ZNSET2D(zc,z1,z2,z3,z4)  ;
   ZNSET2D(phi,p1,p2,p3,p4) ;
   if ( ifplane == 1 ) {
      rp = 1.0 ;
      ry = 0.0 ;
   } else {
      rp = 0.0 ;
      ry = 1.0 ;
   }
   fscl  *= 4.0 ;
   for (index = 0 ; index < numNodes ; index++){
       i = nodelist[index];
       dzdk = 0.5 * ( z1[i] + z2[i] - z3[i] - z4[i] ) ;
       drdk = 0.5 * ( r1[i] + r2[i] - r3[i] - r4[i] ) ;
       dzdl = 0.5 * ( z2[i] + z3[i] - z4[i] - z1[i] ) ;
       drdl = 0.5 * ( r2[i] + r3[i] - r4[i] - r1[i] ) ;
       dpdk = 0.5 * ( p1[i] + p2[i] - p3[i] - p4[i]) ;
       dpdl = 0.5 * ( p2[i] + p3[i] - p4[i] - p1[i]) ;      
       rj = 1.0 / ( fabs(dzdk * drdl - dzdl * drdk) + ptiny) ;
       dpdz = rj * ( dpdk * drdl - dpdl * drdk ) ;
       dpdr = rj * ( dpdl * dzdk - dpdk * dzdl ) ;          
       flmt[i] = fscl * sqrt( dpdz *dpdz + dpdr * dpdr )
	 / ( p1[i] + p2[i] + p3[i] + p4[i] + umin ) ; 
   }
   myflops += 81.0 * ( domain->lrn - domain->frn + 1 ) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
