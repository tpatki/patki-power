#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Command.h"
#include "Region.h"
int Database_setup_attrs(void)
{
  char *me = "Database_setup_attrs";
  static int first_time_thru = TRUE;
  if (RGST_ADD_ATTR_TO_FIELDS("Database_t","dump") != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  if (first_time_thru == TRUE) {
    inst_c("Database_init",     Database_init,      zargse, 0, symtab);
    inst_c("Database_construct",Database_construct, zargse, 0, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
int Database_init(Database_t *ptr)
{
  ptr->type 	     = _Null_ ;
  ptr->number 	     = 0 ;
  ptr->interp_method = 0 ;
  ptr->form 	     = 0 ;
  ptr->ndata 	     = 0 ;
  ptr->data 	     = NULL ;
  ptr->refd 	     = -1.0 ;
  ptr->rhomin        = -1.0 ;
  ptr->rhomax        = -1.0 ;
  ptr->t0            = -1.0 ;
  ptr->abar 	     = -1.0 ;
  ptr->zbar 	     = -1.0 ;
  return(0);
}
Database_t *Database_construct(int num)
{
  char *me = "Database_construct";
  int i;
  Database_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(Database_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    Database_init(&(ptr[i]));
  }
  return(ptr);
}
