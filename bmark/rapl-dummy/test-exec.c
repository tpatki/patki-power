#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
int
main( int argc, char **argv ){
 int return_val=0;

 char *const args[] = 
   {"/bin/ls", "-l", NULL};
 
 MPI_Init(&argc, &argv);

 return_val=execvp("ls", args);

 if(return_val == -1){
    printf("\nCould not execute binary");
 }  

 MPI_Finalize();

 return 0;
}
