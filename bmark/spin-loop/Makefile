
mpi-spin:
	mpicc -o mpi-spin mpi-spin.c -Xlinker -rpath=$(HOME)/local/src/power/rapl/libmsr/lib -L$(HOME)/local/src/power/rapl/libmsr/lib -lrapl

clean:
	rm -f mpi-spin *.o

