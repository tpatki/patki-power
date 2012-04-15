#include "irs.h"
#include "irseos.h"
void calc_dtdr_form ( double *cdtdr,  double *cecold, double *cmu,
                      double *cmu_m,  double  rho0,   double  dtdex,
                      double  etamax, double  etamin, int     n,
                      int     ir,     int     ieos,   double *pflops )
{
   double mu_max, mu_min ;
   double factor, ecx ;
   int i, m ;
   mu_max = etamax - 1.0 ;
   mu_min = etamin - 1.0 ;
   ecx = reg[ir].stress[ieos].ecxfit[0] ;
   for ( i = 0 ; i < n ; i++ ) {
      if ( cmu[i] < mu_min ) cmu[i] = mu_min ;
      if ( cmu[i] > mu_max ) cmu[i] = mu_max ;
      cmu_m [i] = 1.0 ;
      cecold[i] = ecx ;
      cdtdr [i] = 0.0 ;
   }
   for ( m = 1 ; m < 10 ; m++ ) {
      ecx = reg[ir].stress[ieos].ecxfit[m] ;
      for ( i = 0 ; i < n ; i++ ) {
         cdtdr [i] += ecx * cmu_m[i] * (double) m ;
         cmu_m [i] *= cmu[i] ;
         cecold[i] += ecx * cmu_m[i] ;
      }
   }
   factor = -dtdex / ( rho0 + ptiny ) ;
   for ( i = 0 ; i < n ; i++ ) {
      cdtdr[i] *= factor ;
   }
   *pflops += 55.0 * n ;
}
