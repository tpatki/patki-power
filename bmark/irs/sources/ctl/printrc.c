#include "irs.h"
void printrc( void )
{
   char msg[256];
   sprintf( msg, "time = %e cycle = %d radiation iterations = %d",
            ttime, cycle, rdifit ) ;
   ctlmsg(msg) ;
}
