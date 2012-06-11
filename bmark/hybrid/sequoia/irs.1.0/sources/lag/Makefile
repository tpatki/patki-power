
################################################################################
#
# Makefile for irs library lag
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
B = ../$(LIB_DIR)/liblag.a
BI = ../$(LIB_DIR)/liblag_inst.a

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
SRCDIR = ../sources/lag

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

liblag:$(B)(DtTempControls.o) $(B)(DtTempInitialize.o) $(B)(HydroDtControls.o)    \
	  $(B)(InitCycle.o) $(B)(LengthScale.o) $(B)(PostSubcycle.o)              \
	  $(B)(PreSubcycle.o) $(B)(getnm2d0.o) $(B)(getnm3d.o) $(B)(update.o)     \
	  $(B)(updateblk.o) $(B)(xirs.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'lag library current'

# creation deps
#---------------
$(B)(DtTempControls.o):DtTempControls.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/DtTempControls.c $(DB)/DtTempControls.c 

$(B)(DtTempInitialize.o):DtTempInitialize.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/DtTempInitialize.c $(DB)/DtTempInitialize.c 

$(B)(HydroDtControls.o):HydroDtControls.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/HydroDtControls.c $(DB)/HydroDtControls.c 

$(B)(InitCycle.o):InitCycle.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/InitCycle.c $(DB)/InitCycle.c 

$(B)(LengthScale.o):LengthScale.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/LengthScale.c $(DB)/LengthScale.c 

$(B)(PostSubcycle.o):PostSubcycle.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/PostSubcycle.c $(DB)/PostSubcycle.c 

$(B)(PreSubcycle.o):PreSubcycle.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/PreSubcycle.c $(DB)/PreSubcycle.c 

$(B)(getnm2d0.o):getnm2d0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getnm2d0.c $(DB)/getnm2d0.c 

$(B)(getnm3d.o):getnm3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getnm3d.c $(DB)/getnm3d.c 

$(B)(update.o):update.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/update.c $(DB)/update.c 

$(B)(updateblk.o):updateblk.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/updateblk.c $(DB)/updateblk.c 

../../includes/irslag.hh:../../includes/irslag.h
	cp ../../includes/irslag.h ../../includes/irslag.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irslag.hh
	irs_hhinit ../../includes/irslag.hh

$(B)(xirs.o):../../includes/irslag.hh

$(B)(xirs.o):xirs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/xirs.c $(DB)/xirs.c 

#---------------------
# lint pass one target 
#---------------------
lint:DtTempControls.ln DtTempInitialize.ln HydroDtControls.ln InitCycle.ln        \
	  LengthScale.ln PostSubcycle.ln PreSubcycle.ln getnm2d0.ln getnm3d.ln    \
	  update.ln updateblk.ln xirs.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
DtTempControls.ln:DtTempControls.c ../../includes/irs.h ../../includes/irslag.h   \
	  ../../includes/irssys.h ../../includes/irsreg.h                         \
	  ../../includes/irsbndry.h ../../includes/TimeStepControl.h              \
	  ../../includes/FunctionTimer.h ../../includes/TimeStepControl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON DtTempControls.c ***' >> $(LO)
	$$irs_lint DtTempControls.c 2>&1 | tee -a $(LO)

DtTempInitialize.ln:DtTempInitialize.c ../../includes/irs.h                       \
	  ../../includes/irslag.h ../../includes/FunctionTimer.h                  \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON DtTempInitialize.c ***' >> $(LO)
	$$irs_lint DtTempInitialize.c 2>&1 | tee -a $(LO)

HydroDtControls.ln:HydroDtControls.c ../../includes/irs.h ../../includes/irssys.h \
	  ../../includes/irsreg.h ../../includes/irslag.h                         \
	  ../../includes/irsbndry.h ../../includes/irsgen.h                       \
	  ../../includes/FunctionTimer.h ../../includes/TimeStepControl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON HydroDtControls.c ***' >> $(LO)
	$$irs_lint HydroDtControls.c 2>&1 | tee -a $(LO)

InitCycle.ln:InitCycle.c ../../includes/irs.h ../../includes/irslag.h             \
	  ../../includes/FunctionTimer.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON InitCycle.c ***' >> $(LO)
	$$irs_lint InitCycle.c 2>&1 | tee -a $(LO)

LengthScale.ln:LengthScale.c ../../includes/irs.h ../../includes/irsreg.h         \
	  ../../includes/irslag.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON LengthScale.c ***' >> $(LO)
	$$irs_lint LengthScale.c 2>&1 | tee -a $(LO)

PostSubcycle.ln:PostSubcycle.c ../../includes/irs.h ../../includes/irslag.h       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON PostSubcycle.c ***' >> $(LO)
	$$irs_lint PostSubcycle.c 2>&1 | tee -a $(LO)

PreSubcycle.ln:PreSubcycle.c ../../includes/irs.h ../../includes/irslag.h         \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON PreSubcycle.c ***' >> $(LO)
	$$irs_lint PreSubcycle.c 2>&1 | tee -a $(LO)

getnm2d0.ln:getnm2d0.c ../../includes/irs.h ../../includes/irslag.h               \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getnm2d0.c ***' >> $(LO)
	$$irs_lint getnm2d0.c 2>&1 | tee -a $(LO)

getnm3d.ln:getnm3d.c ../../includes/irs.h ../../includes/irslag.h                 \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getnm3d.c ***' >> $(LO)
	$$irs_lint getnm3d.c 2>&1 | tee -a $(LO)

update.ln:update.c ../../includes/irs.h ../../includes/irslag.h                   \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/Tracer.h ../../includes/TimeStepControl.h                \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON update.c ***' >> $(LO)
	$$irs_lint update.c 2>&1 | tee -a $(LO)

updateblk.ln:updateblk.c ../../includes/irs.h ../../includes/irsreg.h             \
	  ../../includes/irslag.h ../../includes/irseos.h                         \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON updateblk.c ***' >> $(LO)
	$$irs_lint updateblk.c 2>&1 | tee -a $(LO)

xirs.ln:xirs.c ../../includes/irs.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/irsctl.h ../../includes/irsdmp.h \
	  ../../includes/irsedits.h ../../includes/irseos.h                       \
	  ../../includes/irslag.hh ../../includes/irsreg.h                        \
	  ../../includes/irssrc.h ../../includes/irssys.h                         \
	  ../../includes/irstdiff.h ../../includes/CycleMesg.h                    \
	  ../../includes/Source.h ../../includes/FunctionTimer.h                  \
	  ../../includes/TimeStepControl.h ../../includes/pardo.h                 \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON xirs.c ***' >> $(LO)
	$$irs_lint xirs.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/DtTempControls.inst.i $(PREDIR)/DtTempInitialize.inst.i      \
	  $(PREDIR)/HydroDtControls.inst.i $(PREDIR)/InitCycle.inst.i             \
	  $(PREDIR)/LengthScale.inst.i $(PREDIR)/PostSubcycle.inst.i              \
	  $(PREDIR)/PreSubcycle.inst.i $(PREDIR)/getnm2d0.inst.i                  \
	  $(PREDIR)/getnm3d.inst.i $(PREDIR)/update.inst.i                        \
	  $(PREDIR)/updateblk.inst.i $(PREDIR)/xirs.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/DtTempControls.inst.i:DtTempControls.c ../../includes/irs.h             \
	  ../../includes/irslag.h ../../includes/irssys.h ../../includes/irsreg.h \
	  ../../includes/irsbndry.h ../../includes/TimeStepControl.h              \
	  ../../includes/FunctionTimer.h ../../includes/TimeStepControl.h
	@rm -f DtTempControls.i
	$$irs_pre DtTempControls.c >> DtTempControls.i
	@mv -f DtTempControls.i $(PREDIR)/DtTempControls.inst.i

$(PREDIR)/DtTempInitialize.inst.i:DtTempInitialize.c ../../includes/irs.h         \
	  ../../includes/irslag.h ../../includes/FunctionTimer.h                  \
	  ../../includes/pardo.h
	@rm -f DtTempInitialize.i
	$$irs_pre DtTempInitialize.c >> DtTempInitialize.i
	@mv -f DtTempInitialize.i $(PREDIR)/DtTempInitialize.inst.i

$(PREDIR)/HydroDtControls.inst.i:HydroDtControls.c ../../includes/irs.h           \
	  ../../includes/irssys.h ../../includes/irsreg.h ../../includes/irslag.h \
	  ../../includes/irsbndry.h ../../includes/irsgen.h                       \
	  ../../includes/FunctionTimer.h ../../includes/TimeStepControl.h
	@rm -f HydroDtControls.i
	$$irs_pre HydroDtControls.c >> HydroDtControls.i
	@mv -f HydroDtControls.i $(PREDIR)/HydroDtControls.inst.i

$(PREDIR)/InitCycle.inst.i:InitCycle.c ../../includes/irs.h                       \
	  ../../includes/irslag.h ../../includes/FunctionTimer.h                  \
	  ../../includes/pardo.h ../../includes/pardo.h
	@rm -f InitCycle.i
	$$irs_pre InitCycle.c >> InitCycle.i
	@mv -f InitCycle.i $(PREDIR)/InitCycle.inst.i

$(PREDIR)/LengthScale.inst.i:LengthScale.c ../../includes/irs.h                   \
	  ../../includes/irsreg.h ../../includes/irslag.h                         \
	  ../../includes/FunctionTimer.h
	@rm -f LengthScale.i
	$$irs_pre LengthScale.c >> LengthScale.i
	@mv -f LengthScale.i $(PREDIR)/LengthScale.inst.i

$(PREDIR)/PostSubcycle.inst.i:PostSubcycle.c ../../includes/irs.h                 \
	  ../../includes/irslag.h ../../includes/FunctionTimer.h
	@rm -f PostSubcycle.i
	$$irs_pre PostSubcycle.c >> PostSubcycle.i
	@mv -f PostSubcycle.i $(PREDIR)/PostSubcycle.inst.i

$(PREDIR)/PreSubcycle.inst.i:PreSubcycle.c ../../includes/irs.h                   \
	  ../../includes/irslag.h ../../includes/FunctionTimer.h
	@rm -f PreSubcycle.i
	$$irs_pre PreSubcycle.c >> PreSubcycle.i
	@mv -f PreSubcycle.i $(PREDIR)/PreSubcycle.inst.i

$(PREDIR)/getnm2d0.inst.i:getnm2d0.c ../../includes/irs.h ../../includes/irslag.h \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	@rm -f getnm2d0.i
	$$irs_pre getnm2d0.c >> getnm2d0.i
	@mv -f getnm2d0.i $(PREDIR)/getnm2d0.inst.i

$(PREDIR)/getnm3d.inst.i:getnm3d.c ../../includes/irs.h ../../includes/irslag.h   \
	  ../../includes/FunctionTimer.h
	@rm -f getnm3d.i
	$$irs_pre getnm3d.c >> getnm3d.i
	@mv -f getnm3d.i $(PREDIR)/getnm3d.inst.i

$(PREDIR)/update.inst.i:update.c ../../includes/irs.h ../../includes/irslag.h     \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/Tracer.h ../../includes/TimeStepControl.h                \
	  ../../includes/pardo.h
	@rm -f update.i
	$$irs_pre update.c >> update.i
	@mv -f update.i $(PREDIR)/update.inst.i

$(PREDIR)/updateblk.inst.i:updateblk.c ../../includes/irs.h                       \
	  ../../includes/irsreg.h ../../includes/irslag.h ../../includes/irseos.h \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f updateblk.i
	$$irs_pre updateblk.c >> updateblk.i
	@mv -f updateblk.i $(PREDIR)/updateblk.inst.i

$(PREDIR)/xirs.inst.i:xirs.c ../../includes/irs.h ../../includes/irsbndry.h       \
	  ../../includes/irscom.h ../../includes/irsctl.h ../../includes/irsdmp.h \
	  ../../includes/irsedits.h ../../includes/irseos.h                       \
	  ../../includes/irslag.hh ../../includes/irsreg.h                        \
	  ../../includes/irssrc.h ../../includes/irssys.h                         \
	  ../../includes/irstdiff.h ../../includes/CycleMesg.h                    \
	  ../../includes/Source.h ../../includes/FunctionTimer.h                  \
	  ../../includes/TimeStepControl.h ../../includes/pardo.h                 \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h
	@rm -f xirs.i
	$$irs_pre xirs.c >> xirs.i
	@mv -f xirs.i $(PREDIR)/xirs.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:liblag_inst

liblag_inst:$(BI)(DtTempControls.inst.o) $(BI)(DtTempInitialize.inst.o)           \
	  $(BI)(HydroDtControls.inst.o) $(BI)(InitCycle.inst.o)                   \
	  $(BI)(LengthScale.inst.o) $(BI)(PostSubcycle.inst.o)                    \
	  $(BI)(PreSubcycle.inst.o) $(BI)(getnm2d0.inst.o) $(BI)(getnm3d.inst.o)  \
	  $(BI)(update.inst.o) $(BI)(updateblk.inst.o) $(BI)(xirs.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf liblag_inst.a $(B); \
		ln -sf liblag_inst.a $(B)); \
	  fi
	  @echo 'liblag_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(DtTempControls.inst.o):$(INSTDIR)/DtTempControls.inst.i
	$$irs_post $(INSTDIR)/DtTempControls.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/DtTempControls.inst.i $(DB)/DtTempControls.c 

$(BI)(DtTempInitialize.inst.o):$(INSTDIR)/DtTempInitialize.inst.i
	$$irs_post $(INSTDIR)/DtTempInitialize.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/DtTempInitialize.inst.i $(DB)/DtTempInitialize.c 

$(BI)(HydroDtControls.inst.o):$(INSTDIR)/HydroDtControls.inst.i
	$$irs_post $(INSTDIR)/HydroDtControls.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/HydroDtControls.inst.i $(DB)/HydroDtControls.c 

$(BI)(InitCycle.inst.o):$(INSTDIR)/InitCycle.inst.i
	$$irs_post $(INSTDIR)/InitCycle.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/InitCycle.inst.i $(DB)/InitCycle.c 

$(BI)(LengthScale.inst.o):$(INSTDIR)/LengthScale.inst.i
	$$irs_post $(INSTDIR)/LengthScale.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/LengthScale.inst.i $(DB)/LengthScale.c 

$(BI)(PostSubcycle.inst.o):$(INSTDIR)/PostSubcycle.inst.i
	$$irs_post $(INSTDIR)/PostSubcycle.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/PostSubcycle.inst.i $(DB)/PostSubcycle.c 

$(BI)(PreSubcycle.inst.o):$(INSTDIR)/PreSubcycle.inst.i
	$$irs_post $(INSTDIR)/PreSubcycle.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/PreSubcycle.inst.i $(DB)/PreSubcycle.c 

$(BI)(getnm2d0.inst.o):$(INSTDIR)/getnm2d0.inst.i
	$$irs_post $(INSTDIR)/getnm2d0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getnm2d0.inst.i $(DB)/getnm2d0.c 

$(BI)(getnm3d.inst.o):$(INSTDIR)/getnm3d.inst.i
	$$irs_post $(INSTDIR)/getnm3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getnm3d.inst.i $(DB)/getnm3d.c 

$(BI)(update.inst.o):$(INSTDIR)/update.inst.i
	$$irs_post $(INSTDIR)/update.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/update.inst.i $(DB)/update.c 

$(BI)(updateblk.inst.o):$(INSTDIR)/updateblk.inst.i
	$$irs_post $(INSTDIR)/updateblk.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/updateblk.inst.i $(DB)/updateblk.c 

$(BI)(xirs.inst.o):$(INSTDIR)/xirs.inst.i
	$$irs_post $(INSTDIR)/xirs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/xirs.inst.i $(DB)/xirs.c 

DEP_SRCS = \
	DtTempControls.c DtTempInitialize.c HydroDtControls.c InitCycle.c LengthScale.c  \
	PostSubcycle.c PreSubcycle.c getnm2d0.c getnm3d.c update.c updateblk.c  \
	xirs.c  

depend:
	@cp -f Makefile.lag Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(DtTempControls.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(DtTempControls.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(DtTempControls.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(DtTempControls.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(DtTempControls.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(DtTempControls.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(DtTempControls.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(DtTempControls.o): /usr/include/bits/stdio_lim.h
$(B)(DtTempControls.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(DtTempControls.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(DtTempControls.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(DtTempControls.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(DtTempControls.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(DtTempControls.o): /usr/include/sys/sysmacros.h
$(B)(DtTempControls.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(DtTempControls.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(DtTempControls.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(DtTempControls.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(DtTempControls.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(DtTempControls.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(DtTempControls.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(DtTempControls.o): /usr/include/ctype.h /usr/include/math.h
$(B)(DtTempControls.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(DtTempControls.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(DtTempControls.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(DtTempControls.o): ../../includes/State.h ../../includes/irssys.h
$(B)(DtTempControls.o): ../../includes/irsreg.h ../../includes/Region.h
$(B)(DtTempControls.o): ../../includes/irsbndry.h ../../includes/TimeStepControl.h
$(B)(DtTempControls.o): ../../includes/FunctionTimer.h
$(B)(DtTempInitialize.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(DtTempInitialize.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(DtTempInitialize.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(DtTempInitialize.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(DtTempInitialize.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(DtTempInitialize.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(DtTempInitialize.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(DtTempInitialize.o): /usr/include/bits/stdio_lim.h
$(B)(DtTempInitialize.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(DtTempInitialize.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(DtTempInitialize.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(DtTempInitialize.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(DtTempInitialize.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(DtTempInitialize.o): /usr/include/sys/sysmacros.h
$(B)(DtTempInitialize.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(DtTempInitialize.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(DtTempInitialize.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(DtTempInitialize.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(DtTempInitialize.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(DtTempInitialize.o): ../../includes/Source.h
$(B)(DtTempInitialize.o): ../../includes/BoundaryCondition.h
$(B)(DtTempInitialize.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(DtTempInitialize.o): /usr/include/ctype.h /usr/include/math.h
$(B)(DtTempInitialize.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(DtTempInitialize.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(DtTempInitialize.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(DtTempInitialize.o): ../../includes/State.h ../../includes/FunctionTimer.h
$(B)(DtTempInitialize.o): ../../includes/pardo.h
$(B)(HydroDtControls.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(HydroDtControls.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(HydroDtControls.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(HydroDtControls.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(HydroDtControls.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(HydroDtControls.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(HydroDtControls.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(HydroDtControls.o): /usr/include/bits/stdio_lim.h
$(B)(HydroDtControls.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(HydroDtControls.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(HydroDtControls.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(HydroDtControls.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(HydroDtControls.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(HydroDtControls.o): /usr/include/sys/sysmacros.h
$(B)(HydroDtControls.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(HydroDtControls.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(HydroDtControls.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(HydroDtControls.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(HydroDtControls.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(HydroDtControls.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(HydroDtControls.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(HydroDtControls.o): /usr/include/ctype.h /usr/include/math.h
$(B)(HydroDtControls.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(HydroDtControls.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(HydroDtControls.o): /usr/include/malloc.h ../../includes/irssys.h
$(B)(HydroDtControls.o): ../../includes/irsreg.h ../../includes/Region.h
$(B)(HydroDtControls.o): ../../includes/irslag.h ../../includes/State.h
$(B)(HydroDtControls.o): ../../includes/irsbndry.h ../../includes/irsgen.h
$(B)(HydroDtControls.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(HydroDtControls.o): ../../includes/FunctionTimer.h
$(B)(HydroDtControls.o): ../../includes/TimeStepControl.h
$(B)(InitCycle.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(InitCycle.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(InitCycle.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(InitCycle.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(InitCycle.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(InitCycle.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(InitCycle.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(InitCycle.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(InitCycle.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(InitCycle.o): /usr/include/time.h /usr/include/endian.h
$(B)(InitCycle.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(InitCycle.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(InitCycle.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(InitCycle.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(InitCycle.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(InitCycle.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(InitCycle.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(InitCycle.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(InitCycle.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(InitCycle.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(InitCycle.o): /usr/include/ctype.h /usr/include/math.h
$(B)(InitCycle.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(InitCycle.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(InitCycle.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(InitCycle.o): ../../includes/State.h ../../includes/FunctionTimer.h
$(B)(InitCycle.o): ../../includes/pardo.h
$(B)(LengthScale.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(LengthScale.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(LengthScale.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(LengthScale.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(LengthScale.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(LengthScale.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(LengthScale.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(LengthScale.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(LengthScale.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(LengthScale.o): /usr/include/time.h /usr/include/endian.h
$(B)(LengthScale.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(LengthScale.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(LengthScale.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(LengthScale.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(LengthScale.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(LengthScale.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(LengthScale.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(LengthScale.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(LengthScale.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(LengthScale.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(LengthScale.o): /usr/include/ctype.h /usr/include/math.h
$(B)(LengthScale.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(LengthScale.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(LengthScale.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(LengthScale.o): ../../includes/Region.h ../../includes/irslag.h
$(B)(LengthScale.o): ../../includes/State.h ../../includes/FunctionTimer.h
$(B)(PostSubcycle.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(PostSubcycle.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(PostSubcycle.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(PostSubcycle.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(PostSubcycle.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(PostSubcycle.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(PostSubcycle.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(PostSubcycle.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(PostSubcycle.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(PostSubcycle.o): /usr/include/time.h /usr/include/endian.h
$(B)(PostSubcycle.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(PostSubcycle.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(PostSubcycle.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(PostSubcycle.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(PostSubcycle.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(PostSubcycle.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(PostSubcycle.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(PostSubcycle.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(PostSubcycle.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(PostSubcycle.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(PostSubcycle.o): /usr/include/ctype.h /usr/include/math.h
$(B)(PostSubcycle.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(PostSubcycle.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(PostSubcycle.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(PostSubcycle.o): ../../includes/State.h ../../includes/FunctionTimer.h
$(B)(PreSubcycle.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(PreSubcycle.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(PreSubcycle.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(PreSubcycle.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(PreSubcycle.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(PreSubcycle.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(PreSubcycle.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(PreSubcycle.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(PreSubcycle.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(PreSubcycle.o): /usr/include/time.h /usr/include/endian.h
$(B)(PreSubcycle.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(PreSubcycle.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(PreSubcycle.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(PreSubcycle.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(PreSubcycle.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(PreSubcycle.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(PreSubcycle.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(PreSubcycle.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(PreSubcycle.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(PreSubcycle.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(PreSubcycle.o): /usr/include/ctype.h /usr/include/math.h
$(B)(PreSubcycle.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(PreSubcycle.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(PreSubcycle.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(PreSubcycle.o): ../../includes/State.h ../../includes/FunctionTimer.h
$(B)(getnm2d0.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(getnm2d0.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(getnm2d0.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(getnm2d0.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(getnm2d0.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(getnm2d0.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(getnm2d0.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(getnm2d0.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(getnm2d0.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(getnm2d0.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(getnm2d0.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(getnm2d0.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(getnm2d0.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(getnm2d0.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(getnm2d0.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(getnm2d0.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(getnm2d0.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(getnm2d0.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(getnm2d0.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(getnm2d0.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(getnm2d0.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getnm2d0.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(getnm2d0.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(getnm2d0.o): ../../includes/State.h ../../includes/irsbndry.h
$(B)(getnm2d0.o): ../../includes/FunctionTimer.h
$(B)(getnm3d.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(getnm3d.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(getnm3d.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(getnm3d.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(getnm3d.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getnm3d.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getnm3d.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getnm3d.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(getnm3d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(getnm3d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(getnm3d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(getnm3d.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(getnm3d.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(getnm3d.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(getnm3d.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(getnm3d.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(getnm3d.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(getnm3d.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(getnm3d.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(getnm3d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getnm3d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(getnm3d.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(getnm3d.o): ../../includes/State.h ../../includes/FunctionTimer.h
$(B)(update.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(update.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(update.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(update.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(update.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(update.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(update.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(update.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(update.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(update.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(update.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(update.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(update.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(update.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(update.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(update.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(update.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(update.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(update.o): /usr/include/ctype.h /usr/include/math.h
$(B)(update.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(update.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(update.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(update.o): ../../includes/State.h ../../includes/irscom.h
$(B)(update.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(update.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(update.o): ../../includes/Tracer.h ../../includes/TimeStepControl.h
$(B)(update.o): ../../includes/pardo.h
$(B)(updateblk.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(updateblk.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(updateblk.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(updateblk.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(updateblk.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(updateblk.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(updateblk.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(updateblk.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(updateblk.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(updateblk.o): /usr/include/time.h /usr/include/endian.h
$(B)(updateblk.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(updateblk.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(updateblk.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(updateblk.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(updateblk.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(updateblk.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(updateblk.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(updateblk.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(updateblk.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(updateblk.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(updateblk.o): /usr/include/ctype.h /usr/include/math.h
$(B)(updateblk.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(updateblk.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(updateblk.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(updateblk.o): ../../includes/Region.h ../../includes/irslag.h
$(B)(updateblk.o): ../../includes/State.h ../../includes/irseos.h
$(B)(updateblk.o): ../../includes/Thermo.h ../../includes/irstdiff.h
$(B)(updateblk.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(updateblk.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(updateblk.o): ../../includes/FunctionTimer.h
$(B)(xirs.o): /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(xirs.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(xirs.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(xirs.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(xirs.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(xirs.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(xirs.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(xirs.o): /usr/include/signal.h /usr/include/bits/sigset.h
$(B)(xirs.o): /usr/include/bits/signum.h /usr/include/time.h
$(B)(xirs.o): /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
$(B)(xirs.o): /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
$(B)(xirs.o): /usr/include/bits/pthreadtypes.h /usr/include/bits/sigthread.h
$(B)(xirs.o): /usr/include/unistd.h /usr/include/bits/posix_opt.h
$(B)(xirs.o): /usr/include/bits/confname.h /usr/include/getopt.h
$(B)(xirs.o): /usr/include/sys/types.h /usr/include/endian.h
$(B)(xirs.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(xirs.o): /usr/include/bits/select.h /usr/include/bits/time.h
$(B)(xirs.o): /usr/include/sys/sysmacros.h /usr/include/sys/time.h
$(B)(xirs.o): ../../includes/irs.h /usr/include/stdlib.h /usr/include/alloca.h
$(B)(xirs.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(xirs.o): ../../includes/irsctl.h ../../includes/Rgst.h ../../includes/Hash.h
$(B)(xirs.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(xirs.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(xirs.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(xirs.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(xirs.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(xirs.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(xirs.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(xirs.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(xirs.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(xirs.o): ../../includes/Extents.h ../../includes/irsdmp.h
$(B)(xirs.o): ../../includes/irsedits.h ../../includes/irseos.h
$(B)(xirs.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(xirs.o): ../../includes/irsreg.h ../../includes/irssrc.h
$(B)(xirs.o): ../../includes/irssys.h ../../includes/irstdiff.h
$(B)(xirs.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(xirs.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(xirs.o): ../../includes/CycleMesg.h ../../includes/TimeStepControl.h
$(B)(xirs.o): ../../includes/pardo.h
