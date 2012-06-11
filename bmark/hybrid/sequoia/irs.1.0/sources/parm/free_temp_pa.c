#include "irs.h"
#include "irsparm.h"
#include "Hash.h"
#include "irsrgst.h"
#include "ProblemArray.h"
int  free_temp_pa( void )
{
  char    *me = "free_temp_pa";
  char     pa_name[128], msg[256];
  int      iblk;
  double  *pa_data;
  ProblemArray_t *prb;
  geta(pa_name);
  prb = ProblemArray_find(pa_name, NULL);
  if (prb == NULL) {
    sprintf(msg,"Object %s does not exist in the registry", pa_name);
    ctlwarning(me,msg);
    return(1);
  }
  if (RGST_QUERY_OBJECT_ATTR(pa_name,"TempVar")  == FALSE) {
    sprintf(msg,"Variable %s is not a temp array, it cannot freed", pa_name);
    ctlwarning(me,msg);
    return(1);
  }
  ProblemArray_free(pa_name);
  return(0) ;
}
