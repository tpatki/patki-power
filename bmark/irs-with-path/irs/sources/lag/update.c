#include "irs.h"
#include "irslag.h"
#include "irscom.h"
#include "FunctionTimer.h"
#include "Tracer.h"
#include "TimeStepControl.h"
int update( double dt, int ifcalcdt )
{
   char *me = "update";
   char msg[256];
   int iblk, error ;
   double dtgtemp;
   double timedat[2];
   int my_nblk = nblk;
   FT_INITIALIZE(me, gv_hash_tbl)
   ndeltat = plarge ;
   dtg     = plarge ;
   error   = 0      ;

#include "pardo.h"
   for ( iblk = 0 ; iblk < my_nblk ; iblk++ ) {
     updateblk( &domains[iblk], ifcalcdt, dt ) ;
   }
 ; 
 ;    if (ifparallel) {
 ;    }
   TimeStepControl_findmin( "ActiveTimeStepControl", &ndeltat ) ;
   FT_FINALIZE(me, gv_hash_tbl, 1)
   return(error) ;
}
