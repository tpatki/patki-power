##############################################################################
#
# sphot Makefile 
#
##############################################################################

PROG     = sphot

#####
# ***Modifications Required***
# Specify linker/loader and flags as well as library directories and libs.
# These can change depending on your preference and platform.
#####
LDR      ?=mpif77
#LDRFLAGS = -qsmp=omp
LDRFLAGS = -fopenmp
LIB_DIRS =-Xlinker -rpath=$(HOME)/local/src/power/rapl/libmsr/lib -L$(HOME)/local/src/power/rapl/libmsr/lib
LIBS     = -lrapl
##### End of required modifications section



##############################################################################
# Rules for Fortran and C object file dependencies
# Note that sphot does not require any C files - references to C files are
# provided as a convenience should you desire to introduce C files for
# profilers, timing tools or something similar.
# Note also that the position of LIBS in the LDR command is critical for
# some platforms. 
##############################################################################


#$(PROG): src/*.f src/*.c includes/*
#	make build;

$(PROG): sources src/*.f includes/*
	cd bin; \
	$(LDR) $(LDRFLAGS) *.o -o $(PROG) $(LIB_DIRS) $(LIBS) ; \
	mv $(PROG) ../.

sources: 
	$(MAKE) -C src -f Makefile.src

clean:
	rm -f $(PROG) bin/*.o

.PHONY: sources
