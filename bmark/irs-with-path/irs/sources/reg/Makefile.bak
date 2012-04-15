
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

