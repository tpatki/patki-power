#include "irs.h"
#include "irstdiff.h"
void setpz2( double *v, double s, Domain_t *domain )
{
   int i, ix, is ;
   int j, jx, js ;
   int n ;
   double *vl ;
   double *vh ;
   if ( ndims == 2 ) {
      vl = v ;
      vh = v + domain->jp*(domain->jmax+1) ;
      ix = domain->imax + 1 ;
      is = 1 ;
      for ( i = 0 ; i <= ix ; i++ ) {
         n     = i*is ;
         vl[n] = s ;
         vh[n] = s ;
      } 
      vl = v ;
      vh = v + (domain->imax+1) ;
      ix = domain->jmax + 1 ;
      is = domain->jp ;
      for ( i = 0 ; i <= ix ; i++ ) {
         n     = i*is ;
         vl[n] = s ;
         vh[n] = s ;
      } 
   } else {
      vl = v ;
      vh = v + domain->kp*(domain->kmax+1) ;
      ix = domain->imax + 1 ;
      is = 1 ;
      jx = domain->jmax + 1 ;
      js = domain->jp ;
      for ( j = 0 ; j <= jx ; j++ ) {
         for ( i = 0 ; i <= ix ; i++ ) {
            n     = j*js + i*is ;
            vl[n] = s ;
            vh[n] = s ;
         }
      }
      vl = v ;
      vh = v + domain->jp*(domain->jmax+1) ;
      ix = domain->imax + 1 ;
      is = 1 ;
      jx = domain->kmax + 1 ;
      js = domain->kp ;
      for ( j = 0 ; j <= jx ; j++ ) {
         for ( i = 0 ; i <= ix ; i++ ) {
            n     = j*js + i*is ;
            vl[n] = s ;
            vh[n] = s ;
         } 
      } 
      vl = v ;
      vh = v + (domain->imax+1) ;
      ix = domain->jmax + 1 ;
      is = domain->jp ;
      jx = domain->kmax + 1 ;
      js = domain->kp ;
      for ( j = 0 ; j <= jx ; j++ ) {
         for ( i = 0 ; i <= ix ; i++ ) {
            n     = j*js + i*is ;
            vl[n] = s ;
            vh[n] = s ;
         } 
      }
   }
}
