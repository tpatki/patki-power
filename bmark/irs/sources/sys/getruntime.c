#include "irs.h"
#include "irssys.h"
#include "FunctionTimer.h"
double getruntime(void)
{
   FunctionTimer_t *ft;
   double runtime = 0.0;
   int saveflag;
   saveflag = ft_timersflag;	
   ft_timersflag = TRUE;
   FunctionTimer_finalize("main", gv_perm_ht, 1.0);
   ft = FunctionTimer_lookup("main",gv_perm_ht);
   if (ft != NULL) {
     runtime = ft->wall_secs;
   } 
   FunctionTimer_initialize("main", gv_perm_ht);
   ft_timersflag = saveflag;
   return(runtime);
}
