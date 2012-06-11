#include "irs.h"
#include "cgl.h"
#include "irscur.h"
void delcur0(
	    int	     cn )
{
   char *me = "delcur0";
   char msg[64];
   if (cn == -1) {
      clrcur() ;
   }
   else if (ifcuron[cn]) {
      ncur-- ;
      if (ncur == 0)  clrcur() ;
      else {
         ifcuron[cn] = 0 ;
         ifcurbd[cn] = 0 ;
         ifcurst[cn] = 0 ;
         FREEMEM(p1d[2*cn].fpa) ;
         FREEMEM(p1d[2*cn+1].fpa) ;
         curlmt() ;
      }
   }
   else {
      sprintf(msg,"can't delete curve %d",cn);
      ctlnotice(me,msg);
   }
}
