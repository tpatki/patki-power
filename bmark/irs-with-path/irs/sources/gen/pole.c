#include "irs.h"
#include "irsgen.h"
int pole( void )
{
   int ibc ;
   ibc = domains[blknum].nbc - 1;
   domains[blknum].bc[ibc].rtype = POLE ;
   return(0);
}
