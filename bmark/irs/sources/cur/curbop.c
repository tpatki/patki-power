#include "irs.h"
#include "cgl.h"
#include "irscur.h"
int  curbop(
	    int	     bop )
{
   char *me = "curbop";
   int error,ca,cb,cflag,n ;
   char xlab[30],ylab[30],chop[30],msg[64];
   double *newx,*newy,*xa,*ya,*xb,*yb ;
   error = 0 ;
   ca = geti(&cflag) ;
   cb = geti(&cflag) ;
   if (ifcuron[ca] == 0)
      {
      error = 1 ;
      sprintf(msg,"Curve %d not defined",ca);
      ctlnotice(me,msg);
      }
   if (ifcuron[cb] == 0)
      {
      error = 1 ;
      sprintf(msg,"Curve %d not defined",cb);
      ctlnotice(me,msg);
      }
   if ((p1d[2*ca+1].palen != p1d[2*cb+1].palen)
     ||(p1d[2*ca  ].palen != p1d[2*cb  ].palen))
      {
      error = 1 ;
      sprintf(msg,"Curves %d and %d have different lengths",ca,cb);
      ctlnotice(me,msg);
      }
   if (error) return(error) ;
   n = p1d[2*ca+1].palen ;
   newx = ALLOT(double,2*n) ;
   newy = newx + n ;   
   xa = p1d[2*ca+1].fpa ;
   ya = p1d[2*ca  ].fpa ;
   xb = p1d[2*cb+1].fpa ;
   yb = p1d[2*cb  ].fpa ;
   dobop(chop,newx,newy,xa,ya,xb,yb,n,bop) ;
   strcpy(xlab,p1d[2*ca+1].namelab) ;
   sprintf(ylab,"%d %s %d",ca,chop,cb) ;
   setcur(newx,newy,n,xlab,ylab) ;
   FREEMEM(newx) ;
   return(error) ;
}
