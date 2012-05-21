
rapl-dummy:
	mpicc -o rapl-dummy rapl-dummy.c -Xlinker -rpath=$(HOME)/local/src/power/rapl/libmsr_blr/lib -L$(HOME)/local/src/power/rapl/libmsr_blr/lib -lrapl
clean:
	rm -f rapl-dummy *.o

