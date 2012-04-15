#include <signal.h>
#include "irs.h"
#include "irsctl.h"
#include "irscur.h"
#include "irsgenrd.h"
#include "CycleMesg.h"
#include "Conditional.h"
#include "FreqMesg.h"
int  domsg(void)
{
  int i, termfg, lasttermfg, tmult;
  int cyctmp;
  double epsilon, tdiff;
  ifcomfg = 0 ;
  pdmd    = 1 ;
  termfg  = TERMFLG_READY ;
  epsilon = 1.0e-10 * ttime ;
  for ( i = 0 ; i < nfq ; i++ ) {
    if ( (ttime + epsilon) >= fq[i].nextTime ) {
      ifdofq	= i ;
      line	= fq[i].msg ;
      ps	= line ;
      symflag	= 0 ;
      if (fqtp[i] >= 0) {
        stoplot(fqtp[i]);
        ps = NULL ;
      }
      else {
        lasttermfg = docmd();
        if ( lasttermfg > termfg ) termfg = lasttermfg;
      }
      if ( fq[i].nextTime >= fq[i].t2 ) {
        fq[i].nextTime = plarge ;
      }
      else {
        tdiff = ttime - fq[i].nextTime;
        tmult = (int)(tdiff / fq[i].dt);
        fq[i].nextTime += (tmult - 1) * fq[i].dt;
        do {
          fq[i].nextTime += fq[i].dt;
          if ( fq[i].nextTime > fq[i].t2) {
            fq[i].nextTime = fq[i].t2 ;
            break ;
          }
        }
        while (fq[i].nextTime <= (ttime + epsilon));
      }
    }
  }
  for ( i = 0 ; i < ncyc ; i++ ) {
    if ( cycle >= cyc[i].nextCycle ) {
      ifdocy  = i ;
      line    = cyc[i].msg ;
      ps      = line ;
      symflag = 0 ;
      if ( cyctp[i] >= 0 ) {
        stoplot(cyctp[i]) ;
        ps = NULL ;
      }
      else {
        lasttermfg = docmd();
        if ( lasttermfg > termfg ) termfg = lasttermfg;
      }
      if ( cyc[i].nextCycle >= cyc[i].c2 ) {
        cyc[i].nextCycle = 99999999 ;
      }
      else {
	cyctmp = cyc[i].nextCycle;
        do {
          cyctmp = cyctmp + cyc[i].dc;
          if ( cyctmp > cyc[i].c2) {
            cyctmp = cyc[i].c2 ;
            break ;
          }
        }
        while (cyctmp <= cycle);
	cyc[i].nextCycle = cyctmp;
      }
    }
  }
  ifdofq = -1 ;
  ifdocy = -1 ;
  line    = lnbuf ;
  ifcomfg = 1 ;
  pdmd    = 0 ;
  lasttermfg = conditionals_eval();
  if ( lasttermfg > termfg ) termfg = lasttermfg;
  return(termfg) ;
}
