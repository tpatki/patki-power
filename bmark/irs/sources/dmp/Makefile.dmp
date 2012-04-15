
################################################################################
#
# Makefile for irs library dmp
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
B = ../$(LIB_DIR)/libdmp.a
BI = ../$(LIB_DIR)/libdmp_inst.a

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
SRCDIR = ../sources/dmp

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libdmp:$(B)(Restart.o) $(B)(conddmp.o) $(B)(condgdmp.o) $(B)(dmpattr.o)           \
	  $(B)(getdmplst.o) $(B)(openpdmp.o) $(B)(rdmaterial.o) $(B)(rdmeshvar.o) \
	  $(B)(rdparms.o) $(B)(rdsilomesh.o) $(B)(rdspecies.o) $(B)(rgfxstate.o)  \
	  $(B)(rootfile.o) $(B)(rwgdmp.o) $(B)(set_silo_option.o) $(B)(wgdmp.o)   \
	  $(B)(wgfxstate.o) $(B)(wtmaterial.o) $(B)(wtmeshvar.o) $(B)(wtparms.o)  \
	  $(B)(wtsilomesh.o) $(B)(wtspecies.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'dmp library current'

# creation deps
#---------------
$(B)(Restart.o):Restart.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Restart.c $(DB)/Restart.c 

../../includes/irsdmp.hh:../../includes/irsdmp.h
	cp ../../includes/irsdmp.h ../../includes/irsdmp.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irsdmp.hh
	irs_hhinit ../../includes/irsdmp.hh

$(B)(conddmp.o):../../includes/irsdmp.hh

$(B)(conddmp.o):conddmp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/conddmp.c $(DB)/conddmp.c 

$(B)(condgdmp.o):condgdmp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/condgdmp.c $(DB)/condgdmp.c 

$(B)(dmpattr.o):dmpattr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/dmpattr.c $(DB)/dmpattr.c 

$(B)(getdmplst.o):getdmplst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getdmplst.c $(DB)/getdmplst.c 

$(B)(openpdmp.o):openpdmp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/openpdmp.c $(DB)/openpdmp.c 

$(B)(rdmaterial.o):rdmaterial.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdmaterial.c $(DB)/rdmaterial.c 

$(B)(rdmeshvar.o):rdmeshvar.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdmeshvar.c $(DB)/rdmeshvar.c 

$(B)(rdparms.o):rdparms.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdparms.c $(DB)/rdparms.c 

$(B)(rdsilomesh.o):rdsilomesh.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdsilomesh.c $(DB)/rdsilomesh.c 

$(B)(rdspecies.o):rdspecies.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdspecies.c $(DB)/rdspecies.c 

$(B)(rgfxstate.o):rgfxstate.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rgfxstate.c $(DB)/rgfxstate.c 

$(B)(rootfile.o):rootfile.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rootfile.c $(DB)/rootfile.c 

$(B)(rwgdmp.o):rwgdmp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rwgdmp.c $(DB)/rwgdmp.c 

$(B)(set_silo_option.o):set_silo_option.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/set_silo_option.c $(DB)/set_silo_option.c 

$(B)(wgdmp.o):wgdmp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/wgdmp.c $(DB)/wgdmp.c 

$(B)(wgfxstate.o):wgfxstate.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/wgfxstate.c $(DB)/wgfxstate.c 

$(B)(wtmaterial.o):wtmaterial.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/wtmaterial.c $(DB)/wtmaterial.c 

$(B)(wtmeshvar.o):wtmeshvar.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/wtmeshvar.c $(DB)/wtmeshvar.c 

$(B)(wtparms.o):wtparms.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/wtparms.c $(DB)/wtparms.c 

$(B)(wtsilomesh.o):wtsilomesh.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/wtsilomesh.c $(DB)/wtsilomesh.c 

$(B)(wtspecies.o):wtspecies.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/wtspecies.c $(DB)/wtspecies.c 

#---------------------
# lint pass one target 
#---------------------
lint:Restart.ln conddmp.ln condgdmp.ln dmpattr.ln getdmplst.ln openpdmp.ln        \
	  rdmaterial.ln rdmeshvar.ln rdparms.ln rdsilomesh.ln rdspecies.ln        \
	  rgfxstate.ln rootfile.ln rwgdmp.ln set_silo_option.ln wgdmp.ln          \
	  wgfxstate.ln wtmaterial.ln wtmeshvar.ln wtparms.ln wtsilomesh.ln        \
	  wtspecies.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
Restart.ln:Restart.c ../../includes/irs.h ../../includes/irslag.h                 \
	  ../../includes/irscom.h ../../includes/irsdmp.h                         \
	  ../../includes/irsedits.h ../../includes/irseos.h                       \
	  ../../includes/irsparm.h ../../includes/irsrgst.h                       \
	  ../../includes/irsreg.h ../../includes/BlockMapping.h                   \
	  ../../includes/Conditional.h ../../includes/Command.h                   \
	  ../../includes/CycleMesg.h ../../includes/FunctionTimer.h               \
	  ../../includes/FreqMesg.h ../../includes/Gparm.h ../../includes/Rgst.h  \
	  ../../includes/Hash.h ../../includes/NodeList.h                         \
	  ../../includes/ProblemArray.h ../../includes/Region.h                   \
	  ../../includes/Stringnam.h ../../includes/Spline.h                      \
	  ../../includes/TimePlot.h ../../includes/TimeStepControl.h              \
	  ../../includes/Tracer.h ../../includes/UserList.h                       \
	  ../../includes/VersionData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Restart.c ***' >> $(LO)
	$$irs_lint Restart.c 2>&1 | tee -a $(LO)

conddmp.ln:conddmp.c ../../includes/irs.h ../../includes/irsblk.h                 \
	  ../../includes/irscom.h ../../includes/irsdmp.hh                        \
	  ../../includes/irsrgst.h ../../includes/Hash.h                          \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON conddmp.c ***' >> $(LO)
	$$irs_lint conddmp.c 2>&1 | tee -a $(LO)

condgdmp.ln:condgdmp.c ../../includes/irs.h ../../includes/irsdmp.h               \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON condgdmp.c ***' >> $(LO)
	$$irs_lint condgdmp.c 2>&1 | tee -a $(LO)

dmpattr.ln:dmpattr.c ../../includes/irs.h ../../includes/irsdmp.h                 \
	  ../../includes/irsrgst.h ../../includes/ProblemArray.h                  \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON dmpattr.c ***' >> $(LO)
	$$irs_lint dmpattr.c 2>&1 | tee -a $(LO)

getdmplst.ln:getdmplst.c ../../includes/irs.h ../../includes/irscom.h             \
	  ../../includes/irsdmp.h ../../includes/irsgen.h ../../includes/irssrc.h \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getdmplst.c ***' >> $(LO)
	$$irs_lint getdmplst.c 2>&1 | tee -a $(LO)

openpdmp.ln:openpdmp.c ../../includes/irs.h ../../includes/irsdmp.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON openpdmp.c ***' >> $(LO)
	$$irs_lint openpdmp.c 2>&1 | tee -a $(LO)

rdmaterial.ln:rdmaterial.c ../../includes/irs.h ../../includes/irsdmp.h           \
	  ../../includes/irsreg.h ../../includes/Extents.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdmaterial.c ***' >> $(LO)
	$$irs_lint rdmaterial.c 2>&1 | tee -a $(LO)

rdmeshvar.ln:rdmeshvar.c ../../includes/irs.h ../../includes/irsdmp.h             \
	  ../../includes/Extents.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdmeshvar.c ***' >> $(LO)
	$$irs_lint rdmeshvar.c 2>&1 | tee -a $(LO)

rdparms.ln:rdparms.c ../../includes/irs.h ../../includes/irsdmp.h                 \
	  ../../includes/irsparm.h ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdparms.c ***' >> $(LO)
	$$irs_lint rdparms.c 2>&1 | tee -a $(LO)

rdsilomesh.ln:rdsilomesh.c ../../includes/irs.h ../../includes/irsdmp.h           \
	  ../../includes/Extents.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdsilomesh.c ***' >> $(LO)
	$$irs_lint rdsilomesh.c 2>&1 | tee -a $(LO)

rdspecies.ln:rdspecies.c ../../includes/irs.h ../../includes/irsdmp.h             \
	  ../../includes/Region.h ../../includes/Extents.h                        \
	  ../../includes/SpeciesFraction.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdspecies.c ***' >> $(LO)
	$$irs_lint rdspecies.c 2>&1 | tee -a $(LO)

rgfxstate.ln:rgfxstate.c ../../includes/irs.h ../../includes/irscom.h             \
	  ../../includes/irsdmp.h ../../includes/mach.h ../../includes/cgl.h      \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rgfxstate.c ***' >> $(LO)
	$$irs_lint rgfxstate.c 2>&1 | tee -a $(LO)

rootfile.ln:rootfile.c ../../includes/irs.h ../../includes/irsobjects.h           \
	  ../../includes/irsdmp.h ../../includes/irscom.h ../../includes/irsreg.h \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h            \
	  ../../includes/Region.h ../../includes/Rgst.h ../../includes/Tracer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rootfile.c ***' >> $(LO)
	$$irs_lint rootfile.c 2>&1 | tee -a $(LO)

rwgdmp.ln:rwgdmp.c ../../includes/irs.h ../../includes/irsdmp.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rwgdmp.c ***' >> $(LO)
	$$irs_lint rwgdmp.c 2>&1 | tee -a $(LO)

set_silo_option.ln:set_silo_option.c ../../includes/irs.h ../../includes/irsdmp.h \
	  ../../includes/BlockMapping.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON set_silo_option.c ***' >> $(LO)
	$$irs_lint set_silo_option.c 2>&1 | tee -a $(LO)

wgdmp.ln:wgdmp.c ../../includes/irs.h ../../includes/irsobjects.h                 \
	  ../../includes/irsdmp.h ../../includes/irsctl.h                         \
	  ../../includes/irsrgst.h ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON wgdmp.c ***' >> $(LO)
	$$irs_lint wgdmp.c 2>&1 | tee -a $(LO)

wgfxstate.ln:wgfxstate.c ../../includes/irs.h ../../includes/irsdmp.h             \
	  ../../includes/mach.h ../../includes/cgl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON wgfxstate.c ***' >> $(LO)
	$$irs_lint wgfxstate.c 2>&1 | tee -a $(LO)

wtmaterial.ln:wtmaterial.c ../../includes/irs.h ../../includes/irsreg.h           \
	  ../../includes/irsdmp.h ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON wtmaterial.c ***' >> $(LO)
	$$irs_lint wtmaterial.c 2>&1 | tee -a $(LO)

wtmeshvar.ln:wtmeshvar.c ../../includes/irs.h ../../includes/irsdmp.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON wtmeshvar.c ***' >> $(LO)
	$$irs_lint wtmeshvar.c 2>&1 | tee -a $(LO)

wtparms.ln:wtparms.c ../../includes/irs.h ../../includes/irsdmp.h                 \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON wtparms.c ***' >> $(LO)
	$$irs_lint wtparms.c 2>&1 | tee -a $(LO)

wtsilomesh.ln:wtsilomesh.c ../../includes/irs.h ../../includes/irsdmp.h           \
	  ../../includes/Extents.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON wtsilomesh.c ***' >> $(LO)
	$$irs_lint wtsilomesh.c 2>&1 | tee -a $(LO)

wtspecies.ln:wtspecies.c ../../includes/irs.h ../../includes/irsdmp.h             \
	  ../../includes/irsreg.h ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON wtspecies.c ***' >> $(LO)
	$$irs_lint wtspecies.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/Restart.inst.i $(PREDIR)/conddmp.inst.i                      \
	  $(PREDIR)/condgdmp.inst.i $(PREDIR)/dmpattr.inst.i                      \
	  $(PREDIR)/getdmplst.inst.i $(PREDIR)/openpdmp.inst.i                    \
	  $(PREDIR)/rdmaterial.inst.i $(PREDIR)/rdmeshvar.inst.i                  \
	  $(PREDIR)/rdparms.inst.i $(PREDIR)/rdsilomesh.inst.i                    \
	  $(PREDIR)/rdspecies.inst.i $(PREDIR)/rgfxstate.inst.i                   \
	  $(PREDIR)/rootfile.inst.i $(PREDIR)/rwgdmp.inst.i                       \
	  $(PREDIR)/set_silo_option.inst.i $(PREDIR)/wgdmp.inst.i                 \
	  $(PREDIR)/wgfxstate.inst.i $(PREDIR)/wtmaterial.inst.i                  \
	  $(PREDIR)/wtmeshvar.inst.i $(PREDIR)/wtparms.inst.i                     \
	  $(PREDIR)/wtsilomesh.inst.i $(PREDIR)/wtspecies.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/Restart.inst.i:Restart.c ../../includes/irs.h ../../includes/irslag.h   \
	  ../../includes/irscom.h ../../includes/irsdmp.h                         \
	  ../../includes/irsedits.h ../../includes/irseos.h                       \
	  ../../includes/irsparm.h ../../includes/irsrgst.h                       \
	  ../../includes/irsreg.h ../../includes/BlockMapping.h                   \
	  ../../includes/Conditional.h ../../includes/Command.h                   \
	  ../../includes/CycleMesg.h ../../includes/FunctionTimer.h               \
	  ../../includes/FreqMesg.h ../../includes/Gparm.h ../../includes/Rgst.h  \
	  ../../includes/Hash.h ../../includes/NodeList.h                         \
	  ../../includes/ProblemArray.h ../../includes/Region.h                   \
	  ../../includes/Stringnam.h ../../includes/Spline.h                      \
	  ../../includes/TimePlot.h ../../includes/TimeStepControl.h              \
	  ../../includes/Tracer.h ../../includes/UserList.h                       \
	  ../../includes/VersionData.h
	@rm -f Restart.i
	$$irs_pre Restart.c >> Restart.i
	@mv -f Restart.i $(PREDIR)/Restart.inst.i

$(PREDIR)/conddmp.inst.i:conddmp.c ../../includes/irs.h ../../includes/irsblk.h   \
	  ../../includes/irscom.h ../../includes/irsdmp.hh                        \
	  ../../includes/irsrgst.h ../../includes/Hash.h                          \
	  ../../includes/ProblemArray.h
	@rm -f conddmp.i
	$$irs_pre conddmp.c >> conddmp.i
	@mv -f conddmp.i $(PREDIR)/conddmp.inst.i

$(PREDIR)/condgdmp.inst.i:condgdmp.c ../../includes/irs.h ../../includes/irsdmp.h \
	  ../../includes/irsrgst.h
	@rm -f condgdmp.i
	$$irs_pre condgdmp.c >> condgdmp.i
	@mv -f condgdmp.i $(PREDIR)/condgdmp.inst.i

$(PREDIR)/dmpattr.inst.i:dmpattr.c ../../includes/irs.h ../../includes/irsdmp.h   \
	  ../../includes/irsrgst.h ../../includes/ProblemArray.h                  \
	  ../../includes/Rgst.h
	@rm -f dmpattr.i
	$$irs_pre dmpattr.c >> dmpattr.i
	@mv -f dmpattr.i $(PREDIR)/dmpattr.inst.i

$(PREDIR)/getdmplst.inst.i:getdmplst.c ../../includes/irs.h                       \
	  ../../includes/irscom.h ../../includes/irsdmp.h ../../includes/irsgen.h \
	  ../../includes/irssrc.h ../../includes/FunctionTimer.h
	@rm -f getdmplst.i
	$$irs_pre getdmplst.c >> getdmplst.i
	@mv -f getdmplst.i $(PREDIR)/getdmplst.inst.i

$(PREDIR)/openpdmp.inst.i:openpdmp.c ../../includes/irs.h                         \
	  ../../includes/irsdmp.h
	@rm -f openpdmp.i
	$$irs_pre openpdmp.c >> openpdmp.i
	@mv -f openpdmp.i $(PREDIR)/openpdmp.inst.i

$(PREDIR)/rdmaterial.inst.i:rdmaterial.c ../../includes/irs.h                     \
	  ../../includes/irsdmp.h ../../includes/irsreg.h                         \
	  ../../includes/Extents.h
	@rm -f rdmaterial.i
	$$irs_pre rdmaterial.c >> rdmaterial.i
	@mv -f rdmaterial.i $(PREDIR)/rdmaterial.inst.i

$(PREDIR)/rdmeshvar.inst.i:rdmeshvar.c ../../includes/irs.h                       \
	  ../../includes/irsdmp.h ../../includes/Extents.h
	@rm -f rdmeshvar.i
	$$irs_pre rdmeshvar.c >> rdmeshvar.i
	@mv -f rdmeshvar.i $(PREDIR)/rdmeshvar.inst.i

$(PREDIR)/rdparms.inst.i:rdparms.c ../../includes/irs.h ../../includes/irsdmp.h   \
	  ../../includes/irsparm.h ../../includes/irsrgst.h
	@rm -f rdparms.i
	$$irs_pre rdparms.c >> rdparms.i
	@mv -f rdparms.i $(PREDIR)/rdparms.inst.i

$(PREDIR)/rdsilomesh.inst.i:rdsilomesh.c ../../includes/irs.h                     \
	  ../../includes/irsdmp.h ../../includes/Extents.h
	@rm -f rdsilomesh.i
	$$irs_pre rdsilomesh.c >> rdsilomesh.i
	@mv -f rdsilomesh.i $(PREDIR)/rdsilomesh.inst.i

$(PREDIR)/rdspecies.inst.i:rdspecies.c ../../includes/irs.h                       \
	  ../../includes/irsdmp.h ../../includes/Region.h                         \
	  ../../includes/Extents.h ../../includes/SpeciesFraction.h
	@rm -f rdspecies.i
	$$irs_pre rdspecies.c >> rdspecies.i
	@mv -f rdspecies.i $(PREDIR)/rdspecies.inst.i

$(PREDIR)/rgfxstate.inst.i:rgfxstate.c ../../includes/irs.h                       \
	  ../../includes/irscom.h ../../includes/irsdmp.h ../../includes/mach.h   \
	  ../../includes/cgl.h ../../includes/FunctionTimer.h
	@rm -f rgfxstate.i
	$$irs_pre rgfxstate.c >> rgfxstate.i
	@mv -f rgfxstate.i $(PREDIR)/rgfxstate.inst.i

$(PREDIR)/rootfile.inst.i:rootfile.c ../../includes/irs.h                         \
	  ../../includes/irsobjects.h ../../includes/irsdmp.h                     \
	  ../../includes/irscom.h ../../includes/irsreg.h                         \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h            \
	  ../../includes/Region.h ../../includes/Rgst.h ../../includes/Tracer.h
	@rm -f rootfile.i
	$$irs_pre rootfile.c >> rootfile.i
	@mv -f rootfile.i $(PREDIR)/rootfile.inst.i

$(PREDIR)/rwgdmp.inst.i:rwgdmp.c ../../includes/irs.h ../../includes/irsdmp.h
	@rm -f rwgdmp.i
	$$irs_pre rwgdmp.c >> rwgdmp.i
	@mv -f rwgdmp.i $(PREDIR)/rwgdmp.inst.i

$(PREDIR)/set_silo_option.inst.i:set_silo_option.c ../../includes/irs.h           \
	  ../../includes/irsdmp.h ../../includes/BlockMapping.h
	@rm -f set_silo_option.i
	$$irs_pre set_silo_option.c >> set_silo_option.i
	@mv -f set_silo_option.i $(PREDIR)/set_silo_option.inst.i

$(PREDIR)/wgdmp.inst.i:wgdmp.c ../../includes/irs.h ../../includes/irsobjects.h   \
	  ../../includes/irsdmp.h ../../includes/irsctl.h                         \
	  ../../includes/irsrgst.h ../../includes/ProblemArray.h
	@rm -f wgdmp.i
	$$irs_pre wgdmp.c >> wgdmp.i
	@mv -f wgdmp.i $(PREDIR)/wgdmp.inst.i

$(PREDIR)/wgfxstate.inst.i:wgfxstate.c ../../includes/irs.h                       \
	  ../../includes/irsdmp.h ../../includes/mach.h ../../includes/cgl.h
	@rm -f wgfxstate.i
	$$irs_pre wgfxstate.c >> wgfxstate.i
	@mv -f wgfxstate.i $(PREDIR)/wgfxstate.inst.i

$(PREDIR)/wtmaterial.inst.i:wtmaterial.c ../../includes/irs.h                     \
	  ../../includes/irsreg.h ../../includes/irsdmp.h                         \
	  ../../includes/Region.h
	@rm -f wtmaterial.i
	$$irs_pre wtmaterial.c >> wtmaterial.i
	@mv -f wtmaterial.i $(PREDIR)/wtmaterial.inst.i

$(PREDIR)/wtmeshvar.inst.i:wtmeshvar.c ../../includes/irs.h                       \
	  ../../includes/irsdmp.h
	@rm -f wtmeshvar.i
	$$irs_pre wtmeshvar.c >> wtmeshvar.i
	@mv -f wtmeshvar.i $(PREDIR)/wtmeshvar.inst.i

$(PREDIR)/wtparms.inst.i:wtparms.c ../../includes/irs.h ../../includes/irsdmp.h   \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	@rm -f wtparms.i
	$$irs_pre wtparms.c >> wtparms.i
	@mv -f wtparms.i $(PREDIR)/wtparms.inst.i

$(PREDIR)/wtsilomesh.inst.i:wtsilomesh.c ../../includes/irs.h                     \
	  ../../includes/irsdmp.h ../../includes/Extents.h
	@rm -f wtsilomesh.i
	$$irs_pre wtsilomesh.c >> wtsilomesh.i
	@mv -f wtsilomesh.i $(PREDIR)/wtsilomesh.inst.i

$(PREDIR)/wtspecies.inst.i:wtspecies.c ../../includes/irs.h                       \
	  ../../includes/irsdmp.h ../../includes/irsreg.h                         \
	  ../../includes/Region.h
	@rm -f wtspecies.i
	$$irs_pre wtspecies.c >> wtspecies.i
	@mv -f wtspecies.i $(PREDIR)/wtspecies.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libdmp_inst

libdmp_inst:$(BI)(Restart.inst.o) $(BI)(conddmp.inst.o) $(BI)(condgdmp.inst.o)    \
	  $(BI)(dmpattr.inst.o) $(BI)(getdmplst.inst.o) $(BI)(openpdmp.inst.o)    \
	  $(BI)(rdmaterial.inst.o) $(BI)(rdmeshvar.inst.o) $(BI)(rdparms.inst.o)  \
	  $(BI)(rdsilomesh.inst.o) $(BI)(rdspecies.inst.o)                        \
	  $(BI)(rgfxstate.inst.o) $(BI)(rootfile.inst.o) $(BI)(rwgdmp.inst.o)     \
	  $(BI)(set_silo_option.inst.o) $(BI)(wgdmp.inst.o)                       \
	  $(BI)(wgfxstate.inst.o) $(BI)(wtmaterial.inst.o)                        \
	  $(BI)(wtmeshvar.inst.o) $(BI)(wtparms.inst.o) $(BI)(wtsilomesh.inst.o)  \
	  $(BI)(wtspecies.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libdmp_inst.a $(B); \
		ln -sf libdmp_inst.a $(B)); \
	  fi
	  @echo 'libdmp_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(Restart.inst.o):$(INSTDIR)/Restart.inst.i
	$$irs_post $(INSTDIR)/Restart.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Restart.inst.i $(DB)/Restart.c 

$(BI)(conddmp.inst.o):$(INSTDIR)/conddmp.inst.i
	$$irs_post $(INSTDIR)/conddmp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/conddmp.inst.i $(DB)/conddmp.c 

$(BI)(condgdmp.inst.o):$(INSTDIR)/condgdmp.inst.i
	$$irs_post $(INSTDIR)/condgdmp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/condgdmp.inst.i $(DB)/condgdmp.c 

$(BI)(dmpattr.inst.o):$(INSTDIR)/dmpattr.inst.i
	$$irs_post $(INSTDIR)/dmpattr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/dmpattr.inst.i $(DB)/dmpattr.c 

$(BI)(getdmplst.inst.o):$(INSTDIR)/getdmplst.inst.i
	$$irs_post $(INSTDIR)/getdmplst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getdmplst.inst.i $(DB)/getdmplst.c 

$(BI)(openpdmp.inst.o):$(INSTDIR)/openpdmp.inst.i
	$$irs_post $(INSTDIR)/openpdmp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/openpdmp.inst.i $(DB)/openpdmp.c 

$(BI)(rdmaterial.inst.o):$(INSTDIR)/rdmaterial.inst.i
	$$irs_post $(INSTDIR)/rdmaterial.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdmaterial.inst.i $(DB)/rdmaterial.c 

$(BI)(rdmeshvar.inst.o):$(INSTDIR)/rdmeshvar.inst.i
	$$irs_post $(INSTDIR)/rdmeshvar.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdmeshvar.inst.i $(DB)/rdmeshvar.c 

$(BI)(rdparms.inst.o):$(INSTDIR)/rdparms.inst.i
	$$irs_post $(INSTDIR)/rdparms.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdparms.inst.i $(DB)/rdparms.c 

$(BI)(rdsilomesh.inst.o):$(INSTDIR)/rdsilomesh.inst.i
	$$irs_post $(INSTDIR)/rdsilomesh.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdsilomesh.inst.i $(DB)/rdsilomesh.c 

$(BI)(rdspecies.inst.o):$(INSTDIR)/rdspecies.inst.i
	$$irs_post $(INSTDIR)/rdspecies.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdspecies.inst.i $(DB)/rdspecies.c 

$(BI)(rgfxstate.inst.o):$(INSTDIR)/rgfxstate.inst.i
	$$irs_post $(INSTDIR)/rgfxstate.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rgfxstate.inst.i $(DB)/rgfxstate.c 

$(BI)(rootfile.inst.o):$(INSTDIR)/rootfile.inst.i
	$$irs_post $(INSTDIR)/rootfile.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rootfile.inst.i $(DB)/rootfile.c 

$(BI)(rwgdmp.inst.o):$(INSTDIR)/rwgdmp.inst.i
	$$irs_post $(INSTDIR)/rwgdmp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rwgdmp.inst.i $(DB)/rwgdmp.c 

$(BI)(set_silo_option.inst.o):$(INSTDIR)/set_silo_option.inst.i
	$$irs_post $(INSTDIR)/set_silo_option.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/set_silo_option.inst.i $(DB)/set_silo_option.c 

$(BI)(wgdmp.inst.o):$(INSTDIR)/wgdmp.inst.i
	$$irs_post $(INSTDIR)/wgdmp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/wgdmp.inst.i $(DB)/wgdmp.c 

$(BI)(wgfxstate.inst.o):$(INSTDIR)/wgfxstate.inst.i
	$$irs_post $(INSTDIR)/wgfxstate.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/wgfxstate.inst.i $(DB)/wgfxstate.c 

$(BI)(wtmaterial.inst.o):$(INSTDIR)/wtmaterial.inst.i
	$$irs_post $(INSTDIR)/wtmaterial.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/wtmaterial.inst.i $(DB)/wtmaterial.c 

$(BI)(wtmeshvar.inst.o):$(INSTDIR)/wtmeshvar.inst.i
	$$irs_post $(INSTDIR)/wtmeshvar.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/wtmeshvar.inst.i $(DB)/wtmeshvar.c 

$(BI)(wtparms.inst.o):$(INSTDIR)/wtparms.inst.i
	$$irs_post $(INSTDIR)/wtparms.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/wtparms.inst.i $(DB)/wtparms.c 

$(BI)(wtsilomesh.inst.o):$(INSTDIR)/wtsilomesh.inst.i
	$$irs_post $(INSTDIR)/wtsilomesh.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/wtsilomesh.inst.i $(DB)/wtsilomesh.c 

$(BI)(wtspecies.inst.o):$(INSTDIR)/wtspecies.inst.i
	$$irs_post $(INSTDIR)/wtspecies.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/wtspecies.inst.i $(DB)/wtspecies.c 

DEP_SRCS = \
	Restart.c conddmp.c condgdmp.c dmpattr.c getdmplst.c openpdmp.c rdmaterial.c  \
	rdmeshvar.c rdparms.c rdsilomesh.c rdspecies.c rgfxstate.c rootfile.c  \
	rwgdmp.c set_silo_option.c wgdmp.c wgfxstate.c wtmaterial.c wtmeshvar.c  \
	wtparms.c wtsilomesh.c wtspecies.c  

depend:
	@cp -f Makefile.dmp Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

