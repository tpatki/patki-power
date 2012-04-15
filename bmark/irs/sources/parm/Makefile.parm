
################################################################################
#
# Makefile for irs library parm
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
B = ../$(LIB_DIR)/libparm.a
BI = ../$(LIB_DIR)/libparm_inst.a

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
SRCDIR = ../sources/parm

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libparm:$(B)(boxid.o) $(B)(create_temp_pa.o) $(B)(free_temp_pa.o) $(B)(memclr.o)  \
	  $(B)(memexp.o) $(B)(ndset.o) $(B)(parm.o) $(B)(parminit.o)              \
	  $(B)(parmsanity.o) $(B)(set.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'parm library current'

# creation deps
#---------------
$(B)(boxid.o):boxid.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/boxid.c $(DB)/boxid.c 

$(B)(create_temp_pa.o):create_temp_pa.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/create_temp_pa.c $(DB)/create_temp_pa.c 

$(B)(free_temp_pa.o):free_temp_pa.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/free_temp_pa.c $(DB)/free_temp_pa.c 

$(B)(memclr.o):memclr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/memclr.c $(DB)/memclr.c 

../../includes/BiQuadradic.hh:../../includes/BiQuadradic.h
	cp ../../includes/BiQuadradic.h ../../includes/BiQuadradic.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/BiQuadradic.hh
	irs_hhinit ../../includes/BiQuadradic.hh

$(B)(memexp.o):../../includes/BiQuadradic.hh

$(B)(memexp.o):memexp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/memexp.c $(DB)/memexp.c 

$(B)(ndset.o):ndset.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ndset.c $(DB)/ndset.c 

$(B)(parm.o):parm.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/parm.c $(DB)/parm.c 

../../includes/irs.hh:../../includes/irs.h
	cp ../../includes/irs.h ../../includes/irs.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irs.hh
	irs_hhinit ../../includes/irs.hh

$(B)(parminit.o):../../includes/irs.hh

../../includes/irslag.hh:../../includes/irslag.h
	cp ../../includes/irslag.h ../../includes/irslag.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irslag.hh
	irs_hhinit ../../includes/irslag.hh

$(B)(parminit.o):../../includes/irslag.hh

../../includes/irsparm.hh:../../includes/irsparm.h
	cp ../../includes/irsparm.h ../../includes/irsparm.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irsparm.hh
	irs_hhinit ../../includes/irsparm.hh

$(B)(parminit.o):../../includes/irsparm.hh

../../includes/TimeStepControl.hh:../../includes/TimeStepControl.h
	cp ../../includes/TimeStepControl.h ../../includes/TimeStepControl.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/TimeStepControl.hh
	irs_hhinit ../../includes/TimeStepControl.hh

$(B)(parminit.o):../../includes/TimeStepControl.hh

$(B)(parminit.o):parminit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/parminit.c $(DB)/parminit.c 

$(B)(parmsanity.o):parmsanity.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/parmsanity.c $(DB)/parmsanity.c 

$(B)(set.o):set.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/set.c $(DB)/set.c 

#---------------------
# lint pass one target 
#---------------------
lint:boxid.ln create_temp_pa.ln free_temp_pa.ln memclr.ln memexp.ln ndset.ln      \
	  parm.ln parminit.ln parmsanity.ln set.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
boxid.ln:boxid.c ../../includes/irs.h ../../includes/irsparm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON boxid.c ***' >> $(LO)
	$$irs_lint boxid.c 2>&1 | tee -a $(LO)

create_temp_pa.ln:create_temp_pa.c ../../includes/irs.h ../../includes/irsparm.h  \
	  ../../includes/Hash.h ../../includes/irsrgst.h                          \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON create_temp_pa.c ***' >> $(LO)
	$$irs_lint create_temp_pa.c 2>&1 | tee -a $(LO)

free_temp_pa.ln:free_temp_pa.c ../../includes/irs.h ../../includes/irsparm.h      \
	  ../../includes/Hash.h ../../includes/irsrgst.h                          \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON free_temp_pa.c ***' >> $(LO)
	$$irs_lint free_temp_pa.c 2>&1 | tee -a $(LO)

memclr.ln:memclr.c ../../includes/irs.h ../../includes/irsblk.h                   \
	  ../../includes/irscom.h ../../includes/irsctl.h                         \
	  ../../includes/irsedits.h ../../includes/irsobjects.h                   \
	  ../../includes/irsparm.h ../../includes/irsrgst.h                       \
	  ../../includes/BiQuadradic.h ../../includes/Command.h                   \
	  ../../includes/Conditional.h ../../includes/CycleMesg.h                 \
	  ../../includes/FunctionTimer.h ../../includes/Gparm.h                   \
	  ../../includes/Hash.h ../../includes/NodeList.h                         \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/Region.h ../../includes/Spline.h ../../includes/Tracer.h \
	  ../../includes/TimePlot.h ../../includes/TimeStepControl.h              \
	  ../../includes/UserList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON memclr.c ***' >> $(LO)
	$$irs_lint memclr.c 2>&1 | tee -a $(LO)

memexp.ln:memexp.c ../../includes/irs.h ../../includes/irsreg.h                   \
	  ../../includes/irsblk.h ../../includes/irscom.h ../../includes/irsctl.h \
	  ../../includes/irsobjects.h ../../includes/irsparm.h                    \
	  ../../includes/irsrgst.h ../../includes/BiQuadradic.hh                  \
	  ../../includes/CycleMesg.h ../../includes/FreqMesg.h                    \
	  ../../includes/Gparm.h ../../includes/Hash.h                            \
	  ../../includes/ProblemArray.h ../../includes/Region.h                   \
	  ../../includes/Source.h ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON memexp.c ***' >> $(LO)
	$$irs_lint memexp.c 2>&1 | tee -a $(LO)

ndset.ln:ndset.c ../../includes/irs.h ../../includes/irsparm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ndset.c ***' >> $(LO)
	$$irs_lint ndset.c 2>&1 | tee -a $(LO)

parm.ln:parm.c ../../includes/irs.h ../../includes/irsparm.h                      \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON parm.c ***' >> $(LO)
	$$irs_lint parm.c 2>&1 | tee -a $(LO)

parminit.ln:parminit.c ../../includes/irs.hh ../../includes/irsbndry.h            \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/irslag.h ../../includes/irsctl.h ../../includes/irsdmp.h \
	  ../../includes/irseos.h ../../includes/irslag.hh                        \
	  ../../includes/irsparm.hh ../../includes/BlockMapping.h                 \
	  ../../includes/CycleMesg.h ../../includes/FunctionTimer.h               \
	  ../../includes/Hash.h ../../includes/Gparm.h                            \
	  ../../includes/VersionData.h ../../includes/TimePlot.h                  \
	  ../../includes/TimeStepControl.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON parminit.c ***' >> $(LO)
	$$irs_lint parminit.c 2>&1 | tee -a $(LO)

parmsanity.ln:parmsanity.c ../../includes/irs.h ../../includes/irsparm.h          \
	  ../../includes/irseos.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON parmsanity.c ***' >> $(LO)
	$$irs_lint parmsanity.c 2>&1 | tee -a $(LO)

set.ln:set.c ../../includes/irs.h ../../includes/irsparm.h                        \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON set.c ***' >> $(LO)
	$$irs_lint set.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/boxid.inst.i $(PREDIR)/create_temp_pa.inst.i                 \
	  $(PREDIR)/free_temp_pa.inst.i $(PREDIR)/memclr.inst.i                   \
	  $(PREDIR)/memexp.inst.i $(PREDIR)/ndset.inst.i $(PREDIR)/parm.inst.i    \
	  $(PREDIR)/parminit.inst.i $(PREDIR)/parmsanity.inst.i                   \
	  $(PREDIR)/set.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/boxid.inst.i:boxid.c ../../includes/irs.h ../../includes/irsparm.h
	@rm -f boxid.i
	$$irs_pre boxid.c >> boxid.i
	@mv -f boxid.i $(PREDIR)/boxid.inst.i

$(PREDIR)/create_temp_pa.inst.i:create_temp_pa.c ../../includes/irs.h             \
	  ../../includes/irsparm.h ../../includes/Hash.h ../../includes/irsrgst.h \
	  ../../includes/ProblemArray.h
	@rm -f create_temp_pa.i
	$$irs_pre create_temp_pa.c >> create_temp_pa.i
	@mv -f create_temp_pa.i $(PREDIR)/create_temp_pa.inst.i

$(PREDIR)/free_temp_pa.inst.i:free_temp_pa.c ../../includes/irs.h                 \
	  ../../includes/irsparm.h ../../includes/Hash.h ../../includes/irsrgst.h \
	  ../../includes/ProblemArray.h
	@rm -f free_temp_pa.i
	$$irs_pre free_temp_pa.c >> free_temp_pa.i
	@mv -f free_temp_pa.i $(PREDIR)/free_temp_pa.inst.i

$(PREDIR)/memclr.inst.i:memclr.c ../../includes/irs.h ../../includes/irsblk.h     \
	  ../../includes/irscom.h ../../includes/irsctl.h                         \
	  ../../includes/irsedits.h ../../includes/irsobjects.h                   \
	  ../../includes/irsparm.h ../../includes/irsrgst.h                       \
	  ../../includes/BiQuadradic.h ../../includes/Command.h                   \
	  ../../includes/Conditional.h ../../includes/CycleMesg.h                 \
	  ../../includes/FunctionTimer.h ../../includes/Gparm.h                   \
	  ../../includes/Hash.h ../../includes/NodeList.h                         \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/Region.h ../../includes/Spline.h ../../includes/Tracer.h \
	  ../../includes/TimePlot.h ../../includes/TimeStepControl.h              \
	  ../../includes/UserList.h
	@rm -f memclr.i
	$$irs_pre memclr.c >> memclr.i
	@mv -f memclr.i $(PREDIR)/memclr.inst.i

$(PREDIR)/memexp.inst.i:memexp.c ../../includes/irs.h ../../includes/irsreg.h     \
	  ../../includes/irsblk.h ../../includes/irscom.h ../../includes/irsctl.h \
	  ../../includes/irsobjects.h ../../includes/irsparm.h                    \
	  ../../includes/irsrgst.h ../../includes/BiQuadradic.hh                  \
	  ../../includes/CycleMesg.h ../../includes/FreqMesg.h                    \
	  ../../includes/Gparm.h ../../includes/Hash.h                            \
	  ../../includes/ProblemArray.h ../../includes/Region.h                   \
	  ../../includes/Source.h ../../includes/TimePlot.h
	@rm -f memexp.i
	$$irs_pre memexp.c >> memexp.i
	@mv -f memexp.i $(PREDIR)/memexp.inst.i

$(PREDIR)/ndset.inst.i:ndset.c ../../includes/irs.h ../../includes/irsparm.h
	@rm -f ndset.i
	$$irs_pre ndset.c >> ndset.i
	@mv -f ndset.i $(PREDIR)/ndset.inst.i

$(PREDIR)/parm.inst.i:parm.c ../../includes/irs.h ../../includes/irsparm.h        \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f parm.i
	$$irs_pre parm.c >> parm.i
	@mv -f parm.i $(PREDIR)/parm.inst.i

$(PREDIR)/parminit.inst.i:parminit.c ../../includes/irs.hh                        \
	  ../../includes/irsbndry.h ../../includes/irsreg.h                       \
	  ../../includes/irsrgst.h ../../includes/irslag.h                        \
	  ../../includes/irsctl.h ../../includes/irsdmp.h ../../includes/irseos.h \
	  ../../includes/irslag.hh ../../includes/irsparm.hh                      \
	  ../../includes/BlockMapping.h ../../includes/CycleMesg.h                \
	  ../../includes/FunctionTimer.h ../../includes/Hash.h                    \
	  ../../includes/Gparm.h ../../includes/VersionData.h                     \
	  ../../includes/TimePlot.h ../../includes/TimeStepControl.hh
	@rm -f parminit.i
	$$irs_pre parminit.c >> parminit.i
	@mv -f parminit.i $(PREDIR)/parminit.inst.i

$(PREDIR)/parmsanity.inst.i:parmsanity.c ../../includes/irs.h                     \
	  ../../includes/irsparm.h ../../includes/irseos.h
	@rm -f parmsanity.i
	$$irs_pre parmsanity.c >> parmsanity.i
	@mv -f parmsanity.i $(PREDIR)/parmsanity.inst.i

$(PREDIR)/set.inst.i:set.c ../../includes/irs.h ../../includes/irsparm.h          \
	  ../../includes/irsrgst.h
	@rm -f set.i
	$$irs_pre set.c >> set.i
	@mv -f set.i $(PREDIR)/set.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libparm_inst

libparm_inst:$(BI)(boxid.inst.o) $(BI)(create_temp_pa.inst.o)                     \
	  $(BI)(free_temp_pa.inst.o) $(BI)(memclr.inst.o) $(BI)(memexp.inst.o)    \
	  $(BI)(ndset.inst.o) $(BI)(parm.inst.o) $(BI)(parminit.inst.o)           \
	  $(BI)(parmsanity.inst.o) $(BI)(set.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libparm_inst.a $(B); \
		ln -sf libparm_inst.a $(B)); \
	  fi
	  @echo 'libparm_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(boxid.inst.o):$(INSTDIR)/boxid.inst.i
	$$irs_post $(INSTDIR)/boxid.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/boxid.inst.i $(DB)/boxid.c 

$(BI)(create_temp_pa.inst.o):$(INSTDIR)/create_temp_pa.inst.i
	$$irs_post $(INSTDIR)/create_temp_pa.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/create_temp_pa.inst.i $(DB)/create_temp_pa.c 

$(BI)(free_temp_pa.inst.o):$(INSTDIR)/free_temp_pa.inst.i
	$$irs_post $(INSTDIR)/free_temp_pa.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/free_temp_pa.inst.i $(DB)/free_temp_pa.c 

$(BI)(memclr.inst.o):$(INSTDIR)/memclr.inst.i
	$$irs_post $(INSTDIR)/memclr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/memclr.inst.i $(DB)/memclr.c 

$(BI)(memexp.inst.o):$(INSTDIR)/memexp.inst.i
	$$irs_post $(INSTDIR)/memexp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/memexp.inst.i $(DB)/memexp.c 

$(BI)(ndset.inst.o):$(INSTDIR)/ndset.inst.i
	$$irs_post $(INSTDIR)/ndset.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ndset.inst.i $(DB)/ndset.c 

$(BI)(parm.inst.o):$(INSTDIR)/parm.inst.i
	$$irs_post $(INSTDIR)/parm.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/parm.inst.i $(DB)/parm.c 

$(BI)(parminit.inst.o):$(INSTDIR)/parminit.inst.i
	$$irs_post $(INSTDIR)/parminit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/parminit.inst.i $(DB)/parminit.c 

$(BI)(parmsanity.inst.o):$(INSTDIR)/parmsanity.inst.i
	$$irs_post $(INSTDIR)/parmsanity.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/parmsanity.inst.i $(DB)/parmsanity.c 

$(BI)(set.inst.o):$(INSTDIR)/set.inst.i
	$$irs_post $(INSTDIR)/set.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/set.inst.i $(DB)/set.c 

DEP_SRCS = \
	boxid.c create_temp_pa.c free_temp_pa.c memclr.c memexp.c ndset.c parm.c  \
	parminit.c parmsanity.c set.c  

depend:
	@cp -f Makefile.parm Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

