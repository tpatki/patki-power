
################################################################################
#
# Makefile for irs library edits
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
B = ../$(LIB_DIR)/libedits.a
BI = ../$(LIB_DIR)/libedits_inst.a

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
SRCDIR = ../sources/edits

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libedits:$(B)(editor.o) $(B)(flagedit.o) $(B)(matedit.o) $(B)(mpi_edit.o)         \
	  $(B)(print.o) $(B)(printcyclefreq.o) $(B)(printcyclefreqs.o)            \
	  $(B)(printmapping.o) $(B)(printnodelist.o) $(B)(printspec.o)            \
	  $(B)(printtimefreq.o) $(B)(printtimefreqs.o) $(B)(printtimeplot.o)      \
	  $(B)(printtimeplots.o) $(B)(printtpcurve.o) $(B)(printtpcurves.o)       \
	  $(B)(query_timer.o) $(B)(reducevar.o) $(B)(regedit.o)                   \
	  $(B)(regenrgy2d.o) $(B)(regenrgy3d.o) $(B)(stateedit.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'edits library current'

# creation deps
#---------------
$(B)(editor.o):editor.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/editor.c $(DB)/editor.c 

$(B)(flagedit.o):flagedit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/flagedit.c $(DB)/flagedit.c 

$(B)(matedit.o):matedit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/matedit.c $(DB)/matedit.c 

$(B)(mpi_edit.o):mpi_edit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/mpi_edit.c $(DB)/mpi_edit.c 

$(B)(print.o):print.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/print.c $(DB)/print.c 

$(B)(printcyclefreq.o):printcyclefreq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printcyclefreq.c $(DB)/printcyclefreq.c 

$(B)(printcyclefreqs.o):printcyclefreqs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printcyclefreqs.c $(DB)/printcyclefreqs.c 

../../includes/BlockMapping.hh:../../includes/BlockMapping.h
	cp ../../includes/BlockMapping.h ../../includes/BlockMapping.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/BlockMapping.hh
	irs_hhinit ../../includes/BlockMapping.hh

$(B)(printmapping.o):../../includes/BlockMapping.hh

$(B)(printmapping.o):printmapping.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printmapping.c $(DB)/printmapping.c 

$(B)(printnodelist.o):printnodelist.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printnodelist.c $(DB)/printnodelist.c 

$(B)(printspec.o):printspec.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printspec.c $(DB)/printspec.c 

$(B)(printtimefreq.o):printtimefreq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printtimefreq.c $(DB)/printtimefreq.c 

$(B)(printtimefreqs.o):printtimefreqs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printtimefreqs.c $(DB)/printtimefreqs.c 

$(B)(printtimeplot.o):printtimeplot.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printtimeplot.c $(DB)/printtimeplot.c 

$(B)(printtimeplots.o):printtimeplots.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printtimeplots.c $(DB)/printtimeplots.c 

$(B)(printtpcurve.o):printtpcurve.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printtpcurve.c $(DB)/printtpcurve.c 

$(B)(printtpcurves.o):printtpcurves.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printtpcurves.c $(DB)/printtpcurves.c 

$(B)(query_timer.o):query_timer.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/query_timer.c $(DB)/query_timer.c 

$(B)(reducevar.o):reducevar.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/reducevar.c $(DB)/reducevar.c 

$(B)(regedit.o):regedit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/regedit.c $(DB)/regedit.c 

$(B)(regenrgy2d.o):regenrgy2d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/regenrgy2d.c $(DB)/regenrgy2d.c 

$(B)(regenrgy3d.o):regenrgy3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/regenrgy3d.c $(DB)/regenrgy3d.c 

$(B)(stateedit.o):stateedit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/stateedit.c $(DB)/stateedit.c 

#---------------------
# lint pass one target 
#---------------------
lint:editor.ln flagedit.ln matedit.ln mpi_edit.ln print.ln printcyclefreq.ln      \
	  printcyclefreqs.ln printmapping.ln printnodelist.ln printspec.ln        \
	  printtimefreq.ln printtimefreqs.ln printtimeplot.ln printtimeplots.ln   \
	  printtpcurve.ln printtpcurves.ln query_timer.ln reducevar.ln regedit.ln \
	  regenrgy2d.ln regenrgy3d.ln stateedit.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
editor.ln:editor.c ../../includes/irs.h ../../includes/irsreg.h                   \
	  ../../includes/irscom.h ../../includes/irsedits.h                       \
	  ../../includes/irsrgst.h ../../includes/FunctionTimer.h                 \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/Source.h ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON editor.c ***' >> $(LO)
	$$irs_lint editor.c 2>&1 | tee -a $(LO)

flagedit.ln:flagedit.c ../../includes/irs.h ../../includes/irsedits.h             \
	  ../../includes/irsparm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON flagedit.c ***' >> $(LO)
	$$irs_lint flagedit.c 2>&1 | tee -a $(LO)

matedit.ln:matedit.c ../../includes/irs.h ../../includes/irsedits.h               \
	  ../../includes/irseos.h ../../includes/irsreg.h                         \
	  ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON matedit.c ***' >> $(LO)
	$$irs_lint matedit.c 2>&1 | tee -a $(LO)

mpi_edit.ln:mpi_edit.c ../../includes/irs.h ../../includes/irscom.h               \
	  ../../includes/irsedits.h ../../includes/FunctionTimer.h                \
	  ../../includes/AEStackElm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON mpi_edit.c ***' >> $(LO)
	$$irs_lint mpi_edit.c 2>&1 | tee -a $(LO)

print.ln:print.c ../../includes/irs.h ../../includes/irsedits.h                   \
	  ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON print.c ***' >> $(LO)
	$$irs_lint print.c 2>&1 | tee -a $(LO)

printcyclefreq.ln:printcyclefreq.c ../../includes/irs.h ../../includes/irsedits.h \
	  ../../includes/CycleMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printcyclefreq.c ***' >> $(LO)
	$$irs_lint printcyclefreq.c 2>&1 | tee -a $(LO)

printcyclefreqs.ln:printcyclefreqs.c ../../includes/irs.h                         \
	  ../../includes/irsedits.h ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printcyclefreqs.c ***' >> $(LO)
	$$irs_lint printcyclefreqs.c 2>&1 | tee -a $(LO)

printmapping.ln:printmapping.c ../../includes/irs.h ../../includes/irsedits.h     \
	  ../../includes/BlockMapping.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printmapping.c ***' >> $(LO)
	$$irs_lint printmapping.c 2>&1 | tee -a $(LO)

printnodelist.ln:printnodelist.c ../../includes/irs.h ../../includes/irsedits.h   \
	  ../../includes/irsrgst.h ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printnodelist.c ***' >> $(LO)
	$$irs_lint printnodelist.c 2>&1 | tee -a $(LO)

printspec.ln:printspec.c ../../includes/irs.h ../../includes/irsedits.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printspec.c ***' >> $(LO)
	$$irs_lint printspec.c 2>&1 | tee -a $(LO)

printtimefreq.ln:printtimefreq.c ../../includes/irs.h ../../includes/irsedits.h   \
	  ../../includes/FreqMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printtimefreq.c ***' >> $(LO)
	$$irs_lint printtimefreq.c 2>&1 | tee -a $(LO)

printtimefreqs.ln:printtimefreqs.c ../../includes/irs.h ../../includes/irsedits.h \
	  ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printtimefreqs.c ***' >> $(LO)
	$$irs_lint printtimefreqs.c 2>&1 | tee -a $(LO)

printtimeplot.ln:printtimeplot.c ../../includes/irs.h ../../includes/irsedits.h   \
	  ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printtimeplot.c ***' >> $(LO)
	$$irs_lint printtimeplot.c 2>&1 | tee -a $(LO)

printtimeplots.ln:printtimeplots.c ../../includes/irs.h ../../includes/irsedits.h \
	  ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printtimeplots.c ***' >> $(LO)
	$$irs_lint printtimeplots.c 2>&1 | tee -a $(LO)

printtpcurve.ln:printtpcurve.c ../../includes/irs.h ../../includes/irsedits.h     \
	  ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printtpcurve.c ***' >> $(LO)
	$$irs_lint printtpcurve.c 2>&1 | tee -a $(LO)

printtpcurves.ln:printtpcurves.c ../../includes/irs.h ../../includes/irsedits.h   \
	  ../../includes/Hash.h ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printtpcurves.c ***' >> $(LO)
	$$irs_lint printtpcurves.c 2>&1 | tee -a $(LO)

query_timer.ln:query_timer.c ../../includes/irs.h ../../includes/irscom.h         \
	  ../../includes/irsedits.h ../../includes/BlockMapping.h                 \
	  ../../includes/FunctionTimer.h ../../includes/AEStackElm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON query_timer.c ***' >> $(LO)
	$$irs_lint query_timer.c 2>&1 | tee -a $(LO)

reducevar.ln:reducevar.c ../../includes/irs.h ../../includes/irsgen.h             \
	  ../../includes/irscom.h ../../includes/irsedits.h                       \
	  ../../includes/irsrgst.h ../../includes/irsreg.h                        \
	  ../../includes/FunctionTimer.h ../../includes/NodeList.h                \
	  ../../includes/ProblemArray.h ../../includes/UserList.h                 \
	  ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON reducevar.c ***' >> $(LO)
	$$irs_lint reducevar.c 2>&1 | tee -a $(LO)

regedit.ln:regedit.c ../../includes/irs.h ../../includes/irsedits.h               \
	  ../../includes/irsreg.h ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON regedit.c ***' >> $(LO)
	$$irs_lint regedit.c 2>&1 | tee -a $(LO)

regenrgy2d.ln:regenrgy2d.c ../../includes/irs.h ../../includes/irsedits.h         \
	  ../../includes/irsreg.h ../../includes/ProblemArray.h                   \
	  ../../includes/FunctionTimer.h ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON regenrgy2d.c ***' >> $(LO)
	$$irs_lint regenrgy2d.c 2>&1 | tee -a $(LO)

regenrgy3d.ln:regenrgy3d.c ../../includes/irs.h ../../includes/irsreg.h           \
	  ../../includes/irsedits.h ../../includes/ProblemArray.h                 \
	  ../../includes/FunctionTimer.h ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON regenrgy3d.c ***' >> $(LO)
	$$irs_lint regenrgy3d.c 2>&1 | tee -a $(LO)

stateedit.ln:stateedit.c ../../includes/irs.h ../../includes/irslag.h             \
	  ../../includes/irsbndry.h ../../includes/irsedits.h                     \
	  ../../includes/irsparm.h ../../includes/BlockMapping.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON stateedit.c ***' >> $(LO)
	$$irs_lint stateedit.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/editor.inst.i $(PREDIR)/flagedit.inst.i                      \
	  $(PREDIR)/matedit.inst.i $(PREDIR)/mpi_edit.inst.i                      \
	  $(PREDIR)/print.inst.i $(PREDIR)/printcyclefreq.inst.i                  \
	  $(PREDIR)/printcyclefreqs.inst.i $(PREDIR)/printmapping.inst.i          \
	  $(PREDIR)/printnodelist.inst.i $(PREDIR)/printspec.inst.i               \
	  $(PREDIR)/printtimefreq.inst.i $(PREDIR)/printtimefreqs.inst.i          \
	  $(PREDIR)/printtimeplot.inst.i $(PREDIR)/printtimeplots.inst.i          \
	  $(PREDIR)/printtpcurve.inst.i $(PREDIR)/printtpcurves.inst.i            \
	  $(PREDIR)/query_timer.inst.i $(PREDIR)/reducevar.inst.i                 \
	  $(PREDIR)/regedit.inst.i $(PREDIR)/regenrgy2d.inst.i                    \
	  $(PREDIR)/regenrgy3d.inst.i $(PREDIR)/stateedit.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/editor.inst.i:editor.c ../../includes/irs.h ../../includes/irsreg.h     \
	  ../../includes/irscom.h ../../includes/irsedits.h                       \
	  ../../includes/irsrgst.h ../../includes/FunctionTimer.h                 \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/Source.h ../../includes/Region.h
	@rm -f editor.i
	$$irs_pre editor.c >> editor.i
	@mv -f editor.i $(PREDIR)/editor.inst.i

$(PREDIR)/flagedit.inst.i:flagedit.c ../../includes/irs.h                         \
	  ../../includes/irsedits.h ../../includes/irsparm.h
	@rm -f flagedit.i
	$$irs_pre flagedit.c >> flagedit.i
	@mv -f flagedit.i $(PREDIR)/flagedit.inst.i

$(PREDIR)/matedit.inst.i:matedit.c ../../includes/irs.h ../../includes/irsedits.h \
	  ../../includes/irseos.h ../../includes/irsreg.h                         \
	  ../../includes/Region.h
	@rm -f matedit.i
	$$irs_pre matedit.c >> matedit.i
	@mv -f matedit.i $(PREDIR)/matedit.inst.i

$(PREDIR)/mpi_edit.inst.i:mpi_edit.c ../../includes/irs.h ../../includes/irscom.h \
	  ../../includes/irsedits.h ../../includes/FunctionTimer.h                \
	  ../../includes/AEStackElm.h
	@rm -f mpi_edit.i
	$$irs_pre mpi_edit.c >> mpi_edit.i
	@mv -f mpi_edit.i $(PREDIR)/mpi_edit.inst.i

$(PREDIR)/print.inst.i:print.c ../../includes/irs.h ../../includes/irsedits.h     \
	  ../../includes/Hash.h
	@rm -f print.i
	$$irs_pre print.c >> print.i
	@mv -f print.i $(PREDIR)/print.inst.i

$(PREDIR)/printcyclefreq.inst.i:printcyclefreq.c ../../includes/irs.h             \
	  ../../includes/irsedits.h ../../includes/CycleMesg.h
	@rm -f printcyclefreq.i
	$$irs_pre printcyclefreq.c >> printcyclefreq.i
	@mv -f printcyclefreq.i $(PREDIR)/printcyclefreq.inst.i

$(PREDIR)/printcyclefreqs.inst.i:printcyclefreqs.c ../../includes/irs.h           \
	  ../../includes/irsedits.h ../../includes/Hash.h
	@rm -f printcyclefreqs.i
	$$irs_pre printcyclefreqs.c >> printcyclefreqs.i
	@mv -f printcyclefreqs.i $(PREDIR)/printcyclefreqs.inst.i

$(PREDIR)/printmapping.inst.i:printmapping.c ../../includes/irs.h                 \
	  ../../includes/irsedits.h ../../includes/BlockMapping.hh
	@rm -f printmapping.i
	$$irs_pre printmapping.c >> printmapping.i
	@mv -f printmapping.i $(PREDIR)/printmapping.inst.i

$(PREDIR)/printnodelist.inst.i:printnodelist.c ../../includes/irs.h               \
	  ../../includes/irsedits.h ../../includes/irsrgst.h                      \
	  ../../includes/NodeList.h
	@rm -f printnodelist.i
	$$irs_pre printnodelist.c >> printnodelist.i
	@mv -f printnodelist.i $(PREDIR)/printnodelist.inst.i

$(PREDIR)/printspec.inst.i:printspec.c ../../includes/irs.h                       \
	  ../../includes/irsedits.h
	@rm -f printspec.i
	$$irs_pre printspec.c >> printspec.i
	@mv -f printspec.i $(PREDIR)/printspec.inst.i

$(PREDIR)/printtimefreq.inst.i:printtimefreq.c ../../includes/irs.h               \
	  ../../includes/irsedits.h ../../includes/FreqMesg.h
	@rm -f printtimefreq.i
	$$irs_pre printtimefreq.c >> printtimefreq.i
	@mv -f printtimefreq.i $(PREDIR)/printtimefreq.inst.i

$(PREDIR)/printtimefreqs.inst.i:printtimefreqs.c ../../includes/irs.h             \
	  ../../includes/irsedits.h ../../includes/Hash.h
	@rm -f printtimefreqs.i
	$$irs_pre printtimefreqs.c >> printtimefreqs.i
	@mv -f printtimefreqs.i $(PREDIR)/printtimefreqs.inst.i

$(PREDIR)/printtimeplot.inst.i:printtimeplot.c ../../includes/irs.h               \
	  ../../includes/irsedits.h ../../includes/TimePlot.h
	@rm -f printtimeplot.i
	$$irs_pre printtimeplot.c >> printtimeplot.i
	@mv -f printtimeplot.i $(PREDIR)/printtimeplot.inst.i

$(PREDIR)/printtimeplots.inst.i:printtimeplots.c ../../includes/irs.h             \
	  ../../includes/irsedits.h ../../includes/Hash.h
	@rm -f printtimeplots.i
	$$irs_pre printtimeplots.c >> printtimeplots.i
	@mv -f printtimeplots.i $(PREDIR)/printtimeplots.inst.i

$(PREDIR)/printtpcurve.inst.i:printtpcurve.c ../../includes/irs.h                 \
	  ../../includes/irsedits.h ../../includes/TimePlot.h
	@rm -f printtpcurve.i
	$$irs_pre printtpcurve.c >> printtpcurve.i
	@mv -f printtpcurve.i $(PREDIR)/printtpcurve.inst.i

$(PREDIR)/printtpcurves.inst.i:printtpcurves.c ../../includes/irs.h               \
	  ../../includes/irsedits.h ../../includes/Hash.h                         \
	  ../../includes/TimePlot.h
	@rm -f printtpcurves.i
	$$irs_pre printtpcurves.c >> printtpcurves.i
	@mv -f printtpcurves.i $(PREDIR)/printtpcurves.inst.i

$(PREDIR)/query_timer.inst.i:query_timer.c ../../includes/irs.h                   \
	  ../../includes/irscom.h ../../includes/irsedits.h                       \
	  ../../includes/BlockMapping.h ../../includes/FunctionTimer.h            \
	  ../../includes/AEStackElm.h
	@rm -f query_timer.i
	$$irs_pre query_timer.c >> query_timer.i
	@mv -f query_timer.i $(PREDIR)/query_timer.inst.i

$(PREDIR)/reducevar.inst.i:reducevar.c ../../includes/irs.h                       \
	  ../../includes/irsgen.h ../../includes/irscom.h                         \
	  ../../includes/irsedits.h ../../includes/irsrgst.h                      \
	  ../../includes/irsreg.h ../../includes/FunctionTimer.h                  \
	  ../../includes/NodeList.h ../../includes/ProblemArray.h                 \
	  ../../includes/UserList.h ../../includes/Region.h
	@rm -f reducevar.i
	$$irs_pre reducevar.c >> reducevar.i
	@mv -f reducevar.i $(PREDIR)/reducevar.inst.i

$(PREDIR)/regedit.inst.i:regedit.c ../../includes/irs.h ../../includes/irsedits.h \
	  ../../includes/irsreg.h ../../includes/ProblemArray.h
	@rm -f regedit.i
	$$irs_pre regedit.c >> regedit.i
	@mv -f regedit.i $(PREDIR)/regedit.inst.i

$(PREDIR)/regenrgy2d.inst.i:regenrgy2d.c ../../includes/irs.h                     \
	  ../../includes/irsedits.h ../../includes/irsreg.h                       \
	  ../../includes/ProblemArray.h ../../includes/FunctionTimer.h            \
	  ../../includes/Region.h
	@rm -f regenrgy2d.i
	$$irs_pre regenrgy2d.c >> regenrgy2d.i
	@mv -f regenrgy2d.i $(PREDIR)/regenrgy2d.inst.i

$(PREDIR)/regenrgy3d.inst.i:regenrgy3d.c ../../includes/irs.h                     \
	  ../../includes/irsreg.h ../../includes/irsedits.h                       \
	  ../../includes/ProblemArray.h ../../includes/FunctionTimer.h            \
	  ../../includes/Region.h
	@rm -f regenrgy3d.i
	$$irs_pre regenrgy3d.c >> regenrgy3d.i
	@mv -f regenrgy3d.i $(PREDIR)/regenrgy3d.inst.i

$(PREDIR)/stateedit.inst.i:stateedit.c ../../includes/irs.h                       \
	  ../../includes/irslag.h ../../includes/irsbndry.h                       \
	  ../../includes/irsedits.h ../../includes/irsparm.h                      \
	  ../../includes/BlockMapping.h
	@rm -f stateedit.i
	$$irs_pre stateedit.c >> stateedit.i
	@mv -f stateedit.i $(PREDIR)/stateedit.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libedits_inst

libedits_inst:$(BI)(editor.inst.o) $(BI)(flagedit.inst.o) $(BI)(matedit.inst.o)   \
	  $(BI)(mpi_edit.inst.o) $(BI)(print.inst.o) $(BI)(printcyclefreq.inst.o) \
	  $(BI)(printcyclefreqs.inst.o) $(BI)(printmapping.inst.o)                \
	  $(BI)(printnodelist.inst.o) $(BI)(printspec.inst.o)                     \
	  $(BI)(printtimefreq.inst.o) $(BI)(printtimefreqs.inst.o)                \
	  $(BI)(printtimeplot.inst.o) $(BI)(printtimeplots.inst.o)                \
	  $(BI)(printtpcurve.inst.o) $(BI)(printtpcurves.inst.o)                  \
	  $(BI)(query_timer.inst.o) $(BI)(reducevar.inst.o) $(BI)(regedit.inst.o) \
	  $(BI)(regenrgy2d.inst.o) $(BI)(regenrgy3d.inst.o)                       \
	  $(BI)(stateedit.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libedits_inst.a $(B); \
		ln -sf libedits_inst.a $(B)); \
	  fi
	  @echo 'libedits_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(editor.inst.o):$(INSTDIR)/editor.inst.i
	$$irs_post $(INSTDIR)/editor.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/editor.inst.i $(DB)/editor.c 

$(BI)(flagedit.inst.o):$(INSTDIR)/flagedit.inst.i
	$$irs_post $(INSTDIR)/flagedit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/flagedit.inst.i $(DB)/flagedit.c 

$(BI)(matedit.inst.o):$(INSTDIR)/matedit.inst.i
	$$irs_post $(INSTDIR)/matedit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/matedit.inst.i $(DB)/matedit.c 

$(BI)(mpi_edit.inst.o):$(INSTDIR)/mpi_edit.inst.i
	$$irs_post $(INSTDIR)/mpi_edit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/mpi_edit.inst.i $(DB)/mpi_edit.c 

$(BI)(print.inst.o):$(INSTDIR)/print.inst.i
	$$irs_post $(INSTDIR)/print.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/print.inst.i $(DB)/print.c 

$(BI)(printcyclefreq.inst.o):$(INSTDIR)/printcyclefreq.inst.i
	$$irs_post $(INSTDIR)/printcyclefreq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printcyclefreq.inst.i $(DB)/printcyclefreq.c 

$(BI)(printcyclefreqs.inst.o):$(INSTDIR)/printcyclefreqs.inst.i
	$$irs_post $(INSTDIR)/printcyclefreqs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printcyclefreqs.inst.i $(DB)/printcyclefreqs.c 

$(BI)(printmapping.inst.o):$(INSTDIR)/printmapping.inst.i
	$$irs_post $(INSTDIR)/printmapping.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printmapping.inst.i $(DB)/printmapping.c 

$(BI)(printnodelist.inst.o):$(INSTDIR)/printnodelist.inst.i
	$$irs_post $(INSTDIR)/printnodelist.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printnodelist.inst.i $(DB)/printnodelist.c 

$(BI)(printspec.inst.o):$(INSTDIR)/printspec.inst.i
	$$irs_post $(INSTDIR)/printspec.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printspec.inst.i $(DB)/printspec.c 

$(BI)(printtimefreq.inst.o):$(INSTDIR)/printtimefreq.inst.i
	$$irs_post $(INSTDIR)/printtimefreq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printtimefreq.inst.i $(DB)/printtimefreq.c 

$(BI)(printtimefreqs.inst.o):$(INSTDIR)/printtimefreqs.inst.i
	$$irs_post $(INSTDIR)/printtimefreqs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printtimefreqs.inst.i $(DB)/printtimefreqs.c 

$(BI)(printtimeplot.inst.o):$(INSTDIR)/printtimeplot.inst.i
	$$irs_post $(INSTDIR)/printtimeplot.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printtimeplot.inst.i $(DB)/printtimeplot.c 

$(BI)(printtimeplots.inst.o):$(INSTDIR)/printtimeplots.inst.i
	$$irs_post $(INSTDIR)/printtimeplots.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printtimeplots.inst.i $(DB)/printtimeplots.c 

$(BI)(printtpcurve.inst.o):$(INSTDIR)/printtpcurve.inst.i
	$$irs_post $(INSTDIR)/printtpcurve.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printtpcurve.inst.i $(DB)/printtpcurve.c 

$(BI)(printtpcurves.inst.o):$(INSTDIR)/printtpcurves.inst.i
	$$irs_post $(INSTDIR)/printtpcurves.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printtpcurves.inst.i $(DB)/printtpcurves.c 

$(BI)(query_timer.inst.o):$(INSTDIR)/query_timer.inst.i
	$$irs_post $(INSTDIR)/query_timer.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/query_timer.inst.i $(DB)/query_timer.c 

$(BI)(reducevar.inst.o):$(INSTDIR)/reducevar.inst.i
	$$irs_post $(INSTDIR)/reducevar.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/reducevar.inst.i $(DB)/reducevar.c 

$(BI)(regedit.inst.o):$(INSTDIR)/regedit.inst.i
	$$irs_post $(INSTDIR)/regedit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/regedit.inst.i $(DB)/regedit.c 

$(BI)(regenrgy2d.inst.o):$(INSTDIR)/regenrgy2d.inst.i
	$$irs_post $(INSTDIR)/regenrgy2d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/regenrgy2d.inst.i $(DB)/regenrgy2d.c 

$(BI)(regenrgy3d.inst.o):$(INSTDIR)/regenrgy3d.inst.i
	$$irs_post $(INSTDIR)/regenrgy3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/regenrgy3d.inst.i $(DB)/regenrgy3d.c 

$(BI)(stateedit.inst.o):$(INSTDIR)/stateedit.inst.i
	$$irs_post $(INSTDIR)/stateedit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/stateedit.inst.i $(DB)/stateedit.c 

DEP_SRCS = \
	editor.c flagedit.c matedit.c mpi_edit.c print.c printcyclefreq.c printcyclefreqs.c  \
	printmapping.c printnodelist.c printspec.c printtimefreq.c printtimefreqs.c  \
	printtimeplot.c printtimeplots.c printtpcurve.c printtpcurves.c query_timer.c  \
	reducevar.c regedit.c regenrgy2d.c regenrgy3d.c stateedit.c  

depend:
	@cp -f Makefile.edits Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(editor.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(editor.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(editor.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(editor.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(editor.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(editor.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(editor.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(editor.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(editor.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(editor.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(editor.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(editor.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(editor.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(editor.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(editor.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(editor.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(editor.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(editor.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(editor.o): /usr/include/ctype.h /usr/include/math.h
$(B)(editor.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(editor.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(editor.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(editor.o): ../../includes/Region.h ../../includes/irscom.h
$(B)(editor.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(editor.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(editor.o): ../../includes/irsedits.h ../../includes/irsrgst.h
$(B)(editor.o): ../../includes/ProblemArray.h
$(B)(flagedit.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(flagedit.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(flagedit.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(flagedit.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(flagedit.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(flagedit.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(flagedit.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(flagedit.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(flagedit.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(flagedit.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(flagedit.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(flagedit.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(flagedit.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(flagedit.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(flagedit.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(flagedit.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(flagedit.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(flagedit.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(flagedit.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(flagedit.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(flagedit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(flagedit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(flagedit.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(flagedit.o): ../../includes/irsparm.h
$(B)(matedit.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(matedit.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(matedit.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(matedit.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(matedit.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(matedit.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(matedit.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(matedit.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(matedit.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(matedit.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(matedit.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(matedit.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(matedit.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(matedit.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(matedit.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(matedit.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(matedit.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(matedit.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(matedit.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(matedit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(matedit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(matedit.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(matedit.o): ../../includes/irseos.h ../../includes/Region.h
$(B)(matedit.o): ../../includes/Thermo.h ../../includes/irsreg.h
$(B)(mpi_edit.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(mpi_edit.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(mpi_edit.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(mpi_edit.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(mpi_edit.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(mpi_edit.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(mpi_edit.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(mpi_edit.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(mpi_edit.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(mpi_edit.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(mpi_edit.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(mpi_edit.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(mpi_edit.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(mpi_edit.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(mpi_edit.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(mpi_edit.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(mpi_edit.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(mpi_edit.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(mpi_edit.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(mpi_edit.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(mpi_edit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(mpi_edit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(mpi_edit.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(mpi_edit.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(mpi_edit.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(mpi_edit.o): ../../includes/irsedits.h ../../includes/AEStackElm.h
$(B)(print.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(print.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(print.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(print.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(print.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(print.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(print.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(print.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(print.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(print.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(print.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(print.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(print.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(print.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(print.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(print.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(print.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(print.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(print.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(print.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(print.o): /usr/include/string.h /usr/include/malloc.h
$(B)(print.o): ../../includes/irsedits.h
$(B)(printcyclefreq.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printcyclefreq.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printcyclefreq.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printcyclefreq.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printcyclefreq.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printcyclefreq.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printcyclefreq.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printcyclefreq.o): /usr/include/bits/stdio_lim.h
$(B)(printcyclefreq.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(printcyclefreq.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(printcyclefreq.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(printcyclefreq.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(printcyclefreq.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(printcyclefreq.o): /usr/include/sys/sysmacros.h
$(B)(printcyclefreq.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printcyclefreq.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printcyclefreq.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printcyclefreq.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printcyclefreq.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printcyclefreq.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printcyclefreq.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printcyclefreq.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printcyclefreq.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printcyclefreq.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printcyclefreq.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printcyclefreq.o): ../../includes/CycleMesg.h
$(B)(printcyclefreqs.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printcyclefreqs.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printcyclefreqs.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printcyclefreqs.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printcyclefreqs.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printcyclefreqs.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printcyclefreqs.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printcyclefreqs.o): /usr/include/bits/stdio_lim.h
$(B)(printcyclefreqs.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(printcyclefreqs.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(printcyclefreqs.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(printcyclefreqs.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(printcyclefreqs.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(printcyclefreqs.o): /usr/include/sys/sysmacros.h
$(B)(printcyclefreqs.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printcyclefreqs.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printcyclefreqs.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printcyclefreqs.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printcyclefreqs.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printcyclefreqs.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printcyclefreqs.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printcyclefreqs.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printcyclefreqs.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printcyclefreqs.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printcyclefreqs.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printmapping.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printmapping.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printmapping.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printmapping.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printmapping.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printmapping.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printmapping.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printmapping.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(printmapping.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(printmapping.o): /usr/include/time.h /usr/include/endian.h
$(B)(printmapping.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(printmapping.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(printmapping.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(printmapping.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printmapping.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printmapping.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printmapping.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printmapping.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printmapping.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printmapping.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printmapping.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printmapping.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printmapping.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printmapping.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printnodelist.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printnodelist.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printnodelist.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printnodelist.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printnodelist.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printnodelist.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printnodelist.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printnodelist.o): /usr/include/bits/stdio_lim.h
$(B)(printnodelist.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(printnodelist.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(printnodelist.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(printnodelist.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(printnodelist.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(printnodelist.o): /usr/include/sys/sysmacros.h
$(B)(printnodelist.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printnodelist.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printnodelist.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printnodelist.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printnodelist.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printnodelist.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printnodelist.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printnodelist.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printnodelist.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printnodelist.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printnodelist.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printnodelist.o): ../../includes/irsrgst.h ../../includes/NodeList.h
$(B)(printnodelist.o): ../../includes/Extents.h
$(B)(printspec.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printspec.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printspec.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printspec.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printspec.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printspec.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printspec.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printspec.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(printspec.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(printspec.o): /usr/include/time.h /usr/include/endian.h
$(B)(printspec.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(printspec.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(printspec.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(printspec.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printspec.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printspec.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printspec.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printspec.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printspec.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printspec.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printspec.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printspec.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printspec.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printspec.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printtimefreq.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printtimefreq.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printtimefreq.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printtimefreq.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printtimefreq.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printtimefreq.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printtimefreq.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printtimefreq.o): /usr/include/bits/stdio_lim.h
$(B)(printtimefreq.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(printtimefreq.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(printtimefreq.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(printtimefreq.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(printtimefreq.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(printtimefreq.o): /usr/include/sys/sysmacros.h
$(B)(printtimefreq.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printtimefreq.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printtimefreq.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printtimefreq.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printtimefreq.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printtimefreq.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printtimefreq.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printtimefreq.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printtimefreq.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printtimefreq.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printtimefreq.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printtimefreq.o): ../../includes/FreqMesg.h
$(B)(printtimefreqs.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printtimefreqs.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printtimefreqs.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printtimefreqs.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printtimefreqs.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printtimefreqs.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printtimefreqs.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printtimefreqs.o): /usr/include/bits/stdio_lim.h
$(B)(printtimefreqs.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(printtimefreqs.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(printtimefreqs.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(printtimefreqs.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(printtimefreqs.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(printtimefreqs.o): /usr/include/sys/sysmacros.h
$(B)(printtimefreqs.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printtimefreqs.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printtimefreqs.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printtimefreqs.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printtimefreqs.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printtimefreqs.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printtimefreqs.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printtimefreqs.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printtimefreqs.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printtimefreqs.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printtimefreqs.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printtimeplot.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printtimeplot.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printtimeplot.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printtimeplot.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printtimeplot.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printtimeplot.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printtimeplot.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printtimeplot.o): /usr/include/bits/stdio_lim.h
$(B)(printtimeplot.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(printtimeplot.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(printtimeplot.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(printtimeplot.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(printtimeplot.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(printtimeplot.o): /usr/include/sys/sysmacros.h
$(B)(printtimeplot.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printtimeplot.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printtimeplot.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printtimeplot.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printtimeplot.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printtimeplot.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printtimeplot.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printtimeplot.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printtimeplot.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printtimeplot.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printtimeplot.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printtimeplot.o): ../../includes/TimePlot.h ../../includes/FreqMesg.h
$(B)(printtimeplot.o): ../../includes/CycleMesg.h
$(B)(printtimeplots.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printtimeplots.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printtimeplots.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printtimeplots.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printtimeplots.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printtimeplots.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printtimeplots.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printtimeplots.o): /usr/include/bits/stdio_lim.h
$(B)(printtimeplots.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(printtimeplots.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(printtimeplots.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(printtimeplots.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(printtimeplots.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(printtimeplots.o): /usr/include/sys/sysmacros.h
$(B)(printtimeplots.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printtimeplots.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printtimeplots.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printtimeplots.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printtimeplots.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printtimeplots.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printtimeplots.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printtimeplots.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printtimeplots.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printtimeplots.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printtimeplots.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printtpcurve.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printtpcurve.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printtpcurve.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printtpcurve.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printtpcurve.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printtpcurve.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printtpcurve.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printtpcurve.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(printtpcurve.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(printtpcurve.o): /usr/include/time.h /usr/include/endian.h
$(B)(printtpcurve.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(printtpcurve.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(printtpcurve.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(printtpcurve.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printtpcurve.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printtpcurve.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printtpcurve.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printtpcurve.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printtpcurve.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printtpcurve.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printtpcurve.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printtpcurve.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printtpcurve.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printtpcurve.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printtpcurve.o): ../../includes/TimePlot.h ../../includes/FreqMesg.h
$(B)(printtpcurve.o): ../../includes/CycleMesg.h
$(B)(printtpcurves.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(printtpcurves.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(printtpcurves.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(printtpcurves.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(printtpcurves.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(printtpcurves.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(printtpcurves.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(printtpcurves.o): /usr/include/bits/stdio_lim.h
$(B)(printtpcurves.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(printtpcurves.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(printtpcurves.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(printtpcurves.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(printtpcurves.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(printtpcurves.o): /usr/include/sys/sysmacros.h
$(B)(printtpcurves.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(printtpcurves.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(printtpcurves.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(printtpcurves.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(printtpcurves.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(printtpcurves.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(printtpcurves.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(printtpcurves.o): /usr/include/ctype.h /usr/include/math.h
$(B)(printtpcurves.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(printtpcurves.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(printtpcurves.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(printtpcurves.o): ../../includes/TimePlot.h ../../includes/FreqMesg.h
$(B)(printtpcurves.o): ../../includes/CycleMesg.h
$(B)(query_timer.o): /usr/include/ctype.h /usr/include/features.h
$(B)(query_timer.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(query_timer.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(query_timer.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(query_timer.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(query_timer.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/libio.h
$(B)(query_timer.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(query_timer.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(query_timer.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(query_timer.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(query_timer.o): /usr/include/time.h /usr/include/sys/select.h
$(B)(query_timer.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(query_timer.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(query_timer.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(query_timer.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(query_timer.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(query_timer.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(query_timer.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(query_timer.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(query_timer.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(query_timer.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(query_timer.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(query_timer.o): /usr/include/string.h /usr/include/malloc.h
$(B)(query_timer.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(query_timer.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(query_timer.o): ../../includes/Extents.h ../../includes/irsedits.h
$(B)(query_timer.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(query_timer.o): ../../includes/AEStackElm.h
$(B)(reducevar.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(reducevar.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(reducevar.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(reducevar.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(reducevar.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(reducevar.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(reducevar.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(reducevar.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(reducevar.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(reducevar.o): /usr/include/time.h /usr/include/endian.h
$(B)(reducevar.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(reducevar.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(reducevar.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(reducevar.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(reducevar.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(reducevar.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(reducevar.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(reducevar.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(reducevar.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(reducevar.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(reducevar.o): /usr/include/ctype.h /usr/include/math.h
$(B)(reducevar.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(reducevar.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(reducevar.o): /usr/include/malloc.h ../../includes/irsgen.h
$(B)(reducevar.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(reducevar.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(reducevar.o): ../../includes/FunctionTimer.h ../../includes/irsedits.h
$(B)(reducevar.o): ../../includes/irsrgst.h ../../includes/irsreg.h
$(B)(reducevar.o): ../../includes/Region.h ../../includes/ProblemArray.h
$(B)(reducevar.o): ../../includes/UserList.h
$(B)(regedit.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(regedit.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(regedit.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(regedit.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(regedit.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(regedit.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(regedit.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(regedit.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(regedit.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(regedit.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(regedit.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(regedit.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(regedit.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(regedit.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(regedit.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(regedit.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(regedit.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(regedit.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(regedit.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(regedit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(regedit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(regedit.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(regedit.o): ../../includes/irsreg.h ../../includes/Region.h
$(B)(regedit.o): ../../includes/ProblemArray.h
$(B)(regenrgy2d.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(regenrgy2d.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(regenrgy2d.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(regenrgy2d.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(regenrgy2d.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(regenrgy2d.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(regenrgy2d.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(regenrgy2d.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(regenrgy2d.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(regenrgy2d.o): /usr/include/time.h /usr/include/endian.h
$(B)(regenrgy2d.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(regenrgy2d.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(regenrgy2d.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(regenrgy2d.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(regenrgy2d.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(regenrgy2d.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(regenrgy2d.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(regenrgy2d.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(regenrgy2d.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(regenrgy2d.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(regenrgy2d.o): /usr/include/ctype.h /usr/include/math.h
$(B)(regenrgy2d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(regenrgy2d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(regenrgy2d.o): /usr/include/malloc.h ../../includes/irsedits.h
$(B)(regenrgy2d.o): ../../includes/irsreg.h ../../includes/Region.h
$(B)(regenrgy2d.o): ../../includes/ProblemArray.h ../../includes/FunctionTimer.h
$(B)(regenrgy3d.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(regenrgy3d.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(regenrgy3d.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(regenrgy3d.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(regenrgy3d.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(regenrgy3d.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(regenrgy3d.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(regenrgy3d.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(regenrgy3d.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(regenrgy3d.o): /usr/include/time.h /usr/include/endian.h
$(B)(regenrgy3d.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(regenrgy3d.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(regenrgy3d.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(regenrgy3d.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(regenrgy3d.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(regenrgy3d.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(regenrgy3d.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(regenrgy3d.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(regenrgy3d.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(regenrgy3d.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(regenrgy3d.o): /usr/include/ctype.h /usr/include/math.h
$(B)(regenrgy3d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(regenrgy3d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(regenrgy3d.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(regenrgy3d.o): ../../includes/Region.h ../../includes/irsedits.h
$(B)(regenrgy3d.o): ../../includes/ProblemArray.h ../../includes/FunctionTimer.h
$(B)(stateedit.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(stateedit.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(stateedit.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(stateedit.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(stateedit.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(stateedit.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(stateedit.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(stateedit.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(stateedit.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(stateedit.o): /usr/include/time.h /usr/include/endian.h
$(B)(stateedit.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(stateedit.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(stateedit.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(stateedit.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(stateedit.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(stateedit.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(stateedit.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(stateedit.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(stateedit.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(stateedit.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(stateedit.o): /usr/include/ctype.h /usr/include/math.h
$(B)(stateedit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(stateedit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(stateedit.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(stateedit.o): ../../includes/State.h ../../includes/irsbndry.h
$(B)(stateedit.o): ../../includes/irsedits.h ../../includes/irsparm.h
$(B)(stateedit.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
