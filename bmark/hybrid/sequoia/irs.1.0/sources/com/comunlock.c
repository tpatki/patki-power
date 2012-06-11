#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
void comunlock( int nbaton ) {
  char *me = "comlock";
  int baton;
  int proc;
  if (num_procs == 1) return;
  if (nbaton < 0) return;
  proc = myid + nbaton;
  if (proc < num_procs) {
     MPI_Send_Wrapper(&baton,1,MPI_INT,proc,myid,MPI_COMM_WORLD);
  }
  combarrier();
}
