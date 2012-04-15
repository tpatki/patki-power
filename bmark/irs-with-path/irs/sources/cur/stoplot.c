#include <unistd.h>		
#include "irs.h"
#include "irscur.h"
#include "irsctl.h"
#include "irsgenrd.h"
#include "irsrgst.h"
#include "cgl.h"
#include "AEStackElm.h"
#include "Hash.h"
#include "FunctionTimer.h"
#include "TimePlot.h"
#define MAX_VALS        64
void stoplot(int my_itp)	
{
  char *me = "stoplot";
  char msg[512], *ps_save, *line_save, sym_save[MAXLINE];
  int  i, ii, j, jj, ae_num, curve_num, data_ndx, error, symflag_save;
  int  num_vals, num_stack_elms, first_time_thru;
  int  output_dest_save;
  TimePlot_t  *my_tpd;
  TimePlotCurve_t  *my_tpc;
  AEStackElm_t *ae_elm, *ae_array[MAX_VALS];
  double myflops = 1 ;
  FT_INITIALIZE(me, gv_hash_tbl);
  itp = my_itp;
  my_tpd = tpdata[my_itp];
  data_ndx = my_tpd->num_data_pts;
  if (data_ndx >= my_tpd->alloc_data_pts) {
    TimePlot_expand(my_tpd);
    if (data_ndx >= my_tpd->alloc_data_pts) ctlerror(me,logic_err);
  }
  for (curve_num=0; curve_num<my_tpd->num_tp_curs; curve_num++) {
    my_tpc = my_tpd->tp_curs[curve_num];
    if (my_tpc == NULL)  { ctlerror(me,logic_err); }
    memcpy(sym_save, sym, MAXLINE);
    line_save = line;
    ps_save = ps;
    symflag_save = symflag;
    memset(sym, '\0', MAXLINE);
    line = NULL;
    ps = my_tpc->eval_string;
    symflag = 0;
    output_dest_save = output_dest;
    output_dest = TO_STACK;
    error = docmd();
    output_dest = output_dest_save;
    memcpy(sym, sym_save, MAXLINE);
    line = line_save;
    ps = ps_save;
    symflag = symflag_save;
    first_time_thru = FALSE;
    if (hash_lookup_elm(my_tpc->eval_string,gv_hash_tbl) == NULL) {
      first_time_thru = TRUE;
      hash_add(my_tpc->eval_string,"boolean flag", NULL, gv_hash_tbl);
    }
    num_stack_elms = ae_stack_num_vals(NULL);
    if (num_stack_elms > MAX_VALS) {
      ctlerror(me,"have programmer increase MAX_VALS");    
    }
    if (num_stack_elms < 1) {
      if (first_time_thru == TRUE) {
        sprintf(msg,"\n\tEvaluation of '%s'"
                    "\n\tleft no data on the stack!"
                    "\n\tAttempting to recover by using data point value of 0.0",
                    my_tpc->eval_string);
        ctlnotice(me,msg);
      }
      num_stack_elms = 1;
      ae_stack_push(me,NULL,R_DOUBLE,0.0);
    }
    num_vals = 0;
    for (ii=0; ii<num_stack_elms; ii++) {
      ae_array[ii] = ae_stack_pop();
      if (ae_array[ii] == NULL) ctlerror(me,logic_err);
      if   (  (ae_array[ii]->type == R_INT)
           || (ae_array[ii]->type == R_DOUBLE)) {
        num_vals++;
      }
      else if (  (ae_array[ii]->type == R_INT_ARRAY)
              || (ae_array[ii]->type == R_DOUBLE_ARRAY)) {
        num_vals = num_vals + ae_array[ii]->len;
      }
      else {
         ctlerror(me,logic_err);
      }
    }
    ae_stack_empty_check();
    if (my_tpc->num_vals == 0) {
      my_tpc->num_vals       = num_vals;
      my_tpc->labels         = ALLOT (char *,   num_vals);
      my_tpc->data           = ALLOT (double *, num_vals);
      my_tpc->alloc_data_pts = ALLOT (int,      num_vals);
      for (ii=0; ii<num_vals; ii++) {
        my_tpc->labels[ii]         = NULL;
        my_tpc->alloc_data_pts[ii] = my_tpd->alloc_data_pts;
        my_tpc->data[ii]           = ALLOT(double, my_tpd->alloc_data_pts);
	for (jj=0; jj<my_tpd->alloc_data_pts; jj++) {
	  my_tpc->data[ii][jj] = 0.0;
        }
      }
    }
    else {
      if (num_vals != my_tpc->num_vals) { ctlerror(me,logic_err); }
    }
    num_vals = 0;
    for (ae_num=0; ae_num<num_stack_elms; ae_num++) {
      ae_elm = ae_array[ae_num];
      if      (ae_elm->type == R_INT) {
        if ( (ae_elm->label != NULL) && (my_tpc->labels[num_vals] == NULL) ) {
          my_tpc->labels[num_vals] = strsave(ae_elm->label);
        }
        my_tpc->data[num_vals][data_ndx] = (double)ae_elm->i_value;
        num_vals++;
      }
      else if (ae_elm->type == R_DOUBLE) {
        if ( (ae_elm->label != NULL) && (my_tpc->labels[num_vals] == NULL) ) {
          my_tpc->labels[num_vals] = strsave(ae_elm->label);
        }
        my_tpc->data[num_vals][data_ndx] = ae_elm->d_value;
        num_vals++;
      }
      else if (ae_elm->type == R_INT_ARRAY) {
        for (j=0; j < ae_elm->len; j++) {
          if ( (ae_elm->label != NULL) && (my_tpc->labels[num_vals] == NULL) ) {
            sprintf(msg,"%s [%d]",ae_elm->label,j);
            my_tpc->labels[num_vals] = strsave(msg);
          }
          my_tpc->data[num_vals][data_ndx] = (double)ae_elm->i_array[j];
          num_vals++;
        }
      }
      else if (ae_elm->type == R_DOUBLE_ARRAY) {
        for (j=0; j < ae_elm->len; j++) {
          if ( (ae_elm->label != NULL) && (my_tpc->labels[num_vals] == NULL) ) {
            sprintf(msg,"%s [%d]",ae_elm->label,j);
            my_tpc->labels[num_vals] = strsave(msg);
          }
          my_tpc->data[num_vals][data_ndx] = ae_elm->d_array[j];
          num_vals++;
        }
      }
      else {
        ctlerror(me,logic_err);
      }
      ae_array[ae_num] = AEStackElm_destruct(ae_array[ae_num]);
    } 
    if (num_vals != my_tpc->num_vals) { ctlerror(me,logic_err); }
  } 
  my_tpd->num_data_pts++; 
  hash_optimize(&gv_hash_tbl);
  FT_FINALIZE(me, gv_hash_tbl, myflops)
}
