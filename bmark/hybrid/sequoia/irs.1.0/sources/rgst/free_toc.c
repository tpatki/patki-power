#include <stdio.h>                      
#include <stdlib.h>                     
#include "irs.h"              
#include "irsrgst.h"             
#include "Rgst.h"

#ifdef SILO
DBtoc *free_toc(
  DBtoc *toc)  
{
  int i;
  if (toc->ncurve > 0) {
    for (i=0; i<toc->ncurve; i++) FREEMEM(toc->curve_names[i]);
    FREEMEM(toc->curve_names);
  }
  if (toc->nmultimesh > 0) {
    for (i=0; i<toc->nmultimesh; i++) FREEMEM(toc->multimesh_names[i]);
    FREEMEM(toc->multimesh_names);
  }
  if (toc->nmultivar > 0) {
    for (i=0; i<toc->nmultivar; i++) FREEMEM(toc->multivar_names[i]);
    FREEMEM(toc->multivar_names);
  }
  if (toc->nmultimat > 0) {
    for (i=0; i<toc->nmultimat; i++) FREEMEM(toc->multimat_names[i]);
    FREEMEM(toc->multimat_names);
  }
  if (toc->nmultimatspecies > 0) {
    for (i=0; i<toc->nmultimatspecies; i++) FREEMEM(toc->matspecies_names[i]);
    FREEMEM(toc->multimatspecies_names);
  }
  if (toc->nqmesh > 0) {
    for (i=0; i<toc->nqmesh; i++) FREEMEM(toc->qmesh_names[i]);
    FREEMEM(toc->qmesh_names);
  }
  if (toc->nqvar > 0) {
    for (i=0; i<toc->nqvar; i++) FREEMEM(toc->qvar_names[i]);
    FREEMEM(toc->qvar_names);
  }
  if (toc->nucdmesh > 0) {
    for (i=0; i<toc->nucdmesh; i++) FREEMEM(toc->ucdmesh_names[i]);
    FREEMEM(toc->ucdmesh_names);
  }
  if (toc->nucdvar > 0) {
    for (i=0; i<toc->nucdvar; i++) FREEMEM(toc->ucdvar_names[i]);
    FREEMEM(toc->ucdvar_names);
  }
  if (toc->nptmesh > 0) {
    for (i=0; i<toc->nptmesh; i++) FREEMEM(toc->ptmesh_names[i]);
    FREEMEM(toc->ptmesh_names);
  }
  if (toc->nptvar > 0) {
    for (i=0; i<toc->nptvar; i++) FREEMEM(toc->ptvar_names[i]);
    FREEMEM(toc->ptvar_names);
  }
  if (toc->nmat > 0) {
    for (i=0; i<toc->nmat; i++) FREEMEM(toc->mat_names[i]);
    FREEMEM(toc->mat_names);
  }
  if (toc->nmatspecies > 0) {
    for (i=0; i<toc->nmatspecies; i++) FREEMEM(toc->matspecies_names[i]);
    FREEMEM(toc->matspecies_names);
  }
  if (toc->nvar > 0) {
    for (i=0; i<toc->nvar; i++) FREEMEM(toc->var_names[i]);
    FREEMEM(toc->var_names);
  }
  if (toc->nobj > 0) {
    for (i=0; i<toc->nobj; i++) FREEMEM(toc->obj_names[i]);
    FREEMEM(toc->obj_names);
  }
  if (toc->ndir > 0) {
    for (i=0; i<toc->ndir; i++) FREEMEM(toc->dir_names[i]);
    FREEMEM(toc->dir_names);
  }
  if (toc->narrays > 0) {
    for (i=0; i<toc->narrays; i++) FREEMEM(toc->array_names[i]);
    FREEMEM(toc->array_names);
  }
  FREEMEM(toc);
  return((DBtoc *) NULL);
}
#endif
