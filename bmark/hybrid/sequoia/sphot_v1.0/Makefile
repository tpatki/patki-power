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
#LDR      = newmpxlf
LDR      = /usr/local/tools/compilers/ibm/mpxlf-9.1.0.8
#LDRFLAGS = -qsmp=omp
LDRFLAGS = -qsmp=omp
LIB_DIRS = 
LIBS     = 
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

$(PROG): src/*.f includes/*
	make build;

build: 
	make sources;
	cd bin; \
	$(LDR)  $(LDRFLAGS) *.o -o $(PROG) $(LIB_DIRS) $(LIBS) ; \
	mv $(PROG) ../.

sources: 
	cd src; make -f Makefile.src all

clean:
	rm -f $(PROG); rm -f bin/*.o

