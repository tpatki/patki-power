
#include <stdio.h>
#include <stdlib.h>
#include "irs.h"
#include "Hash.h"
#include "FunctionTimer.h"

#ifdef TERRY_TRACE

#include <values.h>

#endif

/*
 ***********************************************************************
 * End of Terry Jones Section of code
 ***********************************************************************
 */

#include <unistd.h>


char * ft_mpi_routine_names[MPI_num_routines] = {
   "MPI_Abort",      "MPI_Allgather",   "MPI_Allgatherv",
   "MPI_Allreduce",
   "MPI_Barrier",    "MPI_Bcast",       "MPI_Comm_create", 
   "MPI_Comm_group", "MPI_Comm_rank",   "MPI_Comm_size",  
   "MPI_Finalize",   "MPI_Gather",      "MPI_Gatherv", 
   "MPI_Group_incl", "MPI_Init",
   "MPI_Irecv",      "MPI_Isend",       "MPI_Recv",       
   "MPI_Reduce",     "MPI_Send",        "MPI_Waitall",     
   "MPI_Waitany",    "MPI_Wait",        "MPI_Wtick",      
   "MPI_Wtime",      "Total MPI Calls",
};
int ft_mpi_cntrs[MPI_num_routines] = {
   0, 0, 0, 
   0,
   0, 0, 0,
   0, 0, 0,
   0, 0, 0, 
   0, 0,
   0, 0, 0,
   0, 0, 0,
   0, 0, 0,
   0, 0 
};
#ifndef COMMPI
MPI_Request  MPI_REQUEST_NULL = 0;
MPI_Datatype MPI_DOUBLE       = 11;
MPI_Datatype MPI_CHAR         = 1;
MPI_Datatype MPI_INT          = 6;
MPI_Comm     MPI_COMM_WORLD   = 91;
MPI_Op       MPI_SUM          = 102 ;
MPI_Op       MPI_MIN          = 101 ;
MPI_Op       MPI_MAX          = 100 ;
#endif
static int reset_cycle = 0;
void mpi_reset_cntrs(int cycle)
{
  int i;
  for (i=0; i<MPI_num_routines; i++) { 
    ft_mpi_cntrs[i] = 0; 
  }
  reset_cycle = cycle;
}
int     MPI_Abort_Wrapper(MPI_Comm comm, int errorcode)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Abort_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Abort_cntr]++;
  ierr = MPI_Abort(comm, errorcode);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Allgather_Wrapper(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Allgather_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Allgather_cntr]++;
  ierr = MPI_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Allgatherv_Wrapper(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int *recvcount, int *recvdisp, MPI_Datatype recvtype, MPI_Comm comm)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Allgatherv_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Allgatherv_cntr]++;
  ierr = MPI_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvdisp, recvtype, comm);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}

int 	MPI_Allreduce_Wrapper(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)
{
#ifdef COMMPI

  char *me = ft_mpi_routine_names[MPI_Allreduce_cntr];

  int ierr;

  FT_INITIALIZE(me, ft_global_ht)

  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Allreduce_cntr]++;

#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Allreduce_cntr++;
  if (datatype == MPI_INT) { TRCHKGT(BEFORE_MPI_Allreduce, cycle, TERRY_MPI_Allreduce_cntr, (int)op, count, count*sizeof(int)); }
  else                     { TRCHKGT(BEFORE_MPI_Allreduce, cycle, TERRY_MPI_Allreduce_cntr, (int)op, count, count*sizeof(double)); }
  }
#endif

  ierr = MPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);

#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  if (datatype == MPI_INT) { TRCHKGT(AFTER_MPI_Allreduce, cycle, TERRY_MPI_Allreduce_cntr, (int)op, count, count*sizeof(int)); }
  else                     { TRCHKGT(AFTER_MPI_Allreduce, cycle, TERRY_MPI_Allreduce_cntr, (int)op, count, count*sizeof(double)); }
  }
