#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
int commpigatherv(
  void *buf,          
  int send_count,     
  int *recv_count,    
  int com_type,       
  int data_type)      
{
  char *me = "commpigatherv";
  int i, error, buflen;
  int    *recv_bufi, *bufi, *recv_disp;
  double *recv_bufd, *bufd;
  if ((com_type != COM_ALL) && (com_type != COM_ONE)) {
    ctlerror(me,logic_err);
  }
  if (ifparallel != TRUE) return(0);
  recv_disp = ALLOT(int, num_procs);
  buflen = 0;
  for (i=0; i<num_procs; i++) {
    recv_disp[i] = buflen;
    buflen       += recv_count[i]; 
  }
  switch (data_type) {
   case COM_DOUBLE:
     recv_bufd = ALLOT(double, buflen);
     bufd      = (double *)buf;
     if (com_type == COM_ALL) { 
       error = MPI_Allgatherv_Wrapper(buf,send_count,MPI_DOUBLE,recv_bufd,recv_count,recv_disp,MPI_DOUBLE,MPI_COMM_WORLD);
       for (i=0; i < buflen; i++) { 
         bufd[i] = recv_bufd[i]; 
       }
     }
     else {
       error = MPI_Gatherv_Wrapper(buf,send_count,MPI_DOUBLE,recv_bufd,recv_count,recv_disp,MPI_DOUBLE,0,MPI_COMM_WORLD);
       if (myid == 0) {
         for (i=0; i < buflen; i++) {
           bufd[i] = recv_bufd[i];
         }
       }
     }
     FREEMEM(recv_bufd); 
     break;
   case COM_INT:
     recv_bufi = ALLOT(int, buflen);
     bufi      = (int *)buf;
     if (com_type == COM_ALL) {
       error = MPI_Allgatherv_Wrapper(buf,send_count,MPI_INT,recv_bufi,recv_count,recv_disp,MPI_INT,MPI_COMM_WORLD);
       for (i=0; i < buflen; i++) { 
         bufi[i] = recv_bufi[i]; 
       }
     }
     else {
       error = MPI_Gatherv_Wrapper(buf,send_count,MPI_INT,recv_bufi,recv_count,recv_disp,MPI_INT,0,MPI_COMM_WORLD);
       if (myid == 0) {
         for (i=0; i < buflen; i++) {
           bufi[i] = recv_bufi[i];
         }
       }
     }
     FREEMEM(recv_bufi);
     break;
   default:
     ctlerror(me,logic_err);
  }
  FREEMEM(recv_disp);
  return(error);
}
