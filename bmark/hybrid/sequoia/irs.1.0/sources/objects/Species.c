#include "irs.h"
#include "irsctl.h"
#include "irsreg.h"
#include "irsrgst.h"
#include "Region.h"
#include "UserList.h"
#include "Command.h"
int Species_setup_attrs(void)
{
  char *me = "Species_setup_attrs";
  static int first_time_thru = TRUE;
  char *fields[50] = {
	"name",	"id",   "ncomp",         "reaction",
	"abar",	"zbar", "massFraction0", "atomFraction0",
	"mass",	"comp",
        NULL};
  char *attrs[2] = {"dump", NULL};
  if (RGST_ADD_MULT_FIELD_ATTRS("Species_t",fields,attrs) != 0)
    ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
  if (first_time_thru == TRUE) {
    inst_c("Species_init",      Species_init,      zargse, 0, symtab);
    inst_c("Species_construct", Species_construct, zargse, 0, symtab);

#ifdef SILO
    inst_c("Species_post_read", Species_post_read, zargse, 0, symtab);
#endif
    first_time_thru = FALSE;
  }
  return(0);
}
int Species_init(Species_t *ptr)
{
  memset(ptr->name,'\0',32);
  ptr->id 		= nspecies;
  ptr->ncomp 		= 0;
  ptr->reaction 	= 0;
  ptr->abar 		= -1.0;
  ptr->zbar 		= -1.0;
  ptr->massFraction0 	= -1.0;
  ptr->atomFraction0 	= -1.0;
  ptr->mass 		= 0.0;
  ptr->comp 		= NULL;
  ptr->next 		= NULL;
  return(0);
}
Species_t *Species_construct(int num)
{
  char *me = "Species_construct";
  int i;
  Species_t *spec;
  if (num < 1) ctlerror(me,logic_err);
  spec = ALLOT(Species_t, num);
  if (spec == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    Species_init(&(spec[i]));
  }
  return(spec);
}

#ifdef SILO
int Species_post_read(
  DBfile    *idbid,	 
  Species_t *ptr,	 
  char      *field_name) 
{
  Species_t *spec;
  if (species_find(ptr->name) == NULL) {
    spec = Species_construct(1);
    species_copy(spec, ptr);
    species_add(spec);
    nspecies++;
  }
  return(0);
}
#endif
int Species_getlist(int *list, char *name, Species_t *slist, int slen)
{
   int i, len;
   UserList_t *ul = NULL;
   ul = UserList_find(name);
   if (ul == NULL) return(0);
   len = 0;
   while (ul != NULL) {
      for (i = 0; i < slen; i++) {
         if (!strcmp(ul->name, slist[i].name)) {
            list[len++] = i;
            break;
         }
      }
      ul = ul->next;
   }
   return(len);
}
