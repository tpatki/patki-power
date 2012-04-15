#include "irs.h"
#include "irstdiff.h"
void setpz1( double *v, double s, Domain_t *domain )
{
   int i, ix, is ;
   int j, jx, js ;
   int n ;
   double *vl ;
   double *vh ;
   if ( ndims == 2 ) {
      vl = v + domain->jp ;
      vh = v + domain->jp*domain->jmax ;
      ix = domain->imax ;
      is = 1 ;
      for ( i = 1 ; i <= ix ; i++ ) {
         n     = i*is ;
         vl[n] = s ;
         vh[n] = s ;
      } 
      vl = v + 1 ;
      vh = v + domain->imax ;
      ix = domain->jmax ;
      is = domain->jp ;
      for ( i = 1 ; i <= ix ; i++ ) {
         n     = i*is ;
         vl[n] = s ;
         vh[n] = s ;
      } 
   } else {
      vl = v + domain->kp ;
      vh = v + domain->kp*domain->kmax ;
      ix = domain->imax ;
      is = 1 ;
      jx = domain->jmax ;
      js = domain->jp ;
      for ( j = 1 ; j <= jx ; j++ ) {
         for ( i = 1 ; i <= ix ; i++ ) {
            n     = j*js + i*is ;
            vl[n] = s ;
            vh[n] = s ;
         } 
      } 
      vl = v + domain->jp ;
      vh = v + domain->jp*domain->jmax ;
      ix = domain->imax ;
      is = 1 ;
      jx = domain->kmax ;
      js = domain->kp ;
      for ( j = 1 ; j <= jx ; j++ ) {
         for ( i = 1 ; i <= ix ; i++ ) {
            n     = j*js + i*is ;
            vl[n] = s ;
            vh[n] = s ;
         } 
      } 
      vl = v + 1 ;
      vh = v + domain->imax ;
      ix = domain->jmax ;
      is = domain->jp ;
      jx = domain->kmax ;
      js = domain->kp ;
      for ( j = 1 ; j <= jx ; j++ ) {
         for ( i = 1 ; i <= ix ; i++ ) {
            n     = j*js + i*is ;
            vl[n] = s ;
            vh[n] = s ;
         } 
      } 
   }
}
