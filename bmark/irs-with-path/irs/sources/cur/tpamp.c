#include <unistd.h>		
#include "irs.h"
#include "irscom.h"
#include "irscur.h"
#include "cgl.h"
#include "FunctionTimer.h"
#include "TimePlot.h"
int tpamp( void )
{
  char *me = "tpamp", msg[256];
  int i, j, k, icur;
  double *times;
  TimePlot_t *my_tpd  = NULL;
  TimePlotCurve_t *my_tpc = NULL;
  if (myid != 0) { return(0); }
  strcpy(msg,outpath);
  strcat(msg,pbnm);
  strcat(msg,".ult");
  fpamp = fopen(msg,"wt");
  for (i=0 ; i<ntp ; i++) {
    my_tpd = tpdata[i];
    if (strcmp("time $",my_tpd->tp_curs[0]->eval_string) != 0) {
      ctlerror(me,logic_err);
    }
    if (my_tpd->num_data_pts > 0) {
      times = my_tpd->tp_curs[0]->data[0];
    }
    for (icur=1; icur < my_tpd->num_tp_curs; icur++) {
      my_tpc = my_tpd->tp_curs[icur];
      for (j=0; j<my_tpc->num_vals; j++) {
        if (my_tpc->labels[j] == NULL) {
          if (my_tpc->num_vals == 1) {
            PRINT(fpamp,"# %s vs. time\n",my_tpc->eval_string);
          }
          else {
            PRINT(fpamp,"# %s [%d] vs. time\n",my_tpc->eval_string,j);
          }
        }
        else {
          PRINT(fpamp,"# %s vs. time\n",my_tpc->labels[j]);
        }
        for (k=0; k<my_tpd->num_data_pts; k++) {
          PRINT(fpamp," %.14e  %.14e\n",times[k],my_tpc->data[j][k]);
        }
        PRINT(fpamp,"end\n") ;
      }
    }
  }
  fclose(fpamp);
  return(0);
}
