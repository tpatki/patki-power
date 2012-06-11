
################################################################################
#
# Makefile for irs library sys
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
B = ../$(LIB_DIR)/libsys.a
BI = ../$(LIB_DIR)/libsys_inst.a

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
SRCDIR = ../sources/sys

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libsys:$(B)(HardwareInit.o) $(B)(fprint.o) $(B)(getcpu.o) $(B)(getndx.o)          \
	  $(B)(getndx0.o) $(B)(getruntime.o) $(B)(icasum.o) $(B)(icdot.o)         \
	  $(B)(icnrml2.o) $(B)(icsum.o) $(B)(lists.o) $(B)(sort2.o)               \
	  $(B)(tstsum.o) $(B)(vmax.o) $(B)(vmin.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'sys library current'

# creation deps
#---------------
$(B)(HardwareInit.o):HardwareInit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/HardwareInit.c $(DB)/HardwareInit.c 

$(B)(fprint.o):fprint.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/fprint.c $(DB)/fprint.c 

../../includes/irssys.hh:../../includes/irssys.h
	cp ../../includes/irssys.h ../../includes/irssys.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irssys.hh
	irs_hhinit ../../includes/irssys.hh

$(B)(getcpu.o):../../includes/irssys.hh

$(B)(getcpu.o):getcpu.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getcpu.c $(DB)/getcpu.c 

$(B)(getndx.o):getndx.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getndx.c $(DB)/getndx.c 

$(B)(getndx0.o):getndx0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getndx0.c $(DB)/getndx0.c 

$(B)(getruntime.o):getruntime.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getruntime.c $(DB)/getruntime.c 

$(B)(icasum.o):icasum.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/icasum.c $(DB)/icasum.c 

$(B)(icdot.o):icdot.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/icdot.c $(DB)/icdot.c 

$(B)(icnrml2.o):icnrml2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/icnrml2.c $(DB)/icnrml2.c 

$(B)(icsum.o):icsum.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/icsum.c $(DB)/icsum.c 

$(B)(lists.o):lists.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/lists.c $(DB)/lists.c 

$(B)(sort2.o):sort2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/sort2.c $(DB)/sort2.c 

$(B)(tstsum.o):tstsum.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tstsum.c $(DB)/tstsum.c 

$(B)(vmax.o):vmax.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/vmax.c $(DB)/vmax.c 

$(B)(vmin.o):vmin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/vmin.c $(DB)/vmin.c 

#---------------------
# lint pass one target 
#---------------------
lint:HardwareInit.ln fprint.ln getcpu.ln getndx.ln getndx0.ln getruntime.ln       \
	  icasum.ln icdot.ln icnrml2.ln icsum.ln lists.ln sort2.ln tstsum.ln      \
	  vmax.ln vmin.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
HardwareInit.ln:HardwareInit.c ../../includes/irs.h ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON HardwareInit.c ***' >> $(LO)
	$$irs_lint HardwareInit.c 2>&1 | tee -a $(LO)

fprint.ln:fprint.c ../../includes/irs.h ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON fprint.c ***' >> $(LO)
	$$irs_lint fprint.c 2>&1 | tee -a $(LO)

getcpu.ln:getcpu.c ../../includes/mach.h ../../includes/irs.h                     \
	  ../../includes/irssys.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getcpu.c ***' >> $(LO)
	$$irs_lint getcpu.c 2>&1 | tee -a $(LO)

getndx.ln:getndx.c ../../includes/mach.h ../../includes/irs.h                     \
	  ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getndx.c ***' >> $(LO)
	$$irs_lint getndx.c 2>&1 | tee -a $(LO)

getndx0.ln:getndx0.c ../../includes/mach.h ../../includes/irs.h                   \
	  ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getndx0.c ***' >> $(LO)
	$$irs_lint getndx0.c 2>&1 | tee -a $(LO)

getruntime.ln:getruntime.c ../../includes/irs.h ../../includes/irssys.h           \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getruntime.c ***' >> $(LO)
	$$irs_lint getruntime.c 2>&1 | tee -a $(LO)

icasum.ln:icasum.c ../../includes/irs.h ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON icasum.c ***' >> $(LO)
	$$irs_lint icasum.c 2>&1 | tee -a $(LO)

icdot.ln:icdot.c ../../includes/irs.h ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON icdot.c ***' >> $(LO)
	$$irs_lint icdot.c 2>&1 | tee -a $(LO)

icnrml2.ln:icnrml2.c ../../includes/mach.h ../../includes/irs.h                   \
	  ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON icnrml2.c ***' >> $(LO)
	$$irs_lint icnrml2.c 2>&1 | tee -a $(LO)

icsum.ln:icsum.c ../../includes/irs.h ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON icsum.c ***' >> $(LO)
	$$irs_lint icsum.c 2>&1 | tee -a $(LO)

lists.ln:lists.c ../../includes/irs.h ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON lists.c ***' >> $(LO)
	$$irs_lint lists.c 2>&1 | tee -a $(LO)

sort2.ln:sort2.c ../../includes/irs.h ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON sort2.c ***' >> $(LO)
	$$irs_lint sort2.c 2>&1 | tee -a $(LO)

tstsum.ln:tstsum.c ../../includes/mach.h ../../includes/irs.h                     \
	  ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tstsum.c ***' >> $(LO)
	$$irs_lint tstsum.c 2>&1 | tee -a $(LO)

vmax.ln:vmax.c ../../includes/mach.h ../../includes/irs.h                         \
	  ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON vmax.c ***' >> $(LO)
	$$irs_lint vmax.c 2>&1 | tee -a $(LO)

vmin.ln:vmin.c ../../includes/mach.h ../../includes/irs.h                         \
	  ../../includes/irssys.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON vmin.c ***' >> $(LO)
	$$irs_lint vmin.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/HardwareInit.inst.i $(PREDIR)/fprint.inst.i                  \
	  $(PREDIR)/getcpu.inst.i $(PREDIR)/getndx.inst.i                         \
	  $(PREDIR)/getndx0.inst.i $(PREDIR)/getruntime.inst.i                    \
	  $(PREDIR)/icasum.inst.i $(PREDIR)/icdot.inst.i $(PREDIR)/icnrml2.inst.i \
	  $(PREDIR)/icsum.inst.i $(PREDIR)/lists.inst.i $(PREDIR)/sort2.inst.i    \
	  $(PREDIR)/tstsum.inst.i $(PREDIR)/vmax.inst.i $(PREDIR)/vmin.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/HardwareInit.inst.i:HardwareInit.c ../../includes/irs.h                 \
	  ../../includes/irssys.h
	@rm -f HardwareInit.i
	$$irs_pre HardwareInit.c >> HardwareInit.i
	@mv -f HardwareInit.i $(PREDIR)/HardwareInit.inst.i

$(PREDIR)/fprint.inst.i:fprint.c ../../includes/irs.h ../../includes/irssys.h
	@rm -f fprint.i
	$$irs_pre fprint.c >> fprint.i
	@mv -f fprint.i $(PREDIR)/fprint.inst.i

$(PREDIR)/getcpu.inst.i:getcpu.c ../../includes/mach.h ../../includes/irs.h       \
	  ../../includes/irssys.hh
	@rm -f getcpu.i
	$$irs_pre getcpu.c >> getcpu.i
	@mv -f getcpu.i $(PREDIR)/getcpu.inst.i

$(PREDIR)/getndx.inst.i:getndx.c ../../includes/mach.h ../../includes/irs.h       \
	  ../../includes/irssys.h
	@rm -f getndx.i
	$$irs_pre getndx.c >> getndx.i
	@mv -f getndx.i $(PREDIR)/getndx.inst.i

$(PREDIR)/getndx0.inst.i:getndx0.c ../../includes/mach.h ../../includes/irs.h     \
	  ../../includes/irssys.h
	@rm -f getndx0.i
	$$irs_pre getndx0.c >> getndx0.i
	@mv -f getndx0.i $(PREDIR)/getndx0.inst.i

$(PREDIR)/getruntime.inst.i:getruntime.c ../../includes/irs.h                     \
	  ../../includes/irssys.h ../../includes/FunctionTimer.h
	@rm -f getruntime.i
	$$irs_pre getruntime.c >> getruntime.i
	@mv -f getruntime.i $(PREDIR)/getruntime.inst.i

$(PREDIR)/icasum.inst.i:icasum.c ../../includes/irs.h ../../includes/irssys.h
	@rm -f icasum.i
	$$irs_pre icasum.c >> icasum.i
	@mv -f icasum.i $(PREDIR)/icasum.inst.i

$(PREDIR)/icdot.inst.i:icdot.c ../../includes/irs.h ../../includes/irssys.h
	@rm -f icdot.i
	$$irs_pre icdot.c >> icdot.i
	@mv -f icdot.i $(PREDIR)/icdot.inst.i

$(PREDIR)/icnrml2.inst.i:icnrml2.c ../../includes/mach.h ../../includes/irs.h     \
	  ../../includes/irssys.h
	@rm -f icnrml2.i
	$$irs_pre icnrml2.c >> icnrml2.i
	@mv -f icnrml2.i $(PREDIR)/icnrml2.inst.i

$(PREDIR)/icsum.inst.i:icsum.c ../../includes/irs.h ../../includes/irssys.h
	@rm -f icsum.i
	$$irs_pre icsum.c >> icsum.i
	@mv -f icsum.i $(PREDIR)/icsum.inst.i

$(PREDIR)/lists.inst.i:lists.c ../../includes/irs.h ../../includes/irssys.h
	@rm -f lists.i
	$$irs_pre lists.c >> lists.i
	@mv -f lists.i $(PREDIR)/lists.inst.i

$(PREDIR)/sort2.inst.i:sort2.c ../../includes/irs.h ../../includes/irssys.h
	@rm -f sort2.i
	$$irs_pre sort2.c >> sort2.i
	@mv -f sort2.i $(PREDIR)/sort2.inst.i

$(PREDIR)/tstsum.inst.i:tstsum.c ../../includes/mach.h ../../includes/irs.h       \
	  ../../includes/irssys.h
	@rm -f tstsum.i
	$$irs_pre tstsum.c >> tstsum.i
	@mv -f tstsum.i $(PREDIR)/tstsum.inst.i

$(PREDIR)/vmax.inst.i:vmax.c ../../includes/mach.h ../../includes/irs.h           \
	  ../../includes/irssys.h
	@rm -f vmax.i
	$$irs_pre vmax.c >> vmax.i
	@mv -f vmax.i $(PREDIR)/vmax.inst.i

$(PREDIR)/vmin.inst.i:vmin.c ../../includes/mach.h ../../includes/irs.h           \
	  ../../includes/irssys.h
	@rm -f vmin.i
	$$irs_pre vmin.c >> vmin.i
	@mv -f vmin.i $(PREDIR)/vmin.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libsys_inst

libsys_inst:$(BI)(HardwareInit.inst.o) $(BI)(fprint.inst.o) $(BI)(getcpu.inst.o)  \
	  $(BI)(getndx.inst.o) $(BI)(getndx0.inst.o) $(BI)(getruntime.inst.o)     \
	  $(BI)(icasum.inst.o) $(BI)(icdot.inst.o) $(BI)(icnrml2.inst.o)          \
	  $(BI)(icsum.inst.o) $(BI)(lists.inst.o) $(BI)(sort2.inst.o)             \
	  $(BI)(tstsum.inst.o) $(BI)(vmax.inst.o) $(BI)(vmin.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libsys_inst.a $(B); \
		ln -sf libsys_inst.a $(B)); \
	  fi
	  @echo 'libsys_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(HardwareInit.inst.o):$(INSTDIR)/HardwareInit.inst.i
	$$irs_post $(INSTDIR)/HardwareInit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/HardwareInit.inst.i $(DB)/HardwareInit.c 

$(BI)(fprint.inst.o):$(INSTDIR)/fprint.inst.i
	$$irs_post $(INSTDIR)/fprint.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/fprint.inst.i $(DB)/fprint.c 

$(BI)(getcpu.inst.o):$(INSTDIR)/getcpu.inst.i
	$$irs_post $(INSTDIR)/getcpu.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getcpu.inst.i $(DB)/getcpu.c 

$(BI)(getndx.inst.o):$(INSTDIR)/getndx.inst.i
	$$irs_post $(INSTDIR)/getndx.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getndx.inst.i $(DB)/getndx.c 

$(BI)(getndx0.inst.o):$(INSTDIR)/getndx0.inst.i
	$$irs_post $(INSTDIR)/getndx0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getndx0.inst.i $(DB)/getndx0.c 

$(BI)(getruntime.inst.o):$(INSTDIR)/getruntime.inst.i
	$$irs_post $(INSTDIR)/getruntime.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getruntime.inst.i $(DB)/getruntime.c 

$(BI)(icasum.inst.o):$(INSTDIR)/icasum.inst.i
	$$irs_post $(INSTDIR)/icasum.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/icasum.inst.i $(DB)/icasum.c 

$(BI)(icdot.inst.o):$(INSTDIR)/icdot.inst.i
	$$irs_post $(INSTDIR)/icdot.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/icdot.inst.i $(DB)/icdot.c 

$(BI)(icnrml2.inst.o):$(INSTDIR)/icnrml2.inst.i
	$$irs_post $(INSTDIR)/icnrml2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/icnrml2.inst.i $(DB)/icnrml2.c 

$(BI)(icsum.inst.o):$(INSTDIR)/icsum.inst.i
	$$irs_post $(INSTDIR)/icsum.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/icsum.inst.i $(DB)/icsum.c 

$(BI)(lists.inst.o):$(INSTDIR)/lists.inst.i
	$$irs_post $(INSTDIR)/lists.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/lists.inst.i $(DB)/lists.c 

$(BI)(sort2.inst.o):$(INSTDIR)/sort2.inst.i
	$$irs_post $(INSTDIR)/sort2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/sort2.inst.i $(DB)/sort2.c 

$(BI)(tstsum.inst.o):$(INSTDIR)/tstsum.inst.i
	$$irs_post $(INSTDIR)/tstsum.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tstsum.inst.i $(DB)/tstsum.c 

$(BI)(vmax.inst.o):$(INSTDIR)/vmax.inst.i
	$$irs_post $(INSTDIR)/vmax.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/vmax.inst.i $(DB)/vmax.c 

$(BI)(vmin.inst.o):$(INSTDIR)/vmin.inst.i
	$$irs_post $(INSTDIR)/vmin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/vmin.inst.i $(DB)/vmin.c 

DEP_SRCS = \
	HardwareInit.c fprint.c getcpu.c getndx.c getndx0.c getruntime.c icasum.c  \
	icdot.c icnrml2.c icsum.c lists.c sort2.c tstsum.c vmax.c vmin.c  

depend:
	@cp -f Makefile.sys Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(HardwareInit.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(HardwareInit.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(HardwareInit.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(HardwareInit.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(HardwareInit.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(HardwareInit.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(HardwareInit.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(HardwareInit.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(HardwareInit.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(HardwareInit.o): /usr/include/time.h /usr/include/endian.h
$(B)(HardwareInit.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(HardwareInit.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(HardwareInit.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(HardwareInit.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(HardwareInit.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(HardwareInit.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(HardwareInit.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(HardwareInit.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(HardwareInit.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(HardwareInit.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(HardwareInit.o): /usr/include/ctype.h /usr/include/math.h
$(B)(HardwareInit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(HardwareInit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(HardwareInit.o): /usr/include/malloc.h ../../includes/irssys.h
$(B)(fprint.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(fprint.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(fprint.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(fprint.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(fprint.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(fprint.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(fprint.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(fprint.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(fprint.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(fprint.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(fprint.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(fprint.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(fprint.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(fprint.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(fprint.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(fprint.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(fprint.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(fprint.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(fprint.o): /usr/include/ctype.h /usr/include/math.h
$(B)(fprint.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(fprint.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(fprint.o): /usr/include/malloc.h ../../includes/irssys.h
$(B)(getcpu.o): /usr/include/time.h /usr/include/bits/types.h
$(B)(getcpu.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(getcpu.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(getcpu.o): /usr/include/gnu/stubs-64.h /usr/include/bits/typesizes.h
$(B)(getcpu.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/endian.h
$(B)(getcpu.o): /usr/include/bits/endian.h /usr/include/math.h
$(B)(getcpu.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getcpu.o): /usr/include/bits/mathcalls.h /usr/include/stdio.h
$(B)(getcpu.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getcpu.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getcpu.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getcpu.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(getcpu.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(getcpu.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(getcpu.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(getcpu.o): /usr/include/alloca.h /usr/include/string.h /usr/include/malloc.h
$(B)(getcpu.o): ../../includes/irs.h /usr/include/sys/times.h
$(B)(getcpu.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(getcpu.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(getcpu.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(getcpu.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(getcpu.o): ../../includes/Boundary.h
$(B)(getndx.o): /usr/include/time.h /usr/include/bits/types.h
$(B)(getndx.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(getndx.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(getndx.o): /usr/include/gnu/stubs-64.h /usr/include/bits/typesizes.h
$(B)(getndx.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/endian.h
$(B)(getndx.o): /usr/include/bits/endian.h /usr/include/math.h
$(B)(getndx.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getndx.o): /usr/include/bits/mathcalls.h /usr/include/stdio.h
$(B)(getndx.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getndx.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getndx.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getndx.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(getndx.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(getndx.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(getndx.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(getndx.o): /usr/include/alloca.h /usr/include/string.h /usr/include/malloc.h
$(B)(getndx.o): ../../includes/irs.h /usr/include/sys/times.h
$(B)(getndx.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(getndx.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(getndx.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(getndx.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(getndx.o): ../../includes/Boundary.h ../../includes/irssys.h
$(B)(getndx0.o): /usr/include/time.h /usr/include/bits/types.h
$(B)(getndx0.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(getndx0.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(getndx0.o): /usr/include/gnu/stubs-64.h /usr/include/bits/typesizes.h
$(B)(getndx0.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/endian.h
$(B)(getndx0.o): /usr/include/bits/endian.h /usr/include/math.h
$(B)(getndx0.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getndx0.o): /usr/include/bits/mathcalls.h /usr/include/stdio.h
$(B)(getndx0.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getndx0.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getndx0.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getndx0.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(getndx0.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(getndx0.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(getndx0.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(getndx0.o): /usr/include/alloca.h /usr/include/string.h /usr/include/malloc.h
$(B)(getndx0.o): ../../includes/irs.h /usr/include/sys/times.h
$(B)(getndx0.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(getndx0.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(getndx0.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(getndx0.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(getndx0.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(getndx0.o): ../../includes/irssys.h
$(B)(getruntime.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(getruntime.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(getruntime.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(getruntime.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(getruntime.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(getruntime.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getruntime.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getruntime.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getruntime.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(getruntime.o): /usr/include/time.h /usr/include/endian.h
$(B)(getruntime.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(getruntime.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(getruntime.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(getruntime.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(getruntime.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(getruntime.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(getruntime.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(getruntime.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(getruntime.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(getruntime.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(getruntime.o): /usr/include/ctype.h /usr/include/math.h
$(B)(getruntime.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getruntime.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(getruntime.o): /usr/include/malloc.h ../../includes/irssys.h
$(B)(getruntime.o): ../../includes/FunctionTimer.h
$(B)(icasum.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(icasum.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(icasum.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(icasum.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(icasum.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(icasum.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(icasum.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(icasum.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(icasum.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(icasum.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(icasum.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(icasum.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(icasum.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(icasum.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(icasum.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(icasum.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(icasum.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(icasum.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(icasum.o): /usr/include/ctype.h /usr/include/math.h
$(B)(icasum.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(icasum.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(icasum.o): /usr/include/malloc.h ../../includes/irssys.h
$(B)(icdot.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(icdot.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(icdot.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(icdot.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(icdot.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(icdot.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(icdot.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(icdot.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(icdot.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(icdot.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(icdot.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(icdot.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(icdot.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(icdot.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(icdot.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(icdot.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(icdot.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(icdot.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(icdot.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(icdot.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(icdot.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssys.h
$(B)(icnrml2.o): /usr/include/time.h /usr/include/bits/types.h
$(B)(icnrml2.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(icnrml2.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(icnrml2.o): /usr/include/gnu/stubs-64.h /usr/include/bits/typesizes.h
$(B)(icnrml2.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/endian.h
$(B)(icnrml2.o): /usr/include/bits/endian.h /usr/include/math.h
$(B)(icnrml2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(icnrml2.o): /usr/include/bits/mathcalls.h /usr/include/stdio.h
$(B)(icnrml2.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(icnrml2.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(icnrml2.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(icnrml2.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(icnrml2.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(icnrml2.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(icnrml2.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(icnrml2.o): /usr/include/alloca.h /usr/include/string.h /usr/include/malloc.h
$(B)(icnrml2.o): ../../includes/irs.h /usr/include/sys/times.h
$(B)(icnrml2.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(icnrml2.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(icnrml2.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(icnrml2.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(icnrml2.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(icnrml2.o): ../../includes/irssys.h
$(B)(icsum.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(icsum.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(icsum.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(icsum.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(icsum.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(icsum.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(icsum.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(icsum.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(icsum.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(icsum.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(icsum.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(icsum.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(icsum.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(icsum.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(icsum.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(icsum.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(icsum.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(icsum.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(icsum.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(icsum.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(icsum.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssys.h
$(B)(lists.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(lists.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(lists.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(lists.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(lists.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(lists.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(lists.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(lists.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(lists.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(lists.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(lists.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(lists.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(lists.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(lists.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(lists.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(lists.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(lists.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(lists.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(lists.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(lists.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(lists.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssys.h
$(B)(sort2.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(sort2.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(sort2.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(sort2.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(sort2.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(sort2.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(sort2.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(sort2.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(sort2.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(sort2.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(sort2.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(sort2.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(sort2.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(sort2.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(sort2.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(sort2.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(sort2.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(sort2.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(sort2.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(sort2.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(sort2.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssys.h
$(B)(tstsum.o): /usr/include/time.h /usr/include/bits/types.h
$(B)(tstsum.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(tstsum.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(tstsum.o): /usr/include/gnu/stubs-64.h /usr/include/bits/typesizes.h
$(B)(tstsum.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/endian.h
$(B)(tstsum.o): /usr/include/bits/endian.h /usr/include/math.h
$(B)(tstsum.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(tstsum.o): /usr/include/bits/mathcalls.h /usr/include/stdio.h
$(B)(tstsum.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(tstsum.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(tstsum.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(tstsum.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(tstsum.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(tstsum.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(tstsum.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(tstsum.o): /usr/include/alloca.h /usr/include/string.h /usr/include/malloc.h
$(B)(tstsum.o): ../../includes/irs.h /usr/include/sys/times.h
$(B)(tstsum.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(tstsum.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(tstsum.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(tstsum.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(tstsum.o): ../../includes/Boundary.h ../../includes/irssys.h
$(B)(vmax.o): /usr/include/time.h /usr/include/bits/types.h /usr/include/features.h
$(B)(vmax.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(vmax.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(vmax.o): /usr/include/bits/typesizes.h ../../includes/mach.h
$(B)(vmax.o): /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h
$(B)(vmax.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(vmax.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(vmax.o): /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
$(B)(vmax.o): /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(vmax.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(vmax.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(vmax.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(vmax.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(vmax.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(vmax.o): /usr/include/alloca.h /usr/include/string.h /usr/include/malloc.h
$(B)(vmax.o): ../../includes/irs.h /usr/include/sys/times.h
$(B)(vmax.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(vmax.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(vmax.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(vmax.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(vmax.o): ../../includes/Boundary.h ../../includes/irssys.h
$(B)(vmin.o): /usr/include/time.h /usr/include/bits/types.h /usr/include/features.h
$(B)(vmin.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(vmin.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(vmin.o): /usr/include/bits/typesizes.h ../../includes/mach.h
$(B)(vmin.o): /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h
$(B)(vmin.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(vmin.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(vmin.o): /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
$(B)(vmin.o): /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(vmin.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(vmin.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(vmin.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(vmin.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(vmin.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(vmin.o): /usr/include/alloca.h /usr/include/string.h /usr/include/malloc.h
$(B)(vmin.o): ../../includes/irs.h /usr/include/sys/times.h
$(B)(vmin.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(vmin.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(vmin.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(vmin.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(vmin.o): ../../includes/Boundary.h ../../includes/irssys.h
