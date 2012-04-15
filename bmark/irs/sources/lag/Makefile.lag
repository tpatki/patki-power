
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

