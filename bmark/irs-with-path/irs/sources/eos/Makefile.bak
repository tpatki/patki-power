
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

