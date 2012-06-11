
################################################################################
#
# Makefile for irs library timers
#

all:
	@ echo " "
	@ echo "Error:"
	@ echo "This Makefile must be called by the driving Makefile."
	@ echo " "

################################################################################

# Must use the bourne shell
#---------------------------
SHELL = /bin/sh

# Harmless suffix rule:
#----------------------
.SUFFIXES : .U

# library relative path name
#----------------------------
B = ../$(LIB_DIR)/libtimers.a
BI = ../$(LIB_DIR)/libtimers_inst.a

# Relative path to the directory of sources for the debugger
#-----------------------------------------------------------
DB  = ../../debug

# Relative path to the instrumented source directory from the source directory
#-----------------------------------------------------------------------------
PREDIR = ../../mccabe/pre
INSTDIR = ../../mccabe/inst

# Relative path to the instrumented source directory from the debug directory
#-----------------------------------------------------------------------------
INSTDIR_D = ../mccabe/inst

# Relative path to the source directory from the debug directory
#----------------------------------------------------------------
SRCDIR = ../sources/timers

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libtimers:$(B)(FunctionTimer_clock.o) $(B)(FunctionTimer_construct.o)             \
	  $(B)(FunctionTimer_error.o) $(B)(FunctionTimer_finalize.o)              \
	  $(B)(FunctionTimer_free.o) $(B)(FunctionTimer_global_vars.o)            \
	  $(B)(FunctionTimer_init.o) $(B)(FunctionTimer_initialize.o)             \
	  $(B)(FunctionTimer_lookup.o) $(B)(FunctionTimer_maxclock.o)             \
	  $(B)(FunctionTimer_mpi_wrappers.o) $(B)(FunctionTimer_out.o)            \
	  $(B)(FunctionTimer_print.o) $(B)(FunctionTimer_setup.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'timers library current'

# creation deps
#---------------
$(B)(FunctionTimer_clock.o):FunctionTimer_clock.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_clock.c $(DB)/FunctionTimer_clock.c 

$(B)(FunctionTimer_construct.o):FunctionTimer_construct.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_construct.c $(DB)/FunctionTimer_construct.c 

$(B)(FunctionTimer_error.o):FunctionTimer_error.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_error.c $(DB)/FunctionTimer_error.c 

$(B)(FunctionTimer_finalize.o):FunctionTimer_finalize.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_finalize.c $(DB)/FunctionTimer_finalize.c 

$(B)(FunctionTimer_free.o):FunctionTimer_free.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_free.c $(DB)/FunctionTimer_free.c 

$(B)(FunctionTimer_global_vars.o):FunctionTimer_global_vars.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_global_vars.c $(DB)/FunctionTimer_global_vars.c 

$(B)(FunctionTimer_init.o):FunctionTimer_init.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_init.c $(DB)/FunctionTimer_init.c 

$(B)(FunctionTimer_initialize.o):FunctionTimer_initialize.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_initialize.c $(DB)/FunctionTimer_initialize.c 

$(B)(FunctionTimer_lookup.o):FunctionTimer_lookup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_lookup.c $(DB)/FunctionTimer_lookup.c 

$(B)(FunctionTimer_maxclock.o):FunctionTimer_maxclock.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_maxclock.c $(DB)/FunctionTimer_maxclock.c 

$(B)(FunctionTimer_mpi_wrappers.o):FunctionTimer_mpi_wrappers.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_mpi_wrappers.c $(DB)/FunctionTimer_mpi_wrappers.c 

$(B)(FunctionTimer_out.o):FunctionTimer_out.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_out.c $(DB)/FunctionTimer_out.c 

$(B)(FunctionTimer_print.o):FunctionTimer_print.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_print.c $(DB)/FunctionTimer_print.c 

$(B)(FunctionTimer_setup.o):FunctionTimer_setup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer_setup.c $(DB)/FunctionTimer_setup.c 

#---------------------
# lint pass one target 
#---------------------
lint:FunctionTimer_clock.ln FunctionTimer_construct.ln FunctionTimer_error.ln     \
	  FunctionTimer_finalize.ln FunctionTimer_free.ln                         \
	  FunctionTimer_global_vars.ln FunctionTimer_init.ln                      \
	  FunctionTimer_initialize.ln FunctionTimer_lookup.ln                     \
	  FunctionTimer_maxclock.ln FunctionTimer_mpi_wrappers.ln                 \
	  FunctionTimer_out.ln FunctionTimer_print.ln FunctionTimer_setup.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
FunctionTimer_clock.ln:FunctionTimer_clock.c ../../includes/Hash.h                \
	  ../../includes/FunctionTimer.h ../../includes/parcrit.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_clock.c ***' >> $(LO)
	$$irs_lint FunctionTimer_clock.c 2>&1 | tee -a $(LO)

FunctionTimer_construct.ln:FunctionTimer_construct.c ../../includes/Hash.h        \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_construct.c ***' >> $(LO)
	$$irs_lint FunctionTimer_construct.c 2>&1 | tee -a $(LO)

FunctionTimer_error.ln:FunctionTimer_error.c ../../includes/Hash.h                \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_error.c ***' >> $(LO)
	$$irs_lint FunctionTimer_error.c 2>&1 | tee -a $(LO)

FunctionTimer_finalize.ln:FunctionTimer_finalize.c ../../includes/Hash.h          \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_finalize.c ***' >> $(LO)
	$$irs_lint FunctionTimer_finalize.c 2>&1 | tee -a $(LO)

FunctionTimer_free.ln:FunctionTimer_free.c ../../includes/Hash.h                  \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_free.c ***' >> $(LO)
	$$irs_lint FunctionTimer_free.c 2>&1 | tee -a $(LO)

FunctionTimer_global_vars.ln:FunctionTimer_global_vars.c ../../includes/Hash.h    \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_global_vars.c ***' >> $(LO)
	$$irs_lint FunctionTimer_global_vars.c 2>&1 | tee -a $(LO)

FunctionTimer_init.ln:FunctionTimer_init.c ../../includes/Hash.h                  \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_init.c ***' >> $(LO)
	$$irs_lint FunctionTimer_init.c 2>&1 | tee -a $(LO)

FunctionTimer_initialize.ln:FunctionTimer_initialize.c ../../includes/Hash.h      \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_initialize.c ***' >> $(LO)
	$$irs_lint FunctionTimer_initialize.c 2>&1 | tee -a $(LO)

FunctionTimer_lookup.ln:FunctionTimer_lookup.c ../../includes/Hash.h              \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_lookup.c ***' >> $(LO)
	$$irs_lint FunctionTimer_lookup.c 2>&1 | tee -a $(LO)

FunctionTimer_maxclock.ln:FunctionTimer_maxclock.c ../../includes/Hash.h          \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_maxclock.c ***' >> $(LO)
	$$irs_lint FunctionTimer_maxclock.c 2>&1 | tee -a $(LO)

FunctionTimer_mpi_wrappers.ln:FunctionTimer_mpi_wrappers.c ../../includes/Hash.h  \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_mpi_wrappers.c ***' >> $(LO)
	$$irs_lint FunctionTimer_mpi_wrappers.c 2>&1 | tee -a $(LO)

FunctionTimer_out.ln:FunctionTimer_out.c ../../includes/Hash.h                    \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_out.c ***' >> $(LO)
	$$irs_lint FunctionTimer_out.c 2>&1 | tee -a $(LO)

FunctionTimer_print.ln:FunctionTimer_print.c ../../includes/Hash.h                \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_print.c ***' >> $(LO)
	$$irs_lint FunctionTimer_print.c 2>&1 | tee -a $(LO)

FunctionTimer_setup.ln:FunctionTimer_setup.c ../../includes/Hash.h                \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer_setup.c ***' >> $(LO)
	$$irs_lint FunctionTimer_setup.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/FunctionTimer_clock.inst.i                                   \
	  $(PREDIR)/FunctionTimer_construct.inst.i                                \
	  $(PREDIR)/FunctionTimer_error.inst.i                                    \
	  $(PREDIR)/FunctionTimer_finalize.inst.i                                 \
	  $(PREDIR)/FunctionTimer_free.inst.i                                     \
	  $(PREDIR)/FunctionTimer_global_vars.inst.i                              \
	  $(PREDIR)/FunctionTimer_init.inst.i                                     \
	  $(PREDIR)/FunctionTimer_initialize.inst.i                               \
	  $(PREDIR)/FunctionTimer_lookup.inst.i                                   \
	  $(PREDIR)/FunctionTimer_maxclock.inst.i                                 \
	  $(PREDIR)/FunctionTimer_mpi_wrappers.inst.i                             \
	  $(PREDIR)/FunctionTimer_out.inst.i $(PREDIR)/FunctionTimer_print.inst.i \
	  $(PREDIR)/FunctionTimer_setup.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/FunctionTimer_clock.inst.i:FunctionTimer_clock.c ../../includes/Hash.h  \
	  ../../includes/FunctionTimer.h ../../includes/parcrit.h
	@rm -f FunctionTimer_clock.i
	$$irs_pre FunctionTimer_clock.c >> FunctionTimer_clock.i
	@mv -f FunctionTimer_clock.i $(PREDIR)/FunctionTimer_clock.inst.i

$(PREDIR)/FunctionTimer_construct.inst.i:FunctionTimer_construct.c                \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_construct.i
	$$irs_pre FunctionTimer_construct.c >> FunctionTimer_construct.i
	@mv -f FunctionTimer_construct.i $(PREDIR)/FunctionTimer_construct.inst.i

$(PREDIR)/FunctionTimer_error.inst.i:FunctionTimer_error.c ../../includes/Hash.h  \
	  ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_error.i
	$$irs_pre FunctionTimer_error.c >> FunctionTimer_error.i
	@mv -f FunctionTimer_error.i $(PREDIR)/FunctionTimer_error.inst.i

$(PREDIR)/FunctionTimer_finalize.inst.i:FunctionTimer_finalize.c                  \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_finalize.i
	$$irs_pre FunctionTimer_finalize.c >> FunctionTimer_finalize.i
	@mv -f FunctionTimer_finalize.i $(PREDIR)/FunctionTimer_finalize.inst.i

$(PREDIR)/FunctionTimer_free.inst.i:FunctionTimer_free.c ../../includes/Hash.h    \
	  ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_free.i
	$$irs_pre FunctionTimer_free.c >> FunctionTimer_free.i
	@mv -f FunctionTimer_free.i $(PREDIR)/FunctionTimer_free.inst.i

$(PREDIR)/FunctionTimer_global_vars.inst.i:FunctionTimer_global_vars.c            \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_global_vars.i
	$$irs_pre FunctionTimer_global_vars.c >> FunctionTimer_global_vars.i
	@mv -f FunctionTimer_global_vars.i $(PREDIR)/FunctionTimer_global_vars.inst.i

$(PREDIR)/FunctionTimer_init.inst.i:FunctionTimer_init.c ../../includes/Hash.h    \
	  ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_init.i
	$$irs_pre FunctionTimer_init.c >> FunctionTimer_init.i
	@mv -f FunctionTimer_init.i $(PREDIR)/FunctionTimer_init.inst.i

$(PREDIR)/FunctionTimer_initialize.inst.i:FunctionTimer_initialize.c              \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_initialize.i
	$$irs_pre FunctionTimer_initialize.c >> FunctionTimer_initialize.i
	@mv -f FunctionTimer_initialize.i $(PREDIR)/FunctionTimer_initialize.inst.i

$(PREDIR)/FunctionTimer_lookup.inst.i:FunctionTimer_lookup.c                      \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_lookup.i
	$$irs_pre FunctionTimer_lookup.c >> FunctionTimer_lookup.i
	@mv -f FunctionTimer_lookup.i $(PREDIR)/FunctionTimer_lookup.inst.i

$(PREDIR)/FunctionTimer_maxclock.inst.i:FunctionTimer_maxclock.c                  \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_maxclock.i
	$$irs_pre FunctionTimer_maxclock.c >> FunctionTimer_maxclock.i
	@mv -f FunctionTimer_maxclock.i $(PREDIR)/FunctionTimer_maxclock.inst.i

$(PREDIR)/FunctionTimer_mpi_wrappers.inst.i:FunctionTimer_mpi_wrappers.c          \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_mpi_wrappers.i
	$$irs_pre FunctionTimer_mpi_wrappers.c >> FunctionTimer_mpi_wrappers.i
	@mv -f FunctionTimer_mpi_wrappers.i $(PREDIR)/FunctionTimer_mpi_wrappers.inst.i

$(PREDIR)/FunctionTimer_out.inst.i:FunctionTimer_out.c ../../includes/Hash.h      \
	  ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_out.i
	$$irs_pre FunctionTimer_out.c >> FunctionTimer_out.i
	@mv -f FunctionTimer_out.i $(PREDIR)/FunctionTimer_out.inst.i

$(PREDIR)/FunctionTimer_print.inst.i:FunctionTimer_print.c ../../includes/Hash.h  \
	  ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_print.i
	$$irs_pre FunctionTimer_print.c >> FunctionTimer_print.i
	@mv -f FunctionTimer_print.i $(PREDIR)/FunctionTimer_print.inst.i

$(PREDIR)/FunctionTimer_setup.inst.i:FunctionTimer_setup.c ../../includes/Hash.h  \
	  ../../includes/FunctionTimer.h
	@rm -f FunctionTimer_setup.i
	$$irs_pre FunctionTimer_setup.c >> FunctionTimer_setup.i
	@mv -f FunctionTimer_setup.i $(PREDIR)/FunctionTimer_setup.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libtimers_inst

libtimers_inst:$(BI)(FunctionTimer_clock.inst.o)                                  \
	  $(BI)(FunctionTimer_construct.inst.o) $(BI)(FunctionTimer_error.inst.o) \
	  $(BI)(FunctionTimer_finalize.inst.o) $(BI)(FunctionTimer_free.inst.o)   \
	  $(BI)(FunctionTimer_global_vars.inst.o)                                 \
	  $(BI)(FunctionTimer_init.inst.o) $(BI)(FunctionTimer_initialize.inst.o) \
	  $(BI)(FunctionTimer_lookup.inst.o) $(BI)(FunctionTimer_maxclock.inst.o) \
	  $(BI)(FunctionTimer_mpi_wrappers.inst.o)                                \
	  $(BI)(FunctionTimer_out.inst.o) $(BI)(FunctionTimer_print.inst.o)       \
	  $(BI)(FunctionTimer_setup.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libtimers_inst.a $(B); \
		ln -sf libtimers_inst.a $(B)); \
	  fi
	  @echo 'libtimers_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(FunctionTimer_clock.inst.o):$(INSTDIR)/FunctionTimer_clock.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_clock.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_clock.inst.i $(DB)/FunctionTimer_clock.c 

$(BI)(FunctionTimer_construct.inst.o):$(INSTDIR)/FunctionTimer_construct.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_construct.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_construct.inst.i $(DB)/FunctionTimer_construct.c 

$(BI)(FunctionTimer_error.inst.o):$(INSTDIR)/FunctionTimer_error.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_error.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_error.inst.i $(DB)/FunctionTimer_error.c 

$(BI)(FunctionTimer_finalize.inst.o):$(INSTDIR)/FunctionTimer_finalize.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_finalize.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_finalize.inst.i $(DB)/FunctionTimer_finalize.c 

$(BI)(FunctionTimer_free.inst.o):$(INSTDIR)/FunctionTimer_free.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_free.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_free.inst.i $(DB)/FunctionTimer_free.c 

$(BI)(FunctionTimer_global_vars.inst.o):$(INSTDIR)/FunctionTimer_global_vars.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_global_vars.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_global_vars.inst.i $(DB)/FunctionTimer_global_vars.c 

$(BI)(FunctionTimer_init.inst.o):$(INSTDIR)/FunctionTimer_init.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_init.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_init.inst.i $(DB)/FunctionTimer_init.c 

$(BI)(FunctionTimer_initialize.inst.o):$(INSTDIR)/FunctionTimer_initialize.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_initialize.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_initialize.inst.i $(DB)/FunctionTimer_initialize.c 

$(BI)(FunctionTimer_lookup.inst.o):$(INSTDIR)/FunctionTimer_lookup.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_lookup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_lookup.inst.i $(DB)/FunctionTimer_lookup.c 

$(BI)(FunctionTimer_maxclock.inst.o):$(INSTDIR)/FunctionTimer_maxclock.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_maxclock.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_maxclock.inst.i $(DB)/FunctionTimer_maxclock.c 

$(BI)(FunctionTimer_mpi_wrappers.inst.o):$(INSTDIR)/FunctionTimer_mpi_wrappers.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_mpi_wrappers.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_mpi_wrappers.inst.i $(DB)/FunctionTimer_mpi_wrappers.c 

$(BI)(FunctionTimer_out.inst.o):$(INSTDIR)/FunctionTimer_out.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_out.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_out.inst.i $(DB)/FunctionTimer_out.c 

$(BI)(FunctionTimer_print.inst.o):$(INSTDIR)/FunctionTimer_print.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_print.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_print.inst.i $(DB)/FunctionTimer_print.c 

$(BI)(FunctionTimer_setup.inst.o):$(INSTDIR)/FunctionTimer_setup.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer_setup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer_setup.inst.i $(DB)/FunctionTimer_setup.c 

DEP_SRCS = \
	FunctionTimer_clock.c FunctionTimer_construct.c FunctionTimer_error.c  \
	FunctionTimer_finalize.c FunctionTimer_free.c FunctionTimer_global_vars.c  \
	FunctionTimer_init.c FunctionTimer_initialize.c FunctionTimer_lookup.c  \
	FunctionTimer_maxclock.c FunctionTimer_mpi_wrappers.c FunctionTimer_out.c  \
	FunctionTimer_print.c FunctionTimer_setup.c  

depend:
	@cp -f Makefile.timers Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(FunctionTimer_clock.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_clock.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FunctionTimer_clock.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/types.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FunctionTimer_clock.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FunctionTimer_clock.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FunctionTimer_clock.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FunctionTimer_clock.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_clock.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FunctionTimer_clock.o): /usr/include/unistd.h /usr/include/bits/posix_opt.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/confname.h /usr/include/getopt.h
$(B)(FunctionTimer_clock.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/mathdef.h
$(B)(FunctionTimer_clock.o): /usr/include/bits/mathcalls.h ../../includes/Hash.h
$(B)(FunctionTimer_clock.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_clock.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_clock.o): ../../includes/parcrit.h
$(B)(FunctionTimer_construct.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_construct.o): /usr/include/sys/cdefs.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/wordsize.h
$(B)(FunctionTimer_construct.o): /usr/include/gnu/stubs.h
$(B)(FunctionTimer_construct.o): /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/types.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FunctionTimer_construct.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/sys_errlist.h
$(B)(FunctionTimer_construct.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(FunctionTimer_construct.o): /usr/include/time.h /usr/include/endian.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/endian.h
$(B)(FunctionTimer_construct.o): /usr/include/sys/select.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/select.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/sigset.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/time.h
$(B)(FunctionTimer_construct.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_construct.o): /usr/include/bits/pthreadtypes.h
$(B)(FunctionTimer_construct.o): /usr/include/alloca.h ../../includes/Hash.h
$(B)(FunctionTimer_construct.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_construct.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_error.o): /usr/include/stdlib.h /usr/include/features.h
$(B)(FunctionTimer_error.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FunctionTimer_error.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_error.o): /usr/include/sys/types.h /usr/include/bits/types.h
$(B)(FunctionTimer_error.o): /usr/include/bits/typesizes.h /usr/include/time.h
$(B)(FunctionTimer_error.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FunctionTimer_error.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FunctionTimer_error.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_error.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_error.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FunctionTimer_error.o): /usr/include/stdio.h /usr/include/libio.h
$(B)(FunctionTimer_error.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FunctionTimer_error.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FunctionTimer_error.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_error.o): /usr/include/bits/sys_errlist.h ../../includes/Hash.h
$(B)(FunctionTimer_error.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_error.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_finalize.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_finalize.o): /usr/include/sys/cdefs.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/wordsize.h
$(B)(FunctionTimer_finalize.o): /usr/include/gnu/stubs.h
$(B)(FunctionTimer_finalize.o): /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/types.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FunctionTimer_finalize.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/sys_errlist.h
$(B)(FunctionTimer_finalize.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(FunctionTimer_finalize.o): /usr/include/time.h /usr/include/endian.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/endian.h
$(B)(FunctionTimer_finalize.o): /usr/include/sys/select.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/select.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_finalize.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/pthreadtypes.h
$(B)(FunctionTimer_finalize.o): /usr/include/alloca.h /usr/include/unistd.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/posix_opt.h
$(B)(FunctionTimer_finalize.o): /usr/include/bits/confname.h /usr/include/getopt.h
$(B)(FunctionTimer_finalize.o): ../../includes/Hash.h
$(B)(FunctionTimer_finalize.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_finalize.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_free.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_free.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FunctionTimer_free.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_free.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(FunctionTimer_free.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(FunctionTimer_free.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(FunctionTimer_free.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_free.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FunctionTimer_free.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FunctionTimer_free.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FunctionTimer_free.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FunctionTimer_free.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_free.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_free.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FunctionTimer_free.o): ../../includes/Hash.h ../../includes/FunctionTimer.h
$(B)(FunctionTimer_free.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_global_vars.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_global_vars.o): /usr/include/sys/cdefs.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/wordsize.h
$(B)(FunctionTimer_global_vars.o): /usr/include/gnu/stubs.h
$(B)(FunctionTimer_global_vars.o): /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/types.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/typesizes.h
$(B)(FunctionTimer_global_vars.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(FunctionTimer_global_vars.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(FunctionTimer_global_vars.o): /usr/include/gconv.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/sys_errlist.h
$(B)(FunctionTimer_global_vars.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(FunctionTimer_global_vars.o): /usr/include/time.h /usr/include/endian.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/endian.h
$(B)(FunctionTimer_global_vars.o): /usr/include/sys/select.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/select.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/sigset.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/time.h
$(B)(FunctionTimer_global_vars.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_global_vars.o): /usr/include/bits/pthreadtypes.h
$(B)(FunctionTimer_global_vars.o): /usr/include/alloca.h ../../includes/Hash.h
$(B)(FunctionTimer_global_vars.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_global_vars.o): /usr/include/sys/times.h
$(B)(FunctionTimer_global_vars.o): ../../includes/irsdefs.h
$(B)(FunctionTimer_init.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_init.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FunctionTimer_init.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_init.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(FunctionTimer_init.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(FunctionTimer_init.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(FunctionTimer_init.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_init.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FunctionTimer_init.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FunctionTimer_init.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FunctionTimer_init.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FunctionTimer_init.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_init.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_init.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FunctionTimer_init.o): /usr/include/string.h ../../includes/Hash.h
$(B)(FunctionTimer_init.o): ../../includes/FunctionTimer.h /usr/include/sys/times.h
$(B)(FunctionTimer_init.o): ../../includes/irsdefs.h
$(B)(FunctionTimer_initialize.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_initialize.o): /usr/include/sys/cdefs.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/wordsize.h
$(B)(FunctionTimer_initialize.o): /usr/include/gnu/stubs.h
$(B)(FunctionTimer_initialize.o): /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/types.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/typesizes.h
$(B)(FunctionTimer_initialize.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(FunctionTimer_initialize.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(FunctionTimer_initialize.o): /usr/include/gconv.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/sys_errlist.h
$(B)(FunctionTimer_initialize.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(FunctionTimer_initialize.o): /usr/include/time.h /usr/include/endian.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/endian.h
$(B)(FunctionTimer_initialize.o): /usr/include/sys/select.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/select.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/sigset.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/time.h
$(B)(FunctionTimer_initialize.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_initialize.o): /usr/include/bits/pthreadtypes.h
$(B)(FunctionTimer_initialize.o): /usr/include/alloca.h /usr/include/string.h
$(B)(FunctionTimer_initialize.o): ../../includes/Hash.h
$(B)(FunctionTimer_initialize.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_initialize.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_lookup.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_lookup.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FunctionTimer_lookup.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_lookup.o): /usr/include/bits/types.h
$(B)(FunctionTimer_lookup.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FunctionTimer_lookup.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FunctionTimer_lookup.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FunctionTimer_lookup.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_lookup.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FunctionTimer_lookup.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FunctionTimer_lookup.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FunctionTimer_lookup.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FunctionTimer_lookup.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_lookup.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_lookup.o): /usr/include/bits/pthreadtypes.h
$(B)(FunctionTimer_lookup.o): /usr/include/alloca.h ../../includes/Hash.h
$(B)(FunctionTimer_lookup.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_lookup.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_maxclock.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_maxclock.o): /usr/include/sys/cdefs.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/wordsize.h
$(B)(FunctionTimer_maxclock.o): /usr/include/gnu/stubs.h
$(B)(FunctionTimer_maxclock.o): /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/types.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FunctionTimer_maxclock.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/sys_errlist.h
$(B)(FunctionTimer_maxclock.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(FunctionTimer_maxclock.o): /usr/include/time.h /usr/include/endian.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/endian.h
$(B)(FunctionTimer_maxclock.o): /usr/include/sys/select.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/select.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_maxclock.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/pthreadtypes.h
$(B)(FunctionTimer_maxclock.o): /usr/include/alloca.h /usr/include/math.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/huge_val.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/mathdef.h
$(B)(FunctionTimer_maxclock.o): /usr/include/bits/mathcalls.h ../../includes/Hash.h
$(B)(FunctionTimer_maxclock.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_maxclock.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/sys/cdefs.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/wordsize.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/gnu/stubs.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/types.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/typesizes.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/gconv.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/sys_errlist.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/time.h /usr/include/endian.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/endian.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/sys/select.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/select.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/sigset.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/time.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/pthreadtypes.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/alloca.h ../../includes/irs.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/sys/times.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/irsdefs.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/pint.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/SpeciesFraction.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/Source.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/BoundaryCondition.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/ctype.h /usr/include/math.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/huge_val.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/mathdef.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/mathcalls.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/string.h /usr/include/malloc.h
$(B)(FunctionTimer_mpi_wrappers.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/unistd.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/posix_opt.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/bits/confname.h
$(B)(FunctionTimer_mpi_wrappers.o): /usr/include/getopt.h
$(B)(FunctionTimer_out.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_out.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FunctionTimer_out.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_out.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(FunctionTimer_out.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(FunctionTimer_out.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(FunctionTimer_out.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_out.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FunctionTimer_out.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FunctionTimer_out.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FunctionTimer_out.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FunctionTimer_out.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_out.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_out.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FunctionTimer_out.o): /usr/include/string.h ../../includes/Hash.h
$(B)(FunctionTimer_out.o): ../../includes/FunctionTimer.h /usr/include/sys/times.h
$(B)(FunctionTimer_out.o): ../../includes/irsdefs.h
$(B)(FunctionTimer_print.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_print.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FunctionTimer_print.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_print.o): /usr/include/bits/types.h
$(B)(FunctionTimer_print.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FunctionTimer_print.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FunctionTimer_print.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FunctionTimer_print.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_print.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FunctionTimer_print.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FunctionTimer_print.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FunctionTimer_print.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FunctionTimer_print.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_print.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_print.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FunctionTimer_print.o): /usr/include/string.h ../../includes/Hash.h
$(B)(FunctionTimer_print.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_print.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FunctionTimer_setup.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FunctionTimer_setup.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FunctionTimer_setup.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FunctionTimer_setup.o): /usr/include/bits/types.h
$(B)(FunctionTimer_setup.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FunctionTimer_setup.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FunctionTimer_setup.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FunctionTimer_setup.o): /usr/include/bits/stdio_lim.h
$(B)(FunctionTimer_setup.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FunctionTimer_setup.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FunctionTimer_setup.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FunctionTimer_setup.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FunctionTimer_setup.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FunctionTimer_setup.o): /usr/include/sys/sysmacros.h
$(B)(FunctionTimer_setup.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FunctionTimer_setup.o): /usr/include/string.h ../../includes/Hash.h
$(B)(FunctionTimer_setup.o): ../../includes/FunctionTimer.h
$(B)(FunctionTimer_setup.o): /usr/include/sys/times.h ../../includes/irsdefs.h
