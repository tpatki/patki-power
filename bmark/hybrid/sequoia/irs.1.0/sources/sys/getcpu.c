#ifdef TFLOPS
#include <nx.h>
#endif
#include <time.h>
#include "mach.h" 
#include "irs.h" 
#include "irssys.hh"
double getcpu( void )
{
   double tnow,convert = 1.0e6 ;
#ifdef CLK_TCK
   convert = CLK_TCK ;
#endif
#ifdef CLOCKS_PER_SEC
   convert = CLOCKS_PER_SEC ;
#endif
#ifdef TFLOPS
   tnow = dclock();
#else
   tnow = (double ) clock()/convert ;
#endif
   if (tnow < tlast) base += (tlast - tnow) ; 
   tlast = tnow ;
   tnow = base + tnow ;
   return(tnow) ;
}
