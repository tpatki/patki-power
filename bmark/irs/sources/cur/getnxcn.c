#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int  getnxcn( void )
{
   char *me = "getnxcn";
   char msg[64];
   int cc ;
   if (cnset == -1)
      {
      for ( cc = 0 ; cc < ncurx ; cc++ )
         if (ifcuron[cc] == 0) break ;
      if ( cc >= ncurx)
         {
         sprintf(msg,"only %d curves allowed at once",ncurx);
         ctlnotice(me,msg);
         return(-1) ;
         }
      }
   else
      {
      cc = cnset ;
      if (ifcuron[cc] == 1) delcur0(cc) ;
      cnset = -1 ;
      }
   return(cc) ;
}
