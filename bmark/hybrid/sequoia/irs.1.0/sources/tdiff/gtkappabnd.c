#include "irs.h"
#include "irscom.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
#include "ProblemArray.h"
void gtkappabnd(Domain_t *domain, double  dtrad )
{
   char *me = "gtkappabnd";
   int i ;
   double kp, deni, third = 1.0 / 3.0 ;
   double *tcen  = MALLOT(double, domain->namix);
   double *twork = MALLOT(double, domain->namix);
   double *phi   = ProblemArray_ptr("phi", domain->hash);
   double *xplnk = ProblemArray_ptr("xplnk", domain->hash);
   double *kl = ProblemArray_ptr("diffCoefL", domain->hash);
   double *kr = ProblemArray_ptr("diffCoefR", domain->hash); 
   double *kb = ProblemArray_ptr("diffCoefB", domain->hash); 
   double *kf = ProblemArray_ptr("diffCoefF", domain->hash); 
   double *kd = ProblemArray_ptr("diffCoefD", domain->hash);
   double *ku = ProblemArray_ptr("diffCoefU", domain->hash);
   double *krcen = twork;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   for ( i = 0 ; i < domain->namix ; i++ ) {
     tcen[i]  = domain->trad[i] ;
     twork[i] = tcen[i];
   }
   SetFaceTemperature_Driver(domain, domain->vol, tcen,
			     ku, kd, kl, kr, kf, kb);
   for ( i = 0 ; i < domain->namix ; i++ ) {
      twork[i] = kl[i] ;
   }
   opac2t( phi, domain, kl, twork, dtrad ) ;
   for ( i = 0 ; i < domain->namix ; i++ ) {
      twork[i] = kr[i] ;
   }
   opac2t( phi, domain, kr, twork, dtrad ) ;
   for ( i = 0 ; i < domain->namix ; i++ ) {
      twork[i] = kb[i] ;
   }
   opac2t( phi, domain, kb, twork, dtrad ) ;
   for ( i = 0 ; i < domain->namix ; i++ ) {
      twork[i] = kf[i] ;
   }
   opac2t( phi, domain, kf, twork, dtrad ) ;
   if ( ndims == 3 ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
         twork[i] = kd[i] ;
      }
      opac2t( phi, domain, kd, twork, dtrad ) ;
      for ( i = 0 ; i < domain->namix ; i++ ) {
         twork[i] = ku[i] ;
      }
      opac2t( phi, domain, ku, twork, dtrad ) ;
   }
   planck_opacity( xplnk, tcen, dtrad, phi, domain ) ;
   if ( kapsav == 1 ) {
      for ( i = 0 ; i < domain->namix ; i++ ) {
         tcen[i] = domain->trad[i] ;
      }
      opac2t( phi, domain, krcen, tcen, dtrad ) ;
      kp = 1.0 / ( dtrad * 2.998e4 ) ;
      for ( i = 0 ; i < domain->namix ; i++ ) {
         deni      = 1.0 / ( domain->den[i] + ptiny ) ;
         domain->kros[i]  = third * deni * krcen[i] ;
         domain->kplnk[i] = kp * deni * xplnk[i] ;
      }
      myflops += 9.0 * domain->namix ;
   }
   FREEMEM(tcen);
   FREEMEM(twork);
   FT_FINALIZE(me, domain->hash, myflops)
}
