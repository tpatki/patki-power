#include "irs.h"
#include "irstdiff.h"
#include "FunctionTimer.h"
void kapmlt(double *kros, double *xplnk, double *t, 
            int *ndx, int n, double *data, int ndata) 
{
   char *me = "kapmlt";
   int i,ipair,npairs ;
   double tlo,flo,thi,fhi,slope,flmtlo,flmthi,f ;
   double myflops = 0.0; 
   FT_INITIALIZE(me, gv_hash_tbl)  
   npairs = ndata/2 ;
   for ( ipair = 0 ; ipair < npairs-1 ; ipair++ )
   {
      tlo = data[2*ipair] ;
      flo = data[2*ipair + 1] ;
      thi = data[2*ipair + 2] ;
      fhi = data[2*ipair + 3] ;
      slope = (fhi - flo)/(thi - tlo) ;
      flmtlo = 1.0 ;
      flmthi = 1.0 ;
      for ( i = 0 ; i < n ; i++ )
      {
         f = flo + slope*(t[ndx[i]] - tlo) ;
         if (t[ndx[i]] < tlo) f = flmtlo ;
         if (t[ndx[i]] > thi) f = flmthi ;
         kros[ndx[i]]  *= f ;
         xplnk[ndx[i]] *= f ;
      }
      myflops += 7*n ;
   }
   FT_FINALIZE(me, gv_hash_tbl, myflops) 
}
