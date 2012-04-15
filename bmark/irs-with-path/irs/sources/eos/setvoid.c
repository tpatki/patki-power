#include "irs.h"
#include "irseos.h"
#include "FunctionTimer.h"
void setvoid( double *den,  double *emat,  double *tmat, double *eion,
              double *tion, double *p,     double *pion, double *cs2,
              double *dedt, double *deidt, int *ndx, int n,
              Domain_t *domain)
{
   char *me = "setvoid";
   int i ;
   double myflops = 0.0; 
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < n ; i++ ) {
      den[ndx[i]]  = denvoid ;
      emat[ndx[i]] = ematvoid ;
      tmat[ndx[i]] = tfloor ;
      p[ndx[i]]    = 0.0 ;
      cs2[ndx[i]]  = 0.0 ;
      dedt[ndx[i]] = 1.0 ;
   }
   if ( iftion == 1 ) {
      for ( i = 0 ; i < n ; i++ ) {
         eion[ndx[i]]  = ematvoid ;
         tion[ndx[i]]  = tfloor ;
         pion[ndx[i]]  = 0.0 ;
         deidt[ndx[i]] = 1.0 ;
      }
   }
   FT_FINALIZE(me, domain->hash, myflops)
}
