
################################################################################
#
# Makefile for irs library gen
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
B = ../$(LIB_DIR)/libgen.a
BI = ../$(LIB_DIR)/libgen_inst.a

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
SRCDIR = ../sources/gen

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libgen:$(B)(altmesh.o) $(B)(arcal2ds.o) $(B)(doarg.o) $(B)(dopa.o)                \
	  $(B)(fillvar.o) $(B)(gen.o) $(B)(getarg.o) $(B)(getematblk.o)           \
	  $(B)(getfarg.o) $(B)(getfpaa.o) $(B)(getiarg.o) $(B)(getrgstdata.o)     \
	  $(B)(getspeed2.o) $(B)(gnorm.o) $(B)(isargfun.o) $(B)(isbeta.o)         \
	  $(B)(meshgen.o) $(B)(mixzn.o) $(B)(mkpalab.o) $(B)(plgndr.o)            \
	  $(B)(pole.o) $(B)(purify.o) $(B)(ratioeval.o) $(B)(ratiosum.o)          \
	  $(B)(rdmesh.o) $(B)(rdsilogrid.o) $(B)(rdtruegrid.o) $(B)(realindex.o)  \
	  $(B)(regen.o) $(B)(sanityck.o) $(B)(sewmeshes.o) $(B)(spline.o)         \
	  $(B)(tagvoid.o) $(B)(volcal2d.o) $(B)(volcal3d.o) $(B)(wtmesh.o)        \
	  $(B)(zone.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'gen library current'

# creation deps
#---------------
$(B)(altmesh.o):altmesh.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/altmesh.c $(DB)/altmesh.c 

$(B)(arcal2ds.o):arcal2ds.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/arcal2ds.c $(DB)/arcal2ds.c 

$(B)(doarg.o):doarg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/doarg.c $(DB)/doarg.c 

$(B)(dopa.o):dopa.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/dopa.c $(DB)/dopa.c 

$(B)(fillvar.o):fillvar.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/fillvar.c $(DB)/fillvar.c 

../../includes/irsgen.hh:../../includes/irsgen.h
	cp ../../includes/irsgen.h ../../includes/irsgen.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irsgen.hh
	irs_hhinit ../../includes/irsgen.hh

$(B)(gen.o):../../includes/irsgen.hh

$(B)(gen.o):gen.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/gen.c $(DB)/gen.c 

$(B)(getarg.o):getarg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getarg.c $(DB)/getarg.c 

$(B)(getematblk.o):getematblk.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getematblk.c $(DB)/getematblk.c 

$(B)(getfarg.o):getfarg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getfarg.c $(DB)/getfarg.c 

$(B)(getfpaa.o):getfpaa.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getfpaa.c $(DB)/getfpaa.c 

$(B)(getiarg.o):getiarg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getiarg.c $(DB)/getiarg.c 

$(B)(getrgstdata.o):getrgstdata.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getrgstdata.c $(DB)/getrgstdata.c 

$(B)(getspeed2.o):getspeed2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getspeed2.c $(DB)/getspeed2.c 

$(B)(gnorm.o):gnorm.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/gnorm.c $(DB)/gnorm.c 

$(B)(isargfun.o):isargfun.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/isargfun.c $(DB)/isargfun.c 

$(B)(isbeta.o):isbeta.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/isbeta.c $(DB)/isbeta.c 

$(B)(meshgen.o):meshgen.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/meshgen.c $(DB)/meshgen.c 

$(B)(mixzn.o):mixzn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/mixzn.c $(DB)/mixzn.c 

$(B)(mkpalab.o):mkpalab.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/mkpalab.c $(DB)/mkpalab.c 

$(B)(plgndr.o):plgndr.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/plgndr.c $(DB)/plgndr.c 

$(B)(pole.o):pole.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/pole.c $(DB)/pole.c 

$(B)(purify.o):purify.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/purify.c $(DB)/purify.c 

$(B)(ratioeval.o):ratioeval.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ratioeval.c $(DB)/ratioeval.c 

$(B)(ratiosum.o):ratiosum.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ratiosum.c $(DB)/ratiosum.c 

$(B)(rdmesh.o):rdmesh.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdmesh.c $(DB)/rdmesh.c 

$(B)(rdsilogrid.o):rdsilogrid.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdsilogrid.c $(DB)/rdsilogrid.c 

$(B)(rdtruegrid.o):rdtruegrid.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdtruegrid.c $(DB)/rdtruegrid.c 

$(B)(realindex.o):realindex.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/realindex.c $(DB)/realindex.c 

$(B)(regen.o):regen.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/regen.c $(DB)/regen.c 

$(B)(sanityck.o):sanityck.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/sanityck.c $(DB)/sanityck.c 

$(B)(sewmeshes.o):sewmeshes.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/sewmeshes.c $(DB)/sewmeshes.c 

$(B)(spline.o):spline.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/spline.c $(DB)/spline.c 

$(B)(tagvoid.o):tagvoid.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tagvoid.c $(DB)/tagvoid.c 

$(B)(volcal2d.o):volcal2d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/volcal2d.c $(DB)/volcal2d.c 

$(B)(volcal3d.o):volcal3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/volcal3d.c $(DB)/volcal3d.c 

$(B)(wtmesh.o):wtmesh.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/wtmesh.c $(DB)/wtmesh.c 

$(B)(zone.o):zone.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/zone.c $(DB)/zone.c 

#---------------------
# lint pass one target 
#---------------------
lint:altmesh.ln arcal2ds.ln doarg.ln dopa.ln fillvar.ln gen.ln getarg.ln          \
	  getematblk.ln getfarg.ln getfpaa.ln getiarg.ln getrgstdata.ln           \
	  getspeed2.ln gnorm.ln isargfun.ln isbeta.ln meshgen.ln mixzn.ln         \
	  mkpalab.ln plgndr.ln pole.ln purify.ln ratioeval.ln ratiosum.ln         \
	  rdmesh.ln rdsilogrid.ln rdtruegrid.ln realindex.ln regen.ln sanityck.ln \
	  sewmeshes.ln spline.ln tagvoid.ln volcal2d.ln volcal3d.ln wtmesh.ln     \
	  zone.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
altmesh.ln:altmesh.c ../../includes/irs.h ../../includes/irsblk.h                 \
	  ../../includes/irsgen.h ../../includes/irsreg.h                         \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Extents.h ../../includes/NodeList.h                      \
	  ../../includes/Hash.h ../../includes/ProblemArray.h                     \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON altmesh.c ***' >> $(LO)
	$$irs_lint altmesh.c 2>&1 | tee -a $(LO)

arcal2ds.ln:arcal2ds.c ../../includes/irs.h ../../includes/irsgen.h               \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON arcal2ds.c ***' >> $(LO)
	$$irs_lint arcal2ds.c 2>&1 | tee -a $(LO)

doarg.ln:doarg.c ../../includes/irs.h ../../includes/irsgen.h                     \
	  ../../includes/irsctl.h ../../includes/Spline.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON doarg.c ***' >> $(LO)
	$$irs_lint doarg.c 2>&1 | tee -a $(LO)

dopa.ln:dopa.c ../../includes/irs.h ../../includes/irscom.h                       \
	  ../../includes/irscur.h ../../includes/irsgen.h                         \
	  ../../includes/irsrgst.h ../../includes/NodeList.h                      \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON dopa.c ***' >> $(LO)
	$$irs_lint dopa.c 2>&1 | tee -a $(LO)

fillvar.ln:fillvar.c ../../includes/irs.h ../../includes/irsbndry.h               \
	  ../../includes/irsctl.h ../../includes/irsedits.h                       \
	  ../../includes/irsgen.h ../../includes/irsreg.h                         \
	  ../../includes/irsrgst.h ../../includes/irssys.h                        \
	  ../../includes/Spline.h ../../includes/NodeList.h                       \
	  ../../includes/ProblemArray.h ../../includes/UserList.h                 \
	  ../../includes/Transform.h ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON fillvar.c ***' >> $(LO)
	$$irs_lint fillvar.c 2>&1 | tee -a $(LO)

gen.ln:gen.c ../../includes/irs.h ../../includes/irsblk.h                         \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsdmp.h ../../includes/irsedits.h                       \
	  ../../includes/irseos.h ../../includes/irsgen.h ../../includes/irslag.h \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/Command.h ../../includes/FunctionTimer.h                 \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/TimeStepControl.h ../../includes/irsgen.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON gen.c ***' >> $(LO)
	$$irs_lint gen.c 2>&1 | tee -a $(LO)

getarg.ln:getarg.c ../../includes/irs.h ../../includes/irsgen.h                   \
	  ../../includes/irsrgst.h ../../includes/ProblemArray.h                  \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getarg.c ***' >> $(LO)
	$$irs_lint getarg.c 2>&1 | tee -a $(LO)

getematblk.ln:getematblk.c ../../includes/irs.h ../../includes/irsreg.h           \
	  ../../includes/irsgen.h ../../includes/irseos.h                         \
	  ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getematblk.c ***' >> $(LO)
	$$irs_lint getematblk.c 2>&1 | tee -a $(LO)

getfarg.ln:getfarg.c ../../includes/irs.h ../../includes/irsgen.h                 \
	  ../../includes/irsrgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getfarg.c ***' >> $(LO)
	$$irs_lint getfarg.c 2>&1 | tee -a $(LO)

getfpaa.ln:getfpaa.c ../../includes/irs.h ../../includes/irsgen.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h                  \
	  ../../includes/irsrgst.h ../../includes/NodeList.h                      \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getfpaa.c ***' >> $(LO)
	$$irs_lint getfpaa.c 2>&1 | tee -a $(LO)

getiarg.ln:getiarg.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getiarg.c ***' >> $(LO)
	$$irs_lint getiarg.c 2>&1 | tee -a $(LO)

getrgstdata.ln:getrgstdata.c ../../includes/irs.h ../../includes/irsgen.h         \
	  ../../includes/irsrgst.h ../../includes/AEStackElm.h                    \
	  ../../includes/Command.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getrgstdata.c ***' >> $(LO)
	$$irs_lint getrgstdata.c 2>&1 | tee -a $(LO)

getspeed2.ln:getspeed2.c ../../includes/irs.h ../../includes/irsgen.h             \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getspeed2.c ***' >> $(LO)
	$$irs_lint getspeed2.c 2>&1 | tee -a $(LO)

gnorm.ln:gnorm.c ../../includes/irs.h ../../includes/irsgen.h                     \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON gnorm.c ***' >> $(LO)
	$$irs_lint gnorm.c 2>&1 | tee -a $(LO)

isargfun.ln:isargfun.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON isargfun.c ***' >> $(LO)
	$$irs_lint isargfun.c 2>&1 | tee -a $(LO)

isbeta.ln:isbeta.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON isbeta.c ***' >> $(LO)
	$$irs_lint isbeta.c 2>&1 | tee -a $(LO)

meshgen.ln:meshgen.c ../../includes/irs.h ../../includes/irsbndry.h               \
	  ../../includes/irscom.h ../../includes/irsctl.h ../../includes/irsgen.h \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/Extents.h ../../includes/NodeList.h                      \
	  ../../includes/Spline.h ../../includes/FunctionTimer.h                  \
	  ../../includes/GbndList.h ../../includes/Transform.h                    \
	  ../../includes/UserList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON meshgen.c ***' >> $(LO)
	$$irs_lint meshgen.c 2>&1 | tee -a $(LO)

mixzn.ln:mixzn.c ../../includes/irs.h ../../includes/irsgen.h                     \
	  ../../includes/BlockMapping.h ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON mixzn.c ***' >> $(LO)
	$$irs_lint mixzn.c 2>&1 | tee -a $(LO)

mkpalab.ln:mkpalab.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON mkpalab.c ***' >> $(LO)
	$$irs_lint mkpalab.c 2>&1 | tee -a $(LO)

plgndr.ln:plgndr.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON plgndr.c ***' >> $(LO)
	$$irs_lint plgndr.c 2>&1 | tee -a $(LO)

pole.ln:pole.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON pole.c ***' >> $(LO)
	$$irs_lint pole.c 2>&1 | tee -a $(LO)

purify.ln:purify.c ../../includes/irs.h ../../includes/irsgen.h                   \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON purify.c ***' >> $(LO)
	$$irs_lint purify.c 2>&1 | tee -a $(LO)

ratioeval.ln:ratioeval.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ratioeval.c ***' >> $(LO)
	$$irs_lint ratioeval.c 2>&1 | tee -a $(LO)

ratiosum.ln:ratiosum.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ratiosum.c ***' >> $(LO)
	$$irs_lint ratiosum.c 2>&1 | tee -a $(LO)

rdmesh.ln:rdmesh.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdmesh.c ***' >> $(LO)
	$$irs_lint rdmesh.c 2>&1 | tee -a $(LO)

rdsilogrid.ln:rdsilogrid.c ../../includes/irs.h ../../includes/irsblk.h           \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsdmp.h ../../includes/irsgen.h                         \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdsilogrid.c ***' >> $(LO)
	$$irs_lint rdsilogrid.c 2>&1 | tee -a $(LO)

rdtruegrid.ln:rdtruegrid.c ../../includes/irs.h ../../includes/irsblk.h           \
	  ../../includes/irsdmp.h ../../includes/irsgen.h                         \
	  ../../includes/BndMapping.h ../../includes/BlockMapping.h               \
	  ../../includes/Hash.h ../../includes/Extents.h                          \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdtruegrid.c ***' >> $(LO)
	$$irs_lint rdtruegrid.c 2>&1 | tee -a $(LO)

realindex.ln:realindex.c ../../includes/irs.h ../../includes/irsgen.h             \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON realindex.c ***' >> $(LO)
	$$irs_lint realindex.c 2>&1 | tee -a $(LO)

regen.ln:regen.c ../../includes/irs.h ../../includes/irsblk.h                     \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsedits.h ../../includes/irsgen.h                       \
	  ../../includes/irsobjects.h ../../includes/irsparm.h                    \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/BlockMapping.h ../../includes/Command.h                  \
	  ../../includes/Domain.h ../../includes/FunctionTimer.h                  \
	  ../../includes/TimeStepControl.h ../../includes/Rgst.h                  \
	  ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON regen.c ***' >> $(LO)
	$$irs_lint regen.c 2>&1 | tee -a $(LO)

sanityck.ln:sanityck.c ../../includes/irs.h ../../includes/irsgen.h               \
	  ../../includes/irscom.h ../../includes/irsreg.h                         \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/FunctionTimer.h ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON sanityck.c ***' >> $(LO)
	$$irs_lint sanityck.c 2>&1 | tee -a $(LO)

sewmeshes.ln:sewmeshes.c ../../includes/irs.h ../../includes/irsrgst.h            \
	  ../../includes/irsblk.h ../../includes/irscom.h                         \
	  ../../includes/irsbndry.h ../../includes/irsdmp.h                       \
	  ../../includes/irsctl.h ../../includes/irsgen.h                         \
	  ../../includes/BndMapping.h ../../includes/BlockMapping.h               \
	  ../../includes/Extents.h ../../includes/Hash.h                          \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON sewmeshes.c ***' >> $(LO)
	$$irs_lint sewmeshes.c 2>&1 | tee -a $(LO)

spline.ln:spline.c ../../includes/irs.h ../../includes/irsgen.h                   \
	  ../../includes/irsctl.h ../../includes/irsrgst.h ../../includes/Rgst.h  \
	  ../../includes/Spline.h ../../includes/Hash.h ../../includes/NodeList.h \
	  ../../includes/Transform.h ../../includes/irs.h                         \
	  ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON spline.c ***' >> $(LO)
	$$irs_lint spline.c 2>&1 | tee -a $(LO)

tagvoid.ln:tagvoid.c ../../includes/irs.h ../../includes/irsgen.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tagvoid.c ***' >> $(LO)
	$$irs_lint tagvoid.c 2>&1 | tee -a $(LO)

volcal2d.ln:volcal2d.c ../../includes/irs.h ../../includes/irsgen.h               \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON volcal2d.c ***' >> $(LO)
	$$irs_lint volcal2d.c 2>&1 | tee -a $(LO)

volcal3d.ln:volcal3d.c ../../includes/irs.h ../../includes/irsgen.h               \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON volcal3d.c ***' >> $(LO)
	$$irs_lint volcal3d.c 2>&1 | tee -a $(LO)

wtmesh.ln:wtmesh.c ../../includes/irs.h ../../includes/irscom.h                   \
	  ../../includes/irsdmp.h ../../includes/irsgen.h                         \
	  ../../includes/Extents.h ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON wtmesh.c ***' >> $(LO)
	$$irs_lint wtmesh.c 2>&1 | tee -a $(LO)

zone.ln:zone.c ../../includes/irs.h ../../includes/irsgen.h                       \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON zone.c ***' >> $(LO)
	$$irs_lint zone.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/altmesh.inst.i $(PREDIR)/arcal2ds.inst.i                     \
	  $(PREDIR)/doarg.inst.i $(PREDIR)/dopa.inst.i $(PREDIR)/fillvar.inst.i   \
	  $(PREDIR)/gen.inst.i $(PREDIR)/getarg.inst.i                            \
	  $(PREDIR)/getematblk.inst.i $(PREDIR)/getfarg.inst.i                    \
	  $(PREDIR)/getfpaa.inst.i $(PREDIR)/getiarg.inst.i                       \
	  $(PREDIR)/getrgstdata.inst.i $(PREDIR)/getspeed2.inst.i                 \
	  $(PREDIR)/gnorm.inst.i $(PREDIR)/isargfun.inst.i                        \
	  $(PREDIR)/isbeta.inst.i $(PREDIR)/meshgen.inst.i $(PREDIR)/mixzn.inst.i \
	  $(PREDIR)/mkpalab.inst.i $(PREDIR)/plgndr.inst.i $(PREDIR)/pole.inst.i  \
	  $(PREDIR)/purify.inst.i $(PREDIR)/ratioeval.inst.i                      \
	  $(PREDIR)/ratiosum.inst.i $(PREDIR)/rdmesh.inst.i                       \
	  $(PREDIR)/rdsilogrid.inst.i $(PREDIR)/rdtruegrid.inst.i                 \
	  $(PREDIR)/realindex.inst.i $(PREDIR)/regen.inst.i                       \
	  $(PREDIR)/sanityck.inst.i $(PREDIR)/sewmeshes.inst.i                    \
	  $(PREDIR)/spline.inst.i $(PREDIR)/tagvoid.inst.i                        \
	  $(PREDIR)/volcal2d.inst.i $(PREDIR)/volcal3d.inst.i                     \
	  $(PREDIR)/wtmesh.inst.i $(PREDIR)/zone.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/altmesh.inst.i:altmesh.c ../../includes/irs.h ../../includes/irsblk.h   \
	  ../../includes/irsgen.h ../../includes/irsreg.h                         \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Extents.h ../../includes/NodeList.h                      \
	  ../../includes/Hash.h ../../includes/ProblemArray.h                     \
	  ../../includes/Rgst.h
	@rm -f altmesh.i
	$$irs_pre altmesh.c >> altmesh.i
	@mv -f altmesh.i $(PREDIR)/altmesh.inst.i

$(PREDIR)/arcal2ds.inst.i:arcal2ds.c ../../includes/irs.h ../../includes/irsgen.h \
	  ../../includes/FunctionTimer.h
	@rm -f arcal2ds.i
	$$irs_pre arcal2ds.c >> arcal2ds.i
	@mv -f arcal2ds.i $(PREDIR)/arcal2ds.inst.i

$(PREDIR)/doarg.inst.i:doarg.c ../../includes/irs.h ../../includes/irsgen.h       \
	  ../../includes/irsctl.h ../../includes/Spline.h
	@rm -f doarg.i
	$$irs_pre doarg.c >> doarg.i
	@mv -f doarg.i $(PREDIR)/doarg.inst.i

$(PREDIR)/dopa.inst.i:dopa.c ../../includes/irs.h ../../includes/irscom.h         \
	  ../../includes/irscur.h ../../includes/irsgen.h                         \
	  ../../includes/irsrgst.h ../../includes/NodeList.h                      \
	  ../../includes/ProblemArray.h
	@rm -f dopa.i
	$$irs_pre dopa.c >> dopa.i
	@mv -f dopa.i $(PREDIR)/dopa.inst.i

$(PREDIR)/fillvar.inst.i:fillvar.c ../../includes/irs.h ../../includes/irsbndry.h \
	  ../../includes/irsctl.h ../../includes/irsedits.h                       \
	  ../../includes/irsgen.h ../../includes/irsreg.h                         \
	  ../../includes/irsrgst.h ../../includes/irssys.h                        \
	  ../../includes/Spline.h ../../includes/NodeList.h                       \
	  ../../includes/ProblemArray.h ../../includes/UserList.h                 \
	  ../../includes/Transform.h ../../includes/Region.h
	@rm -f fillvar.i
	$$irs_pre fillvar.c >> fillvar.i
	@mv -f fillvar.i $(PREDIR)/fillvar.inst.i

$(PREDIR)/gen.inst.i:gen.c ../../includes/irs.h ../../includes/irsblk.h           \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsdmp.h ../../includes/irsedits.h                       \
	  ../../includes/irseos.h ../../includes/irsgen.h ../../includes/irslag.h \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/Command.h ../../includes/FunctionTimer.h                 \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/TimeStepControl.h ../../includes/irsgen.hh
	@rm -f gen.i
	$$irs_pre gen.c >> gen.i
	@mv -f gen.i $(PREDIR)/gen.inst.i

$(PREDIR)/getarg.inst.i:getarg.c ../../includes/irs.h ../../includes/irsgen.h     \
	  ../../includes/irsrgst.h ../../includes/ProblemArray.h                  \
	  ../../includes/Rgst.h
	@rm -f getarg.i
	$$irs_pre getarg.c >> getarg.i
	@mv -f getarg.i $(PREDIR)/getarg.inst.i

$(PREDIR)/getematblk.inst.i:getematblk.c ../../includes/irs.h                     \
	  ../../includes/irsreg.h ../../includes/irsgen.h ../../includes/irseos.h \
	  ../../includes/irstdiff.h
	@rm -f getematblk.i
	$$irs_pre getematblk.c >> getematblk.i
	@mv -f getematblk.i $(PREDIR)/getematblk.inst.i

$(PREDIR)/getfarg.inst.i:getfarg.c ../../includes/irs.h ../../includes/irsgen.h   \
	  ../../includes/irsrgst.h
	@rm -f getfarg.i
	$$irs_pre getfarg.c >> getfarg.i
	@mv -f getfarg.i $(PREDIR)/getfarg.inst.i

$(PREDIR)/getfpaa.inst.i:getfpaa.c ../../includes/irs.h ../../includes/irsgen.h   \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h                  \
	  ../../includes/irsrgst.h ../../includes/NodeList.h                      \
	  ../../includes/ProblemArray.h
	@rm -f getfpaa.i
	$$irs_pre getfpaa.c >> getfpaa.i
	@mv -f getfpaa.i $(PREDIR)/getfpaa.inst.i

$(PREDIR)/getiarg.inst.i:getiarg.c ../../includes/irs.h ../../includes/irsgen.h
	@rm -f getiarg.i
	$$irs_pre getiarg.c >> getiarg.i
	@mv -f getiarg.i $(PREDIR)/getiarg.inst.i

$(PREDIR)/getrgstdata.inst.i:getrgstdata.c ../../includes/irs.h                   \
	  ../../includes/irsgen.h ../../includes/irsrgst.h                        \
	  ../../includes/AEStackElm.h ../../includes/Command.h                    \
	  ../../includes/Rgst.h
	@rm -f getrgstdata.i
	$$irs_pre getrgstdata.c >> getrgstdata.i
	@mv -f getrgstdata.i $(PREDIR)/getrgstdata.inst.i

$(PREDIR)/getspeed2.inst.i:getspeed2.c ../../includes/irs.h                       \
	  ../../includes/irsgen.h ../../includes/FunctionTimer.h
	@rm -f getspeed2.i
	$$irs_pre getspeed2.c >> getspeed2.i
	@mv -f getspeed2.i $(PREDIR)/getspeed2.inst.i

$(PREDIR)/gnorm.inst.i:gnorm.c ../../includes/irs.h ../../includes/irsgen.h       \
	  ../../includes/NodeList.h
	@rm -f gnorm.i
	$$irs_pre gnorm.c >> gnorm.i
	@mv -f gnorm.i $(PREDIR)/gnorm.inst.i

$(PREDIR)/isargfun.inst.i:isargfun.c ../../includes/irs.h                         \
	  ../../includes/irsgen.h
	@rm -f isargfun.i
	$$irs_pre isargfun.c >> isargfun.i
	@mv -f isargfun.i $(PREDIR)/isargfun.inst.i

$(PREDIR)/isbeta.inst.i:isbeta.c ../../includes/irs.h ../../includes/irsgen.h
	@rm -f isbeta.i
	$$irs_pre isbeta.c >> isbeta.i
	@mv -f isbeta.i $(PREDIR)/isbeta.inst.i

$(PREDIR)/meshgen.inst.i:meshgen.c ../../includes/irs.h ../../includes/irsbndry.h \
	  ../../includes/irscom.h ../../includes/irsctl.h ../../includes/irsgen.h \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/Extents.h ../../includes/NodeList.h                      \
	  ../../includes/Spline.h ../../includes/FunctionTimer.h                  \
	  ../../includes/GbndList.h ../../includes/Transform.h                    \
	  ../../includes/UserList.h
	@rm -f meshgen.i
	$$irs_pre meshgen.c >> meshgen.i
	@mv -f meshgen.i $(PREDIR)/meshgen.inst.i

$(PREDIR)/mixzn.inst.i:mixzn.c ../../includes/irs.h ../../includes/irsgen.h       \
	  ../../includes/BlockMapping.h ../../includes/NodeList.h
	@rm -f mixzn.i
	$$irs_pre mixzn.c >> mixzn.i
	@mv -f mixzn.i $(PREDIR)/mixzn.inst.i

$(PREDIR)/mkpalab.inst.i:mkpalab.c ../../includes/irs.h ../../includes/irsgen.h
	@rm -f mkpalab.i
	$$irs_pre mkpalab.c >> mkpalab.i
	@mv -f mkpalab.i $(PREDIR)/mkpalab.inst.i

$(PREDIR)/plgndr.inst.i:plgndr.c ../../includes/irs.h ../../includes/irsgen.h
	@rm -f plgndr.i
	$$irs_pre plgndr.c >> plgndr.i
	@mv -f plgndr.i $(PREDIR)/plgndr.inst.i

$(PREDIR)/pole.inst.i:pole.c ../../includes/irs.h ../../includes/irsgen.h
	@rm -f pole.i
	$$irs_pre pole.c >> pole.i
	@mv -f pole.i $(PREDIR)/pole.inst.i

$(PREDIR)/purify.inst.i:purify.c ../../includes/irs.h ../../includes/irsgen.h     \
	  ../../includes/NodeList.h
	@rm -f purify.i
	$$irs_pre purify.c >> purify.i
	@mv -f purify.i $(PREDIR)/purify.inst.i

$(PREDIR)/ratioeval.inst.i:ratioeval.c ../../includes/irs.h                       \
	  ../../includes/irsgen.h
	@rm -f ratioeval.i
	$$irs_pre ratioeval.c >> ratioeval.i
	@mv -f ratioeval.i $(PREDIR)/ratioeval.inst.i

$(PREDIR)/ratiosum.inst.i:ratiosum.c ../../includes/irs.h                         \
	  ../../includes/irsgen.h
	@rm -f ratiosum.i
	$$irs_pre ratiosum.c >> ratiosum.i
	@mv -f ratiosum.i $(PREDIR)/ratiosum.inst.i

$(PREDIR)/rdmesh.inst.i:rdmesh.c ../../includes/irs.h ../../includes/irsgen.h
	@rm -f rdmesh.i
	$$irs_pre rdmesh.c >> rdmesh.i
	@mv -f rdmesh.i $(PREDIR)/rdmesh.inst.i

$(PREDIR)/rdsilogrid.inst.i:rdsilogrid.c ../../includes/irs.h                     \
	  ../../includes/irsblk.h ../../includes/irsbndry.h                       \
	  ../../includes/irscom.h ../../includes/irsdmp.h ../../includes/irsgen.h \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/NodeList.h
	@rm -f rdsilogrid.i
	$$irs_pre rdsilogrid.c >> rdsilogrid.i
	@mv -f rdsilogrid.i $(PREDIR)/rdsilogrid.inst.i

$(PREDIR)/rdtruegrid.inst.i:rdtruegrid.c ../../includes/irs.h                     \
	  ../../includes/irsblk.h ../../includes/irsdmp.h ../../includes/irsgen.h \
	  ../../includes/BndMapping.h ../../includes/BlockMapping.h               \
	  ../../includes/Hash.h ../../includes/Extents.h                          \
	  ../../includes/NodeList.h
	@rm -f rdtruegrid.i
	$$irs_pre rdtruegrid.c >> rdtruegrid.i
	@mv -f rdtruegrid.i $(PREDIR)/rdtruegrid.inst.i

$(PREDIR)/realindex.inst.i:realindex.c ../../includes/irs.h                       \
	  ../../includes/irsgen.h ../../includes/BlockMapping.h                   \
	  ../../includes/Extents.h ../../includes/NodeList.h
	@rm -f realindex.i
	$$irs_pre realindex.c >> realindex.i
	@mv -f realindex.i $(PREDIR)/realindex.inst.i

$(PREDIR)/regen.inst.i:regen.c ../../includes/irs.h ../../includes/irsblk.h       \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsedits.h ../../includes/irsgen.h                       \
	  ../../includes/irsobjects.h ../../includes/irsparm.h                    \
	  ../../includes/irsreg.h ../../includes/irsrgst.h                        \
	  ../../includes/BlockMapping.h ../../includes/Command.h                  \
	  ../../includes/Domain.h ../../includes/FunctionTimer.h                  \
	  ../../includes/TimeStepControl.h ../../includes/Rgst.h                  \
	  ../../includes/Region.h
	@rm -f regen.i
	$$irs_pre regen.c >> regen.i
	@mv -f regen.i $(PREDIR)/regen.inst.i

$(PREDIR)/sanityck.inst.i:sanityck.c ../../includes/irs.h ../../includes/irsgen.h \
	  ../../includes/irscom.h ../../includes/irsreg.h                         \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/FunctionTimer.h ../../includes/Region.h
	@rm -f sanityck.i
	$$irs_pre sanityck.c >> sanityck.i
	@mv -f sanityck.i $(PREDIR)/sanityck.inst.i

$(PREDIR)/sewmeshes.inst.i:sewmeshes.c ../../includes/irs.h                       \
	  ../../includes/irsrgst.h ../../includes/irsblk.h                        \
	  ../../includes/irscom.h ../../includes/irsbndry.h                       \
	  ../../includes/irsdmp.h ../../includes/irsctl.h ../../includes/irsgen.h \
	  ../../includes/BndMapping.h ../../includes/BlockMapping.h               \
	  ../../includes/Extents.h ../../includes/Hash.h                          \
	  ../../includes/NodeList.h
	@rm -f sewmeshes.i
	$$irs_pre sewmeshes.c >> sewmeshes.i
	@mv -f sewmeshes.i $(PREDIR)/sewmeshes.inst.i

$(PREDIR)/spline.inst.i:spline.c ../../includes/irs.h ../../includes/irsgen.h     \
	  ../../includes/irsctl.h ../../includes/irsrgst.h ../../includes/Rgst.h  \
	  ../../includes/Spline.h ../../includes/Hash.h ../../includes/NodeList.h \
	  ../../includes/Transform.h ../../includes/irs.h                         \
	  ../../includes/irsgen.h
	@rm -f spline.i
	$$irs_pre spline.c >> spline.i
	@mv -f spline.i $(PREDIR)/spline.inst.i

$(PREDIR)/tagvoid.inst.i:tagvoid.c ../../includes/irs.h ../../includes/irsgen.h
	@rm -f tagvoid.i
	$$irs_pre tagvoid.c >> tagvoid.i
	@mv -f tagvoid.i $(PREDIR)/tagvoid.inst.i

$(PREDIR)/volcal2d.inst.i:volcal2d.c ../../includes/irs.h ../../includes/irsgen.h \
	  ../../includes/FunctionTimer.h
	@rm -f volcal2d.i
	$$irs_pre volcal2d.c >> volcal2d.i
	@mv -f volcal2d.i $(PREDIR)/volcal2d.inst.i

$(PREDIR)/volcal3d.inst.i:volcal3d.c ../../includes/irs.h ../../includes/irsgen.h \
	  ../../includes/FunctionTimer.h
	@rm -f volcal3d.i
	$$irs_pre volcal3d.c >> volcal3d.i
	@mv -f volcal3d.i $(PREDIR)/volcal3d.inst.i

$(PREDIR)/wtmesh.inst.i:wtmesh.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/irsdmp.h ../../includes/irsgen.h                         \
	  ../../includes/Extents.h ../../includes/NodeList.h
	@rm -f wtmesh.i
	$$irs_pre wtmesh.c >> wtmesh.i
	@mv -f wtmesh.i $(PREDIR)/wtmesh.inst.i

$(PREDIR)/zone.inst.i:zone.c ../../includes/irs.h ../../includes/irsgen.h         \
	  ../../includes/NodeList.h
	@rm -f zone.i
	$$irs_pre zone.c >> zone.i
	@mv -f zone.i $(PREDIR)/zone.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libgen_inst

libgen_inst:$(BI)(altmesh.inst.o) $(BI)(arcal2ds.inst.o) $(BI)(doarg.inst.o)      \
	  $(BI)(dopa.inst.o) $(BI)(fillvar.inst.o) $(BI)(gen.inst.o)              \
	  $(BI)(getarg.inst.o) $(BI)(getematblk.inst.o) $(BI)(getfarg.inst.o)     \
	  $(BI)(getfpaa.inst.o) $(BI)(getiarg.inst.o) $(BI)(getrgstdata.inst.o)   \
	  $(BI)(getspeed2.inst.o) $(BI)(gnorm.inst.o) $(BI)(isargfun.inst.o)      \
	  $(BI)(isbeta.inst.o) $(BI)(meshgen.inst.o) $(BI)(mixzn.inst.o)          \
	  $(BI)(mkpalab.inst.o) $(BI)(plgndr.inst.o) $(BI)(pole.inst.o)           \
	  $(BI)(purify.inst.o) $(BI)(ratioeval.inst.o) $(BI)(ratiosum.inst.o)     \
	  $(BI)(rdmesh.inst.o) $(BI)(rdsilogrid.inst.o) $(BI)(rdtruegrid.inst.o)  \
	  $(BI)(realindex.inst.o) $(BI)(regen.inst.o) $(BI)(sanityck.inst.o)      \
	  $(BI)(sewmeshes.inst.o) $(BI)(spline.inst.o) $(BI)(tagvoid.inst.o)      \
	  $(BI)(volcal2d.inst.o) $(BI)(volcal3d.inst.o) $(BI)(wtmesh.inst.o)      \
	  $(BI)(zone.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libgen_inst.a $(B); \
		ln -sf libgen_inst.a $(B)); \
	  fi
	  @echo 'libgen_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(altmesh.inst.o):$(INSTDIR)/altmesh.inst.i
	$$irs_post $(INSTDIR)/altmesh.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/altmesh.inst.i $(DB)/altmesh.c 

$(BI)(arcal2ds.inst.o):$(INSTDIR)/arcal2ds.inst.i
	$$irs_post $(INSTDIR)/arcal2ds.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/arcal2ds.inst.i $(DB)/arcal2ds.c 

$(BI)(doarg.inst.o):$(INSTDIR)/doarg.inst.i
	$$irs_post $(INSTDIR)/doarg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/doarg.inst.i $(DB)/doarg.c 

$(BI)(dopa.inst.o):$(INSTDIR)/dopa.inst.i
	$$irs_post $(INSTDIR)/dopa.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/dopa.inst.i $(DB)/dopa.c 

$(BI)(fillvar.inst.o):$(INSTDIR)/fillvar.inst.i
	$$irs_post $(INSTDIR)/fillvar.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/fillvar.inst.i $(DB)/fillvar.c 

$(BI)(gen.inst.o):$(INSTDIR)/gen.inst.i
	$$irs_post $(INSTDIR)/gen.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/gen.inst.i $(DB)/gen.c 

$(BI)(getarg.inst.o):$(INSTDIR)/getarg.inst.i
	$$irs_post $(INSTDIR)/getarg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getarg.inst.i $(DB)/getarg.c 

$(BI)(getematblk.inst.o):$(INSTDIR)/getematblk.inst.i
	$$irs_post $(INSTDIR)/getematblk.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getematblk.inst.i $(DB)/getematblk.c 

$(BI)(getfarg.inst.o):$(INSTDIR)/getfarg.inst.i
	$$irs_post $(INSTDIR)/getfarg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getfarg.inst.i $(DB)/getfarg.c 

$(BI)(getfpaa.inst.o):$(INSTDIR)/getfpaa.inst.i
	$$irs_post $(INSTDIR)/getfpaa.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getfpaa.inst.i $(DB)/getfpaa.c 

$(BI)(getiarg.inst.o):$(INSTDIR)/getiarg.inst.i
	$$irs_post $(INSTDIR)/getiarg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getiarg.inst.i $(DB)/getiarg.c 

$(BI)(getrgstdata.inst.o):$(INSTDIR)/getrgstdata.inst.i
	$$irs_post $(INSTDIR)/getrgstdata.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getrgstdata.inst.i $(DB)/getrgstdata.c 

$(BI)(getspeed2.inst.o):$(INSTDIR)/getspeed2.inst.i
	$$irs_post $(INSTDIR)/getspeed2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getspeed2.inst.i $(DB)/getspeed2.c 

$(BI)(gnorm.inst.o):$(INSTDIR)/gnorm.inst.i
	$$irs_post $(INSTDIR)/gnorm.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/gnorm.inst.i $(DB)/gnorm.c 

$(BI)(isargfun.inst.o):$(INSTDIR)/isargfun.inst.i
	$$irs_post $(INSTDIR)/isargfun.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/isargfun.inst.i $(DB)/isargfun.c 

$(BI)(isbeta.inst.o):$(INSTDIR)/isbeta.inst.i
	$$irs_post $(INSTDIR)/isbeta.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/isbeta.inst.i $(DB)/isbeta.c 

$(BI)(meshgen.inst.o):$(INSTDIR)/meshgen.inst.i
	$$irs_post $(INSTDIR)/meshgen.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/meshgen.inst.i $(DB)/meshgen.c 

$(BI)(mixzn.inst.o):$(INSTDIR)/mixzn.inst.i
	$$irs_post $(INSTDIR)/mixzn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/mixzn.inst.i $(DB)/mixzn.c 

$(BI)(mkpalab.inst.o):$(INSTDIR)/mkpalab.inst.i
	$$irs_post $(INSTDIR)/mkpalab.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/mkpalab.inst.i $(DB)/mkpalab.c 

$(BI)(plgndr.inst.o):$(INSTDIR)/plgndr.inst.i
	$$irs_post $(INSTDIR)/plgndr.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/plgndr.inst.i $(DB)/plgndr.c 

$(BI)(pole.inst.o):$(INSTDIR)/pole.inst.i
	$$irs_post $(INSTDIR)/pole.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/pole.inst.i $(DB)/pole.c 

$(BI)(purify.inst.o):$(INSTDIR)/purify.inst.i
	$$irs_post $(INSTDIR)/purify.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/purify.inst.i $(DB)/purify.c 

$(BI)(ratioeval.inst.o):$(INSTDIR)/ratioeval.inst.i
	$$irs_post $(INSTDIR)/ratioeval.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ratioeval.inst.i $(DB)/ratioeval.c 

$(BI)(ratiosum.inst.o):$(INSTDIR)/ratiosum.inst.i
	$$irs_post $(INSTDIR)/ratiosum.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ratiosum.inst.i $(DB)/ratiosum.c 

$(BI)(rdmesh.inst.o):$(INSTDIR)/rdmesh.inst.i
	$$irs_post $(INSTDIR)/rdmesh.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdmesh.inst.i $(DB)/rdmesh.c 

$(BI)(rdsilogrid.inst.o):$(INSTDIR)/rdsilogrid.inst.i
	$$irs_post $(INSTDIR)/rdsilogrid.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdsilogrid.inst.i $(DB)/rdsilogrid.c 

$(BI)(rdtruegrid.inst.o):$(INSTDIR)/rdtruegrid.inst.i
	$$irs_post $(INSTDIR)/rdtruegrid.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdtruegrid.inst.i $(DB)/rdtruegrid.c 

$(BI)(realindex.inst.o):$(INSTDIR)/realindex.inst.i
	$$irs_post $(INSTDIR)/realindex.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/realindex.inst.i $(DB)/realindex.c 

$(BI)(regen.inst.o):$(INSTDIR)/regen.inst.i
	$$irs_post $(INSTDIR)/regen.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/regen.inst.i $(DB)/regen.c 

$(BI)(sanityck.inst.o):$(INSTDIR)/sanityck.inst.i
	$$irs_post $(INSTDIR)/sanityck.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/sanityck.inst.i $(DB)/sanityck.c 

$(BI)(sewmeshes.inst.o):$(INSTDIR)/sewmeshes.inst.i
	$$irs_post $(INSTDIR)/sewmeshes.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/sewmeshes.inst.i $(DB)/sewmeshes.c 

$(BI)(spline.inst.o):$(INSTDIR)/spline.inst.i
	$$irs_post $(INSTDIR)/spline.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/spline.inst.i $(DB)/spline.c 

$(BI)(tagvoid.inst.o):$(INSTDIR)/tagvoid.inst.i
	$$irs_post $(INSTDIR)/tagvoid.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tagvoid.inst.i $(DB)/tagvoid.c 

$(BI)(volcal2d.inst.o):$(INSTDIR)/volcal2d.inst.i
	$$irs_post $(INSTDIR)/volcal2d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/volcal2d.inst.i $(DB)/volcal2d.c 

$(BI)(volcal3d.inst.o):$(INSTDIR)/volcal3d.inst.i
	$$irs_post $(INSTDIR)/volcal3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/volcal3d.inst.i $(DB)/volcal3d.c 

$(BI)(wtmesh.inst.o):$(INSTDIR)/wtmesh.inst.i
	$$irs_post $(INSTDIR)/wtmesh.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/wtmesh.inst.i $(DB)/wtmesh.c 

$(BI)(zone.inst.o):$(INSTDIR)/zone.inst.i
	$$irs_post $(INSTDIR)/zone.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/zone.inst.i $(DB)/zone.c 

DEP_SRCS = \
	altmesh.c arcal2ds.c doarg.c dopa.c fillvar.c gen.c getarg.c getematblk.c  \
	getfarg.c getfpaa.c getiarg.c getrgstdata.c getspeed2.c gnorm.c isargfun.c  \
	isbeta.c meshgen.c mixzn.c mkpalab.c plgndr.c pole.c purify.c ratioeval.c  \
	ratiosum.c rdmesh.c rdsilogrid.c rdtruegrid.c realindex.c regen.c sanityck.c  \
	sewmeshes.c spline.c tagvoid.c volcal2d.c volcal3d.c wtmesh.c zone.c  

depend:
	@cp -f Makefile.gen Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

