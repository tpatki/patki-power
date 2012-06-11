#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "Hash.h"
#include "FunctionTimer.h"
void FunctionTimer_clock(
  int              flag,		
  FunctionTimer_t *fts)		
{
  double clock_this;
  int    clock_rolls;
  struct tms tms0;
#include "parcrit.h"
  {
    clock_this = (double)clock();
    if (clock_this < ft_clock_last) { 
	ft_clock_rolls++; 
	fflush(stderr);
    }
    ft_clock_last = clock_this;
    clock_rolls = ft_clock_rolls;
  }
  if (flag == TIMER_START) {
      fts->times_start       = (double)times(&tms0);
      fts->clock_start       = clock_this;
      fts->clock_rolls_start = clock_rolls;
  }
  else {
      fts->clock_stop       = clock_this;
      fts->clock_rolls_stop = clock_rolls;
      fts->times_stop       = (double)times(&tms0);
  }
}
int test_clockroll(int rolls, HashTable_t *hash)
{
  char *me = "test_clockroll";
  int i, j, numrolls;
  double a, b, c, t1, emins;
  double cstart, cstop, myflops = 0;;
  cstart = (double)clock();
  numrolls = 0;
  for ( ; ; ) {
    myflops = 0.0;
    FT_INITIALIZE(me, hash);
    c = 2;
    for (j=0; j<99999999; j++) {
       a = j * 123.456 * c / (94.123);
       b = sin(a);
       c = cos(b);
    }
    cstop = (double)clock();
    if (cstop < cstart) {
      numrolls++;
      cstart = cstop;
    }
    t1                    = ((((cstop - cstart)                                / CLOCKS_PER_SEC)) / 60.0);
    if (numrolls > 0) t1 += ft_maxclock                                         / CLOCKS_PER_SEC / 60.0;
    if (numrolls > 1) t1 += (numrolls - 1) * (((ft_maxclock - ft_minclock) + 1) / CLOCKS_PER_SEC / 60.0);
    if (t1 > (emins + 1.0)) {
      emins = t1;
      fprintf(stderr,"Elapsed %d rolls %f minutes cstop = %d cstart = %d \n",numrolls,emins,(int)cstop,(int)cstart);
      fflush(stderr);
    }
    myflops += ((5 + 8 + 8) * (99999999)) + 1 + 1 + 9 + 2 + 11 + 12;
    FT_FINALIZE(me, hash, myflops)
    if (numrolls >= rolls) {
      break;
    }
  }
  fprintf(stderr,"\n!Done!\n"); fflush(stderr);
  return(0);
}
