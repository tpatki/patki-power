#include "irs.h"
#include "cgl.h"
#include "irscur.h"
void clrcur( void )
{
   int i ;
   ncur = 0 ;
   for ( i = 0 ; i < ncurx ; i++ )
      {
      if (ifcuron[i])
         {
         ifcuron[i] = 0 ;
         ifcurbd[i] = 0 ;
         ifcurst[i] = 0 ;
         FREEMEM(p1d[2*i].fpa) ;
         FREEMEM(p1d[2*i+1].fpa) ;
         }
      }
}
