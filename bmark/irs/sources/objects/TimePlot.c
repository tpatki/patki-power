#include "irs.h"
#include "irsctl.h"
#include "irsrgst.h"
#include "Command.h"
#include "Hash.h"
#include "TimePlot.h"
#include "FreqMesg.h"
int TimePlot_setup_attrs(void)
{
  char *me = "TimePlot_setup_attrs";
  static int first_time_thru = TRUE;
  char *fields[20] = {
        "name",			"fq_name",		"cyc_name",
	"tp_curs_names",
        "num_data_pts",		"max_data_pts",		"alloc_data_pts",
	"inc_data_pts",		"num_tp_curs",
        NULL};
  char *attrs[2] = {"dump", NULL};
  if (RGST_ADD_MULT_FIELD_ATTRS("TimePlot_t",fields,attrs) != 0)
    ctlerror(me,gv_errmsg_rgst_add_mult_attrs);
  if (first_time_thru == TRUE) {
    inst_c("TimePlot_init",      TimePlot_init,      zargse, 0, symtab);
    inst_c("TimePlot_construct", TimePlot_construct, zargse, 0, symtab);
    inst_c("TimePlot_destruct",  TimePlot_destruct,  zargse, 0, symtab);
#ifdef SILO
    inst_c("TimePlot_write",     TimePlot_write,     zargse, 0, symtab);
    inst_c("TimePlot_post_read", TimePlot_post_read, zargse, 0, symtab);
#endif
    first_time_thru = FALSE;
  }
  return(0);
}
int TimePlot_init(TimePlot_t *ptr)
{
  ptr->name		= NULL;
  ptr->fq_name		= NULL;
  ptr->fq_dat		= NULL;
  ptr->cyc_name		= NULL;
  ptr->cyc_dat		= NULL;
  ptr->tp_curs		= NULL;
  ptr->tp_curs_names	= NULL;
  ptr->num_data_pts	= 0;
  ptr->max_data_pts	= 0;
  ptr->alloc_data_pts	= 0;
  ptr->inc_data_pts	= 0;
  ptr->num_tp_curs	= 0;
  return(0);
}
TimePlot_t *TimePlot_construct(int num)
{
  char *me = "TimePlot_construct";
  int i;
  TimePlot_t *ptr;
  if (num < 1) ctlerror(me,logic_err);
  ptr = ALLOT(TimePlot_t, num);
  if (ptr == NULL) ctlerror(me,gv_errmsg_memory);
  for (i=0; i<num; i++) {
     TimePlot_init(&(ptr[i]));
  }
  return(ptr);
}
TimePlot_t * TimePlot_destruct(TimePlot_t *ptr)
{
  int i;
  if (ptr != NULL) {
    for (i=0; i<ptr->num_tp_curs; i++) {
      FREEMEM(ptr->tp_curs_names[i]);
    }
    FREEMEM(ptr->name); 
    FREEMEM(ptr->fq_name);
    FREEMEM(ptr->cyc_name); 
    FREEMEM(ptr->tp_curs); 
    FREEMEM(ptr->tp_curs_names);
    FREEMEM(ptr);
  }
  return(NULL);
}

#ifdef SILO
int TimePlot_write(
  DBfile      *idbid,   
  TimePlot_t  *ptr,     
  char *field_name)     
{
  char *me = "TimePlot_write";
  char msg[128], dirname[64];
  int i;
  for (i=0; i<ptr->num_tp_curs; i++) {
    sprintf(dirname,"TimePlotCurve%i",i);
    if (rgst_write_struct_in_dir(idbid,dirname,"TimePlotCurve_t",ptr->tp_curs[i],NULL) != 0) {
      ctlerror(me,gv_errmsg_rgst_write_struct_in_dir);
    }
  }
  return(0);
}
#endif

#ifdef SILO
int TimePlot_post_read(
  DBfile *idbid,	
  TimePlot_t *ptr,	
  char *field_name)	
{
  char *me = "TimePlot_post_read";
  char msg[128], str[128], dirname[64];
  int i, n, ierr = 0;
  TimePlotCurve_t *my_tpc;
  ptr->tp_curs       = ALLOT(TimePlotCurve_t *, ptr->num_tp_curs);
  for (i=0; i<ptr->num_tp_curs; i++) {
    sprintf(dirname,"TimePlotCurve%i",i);
    my_tpc = rgst_read_struct_in_dir(idbid, dirname, "TimePlotCurve_t", NULL, NULL);		            
    if (my_tpc == NULL) ctlerror(me,gv_errmsg_rgst_read_struct_in_dir);
    ptr->tp_curs[i]       = my_tpc;
  }
  if (ptr->fq_name != NULL) {
    ptr->fq_dat = rgst_get_t(ptr->fq_name,"FreqMesg_t");
    if (ptr->fq_dat == NULL) {
      sprintf(msg,"time frequency '%s' not found in registry",ptr->fq_name);
      ctlerror(me,msg);
    }
  }
  if (ptr->cyc_name != NULL) {
    ptr->cyc_dat = rgst_get_t(ptr->cyc_name,"CycleMesg_t");
    if (ptr->cyc_dat == NULL) {
      sprintf(msg,"cycle frequency '%s' not found in registry",ptr->cyc_name);
      ctlerror(me,msg);
    }
  }
  rgst_add(ptr->name,"TimePlot_t",ptr,NULL);
  return(0);
}
#endif

void TimePlot_expand(TimePlot_t *tp) 
{
  char *me = "TimePlot_expand";
  int i, j, k, old_alloc_data_pts;
  TimePlotCurve_t *tpc;
  old_alloc_data_pts = tp->alloc_data_pts;
  tp->alloc_data_pts += tp->inc_data_pts;
  if (tp->alloc_data_pts > tp->max_data_pts) {
    tp->max_data_pts = tp->alloc_data_pts + tp->inc_data_pts;
  }
  for (i=0; i<tp->num_tp_curs; i++) {
    tpc = tp->tp_curs[i];
    if (tpc != NULL) {
      for (j=0; j < tpc->num_vals; j++) {
	tpc->alloc_data_pts[j] = tp->alloc_data_pts;
        if (tpc->data[j] == NULL) {
          tpc->data[j] = ALLOT(double, tp->alloc_data_pts);
	  for (k=0; k<tp->alloc_data_pts; k++) {
            tpc->data[j][k] = 0.0;
	  }
        }
        else {
          tpc->data[j] = REALLOT(tpc->data[j], double, tp->alloc_data_pts);
	  for (k=old_alloc_data_pts; k<tp->alloc_data_pts; k++) {
	    tpc->data[j][k] = 0.0;
          }
        }
        if (tpc->data[j] == NULL) {
          ctlerror(me,gv_errmsg_memory);
        }
      }
    }
  }
}
