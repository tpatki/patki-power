#include "irs.h"
#include "irsreg.h"
#include "irseos.h"
int OpacTypesIn_Kr( int number, int form )
{
   char *me = "OpacTypesIn_Kr";
   char msg[128] ;
   int error, cflag, n, i, ir, iopac ;
   error = 0 ;
   ir    = current_region ;
   iopac = current_eos ;
   if ( reg[ir].opacityGroup[iopac].rosTable.ndata > 0 ) {
         FREEMEM(reg[ir].opacityGroup[iopac].rosTable.data) ;
   }
   reg[ir].opacityGroup[iopac].rosTable.number = number ;
   reg[ir].opacityGroup[iopac].rosTable.form   = form   ;
   reg[ir].opacityGroup[iopac].rosTable.type   = _Form_ ;
        if ( form == 0 )  { n = geti(&cflag) ; }
   else if ( form == 1 )    n = 1 ;
   else if ( form == 2 )    n = 0 ;
   else if ( form == 3 )    n = 1 ;
   else if ( form == 4 )    n = 0 ;
   else if ( form == 5 )    n = 0 ;
   else if ( form == 6 )    n = 3 ;
   else if ( form == 7 )    n = 3 ;
   else if ( form == 8 )    n = 1 ;
   else if ( form == 9 )    n = 8 ;
   else {
      error = 1 ;
      sprintf( msg,
               "Rosseland opacity form %d not allowed or currently supported.",
               form ) ;
      ctlnotice(me,msg) ;
      return(error) ;
   }
   reg[ir].opacityGroup[iopac].rosTable.ndata = n ;
   if ( (n > 0) && (error == 0) ) {
      reg[ir].opacityGroup[iopac].rosTable.data = MALLOT(double, n) ;
      for ( i = 0 ; i < n ; i++ ) {
         reg[ir].opacityGroup[iopac].rosTable.data[i] = getf(&cflag) ;
         if (cflag) {
            error = 1 ;
            sprintf( msg,
            "Rosseland opacity %d, form %d, should have %d entries not %d.",
                     number, form, n, i ) ;
            ctlwarning(me,msg) ;
            return(error) ;
         }
      }
   }
   return(error) ;
}
int OpacTypesIn_Kp( int number, int form )
{
   char *me = "OpacTypesIn_Kp";
   char msg[128] ;
   int error, cflag, n, i, ir, iopac ;
   error = 0 ;
   ir    = current_region ;
   iopac = current_eos ;
   if ( reg[ir].opacityGroup[iopac].planckTable.ndata > 0 ) {
         FREEMEM(reg[ir].opacityGroup[iopac].planckTable.data) ;
   }
   reg[ir].opacityGroup[iopac].planckTable.number = number ;
   reg[ir].opacityGroup[iopac].planckTable.form   = form   ;
   reg[ir].opacityGroup[iopac].planckTable.type   = _Form_ ;
        if ( form == 1 )    n = 1 ;
   else if ( form == 2 )    n = 0 ;
   else if ( form == 3 )    n = 1 ;
   else if ( form == 4 )    n = 0 ;
   else if ( form == 5 )    n = 0 ;
   else if ( form == 6 )    n = 3 ;
   else if ( form == 7 )    n = 3 ;
   else if ( form == 8 )    n = 0 ;
   else if ( form == 9 )    n = 0 ;
   else {
      error = 1 ;
      sprintf( msg,"Planck opacity form %d not allowed or currently supported.",
               form ) ;
      ctlnotice(me,msg) ;
      return(error) ;
   }
   reg[ir].opacityGroup[iopac].planckTable.ndata = n ;
   if ( (n > 0) && (error == 0) ) {
      reg[ir].opacityGroup[iopac].planckTable.data = MALLOT(double, n) ;
      for ( i = 0 ; i < n ; i++ ) {
         reg[ir].opacityGroup[iopac].planckTable.data[i] = getf(&cflag) ;
         if (cflag) {
            error = 1 ;
            sprintf( msg,
            "Planck opacity %d, form %d, should have %d entries not %d.",
                     number, form, n, i ) ;
            ctlwarning(me,msg) ;
            return(error) ;
         }
      }
   }
   return(error) ;
}
