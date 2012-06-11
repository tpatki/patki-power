
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

# DO NOT DELETE

$(B)(dsrc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(dsrc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(dsrc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(dsrc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(dsrc.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(dsrc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(dsrc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(dsrc.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(dsrc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(dsrc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(dsrc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(dsrc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(dsrc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(dsrc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(dsrc.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(dsrc.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(dsrc.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(dsrc.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(dsrc.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(dsrc.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(dsrc.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssrc.h
$(B)(dsrc.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(dsrc.o): ../../includes/FunctionTimer.h
$(B)(erate.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(erate.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(erate.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(erate.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(erate.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(erate.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(erate.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(erate.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(erate.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(erate.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(erate.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(erate.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(erate.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(erate.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(erate.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(erate.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(erate.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(erate.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(erate.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(erate.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(erate.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssrc.h
$(B)(erate.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(erate.o): ../../includes/FunctionTimer.h ../../includes/UserList.h
$(B)(erate.o): ../../includes/Region.h
$(B)(esrc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(esrc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(esrc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(esrc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(esrc.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(esrc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(esrc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(esrc.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(esrc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(esrc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(esrc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(esrc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(esrc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(esrc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(esrc.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(esrc.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(esrc.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(esrc.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(esrc.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(esrc.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(esrc.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssrc.h
$(B)(esrc.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(esrc.o): ../../includes/FunctionTimer.h
$(B)(psrc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(psrc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(psrc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(psrc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(psrc.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(psrc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(psrc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(psrc.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(psrc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(psrc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(psrc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(psrc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(psrc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(psrc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(psrc.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(psrc.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(psrc.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(psrc.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(psrc.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(psrc.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(psrc.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssrc.h
$(B)(psrc.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(psrc.o): ../../includes/FunctionTimer.h
$(B)(srccopy.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(srccopy.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(srccopy.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(srccopy.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(srccopy.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(srccopy.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(srccopy.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(srccopy.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(srccopy.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(srccopy.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(srccopy.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(srccopy.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(srccopy.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(srccopy.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(srccopy.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(srccopy.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(srccopy.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(srccopy.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(srccopy.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(srccopy.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(srccopy.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(srccopy.o): /usr/include/malloc.h ../../includes/irssrc.h
$(B)(srccopy.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(srcin.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(srcin.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(srcin.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(srcin.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(srcin.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(srcin.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(srcin.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(srcin.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(srcin.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(srcin.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(srcin.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(srcin.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(srcin.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(srcin.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(srcin.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(srcin.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(srcin.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(srcin.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(srcin.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(srcin.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(srcin.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssrc.h
$(B)(srcin.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(srcin.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(srcin.o): ../../includes/UserList.h
$(B)(tmsrc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(tmsrc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(tmsrc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(tmsrc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(tmsrc.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(tmsrc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(tmsrc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(tmsrc.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(tmsrc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(tmsrc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(tmsrc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(tmsrc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(tmsrc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(tmsrc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(tmsrc.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(tmsrc.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(tmsrc.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(tmsrc.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(tmsrc.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(tmsrc.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(tmsrc.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irssrc.h
$(B)(tmsrc.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(tmsrc.o): ../../includes/FunctionTimer.h
