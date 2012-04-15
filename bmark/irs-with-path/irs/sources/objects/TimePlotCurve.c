#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Command.h"
#include "TimePlot.h"
#define STRLEN	256
int TimePlotCurve_setup_attrs(void)
{
  char *me = "TimePlotCurve_setup_attrs";
  int ierr = 0;
  static int first_time_thru = TRUE;
  if (RGST_ADD_ATTR_TO_FIELDS("TimePlotCurve_t","dump") != 0)
    ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
  if (first_time_thru == TRUE) {
    inst_c("TimePlotCurve_init",      TimePlotCurve_init,       zargse, 0, symtab);
    inst_c("TimePlotCurve_construct", TimePlotCurve_construct,  zargse, 0, symtab);
    inst_c("TimePlotCurve_destruct",  TimePlotCurve_destruct,   zargse, 0, symtab);
#ifdef SILO
    inst_c("TimePlotCurve_post_read", TimePlotCurve_post_read,  zargse, 0, symtab);
#endif
    first_time_thru = FALSE;
  }
  return(0);
}
int TimePlotCurve_init(TimePlotCurve_t *ptr)
{
  ptr->name       	= NULL;
  ptr->eval_string	= NULL;
  ptr->num_vals  	= 0;
  ptr->labels    	= NULL;
  ptr->data        	= NULL;
  ptr->alloc_data_pts	= NULL;
  return(0);
}
TimePlotCurve_t *TimePlotCurve_construct(int num)
{
  char *me = "TimePlotCurve_construct";
  int i;
  TimePlotCurve_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(TimePlotCurve_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
    TimePlotCurve_init(&(ptr[i]));
  }
  return(ptr);
}
TimePlotCurve_t * TimePlotCurve_destruct(TimePlotCurve_t *ptr)
{
  int i;
  if (ptr != NULL) {
    for (i=0; i<ptr->num_vals; i++) {
      FREEMEM(ptr->labels[i]);
      FREEMEM(ptr->data[i]);
    }
    FREEMEM(ptr->name);
    FREEMEM(ptr->eval_string);
    FREEMEM(ptr->labels);
    FREEMEM(ptr->data);
    FREEMEM(ptr->alloc_data_pts);
    FREEMEM(ptr);
  }
  return(NULL);
}
#ifdef SILO
int TimePlotCurve_post_read(
  DBfile *idbid,	
  TimePlotCurve_t *ptr,	
  char *field_name)	
{
  rgst_add(ptr->name,"TimePlotCurve_t",ptr,NULL);
  return(0);
}
#endif


TimePlotCurve_t *TimePlotCurve_create(
  char *sym,                 
  int   tpc_num)             
{
  char *me = "TimePlotCurve_create";
  char msg[128], label[256], label2[256], str[STRLEN];
  int i;
  TimePlotCurve_t    *tpc;
  if (  (strcmp(sym,"time") == 0) || (ctlflag == iflf)) {
    memset(str,'\0',STRLEN);
  }
  else {
    get_words_at_prompt(str,STRLEN);
  }
  strcpy(label,sym);
  strcat(label," ");
  strcat(label,str);
  strcpy(label2,label);
  strcat(label2,"$");
  tpc = TimePlotCurve_construct(1);
  sprintf(msg,"tp_%03d_%s_tp_curve",tpc_num,label);
  for (i=0; i<strlen(msg); i++) { 	
    if (msg[i] == ' ') { msg[i] = '_'; }
  }
  tpc->name        = strsave(msg);
  tpc->eval_string = strsave(label2);
  rgst_add(tpc->name,"TimePlotCurve_t",tpc,NULL);
  return(tpc);
}
