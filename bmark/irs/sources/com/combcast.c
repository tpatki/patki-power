#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
int combcast(void *inbuf, int len, int type, int sender)
{
   int error;
   MPI_Datatype mtype;
   error=0;
   com_start = MPI_Wtime_Wrapper() ;
   if (type==COM_INT) {
      mtype = MPI_INT;
   } else if (type==COM_DOUBLE) {
      mtype = MPI_DOUBLE;
   } else if (type==COM_CHAR) {
      mtype = MPI_CHAR;
   } 
   error += MPI_Bcast_Wrapper(inbuf,len,mtype,sender,MPI_COMM_WORLD);
   com_brdcst_time += MPI_Wtime_Wrapper () - com_start;
   return(error);
}
