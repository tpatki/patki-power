#include "irs.h"
#include "irsblk.h"
#include "irsbndry.h"
#include "irscom.h"
#include "irsdmp.h"
#include "irsedits.h"
#include "irseos.h"
#include "irsgen.h"
#include "irslag.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "Command.h"
#include "FunctionTimer.h"
#include "ProblemArray.h"
#include "Rgst.h"
#include "TimeStepControl.h"
#include "irsgen.hh"
int  gen( void )
{
   char *me = "gen";
   char msg[MAXLINE];
   int i,ir,error,iblk ;
   int ibc, gblk, lblk ;
   int len ;
   int *zdx_in ;
   RGST_AttributeElem_t *func ;
   error = 0 ;
   if ( (ifcom) && (!ifparallel) ) {
      bndry_init() ;
   }
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      neosgroup = MAX( neosgroup, reg[ir].numGroups ) ;
   }
   if ( neosgroup == 1 ) {
      neosgroup = 0 ;
   }

   if ( ifvsame ) {
      vsameorg() ;
   }
   regen_reset() ;
   genmd = 1     ;
   if ( !ifparallel ) {
      initcom( NULL, 0 ) ;
   }
   if (ifcom) {
      bndry_setmomflx() ;
      bndry_zdxneighbor() ;
   }
   sewbndry() ;
   if ( ifparallel ) {
      initcombufs() ;
   }
 ;    if ( nspec > 0 ) {
      species_init() ;
   } else {
      ifdynspec = 0 ;
      ProblemArray_del("specfrac", NULL) ;
   } 
   sanityck() ;
   swapcoords() ;
   func = rgst_list_attr(A_OBJECT, "Function_Gen") ;
   while ( func != NULL ) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj ;
      (*(cp->proc))() ;
      func = func->next ;
   }
   for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
      error += blkgen( &domains[iblk] ) ;
   }
   if ( ifcom ) {
      comverify() ;
   }

   eos_init(1) ;
   if ( ifconvert == 0 ) {
      for ( iblk = 0 ; iblk < nblk ; iblk++ ) {
         getematblk( 1, &domains[iblk] ) ;
      } 
   } 
   TimeStepControl_initialize() ;
   error += update( 0.0, 0 ) ;
   if ( ndeltat < deltat ) {
      deltat = ndeltat ;
   }
   deltatSubcycle = deltat ;
   error += editor( FULL_STEP ) ;
   genmd = 0 ;
   hash_optimize_all();
   return(error) ;
}
