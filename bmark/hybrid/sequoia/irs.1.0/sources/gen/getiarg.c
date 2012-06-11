#include "irs.h"
#include "irsgen.h"
int  getiarg( int *iarg, int lentar )
{
   char sym[128] ;
   int i,len,cflag ;
   peekc(sym) ;
   if (isbeta(sym))
      {
      }
   else
      {
      len = lentar ;
      for ( i = 0 ; i < lentar ; i++ )
	 {
         iarg[i] = geti(&cflag) ;
         if (cflag) {len = i ; break ;}
	 }
      }
   return(len) ;
}
