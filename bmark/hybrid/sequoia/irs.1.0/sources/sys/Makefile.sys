
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