#endif

  FT_FINALIZE(me, ft_global_ht, 1)

  return(ierr);

#else
  return(0);
#endif
}


int 	MPI_Barrier_Wrapper(MPI_Comm comm)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Barrier_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Barrier_cntr]++;

#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Barrier_cntr++;
  TRCHKGT(BEFORE_MPI_Barrier, cycle, TERRY_MPI_Barrier_cntr, 0, 0, 0);
  }
#endif

  ierr = MPI_Barrier(comm);

#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TRCHKGT(AFTER_MPI_Barrier, cycle, TERRY_MPI_Barrier_cntr, 0, 0, 0); 
  }
#endif

  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Bcast_Wrapper(void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm )
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Bcast_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Bcast_cntr]++;
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Bcast_cntr++;
  if      (datatype == MPI_INT)    { TRCHKGT(BEFORE_MPI_Bcast, cycle, TERRY_MPI_Bcast_cntr, root, count, count*sizeof(int));    }
  else if (datatype == MPI_DOUBLE) { TRCHKGT(BEFORE_MPI_Bcast, cycle, TERRY_MPI_Bcast_cntr, root, count, count*sizeof(double)); }
  else                             { TRCHKGT(BEFORE_MPI_Bcast, cycle, TERRY_MPI_Bcast_cntr, root, count, count*sizeof(char));   }
  }
#endif
  ierr = MPI_Bcast(buffer, count, datatype, root, comm);
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  if      (datatype == MPI_INT)    { TRCHKGT(AFTER_MPI_Bcast, cycle, TERRY_MPI_Bcast_cntr, root, count,  count*sizeof(int));     }
  else if (datatype == MPI_DOUBLE) { TRCHKGT(AFTER_MPI_Bcast, cycle, TERRY_MPI_Bcast_cntr, root, count,  count*sizeof(double));  }
  else                             { TRCHKGT(AFTER_MPI_Bcast, cycle, TERRY_MPI_Bcast_cntr, root, count,  count*sizeof(char));    }
  }
#endif
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Comm_create_Wrapper(MPI_Comm comm, MPI_Group group, MPI_Comm *newcomm)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Comm_create_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Comm_create_cntr]++;
  ierr = MPI_Comm_create(comm, group, newcomm);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Comm_group_Wrapper(MPI_Comm comm, MPI_Group *group)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Comm_group_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Comm_group_cntr]++;
  ierr = MPI_Comm_group(comm, group);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Comm_rank_Wrapper(MPI_Comm comm, int *rank)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Comm_rank_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Comm_rank_cntr]++;
  ierr = MPI_Comm_rank(comm, rank);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Comm_size_Wrapper(MPI_Comm comm, int *size)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Comm_size_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Comm_size_cntr]++;
  ierr = MPI_Comm_size(comm, size);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Finalize_Wrapper(void)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Finalize_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Finalize_cntr]++;
  ierr = MPI_Finalize();
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Gather_Wrapper(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Gather_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Gather_cntr]++;                                                                
  ierr = MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Gatherv_Wrapper(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int *recvcount, int *recvdisp, MPI_Datatype recvtype, int root, MPI_Comm comm)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Gatherv_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Gatherv_cntr]++;                                                                
  ierr = MPI_Gatherv(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvdisp, recvtype, root, comm);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Group_incl_Wrapper(MPI_Group group, int n, int *ranks, MPI_Group *newgroup)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Group_incl_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Group_incl_cntr]++;
  ierr = MPI_Group_incl(group, n, ranks, newgroup);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int	MPI_Init_Wrapper(int *argc, char ***argv) 
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Init_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Init_cntr]++;
  ierr = MPI_Init(argc,argv);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(NO_MPI);
