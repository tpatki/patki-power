#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Conditional.h"
#include "Command.h"
int Conditional_setup_attrs(void)
{
  char *me = "Conditional_setup_attrs";
  static int first_time_thru = TRUE;
  char *fields[10] = {
    "id",             "once",   "active",
    "expression_len", "msg_len",
    "expression",     "msg",
    NULL
  };
  char *attrs[2] = {"dump", NULL};
  if (RGST_ADD_MULT_FIELD_ATTRS("Conditional_t",fields,attrs) != 0)
     ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
  if (first_time_thru == TRUE) {
    inst_c("Conditional_init",      Conditional_init,      zargse, 0, symtab);
    inst_c("Conditional_construct", Conditional_construct, zargse, 0, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
int Conditional_init(Conditional_t *ptr)
{
   ptr->id             = -1;
   ptr->active         = 1;
   ptr->once           = 0;
   ptr->msg_len        = 0;
   ptr->expression_len = 0;
   ptr->expression     = NULL;
   ptr->msg            = NULL;
   ptr->next           = NULL;
  return(0);
}
Conditional_t *Conditional_construct(int num)
{
  char *me = "Conditional_construct";
  int i;
  Conditional_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(Conditional_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    Conditional_init(&(ptr[i]));
  }
  return(ptr);
}
