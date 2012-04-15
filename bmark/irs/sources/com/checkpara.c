#include "irs.h"
#include "irsctl.h"
#include "FunctionTimer.h"
#include "irscom.h"
int checkpara(int *argc, char **argv, char ***myargv) {
  char *me = "checkpara";
  char **my_argv;
  int flag, i, ierr;
  ierr = MPI_Init_Wrapper(argc,&argv);
  if (ierr == MPI_SUCCESS) { ifmpi = TRUE; }
  else                     { ifmpi = FALSE; }
  my_argv = *myargv;
  for (i=0; i<*argc; i++) {
    my_argv[i] = strsave(argv[i]);
  }
  if (  (ierr < 0) 
      || (sp2_seq_run_flag  == TRUE)
      || (sp2_dont_run_flag == TRUE) ) {
    num_procs=1;
  } 
  else {
     MPI_Comm_size_Wrapper (MPI_COMM_WORLD,&num_procs);
     MPI_Comm_rank_Wrapper (MPI_COMM_WORLD,&myid);
     MPI_Comm_group_Wrapper(MPI_COMM_WORLD,&global_group);
  }
  flag=1;
  if (num_procs==1) { 
     myid = 0;
     flag=0;
  } 
  return(flag); 
}
