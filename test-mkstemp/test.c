#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main( int argc, char **argv ){

  int rank;
  int fd=-1;
  char filename[25];
  FILE *f;
   
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   
        sprintf(filename, "%d__XXXXXX", rank);
        fd=mkstemp(filename);
        fprintf(stderr, "filename=%s\n", filename);
        if(fd==-1){
                fprintf(stderr, "Error opening %s for reading.\n", filename);
		exit(0);
        }
	else {
		printf("Success.\n");
	        close(fd);
		f = fopen(filename, "w");
		if(f!=NULL)
			fprintf(f, "Rank %d is writing to its file", rank);
		fclose (f);
	}

 MPI_Finalize();
 return 0;
}






