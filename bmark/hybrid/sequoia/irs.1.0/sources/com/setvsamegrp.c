#include "irs.h"
#include "irscom.h"
#include "FunctionTimer.h" 
#include "Tagorder.h"
void setvsamegrp(void) {
   char *me = "setvsamegrp";
   char msg[128];
   int i,id;
   int error;
   int count;
   int *myvsame;
   int *allvsame;
   int *rank;
   error = 0;
   vsame_group = ALLOT(MPI_Group,vsame_max_id);
   myvsame = ALLOT(int,vsame_max_id);
   for (id = 0; id < vsame_max_id; id++) {
      myvsame[id] = 0;
      if (vsame_order[id].len > 0) {
         myvsame[id] = 1;
      }
   }
   allvsame = ALLOT(int,vsame_max_id*num_procs);
   error += MPI_Allgather_Wrapper(myvsame,vsame_max_id,MPI_INT,allvsame,vsame_max_id,
                          MPI_INT, MPI_COMM_WORLD);
   rank = ALLOT(int,num_procs);
   for (id = 0; id < vsame_max_id; id++) {
      count = 0;
      for (i=0;i<num_procs;i++) {
         if (allvsame[i*vsame_max_id + id] > 0) {
            rank[count] = i; 
            count++;
         }
      }
      vsame_procs[id] = count;
      if (count > 0) {
         error+=MPI_Group_incl_Wrapper(global_group,count,rank,&vsame_group[id]);
         error+=MPI_Comm_create_Wrapper(MPI_COMM_WORLD,vsame_group[id],
                         &combuf[VSAMECOM].comm[id]);
      }
   }
   if (error > 0) {
      sprintf(msg,"NODE %i: Failure setting vsame groups",myid);
      ctlnotice(me,msg);
   }
   FREEMEM(rank);
   FREEMEM(myvsame);
   FREEMEM(allvsame);
   return;
}
