
rapl-dummy:
	mpicc -o rapl-dummy rapl-dummy.c -Xlinker -rpath=$(HOME)/local/src/merlot-power-local-setup/rapl/libmsr_blr/lib -L$(HOME)/local/src/merlot-power-local-setup/rapl/libmsr_blr/lib -lrapl
test-exec:
	mpicc -o test-exec test-exec.c -Xlinker -rpath=$(HOME)/local/src/merlot-power-local-setup/rapl/libmsr_blr/lib -L$(HOME)/local/src/merlot-power-local-setup/rapl/libmsr_blr/lib -lrapl
clean:
	rm -f rapl-dummy test-exec *.o

