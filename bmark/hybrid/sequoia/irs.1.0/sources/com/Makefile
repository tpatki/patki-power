
################################################################################
#
# Makefile for irs library com
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
B = ../$(LIB_DIR)/libcom.a
BI = ../$(LIB_DIR)/libcom_inst.a

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
SRCDIR = ../sources/com

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libcom:$(B)(ComNodalZonal.o) $(B)(acumnm.o) $(B)(calculate_mappings.o)            \
	  $(B)(checkpara.o) $(B)(combarrier.o) $(B)(combcast.o) $(B)(combuf.o)    \
	  $(B)(comcleanup.o) $(B)(comgather.o) $(B)(comlen.o) $(B)(comlock.o)     \
	  $(B)(commpigather.o) $(B)(commpigatherv.o) $(B)(comreduce.o)            \
	  $(B)(comsummary.o) $(B)(comunlock.o) $(B)(comverify.o) $(B)(decomp.o)   \
	  $(B)(facecom.o) $(B)(getdata.o) $(B)(initcom.o) $(B)(matcom.o)          \
	  $(B)(putdata.o) $(B)(qbnd.o) $(B)(radcom.o) $(B)(rbndcom.o)             \
	  $(B)(setgmap.o) $(B)(setstdout.o) $(B)(setumap.o) $(B)(setvsamegrp.o)   \
	  $(B)(setvsameorder.o) $(B)(speccom.o) $(B)(swapcoords.o) $(B)(varcom.o) \
	  $(B)(vsamecom.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'com library current'

# creation deps
#---------------
$(B)(ComNodalZonal.o):ComNodalZonal.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ComNodalZonal.c $(DB)/ComNodalZonal.c 

$(B)(acumnm.o):acumnm.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/acumnm.c $(DB)/acumnm.c 

$(B)(calculate_mappings.o):calculate_mappings.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/calculate_mappings.c $(DB)/calculate_mappings.c 

$(B)(checkpara.o):checkpara.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/checkpara.c $(DB)/checkpara.c 

$(B)(combarrier.o):combarrier.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/combarrier.c $(DB)/combarrier.c 

$(B)(combcast.o):combcast.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/combcast.c $(DB)/combcast.c 

$(B)(combuf.o):combuf.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/combuf.c $(DB)/combuf.c 

$(B)(comcleanup.o):comcleanup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/comcleanup.c $(DB)/comcleanup.c 

$(B)(comgather.o):comgather.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/comgather.c $(DB)/comgather.c 

$(B)(comlen.o):comlen.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/comlen.c $(DB)/comlen.c 

$(B)(comlock.o):comlock.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/comlock.c $(DB)/comlock.c 

$(B)(commpigather.o):commpigather.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/commpigather.c $(DB)/commpigather.c 

$(B)(commpigatherv.o):commpigatherv.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/commpigatherv.c $(DB)/commpigatherv.c 

$(B)(comreduce.o):comreduce.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/comreduce.c $(DB)/comreduce.c 

$(B)(comsummary.o):comsummary.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/comsummary.c $(DB)/comsummary.c 

$(B)(comunlock.o):comunlock.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/comunlock.c $(DB)/comunlock.c 

$(B)(comverify.o):comverify.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/comverify.c $(DB)/comverify.c 

$(B)(decomp.o):decomp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/decomp.c $(DB)/decomp.c 

../../includes/Bndlist.hh:../../includes/Bndlist.h
	cp ../../includes/Bndlist.h ../../includes/Bndlist.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/Bndlist.hh
	irs_hhinit ../../includes/Bndlist.hh

$(B)(facecom.o):../../includes/Bndlist.hh

../../includes/VdenData.hh:../../includes/VdenData.h
	cp ../../includes/VdenData.h ../../includes/VdenData.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/VdenData.hh
	irs_hhinit ../../includes/VdenData.hh

$(B)(facecom.o):../../includes/VdenData.hh

$(B)(facecom.o):facecom.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/facecom.c $(DB)/facecom.c 

$(B)(getdata.o):getdata.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getdata.c $(DB)/getdata.c 

../../includes/irscom.hh:../../includes/irscom.h
	cp ../../includes/irscom.h ../../includes/irscom.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irscom.hh
	irs_hhinit ../../includes/irscom.hh

$(B)(initcom.o):../../includes/irscom.hh

../../includes/Tagorder.hh:../../includes/Tagorder.h
	cp ../../includes/Tagorder.h ../../includes/Tagorder.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/Tagorder.hh
	irs_hhinit ../../includes/Tagorder.hh

$(B)(initcom.o):../../includes/Tagorder.hh

$(B)(initcom.o):initcom.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/initcom.c $(DB)/initcom.c 

$(B)(matcom.o):matcom.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/matcom.c $(DB)/matcom.c 

$(B)(putdata.o):putdata.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/putdata.c $(DB)/putdata.c 

$(B)(qbnd.o):qbnd.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/qbnd.c $(DB)/qbnd.c 

$(B)(radcom.o):radcom.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/radcom.c $(DB)/radcom.c 

$(B)(rbndcom.o):rbndcom.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rbndcom.c $(DB)/rbndcom.c 

$(B)(setgmap.o):setgmap.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setgmap.c $(DB)/setgmap.c 

$(B)(setstdout.o):setstdout.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setstdout.c $(DB)/setstdout.c 

$(B)(setumap.o):setumap.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setumap.c $(DB)/setumap.c 

$(B)(setvsamegrp.o):setvsamegrp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setvsamegrp.c $(DB)/setvsamegrp.c 

$(B)(setvsameorder.o):setvsameorder.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setvsameorder.c $(DB)/setvsameorder.c 

$(B)(speccom.o):speccom.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/speccom.c $(DB)/speccom.c 

$(B)(swapcoords.o):swapcoords.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/swapcoords.c $(DB)/swapcoords.c 

$(B)(varcom.o):varcom.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/varcom.c $(DB)/varcom.c 

$(B)(vsamecom.o):vsamecom.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/vsamecom.c $(DB)/vsamecom.c 

#---------------------
# lint pass one target 
#---------------------
lint:ComNodalZonal.ln acumnm.ln calculate_mappings.ln checkpara.ln combarrier.ln  \
	  combcast.ln combuf.ln comcleanup.ln comgather.ln comlen.ln comlock.ln   \
	  commpigather.ln commpigatherv.ln comreduce.ln comsummary.ln             \
	  comunlock.ln comverify.ln decomp.ln facecom.ln getdata.ln initcom.ln    \
	  matcom.ln putdata.ln qbnd.ln radcom.ln rbndcom.ln setgmap.ln            \
	  setstdout.ln setumap.ln setvsamegrp.ln setvsameorder.ln speccom.ln      \
	  swapcoords.ln varcom.ln vsamecom.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
ComNodalZonal.ln:ComNodalZonal.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ComNodalZonal.c ***' >> $(LO)
	$$irs_lint ComNodalZonal.c 2>&1 | tee -a $(LO)

acumnm.ln:acumnm.c ../../includes/irs.h ../../includes/irscom.h                   \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON acumnm.c ***' >> $(LO)
	$$irs_lint acumnm.c 2>&1 | tee -a $(LO)

calculate_mappings.ln:calculate_mappings.c ../../includes/irs.h                   \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/BlockMapping.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON calculate_mappings.c ***' >> $(LO)
	$$irs_lint calculate_mappings.c 2>&1 | tee -a $(LO)

checkpara.ln:checkpara.c ../../includes/irs.h ../../includes/irsctl.h             \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON checkpara.c ***' >> $(LO)
	$$irs_lint checkpara.c 2>&1 | tee -a $(LO)

combarrier.ln:combarrier.c ../../includes/irs.h ../../includes/FunctionTimer.h    \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON combarrier.c ***' >> $(LO)
	$$irs_lint combarrier.c 2>&1 | tee -a $(LO)

combcast.ln:combcast.c ../../includes/irs.h ../../includes/FunctionTimer.h        \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON combcast.c ***' >> $(LO)
	$$irs_lint combcast.c 2>&1 | tee -a $(LO)

combuf.ln:combuf.c ../../includes/irs.h ../../includes/irscom.h                   \
	  ../../includes/BlockMapping.h ../../includes/FunctionTimer.h            \
	  ../../includes/Combuffer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON combuf.c ***' >> $(LO)
	$$irs_lint combuf.c 2>&1 | tee -a $(LO)

comcleanup.ln:comcleanup.c ../../includes/irs.h ../../includes/FunctionTimer.h    \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON comcleanup.c ***' >> $(LO)
	$$irs_lint comcleanup.c 2>&1 | tee -a $(LO)

comgather.ln:comgather.c ../../includes/irs.h ../../includes/irscom.h             \
	  ../../includes/irsrgst.h ../../includes/FunctionTimer.h                 \
	  ../../includes/NodeList.h ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON comgather.c ***' >> $(LO)
	$$irs_lint comgather.c 2>&1 | tee -a $(LO)

comlen.ln:comlen.c ../../includes/irs.h ../../includes/Boundary.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON comlen.c ***' >> $(LO)
	$$irs_lint comlen.c 2>&1 | tee -a $(LO)

comlock.ln:comlock.c ../../includes/irs.h ../../includes/FunctionTimer.h          \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON comlock.c ***' >> $(LO)
	$$irs_lint comlock.c 2>&1 | tee -a $(LO)

commpigather.ln:commpigather.c ../../includes/irs.h                               \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON commpigather.c ***' >> $(LO)
	$$irs_lint commpigather.c 2>&1 | tee -a $(LO)

commpigatherv.ln:commpigatherv.c ../../includes/irs.h                             \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON commpigatherv.c ***' >> $(LO)
	$$irs_lint commpigatherv.c 2>&1 | tee -a $(LO)

comreduce.ln:comreduce.c ../../includes/irs.h ../../includes/FunctionTimer.h      \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON comreduce.c ***' >> $(LO)
	$$irs_lint comreduce.c 2>&1 | tee -a $(LO)

comsummary.ln:comsummary.c ../../includes/irs.h ../../includes/FunctionTimer.h    \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON comsummary.c ***' >> $(LO)
	$$irs_lint comsummary.c 2>&1 | tee -a $(LO)

comunlock.ln:comunlock.c ../../includes/irs.h ../../includes/FunctionTimer.h      \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON comunlock.c ***' >> $(LO)
	$$irs_lint comunlock.c 2>&1 | tee -a $(LO)

comverify.ln:comverify.c ../../includes/irs.h ../../includes/FunctionTimer.h      \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON comverify.c ***' >> $(LO)
	$$irs_lint comverify.c 2>&1 | tee -a $(LO)

decomp.ln:decomp.c ../../includes/irs.h ../../includes/irscom.h                   \
	  ../../includes/BndMapping.h ../../includes/BlockMapping.h               \
	  ../../includes/Extents.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON decomp.c ***' >> $(LO)
	$$irs_lint decomp.c 2>&1 | tee -a $(LO)

facecom.ln:facecom.c ../../includes/irs.h ../../includes/irsbndry.h               \
	  ../../includes/irscom.h ../../includes/BlockMapping.h                   \
	  ../../includes/Boundary.h ../../includes/Bndlist.hh                     \
	  ../../includes/FunctionTimer.h ../../includes/VdenData.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON facecom.c ***' >> $(LO)
	$$irs_lint facecom.c 2>&1 | tee -a $(LO)

getdata.ln:getdata.c ../../includes/irs.h ../../includes/irscom.h                 \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getdata.c ***' >> $(LO)
	$$irs_lint getdata.c 2>&1 | tee -a $(LO)

initcom.ln:initcom.c ../../includes/irs.h ../../includes/irslag.h                 \
	  ../../includes/irsdmp.h ../../includes/irsedits.h                       \
	  ../../includes/irsrgst.h ../../includes/irscom.hh                       \
	  ../../includes/BlockMapping.h ../../includes/Command.h                  \
	  ../../includes/FunctionTimer.h ../../includes/Rgst.h                    \
	  ../../includes/Tagorder.hh ../../includes/TimeStepControl.h             \
	  ../../includes/Tracer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON initcom.c ***' >> $(LO)
	$$irs_lint initcom.c 2>&1 | tee -a $(LO)

matcom.ln:matcom.c ../../includes/irs.h ../../includes/irscom.h                   \
	  ../../includes/irsreg.h ../../includes/Boundary.h                       \
	  ../../includes/FunctionTimer.h ../../includes/SpeciesFraction.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON matcom.c ***' >> $(LO)
	$$irs_lint matcom.c 2>&1 | tee -a $(LO)

putdata.ln:putdata.c ../../includes/irs.h ../../includes/BlockMapping.h           \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON putdata.c ***' >> $(LO)
	$$irs_lint putdata.c 2>&1 | tee -a $(LO)

qbnd.ln:qbnd.c ../../includes/irs.h ../../includes/BlockMapping.h                 \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON qbnd.c ***' >> $(LO)
	$$irs_lint qbnd.c 2>&1 | tee -a $(LO)

radcom.ln:radcom.c ../../includes/irs.h ../../includes/BlockMapping.h             \
	  ../../includes/irscom.h ../../includes/Boundary.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON radcom.c ***' >> $(LO)
	$$irs_lint radcom.c 2>&1 | tee -a $(LO)

rbndcom.ln:rbndcom.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/irscom.h ../../includes/BlockMapping.h                   \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rbndcom.c ***' >> $(LO)
	$$irs_lint rbndcom.c 2>&1 | tee -a $(LO)

setgmap.ln:setgmap.c ../../includes/irs.h ../../includes/BlockMapping.h           \
	  ../../includes/BndMapping.h ../../includes/Extents.h                    \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setgmap.c ***' >> $(LO)
	$$irs_lint setgmap.c 2>&1 | tee -a $(LO)

setstdout.ln:setstdout.c ../../includes/irs.h ../../includes/FunctionTimer.h      \
	  ../../includes/irscom.h ../../includes/irsdmp.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setstdout.c ***' >> $(LO)
	$$irs_lint setstdout.c 2>&1 | tee -a $(LO)

setumap.ln:setumap.c ../../includes/irs.h ../../includes/BlockMapping.h           \
	  ../../includes/BndMapping.h ../../includes/Extents.h                    \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setumap.c ***' >> $(LO)
	$$irs_lint setumap.c 2>&1 | tee -a $(LO)

setvsamegrp.ln:setvsamegrp.c ../../includes/irs.h ../../includes/irscom.h         \
	  ../../includes/FunctionTimer.h ../../includes/Tagorder.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setvsamegrp.c ***' >> $(LO)
	$$irs_lint setvsamegrp.c 2>&1 | tee -a $(LO)

setvsameorder.ln:setvsameorder.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/FunctionTimer.h ../../includes/Tagorder.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setvsameorder.c ***' >> $(LO)
	$$irs_lint setvsameorder.c 2>&1 | tee -a $(LO)

speccom.ln:speccom.c ../../includes/irs.h ../../includes/irscom.h                 \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/Region.h ../../includes/SpeciesFraction.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON speccom.c ***' >> $(LO)
	$$irs_lint speccom.c 2>&1 | tee -a $(LO)

swapcoords.ln:swapcoords.c ../../includes/irs.h ../../includes/FunctionTimer.h    \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON swapcoords.c ***' >> $(LO)
	$$irs_lint swapcoords.c 2>&1 | tee -a $(LO)

varcom.ln:varcom.c ../../includes/irs.h ../../includes/BlockMapping.h             \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/irscom.h ../../includes/Hash.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON varcom.c ***' >> $(LO)
	$$irs_lint varcom.c 2>&1 | tee -a $(LO)

vsamecom.ln:vsamecom.c ../../includes/irs.h ../../includes/irscom.h               \
	  ../../includes/FunctionTimer.h ../../includes/Tagorder.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON vsamecom.c ***' >> $(LO)
	$$irs_lint vsamecom.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/ComNodalZonal.inst.i $(PREDIR)/acumnm.inst.i                 \
	  $(PREDIR)/calculate_mappings.inst.i $(PREDIR)/checkpara.inst.i          \
	  $(PREDIR)/combarrier.inst.i $(PREDIR)/combcast.inst.i                   \
	  $(PREDIR)/combuf.inst.i $(PREDIR)/comcleanup.inst.i                     \
	  $(PREDIR)/comgather.inst.i $(PREDIR)/comlen.inst.i                      \
	  $(PREDIR)/comlock.inst.i $(PREDIR)/commpigather.inst.i                  \
	  $(PREDIR)/commpigatherv.inst.i $(PREDIR)/comreduce.inst.i               \
	  $(PREDIR)/comsummary.inst.i $(PREDIR)/comunlock.inst.i                  \
	  $(PREDIR)/comverify.inst.i $(PREDIR)/decomp.inst.i                      \
	  $(PREDIR)/facecom.inst.i $(PREDIR)/getdata.inst.i                       \
	  $(PREDIR)/initcom.inst.i $(PREDIR)/matcom.inst.i                        \
	  $(PREDIR)/putdata.inst.i $(PREDIR)/qbnd.inst.i $(PREDIR)/radcom.inst.i  \
	  $(PREDIR)/rbndcom.inst.i $(PREDIR)/setgmap.inst.i                       \
	  $(PREDIR)/setstdout.inst.i $(PREDIR)/setumap.inst.i                     \
	  $(PREDIR)/setvsamegrp.inst.i $(PREDIR)/setvsameorder.inst.i             \
	  $(PREDIR)/speccom.inst.i $(PREDIR)/swapcoords.inst.i                    \
	  $(PREDIR)/varcom.inst.i $(PREDIR)/vsamecom.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/ComNodalZonal.inst.i:ComNodalZonal.c ../../includes/irs.h               \
	  ../../includes/irscom.h ../../includes/irsrgst.h                        \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h            \
	  ../../includes/Rgst.h
	@rm -f ComNodalZonal.i
	$$irs_pre ComNodalZonal.c >> ComNodalZonal.i
	@mv -f ComNodalZonal.i $(PREDIR)/ComNodalZonal.inst.i

$(PREDIR)/acumnm.inst.i:acumnm.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/FunctionTimer.h
	@rm -f acumnm.i
	$$irs_pre acumnm.c >> acumnm.i
	@mv -f acumnm.i $(PREDIR)/acumnm.inst.i

$(PREDIR)/calculate_mappings.inst.i:calculate_mappings.c ../../includes/irs.h     \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/BlockMapping.h
	@rm -f calculate_mappings.i
	$$irs_pre calculate_mappings.c >> calculate_mappings.i
	@mv -f calculate_mappings.i $(PREDIR)/calculate_mappings.inst.i

$(PREDIR)/checkpara.inst.i:checkpara.c ../../includes/irs.h                       \
	  ../../includes/irsctl.h ../../includes/FunctionTimer.h                  \
	  ../../includes/irscom.h
	@rm -f checkpara.i
	$$irs_pre checkpara.c >> checkpara.i
	@mv -f checkpara.i $(PREDIR)/checkpara.inst.i

$(PREDIR)/combarrier.inst.i:combarrier.c ../../includes/irs.h                     \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f combarrier.i
	$$irs_pre combarrier.c >> combarrier.i
	@mv -f combarrier.i $(PREDIR)/combarrier.inst.i

$(PREDIR)/combcast.inst.i:combcast.c ../../includes/irs.h                         \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f combcast.i
	$$irs_pre combcast.c >> combcast.i
	@mv -f combcast.i $(PREDIR)/combcast.inst.i

$(PREDIR)/combuf.inst.i:combuf.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/BlockMapping.h ../../includes/FunctionTimer.h            \
	  ../../includes/Combuffer.h
	@rm -f combuf.i
	$$irs_pre combuf.c >> combuf.i
	@mv -f combuf.i $(PREDIR)/combuf.inst.i

$(PREDIR)/comcleanup.inst.i:comcleanup.c ../../includes/irs.h                     \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f comcleanup.i
	$$irs_pre comcleanup.c >> comcleanup.i
	@mv -f comcleanup.i $(PREDIR)/comcleanup.inst.i

$(PREDIR)/comgather.inst.i:comgather.c ../../includes/irs.h                       \
	  ../../includes/irscom.h ../../includes/irsrgst.h                        \
	  ../../includes/FunctionTimer.h ../../includes/NodeList.h                \
	  ../../includes/ProblemArray.h
	@rm -f comgather.i
	$$irs_pre comgather.c >> comgather.i
	@mv -f comgather.i $(PREDIR)/comgather.inst.i

$(PREDIR)/comlen.inst.i:comlen.c ../../includes/irs.h ../../includes/Boundary.h   \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f comlen.i
	$$irs_pre comlen.c >> comlen.i
	@mv -f comlen.i $(PREDIR)/comlen.inst.i

$(PREDIR)/comlock.inst.i:comlock.c ../../includes/irs.h                           \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f comlock.i
	$$irs_pre comlock.c >> comlock.i
	@mv -f comlock.i $(PREDIR)/comlock.inst.i

$(PREDIR)/commpigather.inst.i:commpigather.c ../../includes/irs.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f commpigather.i
	$$irs_pre commpigather.c >> commpigather.i
	@mv -f commpigather.i $(PREDIR)/commpigather.inst.i

$(PREDIR)/commpigatherv.inst.i:commpigatherv.c ../../includes/irs.h               \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f commpigatherv.i
	$$irs_pre commpigatherv.c >> commpigatherv.i
	@mv -f commpigatherv.i $(PREDIR)/commpigatherv.inst.i

$(PREDIR)/comreduce.inst.i:comreduce.c ../../includes/irs.h                       \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f comreduce.i
	$$irs_pre comreduce.c >> comreduce.i
	@mv -f comreduce.i $(PREDIR)/comreduce.inst.i

$(PREDIR)/comsummary.inst.i:comsummary.c ../../includes/irs.h                     \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f comsummary.i
	$$irs_pre comsummary.c >> comsummary.i
	@mv -f comsummary.i $(PREDIR)/comsummary.inst.i

$(PREDIR)/comunlock.inst.i:comunlock.c ../../includes/irs.h                       \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f comunlock.i
	$$irs_pre comunlock.c >> comunlock.i
	@mv -f comunlock.i $(PREDIR)/comunlock.inst.i

$(PREDIR)/comverify.inst.i:comverify.c ../../includes/irs.h                       \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f comverify.i
	$$irs_pre comverify.c >> comverify.i
	@mv -f comverify.i $(PREDIR)/comverify.inst.i

$(PREDIR)/decomp.inst.i:decomp.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/BndMapping.h ../../includes/BlockMapping.h               \
	  ../../includes/Extents.h ../../includes/FunctionTimer.h
	@rm -f decomp.i
	$$irs_pre decomp.c >> decomp.i
	@mv -f decomp.i $(PREDIR)/decomp.inst.i

$(PREDIR)/facecom.inst.i:facecom.c ../../includes/irs.h ../../includes/irsbndry.h \
	  ../../includes/irscom.h ../../includes/BlockMapping.h                   \
	  ../../includes/Boundary.h ../../includes/Bndlist.hh                     \
	  ../../includes/FunctionTimer.h ../../includes/VdenData.hh
	@rm -f facecom.i
	$$irs_pre facecom.c >> facecom.i
	@mv -f facecom.i $(PREDIR)/facecom.inst.i

$(PREDIR)/getdata.inst.i:getdata.c ../../includes/irs.h ../../includes/irscom.h   \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/FunctionTimer.h
	@rm -f getdata.i
	$$irs_pre getdata.c >> getdata.i
	@mv -f getdata.i $(PREDIR)/getdata.inst.i

$(PREDIR)/initcom.inst.i:initcom.c ../../includes/irs.h ../../includes/irslag.h   \
	  ../../includes/irsdmp.h ../../includes/irsedits.h                       \
	  ../../includes/irsrgst.h ../../includes/irscom.hh                       \
	  ../../includes/BlockMapping.h ../../includes/Command.h                  \
	  ../../includes/FunctionTimer.h ../../includes/Rgst.h                    \
	  ../../includes/Tagorder.hh ../../includes/TimeStepControl.h             \
	  ../../includes/Tracer.h
	@rm -f initcom.i
	$$irs_pre initcom.c >> initcom.i
	@mv -f initcom.i $(PREDIR)/initcom.inst.i

$(PREDIR)/matcom.inst.i:matcom.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/irsreg.h ../../includes/Boundary.h                       \
	  ../../includes/FunctionTimer.h ../../includes/SpeciesFraction.h
	@rm -f matcom.i
	$$irs_pre matcom.c >> matcom.i
	@mv -f matcom.i $(PREDIR)/matcom.inst.i

$(PREDIR)/putdata.inst.i:putdata.c ../../includes/irs.h                           \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f putdata.i
	$$irs_pre putdata.c >> putdata.i
	@mv -f putdata.i $(PREDIR)/putdata.inst.i

$(PREDIR)/qbnd.inst.i:qbnd.c ../../includes/irs.h ../../includes/BlockMapping.h   \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/irscom.h
	@rm -f qbnd.i
	$$irs_pre qbnd.c >> qbnd.i
	@mv -f qbnd.i $(PREDIR)/qbnd.inst.i

$(PREDIR)/radcom.inst.i:radcom.c ../../includes/irs.h                             \
	  ../../includes/BlockMapping.h ../../includes/irscom.h                   \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h
	@rm -f radcom.i
	$$irs_pre radcom.c >> radcom.i
	@mv -f radcom.i $(PREDIR)/radcom.inst.i

$(PREDIR)/rbndcom.inst.i:rbndcom.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/irscom.h ../../includes/BlockMapping.h                   \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/ProblemArray.h
	@rm -f rbndcom.i
	$$irs_pre rbndcom.c >> rbndcom.i
	@mv -f rbndcom.i $(PREDIR)/rbndcom.inst.i

$(PREDIR)/setgmap.inst.i:setgmap.c ../../includes/irs.h                           \
	  ../../includes/BlockMapping.h ../../includes/BndMapping.h               \
	  ../../includes/Extents.h ../../includes/FunctionTimer.h                 \
	  ../../includes/irscom.h
	@rm -f setgmap.i
	$$irs_pre setgmap.c >> setgmap.i
	@mv -f setgmap.i $(PREDIR)/setgmap.inst.i

$(PREDIR)/setstdout.inst.i:setstdout.c ../../includes/irs.h                       \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h                  \
	  ../../includes/irsdmp.h
	@rm -f setstdout.i
	$$irs_pre setstdout.c >> setstdout.i
	@mv -f setstdout.i $(PREDIR)/setstdout.inst.i

$(PREDIR)/setumap.inst.i:setumap.c ../../includes/irs.h                           \
	  ../../includes/BlockMapping.h ../../includes/BndMapping.h               \
	  ../../includes/Extents.h ../../includes/FunctionTimer.h                 \
	  ../../includes/irscom.h
	@rm -f setumap.i
	$$irs_pre setumap.c >> setumap.i
	@mv -f setumap.i $(PREDIR)/setumap.inst.i

$(PREDIR)/setvsamegrp.inst.i:setvsamegrp.c ../../includes/irs.h                   \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/Tagorder.h
	@rm -f setvsamegrp.i
	$$irs_pre setvsamegrp.c >> setvsamegrp.i
	@mv -f setvsamegrp.i $(PREDIR)/setvsamegrp.inst.i

$(PREDIR)/setvsameorder.inst.i:setvsameorder.c ../../includes/irs.h               \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/Tagorder.h
	@rm -f setvsameorder.i
	$$irs_pre setvsameorder.c >> setvsameorder.i
	@mv -f setvsameorder.i $(PREDIR)/setvsameorder.inst.i

$(PREDIR)/speccom.inst.i:speccom.c ../../includes/irs.h ../../includes/irscom.h   \
	  ../../includes/Boundary.h ../../includes/FunctionTimer.h                \
	  ../../includes/Region.h ../../includes/SpeciesFraction.h
	@rm -f speccom.i
	$$irs_pre speccom.c >> speccom.i
	@mv -f speccom.i $(PREDIR)/speccom.inst.i

$(PREDIR)/swapcoords.inst.i:swapcoords.c ../../includes/irs.h                     \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f swapcoords.i
	$$irs_pre swapcoords.c >> swapcoords.i
	@mv -f swapcoords.i $(PREDIR)/swapcoords.inst.i

$(PREDIR)/varcom.inst.i:varcom.c ../../includes/irs.h                             \
	  ../../includes/BlockMapping.h ../../includes/Boundary.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h                  \
	  ../../includes/Hash.h
	@rm -f varcom.i
	$$irs_pre varcom.c >> varcom.i
	@mv -f varcom.i $(PREDIR)/varcom.inst.i

$(PREDIR)/vsamecom.inst.i:vsamecom.c ../../includes/irs.h ../../includes/irscom.h \
	  ../../includes/FunctionTimer.h ../../includes/Tagorder.h
	@rm -f vsamecom.i
	$$irs_pre vsamecom.c >> vsamecom.i
	@mv -f vsamecom.i $(PREDIR)/vsamecom.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libcom_inst

libcom_inst:$(BI)(ComNodalZonal.inst.o) $(BI)(acumnm.inst.o)                      \
	  $(BI)(calculate_mappings.inst.o) $(BI)(checkpara.inst.o)                \
	  $(BI)(combarrier.inst.o) $(BI)(combcast.inst.o) $(BI)(combuf.inst.o)    \
	  $(BI)(comcleanup.inst.o) $(BI)(comgather.inst.o) $(BI)(comlen.inst.o)   \
	  $(BI)(comlock.inst.o) $(BI)(commpigather.inst.o)                        \
	  $(BI)(commpigatherv.inst.o) $(BI)(comreduce.inst.o)                     \
	  $(BI)(comsummary.inst.o) $(BI)(comunlock.inst.o)                        \
	  $(BI)(comverify.inst.o) $(BI)(decomp.inst.o) $(BI)(facecom.inst.o)      \
	  $(BI)(getdata.inst.o) $(BI)(initcom.inst.o) $(BI)(matcom.inst.o)        \
	  $(BI)(putdata.inst.o) $(BI)(qbnd.inst.o) $(BI)(radcom.inst.o)           \
	  $(BI)(rbndcom.inst.o) $(BI)(setgmap.inst.o) $(BI)(setstdout.inst.o)     \
	  $(BI)(setumap.inst.o) $(BI)(setvsamegrp.inst.o)                         \
	  $(BI)(setvsameorder.inst.o) $(BI)(speccom.inst.o)                       \
	  $(BI)(swapcoords.inst.o) $(BI)(varcom.inst.o) $(BI)(vsamecom.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libcom_inst.a $(B); \
		ln -sf libcom_inst.a $(B)); \
	  fi
	  @echo 'libcom_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(ComNodalZonal.inst.o):$(INSTDIR)/ComNodalZonal.inst.i
	$$irs_post $(INSTDIR)/ComNodalZonal.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ComNodalZonal.inst.i $(DB)/ComNodalZonal.c 

$(BI)(acumnm.inst.o):$(INSTDIR)/acumnm.inst.i
	$$irs_post $(INSTDIR)/acumnm.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/acumnm.inst.i $(DB)/acumnm.c 

$(BI)(calculate_mappings.inst.o):$(INSTDIR)/calculate_mappings.inst.i
	$$irs_post $(INSTDIR)/calculate_mappings.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/calculate_mappings.inst.i $(DB)/calculate_mappings.c 

$(BI)(checkpara.inst.o):$(INSTDIR)/checkpara.inst.i
	$$irs_post $(INSTDIR)/checkpara.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/checkpara.inst.i $(DB)/checkpara.c 

$(BI)(combarrier.inst.o):$(INSTDIR)/combarrier.inst.i
	$$irs_post $(INSTDIR)/combarrier.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/combarrier.inst.i $(DB)/combarrier.c 

$(BI)(combcast.inst.o):$(INSTDIR)/combcast.inst.i
	$$irs_post $(INSTDIR)/combcast.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/combcast.inst.i $(DB)/combcast.c 

$(BI)(combuf.inst.o):$(INSTDIR)/combuf.inst.i
	$$irs_post $(INSTDIR)/combuf.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/combuf.inst.i $(DB)/combuf.c 

$(BI)(comcleanup.inst.o):$(INSTDIR)/comcleanup.inst.i
	$$irs_post $(INSTDIR)/comcleanup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/comcleanup.inst.i $(DB)/comcleanup.c 

$(BI)(comgather.inst.o):$(INSTDIR)/comgather.inst.i
	$$irs_post $(INSTDIR)/comgather.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/comgather.inst.i $(DB)/comgather.c 

$(BI)(comlen.inst.o):$(INSTDIR)/comlen.inst.i
	$$irs_post $(INSTDIR)/comlen.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/comlen.inst.i $(DB)/comlen.c 

$(BI)(comlock.inst.o):$(INSTDIR)/comlock.inst.i
	$$irs_post $(INSTDIR)/comlock.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/comlock.inst.i $(DB)/comlock.c 

$(BI)(commpigather.inst.o):$(INSTDIR)/commpigather.inst.i
	$$irs_post $(INSTDIR)/commpigather.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/commpigather.inst.i $(DB)/commpigather.c 

$(BI)(commpigatherv.inst.o):$(INSTDIR)/commpigatherv.inst.i
	$$irs_post $(INSTDIR)/commpigatherv.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/commpigatherv.inst.i $(DB)/commpigatherv.c 

$(BI)(comreduce.inst.o):$(INSTDIR)/comreduce.inst.i
	$$irs_post $(INSTDIR)/comreduce.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/comreduce.inst.i $(DB)/comreduce.c 

$(BI)(comsummary.inst.o):$(INSTDIR)/comsummary.inst.i
	$$irs_post $(INSTDIR)/comsummary.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/comsummary.inst.i $(DB)/comsummary.c 

$(BI)(comunlock.inst.o):$(INSTDIR)/comunlock.inst.i
	$$irs_post $(INSTDIR)/comunlock.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/comunlock.inst.i $(DB)/comunlock.c 

$(BI)(comverify.inst.o):$(INSTDIR)/comverify.inst.i
	$$irs_post $(INSTDIR)/comverify.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/comverify.inst.i $(DB)/comverify.c 

$(BI)(decomp.inst.o):$(INSTDIR)/decomp.inst.i
	$$irs_post $(INSTDIR)/decomp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/decomp.inst.i $(DB)/decomp.c 

$(BI)(facecom.inst.o):$(INSTDIR)/facecom.inst.i
	$$irs_post $(INSTDIR)/facecom.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/facecom.inst.i $(DB)/facecom.c 

$(BI)(getdata.inst.o):$(INSTDIR)/getdata.inst.i
	$$irs_post $(INSTDIR)/getdata.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getdata.inst.i $(DB)/getdata.c 

$(BI)(initcom.inst.o):$(INSTDIR)/initcom.inst.i
	$$irs_post $(INSTDIR)/initcom.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/initcom.inst.i $(DB)/initcom.c 

$(BI)(matcom.inst.o):$(INSTDIR)/matcom.inst.i
	$$irs_post $(INSTDIR)/matcom.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/matcom.inst.i $(DB)/matcom.c 

$(BI)(putdata.inst.o):$(INSTDIR)/putdata.inst.i
	$$irs_post $(INSTDIR)/putdata.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/putdata.inst.i $(DB)/putdata.c 

$(BI)(qbnd.inst.o):$(INSTDIR)/qbnd.inst.i
	$$irs_post $(INSTDIR)/qbnd.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/qbnd.inst.i $(DB)/qbnd.c 

$(BI)(radcom.inst.o):$(INSTDIR)/radcom.inst.i
	$$irs_post $(INSTDIR)/radcom.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/radcom.inst.i $(DB)/radcom.c 

$(BI)(rbndcom.inst.o):$(INSTDIR)/rbndcom.inst.i
	$$irs_post $(INSTDIR)/rbndcom.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rbndcom.inst.i $(DB)/rbndcom.c 

$(BI)(setgmap.inst.o):$(INSTDIR)/setgmap.inst.i
	$$irs_post $(INSTDIR)/setgmap.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setgmap.inst.i $(DB)/setgmap.c 

$(BI)(setstdout.inst.o):$(INSTDIR)/setstdout.inst.i
	$$irs_post $(INSTDIR)/setstdout.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setstdout.inst.i $(DB)/setstdout.c 

$(BI)(setumap.inst.o):$(INSTDIR)/setumap.inst.i
	$$irs_post $(INSTDIR)/setumap.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setumap.inst.i $(DB)/setumap.c 

$(BI)(setvsamegrp.inst.o):$(INSTDIR)/setvsamegrp.inst.i
	$$irs_post $(INSTDIR)/setvsamegrp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setvsamegrp.inst.i $(DB)/setvsamegrp.c 

$(BI)(setvsameorder.inst.o):$(INSTDIR)/setvsameorder.inst.i
	$$irs_post $(INSTDIR)/setvsameorder.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setvsameorder.inst.i $(DB)/setvsameorder.c 

$(BI)(speccom.inst.o):$(INSTDIR)/speccom.inst.i
	$$irs_post $(INSTDIR)/speccom.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/speccom.inst.i $(DB)/speccom.c 

$(BI)(swapcoords.inst.o):$(INSTDIR)/swapcoords.inst.i
	$$irs_post $(INSTDIR)/swapcoords.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/swapcoords.inst.i $(DB)/swapcoords.c 

$(BI)(varcom.inst.o):$(INSTDIR)/varcom.inst.i
	$$irs_post $(INSTDIR)/varcom.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/varcom.inst.i $(DB)/varcom.c 

$(BI)(vsamecom.inst.o):$(INSTDIR)/vsamecom.inst.i
	$$irs_post $(INSTDIR)/vsamecom.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/vsamecom.inst.i $(DB)/vsamecom.c 

DEP_SRCS = \
	ComNodalZonal.c acumnm.c calculate_mappings.c checkpara.c combarrier.c  \
	combcast.c combuf.c comcleanup.c comgather.c comlen.c comlock.c commpigather.c  \
	commpigatherv.c comreduce.c comsummary.c comunlock.c comverify.c decomp.c  \
	facecom.c getdata.c initcom.c matcom.c putdata.c qbnd.c radcom.c rbndcom.c  \
	setgmap.c setstdout.c setumap.c setvsamegrp.c setvsameorder.c speccom.c  \
	swapcoords.c varcom.c vsamecom.c  

depend:
	@cp -f Makefile.com Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(ComNodalZonal.o): /usr/include/string.h /usr/include/features.h
$(B)(ComNodalZonal.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(ComNodalZonal.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(ComNodalZonal.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(ComNodalZonal.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(ComNodalZonal.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(ComNodalZonal.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(ComNodalZonal.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(ComNodalZonal.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(ComNodalZonal.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(ComNodalZonal.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(ComNodalZonal.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(ComNodalZonal.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(ComNodalZonal.o): /usr/include/sys/sysmacros.h
$(B)(ComNodalZonal.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(ComNodalZonal.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(ComNodalZonal.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(ComNodalZonal.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(ComNodalZonal.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(ComNodalZonal.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(ComNodalZonal.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(ComNodalZonal.o): /usr/include/ctype.h /usr/include/math.h
$(B)(ComNodalZonal.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(ComNodalZonal.o): /usr/include/bits/mathcalls.h /usr/include/malloc.h
$(B)(ComNodalZonal.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(ComNodalZonal.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(ComNodalZonal.o): ../../includes/Extents.h ../../includes/irsrgst.h
$(B)(ComNodalZonal.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(ComNodalZonal.o): ../../includes/ProblemArray.h
$(B)(acumnm.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(acumnm.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(acumnm.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(acumnm.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(acumnm.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(acumnm.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(acumnm.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(acumnm.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(acumnm.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(acumnm.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(acumnm.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(acumnm.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(acumnm.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(acumnm.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(acumnm.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(acumnm.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(acumnm.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(acumnm.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(acumnm.o): /usr/include/ctype.h /usr/include/math.h
$(B)(acumnm.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(acumnm.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(acumnm.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(acumnm.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(acumnm.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(acumnm.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(calculate_mappings.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(calculate_mappings.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(calculate_mappings.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(calculate_mappings.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(calculate_mappings.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(calculate_mappings.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(calculate_mappings.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(calculate_mappings.o): /usr/include/bits/stdio_lim.h
$(B)(calculate_mappings.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(calculate_mappings.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(calculate_mappings.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(calculate_mappings.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(calculate_mappings.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(calculate_mappings.o): /usr/include/sys/sysmacros.h
$(B)(calculate_mappings.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(calculate_mappings.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(calculate_mappings.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(calculate_mappings.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(calculate_mappings.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(calculate_mappings.o): ../../includes/Source.h
$(B)(calculate_mappings.o): ../../includes/BoundaryCondition.h
$(B)(calculate_mappings.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(calculate_mappings.o): /usr/include/ctype.h /usr/include/math.h
$(B)(calculate_mappings.o): /usr/include/bits/huge_val.h
$(B)(calculate_mappings.o): /usr/include/bits/mathdef.h
$(B)(calculate_mappings.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(calculate_mappings.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(calculate_mappings.o): ../../includes/Combuffer.h
$(B)(calculate_mappings.o): ../../includes/FunctionTimer.h
$(B)(calculate_mappings.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(calculate_mappings.o): ../../includes/BlockMapping.h
$(B)(calculate_mappings.o): ../../includes/BndMapping.h
$(B)(checkpara.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(checkpara.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(checkpara.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(checkpara.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(checkpara.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(checkpara.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(checkpara.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(checkpara.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(checkpara.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(checkpara.o): /usr/include/time.h /usr/include/endian.h
$(B)(checkpara.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(checkpara.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(checkpara.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(checkpara.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(checkpara.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(checkpara.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(checkpara.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(checkpara.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(checkpara.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(checkpara.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(checkpara.o): /usr/include/ctype.h /usr/include/math.h
$(B)(checkpara.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(checkpara.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(checkpara.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(checkpara.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(checkpara.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(combarrier.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(combarrier.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(combarrier.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(combarrier.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(combarrier.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(combarrier.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(combarrier.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(combarrier.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(combarrier.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(combarrier.o): /usr/include/time.h /usr/include/endian.h
$(B)(combarrier.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(combarrier.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(combarrier.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(combarrier.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(combarrier.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(combarrier.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(combarrier.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(combarrier.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(combarrier.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(combarrier.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(combarrier.o): /usr/include/ctype.h /usr/include/math.h
$(B)(combarrier.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(combarrier.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(combarrier.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(combarrier.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(combarrier.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(combcast.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(combcast.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(combcast.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(combcast.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(combcast.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(combcast.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(combcast.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(combcast.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(combcast.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(combcast.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(combcast.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(combcast.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(combcast.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(combcast.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(combcast.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(combcast.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(combcast.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(combcast.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(combcast.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(combcast.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(combcast.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(combcast.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(combcast.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(combcast.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(combcast.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(combuf.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(combuf.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(combuf.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(combuf.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(combuf.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(combuf.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(combuf.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(combuf.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(combuf.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(combuf.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(combuf.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(combuf.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(combuf.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(combuf.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(combuf.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(combuf.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(combuf.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(combuf.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(combuf.o): /usr/include/ctype.h /usr/include/math.h
$(B)(combuf.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(combuf.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(combuf.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(combuf.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(combuf.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(combuf.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(comcleanup.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(comcleanup.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(comcleanup.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(comcleanup.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(comcleanup.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(comcleanup.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(comcleanup.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(comcleanup.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(comcleanup.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(comcleanup.o): /usr/include/time.h /usr/include/endian.h
$(B)(comcleanup.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(comcleanup.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(comcleanup.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(comcleanup.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(comcleanup.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(comcleanup.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(comcleanup.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(comcleanup.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(comcleanup.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(comcleanup.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(comcleanup.o): /usr/include/ctype.h /usr/include/math.h
$(B)(comcleanup.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(comcleanup.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(comcleanup.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(comcleanup.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(comcleanup.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(comgather.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(comgather.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(comgather.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(comgather.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(comgather.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(comgather.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(comgather.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(comgather.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(comgather.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(comgather.o): /usr/include/time.h /usr/include/endian.h
$(B)(comgather.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(comgather.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(comgather.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(comgather.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(comgather.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(comgather.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(comgather.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(comgather.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(comgather.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(comgather.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(comgather.o): /usr/include/ctype.h /usr/include/math.h
$(B)(comgather.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(comgather.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(comgather.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(comgather.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(comgather.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(comgather.o): ../../includes/irsrgst.h ../../includes/ProblemArray.h
$(B)(comlen.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(comlen.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(comlen.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(comlen.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(comlen.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(comlen.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(comlen.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(comlen.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(comlen.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(comlen.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(comlen.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(comlen.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(comlen.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(comlen.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(comlen.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(comlen.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(comlen.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(comlen.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(comlen.o): /usr/include/ctype.h /usr/include/math.h
$(B)(comlen.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(comlen.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(comlen.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(comlen.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(comlen.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(comlock.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(comlock.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(comlock.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(comlock.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(comlock.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(comlock.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(comlock.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(comlock.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(comlock.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(comlock.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(comlock.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(comlock.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(comlock.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(comlock.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(comlock.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(comlock.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(comlock.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(comlock.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(comlock.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(comlock.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(comlock.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(comlock.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(comlock.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(comlock.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(commpigather.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(commpigather.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(commpigather.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(commpigather.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(commpigather.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(commpigather.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(commpigather.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(commpigather.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(commpigather.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(commpigather.o): /usr/include/time.h /usr/include/endian.h
$(B)(commpigather.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(commpigather.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(commpigather.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(commpigather.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(commpigather.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(commpigather.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(commpigather.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(commpigather.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(commpigather.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(commpigather.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(commpigather.o): /usr/include/ctype.h /usr/include/math.h
$(B)(commpigather.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(commpigather.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(commpigather.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(commpigather.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(commpigather.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(commpigatherv.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(commpigatherv.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(commpigatherv.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(commpigatherv.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(commpigatherv.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(commpigatherv.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(commpigatherv.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(commpigatherv.o): /usr/include/bits/stdio_lim.h
$(B)(commpigatherv.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(commpigatherv.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(commpigatherv.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(commpigatherv.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(commpigatherv.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(commpigatherv.o): /usr/include/sys/sysmacros.h
$(B)(commpigatherv.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(commpigatherv.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(commpigatherv.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(commpigatherv.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(commpigatherv.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(commpigatherv.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(commpigatherv.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(commpigatherv.o): /usr/include/ctype.h /usr/include/math.h
$(B)(commpigatherv.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(commpigatherv.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(commpigatherv.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(commpigatherv.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(commpigatherv.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(comreduce.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(comreduce.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(comreduce.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(comreduce.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(comreduce.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(comreduce.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(comreduce.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(comreduce.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(comreduce.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(comreduce.o): /usr/include/time.h /usr/include/endian.h
$(B)(comreduce.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(comreduce.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(comreduce.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(comreduce.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(comreduce.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(comreduce.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(comreduce.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(comreduce.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(comreduce.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(comreduce.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(comreduce.o): /usr/include/ctype.h /usr/include/math.h
$(B)(comreduce.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(comreduce.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(comreduce.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(comreduce.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(comreduce.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(comsummary.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(comsummary.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(comsummary.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(comsummary.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(comsummary.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(comsummary.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(comsummary.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(comsummary.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(comsummary.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(comsummary.o): /usr/include/time.h /usr/include/endian.h
$(B)(comsummary.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(comsummary.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(comsummary.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(comsummary.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(comsummary.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(comsummary.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(comsummary.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(comsummary.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(comsummary.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(comsummary.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(comsummary.o): /usr/include/ctype.h /usr/include/math.h
$(B)(comsummary.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(comsummary.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(comsummary.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(comsummary.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(comsummary.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(comunlock.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(comunlock.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(comunlock.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(comunlock.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(comunlock.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(comunlock.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(comunlock.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(comunlock.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(comunlock.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(comunlock.o): /usr/include/time.h /usr/include/endian.h
$(B)(comunlock.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(comunlock.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(comunlock.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(comunlock.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(comunlock.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(comunlock.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(comunlock.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(comunlock.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(comunlock.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(comunlock.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(comunlock.o): /usr/include/ctype.h /usr/include/math.h
$(B)(comunlock.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(comunlock.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(comunlock.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(comunlock.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(comunlock.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(comverify.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(comverify.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(comverify.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(comverify.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(comverify.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(comverify.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(comverify.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(comverify.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(comverify.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(comverify.o): /usr/include/time.h /usr/include/endian.h
$(B)(comverify.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(comverify.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(comverify.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(comverify.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(comverify.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(comverify.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(comverify.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(comverify.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(comverify.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(comverify.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(comverify.o): /usr/include/ctype.h /usr/include/math.h
$(B)(comverify.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(comverify.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(comverify.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(comverify.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(comverify.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(decomp.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(decomp.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(decomp.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(decomp.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(decomp.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(decomp.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(decomp.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(decomp.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(decomp.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(decomp.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(decomp.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(decomp.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(decomp.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(decomp.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(decomp.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(decomp.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(decomp.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(decomp.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(decomp.o): /usr/include/ctype.h /usr/include/math.h
$(B)(decomp.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(decomp.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(decomp.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(decomp.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(decomp.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(decomp.o): ../../includes/BndMapping.h ../../includes/BlockMapping.h
$(B)(facecom.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(facecom.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(facecom.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(facecom.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(facecom.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(facecom.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(facecom.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(facecom.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(facecom.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(facecom.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(facecom.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(facecom.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(facecom.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(facecom.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(facecom.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(facecom.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(facecom.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(facecom.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(facecom.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(facecom.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(facecom.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(facecom.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(facecom.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(facecom.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(facecom.o): ../../includes/Extents.h ../../includes/BlockMapping.h
$(B)(facecom.o): ../../includes/BndMapping.h
$(B)(getdata.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(getdata.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(getdata.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(getdata.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(getdata.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getdata.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getdata.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getdata.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(getdata.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(getdata.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(getdata.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(getdata.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(getdata.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(getdata.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(getdata.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(getdata.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(getdata.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(getdata.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(getdata.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(getdata.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getdata.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(getdata.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(getdata.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(getdata.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(getdata.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(initcom.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(initcom.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(initcom.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(initcom.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(initcom.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(initcom.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(initcom.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(initcom.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(initcom.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(initcom.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(initcom.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(initcom.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(initcom.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(initcom.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(initcom.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(initcom.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(initcom.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(initcom.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(initcom.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(initcom.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(initcom.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(initcom.o): /usr/include/malloc.h ../../includes/irslag.h
$(B)(initcom.o): ../../includes/State.h ../../includes/irsdmp.h
$(B)(initcom.o): ../../includes/Extents.h ../../includes/irsedits.h
$(B)(initcom.o): ../../includes/irsrgst.h ../../includes/BlockMapping.h
$(B)(initcom.o): ../../includes/BndMapping.h ../../includes/Command.h
$(B)(initcom.o): ../../includes/FunctionTimer.h ../../includes/TimeStepControl.h
$(B)(initcom.o): ../../includes/Tracer.h
$(B)(matcom.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(matcom.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(matcom.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(matcom.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(matcom.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(matcom.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(matcom.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(matcom.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(matcom.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(matcom.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(matcom.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(matcom.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(matcom.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(matcom.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(matcom.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(matcom.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(matcom.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(matcom.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(matcom.o): /usr/include/ctype.h /usr/include/math.h
$(B)(matcom.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(matcom.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(matcom.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(matcom.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(matcom.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(matcom.o): ../../includes/irsreg.h ../../includes/Region.h
$(B)(putdata.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(putdata.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(putdata.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(putdata.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(putdata.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(putdata.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(putdata.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(putdata.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(putdata.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(putdata.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(putdata.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(putdata.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(putdata.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(putdata.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(putdata.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(putdata.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(putdata.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(putdata.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(putdata.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(putdata.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(putdata.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(putdata.o): /usr/include/malloc.h ../../includes/BlockMapping.h
$(B)(putdata.o): ../../includes/BndMapping.h ../../includes/FunctionTimer.h
$(B)(putdata.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(putdata.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(qbnd.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(qbnd.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(qbnd.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(qbnd.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(qbnd.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(qbnd.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(qbnd.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(qbnd.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(qbnd.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(qbnd.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(qbnd.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(qbnd.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(qbnd.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(qbnd.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(qbnd.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(qbnd.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(qbnd.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(qbnd.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(qbnd.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(qbnd.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(qbnd.o): /usr/include/string.h /usr/include/malloc.h
$(B)(qbnd.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(qbnd.o): ../../includes/FunctionTimer.h ../../includes/irscom.h
$(B)(qbnd.o): ../../includes/Combuffer.h ../../includes/NodeList.h
$(B)(qbnd.o): ../../includes/Extents.h
$(B)(radcom.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(radcom.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(radcom.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(radcom.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(radcom.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(radcom.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(radcom.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(radcom.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(radcom.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(radcom.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(radcom.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(radcom.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(radcom.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(radcom.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(radcom.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(radcom.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(radcom.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(radcom.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(radcom.o): /usr/include/ctype.h /usr/include/math.h
$(B)(radcom.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(radcom.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(radcom.o): /usr/include/malloc.h ../../includes/BlockMapping.h
$(B)(radcom.o): ../../includes/BndMapping.h ../../includes/irscom.h
$(B)(radcom.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(radcom.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rbndcom.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rbndcom.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rbndcom.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rbndcom.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rbndcom.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(rbndcom.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(rbndcom.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(rbndcom.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(rbndcom.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rbndcom.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rbndcom.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rbndcom.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rbndcom.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rbndcom.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rbndcom.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rbndcom.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rbndcom.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rbndcom.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rbndcom.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rbndcom.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rbndcom.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rbndcom.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(rbndcom.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rbndcom.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rbndcom.o): ../../includes/Region.h ../../includes/irscom.h
$(B)(rbndcom.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(rbndcom.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rbndcom.o): ../../includes/ProblemArray.h
$(B)(setgmap.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(setgmap.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(setgmap.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(setgmap.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(setgmap.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setgmap.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setgmap.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setgmap.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(setgmap.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(setgmap.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(setgmap.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(setgmap.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(setgmap.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(setgmap.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(setgmap.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(setgmap.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(setgmap.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(setgmap.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(setgmap.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(setgmap.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setgmap.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setgmap.o): /usr/include/malloc.h ../../includes/BlockMapping.h
$(B)(setgmap.o): ../../includes/BndMapping.h ../../includes/Extents.h
$(B)(setgmap.o): ../../includes/FunctionTimer.h ../../includes/irscom.h
$(B)(setgmap.o): ../../includes/Combuffer.h ../../includes/NodeList.h
$(B)(setstdout.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(setstdout.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(setstdout.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(setstdout.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(setstdout.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(setstdout.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setstdout.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setstdout.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setstdout.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(setstdout.o): /usr/include/time.h /usr/include/endian.h
$(B)(setstdout.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(setstdout.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(setstdout.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(setstdout.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(setstdout.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(setstdout.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(setstdout.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(setstdout.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(setstdout.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(setstdout.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(setstdout.o): /usr/include/ctype.h /usr/include/math.h
$(B)(setstdout.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setstdout.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setstdout.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(setstdout.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(setstdout.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(setstdout.o): ../../includes/irsdmp.h
$(B)(setumap.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(setumap.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(setumap.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(setumap.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(setumap.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setumap.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setumap.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setumap.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(setumap.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(setumap.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(setumap.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(setumap.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(setumap.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(setumap.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(setumap.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(setumap.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(setumap.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(setumap.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(setumap.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(setumap.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setumap.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setumap.o): /usr/include/malloc.h ../../includes/BlockMapping.h
$(B)(setumap.o): ../../includes/BndMapping.h ../../includes/Extents.h
$(B)(setumap.o): ../../includes/FunctionTimer.h ../../includes/irscom.h
$(B)(setumap.o): ../../includes/Combuffer.h ../../includes/NodeList.h
$(B)(setvsamegrp.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(setvsamegrp.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(setvsamegrp.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(setvsamegrp.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(setvsamegrp.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(setvsamegrp.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setvsamegrp.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setvsamegrp.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setvsamegrp.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(setvsamegrp.o): /usr/include/time.h /usr/include/endian.h
$(B)(setvsamegrp.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(setvsamegrp.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(setvsamegrp.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(setvsamegrp.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(setvsamegrp.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(setvsamegrp.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(setvsamegrp.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(setvsamegrp.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(setvsamegrp.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(setvsamegrp.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(setvsamegrp.o): /usr/include/ctype.h /usr/include/math.h
$(B)(setvsamegrp.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setvsamegrp.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setvsamegrp.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(setvsamegrp.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(setvsamegrp.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(setvsamegrp.o): ../../includes/Tagorder.h
$(B)(setvsameorder.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(setvsameorder.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(setvsameorder.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(setvsameorder.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(setvsameorder.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(setvsameorder.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setvsameorder.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setvsameorder.o): /usr/include/bits/stdio_lim.h
$(B)(setvsameorder.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(setvsameorder.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(setvsameorder.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(setvsameorder.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(setvsameorder.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(setvsameorder.o): /usr/include/sys/sysmacros.h
$(B)(setvsameorder.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(setvsameorder.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(setvsameorder.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(setvsameorder.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(setvsameorder.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(setvsameorder.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(setvsameorder.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(setvsameorder.o): /usr/include/ctype.h /usr/include/math.h
$(B)(setvsameorder.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setvsameorder.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setvsameorder.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(setvsameorder.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(setvsameorder.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(setvsameorder.o): ../../includes/Tagorder.h
$(B)(speccom.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(speccom.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(speccom.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(speccom.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(speccom.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(speccom.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(speccom.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(speccom.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(speccom.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(speccom.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(speccom.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(speccom.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(speccom.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(speccom.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(speccom.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(speccom.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(speccom.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(speccom.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(speccom.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(speccom.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(speccom.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(speccom.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(speccom.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(speccom.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(speccom.o): ../../includes/Region.h
$(B)(swapcoords.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(swapcoords.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(swapcoords.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(swapcoords.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(swapcoords.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(swapcoords.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(swapcoords.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(swapcoords.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(swapcoords.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(swapcoords.o): /usr/include/time.h /usr/include/endian.h
$(B)(swapcoords.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(swapcoords.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(swapcoords.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(swapcoords.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(swapcoords.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(swapcoords.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(swapcoords.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(swapcoords.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(swapcoords.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(swapcoords.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(swapcoords.o): /usr/include/ctype.h /usr/include/math.h
$(B)(swapcoords.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(swapcoords.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(swapcoords.o): /usr/include/malloc.h ../../includes/FunctionTimer.h
$(B)(swapcoords.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(swapcoords.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(varcom.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(varcom.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(varcom.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(varcom.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(varcom.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(varcom.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(varcom.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(varcom.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(varcom.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(varcom.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(varcom.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(varcom.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(varcom.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(varcom.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(varcom.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(varcom.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(varcom.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(varcom.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(varcom.o): /usr/include/ctype.h /usr/include/math.h
$(B)(varcom.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(varcom.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(varcom.o): /usr/include/malloc.h ../../includes/BlockMapping.h
$(B)(varcom.o): ../../includes/BndMapping.h ../../includes/FunctionTimer.h
$(B)(varcom.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(varcom.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(vsamecom.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(vsamecom.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(vsamecom.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(vsamecom.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(vsamecom.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(vsamecom.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(vsamecom.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(vsamecom.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(vsamecom.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(vsamecom.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(vsamecom.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(vsamecom.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(vsamecom.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(vsamecom.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(vsamecom.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(vsamecom.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(vsamecom.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(vsamecom.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(vsamecom.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(vsamecom.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(vsamecom.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(vsamecom.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(vsamecom.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(vsamecom.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(vsamecom.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(vsamecom.o): ../../includes/Tagorder.h
