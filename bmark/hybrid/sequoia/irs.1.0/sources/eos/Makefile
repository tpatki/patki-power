
################################################################################
#
# Makefile for irs library eos
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
B = ../$(LIB_DIR)/libeos.a
BI = ../$(LIB_DIR)/libeos_inst.a

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
SRCDIR = ../sources/eos

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libeos:$(B)(DensityEnergyMin.o) $(B)(EosDriver.o) $(B)(calc_dtdr_form.o)          \
	  $(B)(eosfm5.o) $(B)(etaminchk.o) $(B)(getemat.o) $(B)(getematnomix.o)   \
	  $(B)(geteos.o) $(B)(geteosnomix.o) $(B)(geteosx.o) $(B)(pminchk.o)      \
	  $(B)(setvoid.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'eos library current'

# creation deps
#---------------
$(B)(DensityEnergyMin.o):DensityEnergyMin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/DensityEnergyMin.c $(DB)/DensityEnergyMin.c 

$(B)(EosDriver.o):EosDriver.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/EosDriver.c $(DB)/EosDriver.c 

$(B)(calc_dtdr_form.o):calc_dtdr_form.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/calc_dtdr_form.c $(DB)/calc_dtdr_form.c 

$(B)(eosfm5.o):eosfm5.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/eosfm5.c $(DB)/eosfm5.c 

$(B)(etaminchk.o):etaminchk.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/etaminchk.c $(DB)/etaminchk.c 

$(B)(getemat.o):getemat.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getemat.c $(DB)/getemat.c 

$(B)(getematnomix.o):getematnomix.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getematnomix.c $(DB)/getematnomix.c 

../../includes/irseos.hh:../../includes/irseos.h
	cp ../../includes/irseos.h ../../includes/irseos.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irseos.hh
	irs_hhinit ../../includes/irseos.hh

$(B)(geteos.o):../../includes/irseos.hh

$(B)(geteos.o):geteos.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geteos.c $(DB)/geteos.c 

$(B)(geteosnomix.o):geteosnomix.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geteosnomix.c $(DB)/geteosnomix.c 

$(B)(geteosx.o):geteosx.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geteosx.c $(DB)/geteosx.c 

$(B)(pminchk.o):pminchk.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/pminchk.c $(DB)/pminchk.c 

$(B)(setvoid.o):setvoid.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setvoid.c $(DB)/setvoid.c 

#---------------------
# lint pass one target 
#---------------------
lint:DensityEnergyMin.ln EosDriver.ln calc_dtdr_form.ln eosfm5.ln etaminchk.ln    \
	  getemat.ln getematnomix.ln geteos.ln geteosnomix.ln geteosx.ln          \
	  pminchk.ln setvoid.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
DensityEnergyMin.ln:DensityEnergyMin.c ../../includes/irs.h                       \
	  ../../includes/irseos.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON DensityEnergyMin.c ***' >> $(LO)
	$$irs_lint DensityEnergyMin.c 2>&1 | tee -a $(LO)

EosDriver.ln:EosDriver.c ../../includes/irs.h ../../includes/irsreg.h             \
	  ../../includes/irseos.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON EosDriver.c ***' >> $(LO)
	$$irs_lint EosDriver.c 2>&1 | tee -a $(LO)

calc_dtdr_form.ln:calc_dtdr_form.c ../../includes/irs.h ../../includes/irseos.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON calc_dtdr_form.c ***' >> $(LO)
	$$irs_lint calc_dtdr_form.c 2>&1 | tee -a $(LO)

eosfm5.ln:eosfm5.c ../../includes/irs.h ../../includes/irseos.h                   \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON eosfm5.c ***' >> $(LO)
	$$irs_lint eosfm5.c 2>&1 | tee -a $(LO)

etaminchk.ln:etaminchk.c ../../includes/irs.h ../../includes/irseos.h             \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON etaminchk.c ***' >> $(LO)
	$$irs_lint etaminchk.c 2>&1 | tee -a $(LO)

getemat.ln:getemat.c ../../includes/irs.h ../../includes/irsreg.h                 \
	  ../../includes/irseos.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getemat.c ***' >> $(LO)
	$$irs_lint getemat.c 2>&1 | tee -a $(LO)

getematnomix.ln:getematnomix.c ../../includes/irs.h ../../includes/irseos.h       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getematnomix.c ***' >> $(LO)
	$$irs_lint getematnomix.c 2>&1 | tee -a $(LO)

geteos.ln:geteos.c ../../includes/irs.h ../../includes/irsreg.h                   \
	  ../../includes/irssrc.h ../../includes/irseos.hh                        \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/Source.h ../../includes/SpeciesFraction.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geteos.c ***' >> $(LO)
	$$irs_lint geteos.c 2>&1 | tee -a $(LO)

geteosnomix.ln:geteosnomix.c ../../includes/irs.h ../../includes/irseos.h         \
	  ../../includes/FunctionTimer.h ../../includes/SpeciesFraction.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geteosnomix.c ***' >> $(LO)
	$$irs_lint geteosnomix.c 2>&1 | tee -a $(LO)

geteosx.ln:geteosx.c ../../includes/irs.h ../../includes/irseos.h                 \
	  ../../includes/FunctionTimer.h ../../includes/SpeciesFraction.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geteosx.c ***' >> $(LO)
	$$irs_lint geteosx.c 2>&1 | tee -a $(LO)

pminchk.ln:pminchk.c ../../includes/irs.h ../../includes/irseos.h                 \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON pminchk.c ***' >> $(LO)
	$$irs_lint pminchk.c 2>&1 | tee -a $(LO)

setvoid.ln:setvoid.c ../../includes/irs.h ../../includes/irseos.h                 \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setvoid.c ***' >> $(LO)
	$$irs_lint setvoid.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/DensityEnergyMin.inst.i $(PREDIR)/EosDriver.inst.i           \
	  $(PREDIR)/calc_dtdr_form.inst.i $(PREDIR)/eosfm5.inst.i                 \
	  $(PREDIR)/etaminchk.inst.i $(PREDIR)/getemat.inst.i                     \
	  $(PREDIR)/getematnomix.inst.i $(PREDIR)/geteos.inst.i                   \
	  $(PREDIR)/geteosnomix.inst.i $(PREDIR)/geteosx.inst.i                   \
	  $(PREDIR)/pminchk.inst.i $(PREDIR)/setvoid.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/DensityEnergyMin.inst.i:DensityEnergyMin.c ../../includes/irs.h         \
	  ../../includes/irseos.h ../../includes/FunctionTimer.h
	@rm -f DensityEnergyMin.i
	$$irs_pre DensityEnergyMin.c >> DensityEnergyMin.i
	@mv -f DensityEnergyMin.i $(PREDIR)/DensityEnergyMin.inst.i

$(PREDIR)/EosDriver.inst.i:EosDriver.c ../../includes/irs.h                       \
	  ../../includes/irsreg.h ../../includes/irseos.h                         \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/pardo.h
	@rm -f EosDriver.i
	$$irs_pre EosDriver.c >> EosDriver.i
	@mv -f EosDriver.i $(PREDIR)/EosDriver.inst.i

$(PREDIR)/calc_dtdr_form.inst.i:calc_dtdr_form.c ../../includes/irs.h             \
	  ../../includes/irseos.h
	@rm -f calc_dtdr_form.i
	$$irs_pre calc_dtdr_form.c >> calc_dtdr_form.i
	@mv -f calc_dtdr_form.i $(PREDIR)/calc_dtdr_form.inst.i

$(PREDIR)/eosfm5.inst.i:eosfm5.c ../../includes/irs.h ../../includes/irseos.h     \
	  ../../includes/FunctionTimer.h
	@rm -f eosfm5.i
	$$irs_pre eosfm5.c >> eosfm5.i
	@mv -f eosfm5.i $(PREDIR)/eosfm5.inst.i

$(PREDIR)/etaminchk.inst.i:etaminchk.c ../../includes/irs.h                       \
	  ../../includes/irseos.h ../../includes/FunctionTimer.h
	@rm -f etaminchk.i
	$$irs_pre etaminchk.c >> etaminchk.i
	@mv -f etaminchk.i $(PREDIR)/etaminchk.inst.i

$(PREDIR)/getemat.inst.i:getemat.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irseos.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f getemat.i
	$$irs_pre getemat.c >> getemat.i
	@mv -f getemat.i $(PREDIR)/getemat.inst.i

$(PREDIR)/getematnomix.inst.i:getematnomix.c ../../includes/irs.h                 \
	  ../../includes/irseos.h ../../includes/FunctionTimer.h
	@rm -f getematnomix.i
	$$irs_pre getematnomix.c >> getematnomix.i
	@mv -f getematnomix.i $(PREDIR)/getematnomix.inst.i

$(PREDIR)/geteos.inst.i:geteos.c ../../includes/irs.h ../../includes/irsreg.h     \
	  ../../includes/irssrc.h ../../includes/irseos.hh                        \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/Source.h ../../includes/SpeciesFraction.h
	@rm -f geteos.i
	$$irs_pre geteos.c >> geteos.i
	@mv -f geteos.i $(PREDIR)/geteos.inst.i

$(PREDIR)/geteosnomix.inst.i:geteosnomix.c ../../includes/irs.h                   \
	  ../../includes/irseos.h ../../includes/FunctionTimer.h                  \
	  ../../includes/SpeciesFraction.h
	@rm -f geteosnomix.i
	$$irs_pre geteosnomix.c >> geteosnomix.i
	@mv -f geteosnomix.i $(PREDIR)/geteosnomix.inst.i

$(PREDIR)/geteosx.inst.i:geteosx.c ../../includes/irs.h ../../includes/irseos.h   \
	  ../../includes/FunctionTimer.h ../../includes/SpeciesFraction.h
	@rm -f geteosx.i
	$$irs_pre geteosx.c >> geteosx.i
	@mv -f geteosx.i $(PREDIR)/geteosx.inst.i

$(PREDIR)/pminchk.inst.i:pminchk.c ../../includes/irs.h ../../includes/irseos.h   \
	  ../../includes/FunctionTimer.h
	@rm -f pminchk.i
	$$irs_pre pminchk.c >> pminchk.i
	@mv -f pminchk.i $(PREDIR)/pminchk.inst.i

$(PREDIR)/setvoid.inst.i:setvoid.c ../../includes/irs.h ../../includes/irseos.h   \
	  ../../includes/FunctionTimer.h
	@rm -f setvoid.i
	$$irs_pre setvoid.c >> setvoid.i
	@mv -f setvoid.i $(PREDIR)/setvoid.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libeos_inst

libeos_inst:$(BI)(DensityEnergyMin.inst.o) $(BI)(EosDriver.inst.o)                \
	  $(BI)(calc_dtdr_form.inst.o) $(BI)(eosfm5.inst.o)                       \
	  $(BI)(etaminchk.inst.o) $(BI)(getemat.inst.o)                           \
	  $(BI)(getematnomix.inst.o) $(BI)(geteos.inst.o)                         \
	  $(BI)(geteosnomix.inst.o) $(BI)(geteosx.inst.o) $(BI)(pminchk.inst.o)   \
	  $(BI)(setvoid.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libeos_inst.a $(B); \
		ln -sf libeos_inst.a $(B)); \
	  fi
	  @echo 'libeos_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(DensityEnergyMin.inst.o):$(INSTDIR)/DensityEnergyMin.inst.i
	$$irs_post $(INSTDIR)/DensityEnergyMin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/DensityEnergyMin.inst.i $(DB)/DensityEnergyMin.c 

$(BI)(EosDriver.inst.o):$(INSTDIR)/EosDriver.inst.i
	$$irs_post $(INSTDIR)/EosDriver.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/EosDriver.inst.i $(DB)/EosDriver.c 

$(BI)(calc_dtdr_form.inst.o):$(INSTDIR)/calc_dtdr_form.inst.i
	$$irs_post $(INSTDIR)/calc_dtdr_form.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/calc_dtdr_form.inst.i $(DB)/calc_dtdr_form.c 

$(BI)(eosfm5.inst.o):$(INSTDIR)/eosfm5.inst.i
	$$irs_post $(INSTDIR)/eosfm5.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/eosfm5.inst.i $(DB)/eosfm5.c 

$(BI)(etaminchk.inst.o):$(INSTDIR)/etaminchk.inst.i
	$$irs_post $(INSTDIR)/etaminchk.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/etaminchk.inst.i $(DB)/etaminchk.c 

$(BI)(getemat.inst.o):$(INSTDIR)/getemat.inst.i
	$$irs_post $(INSTDIR)/getemat.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getemat.inst.i $(DB)/getemat.c 

$(BI)(getematnomix.inst.o):$(INSTDIR)/getematnomix.inst.i
	$$irs_post $(INSTDIR)/getematnomix.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getematnomix.inst.i $(DB)/getematnomix.c 

$(BI)(geteos.inst.o):$(INSTDIR)/geteos.inst.i
	$$irs_post $(INSTDIR)/geteos.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geteos.inst.i $(DB)/geteos.c 

$(BI)(geteosnomix.inst.o):$(INSTDIR)/geteosnomix.inst.i
	$$irs_post $(INSTDIR)/geteosnomix.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geteosnomix.inst.i $(DB)/geteosnomix.c 

$(BI)(geteosx.inst.o):$(INSTDIR)/geteosx.inst.i
	$$irs_post $(INSTDIR)/geteosx.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geteosx.inst.i $(DB)/geteosx.c 

$(BI)(pminchk.inst.o):$(INSTDIR)/pminchk.inst.i
	$$irs_post $(INSTDIR)/pminchk.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/pminchk.inst.i $(DB)/pminchk.c 

$(BI)(setvoid.inst.o):$(INSTDIR)/setvoid.inst.i
	$$irs_post $(INSTDIR)/setvoid.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setvoid.inst.i $(DB)/setvoid.c 

DEP_SRCS = \
	DensityEnergyMin.c EosDriver.c calc_dtdr_form.c eosfm5.c etaminchk.c getemat.c  \
	getematnomix.c geteos.c geteosnomix.c geteosx.c pminchk.c setvoid.c  

depend:
	@cp -f Makefile.eos Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(DensityEnergyMin.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(DensityEnergyMin.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(DensityEnergyMin.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(DensityEnergyMin.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(DensityEnergyMin.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(DensityEnergyMin.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(DensityEnergyMin.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(DensityEnergyMin.o): /usr/include/bits/stdio_lim.h
$(B)(DensityEnergyMin.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(DensityEnergyMin.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(DensityEnergyMin.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(DensityEnergyMin.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(DensityEnergyMin.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(DensityEnergyMin.o): /usr/include/sys/sysmacros.h
$(B)(DensityEnergyMin.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(DensityEnergyMin.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(DensityEnergyMin.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(DensityEnergyMin.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(DensityEnergyMin.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(DensityEnergyMin.o): ../../includes/Source.h
$(B)(DensityEnergyMin.o): ../../includes/BoundaryCondition.h
$(B)(DensityEnergyMin.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(DensityEnergyMin.o): /usr/include/ctype.h /usr/include/math.h
$(B)(DensityEnergyMin.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(DensityEnergyMin.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(DensityEnergyMin.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(DensityEnergyMin.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(DensityEnergyMin.o): ../../includes/FunctionTimer.h
$(B)(EosDriver.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(EosDriver.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(EosDriver.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(EosDriver.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(EosDriver.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(EosDriver.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(EosDriver.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(EosDriver.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(EosDriver.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(EosDriver.o): /usr/include/time.h /usr/include/endian.h
$(B)(EosDriver.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(EosDriver.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(EosDriver.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(EosDriver.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(EosDriver.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(EosDriver.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(EosDriver.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(EosDriver.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(EosDriver.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(EosDriver.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(EosDriver.o): /usr/include/ctype.h /usr/include/math.h
$(B)(EosDriver.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(EosDriver.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(EosDriver.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(EosDriver.o): ../../includes/Region.h ../../includes/irseos.h
$(B)(EosDriver.o): ../../includes/Thermo.h ../../includes/irstdiff.h
$(B)(EosDriver.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(EosDriver.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(EosDriver.o): ../../includes/FunctionTimer.h ../../includes/pardo.h
$(B)(calc_dtdr_form.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(calc_dtdr_form.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(calc_dtdr_form.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(calc_dtdr_form.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(calc_dtdr_form.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(calc_dtdr_form.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(calc_dtdr_form.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(calc_dtdr_form.o): /usr/include/bits/stdio_lim.h
$(B)(calc_dtdr_form.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(calc_dtdr_form.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(calc_dtdr_form.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(calc_dtdr_form.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(calc_dtdr_form.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(calc_dtdr_form.o): /usr/include/sys/sysmacros.h
$(B)(calc_dtdr_form.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(calc_dtdr_form.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(calc_dtdr_form.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(calc_dtdr_form.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(calc_dtdr_form.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(calc_dtdr_form.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(calc_dtdr_form.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(calc_dtdr_form.o): /usr/include/ctype.h /usr/include/math.h
$(B)(calc_dtdr_form.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(calc_dtdr_form.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(calc_dtdr_form.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(calc_dtdr_form.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(eosfm5.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(eosfm5.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(eosfm5.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(eosfm5.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(eosfm5.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(eosfm5.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(eosfm5.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(eosfm5.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(eosfm5.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(eosfm5.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(eosfm5.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(eosfm5.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(eosfm5.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(eosfm5.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(eosfm5.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(eosfm5.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(eosfm5.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(eosfm5.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(eosfm5.o): /usr/include/ctype.h /usr/include/math.h
$(B)(eosfm5.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(eosfm5.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(eosfm5.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(eosfm5.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(eosfm5.o): ../../includes/FunctionTimer.h
$(B)(etaminchk.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(etaminchk.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(etaminchk.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(etaminchk.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(etaminchk.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(etaminchk.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(etaminchk.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(etaminchk.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(etaminchk.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(etaminchk.o): /usr/include/time.h /usr/include/endian.h
$(B)(etaminchk.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(etaminchk.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(etaminchk.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(etaminchk.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(etaminchk.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(etaminchk.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(etaminchk.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(etaminchk.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(etaminchk.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(etaminchk.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(etaminchk.o): /usr/include/ctype.h /usr/include/math.h
$(B)(etaminchk.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(etaminchk.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(etaminchk.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(etaminchk.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(etaminchk.o): ../../includes/FunctionTimer.h
$(B)(getemat.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(getemat.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(getemat.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(getemat.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(getemat.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getemat.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getemat.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getemat.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(getemat.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(getemat.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(getemat.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(getemat.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(getemat.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(getemat.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(getemat.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(getemat.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(getemat.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(getemat.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(getemat.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(getemat.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getemat.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(getemat.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(getemat.o): ../../includes/Region.h ../../includes/irseos.h
$(B)(getemat.o): ../../includes/Thermo.h ../../includes/irstdiff.h
$(B)(getemat.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(getemat.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(getemat.o): ../../includes/FunctionTimer.h
$(B)(getematnomix.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(getematnomix.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(getematnomix.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(getematnomix.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(getematnomix.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(getematnomix.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getematnomix.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getematnomix.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getematnomix.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(getematnomix.o): /usr/include/time.h /usr/include/endian.h
$(B)(getematnomix.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(getematnomix.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(getematnomix.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(getematnomix.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(getematnomix.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(getematnomix.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(getematnomix.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(getematnomix.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(getematnomix.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(getematnomix.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(getematnomix.o): /usr/include/ctype.h /usr/include/math.h
$(B)(getematnomix.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getematnomix.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(getematnomix.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(getematnomix.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(getematnomix.o): ../../includes/FunctionTimer.h
$(B)(geteos.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(geteos.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(geteos.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(geteos.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(geteos.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(geteos.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(geteos.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(geteos.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(geteos.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(geteos.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(geteos.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(geteos.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(geteos.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(geteos.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(geteos.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(geteos.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(geteos.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(geteos.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(geteos.o): /usr/include/ctype.h /usr/include/math.h
$(B)(geteos.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(geteos.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(geteos.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(geteos.o): ../../includes/Region.h ../../includes/irssrc.h
$(B)(geteos.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(geteos.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(geteos.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(geteos.o): ../../includes/DiffusionData.h ../../includes/FunctionTimer.h
$(B)(geteosnomix.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(geteosnomix.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(geteosnomix.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(geteosnomix.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(geteosnomix.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(geteosnomix.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(geteosnomix.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(geteosnomix.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(geteosnomix.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(geteosnomix.o): /usr/include/time.h /usr/include/endian.h
$(B)(geteosnomix.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(geteosnomix.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(geteosnomix.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(geteosnomix.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(geteosnomix.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(geteosnomix.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(geteosnomix.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(geteosnomix.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(geteosnomix.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(geteosnomix.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(geteosnomix.o): /usr/include/ctype.h /usr/include/math.h
$(B)(geteosnomix.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(geteosnomix.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(geteosnomix.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(geteosnomix.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(geteosnomix.o): ../../includes/FunctionTimer.h
$(B)(geteosx.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(geteosx.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(geteosx.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(geteosx.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(geteosx.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(geteosx.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(geteosx.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(geteosx.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(geteosx.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(geteosx.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(geteosx.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(geteosx.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(geteosx.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(geteosx.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(geteosx.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(geteosx.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(geteosx.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(geteosx.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(geteosx.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(geteosx.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(geteosx.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(geteosx.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(geteosx.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(geteosx.o): ../../includes/FunctionTimer.h
$(B)(pminchk.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(pminchk.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(pminchk.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(pminchk.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(pminchk.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(pminchk.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(pminchk.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(pminchk.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(pminchk.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(pminchk.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(pminchk.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(pminchk.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(pminchk.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(pminchk.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(pminchk.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(pminchk.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(pminchk.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(pminchk.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(pminchk.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(pminchk.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(pminchk.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(pminchk.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(pminchk.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(pminchk.o): ../../includes/FunctionTimer.h
$(B)(setvoid.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(setvoid.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(setvoid.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(setvoid.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(setvoid.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setvoid.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setvoid.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setvoid.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(setvoid.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(setvoid.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(setvoid.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(setvoid.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(setvoid.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(setvoid.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(setvoid.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(setvoid.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(setvoid.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(setvoid.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(setvoid.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(setvoid.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setvoid.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setvoid.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(setvoid.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(setvoid.o): ../../includes/FunctionTimer.h
