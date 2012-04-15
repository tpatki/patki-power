
################################################################################
#
# Makefile for irs library cur
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
B = ../$(LIB_DIR)/libcur.a
BI = ../$(LIB_DIR)/libcur_inst.a

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
SRCDIR = ../sources/cur

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libcur:$(B)(clrcur.o) $(B)(curbold.o) $(B)(curbop.o) $(B)(curgetxy.o)             \
	  $(B)(curgetxy0.o) $(B)(curlmt.o) $(B)(curwrtxy.o) $(B)(curwrtxy0.o)     \
	  $(B)(delcur.o) $(B)(delcur0.o) $(B)(dobop.o) $(B)(dorop.o)              \
	  $(B)(getcur.o) $(B)(getcurroot.o) $(B)(getnxcn.o) $(B)(getvec.o)        \
	  $(B)(getvec1.o) $(B)(getvectp.o) $(B)(irsfmax.o) $(B)(irsfmin.o)        \
	  $(B)(pamp.o) $(B)(plot.o) $(B)(plotmd.o) $(B)(setcur.o) $(B)(setcur0.o) \
	  $(B)(stoplot.o) $(B)(tpamp.o) $(B)(tplot.o) $(B)(xlim.o) $(B)(ylim.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'cur library current'

# creation deps
#---------------
$(B)(clrcur.o):clrcur.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/clrcur.c $(DB)/clrcur.c 

$(B)(curbold.o):curbold.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/curbold.c $(DB)/curbold.c 

$(B)(curbop.o):curbop.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/curbop.c $(DB)/curbop.c 

../../includes/irscur.hh:../../includes/irscur.h
	cp ../../includes/irscur.h ../../includes/irscur.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irscur.hh
	irs_hhinit ../../includes/irscur.hh

$(B)(curgetxy.o):../../includes/irscur.hh

$(B)(curgetxy.o):curgetxy.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/curgetxy.c $(DB)/curgetxy.c 

$(B)(curgetxy0.o):curgetxy0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/curgetxy0.c $(DB)/curgetxy0.c 

$(B)(curlmt.o):curlmt.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/curlmt.c $(DB)/curlmt.c 

$(B)(curwrtxy.o):curwrtxy.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/curwrtxy.c $(DB)/curwrtxy.c 

$(B)(curwrtxy0.o):curwrtxy0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/curwrtxy0.c $(DB)/curwrtxy0.c 

$(B)(delcur.o):delcur.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/delcur.c $(DB)/delcur.c 

$(B)(delcur0.o):delcur0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/delcur0.c $(DB)/delcur0.c 

$(B)(dobop.o):dobop.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/dobop.c $(DB)/dobop.c 

$(B)(dorop.o):dorop.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/dorop.c $(DB)/dorop.c 

$(B)(getcur.o):getcur.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getcur.c $(DB)/getcur.c 

$(B)(getcurroot.o):getcurroot.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getcurroot.c $(DB)/getcurroot.c 

$(B)(getnxcn.o):getnxcn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getnxcn.c $(DB)/getnxcn.c 

$(B)(getvec.o):getvec.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getvec.c $(DB)/getvec.c 

$(B)(getvec1.o):getvec1.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getvec1.c $(DB)/getvec1.c 

$(B)(getvectp.o):getvectp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getvectp.c $(DB)/getvectp.c 

$(B)(irsfmax.o):irsfmax.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/irsfmax.c $(DB)/irsfmax.c 

$(B)(irsfmin.o):irsfmin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/irsfmin.c $(DB)/irsfmin.c 

$(B)(pamp.o):pamp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/pamp.c $(DB)/pamp.c 

$(B)(plot.o):plot.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/plot.c $(DB)/plot.c 

$(B)(plotmd.o):plotmd.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/plotmd.c $(DB)/plotmd.c 

$(B)(setcur.o):setcur.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setcur.c $(DB)/setcur.c 

$(B)(setcur0.o):setcur0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setcur0.c $(DB)/setcur0.c 

$(B)(stoplot.o):stoplot.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/stoplot.c $(DB)/stoplot.c 

$(B)(tpamp.o):tpamp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tpamp.c $(DB)/tpamp.c 

$(B)(tplot.o):tplot.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tplot.c $(DB)/tplot.c 

$(B)(xlim.o):xlim.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/xlim.c $(DB)/xlim.c 

$(B)(ylim.o):ylim.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ylim.c $(DB)/ylim.c 

#---------------------
# lint pass one target 
#---------------------
lint:clrcur.ln curbold.ln curbop.ln curgetxy.ln curgetxy0.ln curlmt.ln            \
	  curwrtxy.ln curwrtxy0.ln delcur.ln delcur0.ln dobop.ln dorop.ln         \
	  getcur.ln getcurroot.ln getnxcn.ln getvec.ln getvec1.ln getvectp.ln     \
	  irsfmax.ln irsfmin.ln pamp.ln plot.ln plotmd.ln setcur.ln setcur0.ln    \
	  stoplot.ln tpamp.ln tplot.ln xlim.ln ylim.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
clrcur.ln:clrcur.c ../../includes/irs.h ../../includes/cgl.h                      \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON clrcur.c ***' >> $(LO)
	$$irs_lint clrcur.c 2>&1 | tee -a $(LO)

curbold.ln:curbold.c ../../includes/irs.h ../../includes/cgl.h                    \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON curbold.c ***' >> $(LO)
	$$irs_lint curbold.c 2>&1 | tee -a $(LO)

curbop.ln:curbop.c ../../includes/irs.h ../../includes/cgl.h                      \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON curbop.c ***' >> $(LO)
	$$irs_lint curbop.c 2>&1 | tee -a $(LO)

curgetxy.ln:curgetxy.c ../../includes/irs.h ../../includes/cgl.h                  \
	  ../../includes/irscur.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON curgetxy.c ***' >> $(LO)
	$$irs_lint curgetxy.c 2>&1 | tee -a $(LO)

curgetxy0.ln:curgetxy0.c ../../includes/irs.h ../../includes/cgl.h                \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON curgetxy0.c ***' >> $(LO)
	$$irs_lint curgetxy0.c 2>&1 | tee -a $(LO)

curlmt.ln:curlmt.c ../../includes/irs.h ../../includes/cgl.h                      \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON curlmt.c ***' >> $(LO)
	$$irs_lint curlmt.c 2>&1 | tee -a $(LO)

curwrtxy.ln:curwrtxy.c ../../includes/irs.h ../../includes/cgl.h                  \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON curwrtxy.c ***' >> $(LO)
	$$irs_lint curwrtxy.c 2>&1 | tee -a $(LO)

curwrtxy0.ln:curwrtxy0.c ../../includes/irs.h ../../includes/cgl.h                \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON curwrtxy0.c ***' >> $(LO)
	$$irs_lint curwrtxy0.c 2>&1 | tee -a $(LO)

delcur.ln:delcur.c ../../includes/irs.h ../../includes/cgl.h                      \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON delcur.c ***' >> $(LO)
	$$irs_lint delcur.c 2>&1 | tee -a $(LO)

delcur0.ln:delcur0.c ../../includes/irs.h ../../includes/cgl.h                    \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON delcur0.c ***' >> $(LO)
	$$irs_lint delcur0.c 2>&1 | tee -a $(LO)

dobop.ln:dobop.c ../../includes/irs.h ../../includes/cgl.h                        \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON dobop.c ***' >> $(LO)
	$$irs_lint dobop.c 2>&1 | tee -a $(LO)

dorop.ln:dorop.c ../../includes/irs.h ../../includes/cgl.h                        \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON dorop.c ***' >> $(LO)
	$$irs_lint dorop.c 2>&1 | tee -a $(LO)

getcur.ln:getcur.c ../../includes/irs.h ../../includes/cgl.h                      \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getcur.c ***' >> $(LO)
	$$irs_lint getcur.c 2>&1 | tee -a $(LO)

getcurroot.ln:getcurroot.c ../../includes/irs.h ../../includes/cgl.h              \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getcurroot.c ***' >> $(LO)
	$$irs_lint getcurroot.c 2>&1 | tee -a $(LO)

getnxcn.ln:getnxcn.c ../../includes/irs.h ../../includes/cgl.h                    \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getnxcn.c ***' >> $(LO)
	$$irs_lint getnxcn.c 2>&1 | tee -a $(LO)

getvec.ln:getvec.c ../../includes/irs.h ../../includes/irsrgst.h                  \
	  ../../includes/irscur.h ../../includes/cgl.h ../../includes/Hash.h      \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/VectorStruct.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getvec.c ***' >> $(LO)
	$$irs_lint getvec.c 2>&1 | tee -a $(LO)

getvec1.ln:getvec1.c ../../includes/irs.h ../../includes/irsgen.h                 \
	  ../../includes/cgl.h ../../includes/irscur.h ../../includes/NodeList.h  \
	  ../../includes/VectorStruct.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getvec1.c ***' >> $(LO)
	$$irs_lint getvec1.c 2>&1 | tee -a $(LO)

getvectp.ln:getvectp.c ../../includes/irs.h ../../includes/cgl.h                  \
	  ../../includes/irscur.h ../../includes/VectorStruct.h                   \
	  ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getvectp.c ***' >> $(LO)
	$$irs_lint getvectp.c 2>&1 | tee -a $(LO)

irsfmax.ln:irsfmax.c ../../includes/irs.h ../../includes/cgl.h                    \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON irsfmax.c ***' >> $(LO)
	$$irs_lint irsfmax.c 2>&1 | tee -a $(LO)

irsfmin.ln:irsfmin.c ../../includes/irs.h ../../includes/cgl.h                    \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON irsfmin.c ***' >> $(LO)
	$$irs_lint irsfmin.c 2>&1 | tee -a $(LO)

pamp.ln:pamp.c ../../includes/irs.h ../../includes/cgl.h                          \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON pamp.c ***' >> $(LO)
	$$irs_lint pamp.c 2>&1 | tee -a $(LO)

plot.ln:plot.c ../../includes/irs.h ../../includes/cgl.h                          \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON plot.c ***' >> $(LO)
	$$irs_lint plot.c 2>&1 | tee -a $(LO)

plotmd.ln:plotmd.c ../../includes/irs.h ../../includes/cgl.h                      \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON plotmd.c ***' >> $(LO)
	$$irs_lint plotmd.c 2>&1 | tee -a $(LO)

setcur.ln:setcur.c ../../includes/irs.h ../../includes/cgl.h                      \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setcur.c ***' >> $(LO)
	$$irs_lint setcur.c 2>&1 | tee -a $(LO)

setcur0.ln:setcur0.c ../../includes/irs.h ../../includes/cgl.h                    \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setcur0.c ***' >> $(LO)
	$$irs_lint setcur0.c 2>&1 | tee -a $(LO)

stoplot.ln:stoplot.c ../../includes/irs.h ../../includes/irscur.h                 \
	  ../../includes/irsctl.h ../../includes/irsgenrd.h                       \
	  ../../includes/irsrgst.h ../../includes/cgl.h                           \
	  ../../includes/AEStackElm.h ../../includes/Hash.h                       \
	  ../../includes/FunctionTimer.h ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON stoplot.c ***' >> $(LO)
	$$irs_lint stoplot.c 2>&1 | tee -a $(LO)

tpamp.ln:tpamp.c ../../includes/irs.h ../../includes/irscom.h                     \
	  ../../includes/irscur.h ../../includes/cgl.h                            \
	  ../../includes/FunctionTimer.h ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tpamp.c ***' >> $(LO)
	$$irs_lint tpamp.c 2>&1 | tee -a $(LO)

tplot.ln:tplot.c ../../includes/irs.h ../../includes/cgl.h                        \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tplot.c ***' >> $(LO)
	$$irs_lint tplot.c 2>&1 | tee -a $(LO)

xlim.ln:xlim.c ../../includes/irs.h ../../includes/cgl.h                          \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON xlim.c ***' >> $(LO)
	$$irs_lint xlim.c 2>&1 | tee -a $(LO)

ylim.ln:ylim.c ../../includes/irs.h ../../includes/cgl.h                          \
	  ../../includes/irscur.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ylim.c ***' >> $(LO)
	$$irs_lint ylim.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/clrcur.inst.i $(PREDIR)/curbold.inst.i                       \
	  $(PREDIR)/curbop.inst.i $(PREDIR)/curgetxy.inst.i                       \
	  $(PREDIR)/curgetxy0.inst.i $(PREDIR)/curlmt.inst.i                      \
	  $(PREDIR)/curwrtxy.inst.i $(PREDIR)/curwrtxy0.inst.i                    \
	  $(PREDIR)/delcur.inst.i $(PREDIR)/delcur0.inst.i $(PREDIR)/dobop.inst.i \
	  $(PREDIR)/dorop.inst.i $(PREDIR)/getcur.inst.i                          \
	  $(PREDIR)/getcurroot.inst.i $(PREDIR)/getnxcn.inst.i                    \
	  $(PREDIR)/getvec.inst.i $(PREDIR)/getvec1.inst.i                        \
	  $(PREDIR)/getvectp.inst.i $(PREDIR)/irsfmax.inst.i                      \
	  $(PREDIR)/irsfmin.inst.i $(PREDIR)/pamp.inst.i $(PREDIR)/plot.inst.i    \
	  $(PREDIR)/plotmd.inst.i $(PREDIR)/setcur.inst.i                         \
	  $(PREDIR)/setcur0.inst.i $(PREDIR)/stoplot.inst.i                       \
	  $(PREDIR)/tpamp.inst.i $(PREDIR)/tplot.inst.i $(PREDIR)/xlim.inst.i     \
	  $(PREDIR)/ylim.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/clrcur.inst.i:clrcur.c ../../includes/irs.h ../../includes/cgl.h        \
	  ../../includes/irscur.h
	@rm -f clrcur.i
	$$irs_pre clrcur.c >> clrcur.i
	@mv -f clrcur.i $(PREDIR)/clrcur.inst.i

$(PREDIR)/curbold.inst.i:curbold.c ../../includes/irs.h ../../includes/cgl.h      \
	  ../../includes/irscur.h
	@rm -f curbold.i
	$$irs_pre curbold.c >> curbold.i
	@mv -f curbold.i $(PREDIR)/curbold.inst.i

$(PREDIR)/curbop.inst.i:curbop.c ../../includes/irs.h ../../includes/cgl.h        \
	  ../../includes/irscur.h
	@rm -f curbop.i
	$$irs_pre curbop.c >> curbop.i
	@mv -f curbop.i $(PREDIR)/curbop.inst.i

$(PREDIR)/curgetxy.inst.i:curgetxy.c ../../includes/irs.h ../../includes/cgl.h    \
	  ../../includes/irscur.hh
	@rm -f curgetxy.i
	$$irs_pre curgetxy.c >> curgetxy.i
	@mv -f curgetxy.i $(PREDIR)/curgetxy.inst.i

$(PREDIR)/curgetxy0.inst.i:curgetxy0.c ../../includes/irs.h ../../includes/cgl.h  \
	  ../../includes/irscur.h
	@rm -f curgetxy0.i
	$$irs_pre curgetxy0.c >> curgetxy0.i
	@mv -f curgetxy0.i $(PREDIR)/curgetxy0.inst.i

$(PREDIR)/curlmt.inst.i:curlmt.c ../../includes/irs.h ../../includes/cgl.h        \
	  ../../includes/irscur.h
	@rm -f curlmt.i
	$$irs_pre curlmt.c >> curlmt.i
	@mv -f curlmt.i $(PREDIR)/curlmt.inst.i

$(PREDIR)/curwrtxy.inst.i:curwrtxy.c ../../includes/irs.h ../../includes/cgl.h    \
	  ../../includes/irscur.h
	@rm -f curwrtxy.i
	$$irs_pre curwrtxy.c >> curwrtxy.i
	@mv -f curwrtxy.i $(PREDIR)/curwrtxy.inst.i

$(PREDIR)/curwrtxy0.inst.i:curwrtxy0.c ../../includes/irs.h ../../includes/cgl.h  \
	  ../../includes/irscur.h
	@rm -f curwrtxy0.i
	$$irs_pre curwrtxy0.c >> curwrtxy0.i
	@mv -f curwrtxy0.i $(PREDIR)/curwrtxy0.inst.i

$(PREDIR)/delcur.inst.i:delcur.c ../../includes/irs.h ../../includes/cgl.h        \
	  ../../includes/irscur.h
	@rm -f delcur.i
	$$irs_pre delcur.c >> delcur.i
	@mv -f delcur.i $(PREDIR)/delcur.inst.i

$(PREDIR)/delcur0.inst.i:delcur0.c ../../includes/irs.h ../../includes/cgl.h      \
	  ../../includes/irscur.h
	@rm -f delcur0.i
	$$irs_pre delcur0.c >> delcur0.i
	@mv -f delcur0.i $(PREDIR)/delcur0.inst.i

$(PREDIR)/dobop.inst.i:dobop.c ../../includes/irs.h ../../includes/cgl.h          \
	  ../../includes/irscur.h
	@rm -f dobop.i
	$$irs_pre dobop.c >> dobop.i
	@mv -f dobop.i $(PREDIR)/dobop.inst.i

$(PREDIR)/dorop.inst.i:dorop.c ../../includes/irs.h ../../includes/cgl.h          \
	  ../../includes/irscur.h
	@rm -f dorop.i
	$$irs_pre dorop.c >> dorop.i
	@mv -f dorop.i $(PREDIR)/dorop.inst.i

$(PREDIR)/getcur.inst.i:getcur.c ../../includes/irs.h ../../includes/cgl.h        \
	  ../../includes/irscur.h
	@rm -f getcur.i
	$$irs_pre getcur.c >> getcur.i
	@mv -f getcur.i $(PREDIR)/getcur.inst.i

$(PREDIR)/getcurroot.inst.i:getcurroot.c ../../includes/irs.h                     \
	  ../../includes/cgl.h ../../includes/irscur.h
	@rm -f getcurroot.i
	$$irs_pre getcurroot.c >> getcurroot.i
	@mv -f getcurroot.i $(PREDIR)/getcurroot.inst.i

$(PREDIR)/getnxcn.inst.i:getnxcn.c ../../includes/irs.h ../../includes/cgl.h      \
	  ../../includes/irscur.h
	@rm -f getnxcn.i
	$$irs_pre getnxcn.c >> getnxcn.i
	@mv -f getnxcn.i $(PREDIR)/getnxcn.inst.i

$(PREDIR)/getvec.inst.i:getvec.c ../../includes/irs.h ../../includes/irsrgst.h    \
	  ../../includes/irscur.h ../../includes/cgl.h ../../includes/Hash.h      \
	  ../../includes/ProblemArray.h ../../includes/Rgst.h                     \
	  ../../includes/VectorStruct.h
	@rm -f getvec.i
	$$irs_pre getvec.c >> getvec.i
	@mv -f getvec.i $(PREDIR)/getvec.inst.i

$(PREDIR)/getvec1.inst.i:getvec1.c ../../includes/irs.h ../../includes/irsgen.h   \
	  ../../includes/cgl.h ../../includes/irscur.h ../../includes/NodeList.h  \
	  ../../includes/VectorStruct.h
	@rm -f getvec1.i
	$$irs_pre getvec1.c >> getvec1.i
	@mv -f getvec1.i $(PREDIR)/getvec1.inst.i

$(PREDIR)/getvectp.inst.i:getvectp.c ../../includes/irs.h ../../includes/cgl.h    \
	  ../../includes/irscur.h ../../includes/VectorStruct.h                   \
	  ../../includes/TimePlot.h
	@rm -f getvectp.i
	$$irs_pre getvectp.c >> getvectp.i
	@mv -f getvectp.i $(PREDIR)/getvectp.inst.i

$(PREDIR)/irsfmax.inst.i:irsfmax.c ../../includes/irs.h ../../includes/cgl.h      \
	  ../../includes/irscur.h
	@rm -f irsfmax.i
	$$irs_pre irsfmax.c >> irsfmax.i
	@mv -f irsfmax.i $(PREDIR)/irsfmax.inst.i

$(PREDIR)/irsfmin.inst.i:irsfmin.c ../../includes/irs.h ../../includes/cgl.h      \
	  ../../includes/irscur.h
	@rm -f irsfmin.i
	$$irs_pre irsfmin.c >> irsfmin.i
	@mv -f irsfmin.i $(PREDIR)/irsfmin.inst.i

$(PREDIR)/pamp.inst.i:pamp.c ../../includes/irs.h ../../includes/cgl.h            \
	  ../../includes/irscur.h
	@rm -f pamp.i
	$$irs_pre pamp.c >> pamp.i
	@mv -f pamp.i $(PREDIR)/pamp.inst.i

$(PREDIR)/plot.inst.i:plot.c ../../includes/irs.h ../../includes/cgl.h            \
	  ../../includes/irscur.h
	@rm -f plot.i
	$$irs_pre plot.c >> plot.i
	@mv -f plot.i $(PREDIR)/plot.inst.i

$(PREDIR)/plotmd.inst.i:plotmd.c ../../includes/irs.h ../../includes/cgl.h        \
	  ../../includes/irscur.h
	@rm -f plotmd.i
	$$irs_pre plotmd.c >> plotmd.i
	@mv -f plotmd.i $(PREDIR)/plotmd.inst.i

$(PREDIR)/setcur.inst.i:setcur.c ../../includes/irs.h ../../includes/cgl.h        \
	  ../../includes/irscur.h
	@rm -f setcur.i
	$$irs_pre setcur.c >> setcur.i
	@mv -f setcur.i $(PREDIR)/setcur.inst.i

$(PREDIR)/setcur0.inst.i:setcur0.c ../../includes/irs.h ../../includes/cgl.h      \
	  ../../includes/irscur.h
	@rm -f setcur0.i
	$$irs_pre setcur0.c >> setcur0.i
	@mv -f setcur0.i $(PREDIR)/setcur0.inst.i

$(PREDIR)/stoplot.inst.i:stoplot.c ../../includes/irs.h ../../includes/irscur.h   \
	  ../../includes/irsctl.h ../../includes/irsgenrd.h                       \
	  ../../includes/irsrgst.h ../../includes/cgl.h                           \
	  ../../includes/AEStackElm.h ../../includes/Hash.h                       \
	  ../../includes/FunctionTimer.h ../../includes/TimePlot.h
	@rm -f stoplot.i
	$$irs_pre stoplot.c >> stoplot.i
	@mv -f stoplot.i $(PREDIR)/stoplot.inst.i

$(PREDIR)/tpamp.inst.i:tpamp.c ../../includes/irs.h ../../includes/irscom.h       \
	  ../../includes/irscur.h ../../includes/cgl.h                            \
	  ../../includes/FunctionTimer.h ../../includes/TimePlot.h
	@rm -f tpamp.i
	$$irs_pre tpamp.c >> tpamp.i
	@mv -f tpamp.i $(PREDIR)/tpamp.inst.i

$(PREDIR)/tplot.inst.i:tplot.c ../../includes/irs.h ../../includes/cgl.h          \
	  ../../includes/irscur.h
	@rm -f tplot.i
	$$irs_pre tplot.c >> tplot.i
	@mv -f tplot.i $(PREDIR)/tplot.inst.i

$(PREDIR)/xlim.inst.i:xlim.c ../../includes/irs.h ../../includes/cgl.h            \
	  ../../includes/irscur.h
	@rm -f xlim.i
	$$irs_pre xlim.c >> xlim.i
	@mv -f xlim.i $(PREDIR)/xlim.inst.i

$(PREDIR)/ylim.inst.i:ylim.c ../../includes/irs.h ../../includes/cgl.h            \
	  ../../includes/irscur.h
	@rm -f ylim.i
	$$irs_pre ylim.c >> ylim.i
	@mv -f ylim.i $(PREDIR)/ylim.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libcur_inst

libcur_inst:$(BI)(clrcur.inst.o) $(BI)(curbold.inst.o) $(BI)(curbop.inst.o)       \
	  $(BI)(curgetxy.inst.o) $(BI)(curgetxy0.inst.o) $(BI)(curlmt.inst.o)     \
	  $(BI)(curwrtxy.inst.o) $(BI)(curwrtxy0.inst.o) $(BI)(delcur.inst.o)     \
	  $(BI)(delcur0.inst.o) $(BI)(dobop.inst.o) $(BI)(dorop.inst.o)           \
	  $(BI)(getcur.inst.o) $(BI)(getcurroot.inst.o) $(BI)(getnxcn.inst.o)     \
	  $(BI)(getvec.inst.o) $(BI)(getvec1.inst.o) $(BI)(getvectp.inst.o)       \
	  $(BI)(irsfmax.inst.o) $(BI)(irsfmin.inst.o) $(BI)(pamp.inst.o)          \
	  $(BI)(plot.inst.o) $(BI)(plotmd.inst.o) $(BI)(setcur.inst.o)            \
	  $(BI)(setcur0.inst.o) $(BI)(stoplot.inst.o) $(BI)(tpamp.inst.o)         \
	  $(BI)(tplot.inst.o) $(BI)(xlim.inst.o) $(BI)(ylim.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libcur_inst.a $(B); \
		ln -sf libcur_inst.a $(B)); \
	  fi
	  @echo 'libcur_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(clrcur.inst.o):$(INSTDIR)/clrcur.inst.i
	$$irs_post $(INSTDIR)/clrcur.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/clrcur.inst.i $(DB)/clrcur.c 

$(BI)(curbold.inst.o):$(INSTDIR)/curbold.inst.i
	$$irs_post $(INSTDIR)/curbold.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/curbold.inst.i $(DB)/curbold.c 

$(BI)(curbop.inst.o):$(INSTDIR)/curbop.inst.i
	$$irs_post $(INSTDIR)/curbop.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/curbop.inst.i $(DB)/curbop.c 

$(BI)(curgetxy.inst.o):$(INSTDIR)/curgetxy.inst.i
	$$irs_post $(INSTDIR)/curgetxy.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/curgetxy.inst.i $(DB)/curgetxy.c 

$(BI)(curgetxy0.inst.o):$(INSTDIR)/curgetxy0.inst.i
	$$irs_post $(INSTDIR)/curgetxy0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/curgetxy0.inst.i $(DB)/curgetxy0.c 

$(BI)(curlmt.inst.o):$(INSTDIR)/curlmt.inst.i
	$$irs_post $(INSTDIR)/curlmt.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/curlmt.inst.i $(DB)/curlmt.c 

$(BI)(curwrtxy.inst.o):$(INSTDIR)/curwrtxy.inst.i
	$$irs_post $(INSTDIR)/curwrtxy.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/curwrtxy.inst.i $(DB)/curwrtxy.c 

$(BI)(curwrtxy0.inst.o):$(INSTDIR)/curwrtxy0.inst.i
	$$irs_post $(INSTDIR)/curwrtxy0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/curwrtxy0.inst.i $(DB)/curwrtxy0.c 

$(BI)(delcur.inst.o):$(INSTDIR)/delcur.inst.i
	$$irs_post $(INSTDIR)/delcur.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/delcur.inst.i $(DB)/delcur.c 

$(BI)(delcur0.inst.o):$(INSTDIR)/delcur0.inst.i
	$$irs_post $(INSTDIR)/delcur0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/delcur0.inst.i $(DB)/delcur0.c 

$(BI)(dobop.inst.o):$(INSTDIR)/dobop.inst.i
	$$irs_post $(INSTDIR)/dobop.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/dobop.inst.i $(DB)/dobop.c 

$(BI)(dorop.inst.o):$(INSTDIR)/dorop.inst.i
	$$irs_post $(INSTDIR)/dorop.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/dorop.inst.i $(DB)/dorop.c 

$(BI)(getcur.inst.o):$(INSTDIR)/getcur.inst.i
	$$irs_post $(INSTDIR)/getcur.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getcur.inst.i $(DB)/getcur.c 

$(BI)(getcurroot.inst.o):$(INSTDIR)/getcurroot.inst.i
	$$irs_post $(INSTDIR)/getcurroot.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getcurroot.inst.i $(DB)/getcurroot.c 

$(BI)(getnxcn.inst.o):$(INSTDIR)/getnxcn.inst.i
	$$irs_post $(INSTDIR)/getnxcn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getnxcn.inst.i $(DB)/getnxcn.c 

$(BI)(getvec.inst.o):$(INSTDIR)/getvec.inst.i
	$$irs_post $(INSTDIR)/getvec.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getvec.inst.i $(DB)/getvec.c 

$(BI)(getvec1.inst.o):$(INSTDIR)/getvec1.inst.i
	$$irs_post $(INSTDIR)/getvec1.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getvec1.inst.i $(DB)/getvec1.c 

$(BI)(getvectp.inst.o):$(INSTDIR)/getvectp.inst.i
	$$irs_post $(INSTDIR)/getvectp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getvectp.inst.i $(DB)/getvectp.c 

$(BI)(irsfmax.inst.o):$(INSTDIR)/irsfmax.inst.i
	$$irs_post $(INSTDIR)/irsfmax.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/irsfmax.inst.i $(DB)/irsfmax.c 

$(BI)(irsfmin.inst.o):$(INSTDIR)/irsfmin.inst.i
	$$irs_post $(INSTDIR)/irsfmin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/irsfmin.inst.i $(DB)/irsfmin.c 

$(BI)(pamp.inst.o):$(INSTDIR)/pamp.inst.i
	$$irs_post $(INSTDIR)/pamp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/pamp.inst.i $(DB)/pamp.c 

$(BI)(plot.inst.o):$(INSTDIR)/plot.inst.i
	$$irs_post $(INSTDIR)/plot.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/plot.inst.i $(DB)/plot.c 

$(BI)(plotmd.inst.o):$(INSTDIR)/plotmd.inst.i
	$$irs_post $(INSTDIR)/plotmd.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/plotmd.inst.i $(DB)/plotmd.c 

$(BI)(setcur.inst.o):$(INSTDIR)/setcur.inst.i
	$$irs_post $(INSTDIR)/setcur.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setcur.inst.i $(DB)/setcur.c 

$(BI)(setcur0.inst.o):$(INSTDIR)/setcur0.inst.i
	$$irs_post $(INSTDIR)/setcur0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setcur0.inst.i $(DB)/setcur0.c 

$(BI)(stoplot.inst.o):$(INSTDIR)/stoplot.inst.i
	$$irs_post $(INSTDIR)/stoplot.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/stoplot.inst.i $(DB)/stoplot.c 

$(BI)(tpamp.inst.o):$(INSTDIR)/tpamp.inst.i
	$$irs_post $(INSTDIR)/tpamp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tpamp.inst.i $(DB)/tpamp.c 

$(BI)(tplot.inst.o):$(INSTDIR)/tplot.inst.i
	$$irs_post $(INSTDIR)/tplot.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tplot.inst.i $(DB)/tplot.c 

$(BI)(xlim.inst.o):$(INSTDIR)/xlim.inst.i
	$$irs_post $(INSTDIR)/xlim.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/xlim.inst.i $(DB)/xlim.c 

$(BI)(ylim.inst.o):$(INSTDIR)/ylim.inst.i
	$$irs_post $(INSTDIR)/ylim.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ylim.inst.i $(DB)/ylim.c 

DEP_SRCS = \
	clrcur.c curbold.c curbop.c curgetxy.c curgetxy0.c curlmt.c curwrtxy.c  \
	curwrtxy0.c delcur.c delcur0.c dobop.c dorop.c getcur.c getcurroot.c getnxcn.c  \
	getvec.c getvec1.c getvectp.c irsfmax.c irsfmin.c pamp.c plot.c plotmd.c  \
	setcur.c setcur0.c stoplot.c tpamp.c tplot.c xlim.c ylim.c  

depend:
	@cp -f Makefile.cur Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

