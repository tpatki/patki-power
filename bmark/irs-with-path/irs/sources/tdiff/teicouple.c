#include "irs.h"
#include "irsreg.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void teicouple( double *emat, double *tmat,  double *dedt, double *eion,
                double *tion, double *deidt, double *den,  double scale,
                double dtcup, Domain_t *domain )
{
   char *me = "teicouple";
   int i, ir, length, nmixzn, namix ;
   int *ndx, *ndxmix, *grdmix, *grdzn ;
   double factor, de, wm, delm ;
   double *rate ;
   double myflops = 0.0;
   FT_INITIALIZE(me, domain->hash)
   namix  = domain->namix  ;
   nmixzn = domain->nmixzn ;
   grdzn  = domain->grdzn  ;
   rate = ALLOT(double,namix) ;
   geteicouple( rate, tmat, den, scale*dtcup, domain ) ;
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      length = domain->rlen[ir] ;
      ndx    = domain->rndx[ir] ;
      for ( i = 0 ; i < length ; i++ ) {
         factor   = rate[ndx[i]] * ( tion[ndx[i]] - tmat[ndx[i]] )
                  / ( deidt[ndx[i]] +
                      rate[ndx[i]]  * ( dedt[ndx[i]] + deidt[ndx[i]] ) ) ;
         de       = dedt[ndx[i]] * deidt[ndx[i]] * factor ;
         emat[ndx[i]] += de ;
         eion[ndx[i]] -= de ;
         tmat[ndx[i]] += deidt[ndx[i]] * factor ;
         tion[ndx[i]] -= dedt[ndx[i]]  * factor ;
         tmat[ndx[i]]  = MAX( tmat[ndx[i]], tfloor ) ;
         tion[ndx[i]]  = MAX( tion[ndx[i]], tfloor ) ;
      }
      myflops += 17.0 * length ;
   }
   FREEMEM(rate) ;
   FT_FINALIZE(me, domain->hash, myflops)
}
