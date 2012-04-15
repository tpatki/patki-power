#include "irs.h"
#include "cgl.h"
#include "irscur.h"
void curgetxy0(
	    int	     cn,	   double   val,	  int	   mode )
{
   char *me = "curgetxy0";
   char msg[128];
   double ret[100] ;
   int i,nret ;
   if (mode == 1)  
      {
      getcurroot( ret, &nret  
                , p1d[2*cn+1].fpa , p1d[2*cn].fpa , p1d[2*cn].palen , val 
                , xmn , xmx ) ;
      for ( i = 0 ; i < nret ; i++ )
	 {
         sprintf(msg,"%d x = %e",i,ret[i]);
         ctlmsg(msg);
	 }
      }
   else if ( mode == 2 ) 
      {
      getcurroot( ret, &nret  
                , p1d[2*cn].fpa , p1d[2*cn+1].fpa , p1d[2*cn].palen , val 
                , ymn , ymx ) ;
      for ( i = 0 ; i < nret ; i++ )
	 {
         sprintf(msg,"%d y = %e",i,ret[i]);
         ctlmsg(msg);
	 }
      }
}
