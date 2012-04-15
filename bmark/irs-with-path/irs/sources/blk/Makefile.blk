
################################################################################
#
# Makefile for irs library blk
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
B = ../$(LIB_DIR)/libblk.a
BI = ../$(LIB_DIR)/libblk_inst.a

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
SRCDIR = ../sources/blk

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libblk:$(B)(Blocks.o) $(B)(blkdiv.o) $(B)(blkdivin.o) $(B)(blkgen.o)              \
	  $(B)(blockin0.o) $(B)(domain.o) $(B)(domaincopy.o) $(B)(extents.o)      \
	  $(B)(initblk.o) $(B)(reblkdiv.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'blk library current'

# creation deps
#---------------
$(B)(Blocks.o):Blocks.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/Blocks.c $(DB)/Blocks.c 

$(B)(blkdiv.o):blkdiv.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/blkdiv.c $(DB)/blkdiv.c 

$(B)(blkdivin.o):blkdivin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/blkdivin.c $(DB)/blkdivin.c 

$(B)(blkgen.o):blkgen.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/blkgen.c $(DB)/blkgen.c 

$(B)(blockin0.o):blockin0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/blockin0.c $(DB)/blockin0.c 

$(B)(domain.o):domain.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/domain.c $(DB)/domain.c 

$(B)(domaincopy.o):domaincopy.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/domaincopy.c $(DB)/domaincopy.c 

$(B)(extents.o):extents.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/extents.c $(DB)/extents.c 

$(B)(initblk.o):initblk.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/initblk.c $(DB)/initblk.c 

$(B)(reblkdiv.o):reblkdiv.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/reblkdiv.c $(DB)/reblkdiv.c 

#---------------------
# lint pass one target 
#---------------------
lint:Blocks.ln blkdiv.ln blkdivin.ln blkgen.ln blockin0.ln domain.ln              \
	  domaincopy.ln extents.ln initblk.ln reblkdiv.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
Blocks.ln:Blocks.c ../../includes/irs.h ../../includes/irsblk.h                   \
	  ../../includes/irsbndry.h ../../includes/irsctl.h                       \
	  ../../includes/irsobjects.h ../../includes/irscom.h                     \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/FunctionTimer.h ../../includes/UserList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON Blocks.c ***' >> $(LO)
	$$irs_lint Blocks.c 2>&1 | tee -a $(LO)

blkdiv.ln:blkdiv.c ../../includes/irs.h ../../includes/irsgen.h                   \
	  ../../includes/irsblk.h ../../includes/irsreg.h                         \
	  ../../includes/BlockMapping.h ../../includes/Extents.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON blkdiv.c ***' >> $(LO)
	$$irs_lint blkdiv.c 2>&1 | tee -a $(LO)

blkdivin.ln:blkdivin.c ../../includes/irs.h ../../includes/irsblk.h               \
	  ../../includes/irscom.h ../../includes/irsctl.h                         \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON blkdivin.c ***' >> $(LO)
	$$irs_lint blkdivin.c 2>&1 | tee -a $(LO)

blkgen.ln:blkgen.c ../../includes/irs.h ../../includes/irssrc.h                   \
	  ../../includes/irsbndry.h ../../includes/irsblk.h                       \
	  ../../includes/irsgen.h ../../includes/irsreg.h                         \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Command.h ../../includes/Source.h                        \
	  ../../includes/Domain.h ../../includes/Rgst.h ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON blkgen.c ***' >> $(LO)
	$$irs_lint blkgen.c 2>&1 | tee -a $(LO)

blockin0.ln:blockin0.c ../../includes/irs.h ../../includes/irsblk.h               \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsctl.h ../../includes/BlockMapping.h                   \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON blockin0.c ***' >> $(LO)
	$$irs_lint blockin0.c 2>&1 | tee -a $(LO)

domain.ln:domain.c ../../includes/irs.h ../../includes/irsblk.h                   \
	  ../../includes/irscom.h ../../includes/irsobjects.h                     \
	  ../../includes/irsparm.h ../../includes/irsreg.h                        \
	  ../../includes/irsrgst.h ../../includes/BoundaryCondition.h             \
	  ../../includes/Boundary.h ../../includes/Command.h                      \
	  ../../includes/Domain.h ../../includes/Hash.h                           \
	  ../../includes/ProblemArray.h ../../includes/FunctionTimer.h            \
	  ../../includes/Rgst.h ../../includes/SpeciesFraction.h                  \
	  ../../includes/TimeStepControl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON domain.c ***' >> $(LO)
	$$irs_lint domain.c 2>&1 | tee -a $(LO)

domaincopy.ln:domaincopy.c ../../includes/irs.h ../../includes/irssrc.h           \
	  ../../includes/irsblk.h ../../includes/irsbndry.h                       \
	  ../../includes/irsrgst.h ../../includes/irsreg.h ../../includes/pint.h  \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/Region.h ../../includes/SpeciesFraction.h                \
	  ../../includes/Extents.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON domaincopy.c ***' >> $(LO)
	$$irs_lint domaincopy.c 2>&1 | tee -a $(LO)

extents.ln:extents.c ../../includes/irs.h ../../includes/irsblk.h                 \
	  ../../includes/Extents.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON extents.c ***' >> $(LO)
	$$irs_lint extents.c 2>&1 | tee -a $(LO)

initblk.ln:initblk.c ../../includes/irs.h ../../includes/irsgen.h                 \
	  ../../includes/irsblk.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON initblk.c ***' >> $(LO)
	$$irs_lint initblk.c 2>&1 | tee -a $(LO)

reblkdiv.ln:reblkdiv.c ../../includes/irs.h ../../includes/irsblk.h               \
	  ../../includes/irscom.h ../../includes/irsdmp.h ../../includes/irsgen.h \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Extents.h ../../includes/NodeList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON reblkdiv.c ***' >> $(LO)
	$$irs_lint reblkdiv.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/Blocks.inst.i $(PREDIR)/blkdiv.inst.i                        \
	  $(PREDIR)/blkdivin.inst.i $(PREDIR)/blkgen.inst.i                       \
	  $(PREDIR)/blockin0.inst.i $(PREDIR)/domain.inst.i                       \
	  $(PREDIR)/domaincopy.inst.i $(PREDIR)/extents.inst.i                    \
	  $(PREDIR)/initblk.inst.i $(PREDIR)/reblkdiv.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/Blocks.inst.i:Blocks.c ../../includes/irs.h ../../includes/irsblk.h     \
	  ../../includes/irsbndry.h ../../includes/irsctl.h                       \
	  ../../includes/irsobjects.h ../../includes/irscom.h                     \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/FunctionTimer.h ../../includes/UserList.h
	@rm -f Blocks.i
	$$irs_pre Blocks.c >> Blocks.i
	@mv -f Blocks.i $(PREDIR)/Blocks.inst.i

$(PREDIR)/blkdiv.inst.i:blkdiv.c ../../includes/irs.h ../../includes/irsgen.h     \
	  ../../includes/irsblk.h ../../includes/irsreg.h                         \
	  ../../includes/BlockMapping.h ../../includes/Extents.h
	@rm -f blkdiv.i
	$$irs_pre blkdiv.c >> blkdiv.i
	@mv -f blkdiv.i $(PREDIR)/blkdiv.inst.i

$(PREDIR)/blkdivin.inst.i:blkdivin.c ../../includes/irs.h ../../includes/irsblk.h \
	  ../../includes/irscom.h ../../includes/irsctl.h                         \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/FunctionTimer.h
	@rm -f blkdivin.i
	$$irs_pre blkdivin.c >> blkdivin.i
	@mv -f blkdivin.i $(PREDIR)/blkdivin.inst.i

$(PREDIR)/blkgen.inst.i:blkgen.c ../../includes/irs.h ../../includes/irssrc.h     \
	  ../../includes/irsbndry.h ../../includes/irsblk.h                       \
	  ../../includes/irsgen.h ../../includes/irsreg.h                         \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Command.h ../../includes/Source.h                        \
	  ../../includes/Domain.h ../../includes/Rgst.h ../../includes/Region.h
	@rm -f blkgen.i
	$$irs_pre blkgen.c >> blkgen.i
	@mv -f blkgen.i $(PREDIR)/blkgen.inst.i

$(PREDIR)/blockin0.inst.i:blockin0.c ../../includes/irs.h ../../includes/irsblk.h \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irsctl.h ../../includes/BlockMapping.h                   \
	  ../../includes/FunctionTimer.h
	@rm -f blockin0.i
	$$irs_pre blockin0.c >> blockin0.i
	@mv -f blockin0.i $(PREDIR)/blockin0.inst.i

$(PREDIR)/domain.inst.i:domain.c ../../includes/irs.h ../../includes/irsblk.h     \
	  ../../includes/irscom.h ../../includes/irsobjects.h                     \
	  ../../includes/irsparm.h ../../includes/irsreg.h                        \
	  ../../includes/irsrgst.h ../../includes/BoundaryCondition.h             \
	  ../../includes/Boundary.h ../../includes/Command.h                      \
	  ../../includes/Domain.h ../../includes/Hash.h                           \
	  ../../includes/ProblemArray.h ../../includes/FunctionTimer.h            \
	  ../../includes/Rgst.h ../../includes/SpeciesFraction.h                  \
	  ../../includes/TimeStepControl.h
	@rm -f domain.i
	$$irs_pre domain.c >> domain.i
	@mv -f domain.i $(PREDIR)/domain.inst.i

$(PREDIR)/domaincopy.inst.i:domaincopy.c ../../includes/irs.h                     \
	  ../../includes/irssrc.h ../../includes/irsblk.h                         \
	  ../../includes/irsbndry.h ../../includes/irsrgst.h                      \
	  ../../includes/irsreg.h ../../includes/pint.h                           \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/Region.h ../../includes/SpeciesFraction.h                \
	  ../../includes/Extents.h
	@rm -f domaincopy.i
	$$irs_pre domaincopy.c >> domaincopy.i
	@mv -f domaincopy.i $(PREDIR)/domaincopy.inst.i

$(PREDIR)/extents.inst.i:extents.c ../../includes/irs.h ../../includes/irsblk.h   \
	  ../../includes/Extents.h
	@rm -f extents.i
	$$irs_pre extents.c >> extents.i
	@mv -f extents.i $(PREDIR)/extents.inst.i

$(PREDIR)/initblk.inst.i:initblk.c ../../includes/irs.h ../../includes/irsgen.h   \
	  ../../includes/irsblk.h
	@rm -f initblk.i
	$$irs_pre initblk.c >> initblk.i
	@mv -f initblk.i $(PREDIR)/initblk.inst.i

$(PREDIR)/reblkdiv.inst.i:reblkdiv.c ../../includes/irs.h ../../includes/irsblk.h \
	  ../../includes/irscom.h ../../includes/irsdmp.h ../../includes/irsgen.h \
	  ../../includes/irsrgst.h ../../includes/BlockMapping.h                  \
	  ../../includes/Extents.h ../../includes/NodeList.h
	@rm -f reblkdiv.i
	$$irs_pre reblkdiv.c >> reblkdiv.i
	@mv -f reblkdiv.i $(PREDIR)/reblkdiv.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libblk_inst

libblk_inst:$(BI)(Blocks.inst.o) $(BI)(blkdiv.inst.o) $(BI)(blkdivin.inst.o)      \
	  $(BI)(blkgen.inst.o) $(BI)(blockin0.inst.o) $(BI)(domain.inst.o)        \
	  $(BI)(domaincopy.inst.o) $(BI)(extents.inst.o) $(BI)(initblk.inst.o)    \
	  $(BI)(reblkdiv.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libblk_inst.a $(B); \
		ln -sf libblk_inst.a $(B)); \
	  fi
	  @echo 'libblk_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(Blocks.inst.o):$(INSTDIR)/Blocks.inst.i
	$$irs_post $(INSTDIR)/Blocks.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/Blocks.inst.i $(DB)/Blocks.c 

$(BI)(blkdiv.inst.o):$(INSTDIR)/blkdiv.inst.i
	$$irs_post $(INSTDIR)/blkdiv.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/blkdiv.inst.i $(DB)/blkdiv.c 

$(BI)(blkdivin.inst.o):$(INSTDIR)/blkdivin.inst.i
	$$irs_post $(INSTDIR)/blkdivin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/blkdivin.inst.i $(DB)/blkdivin.c 

$(BI)(blkgen.inst.o):$(INSTDIR)/blkgen.inst.i
	$$irs_post $(INSTDIR)/blkgen.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/blkgen.inst.i $(DB)/blkgen.c 

$(BI)(blockin0.inst.o):$(INSTDIR)/blockin0.inst.i
	$$irs_post $(INSTDIR)/blockin0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/blockin0.inst.i $(DB)/blockin0.c 

$(BI)(domain.inst.o):$(INSTDIR)/domain.inst.i
	$$irs_post $(INSTDIR)/domain.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/domain.inst.i $(DB)/domain.c 

$(BI)(domaincopy.inst.o):$(INSTDIR)/domaincopy.inst.i
	$$irs_post $(INSTDIR)/domaincopy.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/domaincopy.inst.i $(DB)/domaincopy.c 

$(BI)(extents.inst.o):$(INSTDIR)/extents.inst.i
	$$irs_post $(INSTDIR)/extents.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/extents.inst.i $(DB)/extents.c 

$(BI)(initblk.inst.o):$(INSTDIR)/initblk.inst.i
	$$irs_post $(INSTDIR)/initblk.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/initblk.inst.i $(DB)/initblk.c 

$(BI)(reblkdiv.inst.o):$(INSTDIR)/reblkdiv.inst.i
	$$irs_post $(INSTDIR)/reblkdiv.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/reblkdiv.inst.i $(DB)/reblkdiv.c 

DEP_SRCS = \
	Blocks.c blkdiv.c blkdivin.c blkgen.c blockin0.c domain.c domaincopy.c  \
	extents.c initblk.c reblkdiv.c  

depend:
	@cp -f Makefile.blk Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

