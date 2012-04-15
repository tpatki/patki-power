#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Command.h"
#include "Region.h"
int OpacityGroup_setup_attrs(void)
{
  char *me = "OpacityGroup_setup_attrs";
  static int first_time_thru = TRUE;
  if ((RGST_ADD_ATTR_TO_FIELDS("OpacityGroup_t","dump")) != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  if (first_time_thru == TRUE) {
    inst_c("OpacityGroup_init",     OpacityGroup_init,      zargse, 0, symtab);
    inst_c("OpacityGroup_construct",OpacityGroup_construct, zargse, 0, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
int OpacityGroup_init(OpacityGroup_t *ptr)
{
  Database_init(&(ptr->planckTable));
  Database_init(&(ptr->rosTable));
  Database_init(&(ptr->multiGroupTable));
  ptr->planckTable.form		= -1   ;
  ptr->rosTable.form		= -1   ;
  ptr->multiGroupTable.form	= -1   ;
  ptr->numSpeciesInGroup	= 0    ;
  ptr->speclist			= NULL ;
  ptr->densityMultiplier	= 1.0  ;
  ptr->planckMultiplier		= 1.0  ;
  ptr->rosMultiplier		= 1.0  ;
  ptr->KTfloor                  = ktfloor ;
  return(0);
}
OpacityGroup_t *OpacityGroup_construct(int num)
{
  char *me = "OpacityGroup_construct";
  int i;
  OpacityGroup_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(OpacityGroup_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    OpacityGroup_init(&(ptr[i]));
  }
  return(ptr);
}
