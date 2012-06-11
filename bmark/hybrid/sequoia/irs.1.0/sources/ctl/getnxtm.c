#include <signal.h>
#include "irs.h"
#include "irsctl.h"
#include "FreqMesg.h"
double getnxtm(void)
{
  int i ;
  double nxtm = tstop;
  for (i=0 ; i<nfq ; i++) {
    if (fq[i].nextTime < nxtm) { nxtm = fq[i].nextTime; }
  }
  return(nxtm) ;
}
