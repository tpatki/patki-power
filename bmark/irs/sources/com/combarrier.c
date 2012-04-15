#include "irs.h"
#include "FunctionTimer.h"
#include "irscom.h"
int combarrier( void )
{
   int error;
   com_start = MPI_Wtime_Wrapper(); 
   error = MPI_Barrier_Wrapper(MPI_COMM_WORLD);
   com_barrier_time += MPI_Wtime_Wrapper() - com_start;
   return(error);
}
