#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
int comreduce(
  void *inbuf,          
  int count,            
  int op,               
  int com_type,         
  int data_type)        
{
  char *me = "comreduce";
  int i, error;
  int    *outbufi, *inbufi;
  double *outbufd, *inbufd;
  MPI_Op opout;
  com_start = MPI_Wtime_Wrapper();
  if ((com_type != COM_ALL) && (com_type != COM_ONE))
    ctlerror(me,logic_err);
  switch(op) {
   case COM_SUM: opout = MPI_SUM; break;
   case COM_MAX: opout = MPI_MAX; break;
   case COM_MIN: opout = MPI_MIN; break;
   default     : ctlerror(me,logic_err);
  }
  switch (data_type) {
   case COM_DOUBLE:
    outbufd = ALLOT(double,count);
    inbufd  = inbuf;
    if (com_type==COM_ALL) 
     error = MPI_Allreduce_Wrapper(inbuf,outbufd,count,MPI_DOUBLE,opout,MPI_COMM_WORLD);
    else 
     error = MPI_Reduce_Wrapper(inbuf,outbufd,count,MPI_DOUBLE,opout,0,MPI_COMM_WORLD);
    for (i=0;i<count;i++) inbufd[i]=outbufd[i]; 
    FREEMEM(outbufd);
    break;
   case COM_INT:
    outbufi = ALLOT(int,count);
    inbufi  = inbuf;
    if (com_type==COM_ALL) 
     error = MPI_Allreduce_Wrapper(inbuf,outbufi,count,MPI_INT,opout,MPI_COMM_WORLD);
    else 
     error = MPI_Reduce_Wrapper(inbuf,outbufi,count,MPI_INT,opout,0,MPI_COMM_WORLD);
    for (i=0;i<count;i++) inbufi[i]=outbufi[i]; 
    FREEMEM(outbufi);
    break;
   default:
     ctlerror(me,logic_err);
  }
  com_reduce_time += MPI_Wtime_Wrapper() - com_start;
  return(error);
}
