#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Boundary.h"
#include "Command.h"
static char *bnd_fields[50] = {
       "active",      "blk_send",   "bndnbc",      "orientation",
       "pn",          "rz",         "pz",
       "len_nsend1",  "len_nsend2", "len_nsendc",  "len_nsendtot",
       "len_zsend1",  "len_zsend2", "len_zsendc",  "len_zsendtot",
       "len_nrecv1",  "len_nrecv2", "len_nrecvc",  "len_nrecvtot",
       "len_zrecv1",  "len_zrecv2", "len_zrecvc",  "len_zrecvtot",
       "ndx_send",    "zdx_send",   "ndx_recv",    "zdx_recv",
       "encon","pn_vector", "momflxtag", "len_momflxtag",
       "zdx_neighbor",
       NULL};
static char *sldbnd_fields[25] = {
       "active", "blk_send",    "bndnbc",
       "pn",          "rz",         "pz",
       "len_nsend1",  "len_nsend2", "len_nsendc",  "len_nsendtot",
                                                   "len_zsendtot",
       "len_nrecv1",  "len_nrecv2", "len_nrecvc",  "len_nrecvtot",
       "ndx_send",    "zdx_send",   "ndx_recv",
       "momflxtag", "len_momflxtag",
       NULL};
static char *attrs[2] = {"dump", NULL};
int Boundary_setup_attrs(void)
{
  char *me = "Boundary_setup_attrs";
  static int first_time_thru = TRUE;
  if (RGST_ADD_MULT_FIELD_ATTRS("Boundary_t",bnd_fields,attrs) != 0)
    ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
  if (first_time_thru == TRUE) {
#ifdef SILO
    inst_c("Boundary_write",    Boundary_write,    zargse, 0, symtab);
    inst_c("Boundary_pre_read", Boundary_pre_read, zargse, 0, symtab);
#endif
    first_time_thru = FALSE;
  }
  return(0);
}

#ifdef SILO
int Boundary_write(
  DBfile *idbid, 	
  Boundary_t *ptr, 	
  char *field)		
{
  char *me = "Boundary_write";
  if (RGST_DEL_ATTR_FROM_FIELDS("Boundary_t","dump") != 0)
    ctlerror(me,gv_errmsg_rgst_del_attrs_from_fields);
  if (strcmp(field,"bnd") == 0) {
    if (RGST_ADD_MULT_FIELD_ATTRS("Boundary_t",bnd_fields,attrs) != 0) {
      ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
    }
    ptr->len_nsendtot = ptr->len_nsend1 + ptr->len_nsend2 + ptr->len_nsendc;
    ptr->len_zsendtot = ptr->len_zsend1 + ptr->len_zsend2 + ptr->len_zsendc;
    ptr->len_nrecvtot = ptr->len_nrecv1 + ptr->len_nrecv2 + ptr->len_nrecvc;
    ptr->len_zrecvtot = ptr->len_zrecv1 + ptr->len_zrecv2 + ptr->len_zrecvc;
  } else if (strcmp(field,"sldbnd") == 0) {
    if (RGST_ADD_MULT_FIELD_ATTRS("Boundary_t",sldbnd_fields,attrs) != 0) {
      ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
    }
    ptr->len_nsendtot = ptr->len_nsend1 + ptr->len_nsend2 + ptr->len_nsendc;
    ptr->len_zsendtot = ptr->len_nsend1;
    ptr->len_nrecvtot = ptr->len_nrecv1 + ptr->len_nrecv2 + ptr->len_nrecvc;
  } else {
    Boundary_setup_attrs();
  }
  return(0);
}
#endif

#ifdef SILO
int Boundary_pre_read(
  DBfile *idbid, 	
  Boundary_t *ptr, 	
  char *field)		
{
  char *me = "Boundary_pre_read";
  if (RGST_DEL_ATTR_FROM_FIELDS("Boundary_t","dump") != 0)
    ctlerror(me,gv_errmsg_rgst_del_attrs_from_fields);
  if (strcmp(field,"bnd") == 0) {
    if (RGST_ADD_MULT_FIELD_ATTRS("Boundary_t",bnd_fields,attrs) != 0) {
      ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
    }
  } else if (strcmp(field,"sldbnd") == 0) {
    if (RGST_ADD_MULT_FIELD_ATTRS("Boundary_t",sldbnd_fields,attrs) != 0) {
      ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
    }
    ptr->active       = 1;
    ptr->len_zsend1   = 0;
    ptr->len_zsend2   = 0;
    ptr->len_zsendc   = 0;
    ptr->len_zrecv1   = 0;
    ptr->len_zrecv2   = 0;
    ptr->len_zrecvc   = 0;
    ptr->len_zrecvtot = 0;
  } else {
    Boundary_setup_attrs();
  }
  return(0);
}
#endif
