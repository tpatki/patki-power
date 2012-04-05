###################################
# Build and install SWEEP3D	  #
# By Scott Pakin <pakin@lanl.gov> #
###################################

AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = sweep
sweep_SOURCES = decomp.f flux_err.f inner_auto.f octant.f source.f \
		driver.f initialize.f inner.f read_input.f sweep.f \
		timers.c msg_stuff.h
bin_SCRIPTS = makeinput
nodist_sweep_SOURCES = msg_stuff.f
BUILT_SOURCES = msg_stuff.f
EXTRA_DIST = makeinput msg_stuff.cpp README.html $(sweep_IO_DATA)
sweep_IOdir = $(pkgdatadir)/examples
sweep_IO_DATA = output.150.mpi_2x3 output.150.single output.50.pvm_2x3 \
	        output.150.pvm_2x3 output.50.mpi_2x3 output.50.single \
	        input.50 input.150
MOSTLYCLEANFILES = msg_stuff.f

msg_stuff.f: msg_stuff.cpp msg_stuff.h
	$(CPP) $(CPPFLAGS) -P msg_stuff.cpp > msg_stuff.f
