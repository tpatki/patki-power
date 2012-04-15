#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "BoundaryCondition.h"
#include "Command.h"
#include "Hash.h"
#include "NodeList.h"
int BoundaryCondition_setup_attrs(void)
{
  char *me = "BoundaryCondition_setup_attrs";
  static int first_time_thru = TRUE;
  if (RGST_ADD_ATTR_TO_FIELDS("BoundaryCondition_t","dump") != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  if (first_time_thru == TRUE) {
    inst_c("BoundaryCondition_init", BoundaryCondition_init, zargse, 0, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
int BoundaryCondition_init(BoundaryCondition_t *ptr)
{
  ptr->type        = 0;
  ptr->rtype       = 0;;
  ptr->mode        = 0;
  ptr->ndx         = NULL;
  ptr->len         = 0;
  ptr->zonelist    = NULL;
  ptr->lenZonelist = 0;
  ptr->pn          = 0;
  ptr->rz          = 0;
  ptr->pz          = 0;
  ptr->nx          = 0.0;
  ptr->ny          = 0.0;
  ptr->nz          = 0.0;
  ptr->id          = 0;
  ptr->ngrp        = 0;
  ptr->lgrp        = 0;
  return(0);
}
void BoundaryCondition_merge(Domain_t *domain) {
   char *name;
   int ibc;
   int nbc;
   int numbc;
   NodeList_t *NodeList = NULL;
   NodeWindow_t *ndxin     = NULL;
   NodeWindow_t *ndxin_ptr = NULL;
   BoundaryCondition_t *bc_new;
   BoundaryCondition_t *bc_ptr;
   HashElm_t **hashlist;
   bc_new = MALLOT(BoundaryCondition_t, nbcx);
   for (ibc = 0; ibc < nbcx; ibc++) {
      BoundaryCondition_init(&bc_new[ibc]);
   }
   for (ibc = 0; ibc < domain->nbc; ibc++) {
      name = domain->bc[ibc].ndxName;
      bc_ptr = (BoundaryCondition_t *) hash_lookup_obj(name, domain->hash);
      if (bc_ptr == NULL) {
	 bc_ptr = &domain->bc[ibc];
         hash_add(name, "BoundaryCondition_t", bc_ptr, domain->hash);
      }
   }
   hashlist = hash_get_elm_list(&numbc, "BoundaryCondition_t", domain->hash);
   nbc = 0;
   for (ibc = 0; ibc < numbc; ibc++) {
      bc_ptr = (BoundaryCondition_t *) hashlist[ibc]->obj;
      name   = bc_ptr->ndxName;
      NodeList = NodeList_find(name);
      ndxin_ptr = NodeList->list;
      while (ndxin_ptr != NULL) {
         int gblk = domain->gblk;
         int len  = NodeWindow_fastndx(ndxin_ptr,gblk,NDX_REAL, NDX_NODAL);
         if (len > 0) {
            int i;
            bc_new[nbc].ndx = MALLOT(int,len);
            for (i = 0; i < len; i++) {
               bc_new[nbc].ndx[i] = ndxin_ptr->ndx[i];
            }
            bc_new[nbc].type  = bc_ptr->type;
            bc_new[nbc].rtype = bc_ptr->rtype;
            bc_new[nbc].mode  = bc_ptr->mode ;
            bc_new[nbc].nx    = bc_ptr->nx   ;
            bc_new[nbc].ny    = bc_ptr->ny   ;
            bc_new[nbc].nz    = bc_ptr->nz   ;
            bc_new[nbc].pn    = bc_ptr->pn   ;
            bc_new[nbc].pz    = bc_ptr->pz   ;
            bc_new[nbc].rz    = bc_ptr->rz   ;
            bc_new[nbc].len   = len          ;
            strcpy(bc_new[nbc].ndxName, bc_ptr->ndxName);
            nbc++;
         }
         NodeWindow_freendx(ndxin_ptr);
         ndxin_ptr = ndxin_ptr->next;
      }
      hash_del2(name,"BoundaryCondition_t", domain->hash);
   }
   FREEMEM(hashlist);
   for (ibc = 0; ibc < domain->nbc; ibc++) {
      FREEMEM(domain->bc[ibc].ndx);
   }
   FREEMEM(domain->bc);
   domain->bc  = bc_new;
   domain->nbc = nbc;
}