#endif
}
int 	MPI_Irecv_Wrapper(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Irecv_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Irecv_cntr]++;
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Irecv_cntr++;
  if      (datatype == MPI_INT)    { TRCHKGT(BEFORE_MPI_Irecv, cycle, TERRY_MPI_Irecv_cntr, source, count, count*sizeof(int)); 	}
  else if (datatype == MPI_DOUBLE) { TRCHKGT(BEFORE_MPI_Irecv, cycle, TERRY_MPI_Irecv_cntr, source, count, count*sizeof(double)); 	}
  else                             { TRCHKGT(BEFORE_MPI_Irecv, cycle, TERRY_MPI_Irecv_cntr, source, count, count*sizeof(char)); 	}
  }
#endif
  ierr = MPI_Irecv(buf, count, datatype, source, tag, comm, request);
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  if      (datatype == MPI_INT)    { TRCHKGT(AFTER_MPI_Irecv, cycle, TERRY_MPI_Irecv_cntr, source, count, count*sizeof(int));	} 
  else if (datatype == MPI_DOUBLE) { TRCHKGT(AFTER_MPI_Irecv, cycle, TERRY_MPI_Irecv_cntr, source, count, count*sizeof(double)); 	}
  else                             { TRCHKGT(AFTER_MPI_Irecv, cycle, TERRY_MPI_Irecv_cntr, source, count, count*sizeof(char)); 	}
  }
#endif
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Isend_Wrapper(void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Isend_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Isend_cntr]++;
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Isend_cntr++;
  if      (datatype == MPI_INT)    { TRCHKGT(BEFORE_MPI_Isend, cycle, TERRY_MPI_Isend_cntr, dest, count, count*sizeof(int));	} 
  else if (datatype == MPI_DOUBLE) { TRCHKGT(BEFORE_MPI_Isend, cycle, TERRY_MPI_Isend_cntr, dest, count, count*sizeof(double)); 	}
  else                             { TRCHKGT(BEFORE_MPI_Isend, cycle, TERRY_MPI_Isend_cntr, dest, count, count*sizeof(char)); 	}
  }
#endif
  ierr = MPI_Isend(buf, count, datatype, dest, tag, comm, request);
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  if      (datatype == MPI_INT)    { TRCHKGT(AFTER_MPI_Isend, cycle, TERRY_MPI_Isend_cntr, dest, count, count*sizeof(int)); 	}
  else if (datatype == MPI_DOUBLE) { TRCHKGT(AFTER_MPI_Isend, cycle, TERRY_MPI_Isend_cntr, dest, count, count*sizeof(double)); 	}
  else                             { TRCHKGT(AFTER_MPI_Isend, cycle, TERRY_MPI_Isend_cntr, dest, count, count*sizeof(char)); 	}
  }
#endif
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Recv_Wrapper(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Recv_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Recv_cntr]++;
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Recv_cntr++;
  if      (datatype == MPI_INT)    { TRCHKGT(BEFORE_MPI_Recv, cycle, TERRY_MPI_Recv_cntr, source, count, count*sizeof(int));	}
  else if (datatype == MPI_DOUBLE) { TRCHKGT(BEFORE_MPI_Recv, cycle, TERRY_MPI_Recv_cntr, source, count, count*sizeof(double));	}
  else                             { TRCHKGT(BEFORE_MPI_Recv, cycle, TERRY_MPI_Recv_cntr, source, count, count*sizeof(char));	}
  }
#endif
  ierr = MPI_Recv(buf, count, datatype, source, tag, comm, status);
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  if      (datatype == MPI_INT)    { TRCHKGT(AFTER_MPI_Recv, cycle, TERRY_MPI_Recv_cntr, source, count, count*sizeof(int)); 	}
  else if (datatype == MPI_DOUBLE) { TRCHKGT(AFTER_MPI_Recv, cycle, TERRY_MPI_Recv_cntr, source, count, count*sizeof(double)); 	}
  else                             { TRCHKGT(AFTER_MPI_Recv, cycle, TERRY_MPI_Recv_cntr, source, count, count*sizeof(char));	}
  }
