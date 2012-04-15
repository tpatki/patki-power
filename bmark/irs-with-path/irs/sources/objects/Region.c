#include "irs.h"
#include "irsctl.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "Command.h"
#include "Hash.h"
#include "Region.hh"
#include "FunctionTimer.h"
int Region_setup_attrs(void)
{
  char *me = "Region_setup_attrs";
  static int first_time_thru = TRUE;
  if ((RGST_ADD_ATTR_TO_FIELDS("Region_t","dump")) != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  RGST_DEL_FIELD_ATTR("Region_t","stress", "dump");
  if (first_time_thru == TRUE) {
#ifdef SILO
    inst_c("Region_write",    Region_write,   zargse, 0, symtab);
    inst_c("Region_pre_read", Region_pre_read,zargse, 0, symtab);
#endif
    inst_c("Region_init",     Region_init,      zargse, 0, symtab);
    inst_c("Region_construct",Region_construct, zargse, 0, symtab);
    inst_c("eos_init",eos_init, sargse, 1, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
int Region_init(Region_t *ptr)
{
  int i;
  ptr->eosGroup     = EosGroup_construct(ngroupx);
  ptr->opacityGroup = OpacityGroup_construct(ngroupx);
  ptr->stress             = NULL;
  ptr->reactions          = NULL;
  ptr->reactionMolesList  = NULL;
  ptr->species           = NULL;
  ptr->twoPhase         =  _TwoPhase_NoModel_;
  ptr->twoPhaseMaterial =  -1;
  ptr->type             =  _Nospecies_;
  ptr->numGroups        =  0;
  ptr->nspec            =  0;
  ptr->numReactions     =  0;
  ptr->numReactionMoles =  0;
  ptr->pminmd           =  0;
  ptr->burn             =  0;
  ptr->str              =  0;
  ptr->ioneq            = -1;
  ptr->color            =  0;
  ptr->damage           =  0;
  ptr->particulate      =  0;
  ptr->viscmodel        =  _ViscConst_; 
  ptr->por0    =  0.0  ;
  ptr->porfail =  2.0  ;
  ptr->etahold = -1.0  ;
  ptr->rlagrx  =  4.0 ;
  ptr->rxwgt   =  1.0  ;
  ptr->xray    =  0.04 ;
  ptr->bhe     = -1.0  ;
  ptr->detvel  =  0.0  ;
  ptr->plklmt  =  0.0  ;
  ptr->mfplmt  = -1.0  ;
  ptr->dmin    =  0.0  ;
  ptr->emin    = -1.0  ;
  ptr->pmin    = -0.01 ;
  ptr->qlin    = -1.0  ;
  ptr->qquad   = -1.0  ;
  ptr->hgfrac  = -1.0  ;
  ptr->visca   = 0.0;
  ptr->viscb   = 0.0;
  ptr->viscc   = 1.0;
  ptr->viscn   = 0.0;
  ptr->visccv  = 0.0;
  ptr->schmidt = 0.7;
  ptr->prandtl = 0.7;
  ptr->aturb   = 0.0;
  ptr->bturb   = 0.0;
  ptr->cturb   = 0.0;
  ptr->dturb   = 0.0;
  return(0);
}
Region_t *Region_construct(int num)
{
  char *me = "Region_construct";
  int i;
  Region_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(Region_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    Region_init(&(ptr[i]));
  }
  return(ptr);
}

#ifdef SILO
int Region_write(
  DBfile *idbid,	
  Region_t *ptr,	
  char *field_name)     
{

       {
    RGST_DEL_FIELD_ATTR("Region_t","twoPhaseMaterial", "dump");
    RGST_DEL_FIELD_ATTR("Region_t","twoPhase",         "dump");
  }
  if (ngroup > 0) {
    RGST_ADD_FIELD_ATTR("Region_t","opacityGroup", "dump");
  }
  else {
    RGST_DEL_FIELD_ATTR("Region_t","opacityGroup", "dump");
  }
  return(0);
}
#endif
#ifdef SILO
int Region_pre_read( 
  DBfile *idbid,  	
  Region_t *ptr,  	
  char *field_name)     
{
  ptr->numGroups = ngroupx;

       {
    RGST_DEL_FIELD_ATTR("Region_t","twoPhaseMaterial", "dump");
    RGST_DEL_FIELD_ATTR("Region_t","twoPhase",         "dump");
  }
  if (ngroup > 0) {
    RGST_ADD_FIELD_ATTR("Region_t","opacityGroup", "dump");
  }
  else {
    RGST_DEL_FIELD_ATTR("Region_t","opacityGroup", "dump");
  }
  return(0);
}
#endif
void Region_free( void ) {
   int ir;
   if (reg == NULL) return;
   for (ir = 0; ir <= nregx; ir++) {
      Region_destruct(&reg[ir]);
   }
   rgst_del("regionalData");
   FREEMEM(reg);
}
void Region_destruct( Region_t *region ) {
   int i;
   for (i = 0; i < region->nspec; i++) {
      FREEMEM(region->species[i].comp);
   }
   for (i = 0; i < region->numGroups; i++) {
      FREEMEM(region->eosGroup[i].database.data);
      if (region->eosGroup[i].numSpeciesInGroup > 0) {
         FREEMEM(region->eosGroup[i].speclist);
      }
   }
   FREEMEM(region->reactions);
   FREEMEM(region->reactionMolesList);
   FREEMEM(region->species);
   FREEMEM(region->eosGroup);
   FREEMEM(region->opacityGroup);
}
void Region_check( void )
{
   char *me = "Region_check" ;
   int ir ;
   double myflops = 1.0 ;
   FT_INITIALIZE(me, gv_hash_tbl)
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      if ( reg[ir].etahold == -1.0 ) {
         reg[ir].etahold = 1.0 ;
      }
      if ( reg[ir].ioneq < 0 ) {
         reg[ir].ioneq = 0 ;
      }
      if ( reg[ir].qlin == -1.0 ) {
         reg[ir].qlin = qlin ;
      }
      if ( reg[ir].qquad == -1.0 ) {
         reg[ir].qquad = xquad ;
      }
      if ( reg[ir].hgfrac == -1.0 ) {
         reg[ir].hgfrac = hgfrac ;
      }
   }
   FT_FINALIZE( me, gv_hash_tbl, myflops )
}
void EosGroup_check( void )
{
   char *me = "EosGroup_check" ;
   int ir, jeos ;
   double myflops = 1.0 ;
   FT_INITIALIZE(me, gv_hash_tbl)
   for ( ir = 1 ; ir <= nreg ; ir++ ) {
      for ( jeos = 0 ; jeos < reg[ir].numGroups ; jeos++ ) {
         if ( reg[ir].eosGroup[jeos].zstarform < 0 ) {
               reg[ir].eosGroup[jeos].zstarform = 0 ;
         }
         if ( reg[ir].eosGroup[jeos].econform < 0 ) {
            reg[ir].eosGroup[jeos].econform = 3 ;
	 }
         if ( reg[ir].eosGroup[jeos].iconform < 0 ) {
            reg[ir].eosGroup[jeos].iconform = 3 ;
	 }
      }
   }
   FT_FINALIZE( me, gv_hash_tbl, myflops )
}
