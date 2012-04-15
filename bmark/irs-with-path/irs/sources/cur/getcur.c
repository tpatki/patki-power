#include "irs.h"
#include "cgl.h"
#include "irscur.h"
#define max2(a,b)  ((a) > (b) ? (a) : (b))
#define min2(a,b)  ((a) < (b) ? (a) : (b))
int  getcur( int cc, int tpflag )
{
   char *me = "getcur";
   int error,i ;
   char op[MAXWORD], msg[128];
   error = 0 ;
   if (tpflag) error = getvectp(&p1d[2*cc]) ;
   else        error = getvec(&p1d[2*cc],0,1) ;
   if (error) {
     sprintf(msg,"unknown y array '%s' in plot",p1d[2*cc].namelab);
     ctlnotice(me,msg);
     ifcuron[cc] = 0 ;
     return(error) ;
   }
   geta(op) ;
   if (strcmp(op,"vs.")) {
     error = 1 ;
     sprintf(msg,"'%s' found in place of expected 'vs.' in plot",op);
     ctlnotice(me,msg);
     ifcuron[cc] = 0 ;
     return(error) ;
   }
   if (tpflag) error = getvectp(&p1d[2*cc+1]) ;
   else        error = getvec(&p1d[2*cc+1],0,1);
   if (error) {
     sprintf(msg,"unknown x array '%s' in plot",p1d[2*cc+1].namelab);
     ctlnotice(me,msg);
     ifcuron[cc] = 0 ;
     return(error) ;
   }
   if (p1d[2*cc+1].palen == p1d[2*cc].palen + 1) {
     for ( i = 0 ; i < p1d[2*cc+1].palen-1 ; i++ )
        p1d[2*cc+1].fpa[i] = 0.5*(p1d[2*cc+1].fpa[i] +
                                  p1d[2*cc+1].fpa[i+1]) ;
     p1d[2*cc+1].palen = p1d[2*cc].palen ;
   }
   if (p1d[2*cc+1].palen != p1d[2*cc].palen) {
     error = 1 ;
     sprintf(msg,"\n\tplot '%s' vs. '%s'\n\tx and y arrays are of different length",
                 p1d[2*cc].namelab,p1d[2*cc+1].namelab);
     ctlnotice(me,msg);
     ifcuron[cc] = 0 ;
     return(error) ;
   }
   ncur++ ;
   p1d[2*cc].min   = irsfmin(p1d[2*cc].fpa,p1d[2*cc].palen) ;
   p1d[2*cc].max   = irsfmax(p1d[2*cc].fpa,p1d[2*cc].palen) ;
   p1d[2*cc+1].min = irsfmin(p1d[2*cc+1].fpa,p1d[2*cc+1].palen) ;
   p1d[2*cc+1].max = irsfmax(p1d[2*cc+1].fpa,p1d[2*cc+1].palen) ;
   if (ncur == 1) {
     cxmn = p1d[2*cc+1].min ;
     cxmx = p1d[2*cc+1].max ;
     cymn = p1d[2*cc].min   ;
     cymx = p1d[2*cc].max   ;
   }
   else {
     cxmn = min2(cxmn,p1d[2*cc+1].min) ;
     cxmx = max2(cxmx,p1d[2*cc+1].max) ;
     cymn = min2(cymn,p1d[2*cc].min  ) ;
     cymx = max2(cymx,p1d[2*cc].max  ) ;
   }
   return(error) ;
}
#undef max2
#undef min2
