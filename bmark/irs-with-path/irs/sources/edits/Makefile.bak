
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

