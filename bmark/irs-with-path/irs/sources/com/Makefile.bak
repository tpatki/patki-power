
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

