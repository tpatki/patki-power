all:	../lib/librapl.so

objects=../msr_core.o ../msr_rapl.o ../msr_turbo.o ../blr_util.o ../msr_opt.o ../cpuid.o rapl.o

../lib:
	mkdir -p ../lib

rapl.c: rapl.w
	./wrap.py -f -g -c /home/tpatki/tapasya/test-mvapich/bin/mpicc -o rapl.c rapl.w

rapl.o: rapl.c
	/home/tpatki/tapasya/test-mvapich/bin/mpicc ${COMPILER_SPECIFIC_FLAGS} -DPIC -fPIC -I.. -DARCH_SANDY_BRIDGE -DARCH_062D -c rapl.c -o rapl.o

../lib/librapl.so: ../lib $(objects) wrap.py
	/home/tpatki/tapasya/test-mvapich/bin/mpicc ${COMPILER_SPECIFIC_FLAGS} $(objects) -shared -Wl,-soname,librapl.so -o ../lib/librapl.so  
clean:
	rm -f *.o 


