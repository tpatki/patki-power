#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Region.h"
#include "Spline.h"
#include "Command.h"
int Spline_setup_attrs(void)
{
  char *me = "Spline_setup_attrs";
  static int first_time_thru = TRUE;
  char *fields[25] = {
    "name",   "type",   "coord", "flip",
    "indlab", "deplab",
    "x0",     "y0",     "z0",
    "axis_x", "axis_y", "axis_z",
    "norm_x", "norm_y", "norm_z",
    "len",    "dep",    "ind",
    "dep1",   "dep2",
    NULL
  };
  char *attrs[2] = {"dump", NULL};
  if (RGST_ADD_MULT_FIELD_ATTRS("Spline_t",fields,attrs) != 0)
     ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
  if (first_time_thru == TRUE) {
    inst_c("Spline_init",     Spline_init,      zargse, 0, symtab);
    inst_c("Spline_construct",Spline_construct, zargse, 0, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
int Spline_init(Spline_t *ptr)
{
  memset(ptr->name,  '\0',MAXWORD);
  memset(ptr->indlab,'\0',2);
  memset(ptr->deplab,'\0',2);
  ptr->type   = 0;
  ptr->flip   = 0;
  ptr->len    = 0;
  ptr->coord  = UNKNOWNDATA;
  ptr->ind    = NULL;
  ptr->dep    = NULL;
  ptr->b      = NULL;
  ptr->c      = NULL;
  ptr->d      = NULL;
  ptr->next   = NULL;
  ptr->x0     = 0.0;
  ptr->y0     = 0.0;
  ptr->z0     = 0.0;
  ptr->axis_x = 1.0;
  ptr->axis_y = 0.0;
  ptr->axis_z = 0.0;
  ptr->norm_x = plarge;
  ptr->norm_y = plarge;
  ptr->norm_z = plarge;
  ptr->dep1   = plarge;
  ptr->dep2   = plarge;
  return(0);
}
Spline_t *Spline_construct(int num)
{
  char *me = "Spline_construct";
  int i;
  Spline_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(Spline_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    Spline_init(&(ptr[i]));
  }
  return(ptr);
}
