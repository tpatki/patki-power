#include "irs.h"
#include "irsgen.h"
int isargfun( char *sym )
{
   int ifun ;
   ifun = -1 ;
   if ( !strcmp(sym,"ntrp" ) ) ifun = FNTRP  ;
   if ( !strcmp(sym,"spln" ) ) ifun = FSPLN  ;
   if ( !strcmp(sym,"ratio") ) ifun = FRATIO ;
   if ( !strcmp(sym,"sum"  ) ) ifun = FSUM   ;
   if ( !strcmp(sym,"dif"  ) ) ifun = FDIF   ;
   if ( !strcmp(sym,"mlt"  ) ) ifun = FMLT   ;
   if ( !strcmp(sym,"div"  ) ) ifun = FDIV   ;
   if ( !strcmp(sym,"pow"  ) ) ifun = FPOW   ;
   if ( !strcmp(sym,"sin"  ) ) ifun = FSIN   ;
   if ( !strcmp(sym,"cos"  ) ) ifun = FCOS   ;
   if ( !strcmp(sym,"tan"  ) ) ifun = FTAN   ;
   if ( !strcmp(sym,"cot"  ) ) ifun = FCOT   ;
   if ( !strcmp(sym,"abs"  ) ) ifun = FABS   ;
   if ( !strcmp(sym,"log"  ) ) ifun = FLOG   ;
   if ( !strcmp(sym,"exp"  ) ) ifun = FEXP   ;
   if ( !strcmp(sym,"sqrt" ) ) ifun = FSQRT  ;
   if ( !strcmp(sym,"sqr"  ) ) ifun = FSQR   ;
   if ( !strcmp(sym,"min"  ) ) ifun = FMIN   ;
   if ( !strcmp(sym,"max"  ) ) ifun = FMAX   ;
   if ( !strcmp(sym,"mag"  ) ) ifun = FMAG   ;
   if ( !strcmp(sym,"ft"   ) ) ifun = FFT    ;
   if ( !strcmp(sym,"rand" ) ) ifun = FRAND  ;
   return(ifun) ;
}
