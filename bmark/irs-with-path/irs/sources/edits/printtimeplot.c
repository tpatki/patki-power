#include "irs.h"
#include "irsedits.h"
#include "TimePlot.h"
static char *datatype_str[3] = {"Int", "Float (double)", "Char" };
void printtimeplot (TimePlot_t *tp)
{
  int i, j;
  if (myid != 0) { return; }
  if (tp == NULL) { return; }
  printf("\n PRINT OF TIME PLOT '%s'\n",tp->name);
  printf("  name                       = %s\n",tp->name);
  if (tp->fq_name != NULL) {
    printf("  freq struct name           = %s\n",tp->fq_name);
    printf("  time start                 = %-10.5f\n",tp->fq_dat->t1);
    printf("  time stop                  = %-10.5f\n",tp->fq_dat->t2);
    printf("  time step                  = %-10.5f\n",tp->fq_dat->dt);
    printf("  next time for edit         = %-10.5f\n",tp->fq_dat->nextTime);
  }
  if (tp->cyc_name != NULL) {
    printf("  cycle struct name          = %s\n",tp->cyc_name);
    printf("  cycle start                = %d\n",tp->cyc_dat->c1);
    printf("  cycle stop                 = %d\n",tp->cyc_dat->c2);
    printf("  cycle step                 = %d\n",tp->cyc_dat->dc);
    printf("  next cycle for edit        = %d\n",tp->cyc_dat->nextCycle);
  }  
  printf("  max num of data pts        = %d\n",tp->max_data_pts);
  printf("  current num of data pts    = %d\n",tp->num_data_pts);
  printf("  allocated num data pts     = %d\n",tp->alloc_data_pts);
  printf("  increment num data pts     = %d\n",tp->inc_data_pts);
  printf("  num of curves in time plot = %d\n",tp->num_tp_curs);
  for (i=0; i<tp->num_tp_curs; i++) {
    printf("  curve %3d name             = %-35s\n",i,tp->tp_curs_names[i]);
    for (j=0; j<tp->tp_curs[i]->num_vals; j++) {
      if (tp->tp_curs[i]->labels[j] != NULL) {
        printf("    label %d                 = %-35s\n",j,tp->tp_curs[i]->labels[j]);
      }
      else {
        printf("    label %d                 = %-35s [%d]\n",j,tp->tp_curs[i]->eval_string,j);
      }
    }
    printf ("\n");
  }
}
