#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Command.h"
#include "Region.h"
int EosGroup_setup_attrs(void)
{
  char *me = "EosGroup_setup_attrs";
  static int first_time_thru = TRUE;
  if ((RGST_ADD_ATTR_TO_FIELDS("EosGroup_t","dump")) != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  if (first_time_thru == TRUE) {
    inst_c("EosGroup_init",     EosGroup_init,      zargse, 0, symtab);
    inst_c("EosGroup_construct",EosGroup_construct, zargse, 0, symtab);
    first_time_thru = FALSE;
  }
  return(0);
}
int EosGroup_init(EosGroup_t *ptr)
{
  Database_init(&(ptr->database));
  ptr->numSpeciesInGroup      =  0    ;
  ptr->speclist               =  NULL ;
  ptr->zstarform              = -1    ;
  ptr->econform               = -1    ;
  ptr->iconform               = -1    ;
  ptr->econvalue              =  0.0  ;
  ptr->iconvalue              =  0.0  ;
  ptr->e0                     =  0.0  ;
  ptr->refd                   = -1.0  ;
  ptr->etamax                 =  plarge ;
  ptr->etamin                 =  0.0  ;
  ptr->abar                   = -1.0  ;
  ptr->zbar                   = -1.0  ;
  ptr->densityMultiplier      =  1.0  ;
  ptr->energyMultiplier       =  1.0  ;
  ptr->ion_energyMultiplier   =  1.0  ;
  ptr->pressureMultiplier     =  1.0  ;
  ptr->ion_pressureMultiplier =  1.0  ;
  ptr->eicoupleMultiplier     =  1.0  ;
  return(0);
}
EosGroup_t *EosGroup_construct(int num)
{
  char *me = "EosGroup_construct";
  int i;
  EosGroup_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(EosGroup_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    EosGroup_init(&(ptr[i]));   
  }
  return(ptr);
}
