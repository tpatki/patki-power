
################################################################################
#
# Makefile for irs library genrd
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
B = ../$(LIB_DIR)/libgenrd.a
BI = ../$(LIB_DIR)/libgenrd_inst.a

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
SRCDIR = ../sources/genrd

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libgenrd:$(B)(deck.o) $(B)(docmd.o) $(B)(endchk.o) $(B)(help.o) $(B)(inst_c.o)    \
	  $(B)(inst_com.o) $(B)(sargs.o) $(B)(sargse.o) $(B)(zargs.o)             \
	  $(B)(zargse.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'genrd library current'

# creation deps
#---------------
../../includes/irsgenrd.hh:../../includes/irsgenrd.h
	cp ../../includes/irsgenrd.h ../../includes/irsgenrd.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irsgenrd.hh
	irs_hhinit ../../includes/irsgenrd.hh

$(B)(deck.o):../../includes/irsgenrd.hh

$(B)(deck.o):deck.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/deck.c $(DB)/deck.c 

$(B)(docmd.o):docmd.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/docmd.c $(DB)/docmd.c 

$(B)(endchk.o):endchk.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/endchk.c $(DB)/endchk.c 

$(B)(help.o):help.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/help.c $(DB)/help.c 

$(B)(inst_c.o):inst_c.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/inst_c.c $(DB)/inst_c.c 

$(B)(inst_com.o):inst_com.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/inst_com.c $(DB)/inst_com.c 

$(B)(sargs.o):sargs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/sargs.c $(DB)/sargs.c 

$(B)(sargse.o):sargse.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/sargse.c $(DB)/sargse.c 

$(B)(zargs.o):zargs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/zargs.c $(DB)/zargs.c 

$(B)(zargse.o):zargse.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/zargse.c $(DB)/zargse.c 

#---------------------
# lint pass one target 
#---------------------
lint:deck.ln docmd.ln endchk.ln help.ln inst_c.ln inst_com.ln sargs.ln sargse.ln  \
	  zargs.ln zargse.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
deck.ln:deck.c ../../includes/irs.h ../../includes/irsgenrd.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON deck.c ***' >> $(LO)
	$$irs_lint deck.c 2>&1 | tee -a $(LO)

docmd.ln:docmd.c ../../includes/irs.h ../../includes/irsctl.h                     \
	  ../../includes/irsgen.h ../../includes/irsgenrd.h                       \
	  ../../includes/irsrgst.h ../../includes/AEStackElm.h                    \
	  ../../includes/Command.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON docmd.c ***' >> $(LO)
	$$irs_lint docmd.c 2>&1 | tee -a $(LO)

endchk.ln:endchk.c ../../includes/irs.h ../../includes/irsctl.h                   \
	  ../../includes/irsgenrd.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON endchk.c ***' >> $(LO)
	$$irs_lint endchk.c 2>&1 | tee -a $(LO)

help.ln:help.c ../../includes/irs.h ../../includes/irsgenrd.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON help.c ***' >> $(LO)
	$$irs_lint help.c 2>&1 | tee -a $(LO)

inst_c.ln:inst_c.c ../../includes/irs.h ../../includes/irsgenrd.h                 \
	  ../../includes/irsrgst.h ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON inst_c.c ***' >> $(LO)
	$$irs_lint inst_c.c 2>&1 | tee -a $(LO)

inst_com.ln:inst_com.c ../../includes/irs.h ../../includes/irsblk.h               \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsctl.h ../../includes/irscur.h                         \
	  ../../includes/irsdefs.h ../../includes/irsdmp.h                        \
	  ../../includes/irsedits.h ../../includes/irseos.h                       \
	  ../../includes/irsgen.h ../../includes/irsgenrd.h                       \
	  ../../includes/irslag.h ../../includes/irsobjects.h                     \
	  ../../includes/irsparm.h ../../includes/irsreg.h                        \
	  ../../includes/irsrgst.h ../../includes/irssrc.h                        \
	  ../../includes/irssys.h ../../includes/irstdiff.h ../../includes/irs.h  \
	  ../../includes/Command.h ../../includes/Conditional.h                   \
	  ../../includes/CycleMesg.h ../../includes/FreqMesg.h                    \
	  ../../includes/FunctionTimer.h ../../includes/Hash.h                    \
	  ../../includes/Spline.h ../../includes/TimePlot.h                       \
	  ../../includes/TimeStepControl.h ../../includes/Tracer.h                \
	  ../../includes/Transform.h ../../includes/UserList.h                    \
	  ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON inst_com.c ***' >> $(LO)
	$$irs_lint inst_com.c 2>&1 | tee -a $(LO)

sargs.ln:sargs.c ../../includes/irs.h ../../includes/irsgenrd.h                   \
	  ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON sargs.c ***' >> $(LO)
	$$irs_lint sargs.c 2>&1 | tee -a $(LO)

sargse.ln:sargse.c ../../includes/irs.h ../../includes/irsgenrd.h                 \
	  ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON sargse.c ***' >> $(LO)
	$$irs_lint sargse.c 2>&1 | tee -a $(LO)

zargs.ln:zargs.c ../../includes/irs.h ../../includes/irsgenrd.h                   \
	  ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON zargs.c ***' >> $(LO)
	$$irs_lint zargs.c 2>&1 | tee -a $(LO)

zargse.ln:zargse.c ../../includes/irs.h ../../includes/irsgenrd.h                 \
	  ../../includes/Command.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON zargse.c ***' >> $(LO)
	$$irs_lint zargse.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/deck.inst.i $(PREDIR)/docmd.inst.i $(PREDIR)/endchk.inst.i   \
	  $(PREDIR)/help.inst.i $(PREDIR)/inst_c.inst.i $(PREDIR)/inst_com.inst.i \
	  $(PREDIR)/sargs.inst.i $(PREDIR)/sargse.inst.i $(PREDIR)/zargs.inst.i   \
	  $(PREDIR)/zargse.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/deck.inst.i:deck.c ../../includes/irs.h ../../includes/irsgenrd.hh
	@rm -f deck.i
	$$irs_pre deck.c >> deck.i
	@mv -f deck.i $(PREDIR)/deck.inst.i

$(PREDIR)/docmd.inst.i:docmd.c ../../includes/irs.h ../../includes/irsctl.h       \
	  ../../includes/irsgen.h ../../includes/irsgenrd.h                       \
	  ../../includes/irsrgst.h ../../includes/AEStackElm.h                    \
	  ../../includes/Command.h ../../includes/Rgst.h
	@rm -f docmd.i
	$$irs_pre docmd.c >> docmd.i
	@mv -f docmd.i $(PREDIR)/docmd.inst.i

$(PREDIR)/endchk.inst.i:endchk.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/irsgenrd.h
	@rm -f endchk.i
	$$irs_pre endchk.c >> endchk.i
	@mv -f endchk.i $(PREDIR)/endchk.inst.i

$(PREDIR)/help.inst.i:help.c ../../includes/irs.h ../../includes/irsgenrd.h
	@rm -f help.i
	$$irs_pre help.c >> help.i
	@mv -f help.i $(PREDIR)/help.inst.i

$(PREDIR)/inst_c.inst.i:inst_c.c ../../includes/irs.h ../../includes/irsgenrd.h   \
	  ../../includes/irsrgst.h ../../includes/Command.h
	@rm -f inst_c.i
	$$irs_pre inst_c.c >> inst_c.i
	@mv -f inst_c.i $(PREDIR)/inst_c.inst.i

$(PREDIR)/inst_com.inst.i:inst_com.c ../../includes/irs.h ../../includes/irsblk.h \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsctl.h ../../includes/irscur.h                         \
	  ../../includes/irsdefs.h ../../includes/irsdmp.h                        \
	  ../../includes/irsedits.h ../../includes/irseos.h                       \
	  ../../includes/irsgen.h ../../includes/irsgenrd.h                       \
	  ../../includes/irslag.h ../../includes/irsobjects.h                     \
	  ../../includes/irsparm.h ../../includes/irsreg.h                        \
	  ../../includes/irsrgst.h ../../includes/irssrc.h                        \
	  ../../includes/irssys.h ../../includes/irstdiff.h ../../includes/irs.h  \
	  ../../includes/Command.h ../../includes/Conditional.h                   \
	  ../../includes/CycleMesg.h ../../includes/FreqMesg.h                    \
	  ../../includes/FunctionTimer.h ../../includes/Hash.h                    \
	  ../../includes/Spline.h ../../includes/TimePlot.h                       \
	  ../../includes/TimeStepControl.h ../../includes/Tracer.h                \
	  ../../includes/Transform.h ../../includes/UserList.h                    \
	  ../../includes/NodeList.h
	@rm -f inst_com.i
	$$irs_pre inst_com.c >> inst_com.i
	@mv -f inst_com.i $(PREDIR)/inst_com.inst.i

$(PREDIR)/sargs.inst.i:sargs.c ../../includes/irs.h ../../includes/irsgenrd.h     \
	  ../../includes/Command.h
	@rm -f sargs.i
	$$irs_pre sargs.c >> sargs.i
	@mv -f sargs.i $(PREDIR)/sargs.inst.i

$(PREDIR)/sargse.inst.i:sargse.c ../../includes/irs.h ../../includes/irsgenrd.h   \
	  ../../includes/Command.h
	@rm -f sargse.i
	$$irs_pre sargse.c >> sargse.i
	@mv -f sargse.i $(PREDIR)/sargse.inst.i

$(PREDIR)/zargs.inst.i:zargs.c ../../includes/irs.h ../../includes/irsgenrd.h     \
	  ../../includes/Command.h
	@rm -f zargs.i
	$$irs_pre zargs.c >> zargs.i
	@mv -f zargs.i $(PREDIR)/zargs.inst.i

$(PREDIR)/zargse.inst.i:zargse.c ../../includes/irs.h ../../includes/irsgenrd.h   \
	  ../../includes/Command.h
	@rm -f zargse.i
	$$irs_pre zargse.c >> zargse.i
	@mv -f zargse.i $(PREDIR)/zargse.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libgenrd_inst

libgenrd_inst:$(BI)(deck.inst.o) $(BI)(docmd.inst.o) $(BI)(endchk.inst.o)         \
	  $(BI)(help.inst.o) $(BI)(inst_c.inst.o) $(BI)(inst_com.inst.o)          \
	  $(BI)(sargs.inst.o) $(BI)(sargse.inst.o) $(BI)(zargs.inst.o)            \
	  $(BI)(zargse.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libgenrd_inst.a $(B); \
		ln -sf libgenrd_inst.a $(B)); \
	  fi
	  @echo 'libgenrd_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(deck.inst.o):$(INSTDIR)/deck.inst.i
	$$irs_post $(INSTDIR)/deck.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/deck.inst.i $(DB)/deck.c 

$(BI)(docmd.inst.o):$(INSTDIR)/docmd.inst.i
	$$irs_post $(INSTDIR)/docmd.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/docmd.inst.i $(DB)/docmd.c 

$(BI)(endchk.inst.o):$(INSTDIR)/endchk.inst.i
	$$irs_post $(INSTDIR)/endchk.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/endchk.inst.i $(DB)/endchk.c 

$(BI)(help.inst.o):$(INSTDIR)/help.inst.i
	$$irs_post $(INSTDIR)/help.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/help.inst.i $(DB)/help.c 

$(BI)(inst_c.inst.o):$(INSTDIR)/inst_c.inst.i
	$$irs_post $(INSTDIR)/inst_c.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/inst_c.inst.i $(DB)/inst_c.c 

$(BI)(inst_com.inst.o):$(INSTDIR)/inst_com.inst.i
	$$irs_post $(INSTDIR)/inst_com.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/inst_com.inst.i $(DB)/inst_com.c 

$(BI)(sargs.inst.o):$(INSTDIR)/sargs.inst.i
	$$irs_post $(INSTDIR)/sargs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/sargs.inst.i $(DB)/sargs.c 

$(BI)(sargse.inst.o):$(INSTDIR)/sargse.inst.i
	$$irs_post $(INSTDIR)/sargse.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/sargse.inst.i $(DB)/sargse.c 

$(BI)(zargs.inst.o):$(INSTDIR)/zargs.inst.i
	$$irs_post $(INSTDIR)/zargs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/zargs.inst.i $(DB)/zargs.c 

$(BI)(zargse.inst.o):$(INSTDIR)/zargse.inst.i
	$$irs_post $(INSTDIR)/zargse.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/zargse.inst.i $(DB)/zargse.c 

DEP_SRCS = \
	deck.c docmd.c endchk.c help.c inst_c.c inst_com.c sargs.c sargse.c zargs.c  \
	zargse.c  

depend:
	@cp -f Makefile.genrd Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

