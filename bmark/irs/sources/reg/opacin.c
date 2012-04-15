#include "irs.h"
#include "irsreg.h"
#include "irseos.h"
int opacin( void )
{
   int error, cflag, ir, iopac, opfg, ispec, eosnum, form ;
   char regop[MAXWORD] ;
   error = 0 ;
   ir    = current_region ;
   iopac = current_eos    ;
   opfg  =  1 ;
   ispec = -1 ;
   while ( opfg == 1 ) {
      peekc(regop) ;
      if ( !strcmp(regop,"krmlt") ) {
         geta(regop) ;
         reg[ir].opacityGroup[iopac].rosMultiplier = getf(&cflag) ;
      } else if ( !strcmp(regop,"kpmlt") ) {
         geta(regop) ;
         reg[ir].opacityGroup[iopac].planckMultiplier = getf(&cflag) ;
      } else if ( !strcmp(regop,"ktfloor") ) {
         geta(regop) ;
         reg[ir].opacityGroup[iopac].KTfloor = getf(&cflag) ;
      } else if ( !strcmp(regop,"rosseland") ) {
         geta(regop) ;
         form   = geti(&cflag) ;
         eosnum = 0 ;
         error = OpacTypesIn_Kr( eosnum, form ) ;
      } else if ( !strcmp(regop,"planck") ) {
         geta(regop) ;
         form   = geti(&cflag) ;
         eosnum = 0 ;
         error = OpacTypesIn_Kp( eosnum, form ) ;
      } else {
         opfg = 0 ;
      }
   }
   return(error) ;
}
