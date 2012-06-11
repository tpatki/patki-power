#include "irs.h"
#include "cgl.h"
#include "irscur.h"
#include "VectorStruct.h"
#include "TimePlot.h"
int getvectp(VectorStruct_t *vecstr)	
{
  char *me = "getvectp";
  int  icur, i, my_itp;
  my_itp = itp;
  if (getvec(vecstr,1,0) != 0) return(1); 
  for ( icur = 0 ; icur < tpdata[my_itp]->num_tp_curs ; icur++ ) {
    if (strcmp(tpdata[my_itp]->tp_curs[icur]->eval_string,vecstr->namelab) == 0) {
      vecstr->palen = tpdata[my_itp]->num_data_pts;
      vecstr->fpa = ALLOT(double,vecstr->palen);
      for (i=0 ; i<vecstr->palen ; i++) { 
	vecstr->fpa[i] = tpdata[my_itp]->tp_curs[icur]->data[0][i]; 
      }
      return(0);	
    }
  }
  return(1); 		
}
