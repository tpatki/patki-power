#include "irs.h"
#include "irsgen.h"
#include "irsrgst.h"
int  getfarg( double *farg, int	lentar )
{
   char sym[128] ;
   int len,ifun ;
   peekc(sym) ;
   if (isbeta(sym)) {
      geta(sym) ;
      ifun = isargfun(sym) ;
      if (RGST_QUERY_OBJECT_ATTR(sym,"DomainVar") == TRUE) {
        len = getfpaa(sym,farg);
      } else if (RGST_QUERY_OBJECT_ATTR(sym,"GlobalArray") == TRUE) {
        len = getfpaa(sym,farg);
      } else if (ifun  >= 0) {
        len = doarg_fun(ifun,farg,lentar);
      } else if (rgst_check_for_obj(sym) == TRUE) {
        len = getrgstdata(R_DOUBLE,sym,(void **)&farg,lentar);
      } else {
      }
   } else {
      len = getflst(&farg,lentar) ;
   }
   return(len) ;
}