#endif
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Reduce_Wrapper(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Reduce_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Reduce_cntr]++;
  ierr = MPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm);
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Send_Wrapper(void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Send_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Send_cntr]++;
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Send_cntr++;
  if      (datatype == MPI_INT)    { TRCHKGT(BEFORE_MPI_Send, cycle, TERRY_MPI_Send_cntr, dest, count, count*sizeof(int)); 	}
  else if (datatype == MPI_DOUBLE) { TRCHKGT(BEFORE_MPI_Send, cycle, TERRY_MPI_Send_cntr, dest, count, count*sizeof(double)); 	}
  else                             { TRCHKGT(BEFORE_MPI_Send, cycle, TERRY_MPI_Send_cntr, dest, count, count*sizeof(char)); 	}
  }
#endif
  ierr = MPI_Send(buf, count, datatype, dest, tag, comm);
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  if      (datatype == MPI_INT)    { TRCHKGT(AFTER_MPI_Send, cycle, TERRY_MPI_Send_cntr, dest, count, count*sizeof(int)); 	}
  else if (datatype == MPI_DOUBLE) { TRCHKGT(AFTER_MPI_Send, cycle, TERRY_MPI_Send_cntr, dest, count, count*sizeof(double)); 	}
  else                             { TRCHKGT(AFTER_MPI_Send, cycle, TERRY_MPI_Send_cntr, dest, count, count*sizeof(char)); 	}
  }
#endif
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Waitall_Wrapper(int count, MPI_Request *array_of_requests, MPI_Status *array_of_status)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Waitall_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Waitall_cntr]++;
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Waitall_cntr++;
  TRCHKGT(BEFORE_MPI_Waitall, cycle, TERRY_MPI_Waitall_cntr, 0, 0, 0); 
  }
#endif
  ierr = MPI_Waitall(count, array_of_requests, array_of_status);
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TRCHKGT(AFTER_MPI_Waitall, cycle, TERRY_MPI_Waitall_cntr, 0, 0, 0); 
  }
#endif
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Waitany_Wrapper(int count, MPI_Request *array_of_requests, int *index, MPI_Status *status)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Waitany_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Waitany_cntr]++;
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Waitany_cntr++;
  TRCHKGT(BEFORE_MPI_Waitany, cycle, TERRY_MPI_Waitany_cntr, 0, 0, 0); 
  }
#endif
  ierr = MPI_Waitany(count, array_of_requests, index, status);
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TRCHKGT(AFTER_MPI_Waitany, cycle, TERRY_MPI_Waitany_cntr, 0, 0, 0); 
  }
#endif
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
int 	MPI_Wait_Wrapper(MPI_Request *request, MPI_Status *status)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Wait_cntr];
  int ierr;
  FT_INITIALIZE(me, ft_global_ht)
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Wait_cntr]++;
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TERRY_MPI_Wait_cntr++;
  TRCHKGT(BEFORE_MPI_Wait, cycle, TERRY_MPI_Wait_cntr, 0, 0, 0); 
  }
#endif
  ierr = MPI_Wait(request, status);
#ifdef TERRY_TRACE
  if (terry_trace_flag == TRUE) {
  TRCHKGT(AFTER_MPI_Wait, cycle, TERRY_MPI_Wait_cntr, 0, 0, 0); 
  }
#endif
  FT_FINALIZE(me, ft_global_ht, 1)
  return(ierr);
#else
  return(0);
#endif
}
double 	MPI_Wtick_Wrapper(void)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Wtick_cntr];
  double derr;
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Wtick_cntr]++;
  derr = MPI_Wtick();
  return(derr);
#else
  return(0);
#endif
}
double 	MPI_Wtime_Wrapper(void)
{
#ifdef COMMPI
  char *me = ft_mpi_routine_names[MPI_Wtime_cntr];
  double derr;
  ft_mpi_cntrs[MPI_Total_cntr]++;
  ft_mpi_cntrs[MPI_Wtime_cntr]++;
  derr = MPI_Wtime();
  return(derr);
#else
  return(0);
#endif
}
