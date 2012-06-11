
################################################################################
#
# Makefile for irs library objects
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
B = ../$(LIB_DIR)/libobjects.a
BI = ../$(LIB_DIR)/libobjects_inst.a

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
SRCDIR = ../sources/objects

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libobjects:$(B)(AEStackElm.o) $(B)(AttrArray.o) $(B)(Boundary.o)                  \
	  $(B)(BoundaryCondition.o) $(B)(Conditional.o) $(B)(Database.o)          \
	  $(B)(Domain.o) $(B)(EosGroup.o) $(B)(FunctionTimer.o)                   \
	  $(B)(GlobalArrays.o) $(B)(NodeList.o) $(B)(NodeWindow.o)                \
	  $(B)(ObjectName.o) $(B)(OpacityGroup.o) $(B)(ProblemArray.o)            \
	  $(B)(RGST_Object.o) $(B)(Region.o) $(B)(Source.o) $(B)(SourceNew.o)     \
	  $(B)(Species.o) $(B)(Spline.o) $(B)(SubMesh.o) $(B)(TimePlot.o)         \
	  $(B)(TimePlotCurve.o) $(B)(TimeStepControl.o) $(B)(Transform.o)         \
	  $(B)(UserList.o) $(B)(VersionData.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'objects library current'

# creation deps
#---------------
../../includes/AEStackElm.hh:../../includes/AEStackElm.h
	cp ../../includes/AEStackElm.h ../../includes/AEStackElm.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/AEStackElm.hh
	irs_hhinit ../../includes/AEStackElm.hh

$(B)(AEStackElm.o):../../includes/AEStackElm.hh

$(B)(AEStackElm.o):AEStackElm.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/AEStackElm.c $(DB)/AEStackElm.c 

$(B)(AttrArray.o):AttrArray.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/AttrArray.c $(DB)/AttrArray.c 

$(B)(Boundary.o):Boundary.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Boundary.c $(DB)/Boundary.c 

$(B)(BoundaryCondition.o):BoundaryCondition.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/BoundaryCondition.c $(DB)/BoundaryCondition.c 

$(B)(Conditional.o):Conditional.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Conditional.c $(DB)/Conditional.c 

$(B)(Database.o):Database.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Database.c $(DB)/Database.c 

$(B)(Domain.o):Domain.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Domain.c $(DB)/Domain.c 

$(B)(EosGroup.o):EosGroup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/EosGroup.c $(DB)/EosGroup.c 

$(B)(FunctionTimer.o):FunctionTimer.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FunctionTimer.c $(DB)/FunctionTimer.c 

$(B)(GlobalArrays.o):GlobalArrays.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/GlobalArrays.c $(DB)/GlobalArrays.c 

../../includes/NodeList.hh:../../includes/NodeList.h
	cp ../../includes/NodeList.h ../../includes/NodeList.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/NodeList.hh
	irs_hhinit ../../includes/NodeList.hh

$(B)(NodeList.o):../../includes/NodeList.hh

$(B)(NodeList.o):NodeList.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/NodeList.c $(DB)/NodeList.c 

$(B)(NodeWindow.o):NodeWindow.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/NodeWindow.c $(DB)/NodeWindow.c 

$(B)(ObjectName.o):ObjectName.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ObjectName.c $(DB)/ObjectName.c 

$(B)(OpacityGroup.o):OpacityGroup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/OpacityGroup.c $(DB)/OpacityGroup.c 

$(B)(ProblemArray.o):ProblemArray.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ProblemArray.c $(DB)/ProblemArray.c 

$(B)(RGST_Object.o):RGST_Object.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/RGST_Object.c $(DB)/RGST_Object.c 

../../includes/Region.hh:../../includes/Region.h
	cp ../../includes/Region.h ../../includes/Region.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/Region.hh
	irs_hhinit ../../includes/Region.hh

$(B)(Region.o):../../includes/Region.hh

$(B)(Region.o):Region.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Region.c $(DB)/Region.c 

../../includes/Source.hh:../../includes/Source.h
	cp ../../includes/Source.h ../../includes/Source.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/Source.hh
	irs_hhinit ../../includes/Source.hh

$(B)(Source.o):../../includes/Source.hh

$(B)(Source.o):Source.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Source.c $(DB)/Source.c 

$(B)(SourceNew.o):SourceNew.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/SourceNew.c $(DB)/SourceNew.c 

$(B)(Species.o):Species.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Species.c $(DB)/Species.c 

$(B)(Spline.o):Spline.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Spline.c $(DB)/Spline.c 

$(B)(SubMesh.o):SubMesh.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/SubMesh.c $(DB)/SubMesh.c 

$(B)(TimePlot.o):TimePlot.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/TimePlot.c $(DB)/TimePlot.c 

$(B)(TimePlotCurve.o):TimePlotCurve.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/TimePlotCurve.c $(DB)/TimePlotCurve.c 

$(B)(TimeStepControl.o):TimeStepControl.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/TimeStepControl.c $(DB)/TimeStepControl.c 

$(B)(Transform.o):Transform.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Transform.c $(DB)/Transform.c 

$(B)(UserList.o):UserList.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/UserList.c $(DB)/UserList.c 

$(B)(VersionData.o):VersionData.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/VersionData.c $(DB)/VersionData.c 

#---------------------
# lint pass one target 
#---------------------
lint:AEStackElm.ln AttrArray.ln Boundary.ln BoundaryCondition.ln Conditional.ln   \
	  Database.ln Domain.ln EosGroup.ln FunctionTimer.ln GlobalArrays.ln      \
	  NodeList.ln NodeWindow.ln ObjectName.ln OpacityGroup.ln ProblemArray.ln \
	  RGST_Object.ln Region.ln Source.ln SourceNew.ln Species.ln Spline.ln    \
	  SubMesh.ln TimePlot.ln TimePlotCurve.ln TimeStepControl.ln Transform.ln \
	  UserList.ln VersionData.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
AEStackElm.ln:AEStackElm.c ../../includes/irs.h ../../includes/irsctl.h           \
	  ../../includes/irsrgst.h ../../includes/AEStackElm.hh                   \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON AEStackElm.c ***' >> $(LO)
	$$irs_lint AEStackElm.c 2>&1 | tee -a $(LO)

AttrArray.ln:AttrArray.c ../../includes/irs.h ../../includes/irsctl.h             \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON AttrArray.c ***' >> $(LO)
	$$irs_lint AttrArray.c 2>&1 | tee -a $(LO)

Boundary.ln:Boundary.c ../../includes/irs.h ../../includes/irsctl.h               \
	  ../../includes/irsrgst.h ../../includes/Boundary.h                      \
	  ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Boundary.c ***' >> $(LO)
	$$irs_lint Boundary.c 2>&1 | tee -a $(LO)

BoundaryCondition.ln:BoundaryCondition.c ../../includes/irs.h                     \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/BoundaryCondition.h ../../includes/Command.h             \
	  ../../includes/Hash.h ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON BoundaryCondition.c ***' >> $(LO)
	$$irs_lint BoundaryCondition.c 2>&1 | tee -a $(LO)

Conditional.ln:Conditional.c ../../includes/irs.h ../../includes/irsctl.h         \
	  ../../includes/irsrgst.h ../../includes/Conditional.h                   \
	  ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Conditional.c ***' >> $(LO)
	$$irs_lint Conditional.c 2>&1 | tee -a $(LO)

Database.ln:Database.c ../../includes/irs.h ../../includes/irsctl.h               \
	  ../../includes/irsrgst.h ../../includes/Command.h                       \
	  ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Database.c ***' >> $(LO)
	$$irs_lint Database.c 2>&1 | tee -a $(LO)

Domain.ln:Domain.c ../../includes/irs.h ../../includes/irsblk.h                   \
	  ../../includes/irsgen.h ../../includes/irsbndry.h                       \
	  ../../includes/irsctl.h ../../includes/irsdmp.h                         \
	  ../../includes/irsobjects.h ../../includes/irsrgst.h                    \
	  ../../includes/BlockMapping.h ../../includes/Command.h                  \
	  ../../includes/Domain.h ../../includes/Extents.h                        \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h            \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Domain.c ***' >> $(LO)
	$$irs_lint Domain.c 2>&1 | tee -a $(LO)

EosGroup.ln:EosGroup.c ../../includes/irs.h ../../includes/irsctl.h               \
	  ../../includes/irsrgst.h ../../includes/Command.h                       \
	  ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON EosGroup.c ***' >> $(LO)
	$$irs_lint EosGroup.c 2>&1 | tee -a $(LO)

FunctionTimer.ln:FunctionTimer.c ../../includes/irs.h ../../includes/irssys.h     \
	  ../../includes/irscom.h ../../includes/irsctl.h                         \
	  ../../includes/irsrgst.h ../../includes/irsobjects.h                    \
	  ../../includes/BlockMapping.h ../../includes/Command.h                  \
	  ../../includes/FunctionTimer.h ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FunctionTimer.c ***' >> $(LO)
	$$irs_lint FunctionTimer.c 2>&1 | tee -a $(LO)

GlobalArrays.ln:GlobalArrays.c ../../includes/irs.h ../../includes/irsobjects.h   \
	  ../../includes/irsrgst.h ../../includes/irsreg.h                        \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON GlobalArrays.c ***' >> $(LO)
	$$irs_lint GlobalArrays.c 2>&1 | tee -a $(LO)

NodeList.ln:NodeList.c ../../includes/irs.h ../../includes/irsrgst.h              \
	  ../../includes/irsgen.h ../../includes/irsctl.h                         \
	  ../../includes/NodeList.hh ../../includes/ProblemArray.h                \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON NodeList.c ***' >> $(LO)
	$$irs_lint NodeList.c 2>&1 | tee -a $(LO)

NodeWindow.ln:NodeWindow.c ../../includes/irs.h ../../includes/irsgen.h           \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/Tracer.h ../../includes/NodeList.h ../../includes/Hash.h \
	  ../../includes/ProblemArray.h ../../includes/UserList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON NodeWindow.c ***' >> $(LO)
	$$irs_lint NodeWindow.c 2>&1 | tee -a $(LO)

ObjectName.ln:ObjectName.c ../../includes/irs.h ../../includes/irsobjects.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ObjectName.c ***' >> $(LO)
	$$irs_lint ObjectName.c 2>&1 | tee -a $(LO)

OpacityGroup.ln:OpacityGroup.c ../../includes/irs.h ../../includes/irsctl.h       \
	  ../../includes/irsrgst.h ../../includes/Command.h                       \
	  ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON OpacityGroup.c ***' >> $(LO)
	$$irs_lint OpacityGroup.c 2>&1 | tee -a $(LO)

ProblemArray.ln:ProblemArray.c ../../includes/irs.h ../../includes/irsrgst.h      \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ProblemArray.c ***' >> $(LO)
	$$irs_lint ProblemArray.c 2>&1 | tee -a $(LO)

RGST_Object.ln:RGST_Object.c ../../includes/irs.h ../../includes/irsctl.h         \
	  ../../includes/irsrgst.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON RGST_Object.c ***' >> $(LO)
	$$irs_lint RGST_Object.c 2>&1 | tee -a $(LO)

Region.ln:Region.c ../../includes/irs.h ../../includes/irsctl.h                   \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/Command.h ../../includes/Hash.h ../../includes/Region.hh \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Region.c ***' >> $(LO)
	$$irs_lint Region.c 2>&1 | tee -a $(LO)

Source.ln:Source.c ../../includes/irs.h ../../includes/irsctl.h                   \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Command.h ../../includes/Extents.h                       \
	  ../../includes/NodeList.h ../../includes/Hash.h                         \
	  ../../includes/Source.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Source.c ***' >> $(LO)
	$$irs_lint Source.c 2>&1 | tee -a $(LO)

SourceNew.ln:SourceNew.c ../../includes/irs.h ../../includes/irsctl.h             \
	  ../../includes/irsrgst.h ../../includes/irsobjects.h                    \
	  ../../includes/Command.h ../../includes/Hash.h                          \
	  ../../includes/NodeList.h ../../includes/Rgst.h ../../includes/Region.h \
	  ../../includes/Source.h ../../includes/Transform.h                      \
	  ../../includes/UserList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON SourceNew.c ***' >> $(LO)
	$$irs_lint SourceNew.c 2>&1 | tee -a $(LO)

Species.ln:Species.c ../../includes/irs.h ../../includes/irsctl.h                 \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/Region.h ../../includes/UserList.h                       \
	  ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Species.c ***' >> $(LO)
	$$irs_lint Species.c 2>&1 | tee -a $(LO)

Spline.ln:Spline.c ../../includes/irs.h ../../includes/irsctl.h                   \
	  ../../includes/irsrgst.h ../../includes/Region.h                        \
	  ../../includes/Spline.h ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Spline.c ***' >> $(LO)
	$$irs_lint Spline.c 2>&1 | tee -a $(LO)

SubMesh.ln:SubMesh.c ../../includes/irs.h ../../includes/irsobjects.h             \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Extents.h ../../includes/NodeList.h                      \
	  ../../includes/UserList.h ../../includes/ProblemArray.h                 \
	  ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON SubMesh.c ***' >> $(LO)
	$$irs_lint SubMesh.c 2>&1 | tee -a $(LO)

TimePlot.ln:TimePlot.c ../../includes/irs.h ../../includes/irsctl.h               \
	  ../../includes/irsrgst.h ../../includes/Command.h ../../includes/Hash.h \
	  ../../includes/TimePlot.h ../../includes/FreqMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON TimePlot.c ***' >> $(LO)
	$$irs_lint TimePlot.c 2>&1 | tee -a $(LO)

TimePlotCurve.ln:TimePlotCurve.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/irsrgst.h ../../includes/Command.h                       \
	  ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON TimePlotCurve.c ***' >> $(LO)
	$$irs_lint TimePlotCurve.c 2>&1 | tee -a $(LO)

TimeStepControl.ln:TimeStepControl.c ../../includes/irs.h ../../includes/irscom.h \
	  ../../includes/irsctl.h ../../includes/irsdmp.h ../../includes/irslag.h \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/AEStackElm.h ../../includes/FunctionTimer.h              \
	  ../../includes/Hash.h ../../includes/NodeList.h ../../includes/Rgst.h   \
	  ../../includes/TimeStepControl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON TimeStepControl.c ***' >> $(LO)
	$$irs_lint TimeStepControl.c 2>&1 | tee -a $(LO)

Transform.ln:Transform.c ../../includes/irs.h ../../includes/irsrgst.h            \
	  ../../includes/irsctl.h ../../includes/irscom.h                         \
	  ../../includes/Command.h ../../includes/FunctionTimer.h                 \
	  ../../includes/NodeList.h ../../includes/Transform.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Transform.c ***' >> $(LO)
	$$irs_lint Transform.c 2>&1 | tee -a $(LO)

UserList.ln:UserList.c ../../includes/irs.h ../../includes/irsrgst.h              \
	  ../../includes/irsctl.h ../../includes/UserList.h ../../includes/Hash.h \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON UserList.c ***' >> $(LO)
	$$irs_lint UserList.c 2>&1 | tee -a $(LO)

VersionData.ln:VersionData.c ../../includes/irsdefs.h                             \
	  ../../includes/VersionData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON VersionData.c ***' >> $(LO)
	$$irs_lint VersionData.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/AEStackElm.inst.i $(PREDIR)/AttrArray.inst.i                 \
	  $(PREDIR)/Boundary.inst.i $(PREDIR)/BoundaryCondition.inst.i            \
	  $(PREDIR)/Conditional.inst.i $(PREDIR)/Database.inst.i                  \
	  $(PREDIR)/Domain.inst.i $(PREDIR)/EosGroup.inst.i                       \
	  $(PREDIR)/FunctionTimer.inst.i $(PREDIR)/GlobalArrays.inst.i            \
	  $(PREDIR)/NodeList.inst.i $(PREDIR)/NodeWindow.inst.i                   \
	  $(PREDIR)/ObjectName.inst.i $(PREDIR)/OpacityGroup.inst.i               \
	  $(PREDIR)/ProblemArray.inst.i $(PREDIR)/RGST_Object.inst.i              \
	  $(PREDIR)/Region.inst.i $(PREDIR)/Source.inst.i                         \
	  $(PREDIR)/SourceNew.inst.i $(PREDIR)/Species.inst.i                     \
	  $(PREDIR)/Spline.inst.i $(PREDIR)/SubMesh.inst.i                        \
	  $(PREDIR)/TimePlot.inst.i $(PREDIR)/TimePlotCurve.inst.i                \
	  $(PREDIR)/TimeStepControl.inst.i $(PREDIR)/Transform.inst.i             \
	  $(PREDIR)/UserList.inst.i $(PREDIR)/VersionData.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/AEStackElm.inst.i:AEStackElm.c ../../includes/irs.h                     \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/AEStackElm.hh ../../includes/Rgst.h
	@rm -f AEStackElm.i
	$$irs_pre AEStackElm.c >> AEStackElm.i
	@mv -f AEStackElm.i $(PREDIR)/AEStackElm.inst.i

$(PREDIR)/AttrArray.inst.i:AttrArray.c ../../includes/irs.h                       \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/Rgst.h
	@rm -f AttrArray.i
	$$irs_pre AttrArray.c >> AttrArray.i
	@mv -f AttrArray.i $(PREDIR)/AttrArray.inst.i

$(PREDIR)/Boundary.inst.i:Boundary.c ../../includes/irs.h ../../includes/irsctl.h \
	  ../../includes/irsrgst.h ../../includes/Boundary.h                      \
	  ../../includes/Command.h
	@rm -f Boundary.i
	$$irs_pre Boundary.c >> Boundary.i
	@mv -f Boundary.i $(PREDIR)/Boundary.inst.i

$(PREDIR)/BoundaryCondition.inst.i:BoundaryCondition.c ../../includes/irs.h       \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/BoundaryCondition.h ../../includes/Command.h             \
	  ../../includes/Hash.h ../../includes/NodeList.h
	@rm -f BoundaryCondition.i
	$$irs_pre BoundaryCondition.c >> BoundaryCondition.i
	@mv -f BoundaryCondition.i $(PREDIR)/BoundaryCondition.inst.i

$(PREDIR)/Conditional.inst.i:Conditional.c ../../includes/irs.h                   \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/Conditional.h ../../includes/Command.h
	@rm -f Conditional.i
	$$irs_pre Conditional.c >> Conditional.i
	@mv -f Conditional.i $(PREDIR)/Conditional.inst.i

$(PREDIR)/Database.inst.i:Database.c ../../includes/irs.h ../../includes/irsctl.h \
	  ../../includes/irsrgst.h ../../includes/Command.h                       \
	  ../../includes/Region.h
	@rm -f Database.i
	$$irs_pre Database.c >> Database.i
	@mv -f Database.i $(PREDIR)/Database.inst.i

$(PREDIR)/Domain.inst.i:Domain.c ../../includes/irs.h ../../includes/irsblk.h     \
	  ../../includes/irsgen.h ../../includes/irsbndry.h                       \
	  ../../includes/irsctl.h ../../includes/irsdmp.h                         \
	  ../../includes/irsobjects.h ../../includes/irsrgst.h                    \
	  ../../includes/BlockMapping.h ../../includes/Command.h                  \
	  ../../includes/Domain.h ../../includes/Extents.h                        \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h            \
	  ../../includes/Rgst.h
	@rm -f Domain.i
	$$irs_pre Domain.c >> Domain.i
	@mv -f Domain.i $(PREDIR)/Domain.inst.i

$(PREDIR)/EosGroup.inst.i:EosGroup.c ../../includes/irs.h ../../includes/irsctl.h \
	  ../../includes/irsrgst.h ../../includes/Command.h                       \
	  ../../includes/Region.h
	@rm -f EosGroup.i
	$$irs_pre EosGroup.c >> EosGroup.i
	@mv -f EosGroup.i $(PREDIR)/EosGroup.inst.i

$(PREDIR)/FunctionTimer.inst.i:FunctionTimer.c ../../includes/irs.h               \
	  ../../includes/irssys.h ../../includes/irscom.h ../../includes/irsctl.h \
	  ../../includes/irsrgst.h ../../includes/irsobjects.h                    \
	  ../../includes/BlockMapping.h ../../includes/Command.h                  \
	  ../../includes/FunctionTimer.h ../../includes/Hash.h
	@rm -f FunctionTimer.i
	$$irs_pre FunctionTimer.c >> FunctionTimer.i
	@mv -f FunctionTimer.i $(PREDIR)/FunctionTimer.inst.i

$(PREDIR)/GlobalArrays.inst.i:GlobalArrays.c ../../includes/irs.h                 \
	  ../../includes/irsobjects.h ../../includes/irsrgst.h                    \
	  ../../includes/irsreg.h ../../includes/ProblemArray.h                   \
	  ../../includes/Rgst.h
	@rm -f GlobalArrays.i
	$$irs_pre GlobalArrays.c >> GlobalArrays.i
	@mv -f GlobalArrays.i $(PREDIR)/GlobalArrays.inst.i

$(PREDIR)/NodeList.inst.i:NodeList.c ../../includes/irs.h                         \
	  ../../includes/irsrgst.h ../../includes/irsgen.h                        \
	  ../../includes/irsctl.h ../../includes/NodeList.hh                      \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h
	@rm -f NodeList.i
	$$irs_pre NodeList.c >> NodeList.i
	@mv -f NodeList.i $(PREDIR)/NodeList.inst.i

$(PREDIR)/NodeWindow.inst.i:NodeWindow.c ../../includes/irs.h                     \
	  ../../includes/irsgen.h ../../includes/irsctl.h                         \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Extents.h ../../includes/Tracer.h                        \
	  ../../includes/NodeList.h ../../includes/Hash.h                         \
	  ../../includes/ProblemArray.h ../../includes/UserList.h
	@rm -f NodeWindow.i
	$$irs_pre NodeWindow.c >> NodeWindow.i
	@mv -f NodeWindow.i $(PREDIR)/NodeWindow.inst.i

$(PREDIR)/ObjectName.inst.i:ObjectName.c ../../includes/irs.h                     \
	  ../../includes/irsobjects.h
	@rm -f ObjectName.i
	$$irs_pre ObjectName.c >> ObjectName.i
	@mv -f ObjectName.i $(PREDIR)/ObjectName.inst.i

$(PREDIR)/OpacityGroup.inst.i:OpacityGroup.c ../../includes/irs.h                 \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/Command.h ../../includes/Region.h
	@rm -f OpacityGroup.i
	$$irs_pre OpacityGroup.c >> OpacityGroup.i
	@mv -f OpacityGroup.i $(PREDIR)/OpacityGroup.inst.i

$(PREDIR)/ProblemArray.inst.i:ProblemArray.c ../../includes/irs.h                 \
	  ../../includes/irsrgst.h ../../includes/ProblemArray.h                  \
	  ../../includes/Rgst.h
	@rm -f ProblemArray.i
	$$irs_pre ProblemArray.c >> ProblemArray.i
	@mv -f ProblemArray.i $(PREDIR)/ProblemArray.inst.i

$(PREDIR)/RGST_Object.inst.i:RGST_Object.c ../../includes/irs.h                   \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/Rgst.h
	@rm -f RGST_Object.i
	$$irs_pre RGST_Object.c >> RGST_Object.i
	@mv -f RGST_Object.i $(PREDIR)/RGST_Object.inst.i

$(PREDIR)/Region.inst.i:Region.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/Command.h ../../includes/Hash.h ../../includes/Region.hh \
	  ../../includes/FunctionTimer.h
	@rm -f Region.i
	$$irs_pre Region.c >> Region.i
	@mv -f Region.i $(PREDIR)/Region.inst.i

$(PREDIR)/Source.inst.i:Source.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Command.h ../../includes/Extents.h                       \
	  ../../includes/NodeList.h ../../includes/Hash.h                         \
	  ../../includes/Source.hh
	@rm -f Source.i
	$$irs_pre Source.c >> Source.i
	@mv -f Source.i $(PREDIR)/Source.inst.i

$(PREDIR)/SourceNew.inst.i:SourceNew.c ../../includes/irs.h                       \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/irsobjects.h ../../includes/Command.h                    \
	  ../../includes/Hash.h ../../includes/NodeList.h ../../includes/Rgst.h   \
	  ../../includes/Region.h ../../includes/Source.h                         \
	  ../../includes/Transform.h ../../includes/UserList.h
	@rm -f SourceNew.i
	$$irs_pre SourceNew.c >> SourceNew.i
	@mv -f SourceNew.i $(PREDIR)/SourceNew.inst.i

$(PREDIR)/Species.inst.i:Species.c ../../includes/irs.h ../../includes/irsctl.h   \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/Region.h ../../includes/UserList.h                       \
	  ../../includes/Command.h
	@rm -f Species.i
	$$irs_pre Species.c >> Species.i
	@mv -f Species.i $(PREDIR)/Species.inst.i

$(PREDIR)/Spline.inst.i:Spline.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/irsrgst.h ../../includes/Region.h                        \
	  ../../includes/Spline.h ../../includes/Command.h
	@rm -f Spline.i
	$$irs_pre Spline.c >> Spline.i
	@mv -f Spline.i $(PREDIR)/Spline.inst.i

$(PREDIR)/SubMesh.inst.i:SubMesh.c ../../includes/irs.h                           \
	  ../../includes/irsobjects.h ../../includes/irsrgst.h                    \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/NodeList.h ../../includes/UserList.h                     \
	  ../../includes/ProblemArray.h ../../includes/Hash.h
	@rm -f SubMesh.i
	$$irs_pre SubMesh.c >> SubMesh.i
	@mv -f SubMesh.i $(PREDIR)/SubMesh.inst.i

$(PREDIR)/TimePlot.inst.i:TimePlot.c ../../includes/irs.h ../../includes/irsctl.h \
	  ../../includes/irsrgst.h ../../includes/Command.h ../../includes/Hash.h \
	  ../../includes/TimePlot.h ../../includes/FreqMesg.h
	@rm -f TimePlot.i
	$$irs_pre TimePlot.c >> TimePlot.i
	@mv -f TimePlot.i $(PREDIR)/TimePlot.inst.i

$(PREDIR)/TimePlotCurve.inst.i:TimePlotCurve.c ../../includes/irs.h               \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/Command.h ../../includes/TimePlot.h
	@rm -f TimePlotCurve.i
	$$irs_pre TimePlotCurve.c >> TimePlotCurve.i
	@mv -f TimePlotCurve.i $(PREDIR)/TimePlotCurve.inst.i

$(PREDIR)/TimeStepControl.inst.i:TimeStepControl.c ../../includes/irs.h           \
	  ../../includes/irscom.h ../../includes/irsctl.h ../../includes/irsdmp.h \
	  ../../includes/irslag.h ../../includes/irsrgst.h                        \
	  ../../includes/BlockMapping.h ../../includes/AEStackElm.h               \
	  ../../includes/FunctionTimer.h ../../includes/Hash.h                    \
	  ../../includes/NodeList.h ../../includes/Rgst.h                         \
	  ../../includes/TimeStepControl.h
	@rm -f TimeStepControl.i
	$$irs_pre TimeStepControl.c >> TimeStepControl.i
	@mv -f TimeStepControl.i $(PREDIR)/TimeStepControl.inst.i

$(PREDIR)/Transform.inst.i:Transform.c ../../includes/irs.h                       \
	  ../../includes/irsrgst.h ../../includes/irsctl.h                        \
	  ../../includes/irscom.h ../../includes/Command.h                        \
	  ../../includes/FunctionTimer.h ../../includes/NodeList.h                \
	  ../../includes/Transform.h
	@rm -f Transform.i
	$$irs_pre Transform.c >> Transform.i
	@mv -f Transform.i $(PREDIR)/Transform.inst.i

$(PREDIR)/UserList.inst.i:UserList.c ../../includes/irs.h                         \
	  ../../includes/irsrgst.h ../../includes/irsctl.h                        \
	  ../../includes/UserList.h ../../includes/Hash.h ../../includes/Rgst.h
	@rm -f UserList.i
	$$irs_pre UserList.c >> UserList.i
	@mv -f UserList.i $(PREDIR)/UserList.inst.i

$(PREDIR)/VersionData.inst.i:VersionData.c ../../includes/irsdefs.h               \
	  ../../includes/VersionData.h
	@rm -f VersionData.i
	$$irs_pre VersionData.c >> VersionData.i
	@mv -f VersionData.i $(PREDIR)/VersionData.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libobjects_inst

libobjects_inst:$(BI)(AEStackElm.inst.o) $(BI)(AttrArray.inst.o)                  \
	  $(BI)(Boundary.inst.o) $(BI)(BoundaryCondition.inst.o)                  \
	  $(BI)(Conditional.inst.o) $(BI)(Database.inst.o) $(BI)(Domain.inst.o)   \
	  $(BI)(EosGroup.inst.o) $(BI)(FunctionTimer.inst.o)                      \
	  $(BI)(GlobalArrays.inst.o) $(BI)(NodeList.inst.o)                       \
	  $(BI)(NodeWindow.inst.o) $(BI)(ObjectName.inst.o)                       \
	  $(BI)(OpacityGroup.inst.o) $(BI)(ProblemArray.inst.o)                   \
	  $(BI)(RGST_Object.inst.o) $(BI)(Region.inst.o) $(BI)(Source.inst.o)     \
	  $(BI)(SourceNew.inst.o) $(BI)(Species.inst.o) $(BI)(Spline.inst.o)      \
	  $(BI)(SubMesh.inst.o) $(BI)(TimePlot.inst.o)                            \
	  $(BI)(TimePlotCurve.inst.o) $(BI)(TimeStepControl.inst.o)               \
	  $(BI)(Transform.inst.o) $(BI)(UserList.inst.o)                          \
	  $(BI)(VersionData.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libobjects_inst.a $(B); \
		ln -sf libobjects_inst.a $(B)); \
	  fi
	  @echo 'libobjects_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(AEStackElm.inst.o):$(INSTDIR)/AEStackElm.inst.i
	$$irs_post $(INSTDIR)/AEStackElm.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/AEStackElm.inst.i $(DB)/AEStackElm.c 

$(BI)(AttrArray.inst.o):$(INSTDIR)/AttrArray.inst.i
	$$irs_post $(INSTDIR)/AttrArray.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/AttrArray.inst.i $(DB)/AttrArray.c 

$(BI)(Boundary.inst.o):$(INSTDIR)/Boundary.inst.i
	$$irs_post $(INSTDIR)/Boundary.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Boundary.inst.i $(DB)/Boundary.c 

$(BI)(BoundaryCondition.inst.o):$(INSTDIR)/BoundaryCondition.inst.i
	$$irs_post $(INSTDIR)/BoundaryCondition.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/BoundaryCondition.inst.i $(DB)/BoundaryCondition.c 

$(BI)(Conditional.inst.o):$(INSTDIR)/Conditional.inst.i
	$$irs_post $(INSTDIR)/Conditional.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Conditional.inst.i $(DB)/Conditional.c 

$(BI)(Database.inst.o):$(INSTDIR)/Database.inst.i
	$$irs_post $(INSTDIR)/Database.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Database.inst.i $(DB)/Database.c 

$(BI)(Domain.inst.o):$(INSTDIR)/Domain.inst.i
	$$irs_post $(INSTDIR)/Domain.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Domain.inst.i $(DB)/Domain.c 

$(BI)(EosGroup.inst.o):$(INSTDIR)/EosGroup.inst.i
	$$irs_post $(INSTDIR)/EosGroup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/EosGroup.inst.i $(DB)/EosGroup.c 

$(BI)(FunctionTimer.inst.o):$(INSTDIR)/FunctionTimer.inst.i
	$$irs_post $(INSTDIR)/FunctionTimer.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FunctionTimer.inst.i $(DB)/FunctionTimer.c 

$(BI)(GlobalArrays.inst.o):$(INSTDIR)/GlobalArrays.inst.i
	$$irs_post $(INSTDIR)/GlobalArrays.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/GlobalArrays.inst.i $(DB)/GlobalArrays.c 

$(BI)(NodeList.inst.o):$(INSTDIR)/NodeList.inst.i
	$$irs_post $(INSTDIR)/NodeList.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/NodeList.inst.i $(DB)/NodeList.c 

$(BI)(NodeWindow.inst.o):$(INSTDIR)/NodeWindow.inst.i
	$$irs_post $(INSTDIR)/NodeWindow.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/NodeWindow.inst.i $(DB)/NodeWindow.c 

$(BI)(ObjectName.inst.o):$(INSTDIR)/ObjectName.inst.i
	$$irs_post $(INSTDIR)/ObjectName.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ObjectName.inst.i $(DB)/ObjectName.c 

$(BI)(OpacityGroup.inst.o):$(INSTDIR)/OpacityGroup.inst.i
	$$irs_post $(INSTDIR)/OpacityGroup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/OpacityGroup.inst.i $(DB)/OpacityGroup.c 

$(BI)(ProblemArray.inst.o):$(INSTDIR)/ProblemArray.inst.i
	$$irs_post $(INSTDIR)/ProblemArray.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ProblemArray.inst.i $(DB)/ProblemArray.c 

$(BI)(RGST_Object.inst.o):$(INSTDIR)/RGST_Object.inst.i
	$$irs_post $(INSTDIR)/RGST_Object.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/RGST_Object.inst.i $(DB)/RGST_Object.c 

$(BI)(Region.inst.o):$(INSTDIR)/Region.inst.i
	$$irs_post $(INSTDIR)/Region.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Region.inst.i $(DB)/Region.c 

$(BI)(Source.inst.o):$(INSTDIR)/Source.inst.i
	$$irs_post $(INSTDIR)/Source.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Source.inst.i $(DB)/Source.c 

$(BI)(SourceNew.inst.o):$(INSTDIR)/SourceNew.inst.i
	$$irs_post $(INSTDIR)/SourceNew.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/SourceNew.inst.i $(DB)/SourceNew.c 

$(BI)(Species.inst.o):$(INSTDIR)/Species.inst.i
	$$irs_post $(INSTDIR)/Species.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Species.inst.i $(DB)/Species.c 

$(BI)(Spline.inst.o):$(INSTDIR)/Spline.inst.i
	$$irs_post $(INSTDIR)/Spline.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Spline.inst.i $(DB)/Spline.c 

$(BI)(SubMesh.inst.o):$(INSTDIR)/SubMesh.inst.i
	$$irs_post $(INSTDIR)/SubMesh.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/SubMesh.inst.i $(DB)/SubMesh.c 

$(BI)(TimePlot.inst.o):$(INSTDIR)/TimePlot.inst.i
	$$irs_post $(INSTDIR)/TimePlot.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/TimePlot.inst.i $(DB)/TimePlot.c 

$(BI)(TimePlotCurve.inst.o):$(INSTDIR)/TimePlotCurve.inst.i
	$$irs_post $(INSTDIR)/TimePlotCurve.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/TimePlotCurve.inst.i $(DB)/TimePlotCurve.c 

$(BI)(TimeStepControl.inst.o):$(INSTDIR)/TimeStepControl.inst.i
	$$irs_post $(INSTDIR)/TimeStepControl.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/TimeStepControl.inst.i $(DB)/TimeStepControl.c 

$(BI)(Transform.inst.o):$(INSTDIR)/Transform.inst.i
	$$irs_post $(INSTDIR)/Transform.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Transform.inst.i $(DB)/Transform.c 

$(BI)(UserList.inst.o):$(INSTDIR)/UserList.inst.i
	$$irs_post $(INSTDIR)/UserList.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/UserList.inst.i $(DB)/UserList.c 

$(BI)(VersionData.inst.o):$(INSTDIR)/VersionData.inst.i
	$$irs_post $(INSTDIR)/VersionData.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/VersionData.inst.i $(DB)/VersionData.c 

DEP_SRCS = \
	AEStackElm.c AttrArray.c Boundary.c BoundaryCondition.c Conditional.c  \
	Database.c Domain.c EosGroup.c FunctionTimer.c GlobalArrays.c NodeList.c  \
	NodeWindow.c ObjectName.c OpacityGroup.c ProblemArray.c RGST_Object.c  \
	Region.c Source.c SourceNew.c Species.c Spline.c SubMesh.c TimePlot.c  \
	TimePlotCurve.c TimeStepControl.c Transform.c UserList.c VersionData.c  

depend:
	@cp -f Makefile.objects Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

