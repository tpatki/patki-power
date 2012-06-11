#include <signal.h>
#include "irs.h"
#include "irsctl.h"
int  lnadv(
	    char     *lnout,	   char	    *msg,	  int	   msglen,
	    int	     *count )
{
   int termfg,ncount,i ;
   char *beg ;
   ncount = *count ;
   if (ncount >= msglen)   termfg = 1 ;
   else                    termfg = 0 ;
   if (termfg == 0)
      {
      beg = msg + ncount ;
      for ( i = 0 ; i < 200 ; i++ )
         {
         if (beg[i] == '\n') continue ;
         if (beg[i] != '$')
            {
            *lnout = beg[i] ;
            lnout++ ;
            }
         else
            {
            *lnout ='\0' ;
            ncount += i + 1 ;
            *count = ncount ;
            break ;
            }
         }
      }
   return(termfg) ;
}
