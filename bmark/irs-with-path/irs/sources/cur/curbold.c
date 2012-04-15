#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int curbold( void )
{
   char *me = "curbold";
   int error, cc, cflag ;
   char op[30], msg[64];
   error = 0 ;
   geta(op) ; 
   cc = geti(&cflag) ;
   if ( ifcuron[cc] == 0 ) {
      error = 1 ;
      sprintf( msg, "Curve %d not defined.", cc );
      ctlnotice(me,msg);
      return(error) ;
   }
   if ( !strcmp(op,"on") ) {
      ifcurbd[cc] = 1 ;
   } else if ( !strcmp(op,"off") ) {
      ifcurbd[cc] = 0 ;
   } else {
      error = 1 ;
      sprintf( msg,
               "'%s' option unknown. Valid options are 'on' or 'off'", op );
      ctlnotice(me,msg);
   }
   return(error) ;
}
