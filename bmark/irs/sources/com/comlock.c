#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
void comlock( int nbaton ) {
  char *me = "comlock";
  int baton;
  int proc;
  MPI_Status status;
  if (num_procs == 1) return;
  if (nbaton < 0) return;
  if (myid >= nbaton) {
     proc = myid - nbaton;
     MPI_Recv_Wrapper(&baton,1,MPI_INT,proc,proc, MPI_COMM_WORLD,&status);
  } 
}
