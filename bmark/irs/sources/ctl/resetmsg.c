#include <signal.h>
#include "irs.h"
#include "irsctl.h"
#include "CycleMesg.h"
#include "FreqMesg.h"
void resetmsg( void )
{
   int iadv ;
   if ((ifdofq < 0) & (ifdocy < 0))  return ;
   iadv = 0 ;
   while (line + iadv < ps)  iadv++ ;
   if (ifdofq >= 0)  line = fq[ifdofq].msg ;
   else if (ifdocy >= 0)  line = cyc[ifdocy].msg ;
   ps = line + iadv ;
}
