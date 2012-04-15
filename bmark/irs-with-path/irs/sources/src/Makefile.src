
################################################################################
#
# Makefile for irs library src
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
B = ../$(LIB_DIR)/libsrc.a
BI = ../$(LIB_DIR)/libsrc_inst.a

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
SRCDIR = ../sources/src

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libsrc:$(B)(dsrc.o) $(B)(erate.o) $(B)(esrc.o) $(B)(psrc.o) $(B)(srccopy.o)       \
	  $(B)(srcin.o) $(B)(tmsrc.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'src library current'

# creation deps
#---------------
$(B)(dsrc.o):dsrc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/dsrc.c $(DB)/dsrc.c 

$(B)(erate.o):erate.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/erate.c $(DB)/erate.c 

$(B)(esrc.o):esrc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/esrc.c $(DB)/esrc.c 

$(B)(psrc.o):psrc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/psrc.c $(DB)/psrc.c 

$(B)(srccopy.o):srccopy.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/srccopy.c $(DB)/srccopy.c 

$(B)(srcin.o):srcin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/srcin.c $(DB)/srcin.c 

$(B)(tmsrc.o):tmsrc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tmsrc.c $(DB)/tmsrc.c 

#---------------------
# lint pass one target 
#---------------------
lint:dsrc.ln erate.ln esrc.ln psrc.ln srccopy.ln srcin.ln tmsrc.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
dsrc.ln:dsrc.c ../../includes/irs.h ../../includes/irssrc.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON dsrc.c ***' >> $(LO)
	$$irs_lint dsrc.c 2>&1 | tee -a $(LO)

erate.ln:erate.c ../../includes/irs.h ../../includes/irssrc.h                     \
	  ../../includes/FunctionTimer.h ../../includes/UserList.h                \
	  ../../includes/Region.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON erate.c ***' >> $(LO)
	$$irs_lint erate.c 2>&1 | tee -a $(LO)

esrc.ln:esrc.c ../../includes/irs.h ../../includes/irssrc.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON esrc.c ***' >> $(LO)
	$$irs_lint esrc.c 2>&1 | tee -a $(LO)

psrc.ln:psrc.c ../../includes/irs.h ../../includes/irssrc.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON psrc.c ***' >> $(LO)
	$$irs_lint psrc.c 2>&1 | tee -a $(LO)

srccopy.ln:srccopy.c ../../includes/irs.h ../../includes/irssrc.h                 \
	  ../../includes/Extents.h ../../includes/Source.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON srccopy.c ***' >> $(LO)
	$$irs_lint srccopy.c 2>&1 | tee -a $(LO)

srcin.ln:srcin.c ../../includes/irs.h ../../includes/irssrc.h                     \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/NodeList.h ../../includes/UserList.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON srcin.c ***' >> $(LO)
	$$irs_lint srcin.c 2>&1 | tee -a $(LO)

tmsrc.ln:tmsrc.c ../../includes/irs.h ../../includes/irssrc.h                     \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tmsrc.c ***' >> $(LO)
	$$irs_lint tmsrc.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/dsrc.inst.i $(PREDIR)/erate.inst.i $(PREDIR)/esrc.inst.i     \
	  $(PREDIR)/psrc.inst.i $(PREDIR)/srccopy.inst.i $(PREDIR)/srcin.inst.i   \
	  $(PREDIR)/tmsrc.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/dsrc.inst.i:dsrc.c ../../includes/irs.h ../../includes/irssrc.h         \
	  ../../includes/FunctionTimer.h
	@rm -f dsrc.i
	$$irs_pre dsrc.c >> dsrc.i
	@mv -f dsrc.i $(PREDIR)/dsrc.inst.i

$(PREDIR)/erate.inst.i:erate.c ../../includes/irs.h ../../includes/irssrc.h       \
	  ../../includes/FunctionTimer.h ../../includes/UserList.h                \
	  ../../includes/Region.h
	@rm -f erate.i
	$$irs_pre erate.c >> erate.i
	@mv -f erate.i $(PREDIR)/erate.inst.i

$(PREDIR)/esrc.inst.i:esrc.c ../../includes/irs.h ../../includes/irssrc.h         \
	  ../../includes/FunctionTimer.h
	@rm -f esrc.i
	$$irs_pre esrc.c >> esrc.i
	@mv -f esrc.i $(PREDIR)/esrc.inst.i

$(PREDIR)/psrc.inst.i:psrc.c ../../includes/irs.h ../../includes/irssrc.h         \
	  ../../includes/FunctionTimer.h
	@rm -f psrc.i
	$$irs_pre psrc.c >> psrc.i
	@mv -f psrc.i $(PREDIR)/psrc.inst.i

$(PREDIR)/srccopy.inst.i:srccopy.c ../../includes/irs.h ../../includes/irssrc.h   \
	  ../../includes/Extents.h ../../includes/Source.h
	@rm -f srccopy.i
	$$irs_pre srccopy.c >> srccopy.i
	@mv -f srccopy.i $(PREDIR)/srccopy.inst.i

$(PREDIR)/srcin.inst.i:srcin.c ../../includes/irs.h ../../includes/irssrc.h       \
	  ../../includes/BlockMapping.h ../../includes/Extents.h                  \
	  ../../includes/NodeList.h ../../includes/UserList.h
	@rm -f srcin.i
	$$irs_pre srcin.c >> srcin.i
	@mv -f srcin.i $(PREDIR)/srcin.inst.i

$(PREDIR)/tmsrc.inst.i:tmsrc.c ../../includes/irs.h ../../includes/irssrc.h       \
	  ../../includes/FunctionTimer.h
	@rm -f tmsrc.i
	$$irs_pre tmsrc.c >> tmsrc.i
	@mv -f tmsrc.i $(PREDIR)/tmsrc.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libsrc_inst

libsrc_inst:$(BI)(dsrc.inst.o) $(BI)(erate.inst.o) $(BI)(esrc.inst.o)             \
	  $(BI)(psrc.inst.o) $(BI)(srccopy.inst.o) $(BI)(srcin.inst.o)            \
	  $(BI)(tmsrc.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libsrc_inst.a $(B); \
		ln -sf libsrc_inst.a $(B)); \
	  fi
	  @echo 'libsrc_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(dsrc.inst.o):$(INSTDIR)/dsrc.inst.i
	$$irs_post $(INSTDIR)/dsrc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/dsrc.inst.i $(DB)/dsrc.c 

$(BI)(erate.inst.o):$(INSTDIR)/erate.inst.i
	$$irs_post $(INSTDIR)/erate.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/erate.inst.i $(DB)/erate.c 

$(BI)(esrc.inst.o):$(INSTDIR)/esrc.inst.i
	$$irs_post $(INSTDIR)/esrc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/esrc.inst.i $(DB)/esrc.c 

$(BI)(psrc.inst.o):$(INSTDIR)/psrc.inst.i
	$$irs_post $(INSTDIR)/psrc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/psrc.inst.i $(DB)/psrc.c 

$(BI)(srccopy.inst.o):$(INSTDIR)/srccopy.inst.i
	$$irs_post $(INSTDIR)/srccopy.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/srccopy.inst.i $(DB)/srccopy.c 

$(BI)(srcin.inst.o):$(INSTDIR)/srcin.inst.i
	$$irs_post $(INSTDIR)/srcin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/srcin.inst.i $(DB)/srcin.c 

$(BI)(tmsrc.inst.o):$(INSTDIR)/tmsrc.inst.i
	$$irs_post $(INSTDIR)/tmsrc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tmsrc.inst.i $(DB)/tmsrc.c 

DEP_SRCS = \
	dsrc.c erate.c esrc.c psrc.c srccopy.c srcin.c tmsrc.c  

depend:
	@cp -f Makefile.src Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

