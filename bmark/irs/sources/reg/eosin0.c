#include "irs.h"
#include "irseos.h"
#include "irsreg.h"
int eosin0( int number, int form )
{
   char *me = "eosin0";
   char msg[128];
   int error, cflag, n, i, ir, ieos ;
   error = 0 ;
   ir   = current_region ;
   ieos = current_eos ;
   if ( reg[ir].eosGroup[ieos].database.ndata > 0 ) {
         FREEMEM(reg[ir].eosGroup[ieos].database.data) ;
   }
        if ( form == 0 )  { n = geti(&cflag) ; }
   else if ( form == 1 )   n =  5 ;
   else if ( form == 2 )   n =  7 ;
   else if ( form == 3 )   n = 32 ;
   else if ( form == 4 )   n =  6 ;
   else if ( form == 5 )   n =  1 ;
   else if ( form == 6 )   n = 27 ;
   else if ( form == 7 )   n =  9 ;
   else if ( form == 12 )  n =  7 ;
   else if ( form == 13 )  n =  7 ;
   else if ( form == 15 )  n = 32 ;
   else if ( form == 16 )  n =  0 ;
   else if ( form == 17 )  n = 15 ;
   else if ( form == 18 )  n = 21 ;
   else if ( form == 19 )  n = 18 ;
   else if ( form == 30 )  n =  0 ;
   else if ( form == 105 ) n =  2 ; 
   else if ( form == 107 ) n = 12 ;
   else if ( form == 111 ) n =  4 ;
   else if ( form == 200 ) n =  0 ;
   else if ( form == 211 ) n =  9 ;
   else if ( form == 301 ) n =  0 ;
   else if ( form == 311 ) n =  4 ;
   else if ( form == 312 ) n =  0 ;
   else if ( form == 321 ) n =  9 ;
   else if ( form == 390 ) n =  0 ;
   else if ( form == 900 ) n =  0 ;
   else if ( form == 901 ) n =  0 ;
   else {
      error = 1 ;
      sprintf(msg,"EOS form %d not allowed or currently supported.",form) ;
      ctlnotice(me,msg);
      return(error) ;
   }
   if ( form == 7 ) {
      sprintf(msg,"EOS form 7 is CALE 2-phase water EOS: enter 9 coefs.") ;
      ctlnotice(me,msg);
   }
   reg[ir].eosGroup[ieos].database.ndata = n ;
   if ( (n > 0) && (error == 0) ) {
      reg[ir].eosGroup[ieos].database.data = MALLOT(double, n) ;
      if ( (form == 111) || (form == 211) ||
           (form == 311) || (form == 321)  ) {
         n-- ;
         reg[ir].eosGroup[ieos].database.data[n] = -1.0 ;
      }
      for ( i = 0 ; i < n ; i++ ) {
         reg[ir].eosGroup[ieos].database.data[i] = getf(&cflag) ;
         if (cflag) {
            error = 1 ;
            sprintf( msg,"EOS %d, form %d, should have %d entries not %d.",
                     number, form, n, i ) ;
            ctlwarning(me,msg);
            return(error) ;
         }
      }
   }
   if ( (form == 12) && (ZERO == 0) ) {
      error = 1 ;
      ctlwarning(me,"Eos form 12 ") ;
   }
   if ( (form == 13) && (ZERO == 0) ) {
      error = 1 ;
      ctlwarning(me,"Eos form 13 ") ;
   }
   if ( (form == 18) && (iftmode == 1) ) {
      error = 1 ;
      ctlwarning(me,"Eos form 18 runs in energy mode only.") ;
   }
   if ( (form == 22) && (ZERO == 0) ) {
      error = 1 ;
      ctlwarning(me,"Eos form 22 ") ;
   }
   if ( ( (form == 111) || (form == 211) ||
          (form == 311) || (form == 321)  ) && (ioneq == 0) ) {
      error = 1 ;
      sprintf( msg,"Eos form %d (QEOS) used but ioneq = 0 (set ioneq to 1).",
               form ) ;
      ctlwarning(me,msg);
   }
   if ( ( (form == 111) || (form == 211) ) && (iftmode == 0) ) {
      error = 1 ;
      sprintf( msg,"Eos form %d (QEOS) used but iftmode = 0 (set iftmode to 1).",
               form ) ;
      ctlwarning(me,msg);
   }
   if ( ( (form == 311) || (form == 321) ) && (iftion == 0) ) {
      error = 1 ;
      sprintf( msg,"Eos form %d (QEOS) used but iftion = 0 (set iftion to 1).",
               form ) ;
      ctlwarning(me,msg);
   }
   if ( (form >= 300) && (form < 400) && (iftion == 0) ) {
      error = 1 ;
      ctlwarning(me,"Eos forms in the 300's must have iftion set to 1.") ;
   }
   if ( form == 15 ) {
 ;    }
   return(error) ;
}
