
################################################################################
#
# Makefile for irs library bndry
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
B = ../$(LIB_DIR)/libbndry.a
BI = ../$(LIB_DIR)/libbndry_inst.a

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
SRCDIR = ../sources/bndry

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libbndry:$(B)(bcin.o) $(B)(bcin0.o) $(B)(bcnorm.o) $(B)(bndcopy.o) $(B)(bndin.o)  \
	  $(B)(bndrydev.o) $(B)(bndryinit.o) $(B)(bndzonelist.o)                  \
	  $(B)(genradreflst.o) $(B)(genreflst.o) $(B)(getbcname.o) $(B)(initbc.o) \
	  $(B)(irefzq.o) $(B)(orient.o) $(B)(refadv2d.o) $(B)(refadv3d.o)         \
	  $(B)(refnd2d.o) $(B)(refnd3d.o) $(B)(refnd3ds.o) $(B)(refradnq.o)       \
	  $(B)(refzq.o) $(B)(setbndry.o) $(B)(setcrnlst.o) $(B)(setphony.o)       \
	  $(B)(setphony2.o) $(B)(sewbndry.o) $(B)(vsamein0.o) $(B)(vsameorg.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'bndry library current'

# creation deps
#---------------
../../includes/irsbndry.hh:../../includes/irsbndry.h
	cp ../../includes/irsbndry.h ../../includes/irsbndry.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irsbndry.hh
	irs_hhinit ../../includes/irsbndry.hh

$(B)(bcin.o):../../includes/irsbndry.hh

$(B)(bcin.o):bcin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bcin.c $(DB)/bcin.c 

$(B)(bcin0.o):bcin0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bcin0.c $(DB)/bcin0.c 

$(B)(bcnorm.o):bcnorm.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bcnorm.c $(DB)/bcnorm.c 

$(B)(bndcopy.o):bndcopy.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bndcopy.c $(DB)/bndcopy.c 

$(B)(bndin.o):bndin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bndin.c $(DB)/bndin.c 

$(B)(bndrydev.o):bndrydev.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bndrydev.c $(DB)/bndrydev.c 

$(B)(bndryinit.o):bndryinit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bndryinit.c $(DB)/bndryinit.c 

$(B)(bndzonelist.o):bndzonelist.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bndzonelist.c $(DB)/bndzonelist.c 

$(B)(genradreflst.o):genradreflst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/genradreflst.c $(DB)/genradreflst.c 

$(B)(genreflst.o):genreflst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/genreflst.c $(DB)/genreflst.c 

$(B)(getbcname.o):getbcname.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getbcname.c $(DB)/getbcname.c 

$(B)(initbc.o):initbc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/initbc.c $(DB)/initbc.c 

$(B)(irefzq.o):irefzq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/irefzq.c $(DB)/irefzq.c 

$(B)(orient.o):orient.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/orient.c $(DB)/orient.c 

$(B)(refadv2d.o):refadv2d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/refadv2d.c $(DB)/refadv2d.c 

$(B)(refadv3d.o):refadv3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/refadv3d.c $(DB)/refadv3d.c 

$(B)(refnd2d.o):refnd2d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/refnd2d.c $(DB)/refnd2d.c 

$(B)(refnd3d.o):refnd3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/refnd3d.c $(DB)/refnd3d.c 

$(B)(refnd3ds.o):refnd3ds.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/refnd3ds.c $(DB)/refnd3ds.c 

$(B)(refradnq.o):refradnq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/refradnq.c $(DB)/refradnq.c 

$(B)(refzq.o):refzq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/refzq.c $(DB)/refzq.c 

$(B)(setbndry.o):setbndry.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setbndry.c $(DB)/setbndry.c 

$(B)(setcrnlst.o):setcrnlst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setcrnlst.c $(DB)/setcrnlst.c 

$(B)(setphony.o):setphony.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setphony.c $(DB)/setphony.c 

$(B)(setphony2.o):setphony2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setphony2.c $(DB)/setphony2.c 

$(B)(sewbndry.o):sewbndry.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/sewbndry.c $(DB)/sewbndry.c 

$(B)(vsamein0.o):vsamein0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/vsamein0.c $(DB)/vsamein0.c 

$(B)(vsameorg.o):vsameorg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/vsameorg.c $(DB)/vsameorg.c 

#---------------------
# lint pass one target 
#---------------------
lint:bcin.ln bcin0.ln bcnorm.ln bndcopy.ln bndin.ln bndrydev.ln bndryinit.ln      \
	  bndzonelist.ln genradreflst.ln genreflst.ln getbcname.ln initbc.ln      \
	  irefzq.ln orient.ln refadv2d.ln refadv3d.ln refnd2d.ln refnd3d.ln       \
	  refnd3ds.ln refradnq.ln refzq.ln setbndry.ln setcrnlst.ln setphony.ln   \
	  setphony2.ln sewbndry.ln vsamein0.ln vsameorg.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
bcin.ln:bcin.c ../../includes/irs.h ../../includes/irssrc.h                       \
	  ../../includes/irsbndry.hh ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bcin.c ***' >> $(LO)
	$$irs_lint bcin.c 2>&1 | tee -a $(LO)

bcin0.ln:bcin0.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bcin0.c ***' >> $(LO)
	$$irs_lint bcin0.c 2>&1 | tee -a $(LO)

bcnorm.ln:bcnorm.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bcnorm.c ***' >> $(LO)
	$$irs_lint bcnorm.c 2>&1 | tee -a $(LO)

bndcopy.ln:bndcopy.c ../../includes/irs.h ../../includes/irsbndry.h               \
	  ../../includes/BoundaryCondition.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bndcopy.c ***' >> $(LO)
	$$irs_lint bndcopy.c 2>&1 | tee -a $(LO)

bndin.ln:bndin.c ../../includes/irs.h ../../includes/irsbndry.h                   \
	  ../../includes/BlockMapping.h ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bndin.c ***' >> $(LO)
	$$irs_lint bndin.c 2>&1 | tee -a $(LO)

bndrydev.ln:bndrydev.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/irscom.h ../../includes/irsrgst.h                        \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h            \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bndrydev.c ***' >> $(LO)
	$$irs_lint bndrydev.c 2>&1 | tee -a $(LO)

bndryinit.ln:bndryinit.c ../../includes/irs.h ../../includes/irsblk.h             \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irssys.h ../../includes/Boundary.h                       \
	  ../../includes/BlockMapping.h ../../includes/BndMapping.h               \
	  ../../includes/Extents.h ../../includes/FunctionTimer.h                 \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bndryinit.c ***' >> $(LO)
	$$irs_lint bndryinit.c 2>&1 | tee -a $(LO)

bndzonelist.ln:bndzonelist.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bndzonelist.c ***' >> $(LO)
	$$irs_lint bndzonelist.c 2>&1 | tee -a $(LO)

genradreflst.ln:genradreflst.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON genradreflst.c ***' >> $(LO)
	$$irs_lint genradreflst.c 2>&1 | tee -a $(LO)

genreflst.ln:genreflst.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON genreflst.c ***' >> $(LO)
	$$irs_lint genreflst.c 2>&1 | tee -a $(LO)

getbcname.ln:getbcname.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getbcname.c ***' >> $(LO)
	$$irs_lint getbcname.c 2>&1 | tee -a $(LO)

initbc.ln:initbc.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON initbc.c ***' >> $(LO)
	$$irs_lint initbc.c 2>&1 | tee -a $(LO)

irefzq.ln:irefzq.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON irefzq.c ***' >> $(LO)
	$$irs_lint irefzq.c 2>&1 | tee -a $(LO)

orient.ln:orient.c ../../includes/irs.h ../../includes/irsbndry.h                 \
	  ../../includes/BlockMapping.h ../../includes/BndMapping.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON orient.c ***' >> $(LO)
	$$irs_lint orient.c 2>&1 | tee -a $(LO)

refadv2d.ln:refadv2d.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON refadv2d.c ***' >> $(LO)
	$$irs_lint refadv2d.c 2>&1 | tee -a $(LO)

refadv3d.ln:refadv3d.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON refadv3d.c ***' >> $(LO)
	$$irs_lint refadv3d.c 2>&1 | tee -a $(LO)

refnd2d.ln:refnd2d.c ../../includes/irs.h ../../includes/irsbndry.h               \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON refnd2d.c ***' >> $(LO)
	$$irs_lint refnd2d.c 2>&1 | tee -a $(LO)

refnd3d.ln:refnd3d.c ../../includes/irs.h ../../includes/irsbndry.h               \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON refnd3d.c ***' >> $(LO)
	$$irs_lint refnd3d.c 2>&1 | tee -a $(LO)

refnd3ds.ln:refnd3ds.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON refnd3ds.c ***' >> $(LO)
	$$irs_lint refnd3ds.c 2>&1 | tee -a $(LO)

refradnq.ln:refradnq.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON refradnq.c ***' >> $(LO)
	$$irs_lint refradnq.c 2>&1 | tee -a $(LO)

refzq.ln:refzq.c ../../includes/irs.h ../../includes/irsbndry.h                   \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON refzq.c ***' >> $(LO)
	$$irs_lint refzq.c 2>&1 | tee -a $(LO)

setbndry.ln:setbndry.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setbndry.c ***' >> $(LO)
	$$irs_lint setbndry.c 2>&1 | tee -a $(LO)

setcrnlst.ln:setcrnlst.c ../../includes/irs.h ../../includes/irsbndry.h           \
	  ../../includes/Boundary.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setcrnlst.c ***' >> $(LO)
	$$irs_lint setcrnlst.c 2>&1 | tee -a $(LO)

setphony.ln:setphony.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setphony.c ***' >> $(LO)
	$$irs_lint setphony.c 2>&1 | tee -a $(LO)

setphony2.ln:setphony2.c ../../includes/irs.h ../../includes/irsbndry.h           \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setphony2.c ***' >> $(LO)
	$$irs_lint setphony2.c 2>&1 | tee -a $(LO)

sewbndry.ln:sewbndry.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON sewbndry.c ***' >> $(LO)
	$$irs_lint sewbndry.c 2>&1 | tee -a $(LO)

vsamein0.ln:vsamein0.c ../../includes/irs.h ../../includes/irsbndry.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON vsamein0.c ***' >> $(LO)
	$$irs_lint vsamein0.c 2>&1 | tee -a $(LO)

vsameorg.ln:vsameorg.c ../../includes/irs.h ../../includes/irsbndry.h             \
	  ../../includes/BlockMapping.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON vsameorg.c ***' >> $(LO)
	$$irs_lint vsameorg.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/bcin.inst.i $(PREDIR)/bcin0.inst.i $(PREDIR)/bcnorm.inst.i   \
	  $(PREDIR)/bndcopy.inst.i $(PREDIR)/bndin.inst.i                         \
	  $(PREDIR)/bndrydev.inst.i $(PREDIR)/bndryinit.inst.i                    \
	  $(PREDIR)/bndzonelist.inst.i $(PREDIR)/genradreflst.inst.i              \
	  $(PREDIR)/genreflst.inst.i $(PREDIR)/getbcname.inst.i                   \
	  $(PREDIR)/initbc.inst.i $(PREDIR)/irefzq.inst.i $(PREDIR)/orient.inst.i \
	  $(PREDIR)/refadv2d.inst.i $(PREDIR)/refadv3d.inst.i                     \
	  $(PREDIR)/refnd2d.inst.i $(PREDIR)/refnd3d.inst.i                       \
	  $(PREDIR)/refnd3ds.inst.i $(PREDIR)/refradnq.inst.i                     \
	  $(PREDIR)/refzq.inst.i $(PREDIR)/setbndry.inst.i                        \
	  $(PREDIR)/setcrnlst.inst.i $(PREDIR)/setphony.inst.i                    \
	  $(PREDIR)/setphony2.inst.i $(PREDIR)/sewbndry.inst.i                    \
	  $(PREDIR)/vsamein0.inst.i $(PREDIR)/vsameorg.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/bcin.inst.i:bcin.c ../../includes/irs.h ../../includes/irssrc.h         \
	  ../../includes/irsbndry.hh ../../includes/NodeList.h
	@rm -f bcin.i
	$$irs_pre bcin.c >> bcin.i
	@mv -f bcin.i $(PREDIR)/bcin.inst.i

$(PREDIR)/bcin0.inst.i:bcin0.c ../../includes/irs.h ../../includes/irsbndry.h
	@rm -f bcin0.i
	$$irs_pre bcin0.c >> bcin0.i
	@mv -f bcin0.i $(PREDIR)/bcin0.inst.i

$(PREDIR)/bcnorm.inst.i:bcnorm.c ../../includes/irs.h ../../includes/irsbndry.h
	@rm -f bcnorm.i
	$$irs_pre bcnorm.c >> bcnorm.i
	@mv -f bcnorm.i $(PREDIR)/bcnorm.inst.i

$(PREDIR)/bndcopy.inst.i:bndcopy.c ../../includes/irs.h ../../includes/irsbndry.h \
	  ../../includes/BoundaryCondition.h
	@rm -f bndcopy.i
	$$irs_pre bndcopy.c >> bndcopy.i
	@mv -f bndcopy.i $(PREDIR)/bndcopy.inst.i

$(PREDIR)/bndin.inst.i:bndin.c ../../includes/irs.h ../../includes/irsbndry.h     \
	  ../../includes/BlockMapping.h ../../includes/NodeList.h
	@rm -f bndin.i
	$$irs_pre bndin.c >> bndin.i
	@mv -f bndin.i $(PREDIR)/bndin.inst.i

$(PREDIR)/bndrydev.inst.i:bndrydev.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsrgst.h ../../includes/FunctionTimer.h                 \
	  ../../includes/ProblemArray.h ../../includes/NodeList.h
	@rm -f bndrydev.i
	$$irs_pre bndrydev.c >> bndrydev.i
	@mv -f bndrydev.i $(PREDIR)/bndrydev.inst.i

$(PREDIR)/bndryinit.inst.i:bndryinit.c ../../includes/irs.h                       \
	  ../../includes/irsblk.h ../../includes/irsbndry.h                       \
	  ../../includes/irscom.h ../../includes/irssys.h                         \
	  ../../includes/Boundary.h ../../includes/BlockMapping.h                 \
	  ../../includes/BndMapping.h ../../includes/Extents.h                    \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h
	@rm -f bndryinit.i
	$$irs_pre bndryinit.c >> bndryinit.i
	@mv -f bndryinit.i $(PREDIR)/bndryinit.inst.i

$(PREDIR)/bndzonelist.inst.i:bndzonelist.c ../../includes/irs.h                   \
	  ../../includes/irsbndry.h
	@rm -f bndzonelist.i
	$$irs_pre bndzonelist.c >> bndzonelist.i
	@mv -f bndzonelist.i $(PREDIR)/bndzonelist.inst.i

$(PREDIR)/genradreflst.inst.i:genradreflst.c ../../includes/irs.h                 \
	  ../../includes/irsbndry.h
	@rm -f genradreflst.i
	$$irs_pre genradreflst.c >> genradreflst.i
	@mv -f genradreflst.i $(PREDIR)/genradreflst.inst.i

$(PREDIR)/genreflst.inst.i:genreflst.c ../../includes/irs.h                       \
	  ../../includes/irsbndry.h
	@rm -f genreflst.i
	$$irs_pre genreflst.c >> genreflst.i
	@mv -f genreflst.i $(PREDIR)/genreflst.inst.i

$(PREDIR)/getbcname.inst.i:getbcname.c ../../includes/irs.h                       \
	  ../../includes/irsbndry.h
	@rm -f getbcname.i
	$$irs_pre getbcname.c >> getbcname.i
	@mv -f getbcname.i $(PREDIR)/getbcname.inst.i

$(PREDIR)/initbc.inst.i:initbc.c ../../includes/irs.h ../../includes/irsbndry.h
	@rm -f initbc.i
	$$irs_pre initbc.c >> initbc.i
	@mv -f initbc.i $(PREDIR)/initbc.inst.i

$(PREDIR)/irefzq.inst.i:irefzq.c ../../includes/irs.h ../../includes/irsbndry.h
	@rm -f irefzq.i
	$$irs_pre irefzq.c >> irefzq.i
	@mv -f irefzq.i $(PREDIR)/irefzq.inst.i

$(PREDIR)/orient.inst.i:orient.c ../../includes/irs.h ../../includes/irsbndry.h   \
	  ../../includes/BlockMapping.h ../../includes/BndMapping.h
	@rm -f orient.i
	$$irs_pre orient.c >> orient.i
	@mv -f orient.i $(PREDIR)/orient.inst.i

$(PREDIR)/refadv2d.inst.i:refadv2d.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	@rm -f refadv2d.i
	$$irs_pre refadv2d.c >> refadv2d.i
	@mv -f refadv2d.i $(PREDIR)/refadv2d.inst.i

$(PREDIR)/refadv3d.inst.i:refadv3d.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	@rm -f refadv3d.i
	$$irs_pre refadv3d.c >> refadv3d.i
	@mv -f refadv3d.i $(PREDIR)/refadv3d.inst.i

$(PREDIR)/refnd2d.inst.i:refnd2d.c ../../includes/irs.h ../../includes/irsbndry.h \
	  ../../includes/FunctionTimer.h
	@rm -f refnd2d.i
	$$irs_pre refnd2d.c >> refnd2d.i
	@mv -f refnd2d.i $(PREDIR)/refnd2d.inst.i

$(PREDIR)/refnd3d.inst.i:refnd3d.c ../../includes/irs.h ../../includes/irsbndry.h \
	  ../../includes/FunctionTimer.h
	@rm -f refnd3d.i
	$$irs_pre refnd3d.c >> refnd3d.i
	@mv -f refnd3d.i $(PREDIR)/refnd3d.inst.i

$(PREDIR)/refnd3ds.inst.i:refnd3ds.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	@rm -f refnd3ds.i
	$$irs_pre refnd3ds.c >> refnd3ds.i
	@mv -f refnd3ds.i $(PREDIR)/refnd3ds.inst.i

$(PREDIR)/refradnq.inst.i:refradnq.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	@rm -f refradnq.i
	$$irs_pre refradnq.c >> refradnq.i
	@mv -f refradnq.i $(PREDIR)/refradnq.inst.i

$(PREDIR)/refzq.inst.i:refzq.c ../../includes/irs.h ../../includes/irsbndry.h     \
	  ../../includes/FunctionTimer.h
	@rm -f refzq.i
	$$irs_pre refzq.c >> refzq.i
	@mv -f refzq.i $(PREDIR)/refzq.inst.i

$(PREDIR)/setbndry.inst.i:setbndry.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	@rm -f setbndry.i
	$$irs_pre setbndry.c >> setbndry.i
	@mv -f setbndry.i $(PREDIR)/setbndry.inst.i

$(PREDIR)/setcrnlst.inst.i:setcrnlst.c ../../includes/irs.h                       \
	  ../../includes/irsbndry.h ../../includes/Boundary.h
	@rm -f setcrnlst.i
	$$irs_pre setcrnlst.c >> setcrnlst.i
	@mv -f setcrnlst.i $(PREDIR)/setcrnlst.inst.i

$(PREDIR)/setphony.inst.i:setphony.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	@rm -f setphony.i
	$$irs_pre setphony.c >> setphony.i
	@mv -f setphony.i $(PREDIR)/setphony.inst.i

$(PREDIR)/setphony2.inst.i:setphony2.c ../../includes/irs.h                       \
	  ../../includes/irsbndry.h ../../includes/FunctionTimer.h
	@rm -f setphony2.i
	$$irs_pre setphony2.c >> setphony2.i
	@mv -f setphony2.i $(PREDIR)/setphony2.inst.i

$(PREDIR)/sewbndry.inst.i:sewbndry.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f sewbndry.i
	$$irs_pre sewbndry.c >> sewbndry.i
	@mv -f sewbndry.i $(PREDIR)/sewbndry.inst.i

$(PREDIR)/vsamein0.inst.i:vsamein0.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h
	@rm -f vsamein0.i
	$$irs_pre vsamein0.c >> vsamein0.i
	@mv -f vsamein0.i $(PREDIR)/vsamein0.inst.i

$(PREDIR)/vsameorg.inst.i:vsameorg.c ../../includes/irs.h                         \
	  ../../includes/irsbndry.h ../../includes/BlockMapping.h
	@rm -f vsameorg.i
	$$irs_pre vsameorg.c >> vsameorg.i
	@mv -f vsameorg.i $(PREDIR)/vsameorg.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libbndry_inst

libbndry_inst:$(BI)(bcin.inst.o) $(BI)(bcin0.inst.o) $(BI)(bcnorm.inst.o)         \
	  $(BI)(bndcopy.inst.o) $(BI)(bndin.inst.o) $(BI)(bndrydev.inst.o)        \
	  $(BI)(bndryinit.inst.o) $(BI)(bndzonelist.inst.o)                       \
	  $(BI)(genradreflst.inst.o) $(BI)(genreflst.inst.o)                      \
	  $(BI)(getbcname.inst.o) $(BI)(initbc.inst.o) $(BI)(irefzq.inst.o)       \
	  $(BI)(orient.inst.o) $(BI)(refadv2d.inst.o) $(BI)(refadv3d.inst.o)      \
	  $(BI)(refnd2d.inst.o) $(BI)(refnd3d.inst.o) $(BI)(refnd3ds.inst.o)      \
	  $(BI)(refradnq.inst.o) $(BI)(refzq.inst.o) $(BI)(setbndry.inst.o)       \
	  $(BI)(setcrnlst.inst.o) $(BI)(setphony.inst.o) $(BI)(setphony2.inst.o)  \
	  $(BI)(sewbndry.inst.o) $(BI)(vsamein0.inst.o) $(BI)(vsameorg.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libbndry_inst.a $(B); \
		ln -sf libbndry_inst.a $(B)); \
	  fi
	  @echo 'libbndry_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(bcin.inst.o):$(INSTDIR)/bcin.inst.i
	$$irs_post $(INSTDIR)/bcin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bcin.inst.i $(DB)/bcin.c 

$(BI)(bcin0.inst.o):$(INSTDIR)/bcin0.inst.i
	$$irs_post $(INSTDIR)/bcin0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bcin0.inst.i $(DB)/bcin0.c 

$(BI)(bcnorm.inst.o):$(INSTDIR)/bcnorm.inst.i
	$$irs_post $(INSTDIR)/bcnorm.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bcnorm.inst.i $(DB)/bcnorm.c 

$(BI)(bndcopy.inst.o):$(INSTDIR)/bndcopy.inst.i
	$$irs_post $(INSTDIR)/bndcopy.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bndcopy.inst.i $(DB)/bndcopy.c 

$(BI)(bndin.inst.o):$(INSTDIR)/bndin.inst.i
	$$irs_post $(INSTDIR)/bndin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bndin.inst.i $(DB)/bndin.c 

$(BI)(bndrydev.inst.o):$(INSTDIR)/bndrydev.inst.i
	$$irs_post $(INSTDIR)/bndrydev.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bndrydev.inst.i $(DB)/bndrydev.c 

$(BI)(bndryinit.inst.o):$(INSTDIR)/bndryinit.inst.i
	$$irs_post $(INSTDIR)/bndryinit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bndryinit.inst.i $(DB)/bndryinit.c 

$(BI)(bndzonelist.inst.o):$(INSTDIR)/bndzonelist.inst.i
	$$irs_post $(INSTDIR)/bndzonelist.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bndzonelist.inst.i $(DB)/bndzonelist.c 

$(BI)(genradreflst.inst.o):$(INSTDIR)/genradreflst.inst.i
	$$irs_post $(INSTDIR)/genradreflst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/genradreflst.inst.i $(DB)/genradreflst.c 

$(BI)(genreflst.inst.o):$(INSTDIR)/genreflst.inst.i
	$$irs_post $(INSTDIR)/genreflst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/genreflst.inst.i $(DB)/genreflst.c 

$(BI)(getbcname.inst.o):$(INSTDIR)/getbcname.inst.i
	$$irs_post $(INSTDIR)/getbcname.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getbcname.inst.i $(DB)/getbcname.c 

$(BI)(initbc.inst.o):$(INSTDIR)/initbc.inst.i
	$$irs_post $(INSTDIR)/initbc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/initbc.inst.i $(DB)/initbc.c 

$(BI)(irefzq.inst.o):$(INSTDIR)/irefzq.inst.i
	$$irs_post $(INSTDIR)/irefzq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/irefzq.inst.i $(DB)/irefzq.c 

$(BI)(orient.inst.o):$(INSTDIR)/orient.inst.i
	$$irs_post $(INSTDIR)/orient.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/orient.inst.i $(DB)/orient.c 

$(BI)(refadv2d.inst.o):$(INSTDIR)/refadv2d.inst.i
	$$irs_post $(INSTDIR)/refadv2d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/refadv2d.inst.i $(DB)/refadv2d.c 

$(BI)(refadv3d.inst.o):$(INSTDIR)/refadv3d.inst.i
	$$irs_post $(INSTDIR)/refadv3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/refadv3d.inst.i $(DB)/refadv3d.c 

$(BI)(refnd2d.inst.o):$(INSTDIR)/refnd2d.inst.i
	$$irs_post $(INSTDIR)/refnd2d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/refnd2d.inst.i $(DB)/refnd2d.c 

$(BI)(refnd3d.inst.o):$(INSTDIR)/refnd3d.inst.i
	$$irs_post $(INSTDIR)/refnd3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/refnd3d.inst.i $(DB)/refnd3d.c 

$(BI)(refnd3ds.inst.o):$(INSTDIR)/refnd3ds.inst.i
	$$irs_post $(INSTDIR)/refnd3ds.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/refnd3ds.inst.i $(DB)/refnd3ds.c 

$(BI)(refradnq.inst.o):$(INSTDIR)/refradnq.inst.i
	$$irs_post $(INSTDIR)/refradnq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/refradnq.inst.i $(DB)/refradnq.c 

$(BI)(refzq.inst.o):$(INSTDIR)/refzq.inst.i
	$$irs_post $(INSTDIR)/refzq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/refzq.inst.i $(DB)/refzq.c 

$(BI)(setbndry.inst.o):$(INSTDIR)/setbndry.inst.i
	$$irs_post $(INSTDIR)/setbndry.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setbndry.inst.i $(DB)/setbndry.c 

$(BI)(setcrnlst.inst.o):$(INSTDIR)/setcrnlst.inst.i
	$$irs_post $(INSTDIR)/setcrnlst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setcrnlst.inst.i $(DB)/setcrnlst.c 

$(BI)(setphony.inst.o):$(INSTDIR)/setphony.inst.i
	$$irs_post $(INSTDIR)/setphony.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setphony.inst.i $(DB)/setphony.c 

$(BI)(setphony2.inst.o):$(INSTDIR)/setphony2.inst.i
	$$irs_post $(INSTDIR)/setphony2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setphony2.inst.i $(DB)/setphony2.c 

$(BI)(sewbndry.inst.o):$(INSTDIR)/sewbndry.inst.i
	$$irs_post $(INSTDIR)/sewbndry.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/sewbndry.inst.i $(DB)/sewbndry.c 

$(BI)(vsamein0.inst.o):$(INSTDIR)/vsamein0.inst.i
	$$irs_post $(INSTDIR)/vsamein0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/vsamein0.inst.i $(DB)/vsamein0.c 

$(BI)(vsameorg.inst.o):$(INSTDIR)/vsameorg.inst.i
	$$irs_post $(INSTDIR)/vsameorg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/vsameorg.inst.i $(DB)/vsameorg.c 

DEP_SRCS = \
	bcin.c bcin0.c bcnorm.c bndcopy.c bndin.c bndrydev.c bndryinit.c bndzonelist.c  \
	genradreflst.c genreflst.c getbcname.c initbc.c irefzq.c orient.c refadv2d.c  \
	refadv3d.c refnd2d.c refnd3d.c refnd3ds.c refradnq.c refzq.c setbndry.c  \
	setcrnlst.c setphony.c setphony2.c sewbndry.c vsamein0.c vsameorg.c  

depend:
	@cp -f Makefile.bndry Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(bcin.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(bcin.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(bcin.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(bcin.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(bcin.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(bcin.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(bcin.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(bcin.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(bcin.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(bcin.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(bcin.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(bcin.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(bcin.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(bcin.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(bcin.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(bcin.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(bcin.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(bcin.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(bcin.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(bcin.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(bcin.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssrc.h
$(B)(bcin.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(bcin0.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(bcin0.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(bcin0.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(bcin0.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(bcin0.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(bcin0.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(bcin0.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(bcin0.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(bcin0.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(bcin0.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(bcin0.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(bcin0.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(bcin0.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(bcin0.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(bcin0.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(bcin0.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(bcin0.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(bcin0.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(bcin0.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(bcin0.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(bcin0.o): /usr/include/string.h /usr/include/malloc.h
$(B)(bcin0.o): ../../includes/irsbndry.h
$(B)(bcnorm.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(bcnorm.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(bcnorm.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(bcnorm.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(bcnorm.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(bcnorm.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(bcnorm.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(bcnorm.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(bcnorm.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(bcnorm.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(bcnorm.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(bcnorm.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(bcnorm.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(bcnorm.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(bcnorm.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(bcnorm.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(bcnorm.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(bcnorm.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(bcnorm.o): /usr/include/ctype.h /usr/include/math.h
$(B)(bcnorm.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(bcnorm.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(bcnorm.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(bndcopy.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(bndcopy.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(bndcopy.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(bndcopy.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(bndcopy.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(bndcopy.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(bndcopy.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(bndcopy.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(bndcopy.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(bndcopy.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(bndcopy.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(bndcopy.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(bndcopy.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(bndcopy.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(bndcopy.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(bndcopy.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(bndcopy.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(bndcopy.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(bndcopy.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(bndcopy.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(bndcopy.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(bndcopy.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(bndin.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(bndin.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(bndin.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(bndin.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(bndin.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(bndin.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(bndin.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(bndin.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(bndin.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(bndin.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(bndin.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(bndin.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(bndin.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(bndin.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(bndin.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(bndin.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(bndin.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(bndin.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(bndin.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(bndin.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(bndin.o): /usr/include/string.h /usr/include/malloc.h
$(B)(bndin.o): ../../includes/irsbndry.h ../../includes/BlockMapping.h
$(B)(bndin.o): ../../includes/BndMapping.h ../../includes/NodeList.h
$(B)(bndin.o): ../../includes/Extents.h
$(B)(bndrydev.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(bndrydev.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(bndrydev.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(bndrydev.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(bndrydev.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(bndrydev.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(bndrydev.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(bndrydev.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(bndrydev.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(bndrydev.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(bndrydev.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(bndrydev.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(bndrydev.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(bndrydev.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(bndrydev.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(bndrydev.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(bndrydev.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(bndrydev.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(bndrydev.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(bndrydev.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(bndrydev.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(bndrydev.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(bndrydev.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(bndrydev.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(bndrydev.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(bndrydev.o): ../../includes/Extents.h ../../includes/irsrgst.h
$(B)(bndrydev.o): ../../includes/ProblemArray.h
$(B)(bndryinit.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(bndryinit.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(bndryinit.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(bndryinit.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(bndryinit.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(bndryinit.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(bndryinit.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(bndryinit.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(bndryinit.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(bndryinit.o): /usr/include/time.h /usr/include/endian.h
$(B)(bndryinit.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(bndryinit.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(bndryinit.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(bndryinit.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(bndryinit.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(bndryinit.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(bndryinit.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(bndryinit.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(bndryinit.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(bndryinit.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(bndryinit.o): /usr/include/ctype.h /usr/include/math.h
$(B)(bndryinit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(bndryinit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(bndryinit.o): /usr/include/malloc.h ../../includes/irsblk.h
$(B)(bndryinit.o): ../../includes/Extents.h ../../includes/irsbndry.h
$(B)(bndryinit.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(bndryinit.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(bndryinit.o): ../../includes/irssys.h ../../includes/BlockMapping.h
$(B)(bndryinit.o): ../../includes/BndMapping.h ../../includes/ProblemArray.h
$(B)(bndzonelist.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(bndzonelist.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(bndzonelist.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(bndzonelist.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(bndzonelist.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(bndzonelist.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(bndzonelist.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(bndzonelist.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(bndzonelist.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(bndzonelist.o): /usr/include/time.h /usr/include/endian.h
$(B)(bndzonelist.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(bndzonelist.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(bndzonelist.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(bndzonelist.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(bndzonelist.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(bndzonelist.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(bndzonelist.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(bndzonelist.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(bndzonelist.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(bndzonelist.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(bndzonelist.o): /usr/include/ctype.h /usr/include/math.h
$(B)(bndzonelist.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(bndzonelist.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(bndzonelist.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(genradreflst.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(genradreflst.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(genradreflst.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(genradreflst.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(genradreflst.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(genradreflst.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(genradreflst.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(genradreflst.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(genradreflst.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(genradreflst.o): /usr/include/time.h /usr/include/endian.h
$(B)(genradreflst.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(genradreflst.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(genradreflst.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(genradreflst.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(genradreflst.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(genradreflst.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(genradreflst.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(genradreflst.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(genradreflst.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(genradreflst.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(genradreflst.o): /usr/include/ctype.h /usr/include/math.h
$(B)(genradreflst.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(genradreflst.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(genradreflst.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(genreflst.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(genreflst.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(genreflst.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(genreflst.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(genreflst.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(genreflst.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(genreflst.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(genreflst.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(genreflst.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(genreflst.o): /usr/include/time.h /usr/include/endian.h
$(B)(genreflst.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(genreflst.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(genreflst.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(genreflst.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(genreflst.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(genreflst.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(genreflst.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(genreflst.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(genreflst.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(genreflst.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(genreflst.o): /usr/include/ctype.h /usr/include/math.h
$(B)(genreflst.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(genreflst.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(genreflst.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(getbcname.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(getbcname.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(getbcname.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(getbcname.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(getbcname.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(getbcname.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getbcname.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getbcname.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getbcname.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(getbcname.o): /usr/include/time.h /usr/include/endian.h
$(B)(getbcname.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(getbcname.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(getbcname.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(getbcname.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(getbcname.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(getbcname.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(getbcname.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(getbcname.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(getbcname.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(getbcname.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(getbcname.o): /usr/include/ctype.h /usr/include/math.h
$(B)(getbcname.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getbcname.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(getbcname.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(initbc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(initbc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(initbc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(initbc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(initbc.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(initbc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(initbc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(initbc.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(initbc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(initbc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(initbc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(initbc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(initbc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(initbc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(initbc.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(initbc.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(initbc.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(initbc.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(initbc.o): /usr/include/ctype.h /usr/include/math.h
$(B)(initbc.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(initbc.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(initbc.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(irefzq.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(irefzq.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(irefzq.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(irefzq.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(irefzq.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(irefzq.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(irefzq.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(irefzq.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(irefzq.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(irefzq.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(irefzq.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(irefzq.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(irefzq.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(irefzq.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(irefzq.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(irefzq.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(irefzq.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(irefzq.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(irefzq.o): /usr/include/ctype.h /usr/include/math.h
$(B)(irefzq.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(irefzq.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(irefzq.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(orient.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(orient.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(orient.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(orient.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(orient.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(orient.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(orient.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(orient.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(orient.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(orient.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(orient.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(orient.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(orient.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(orient.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(orient.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(orient.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(orient.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(orient.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(orient.o): /usr/include/ctype.h /usr/include/math.h
$(B)(orient.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(orient.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(orient.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(orient.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(refadv2d.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(refadv2d.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(refadv2d.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(refadv2d.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(refadv2d.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(refadv2d.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(refadv2d.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(refadv2d.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(refadv2d.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(refadv2d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(refadv2d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(refadv2d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(refadv2d.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(refadv2d.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(refadv2d.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(refadv2d.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(refadv2d.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(refadv2d.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(refadv2d.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(refadv2d.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(refadv2d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(refadv2d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(refadv2d.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(refadv2d.o): ../../includes/FunctionTimer.h
$(B)(refadv3d.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(refadv3d.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(refadv3d.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(refadv3d.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(refadv3d.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(refadv3d.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(refadv3d.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(refadv3d.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(refadv3d.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(refadv3d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(refadv3d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(refadv3d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(refadv3d.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(refadv3d.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(refadv3d.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(refadv3d.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(refadv3d.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(refadv3d.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(refadv3d.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(refadv3d.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(refadv3d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(refadv3d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(refadv3d.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(refadv3d.o): ../../includes/FunctionTimer.h
$(B)(refnd2d.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(refnd2d.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(refnd2d.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(refnd2d.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(refnd2d.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(refnd2d.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(refnd2d.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(refnd2d.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(refnd2d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(refnd2d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(refnd2d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(refnd2d.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(refnd2d.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(refnd2d.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(refnd2d.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(refnd2d.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(refnd2d.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(refnd2d.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(refnd2d.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(refnd2d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(refnd2d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(refnd2d.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(refnd2d.o): ../../includes/FunctionTimer.h
$(B)(refnd3d.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(refnd3d.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(refnd3d.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(refnd3d.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(refnd3d.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(refnd3d.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(refnd3d.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(refnd3d.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(refnd3d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(refnd3d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(refnd3d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(refnd3d.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(refnd3d.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(refnd3d.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(refnd3d.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(refnd3d.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(refnd3d.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(refnd3d.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(refnd3d.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(refnd3d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(refnd3d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(refnd3d.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(refnd3d.o): ../../includes/FunctionTimer.h
$(B)(refnd3ds.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(refnd3ds.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(refnd3ds.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(refnd3ds.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(refnd3ds.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(refnd3ds.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(refnd3ds.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(refnd3ds.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(refnd3ds.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(refnd3ds.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(refnd3ds.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(refnd3ds.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(refnd3ds.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(refnd3ds.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(refnd3ds.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(refnd3ds.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(refnd3ds.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(refnd3ds.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(refnd3ds.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(refnd3ds.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(refnd3ds.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(refnd3ds.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(refnd3ds.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(refnd3ds.o): ../../includes/FunctionTimer.h
$(B)(refradnq.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(refradnq.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(refradnq.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(refradnq.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(refradnq.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(refradnq.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(refradnq.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(refradnq.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(refradnq.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(refradnq.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(refradnq.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(refradnq.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(refradnq.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(refradnq.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(refradnq.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(refradnq.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(refradnq.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(refradnq.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(refradnq.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(refradnq.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(refradnq.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(refradnq.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(refradnq.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(refradnq.o): ../../includes/FunctionTimer.h
$(B)(refzq.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(refzq.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(refzq.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(refzq.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(refzq.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(refzq.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(refzq.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(refzq.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(refzq.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(refzq.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(refzq.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(refzq.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(refzq.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(refzq.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(refzq.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(refzq.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(refzq.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(refzq.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(refzq.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(refzq.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(refzq.o): /usr/include/string.h /usr/include/malloc.h
$(B)(refzq.o): ../../includes/irsbndry.h ../../includes/FunctionTimer.h
$(B)(setbndry.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(setbndry.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(setbndry.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(setbndry.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(setbndry.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(setbndry.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(setbndry.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(setbndry.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(setbndry.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(setbndry.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(setbndry.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(setbndry.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(setbndry.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(setbndry.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(setbndry.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(setbndry.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(setbndry.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(setbndry.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(setbndry.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(setbndry.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(setbndry.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setbndry.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setbndry.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(setbndry.o): ../../includes/FunctionTimer.h
$(B)(setcrnlst.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(setcrnlst.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(setcrnlst.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(setcrnlst.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(setcrnlst.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(setcrnlst.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setcrnlst.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setcrnlst.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setcrnlst.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(setcrnlst.o): /usr/include/time.h /usr/include/endian.h
$(B)(setcrnlst.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(setcrnlst.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(setcrnlst.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(setcrnlst.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(setcrnlst.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(setcrnlst.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(setcrnlst.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(setcrnlst.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(setcrnlst.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(setcrnlst.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(setcrnlst.o): /usr/include/ctype.h /usr/include/math.h
$(B)(setcrnlst.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setcrnlst.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setcrnlst.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(setphony.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(setphony.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(setphony.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(setphony.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(setphony.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(setphony.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(setphony.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(setphony.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(setphony.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(setphony.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(setphony.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(setphony.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(setphony.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(setphony.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(setphony.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(setphony.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(setphony.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(setphony.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(setphony.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(setphony.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(setphony.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setphony.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setphony.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(setphony.o): ../../includes/FunctionTimer.h
$(B)(setphony2.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(setphony2.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(setphony2.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(setphony2.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(setphony2.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(setphony2.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setphony2.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setphony2.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setphony2.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(setphony2.o): /usr/include/time.h /usr/include/endian.h
$(B)(setphony2.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(setphony2.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(setphony2.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(setphony2.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(setphony2.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(setphony2.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(setphony2.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(setphony2.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(setphony2.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(setphony2.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(setphony2.o): /usr/include/ctype.h /usr/include/math.h
$(B)(setphony2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setphony2.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setphony2.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(setphony2.o): ../../includes/FunctionTimer.h
$(B)(sewbndry.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(sewbndry.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(sewbndry.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(sewbndry.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(sewbndry.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(sewbndry.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(sewbndry.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(sewbndry.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(sewbndry.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(sewbndry.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(sewbndry.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(sewbndry.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(sewbndry.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(sewbndry.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(sewbndry.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(sewbndry.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(sewbndry.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(sewbndry.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(sewbndry.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(sewbndry.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(sewbndry.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(sewbndry.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(sewbndry.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(sewbndry.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(sewbndry.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(sewbndry.o): ../../includes/Extents.h
$(B)(vsamein0.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(vsamein0.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(vsamein0.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(vsamein0.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(vsamein0.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(vsamein0.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(vsamein0.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(vsamein0.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(vsamein0.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(vsamein0.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(vsamein0.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(vsamein0.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(vsamein0.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(vsamein0.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(vsamein0.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(vsamein0.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(vsamein0.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(vsamein0.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(vsamein0.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(vsamein0.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(vsamein0.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(vsamein0.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(vsamein0.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(vsameorg.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(vsameorg.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(vsameorg.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(vsameorg.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(vsameorg.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(vsameorg.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(vsameorg.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(vsameorg.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(vsameorg.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(vsameorg.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(vsameorg.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(vsameorg.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(vsameorg.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(vsameorg.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(vsameorg.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(vsameorg.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(vsameorg.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(vsameorg.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(vsameorg.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(vsameorg.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(vsameorg.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(vsameorg.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(vsameorg.o): /usr/include/malloc.h ../../includes/irsbndry.h
$(B)(vsameorg.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
