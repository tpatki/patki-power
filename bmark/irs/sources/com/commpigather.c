#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
int commpigather(
  void *buf,          
  int count,          
  int com_type,       
  int data_type)      
{
  char *me = "commpigather";
  int i, error;
  int    *recv_bufi = NULL, *bufi = NULL;
  double *recv_bufd = NULL, *bufd = NULL;
  if ((com_type != COM_ALL) && (com_type != COM_ONE)) {
    ctlerror(me,logic_err);
  }
  if (ifparallel != TRUE) return(0);
  switch (data_type) {
   case COM_DOUBLE:
     if (com_type == COM_ALL) { 
       recv_bufd = ALLOT(double, count * num_procs);
       bufd      = (double *)buf;
       error = MPI_Allgather_Wrapper(buf,count,MPI_DOUBLE,recv_bufd,count,MPI_DOUBLE,MPI_COMM_WORLD);
       for (i=0; i < (count * num_procs); i++) { 
         bufd[i] = recv_bufd[i]; 
       }
       FREEMEM(recv_bufd); 
     }
     else {
       if (myid ==0) {
         recv_bufd = ALLOT(double, count * num_procs);
         bufd      = (double *)buf;
       }
       error = MPI_Gather_Wrapper(buf,count,MPI_DOUBLE,recv_bufd,count,MPI_DOUBLE,0,MPI_COMM_WORLD);
       if (myid == 0) {
         for (i=0; i < (count * num_procs); i++) {
           bufd[i] = recv_bufd[i];
         }
         FREEMEM(recv_bufd); 
       }
     }
     break;
   case COM_INT:
     if (com_type == COM_ALL) {
       recv_bufi = ALLOT(int, count * num_procs);
       bufi      = (int *)buf;
       error = MPI_Allgather_Wrapper(buf,count,MPI_INT,recv_bufi,count,MPI_INT,MPI_COMM_WORLD);
       for (i=0; i < (count * num_procs); i++) { 
         bufi[i] = recv_bufi[i]; 
       }
       FREEMEM(recv_bufi);
     }
     else {
       if (myid == 0) {
         recv_bufi = ALLOT(int, count * num_procs);
         bufi      = (int *)buf;
       }
       error = MPI_Gather_Wrapper(buf,count,MPI_INT,recv_bufi,count,MPI_INT,0,MPI_COMM_WORLD);
       if (myid == 0) {
         for (i=0; i < (count * num_procs); i++) {
           bufi[i] = recv_bufi[i];
         }
         FREEMEM(recv_bufi);
       }
     }
     break;
   default:
     ctlerror(me,logic_err);
  }
  return(error);
}
