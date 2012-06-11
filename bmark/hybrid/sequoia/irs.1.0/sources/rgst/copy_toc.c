#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "irs.h"
#include "irsrgst.h"
#include "Rgst.h"

#ifdef SILO
DBtoc *copy_toc(
  DBtoc *in_toc)  
{
  char  *me = "copy_toc";
  int    i;
  DBtoc *out_toc;
  if ((out_toc = ALLOT(DBtoc, 1)) == NULL) ctlerror(me,gv_errmsg_memory);
  memcpy(out_toc, in_toc, sizeof(DBtoc));
  out_toc->curve_names = NULL;
  out_toc->multimesh_names = NULL;
  out_toc->multivar_names = NULL;
  out_toc->multimat_names = NULL;
  out_toc->multimatspecies_names = NULL;
  out_toc->qmesh_names = NULL;
  out_toc->qvar_names = NULL;
  out_toc->ucdmesh_names = NULL;
  out_toc->ucdvar_names = NULL;
  out_toc->ptmesh_names = NULL;
  out_toc->ptvar_names = NULL;
  out_toc->mat_names = NULL;
  out_toc->matspecies_names = NULL;
  out_toc->var_names = NULL;
  out_toc->obj_names = NULL;
  out_toc->dir_names = NULL;
  out_toc->array_names = NULL;
  if (out_toc->ncurve > 0) {
    out_toc->curve_names = ALLOT(char *, out_toc->ncurve);
    for (i=0; i<out_toc->ncurve; i++) {
      out_toc->curve_names[i] = strsave(in_toc->curve_names[i]);
    }
  }
  if (out_toc->nmultimesh > 0) {
    out_toc->multimesh_names = ALLOT(char *, out_toc->nmultimesh);
    for (i=0; i<out_toc->nmultimesh; i++) {
      out_toc->multimesh_names[i] = strsave(in_toc->multimesh_names[i]);
    }
  }
  if (out_toc->nmultivar > 0) {
    out_toc->multivar_names = ALLOT(char *, out_toc->nmultivar);
    for (i=0; i<out_toc->nmultivar; i++) {
      out_toc->multivar_names[i] = strsave(in_toc->multivar_names[i]);
    }
  }
  if (out_toc->nmultimat > 0) {
    out_toc->multimat_names = ALLOT(char *, out_toc->nmultimat);
    for (i=0; i<out_toc->nmultimat; i++) {
      out_toc->multimat_names[i] = strsave(in_toc->multimat_names[i]);
    }
  }
  if (out_toc->nmultimatspecies > 0) {
    out_toc->multimatspecies_names = ALLOT(char *, out_toc->nmultimatspecies);
    for (i=0; i<out_toc->nmultimatspecies; i++) {
      out_toc->multimatspecies_names[i] = strsave(in_toc->multimatspecies_names[i]);
    }
  }
  if (out_toc->nqmesh > 0) {
    out_toc->qmesh_names = ALLOT(char *, out_toc->nqmesh);
    for (i=0; i<out_toc->nqmesh; i++) {
      out_toc->qmesh_names[i] = strsave(in_toc->qmesh_names[i]);
    }
  }
  if (out_toc->nqvar > 0) {
    out_toc->qvar_names = ALLOT(char *, out_toc->nqvar);
    for (i=0; i<out_toc->nqvar; i++) {
      out_toc->qvar_names[i] = strsave(in_toc->qvar_names[i]);
    }
  }
  if (out_toc->nucdmesh > 0) {
    out_toc->ucdmesh_names = ALLOT(char *, out_toc->nucdmesh);
    for (i=0; i<out_toc->nucdmesh; i++) {
      out_toc->ucdmesh_names[i] = strsave(in_toc->ucdmesh_names[i]);
    }
  }
  if (out_toc->nucdvar > 0) {
    out_toc->ucdvar_names = ALLOT(char *, out_toc->nucdvar);
    for (i=0; i<out_toc->nucdvar; i++) {
      out_toc->ucdvar_names[i] = strsave(in_toc->ucdvar_names[i]);
    }
  }
  if (out_toc->nptmesh > 0) {
    out_toc->ptmesh_names = ALLOT(char *, out_toc->nptmesh);
    for (i=0; i<out_toc->nptmesh; i++) {
      out_toc->ptmesh_names[i] = strsave(in_toc->ptmesh_names[i]);
    }
  }
  if (out_toc->nptvar > 0) {
    out_toc->ptvar_names = ALLOT(char *, out_toc->nptvar);
    for (i=0; i<out_toc->nptvar; i++) {
      out_toc->ptvar_names[i] = strsave(in_toc->ptvar_names[i]);
    }
  }
  if (out_toc->nmat > 0) {
    out_toc->mat_names = ALLOT(char *, out_toc->nmat);
    for (i=0; i<out_toc->nmat; i++) {
      out_toc->mat_names[i] = strsave(in_toc->mat_names[i]);
    }
  }
  if (out_toc->nmatspecies > 0) {
    out_toc->matspecies_names = ALLOT(char *, out_toc->nmatspecies);
    for (i=0; i<out_toc->nmatspecies; i++) {
      out_toc->matspecies_names[i] = strsave(in_toc->matspecies_names[i]);
    }
  }
  if (out_toc->nvar > 0) {
    out_toc->var_names = ALLOT(char *, out_toc->nvar);
    for (i=0; i<out_toc->nvar; i++) {
      out_toc->var_names[i] = strsave(in_toc->var_names[i]);
    }
  }
  if (out_toc->nobj > 0) {
    out_toc->obj_names = ALLOT(char *, out_toc->nobj);
    for (i=0; i<out_toc->nobj; i++) {
      out_toc->obj_names[i] = strsave(in_toc->obj_names[i]);
    }
  }
  if (out_toc->ndir > 0) {
    out_toc->dir_names = ALLOT(char *, out_toc->ndir);
    for (i=0; i<out_toc->ndir; i++) {
      out_toc->dir_names[i] = strsave(in_toc->dir_names[i]);
    }
  }
  if (out_toc->narrays > 0) {
    out_toc->array_names = ALLOT(char *, out_toc->narrays);
    for (i=0; i<out_toc->narrays; i++) {
      out_toc->array_names[i] = strsave(in_toc->array_names[i]);
    }
  }
  return(out_toc);
}
#endif
