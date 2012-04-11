
rapl-dummy:
	mpicc -o rapl-dummy rapl-dummy.c -Xlinker -rpath=$(HOME)/local/src/power/rapl/libmsr/lib -L$(HOME)/local/src/power/rapl/libmsr/lib -lrapl
clean:
	rm -f rapl-dummy *.o

