#include "irs.h"
#include "cgl.h"
#include "irscur.h"
void curlmt( void )
{
   int i,j ;
   for ( i = 0 ; i < ncurx ; i++ )
      if (ifcuron[i] == 1) break ;
   if ( i < ncurx )
      {
      cxmn = p1d[2*i+1].min ;
      cxmx = p1d[2*i+1].max ;
      cymn = p1d[2*i].min ;
      cymx = p1d[2*i].max ;
      for ( j = i + 1 ; j < ncurx ; j++ )
         {
         if (ifcuron[j] == 0) continue ;
         if (p1d[2*j+1].min < cxmn)  cxmn = p1d[2*j+1].min ;
         if (p1d[2*j+1].max > cxmx)  cxmx = p1d[2*j+1].max ;
         if (p1d[2*j].min < cymn)  cymn = p1d[2*j].min ;
         if (p1d[2*j].max > cymx)  cymx = p1d[2*j].max ;
         }
      }
}
