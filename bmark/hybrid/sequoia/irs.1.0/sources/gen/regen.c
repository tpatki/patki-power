#include "irs.h"
#include "irsblk.h"
#include "irsbndry.h"
#include "irscom.h"
#include "irsedits.h"
#include "irsgen.h"
#include "irsobjects.h"
#include "irsparm.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "BlockMapping.h"
#include "Command.h"
#include "Domain.h"
#include "FunctionTimer.h"
#include "TimeStepControl.h"
#include "Rgst.h"
#include "Region.h"
static void regen_blkregen( Domain_t *domain ) ;
static void regen_blkfree( Domain_t *domain) ;
int  regen( void )
{
   char *me = "regen";
   char msg[MAXLINE];
   int i,iblk , ir;
   int gblk ;
   int len;
   int ibc;
   int error = 0 ;
   int *zdx_in;
   RGST_AttributeElem_t *func;
   for (ir = 1; ir <= nreg; ir++) {
      if (reg[ir].numGroups > neosgroup) neosgroup = reg[ir].numGroups;
   }
   if (neosgroup == 1) neosgroup = 0;
   if ( genmd == -1 ) {
      error += regen_reset();
   }
   genmd = 1 ;
   if (ifcom) {
      bndry_init();
      allotcom();
      initbuforder();
      varcom_bufinit();
      bndry_setmomflx();
      bndry_zdxneighbor() ;
      initcombufs();
   }
   sanityck();
   if (nspec > 0) {
      species_init();
   } else {
      ifdynspec = 0;
      rgst_del_attr(A_FIELD, "Domain_t", "specfrac", "Mixed");
      rgst_del_attr(A_FIELD, "Domain_t", "specfrac", "PermVar");
   } 
   func = rgst_list_attr(A_OBJECT, "Function_ReGen");
   while (func != NULL) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj;
      (*(cp->proc))();  
      func = func->next;
   }
   swapcoords();
   for (iblk = 0; iblk < nblk; iblk++) {
      regen_blkregen( &domains[iblk] );
   }
   if (ifcom) comverify();
   TimeStepControl_initialize();
   error += editor( FULL_STEP ) ;
   genmd = 0 ;
   return(error) ;
}
int  regen_pregen( void ) {
   int iblk;
   genmd = -1 ;
   if (ifcom) {
      freecom();
   }
   for (iblk = 0; iblk < nblk; iblk++) {
      regen_blkfree(&domains[iblk]);
   }
   return(0);
}
int  regen_reset( void ) {
   int iblk;
   genmd = 0 ;
   parmsanity();
   domain_free_attr();
   domain_attr();
   GlobalArrays_register();
   for (iblk = 0; iblk < nblk; iblk++) {
      domain_allot_fields(&domains[iblk]);
      domain_setpa(&domains[iblk]);
      regndx(&domains[iblk]);
   }
   return(0);
}
static void regen_blkregen( Domain_t *domain ) {
   int i,j;   
   int ir;   
   int len;   
   RGST_AttributeElem_t *func;
   regndx(domain);
   initbc(domain) ;
   if ( unblk > 1 ) {
   }
   genreflst(domain) ;
   if ( (ngroup > 0) || (ifedif == 1) || (ifidif == 1)  ) {
      genradreflst(domain) ;
   }
   if (ndims == 2) {
      refnd2d( domain->x,    domain->y,    domain ) ;
      refnd2d( domain->xdot, domain->ydot, domain ) ;
         volcal2d( domain->vol, domain->area, domain->x, domain->y, domain ) ;
   } else {
      refnd3d( domain->x,    domain->y,    domain->z   , domain ) ;
      refnd3d( domain->xdot, domain->ydot, domain->zdot, domain ) ;
         volcal3d( domain->vol, domain->x, domain->y, domain->z, domain ) ;
   } 
   if (ifdynspec) {
      for (i = 0; i < domain->namix; i++) {
         ir = domain->ireg[i];
         if ((ir > 0) && (domain->specfrac[i].mass_frac == NULL)) {
            len = reg[ir].nspec;
            domain->specfrac[i].mass_frac = MALLOT(double, len);
            for (j = 0; j < len; j++) {
               domain->specfrac[i].mass_frac[j] = reg[ir].species[j].massFraction0;
            }
         }
      }
   }
   regndx(domain);
   func = rgst_list_attr(A_OBJECT, "Function_ReGenDomain");
   while (func != NULL) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj;
      (*(cp->proc))(domain);  
      func = func->next;
   }
}
static void regen_blkfree( Domain_t *domain) {
   int i;
   int ibc;
   int len;
   RGST_AttributeElem_t *func;
   if (domain->phonlen > 0) {
      FREEMEM(domain->phondx  ) ;
      FREEMEM(domain->phonbc  ) ;
      FREEMEM(domain->bndndx  ) ;
   }
   domain->phonlen  = 0;
   if (domain->phozlen > 0) { 
      FREEMEM(domain->phozdx  ) ;
      FREEMEM(domain->bndzdx  ) ;
   }
   domain->phozlen  = 0;
   for (ibc = 0; ibc < domain->nbnd; ibc++) {
      FREEMEM(domain->bnd[ibc].ndx_send);
      FREEMEM(domain->bnd[ibc].zdx_send);
      FREEMEM(domain->bnd[ibc].ndx_recv);
      FREEMEM(domain->bnd[ibc].zdx_recv);
      FREEMEM(domain->bnd[ibc].zdx_neighbor);
      FREEMEM(domain->bnd[ibc].momflxtag);
      len = domain->sldbnd[ibc].len_nsend1 +
            domain->sldbnd[ibc].len_nsend2;
      if (len > 0) {
         FREEMEM(domain->sldbnd[ibc].ndx_send);
         FREEMEM(domain->sldbnd[ibc].zdx_send);
      }
      len = domain->sldbnd[ibc].len_nrecv1 +
            domain->sldbnd[ibc].len_nrecv2;
      if (len > 0) {
         FREEMEM(domain->sldbnd[ibc].ndx_recv);
         FREEMEM(domain->sldbnd[ibc].momflxtag);
      }
   }
   domain->nbnd = 0;
   func = rgst_list_attr(A_OBJECT, "Function_ReGenDomainFree");
   while (func != NULL) {
      Command_t *cp = (Command_t *) func->rgst_obj->obj;
      (*(cp->proc))(domain->hash);  
      func = func->next;
   }
}
