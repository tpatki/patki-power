
################################################################################
#
# Makefile for irs library reg
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
B = ../$(LIB_DIR)/libreg.a
BI = ../$(LIB_DIR)/libreg_inst.a

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
SRCDIR = ../sources/reg

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libreg:$(B)(OpacTypesIn.o) $(B)(eos_init.o) $(B)(eosin.o) $(B)(eosin0.o)          \
	  $(B)(maxmin.o) $(B)(opacin.o) $(B)(regcnst.o) $(B)(region.o)            \
	  $(B)(regndx.o) $(B)(species.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'reg library current'

# creation deps
#---------------
$(B)(OpacTypesIn.o):OpacTypesIn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/OpacTypesIn.c $(DB)/OpacTypesIn.c 

$(B)(eos_init.o):eos_init.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/eos_init.c $(DB)/eos_init.c 

$(B)(eosin.o):eosin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/eosin.c $(DB)/eosin.c 

$(B)(eosin0.o):eosin0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/eosin0.c $(DB)/eosin0.c 

$(B)(maxmin.o):maxmin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/maxmin.c $(DB)/maxmin.c 

$(B)(opacin.o):opacin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/opacin.c $(DB)/opacin.c 

$(B)(regcnst.o):regcnst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/regcnst.c $(DB)/regcnst.c 

$(B)(region.o):region.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/region.c $(DB)/region.c 

$(B)(regndx.o):regndx.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/regndx.c $(DB)/regndx.c 

../../includes/irsreg.hh:../../includes/irsreg.h
	cp ../../includes/irsreg.h ../../includes/irsreg.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irsreg.hh
	irs_hhinit ../../includes/irsreg.hh

$(B)(species.o):../../includes/irsreg.hh

$(B)(species.o):species.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/species.c $(DB)/species.c 

#---------------------
# lint pass one target 
#---------------------
lint:OpacTypesIn.ln eos_init.ln eosin.ln eosin0.ln maxmin.ln opacin.ln regcnst.ln \
	  region.ln regndx.ln species.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
OpacTypesIn.ln:OpacTypesIn.c ../../includes/irs.h ../../includes/irsreg.h         \
	  ../../includes/irseos.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON OpacTypesIn.c ***' >> $(LO)
	$$irs_lint OpacTypesIn.c 2>&1 | tee -a $(LO)

eos_init.ln:eos_init.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irscom.h ../../includes/irseos.h                         \
	  ../../includes/irsparm.h ../../includes/FunctionTimer.h                 \
	  ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON eos_init.c ***' >> $(LO)
	$$irs_lint eos_init.c 2>&1 | tee -a $(LO)

eosin.ln:eosin.c ../../includes/irs.h ../../includes/irsreg.h                     \
	  ../../includes/irseos.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON eosin.c ***' >> $(LO)
	$$irs_lint eosin.c 2>&1 | tee -a $(LO)

eosin0.ln:eosin0.c ../../includes/irs.h ../../includes/irseos.h                   \
	  ../../includes/irsreg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON eosin0.c ***' >> $(LO)
	$$irs_lint eosin0.c 2>&1 | tee -a $(LO)

maxmin.ln:maxmin.c ../../includes/irs.h ../../includes/irsreg.h                   \
	  ../../includes/irscom.h ../../includes/irsrgst.h                        \
	  ../../includes/BlockMapping.h ../../includes/FunctionTimer.h            \
	  ../../includes/NodeList.h ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON maxmin.c ***' >> $(LO)
	$$irs_lint maxmin.c 2>&1 | tee -a $(LO)

opacin.ln:opacin.c ../../includes/irs.h ../../includes/irsreg.h                   \
	  ../../includes/irseos.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON opacin.c ***' >> $(LO)
	$$irs_lint opacin.c 2>&1 | tee -a $(LO)

regcnst.ln:regcnst.c ../../includes/irs.h ../../includes/irsreg.h                 \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON regcnst.c ***' >> $(LO)
	$$irs_lint regcnst.c 2>&1 | tee -a $(LO)

region.ln:region.c ../../includes/irs.h ../../includes/irsreg.h                   \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/AEStackElm.h ../../includes/NodeList.h                   \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/UserList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON region.c ***' >> $(LO)
	$$irs_lint region.c 2>&1 | tee -a $(LO)

regndx.ln:regndx.c ../../includes/irs.h ../../includes/irsreg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON regndx.c ***' >> $(LO)
	$$irs_lint regndx.c 2>&1 | tee -a $(LO)

species.ln:species.c ../../includes/irs.h ../../includes/irsreg.hh                \
	  ../../includes/Hash.h ../../includes/Region.h ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON species.c ***' >> $(LO)
	$$irs_lint species.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/OpacTypesIn.inst.i $(PREDIR)/eos_init.inst.i                 \
	  $(PREDIR)/eosin.inst.i $(PREDIR)/eosin0.inst.i $(PREDIR)/maxmin.inst.i  \
	  $(PREDIR)/opacin.inst.i $(PREDIR)/regcnst.inst.i                        \
	  $(PREDIR)/region.inst.i $(PREDIR)/regndx.inst.i                         \
	  $(PREDIR)/species.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/OpacTypesIn.inst.i:OpacTypesIn.c ../../includes/irs.h                   \
	  ../../includes/irsreg.h ../../includes/irseos.h
	@rm -f OpacTypesIn.i
	$$irs_pre OpacTypesIn.c >> OpacTypesIn.i
	@mv -f OpacTypesIn.i $(PREDIR)/OpacTypesIn.inst.i

$(PREDIR)/eos_init.inst.i:eos_init.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irscom.h ../../includes/irseos.h                         \
	  ../../includes/irsparm.h ../../includes/FunctionTimer.h                 \
	  ../../includes/Hash.h
	@rm -f eos_init.i
	$$irs_pre eos_init.c >> eos_init.i
	@mv -f eos_init.i $(PREDIR)/eos_init.inst.i

$(PREDIR)/eosin.inst.i:eosin.c ../../includes/irs.h ../../includes/irsreg.h       \
	  ../../includes/irseos.h
	@rm -f eosin.i
	$$irs_pre eosin.c >> eosin.i
	@mv -f eosin.i $(PREDIR)/eosin.inst.i

$(PREDIR)/eosin0.inst.i:eosin0.c ../../includes/irs.h ../../includes/irseos.h     \
	  ../../includes/irsreg.h
	@rm -f eosin0.i
	$$irs_pre eosin0.c >> eosin0.i
	@mv -f eosin0.i $(PREDIR)/eosin0.inst.i

$(PREDIR)/maxmin.inst.i:maxmin.c ../../includes/irs.h ../../includes/irsreg.h     \
	  ../../includes/irscom.h ../../includes/irsrgst.h                        \
	  ../../includes/BlockMapping.h ../../includes/FunctionTimer.h            \
	  ../../includes/NodeList.h ../../includes/ProblemArray.h
	@rm -f maxmin.i
	$$irs_pre maxmin.c >> maxmin.i
	@mv -f maxmin.i $(PREDIR)/maxmin.inst.i

$(PREDIR)/opacin.inst.i:opacin.c ../../includes/irs.h ../../includes/irsreg.h     \
	  ../../includes/irseos.h
	@rm -f opacin.i
	$$irs_pre opacin.c >> opacin.i
	@mv -f opacin.i $(PREDIR)/opacin.inst.i

$(PREDIR)/regcnst.inst.i:regcnst.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/FunctionTimer.h
	@rm -f regcnst.i
	$$irs_pre regcnst.c >> regcnst.i
	@mv -f regcnst.i $(PREDIR)/regcnst.inst.i

$(PREDIR)/region.inst.i:region.c ../../includes/irs.h ../../includes/irsreg.h     \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/AEStackElm.h ../../includes/NodeList.h                   \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/UserList.h
	@rm -f region.i
	$$irs_pre region.c >> region.i
	@mv -f region.i $(PREDIR)/region.inst.i

$(PREDIR)/regndx.inst.i:regndx.c ../../includes/irs.h ../../includes/irsreg.h
	@rm -f regndx.i
	$$irs_pre regndx.c >> regndx.i
	@mv -f regndx.i $(PREDIR)/regndx.inst.i

$(PREDIR)/species.inst.i:species.c ../../includes/irs.h ../../includes/irsreg.hh  \
	  ../../includes/Hash.h ../../includes/Region.h ../../includes/irs.h
	@rm -f species.i
	$$irs_pre species.c >> species.i
	@mv -f species.i $(PREDIR)/species.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libreg_inst

libreg_inst:$(BI)(OpacTypesIn.inst.o) $(BI)(eos_init.inst.o) $(BI)(eosin.inst.o)  \
	  $(BI)(eosin0.inst.o) $(BI)(maxmin.inst.o) $(BI)(opacin.inst.o)          \
	  $(BI)(regcnst.inst.o) $(BI)(region.inst.o) $(BI)(regndx.inst.o)         \
	  $(BI)(species.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libreg_inst.a $(B); \
		ln -sf libreg_inst.a $(B)); \
	  fi
	  @echo 'libreg_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(OpacTypesIn.inst.o):$(INSTDIR)/OpacTypesIn.inst.i
	$$irs_post $(INSTDIR)/OpacTypesIn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/OpacTypesIn.inst.i $(DB)/OpacTypesIn.c 

$(BI)(eos_init.inst.o):$(INSTDIR)/eos_init.inst.i
	$$irs_post $(INSTDIR)/eos_init.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/eos_init.inst.i $(DB)/eos_init.c 

$(BI)(eosin.inst.o):$(INSTDIR)/eosin.inst.i
	$$irs_post $(INSTDIR)/eosin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/eosin.inst.i $(DB)/eosin.c 

$(BI)(eosin0.inst.o):$(INSTDIR)/eosin0.inst.i
	$$irs_post $(INSTDIR)/eosin0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/eosin0.inst.i $(DB)/eosin0.c 

$(BI)(maxmin.inst.o):$(INSTDIR)/maxmin.inst.i
	$$irs_post $(INSTDIR)/maxmin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/maxmin.inst.i $(DB)/maxmin.c 

$(BI)(opacin.inst.o):$(INSTDIR)/opacin.inst.i
	$$irs_post $(INSTDIR)/opacin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/opacin.inst.i $(DB)/opacin.c 

$(BI)(regcnst.inst.o):$(INSTDIR)/regcnst.inst.i
	$$irs_post $(INSTDIR)/regcnst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/regcnst.inst.i $(DB)/regcnst.c 

$(BI)(region.inst.o):$(INSTDIR)/region.inst.i
	$$irs_post $(INSTDIR)/region.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/region.inst.i $(DB)/region.c 

$(BI)(regndx.inst.o):$(INSTDIR)/regndx.inst.i
	$$irs_post $(INSTDIR)/regndx.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/regndx.inst.i $(DB)/regndx.c 

$(BI)(species.inst.o):$(INSTDIR)/species.inst.i
	$$irs_post $(INSTDIR)/species.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/species.inst.i $(DB)/species.c 

DEP_SRCS = \
	OpacTypesIn.c eos_init.c eosin.c eosin0.c maxmin.c opacin.c regcnst.c  \
	region.c regndx.c species.c  

depend:
	@cp -f Makefile.reg Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(OpacTypesIn.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(OpacTypesIn.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(OpacTypesIn.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(OpacTypesIn.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(OpacTypesIn.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(OpacTypesIn.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(OpacTypesIn.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(OpacTypesIn.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(OpacTypesIn.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(OpacTypesIn.o): /usr/include/time.h /usr/include/endian.h
$(B)(OpacTypesIn.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(OpacTypesIn.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(OpacTypesIn.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(OpacTypesIn.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(OpacTypesIn.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(OpacTypesIn.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(OpacTypesIn.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(OpacTypesIn.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(OpacTypesIn.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(OpacTypesIn.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(OpacTypesIn.o): /usr/include/ctype.h /usr/include/math.h
$(B)(OpacTypesIn.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(OpacTypesIn.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(OpacTypesIn.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(OpacTypesIn.o): ../../includes/Region.h ../../includes/irseos.h
$(B)(OpacTypesIn.o): ../../includes/Thermo.h
$(B)(eos_init.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(eos_init.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(eos_init.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(eos_init.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(eos_init.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(eos_init.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(eos_init.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(eos_init.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(eos_init.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(eos_init.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(eos_init.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(eos_init.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(eos_init.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(eos_init.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(eos_init.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(eos_init.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(eos_init.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(eos_init.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(eos_init.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(eos_init.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(eos_init.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(eos_init.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(eos_init.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(eos_init.o): ../../includes/Region.h ../../includes/irscom.h
$(B)(eos_init.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(eos_init.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(eos_init.o): ../../includes/irseos.h ../../includes/Thermo.h
$(B)(eos_init.o): ../../includes/irsparm.h
$(B)(eosin.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(eosin.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(eosin.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(eosin.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(eosin.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(eosin.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(eosin.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(eosin.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(eosin.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(eosin.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(eosin.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(eosin.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(eosin.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(eosin.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(eosin.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(eosin.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(eosin.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(eosin.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(eosin.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(eosin.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(eosin.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irsreg.h
$(B)(eosin.o): ../../includes/Region.h ../../includes/irseos.h
$(B)(eosin.o): ../../includes/Thermo.h
$(B)(eosin0.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(eosin0.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(eosin0.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(eosin0.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(eosin0.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(eosin0.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(eosin0.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(eosin0.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(eosin0.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(eosin0.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(eosin0.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(eosin0.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(eosin0.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(eosin0.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(eosin0.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(eosin0.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(eosin0.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(eosin0.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(eosin0.o): /usr/include/ctype.h /usr/include/math.h
$(B)(eosin0.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(eosin0.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(eosin0.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(eosin0.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(eosin0.o): ../../includes/irsreg.h
$(B)(maxmin.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(maxmin.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(maxmin.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(maxmin.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(maxmin.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(maxmin.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(maxmin.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(maxmin.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(maxmin.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(maxmin.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(maxmin.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(maxmin.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(maxmin.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(maxmin.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(maxmin.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(maxmin.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(maxmin.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(maxmin.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(maxmin.o): /usr/include/ctype.h /usr/include/math.h
$(B)(maxmin.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(maxmin.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(maxmin.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(maxmin.o): ../../includes/Region.h ../../includes/irscom.h
$(B)(maxmin.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(maxmin.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(maxmin.o): ../../includes/irsrgst.h ../../includes/BlockMapping.h
$(B)(maxmin.o): ../../includes/BndMapping.h ../../includes/ProblemArray.h
$(B)(opacin.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(opacin.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(opacin.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(opacin.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(opacin.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(opacin.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(opacin.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(opacin.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(opacin.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(opacin.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(opacin.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(opacin.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(opacin.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(opacin.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(opacin.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(opacin.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(opacin.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(opacin.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(opacin.o): /usr/include/ctype.h /usr/include/math.h
$(B)(opacin.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(opacin.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(opacin.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(opacin.o): ../../includes/Region.h ../../includes/irseos.h
$(B)(opacin.o): ../../includes/Thermo.h
$(B)(regcnst.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(regcnst.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(regcnst.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(regcnst.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(regcnst.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(regcnst.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(regcnst.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(regcnst.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(regcnst.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(regcnst.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(regcnst.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(regcnst.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(regcnst.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(regcnst.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(regcnst.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(regcnst.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(regcnst.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(regcnst.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(regcnst.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(regcnst.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(regcnst.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(regcnst.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(regcnst.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(region.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(region.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(region.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(region.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(region.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(region.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(region.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(region.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(region.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(region.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(region.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(region.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(region.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(region.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(region.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(region.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(region.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(region.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(region.o): /usr/include/ctype.h /usr/include/math.h
$(B)(region.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(region.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(region.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(region.o): ../../includes/Region.h ../../includes/irsrgst.h
$(B)(region.o): ../../includes/AEStackElm.h ../../includes/NodeList.h
$(B)(region.o): ../../includes/Extents.h ../../includes/ProblemArray.h
$(B)(region.o): ../../includes/UserList.h
$(B)(regndx.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(regndx.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(regndx.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(regndx.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(regndx.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(regndx.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(regndx.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(regndx.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(regndx.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(regndx.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(regndx.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(regndx.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(regndx.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(regndx.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(regndx.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(regndx.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(regndx.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(regndx.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(regndx.o): /usr/include/ctype.h /usr/include/math.h
$(B)(regndx.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(regndx.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(regndx.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(regndx.o): ../../includes/Region.h
$(B)(species.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(species.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(species.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(species.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(species.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(species.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(species.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(species.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(species.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(species.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(species.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(species.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(species.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(species.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(species.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(species.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(species.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(species.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(species.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(species.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(species.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(species.o): /usr/include/malloc.h ../../includes/Region.h
