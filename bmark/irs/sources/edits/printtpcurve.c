#include "irs.h"
#include "irsedits.h"
#include "TimePlot.h"
void printtpcurve (TimePlotCurve_t *tpc)
{
  char *me = "printtpcurve";
  int i,j;
  double *dblptr;
  if (myid != 0) { return; }
  if (tpc == NULL) { return; }
  printf("\n PRINT OF TIME PLOT CURVE '%s'\n",tpc->name);
  printf("  tpc.name                 = %s\n",tpc->name);
  printf("  tpc.eval_string          = %s\n",tpc->eval_string);
  printf("  tpc.num_vals             = %d\n",tpc->num_vals);
  for (i=0; i<tpc->num_vals; i++) {
    if (tpc->labels[i] != NULL) {
      printf("  tpc.labels[%3d]          = %s\n",i,tpc->labels[i]);
    }
    else {
      printf("  tpc.labels[%3d]          = %s [%d]\n",i,tpc->eval_string,i);
    }
    if (tpc->alloc_data_pts[i] > 0) {
      for (j=0; j<tpc->alloc_data_pts[i]; j++) {
        printf("    %10.5f ",tpc->data[i][j]);
      }
      if ((j+1)%5 == 0) printf("\n");
    }
    printf("\n");
  }
}
