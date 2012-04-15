#include "irs.h"
#include "irsparm.h"
#include "Hash.h"
#include "irsrgst.h"
#include "ProblemArray.h"
int create_temp_pa( void )
{
  char *me = "create_temp_pa";
  char pa_name[128], msg[256];
  double *pa_data;
  int i,iblk;
  geta(pa_name);
  if (rgst_check_for_obj(pa_name) == TRUE) {
    sprintf(msg,"Cannot create pa '%s', object with same name already exists",
            pa_name);
    ctlwarning(me,msg);
    return(1);
  }
  ProblemArray_add(pa_name, NULL, 0, R_DOUBLE, NULL);
  rgst_add_attr(A_OBJECT, pa_name, "TempVar");
  rgst_add_attr(A_OBJECT, pa_name, "DomainVar");
  rgst_add_attr(A_OBJECT, pa_name, "Nodal");
  for (iblk = 0; iblk < nblk; iblk++) {
     pa_data = MALLOT(double,domains[iblk].namix);
     ProblemArray_add(pa_name, (void *)pa_data, domains[iblk].namix, R_DOUBLE,
                      domains[iblk].hash);
     for (i = 0; i < domains[blknum].namix; i++ ) {
        pa_data[i] = 0.0;
     }
  }
  return(0);
}
