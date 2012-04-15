
################################################################################
#
# Makefile for irs library ctl
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
B = ../$(LIB_DIR)/libctl.a
BI = ../$(LIB_DIR)/libctl_inst.a

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
SRCDIR = ../sources/ctl

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libctl:$(B)(SystemWrapper.o) $(B)(conditionals.o) $(B)(ctlecho.o)                 \
	  $(B)(ctlerror.o) $(B)(ctlmsg.o) $(B)(ctlmsg1.o) $(B)(ctlnotice.o)       \
	  $(B)(ctloutput.o) $(B)(ctlwarning.o) $(B)(delfq.o) $(B)(domsg.o)        \
	  $(B)(endfile.o) $(B)(endout.o) $(B)(eval.o) $(B)(exit_cleanup.o)        \
	  $(B)(expressions.o) $(B)(fqcyc.o) $(B)(geta.o) $(B)(geta_discard.o)     \
	  $(B)(geta_leftparen.o) $(B)(geta_rightparen.o) $(B)(getf.o)             \
	  $(B)(getflst.o) $(B)(getfq.o) $(B)(geti.o) $(B)(getnxcy.o)              \
	  $(B)(getnxtm.o) $(B)(getsym.o) $(B)(getversion.o) $(B)(gpdef.o)         \
	  $(B)(gpdef0.o) $(B)(ifnotin.o) $(B)(initget.o) $(B)(irspcs.o)           \
	  $(B)(lfchk.o) $(B)(lineop.o) $(B)(lnadv.o) $(B)(main.o) $(B)(newfile.o) \
	  $(B)(newline.o) $(B)(noop.o) $(B)(nxtsym.o) $(B)(outfile.o)             \
	  $(B)(parmsym.o) $(B)(peekc.o) $(B)(peekc2.o) $(B)(printdate.o)          \
	  $(B)(printhelp.o) $(B)(printmap.o) $(B)(printmsg.o) $(B)(printrc.o)     \
	  $(B)(printtc.o) $(B)(prirup.o) $(B)(pversion.o) $(B)(redofq.o)          \
	  $(B)(resetio.o) $(B)(resetmsg.o) $(B)(run.o) $(B)(setiomrk.o)           \
	  $(B)(setirup.o) $(B)(setup_attrs.o) $(B)(showfq.o) $(B)(step.o)         \
	  $(B)(terry_trace.o) \
	  $(B)(unsetio.o) $(B)(userexitfn.o) $(B)(walltime.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'ctl library current'

# creation deps
#---------------
$(B)(SystemWrapper.o):SystemWrapper.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/SystemWrapper.c $(DB)/SystemWrapper.c 

$(B)(conditionals.o):conditionals.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/conditionals.c $(DB)/conditionals.c 

$(B)(ctlecho.o):ctlecho.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ctlecho.c $(DB)/ctlecho.c 

$(B)(ctlerror.o):ctlerror.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ctlerror.c $(DB)/ctlerror.c 

$(B)(ctlmsg.o):ctlmsg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ctlmsg.c $(DB)/ctlmsg.c 

$(B)(ctlmsg1.o):ctlmsg1.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ctlmsg1.c $(DB)/ctlmsg1.c 

$(B)(ctlnotice.o):ctlnotice.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ctlnotice.c $(DB)/ctlnotice.c 

$(B)(ctloutput.o):ctloutput.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ctloutput.c $(DB)/ctloutput.c 

$(B)(ctlwarning.o):ctlwarning.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ctlwarning.c $(DB)/ctlwarning.c 

$(B)(delfq.o):delfq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/delfq.c $(DB)/delfq.c 

$(B)(domsg.o):domsg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/domsg.c $(DB)/domsg.c 

$(B)(endfile.o):endfile.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/endfile.c $(DB)/endfile.c 

$(B)(endout.o):endout.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/endout.c $(DB)/endout.c 

$(B)(eval.o):eval.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/eval.c $(DB)/eval.c 

$(B)(exit_cleanup.o):exit_cleanup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/exit_cleanup.c $(DB)/exit_cleanup.c 

$(B)(expressions.o):expressions.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/expressions.c $(DB)/expressions.c 

../../includes/CycleMesg.hh:../../includes/CycleMesg.h
	cp ../../includes/CycleMesg.h ../../includes/CycleMesg.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/CycleMesg.hh
	irs_hhinit ../../includes/CycleMesg.hh

$(B)(fqcyc.o):../../includes/CycleMesg.hh

../../includes/FreqMesg.hh:../../includes/FreqMesg.h
	cp ../../includes/FreqMesg.h ../../includes/FreqMesg.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/FreqMesg.hh
	irs_hhinit ../../includes/FreqMesg.hh

$(B)(fqcyc.o):../../includes/FreqMesg.hh

../../includes/TimePlot.hh:../../includes/TimePlot.h
	cp ../../includes/TimePlot.h ../../includes/TimePlot.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/TimePlot.hh
	irs_hhinit ../../includes/TimePlot.hh

$(B)(fqcyc.o):../../includes/TimePlot.hh

$(B)(fqcyc.o):fqcyc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/fqcyc.c $(DB)/fqcyc.c 

$(B)(geta.o):geta.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geta.c $(DB)/geta.c 

$(B)(geta_discard.o):geta_discard.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geta_discard.c $(DB)/geta_discard.c 

$(B)(geta_leftparen.o):geta_leftparen.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geta_leftparen.c $(DB)/geta_leftparen.c 

$(B)(geta_rightparen.o):geta_rightparen.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geta_rightparen.c $(DB)/geta_rightparen.c 

$(B)(getf.o):getf.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getf.c $(DB)/getf.c 

$(B)(getflst.o):getflst.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getflst.c $(DB)/getflst.c 

$(B)(getfq.o):getfq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getfq.c $(DB)/getfq.c 

$(B)(geti.o):geti.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geti.c $(DB)/geti.c 

$(B)(getnxcy.o):getnxcy.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getnxcy.c $(DB)/getnxcy.c 

$(B)(getnxtm.o):getnxtm.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getnxtm.c $(DB)/getnxtm.c 

$(B)(getsym.o):getsym.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getsym.c $(DB)/getsym.c 

../../includes/VersionData.hh:../../includes/VersionData.h
	cp ../../includes/VersionData.h ../../includes/VersionData.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/VersionData.hh
	irs_hhinit ../../includes/VersionData.hh

$(B)(getversion.o):../../includes/VersionData.hh

$(B)(getversion.o):getversion.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getversion.c $(DB)/getversion.c 

$(B)(gpdef.o):gpdef.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/gpdef.c $(DB)/gpdef.c 

$(B)(gpdef0.o):gpdef0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/gpdef0.c $(DB)/gpdef0.c 

$(B)(ifnotin.o):ifnotin.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ifnotin.c $(DB)/ifnotin.c 

$(B)(initget.o):initget.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/initget.c $(DB)/initget.c 

$(B)(irspcs.o):irspcs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/irspcs.c $(DB)/irspcs.c 

$(B)(lfchk.o):lfchk.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/lfchk.c $(DB)/lfchk.c 

$(B)(lineop.o):lineop.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/lineop.c $(DB)/lineop.c 

$(B)(terry_trace.o):terry_trace.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/terry_trace.c $(DB)/terry_trace.c 

$(B)(lnadv.o):lnadv.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/lnadv.c $(DB)/lnadv.c 

../../includes/irsctl.hh:../../includes/irsctl.h
	cp ../../includes/irsctl.h ../../includes/irsctl.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/irsctl.hh
	irs_hhinit ../../includes/irsctl.hh

$(B)(main.o):../../includes/irsctl.hh

../../includes/Gparm.hh:../../includes/Gparm.h
	cp ../../includes/Gparm.h ../../includes/Gparm.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/Gparm.hh
	irs_hhinit ../../includes/Gparm.hh

$(B)(main.o):../../includes/Gparm.hh

$(B)(main.o):main.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/main.c $(DB)/main.c 

$(B)(newfile.o):newfile.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/newfile.c $(DB)/newfile.c 

$(B)(newline.o):newline.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/newline.c $(DB)/newline.c 

$(B)(noop.o):noop.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/noop.c $(DB)/noop.c 

$(B)(nxtsym.o):nxtsym.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/nxtsym.c $(DB)/nxtsym.c 

$(B)(outfile.o):outfile.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/outfile.c $(DB)/outfile.c 

$(B)(parmsym.o):parmsym.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/parmsym.c $(DB)/parmsym.c 

$(B)(peekc.o):peekc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/peekc.c $(DB)/peekc.c 

$(B)(peekc2.o):peekc2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/peekc2.c $(DB)/peekc2.c 

$(B)(printdate.o):printdate.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printdate.c $(DB)/printdate.c 

$(B)(printhelp.o):printhelp.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printhelp.c $(DB)/printhelp.c 

$(B)(printmap.o):printmap.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printmap.c $(DB)/printmap.c 

$(B)(printmsg.o):printmsg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printmsg.c $(DB)/printmsg.c 

$(B)(printrc.o):printrc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printrc.c $(DB)/printrc.c 

$(B)(printtc.o):printtc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/printtc.c $(DB)/printtc.c 

$(B)(prirup.o):prirup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/prirup.c $(DB)/prirup.c 

$(B)(pversion.o):pversion.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/pversion.c $(DB)/pversion.c 

$(B)(redofq.o):redofq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/redofq.c $(DB)/redofq.c 

$(B)(resetio.o):resetio.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/resetio.c $(DB)/resetio.c 

$(B)(resetmsg.o):resetmsg.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/resetmsg.c $(DB)/resetmsg.c 

$(B)(run.o):run.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/run.c $(DB)/run.c 

$(B)(setiomrk.o):setiomrk.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setiomrk.c $(DB)/setiomrk.c 

$(B)(setirup.o):setirup.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setirup.c $(DB)/setirup.c 

$(B)(setup_attrs.o):setup_attrs.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setup_attrs.c $(DB)/setup_attrs.c 

$(B)(showfq.o):showfq.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/showfq.c $(DB)/showfq.c 

$(B)(step.o):step.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/step.c $(DB)/step.c 

$(B)(unsetio.o):unsetio.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/unsetio.c $(DB)/unsetio.c 

$(B)(userexitfn.o):userexitfn.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/userexitfn.c $(DB)/userexitfn.c 

$(B)(walltime.o):walltime.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/walltime.c $(DB)/walltime.c 

#---------------------
# lint pass one target 
#---------------------
lint:SystemWrapper.ln conditionals.ln ctlecho.ln ctlerror.ln ctlmsg.ln ctlmsg1.ln \
	  ctlnotice.ln ctloutput.ln ctlwarning.ln delfq.ln domsg.ln endfile.ln    \
	  endout.ln eval.ln exit_cleanup.ln expressions.ln fqcyc.ln geta.ln       \
	  geta_discard.ln geta_leftparen.ln geta_rightparen.ln getf.ln getflst.ln \
	  getfq.ln geti.ln getnxcy.ln getnxtm.ln getsym.ln getversion.ln gpdef.ln \
	  gpdef0.ln ifnotin.ln initget.ln irspcs.ln lfchk.ln lineop.ln lnadv.ln   \
	  main.ln newfile.ln newline.ln noop.ln nxtsym.ln outfile.ln parmsym.ln   \
	  peekc.ln peekc2.ln printdate.ln printhelp.ln printmap.ln printmsg.ln    \
	  printrc.ln printtc.ln prirup.ln pversion.ln redofq.ln resetio.ln        \
	  resetmsg.ln run.ln setiomrk.ln setirup.ln setup_attrs.ln showfq.ln      \
	  step.ln unsetio.ln userexitfn.ln walltime.ln terry_trace.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
SystemWrapper.ln:SystemWrapper.c ../../includes/irs.h                             \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h                  \
	  ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON SystemWrapper.c ***' >> $(LO)
	$$irs_lint SystemWrapper.c 2>&1 | tee -a $(LO)

conditionals.ln:conditionals.c ../../includes/irs.h ../../includes/irsrgst.h      \
	  ../../includes/irsctl.h ../../includes/irsgenrd.h ../../includes/Hash.h \
	  ../../includes/Conditional.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON conditionals.c ***' >> $(LO)
	$$irs_lint conditionals.c 2>&1 | tee -a $(LO)

ctlecho.ln:ctlecho.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ctlecho.c ***' >> $(LO)
	$$irs_lint ctlecho.c 2>&1 | tee -a $(LO)

ctlerror.ln:ctlerror.c ../../includes/irs.h ../../includes/irsctl.h               \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ctlerror.c ***' >> $(LO)
	$$irs_lint ctlerror.c 2>&1 | tee -a $(LO)

ctlmsg.ln:ctlmsg.c ../../includes/irs.h ../../includes/irsctl.h                   \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ctlmsg.c ***' >> $(LO)
	$$irs_lint ctlmsg.c 2>&1 | tee -a $(LO)

ctlmsg1.ln:ctlmsg1.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ctlmsg1.c ***' >> $(LO)
	$$irs_lint ctlmsg1.c 2>&1 | tee -a $(LO)

ctlnotice.ln:ctlnotice.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ctlnotice.c ***' >> $(LO)
	$$irs_lint ctlnotice.c 2>&1 | tee -a $(LO)

ctloutput.ln:ctloutput.c ../../includes/irs.h ../../includes/irsctl.h             \
	  ../../includes/AEStackElm.h ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ctloutput.c ***' >> $(LO)
	$$irs_lint ctloutput.c 2>&1 | tee -a $(LO)

ctlwarning.ln:ctlwarning.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ctlwarning.c ***' >> $(LO)
	$$irs_lint ctlwarning.c 2>&1 | tee -a $(LO)

delfq.ln:delfq.c ../../includes/irs.h ../../includes/irsrgst.h                    \
	  ../../includes/irsctl.h ../../includes/Conditional.h                    \
	  ../../includes/CycleMesg.h ../../includes/Hash.h                        \
	  ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON delfq.c ***' >> $(LO)
	$$irs_lint delfq.c 2>&1 | tee -a $(LO)

domsg.ln:domsg.c ../../includes/irs.h ../../includes/irsctl.h                     \
	  ../../includes/irscur.h ../../includes/irsgenrd.h                       \
	  ../../includes/CycleMesg.h ../../includes/Conditional.h                 \
	  ../../includes/FreqMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON domsg.c ***' >> $(LO)
	$$irs_lint domsg.c 2>&1 | tee -a $(LO)

endfile.ln:endfile.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON endfile.c ***' >> $(LO)
	$$irs_lint endfile.c 2>&1 | tee -a $(LO)

endout.ln:endout.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON endout.c ***' >> $(LO)
	$$irs_lint endout.c 2>&1 | tee -a $(LO)

eval.ln:eval.c ../../includes/irs.h ../../includes/irsctl.h                       \
	  ../../includes/AEStackElm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON eval.c ***' >> $(LO)
	$$irs_lint eval.c 2>&1 | tee -a $(LO)

exit_cleanup.ln:exit_cleanup.c ../../includes/irs.h                               \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON exit_cleanup.c ***' >> $(LO)
	$$irs_lint exit_cleanup.c 2>&1 | tee -a $(LO)

expressions.ln:expressions.c ../../includes/irs.h ../../includes/irsgen.h         \
	  ../../includes/irsctl.h ../../includes/irsrgst.h                        \
	  ../../includes/AEStackElm.h ../../includes/Command.h                    \
	  ../../includes/Rgst.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON expressions.c ***' >> $(LO)
	$$irs_lint expressions.c 2>&1 | tee -a $(LO)

fqcyc.ln:fqcyc.c ../../includes/irs.h ../../includes/irsctl.h                     \
	  ../../includes/irsrgst.h ../../includes/CycleMesg.hh                    \
	  ../../includes/FreqMesg.hh ../../includes/TimePlot.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON fqcyc.c ***' >> $(LO)
	$$irs_lint fqcyc.c 2>&1 | tee -a $(LO)

geta.ln:geta.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geta.c ***' >> $(LO)
	$$irs_lint geta.c 2>&1 | tee -a $(LO)

geta_discard.ln:geta_discard.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geta_discard.c ***' >> $(LO)
	$$irs_lint geta_discard.c 2>&1 | tee -a $(LO)

geta_leftparen.ln:geta_leftparen.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geta_leftparen.c ***' >> $(LO)
	$$irs_lint geta_leftparen.c 2>&1 | tee -a $(LO)

geta_rightparen.ln:geta_rightparen.c ../../includes/irs.h                         \
	  ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geta_rightparen.c ***' >> $(LO)
	$$irs_lint geta_rightparen.c 2>&1 | tee -a $(LO)

getf.ln:getf.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getf.c ***' >> $(LO)
	$$irs_lint getf.c 2>&1 | tee -a $(LO)

getflst.ln:getflst.c ../../includes/irs.h ../../includes/Spline.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getflst.c ***' >> $(LO)
	$$irs_lint getflst.c 2>&1 | tee -a $(LO)

getfq.ln:getfq.c ../../includes/irs.h ../../includes/irsctl.h                     \
	  ../../includes/CycleMesg.h ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getfq.c ***' >> $(LO)
	$$irs_lint getfq.c 2>&1 | tee -a $(LO)

geti.ln:geti.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geti.c ***' >> $(LO)
	$$irs_lint geti.c 2>&1 | tee -a $(LO)

getnxcy.ln:getnxcy.c ../../includes/irs.h ../../includes/irsctl.h                 \
	  ../../includes/Conditional.h ../../includes/CycleMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getnxcy.c ***' >> $(LO)
	$$irs_lint getnxcy.c 2>&1 | tee -a $(LO)

getnxtm.ln:getnxtm.c ../../includes/irs.h ../../includes/irsctl.h                 \
	  ../../includes/FreqMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getnxtm.c ***' >> $(LO)
	$$irs_lint getnxtm.c 2>&1 | tee -a $(LO)

getsym.ln:getsym.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getsym.c ***' >> $(LO)
	$$irs_lint getsym.c 2>&1 | tee -a $(LO)

getversion.ln:getversion.c ../../includes/irsversion.h ../../includes/irs.h       \
	  ../../includes/irsdmp.h ../../includes/VersionData.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getversion.c ***' >> $(LO)
	$$irs_lint getversion.c 2>&1 | tee -a $(LO)

gpdef.ln:gpdef.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON gpdef.c ***' >> $(LO)
	$$irs_lint gpdef.c 2>&1 | tee -a $(LO)

gpdef0.ln:gpdef0.c ../../includes/irs.h ../../includes/irsctl.h                   \
	  ../../includes/Gparm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON gpdef0.c ***' >> $(LO)
	$$irs_lint gpdef0.c 2>&1 | tee -a $(LO)

ifnotin.ln:ifnotin.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ifnotin.c ***' >> $(LO)
	$$irs_lint ifnotin.c 2>&1 | tee -a $(LO)

initget.ln:initget.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON initget.c ***' >> $(LO)
	$$irs_lint initget.c 2>&1 | tee -a $(LO)

irspcs.ln:irspcs.c ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON irspcs.c ***' >> $(LO)
	$$irs_lint irspcs.c 2>&1 | tee -a $(LO)

lfchk.ln:lfchk.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON lfchk.c ***' >> $(LO)
	$$irs_lint lfchk.c 2>&1 | tee -a $(LO)

lineop.ln:lineop.c ../../includes/irs.h ../../includes/irsrgst.h                  \
	  ../../includes/irsctl.h ../../includes/FunctionTimer.h                  \
	  ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON lineop.c ***' >> $(LO)
	$$irs_lint lineop.c 2>&1 | tee -a $(LO)

lnadv.ln:lnadv.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON lnadv.c ***' >> $(LO)
	$$irs_lint lnadv.c 2>&1 | tee -a $(LO)

main.ln:main.c ../../includes/irs.h ../../includes/irscom.h                       \
	  ../../includes/irsdmp.h ../../includes/irsedits.h                       \
	  ../../includes/irseos.h ../../includes/irsgen.h                         \
	  ../../includes/irsgenrd.h ../../includes/irsparm.h                      \
	  ../../includes/irsrgst.h ../../includes/irssys.h                        \
	  ../../includes/irsctl.hh ../../includes/Conditional.h                   \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h                    \
	  ../../includes/ProblemArray.h ../../includes/VersionData.h              \
	  ../../includes/Gparm.hh
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON main.c ***' >> $(LO)
	$$irs_lint main.c 2>&1 | tee -a $(LO)

newfile.ln:newfile.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON newfile.c ***' >> $(LO)
	$$irs_lint newfile.c 2>&1 | tee -a $(LO)

newline.ln:newline.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON newline.c ***' >> $(LO)
	$$irs_lint newline.c 2>&1 | tee -a $(LO)

noop.ln:noop.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON noop.c ***' >> $(LO)
	$$irs_lint noop.c 2>&1 | tee -a $(LO)

nxtsym.ln:nxtsym.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON nxtsym.c ***' >> $(LO)
	$$irs_lint nxtsym.c 2>&1 | tee -a $(LO)

outfile.ln:outfile.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON outfile.c ***' >> $(LO)
	$$irs_lint outfile.c 2>&1 | tee -a $(LO)

parmsym.ln:parmsym.c ../../includes/irs.h ../../includes/irsctl.h                 \
	  ../../includes/Gparm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON parmsym.c ***' >> $(LO)
	$$irs_lint parmsym.c 2>&1 | tee -a $(LO)

peekc.ln:peekc.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON peekc.c ***' >> $(LO)
	$$irs_lint peekc.c 2>&1 | tee -a $(LO)

peekc2.ln:peekc2.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON peekc2.c ***' >> $(LO)
	$$irs_lint peekc2.c 2>&1 | tee -a $(LO)

printdate.ln:printdate.c ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printdate.c ***' >> $(LO)
	$$irs_lint printdate.c 2>&1 | tee -a $(LO)

printhelp.ln:printhelp.c ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printhelp.c ***' >> $(LO)
	$$irs_lint printhelp.c 2>&1 | tee -a $(LO)

printmap.ln:printmap.c ../../includes/irs.h ../../includes/irsctl.h               \
	  ../../includes/irscom.h ../../includes/irsdmp.h                         \
	  ../../includes/BlockMapping.h ../../includes/Hash.h                     \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printmap.c ***' >> $(LO)
	$$irs_lint printmap.c 2>&1 | tee -a $(LO)

printmsg.ln:printmsg.c ../../includes/irs.h ../../includes/irsctl.h               \
	  ../../includes/Conditional.h ../../includes/CycleMesg.h                 \
	  ../../includes/FreqMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printmsg.c ***' >> $(LO)
	$$irs_lint printmsg.c 2>&1 | tee -a $(LO)

printrc.ln:printrc.c ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printrc.c ***' >> $(LO)
	$$irs_lint printrc.c 2>&1 | tee -a $(LO)

printtc.ln:printtc.c ../../includes/irs.h ../../includes/irslag.h                 \
	  ../../includes/irsctl.h ../../includes/TimeStepControl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON printtc.c ***' >> $(LO)
	$$irs_lint printtc.c 2>&1 | tee -a $(LO)

prirup.ln:prirup.c ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON prirup.c ***' >> $(LO)
	$$irs_lint prirup.c 2>&1 | tee -a $(LO)

pversion.ln:pversion.c ../../includes/irs.h ../../includes/VersionData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON pversion.c ***' >> $(LO)
	$$irs_lint pversion.c 2>&1 | tee -a $(LO)

redofq.ln:redofq.c ../../includes/irs.h ../../includes/irsrgst.h                  \
	  ../../includes/irsctl.h ../../includes/Conditional.h                    \
	  ../../includes/CycleMesg.h ../../includes/Hash.h                        \
	  ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON redofq.c ***' >> $(LO)
	$$irs_lint redofq.c 2>&1 | tee -a $(LO)

resetio.ln:resetio.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON resetio.c ***' >> $(LO)
	$$irs_lint resetio.c 2>&1 | tee -a $(LO)

resetmsg.ln:resetmsg.c ../../includes/irs.h ../../includes/irsctl.h               \
	  ../../includes/CycleMesg.h ../../includes/FreqMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON resetmsg.c ***' >> $(LO)
	$$irs_lint resetmsg.c 2>&1 | tee -a $(LO)

run.ln:run.c ../../includes/irs.h ../../includes/irslag.h                         \
	  ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON run.c ***' >> $(LO)
	$$irs_lint run.c 2>&1 | tee -a $(LO)

setiomrk.ln:setiomrk.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setiomrk.c ***' >> $(LO)
	$$irs_lint setiomrk.c 2>&1 | tee -a $(LO)

setirup.ln:setirup.c ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setirup.c ***' >> $(LO)
	$$irs_lint setirup.c 2>&1 | tee -a $(LO)

setup_attrs.ln:setup_attrs.c ../../includes/irs.h ../../includes/irsrgst.h        \
	  ../../includes/Conditional.h ../../includes/FunctionTimer.h             \
	  ../../includes/FreqMesg.h ../../includes/Gparm.h                        \
	  ../../includes/Region.h ../../includes/Source.h ../../includes/Spline.h \
	  ../../includes/Transform.h ../../includes/TimePlot.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setup_attrs.c ***' >> $(LO)
	$$irs_lint setup_attrs.c 2>&1 | tee -a $(LO)

showfq.ln:showfq.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON showfq.c ***' >> $(LO)
	$$irs_lint showfq.c 2>&1 | tee -a $(LO)

step.ln:step.c ../../includes/irs.h ../../includes/irslag.h                       \
	  ../../includes/CycleMesg.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON step.c ***' >> $(LO)
	$$irs_lint step.c 2>&1 | tee -a $(LO)

unsetio.ln:unsetio.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON unsetio.c ***' >> $(LO)
	$$irs_lint unsetio.c 2>&1 | tee -a $(LO)

userexitfn.ln:userexitfn.c ../../includes/irs.h ../../includes/irsctl.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON userexitfn.c ***' >> $(LO)
	$$irs_lint userexitfn.c 2>&1 | tee -a $(LO)

walltime.ln:walltime.c ../../includes/irs.h ../../includes/irscom.h               \
	  ../../includes/irsctl.h ../../includes/irssys.h                         \
	  ../../includes/FunctionTimer.h ../../includes/AEStackElm.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON walltime.c ***' >> $(LO)
	$$irs_lint walltime.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/SystemWrapper.inst.i $(PREDIR)/conditionals.inst.i           \
	  $(PREDIR)/ctlecho.inst.i $(PREDIR)/ctlerror.inst.i                      \
	  $(PREDIR)/ctlmsg.inst.i $(PREDIR)/ctlmsg1.inst.i                        \
	  $(PREDIR)/ctlnotice.inst.i $(PREDIR)/ctloutput.inst.i                   \
	  $(PREDIR)/ctlwarning.inst.i $(PREDIR)/delfq.inst.i                      \
	  $(PREDIR)/domsg.inst.i $(PREDIR)/endfile.inst.i $(PREDIR)/endout.inst.i \
	  $(PREDIR)/eval.inst.i $(PREDIR)/exit_cleanup.inst.i                     \
	  $(PREDIR)/expressions.inst.i $(PREDIR)/fqcyc.inst.i                     \
	  $(PREDIR)/geta.inst.i $(PREDIR)/geta_discard.inst.i                     \
	  $(PREDIR)/geta_leftparen.inst.i $(PREDIR)/geta_rightparen.inst.i        \
	  $(PREDIR)/getf.inst.i $(PREDIR)/getflst.inst.i $(PREDIR)/getfq.inst.i   \
	  $(PREDIR)/geti.inst.i $(PREDIR)/getnxcy.inst.i $(PREDIR)/getnxtm.inst.i \
	  $(PREDIR)/getsym.inst.i $(PREDIR)/getversion.inst.i                     \
	  $(PREDIR)/gpdef.inst.i $(PREDIR)/gpdef0.inst.i $(PREDIR)/ifnotin.inst.i \
	  $(PREDIR)/initget.inst.i $(PREDIR)/irspcs.inst.i $(PREDIR)/lfchk.inst.i \
	  $(PREDIR)/lineop.inst.i $(PREDIR)/lnadv.inst.i $(PREDIR)/main.inst.i    \
	  $(PREDIR)/newfile.inst.i $(PREDIR)/newline.inst.i $(PREDIR)/noop.inst.i \
	  $(PREDIR)/nxtsym.inst.i $(PREDIR)/outfile.inst.i                        \
	  $(PREDIR)/parmsym.inst.i $(PREDIR)/peekc.inst.i $(PREDIR)/peekc2.inst.i \
	  $(PREDIR)/printdate.inst.i $(PREDIR)/printhelp.inst.i                   \
	  $(PREDIR)/printmap.inst.i $(PREDIR)/printmsg.inst.i                     \
	  $(PREDIR)/printrc.inst.i $(PREDIR)/printtc.inst.i                       \
	  $(PREDIR)/prirup.inst.i $(PREDIR)/pversion.inst.i                       \
	  $(PREDIR)/redofq.inst.i $(PREDIR)/resetio.inst.i                        \
	  $(PREDIR)/resetmsg.inst.i $(PREDIR)/run.inst.i                          \
	  $(PREDIR)/setiomrk.inst.i $(PREDIR)/setirup.inst.i                      \
	  $(PREDIR)/setup_attrs.inst.i $(PREDIR)/showfq.inst.i                    \
	  $(PREDIR)/step.inst.i $(PREDIR)/unsetio.inst.i                          \
	  $(PREDIR)/userexitfn.inst.i $(PREDIR)/walltime.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/SystemWrapper.inst.i:SystemWrapper.c ../../includes/irs.h               \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h                  \
	  ../../includes/irsctl.h
	@rm -f SystemWrapper.i
	$$irs_pre SystemWrapper.c >> SystemWrapper.i
	@mv -f SystemWrapper.i $(PREDIR)/SystemWrapper.inst.i

$(PREDIR)/conditionals.inst.i:conditionals.c ../../includes/irs.h                 \
	  ../../includes/irsrgst.h ../../includes/irsctl.h                        \
	  ../../includes/irsgenrd.h ../../includes/Hash.h                         \
	  ../../includes/Conditional.h
	@rm -f conditionals.i
	$$irs_pre conditionals.c >> conditionals.i
	@mv -f conditionals.i $(PREDIR)/conditionals.inst.i

$(PREDIR)/ctlecho.inst.i:ctlecho.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f ctlecho.i
	$$irs_pre ctlecho.c >> ctlecho.i
	@mv -f ctlecho.i $(PREDIR)/ctlecho.inst.i

$(PREDIR)/ctlerror.inst.i:ctlerror.c ../../includes/irs.h ../../includes/irsctl.h \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f ctlerror.i
	$$irs_pre ctlerror.c >> ctlerror.i
	@mv -f ctlerror.i $(PREDIR)/ctlerror.inst.i

$(PREDIR)/ctlmsg.inst.i:ctlmsg.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f ctlmsg.i
	$$irs_pre ctlmsg.c >> ctlmsg.i
	@mv -f ctlmsg.i $(PREDIR)/ctlmsg.inst.i

$(PREDIR)/ctlmsg1.inst.i:ctlmsg1.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f ctlmsg1.i
	$$irs_pre ctlmsg1.c >> ctlmsg1.i
	@mv -f ctlmsg1.i $(PREDIR)/ctlmsg1.inst.i

$(PREDIR)/ctlnotice.inst.i:ctlnotice.c ../../includes/irs.h                       \
	  ../../includes/irsctl.h
	@rm -f ctlnotice.i
	$$irs_pre ctlnotice.c >> ctlnotice.i
	@mv -f ctlnotice.i $(PREDIR)/ctlnotice.inst.i

$(PREDIR)/ctloutput.inst.i:ctloutput.c ../../includes/irs.h                       \
	  ../../includes/irsctl.h ../../includes/AEStackElm.h                     \
	  ../../includes/Rgst.h
	@rm -f ctloutput.i
	$$irs_pre ctloutput.c >> ctloutput.i
	@mv -f ctloutput.i $(PREDIR)/ctloutput.inst.i

$(PREDIR)/ctlwarning.inst.i:ctlwarning.c ../../includes/irs.h                     \
	  ../../includes/irsctl.h
	@rm -f ctlwarning.i
	$$irs_pre ctlwarning.c >> ctlwarning.i
	@mv -f ctlwarning.i $(PREDIR)/ctlwarning.inst.i

$(PREDIR)/delfq.inst.i:delfq.c ../../includes/irs.h ../../includes/irsrgst.h      \
	  ../../includes/irsctl.h ../../includes/Conditional.h                    \
	  ../../includes/CycleMesg.h ../../includes/Hash.h                        \
	  ../../includes/TimePlot.h
	@rm -f delfq.i
	$$irs_pre delfq.c >> delfq.i
	@mv -f delfq.i $(PREDIR)/delfq.inst.i

$(PREDIR)/domsg.inst.i:domsg.c ../../includes/irs.h ../../includes/irsctl.h       \
	  ../../includes/irscur.h ../../includes/irsgenrd.h                       \
	  ../../includes/CycleMesg.h ../../includes/Conditional.h                 \
	  ../../includes/FreqMesg.h
	@rm -f domsg.i
	$$irs_pre domsg.c >> domsg.i
	@mv -f domsg.i $(PREDIR)/domsg.inst.i

$(PREDIR)/endfile.inst.i:endfile.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f endfile.i
	$$irs_pre endfile.c >> endfile.i
	@mv -f endfile.i $(PREDIR)/endfile.inst.i

$(PREDIR)/endout.inst.i:endout.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f endout.i
	$$irs_pre endout.c >> endout.i
	@mv -f endout.i $(PREDIR)/endout.inst.i

$(PREDIR)/eval.inst.i:eval.c ../../includes/irs.h ../../includes/irsctl.h         \
	  ../../includes/AEStackElm.h
	@rm -f eval.i
	$$irs_pre eval.c >> eval.i
	@mv -f eval.i $(PREDIR)/eval.inst.i

$(PREDIR)/exit_cleanup.inst.i:exit_cleanup.c ../../includes/irs.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f exit_cleanup.i
	$$irs_pre exit_cleanup.c >> exit_cleanup.i
	@mv -f exit_cleanup.i $(PREDIR)/exit_cleanup.inst.i

$(PREDIR)/expressions.inst.i:expressions.c ../../includes/irs.h                   \
	  ../../includes/irsgen.h ../../includes/irsctl.h                         \
	  ../../includes/irsrgst.h ../../includes/AEStackElm.h                    \
	  ../../includes/Command.h ../../includes/Rgst.h
	@rm -f expressions.i
	$$irs_pre expressions.c >> expressions.i
	@mv -f expressions.i $(PREDIR)/expressions.inst.i

$(PREDIR)/fqcyc.inst.i:fqcyc.c ../../includes/irs.h ../../includes/irsctl.h       \
	  ../../includes/irsrgst.h ../../includes/CycleMesg.hh                    \
	  ../../includes/FreqMesg.hh ../../includes/TimePlot.hh
	@rm -f fqcyc.i
	$$irs_pre fqcyc.c >> fqcyc.i
	@mv -f fqcyc.i $(PREDIR)/fqcyc.inst.i

$(PREDIR)/geta.inst.i:geta.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f geta.i
	$$irs_pre geta.c >> geta.i
	@mv -f geta.i $(PREDIR)/geta.inst.i

$(PREDIR)/geta_discard.inst.i:geta_discard.c ../../includes/irs.h                 \
	  ../../includes/irsctl.h
	@rm -f geta_discard.i
	$$irs_pre geta_discard.c >> geta_discard.i
	@mv -f geta_discard.i $(PREDIR)/geta_discard.inst.i

$(PREDIR)/geta_leftparen.inst.i:geta_leftparen.c ../../includes/irs.h             \
	  ../../includes/irsctl.h
	@rm -f geta_leftparen.i
	$$irs_pre geta_leftparen.c >> geta_leftparen.i
	@mv -f geta_leftparen.i $(PREDIR)/geta_leftparen.inst.i

$(PREDIR)/geta_rightparen.inst.i:geta_rightparen.c ../../includes/irs.h           \
	  ../../includes/irsctl.h
	@rm -f geta_rightparen.i
	$$irs_pre geta_rightparen.c >> geta_rightparen.i
	@mv -f geta_rightparen.i $(PREDIR)/geta_rightparen.inst.i

$(PREDIR)/getf.inst.i:getf.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f getf.i
	$$irs_pre getf.c >> getf.i
	@mv -f getf.i $(PREDIR)/getf.inst.i

$(PREDIR)/getflst.inst.i:getflst.c ../../includes/irs.h ../../includes/Spline.h
	@rm -f getflst.i
	$$irs_pre getflst.c >> getflst.i
	@mv -f getflst.i $(PREDIR)/getflst.inst.i

$(PREDIR)/getfq.inst.i:getfq.c ../../includes/irs.h ../../includes/irsctl.h       \
	  ../../includes/CycleMesg.h ../../includes/TimePlot.h
	@rm -f getfq.i
	$$irs_pre getfq.c >> getfq.i
	@mv -f getfq.i $(PREDIR)/getfq.inst.i

$(PREDIR)/geti.inst.i:geti.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f geti.i
	$$irs_pre geti.c >> geti.i
	@mv -f geti.i $(PREDIR)/geti.inst.i

$(PREDIR)/getnxcy.inst.i:getnxcy.c ../../includes/irs.h ../../includes/irsctl.h   \
	  ../../includes/Conditional.h ../../includes/CycleMesg.h
	@rm -f getnxcy.i
	$$irs_pre getnxcy.c >> getnxcy.i
	@mv -f getnxcy.i $(PREDIR)/getnxcy.inst.i

$(PREDIR)/getnxtm.inst.i:getnxtm.c ../../includes/irs.h ../../includes/irsctl.h   \
	  ../../includes/FreqMesg.h
	@rm -f getnxtm.i
	$$irs_pre getnxtm.c >> getnxtm.i
	@mv -f getnxtm.i $(PREDIR)/getnxtm.inst.i

$(PREDIR)/getsym.inst.i:getsym.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f getsym.i
	$$irs_pre getsym.c >> getsym.i
	@mv -f getsym.i $(PREDIR)/getsym.inst.i

$(PREDIR)/getversion.inst.i:getversion.c ../../includes/irsversion.h              \
	  ../../includes/irs.h ../../includes/irsdmp.h                            \
	  ../../includes/VersionData.hh
	@rm -f getversion.i
	$$irs_pre getversion.c >> getversion.i
	@mv -f getversion.i $(PREDIR)/getversion.inst.i

$(PREDIR)/gpdef.inst.i:gpdef.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f gpdef.i
	$$irs_pre gpdef.c >> gpdef.i
	@mv -f gpdef.i $(PREDIR)/gpdef.inst.i

$(PREDIR)/gpdef0.inst.i:gpdef0.c ../../includes/irs.h ../../includes/irsctl.h     \
	  ../../includes/Gparm.h
	@rm -f gpdef0.i
	$$irs_pre gpdef0.c >> gpdef0.i
	@mv -f gpdef0.i $(PREDIR)/gpdef0.inst.i

$(PREDIR)/ifnotin.inst.i:ifnotin.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f ifnotin.i
	$$irs_pre ifnotin.c >> ifnotin.i
	@mv -f ifnotin.i $(PREDIR)/ifnotin.inst.i

$(PREDIR)/initget.inst.i:initget.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f initget.i
	$$irs_pre initget.c >> initget.i
	@mv -f initget.i $(PREDIR)/initget.inst.i

$(PREDIR)/irspcs.inst.i:irspcs.c ../../includes/irs.h
	@rm -f irspcs.i
	$$irs_pre irspcs.c >> irspcs.i
	@mv -f irspcs.i $(PREDIR)/irspcs.inst.i

$(PREDIR)/lfchk.inst.i:lfchk.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f lfchk.i
	$$irs_pre lfchk.c >> lfchk.i
	@mv -f lfchk.i $(PREDIR)/lfchk.inst.i

$(PREDIR)/lineop.inst.i:lineop.c ../../includes/irs.h ../../includes/irsrgst.h    \
	  ../../includes/irsctl.h ../../includes/FunctionTimer.h                  \
	  ../../includes/irscom.h
	@rm -f lineop.i
	$$irs_pre lineop.c >> lineop.i
	@mv -f lineop.i $(PREDIR)/lineop.inst.i

$(PREDIR)/lnadv.inst.i:lnadv.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f lnadv.i
	$$irs_pre lnadv.c >> lnadv.i
	@mv -f lnadv.i $(PREDIR)/lnadv.inst.i

$(PREDIR)/main.inst.i:main.c ../../includes/irs.h ../../includes/irscom.h         \
	  ../../includes/irsdmp.h ../../includes/irsedits.h                       \
	  ../../includes/irseos.h ../../includes/irsgen.h                         \
	  ../../includes/irsgenrd.h ../../includes/irsparm.h                      \
	  ../../includes/irsrgst.h ../../includes/irssys.h                        \
	  ../../includes/irsctl.hh ../../includes/Conditional.h                   \
	  ../../includes/Hash.h ../../includes/FunctionTimer.h                    \
	  ../../includes/ProblemArray.h ../../includes/VersionData.h              \
	  ../../includes/Gparm.hh
	@rm -f main.i
	$$irs_pre main.c >> main.i
	@mv -f main.i $(PREDIR)/main.inst.i

$(PREDIR)/newfile.inst.i:newfile.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f newfile.i
	$$irs_pre newfile.c >> newfile.i
	@mv -f newfile.i $(PREDIR)/newfile.inst.i

$(PREDIR)/newline.inst.i:newline.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f newline.i
	$$irs_pre newline.c >> newline.i
	@mv -f newline.i $(PREDIR)/newline.inst.i

$(PREDIR)/noop.inst.i:noop.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f noop.i
	$$irs_pre noop.c >> noop.i
	@mv -f noop.i $(PREDIR)/noop.inst.i

$(PREDIR)/nxtsym.inst.i:nxtsym.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f nxtsym.i
	$$irs_pre nxtsym.c >> nxtsym.i
	@mv -f nxtsym.i $(PREDIR)/nxtsym.inst.i

$(PREDIR)/outfile.inst.i:outfile.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f outfile.i
	$$irs_pre outfile.c >> outfile.i
	@mv -f outfile.i $(PREDIR)/outfile.inst.i

$(PREDIR)/parmsym.inst.i:parmsym.c ../../includes/irs.h ../../includes/irsctl.h   \
	  ../../includes/Gparm.h
	@rm -f parmsym.i
	$$irs_pre parmsym.c >> parmsym.i
	@mv -f parmsym.i $(PREDIR)/parmsym.inst.i

$(PREDIR)/peekc.inst.i:peekc.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f peekc.i
	$$irs_pre peekc.c >> peekc.i
	@mv -f peekc.i $(PREDIR)/peekc.inst.i

$(PREDIR)/peekc2.inst.i:peekc2.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f peekc2.i
	$$irs_pre peekc2.c >> peekc2.i
	@mv -f peekc2.i $(PREDIR)/peekc2.inst.i

$(PREDIR)/printdate.inst.i:printdate.c ../../includes/irs.h
	@rm -f printdate.i
	$$irs_pre printdate.c >> printdate.i
	@mv -f printdate.i $(PREDIR)/printdate.inst.i

$(PREDIR)/printhelp.inst.i:printhelp.c ../../includes/irs.h
	@rm -f printhelp.i
	$$irs_pre printhelp.c >> printhelp.i
	@mv -f printhelp.i $(PREDIR)/printhelp.inst.i

$(PREDIR)/printmap.inst.i:printmap.c ../../includes/irs.h ../../includes/irsctl.h \
	  ../../includes/irscom.h ../../includes/irsdmp.h                         \
	  ../../includes/BlockMapping.h ../../includes/Hash.h                     \
	  ../../includes/FunctionTimer.h
	@rm -f printmap.i
	$$irs_pre printmap.c >> printmap.i
	@mv -f printmap.i $(PREDIR)/printmap.inst.i

$(PREDIR)/printmsg.inst.i:printmsg.c ../../includes/irs.h ../../includes/irsctl.h \
	  ../../includes/Conditional.h ../../includes/CycleMesg.h                 \
	  ../../includes/FreqMesg.h
	@rm -f printmsg.i
	$$irs_pre printmsg.c >> printmsg.i
	@mv -f printmsg.i $(PREDIR)/printmsg.inst.i

$(PREDIR)/printrc.inst.i:printrc.c ../../includes/irs.h
	@rm -f printrc.i
	$$irs_pre printrc.c >> printrc.i
	@mv -f printrc.i $(PREDIR)/printrc.inst.i

$(PREDIR)/printtc.inst.i:printtc.c ../../includes/irs.h ../../includes/irslag.h   \
	  ../../includes/irsctl.h ../../includes/TimeStepControl.h
	@rm -f printtc.i
	$$irs_pre printtc.c >> printtc.i
	@mv -f printtc.i $(PREDIR)/printtc.inst.i

$(PREDIR)/prirup.inst.i:prirup.c ../../includes/irs.h
	@rm -f prirup.i
	$$irs_pre prirup.c >> prirup.i
	@mv -f prirup.i $(PREDIR)/prirup.inst.i

$(PREDIR)/pversion.inst.i:pversion.c ../../includes/irs.h                         \
	  ../../includes/VersionData.h
	@rm -f pversion.i
	$$irs_pre pversion.c >> pversion.i
	@mv -f pversion.i $(PREDIR)/pversion.inst.i

$(PREDIR)/redofq.inst.i:redofq.c ../../includes/irs.h ../../includes/irsrgst.h    \
	  ../../includes/irsctl.h ../../includes/Conditional.h                    \
	  ../../includes/CycleMesg.h ../../includes/Hash.h                        \
	  ../../includes/TimePlot.h
	@rm -f redofq.i
	$$irs_pre redofq.c >> redofq.i
	@mv -f redofq.i $(PREDIR)/redofq.inst.i

$(PREDIR)/resetio.inst.i:resetio.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f resetio.i
	$$irs_pre resetio.c >> resetio.i
	@mv -f resetio.i $(PREDIR)/resetio.inst.i

$(PREDIR)/resetmsg.inst.i:resetmsg.c ../../includes/irs.h ../../includes/irsctl.h \
	  ../../includes/CycleMesg.h ../../includes/FreqMesg.h
	@rm -f resetmsg.i
	$$irs_pre resetmsg.c >> resetmsg.i
	@mv -f resetmsg.i $(PREDIR)/resetmsg.inst.i

$(PREDIR)/run.inst.i:run.c ../../includes/irs.h ../../includes/irslag.h           \
	  ../../includes/irsctl.h
	@rm -f run.i
	$$irs_pre run.c >> run.i
	@mv -f run.i $(PREDIR)/run.inst.i

$(PREDIR)/setiomrk.inst.i:setiomrk.c ../../includes/irs.h                         \
	  ../../includes/irsctl.h
	@rm -f setiomrk.i
	$$irs_pre setiomrk.c >> setiomrk.i
	@mv -f setiomrk.i $(PREDIR)/setiomrk.inst.i

$(PREDIR)/setirup.inst.i:setirup.c ../../includes/irs.h
	@rm -f setirup.i
	$$irs_pre setirup.c >> setirup.i
	@mv -f setirup.i $(PREDIR)/setirup.inst.i

$(PREDIR)/setup_attrs.inst.i:setup_attrs.c ../../includes/irs.h                   \
	  ../../includes/irsrgst.h ../../includes/Conditional.h                   \
	  ../../includes/FunctionTimer.h ../../includes/FreqMesg.h                \
	  ../../includes/Gparm.h ../../includes/Region.h ../../includes/Source.h  \
	  ../../includes/Spline.h ../../includes/Transform.h                      \
	  ../../includes/TimePlot.h
	@rm -f setup_attrs.i
	$$irs_pre setup_attrs.c >> setup_attrs.i
	@mv -f setup_attrs.i $(PREDIR)/setup_attrs.inst.i

$(PREDIR)/showfq.inst.i:showfq.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f showfq.i
	$$irs_pre showfq.c >> showfq.i
	@mv -f showfq.i $(PREDIR)/showfq.inst.i

$(PREDIR)/step.inst.i:step.c ../../includes/irs.h ../../includes/irslag.h         \
	  ../../includes/CycleMesg.h
	@rm -f step.i
	$$irs_pre step.c >> step.i
	@mv -f step.i $(PREDIR)/step.inst.i

$(PREDIR)/unsetio.inst.i:unsetio.c ../../includes/irs.h ../../includes/irsctl.h
	@rm -f unsetio.i
	$$irs_pre unsetio.c >> unsetio.i
	@mv -f unsetio.i $(PREDIR)/unsetio.inst.i

$(PREDIR)/userexitfn.inst.i:userexitfn.c ../../includes/irs.h                     \
	  ../../includes/irsctl.h
	@rm -f userexitfn.i
	$$irs_pre userexitfn.c >> userexitfn.i
	@mv -f userexitfn.i $(PREDIR)/userexitfn.inst.i

$(PREDIR)/walltime.inst.i:walltime.c ../../includes/irs.h ../../includes/irscom.h \
	  ../../includes/irsctl.h ../../includes/irssys.h                         \
	  ../../includes/FunctionTimer.h ../../includes/AEStackElm.h
	@rm -f walltime.i
	$$irs_pre walltime.c >> walltime.i
	@mv -f walltime.i $(PREDIR)/walltime.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libctl_inst

libctl_inst:$(BI)(SystemWrapper.inst.o) $(BI)(conditionals.inst.o)                \
	  $(BI)(ctlecho.inst.o) $(BI)(ctlerror.inst.o) $(BI)(ctlmsg.inst.o)       \
	  $(BI)(ctlmsg1.inst.o) $(BI)(ctlnotice.inst.o) $(BI)(ctloutput.inst.o)   \
	  $(BI)(ctlwarning.inst.o) $(BI)(delfq.inst.o) $(BI)(domsg.inst.o)        \
	  $(BI)(endfile.inst.o) $(BI)(endout.inst.o) $(BI)(eval.inst.o)           \
	  $(BI)(exit_cleanup.inst.o) $(BI)(expressions.inst.o)                    \
	  $(BI)(fqcyc.inst.o) $(BI)(geta.inst.o) $(BI)(geta_discard.inst.o)       \
	  $(BI)(geta_leftparen.inst.o) $(BI)(geta_rightparen.inst.o)              \
	  $(BI)(getf.inst.o) $(BI)(getflst.inst.o) $(BI)(getfq.inst.o)            \
	  $(BI)(geti.inst.o) $(BI)(getnxcy.inst.o) $(BI)(getnxtm.inst.o)          \
	  $(BI)(getsym.inst.o) $(BI)(getversion.inst.o) $(BI)(gpdef.inst.o)       \
	  $(BI)(gpdef0.inst.o) $(BI)(ifnotin.inst.o) $(BI)(initget.inst.o)        \
	  $(BI)(irspcs.inst.o) $(BI)(lfchk.inst.o) $(BI)(lineop.inst.o)           \
	  $(BI)(lnadv.inst.o) $(BI)(main.inst.o) $(BI)(newfile.inst.o)            \
	  $(BI)(newline.inst.o) $(BI)(noop.inst.o) $(BI)(nxtsym.inst.o)           \
	  $(BI)(outfile.inst.o) $(BI)(parmsym.inst.o) $(BI)(peekc.inst.o)         \
	  $(BI)(peekc2.inst.o) $(BI)(printdate.inst.o) $(BI)(printhelp.inst.o)    \
	  $(BI)(printmap.inst.o) $(BI)(printmsg.inst.o) $(BI)(printrc.inst.o)     \
	  $(BI)(printtc.inst.o) $(BI)(prirup.inst.o) $(BI)(pversion.inst.o)       \
	  $(BI)(redofq.inst.o) $(BI)(resetio.inst.o) $(BI)(resetmsg.inst.o)       \
	  $(BI)(run.inst.o) $(BI)(setiomrk.inst.o) $(BI)(setirup.inst.o)          \
	  $(BI)(setup_attrs.inst.o) $(BI)(showfq.inst.o) $(BI)(step.inst.o)       \
	  $(BI)(unsetio.inst.o) $(BI)(userexitfn.inst.o) $(BI)(walltime.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libctl_inst.a $(B); \
		ln -sf libctl_inst.a $(B)); \
	  fi
	  @echo 'libctl_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(SystemWrapper.inst.o):$(INSTDIR)/SystemWrapper.inst.i
	$$irs_post $(INSTDIR)/SystemWrapper.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/SystemWrapper.inst.i $(DB)/SystemWrapper.c 

$(BI)(conditionals.inst.o):$(INSTDIR)/conditionals.inst.i
	$$irs_post $(INSTDIR)/conditionals.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/conditionals.inst.i $(DB)/conditionals.c 

$(BI)(ctlecho.inst.o):$(INSTDIR)/ctlecho.inst.i
	$$irs_post $(INSTDIR)/ctlecho.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ctlecho.inst.i $(DB)/ctlecho.c 

$(BI)(ctlerror.inst.o):$(INSTDIR)/ctlerror.inst.i
	$$irs_post $(INSTDIR)/ctlerror.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ctlerror.inst.i $(DB)/ctlerror.c 

$(BI)(ctlmsg.inst.o):$(INSTDIR)/ctlmsg.inst.i
	$$irs_post $(INSTDIR)/ctlmsg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ctlmsg.inst.i $(DB)/ctlmsg.c 

$(BI)(ctlmsg1.inst.o):$(INSTDIR)/ctlmsg1.inst.i
	$$irs_post $(INSTDIR)/ctlmsg1.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ctlmsg1.inst.i $(DB)/ctlmsg1.c 

$(BI)(ctlnotice.inst.o):$(INSTDIR)/ctlnotice.inst.i
	$$irs_post $(INSTDIR)/ctlnotice.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ctlnotice.inst.i $(DB)/ctlnotice.c 

$(BI)(ctloutput.inst.o):$(INSTDIR)/ctloutput.inst.i
	$$irs_post $(INSTDIR)/ctloutput.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ctloutput.inst.i $(DB)/ctloutput.c 

$(BI)(ctlwarning.inst.o):$(INSTDIR)/ctlwarning.inst.i
	$$irs_post $(INSTDIR)/ctlwarning.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ctlwarning.inst.i $(DB)/ctlwarning.c 

$(BI)(delfq.inst.o):$(INSTDIR)/delfq.inst.i
	$$irs_post $(INSTDIR)/delfq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/delfq.inst.i $(DB)/delfq.c 

$(BI)(domsg.inst.o):$(INSTDIR)/domsg.inst.i
	$$irs_post $(INSTDIR)/domsg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/domsg.inst.i $(DB)/domsg.c 

$(BI)(endfile.inst.o):$(INSTDIR)/endfile.inst.i
	$$irs_post $(INSTDIR)/endfile.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/endfile.inst.i $(DB)/endfile.c 

$(BI)(endout.inst.o):$(INSTDIR)/endout.inst.i
	$$irs_post $(INSTDIR)/endout.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/endout.inst.i $(DB)/endout.c 

$(BI)(eval.inst.o):$(INSTDIR)/eval.inst.i
	$$irs_post $(INSTDIR)/eval.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/eval.inst.i $(DB)/eval.c 

$(BI)(exit_cleanup.inst.o):$(INSTDIR)/exit_cleanup.inst.i
	$$irs_post $(INSTDIR)/exit_cleanup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/exit_cleanup.inst.i $(DB)/exit_cleanup.c 

$(BI)(expressions.inst.o):$(INSTDIR)/expressions.inst.i
	$$irs_post $(INSTDIR)/expressions.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/expressions.inst.i $(DB)/expressions.c 

$(BI)(fqcyc.inst.o):$(INSTDIR)/fqcyc.inst.i
	$$irs_post $(INSTDIR)/fqcyc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/fqcyc.inst.i $(DB)/fqcyc.c 

$(BI)(geta.inst.o):$(INSTDIR)/geta.inst.i
	$$irs_post $(INSTDIR)/geta.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geta.inst.i $(DB)/geta.c 

$(BI)(geta_discard.inst.o):$(INSTDIR)/geta_discard.inst.i
	$$irs_post $(INSTDIR)/geta_discard.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geta_discard.inst.i $(DB)/geta_discard.c 

$(BI)(geta_leftparen.inst.o):$(INSTDIR)/geta_leftparen.inst.i
	$$irs_post $(INSTDIR)/geta_leftparen.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geta_leftparen.inst.i $(DB)/geta_leftparen.c 

$(BI)(geta_rightparen.inst.o):$(INSTDIR)/geta_rightparen.inst.i
	$$irs_post $(INSTDIR)/geta_rightparen.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geta_rightparen.inst.i $(DB)/geta_rightparen.c 

$(BI)(getf.inst.o):$(INSTDIR)/getf.inst.i
	$$irs_post $(INSTDIR)/getf.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getf.inst.i $(DB)/getf.c 

$(BI)(getflst.inst.o):$(INSTDIR)/getflst.inst.i
	$$irs_post $(INSTDIR)/getflst.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getflst.inst.i $(DB)/getflst.c 

$(BI)(getfq.inst.o):$(INSTDIR)/getfq.inst.i
	$$irs_post $(INSTDIR)/getfq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getfq.inst.i $(DB)/getfq.c 

$(BI)(geti.inst.o):$(INSTDIR)/geti.inst.i
	$$irs_post $(INSTDIR)/geti.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geti.inst.i $(DB)/geti.c 

$(BI)(getnxcy.inst.o):$(INSTDIR)/getnxcy.inst.i
	$$irs_post $(INSTDIR)/getnxcy.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getnxcy.inst.i $(DB)/getnxcy.c 

$(BI)(getnxtm.inst.o):$(INSTDIR)/getnxtm.inst.i
	$$irs_post $(INSTDIR)/getnxtm.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getnxtm.inst.i $(DB)/getnxtm.c 

$(BI)(getsym.inst.o):$(INSTDIR)/getsym.inst.i
	$$irs_post $(INSTDIR)/getsym.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getsym.inst.i $(DB)/getsym.c 

$(BI)(getversion.inst.o):$(INSTDIR)/getversion.inst.i
	$$irs_post $(INSTDIR)/getversion.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getversion.inst.i $(DB)/getversion.c 

$(BI)(gpdef.inst.o):$(INSTDIR)/gpdef.inst.i
	$$irs_post $(INSTDIR)/gpdef.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/gpdef.inst.i $(DB)/gpdef.c 

$(BI)(gpdef0.inst.o):$(INSTDIR)/gpdef0.inst.i
	$$irs_post $(INSTDIR)/gpdef0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/gpdef0.inst.i $(DB)/gpdef0.c 

$(BI)(ifnotin.inst.o):$(INSTDIR)/ifnotin.inst.i
	$$irs_post $(INSTDIR)/ifnotin.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ifnotin.inst.i $(DB)/ifnotin.c 

$(BI)(initget.inst.o):$(INSTDIR)/initget.inst.i
	$$irs_post $(INSTDIR)/initget.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/initget.inst.i $(DB)/initget.c 

$(BI)(irspcs.inst.o):$(INSTDIR)/irspcs.inst.i
	$$irs_post $(INSTDIR)/irspcs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/irspcs.inst.i $(DB)/irspcs.c 

$(BI)(lfchk.inst.o):$(INSTDIR)/lfchk.inst.i
	$$irs_post $(INSTDIR)/lfchk.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/lfchk.inst.i $(DB)/lfchk.c 

$(BI)(lineop.inst.o):$(INSTDIR)/lineop.inst.i
	$$irs_post $(INSTDIR)/lineop.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/lineop.inst.i $(DB)/lineop.c 

$(BI)(lnadv.inst.o):$(INSTDIR)/lnadv.inst.i
	$$irs_post $(INSTDIR)/lnadv.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/lnadv.inst.i $(DB)/lnadv.c 

$(BI)(main.inst.o):$(INSTDIR)/main.inst.i
	$$irs_post $(INSTDIR)/main.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/main.inst.i $(DB)/main.c 

$(BI)(newfile.inst.o):$(INSTDIR)/newfile.inst.i
	$$irs_post $(INSTDIR)/newfile.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/newfile.inst.i $(DB)/newfile.c 

$(BI)(newline.inst.o):$(INSTDIR)/newline.inst.i
	$$irs_post $(INSTDIR)/newline.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/newline.inst.i $(DB)/newline.c 

$(BI)(noop.inst.o):$(INSTDIR)/noop.inst.i
	$$irs_post $(INSTDIR)/noop.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/noop.inst.i $(DB)/noop.c 

$(BI)(nxtsym.inst.o):$(INSTDIR)/nxtsym.inst.i
	$$irs_post $(INSTDIR)/nxtsym.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/nxtsym.inst.i $(DB)/nxtsym.c 

$(BI)(outfile.inst.o):$(INSTDIR)/outfile.inst.i
	$$irs_post $(INSTDIR)/outfile.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/outfile.inst.i $(DB)/outfile.c 

$(BI)(parmsym.inst.o):$(INSTDIR)/parmsym.inst.i
	$$irs_post $(INSTDIR)/parmsym.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/parmsym.inst.i $(DB)/parmsym.c 

$(BI)(peekc.inst.o):$(INSTDIR)/peekc.inst.i
	$$irs_post $(INSTDIR)/peekc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/peekc.inst.i $(DB)/peekc.c 

$(BI)(peekc2.inst.o):$(INSTDIR)/peekc2.inst.i
	$$irs_post $(INSTDIR)/peekc2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/peekc2.inst.i $(DB)/peekc2.c 

$(BI)(printdate.inst.o):$(INSTDIR)/printdate.inst.i
	$$irs_post $(INSTDIR)/printdate.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printdate.inst.i $(DB)/printdate.c 

$(BI)(printhelp.inst.o):$(INSTDIR)/printhelp.inst.i
	$$irs_post $(INSTDIR)/printhelp.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printhelp.inst.i $(DB)/printhelp.c 

$(BI)(printmap.inst.o):$(INSTDIR)/printmap.inst.i
	$$irs_post $(INSTDIR)/printmap.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printmap.inst.i $(DB)/printmap.c 

$(BI)(printmsg.inst.o):$(INSTDIR)/printmsg.inst.i
	$$irs_post $(INSTDIR)/printmsg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printmsg.inst.i $(DB)/printmsg.c 

$(BI)(printrc.inst.o):$(INSTDIR)/printrc.inst.i
	$$irs_post $(INSTDIR)/printrc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printrc.inst.i $(DB)/printrc.c 

$(BI)(printtc.inst.o):$(INSTDIR)/printtc.inst.i
	$$irs_post $(INSTDIR)/printtc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/printtc.inst.i $(DB)/printtc.c 

$(BI)(prirup.inst.o):$(INSTDIR)/prirup.inst.i
	$$irs_post $(INSTDIR)/prirup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/prirup.inst.i $(DB)/prirup.c 

$(BI)(pversion.inst.o):$(INSTDIR)/pversion.inst.i
	$$irs_post $(INSTDIR)/pversion.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/pversion.inst.i $(DB)/pversion.c 

$(BI)(redofq.inst.o):$(INSTDIR)/redofq.inst.i
	$$irs_post $(INSTDIR)/redofq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/redofq.inst.i $(DB)/redofq.c 

$(BI)(resetio.inst.o):$(INSTDIR)/resetio.inst.i
	$$irs_post $(INSTDIR)/resetio.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/resetio.inst.i $(DB)/resetio.c 

$(BI)(resetmsg.inst.o):$(INSTDIR)/resetmsg.inst.i
	$$irs_post $(INSTDIR)/resetmsg.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/resetmsg.inst.i $(DB)/resetmsg.c 

$(BI)(run.inst.o):$(INSTDIR)/run.inst.i
	$$irs_post $(INSTDIR)/run.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/run.inst.i $(DB)/run.c 

$(BI)(setiomrk.inst.o):$(INSTDIR)/setiomrk.inst.i
	$$irs_post $(INSTDIR)/setiomrk.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setiomrk.inst.i $(DB)/setiomrk.c 

$(BI)(setirup.inst.o):$(INSTDIR)/setirup.inst.i
	$$irs_post $(INSTDIR)/setirup.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setirup.inst.i $(DB)/setirup.c 

$(BI)(setup_attrs.inst.o):$(INSTDIR)/setup_attrs.inst.i
	$$irs_post $(INSTDIR)/setup_attrs.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setup_attrs.inst.i $(DB)/setup_attrs.c 

$(BI)(showfq.inst.o):$(INSTDIR)/showfq.inst.i
	$$irs_post $(INSTDIR)/showfq.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/showfq.inst.i $(DB)/showfq.c 

$(BI)(step.inst.o):$(INSTDIR)/step.inst.i
	$$irs_post $(INSTDIR)/step.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/step.inst.i $(DB)/step.c 

$(BI)(unsetio.inst.o):$(INSTDIR)/unsetio.inst.i
	$$irs_post $(INSTDIR)/unsetio.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/unsetio.inst.i $(DB)/unsetio.c 

$(BI)(userexitfn.inst.o):$(INSTDIR)/userexitfn.inst.i
	$$irs_post $(INSTDIR)/userexitfn.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/userexitfn.inst.i $(DB)/userexitfn.c 

$(BI)(walltime.inst.o):$(INSTDIR)/walltime.inst.i
	$$irs_post $(INSTDIR)/walltime.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/walltime.inst.i $(DB)/walltime.c 

DEP_SRCS = \
	SystemWrapper.c conditionals.c ctlecho.c ctlerror.c ctlmsg.c ctlmsg1.c  \
	ctlnotice.c ctloutput.c ctlwarning.c delfq.c domsg.c endfile.c endout.c  \
	eval.c exit_cleanup.c expressions.c fqcyc.c geta.c geta_discard.c geta_leftparen.c  \
	geta_rightparen.c getf.c getflst.c getfq.c geti.c getnxcy.c getnxtm.c  \
	getsym.c getversion.c gpdef.c gpdef0.c ifnotin.c initget.c irspcs.c lfchk.c  \
	lineop.c lnadv.c main.c newfile.c newline.c noop.c nxtsym.c outfile.c  \
	parmsym.c peekc.c peekc2.c printdate.c printhelp.c printmap.c printmsg.c  \
	printrc.c printtc.c prirup.c pversion.c redofq.c resetio.c resetmsg.c  \
	run.c setiomrk.c setirup.c setup_attrs.c showfq.c step.c unsetio.c userexitfn.c  \
	walltime.c terry_trace.c

depend:
	@cp -f Makefile.ctl Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

