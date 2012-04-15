#include "irs.h"
#include "irscom.h"
#include "irsedits.h"
#include "FunctionTimer.h"
#include "AEStackElm.h"
#define ALL_CNTRS       0
#define TOTAL_CNTR      1
int mpi_edit(void)
{
  char *me = "mpi_edit";
  char op[MAXLINE], msg[256];
  int i;
  int flag = TOTAL_CNTR;
  memset(op,'\0',MAXLINE);
  peekc(op);
  if (op[0] == '(') {
    if (geta_leftparen() != 0) { return(-1); }
    memset(op,'\0',MAXLINE);
    peekc(op);
    if (op[0] != ')') {
      geta(op);
      if ( (strcmp(op,"all") == 0) || (strcmp(op,"ALL") == 0) ) {
        flag = ALL_CNTRS;
      }
      else {
        sprintf(msg,"'%s' is unknown argument to %s()",op,me);
        ctlnotice(me,msg);
      }
    }
    if (geta_rightparen() != 0) { return(-1); }
  }
  if (flag == TOTAL_CNTR) {
    ctloutput(me,ft_mpi_routine_names[MPI_Total_cntr],R_INT,ft_mpi_cntrs[MPI_Total_cntr]);
  }
  else {
    for (i=0; i<MPI_num_routines - 1; i++) {
      if (ft_mpi_cntrs[i] != 0) {
        ctloutput(me,ft_mpi_routine_names[i],R_INT,ft_mpi_cntrs[i]);
      }
    }
    ctloutput(me,ft_mpi_routine_names[MPI_Total_cntr],R_INT,ft_mpi_cntrs[MPI_Total_cntr]);
  }
  return(0);
}
