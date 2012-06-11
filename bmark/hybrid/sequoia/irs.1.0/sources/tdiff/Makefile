
################################################################################
#
# Makefile for irs library tdiff
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
B = ../$(LIB_DIR)/libtdiff.a
BI = ../$(LIB_DIR)/libtdiff_inst.a

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
SRCDIR = ../sources/tdiff

# Relative path to the output file for lint
#------------------------------------------
# LO = ../../build/lint.out

# library objects list
#---------------------

libtdiff:$(B)(ChemPotCalc.o) $(B)(ConductionCoef.o) $(B)(DiffCoef.o)              \
	  $(B)(DivgradDriver.o) $(B)(FemDivgrad3.o) $(B)(FemGrad3d.o)             \
	  $(B)(FluxLimiter2d.o) $(B)(FluxLimiter3d.o) $(B)(FluxLimiterDriver.o)   \
	  $(B)(GefaGedi.o) $(B)(KpAnalytic.o) $(B)(KrAnalytic.o)                  \
	  $(B)(MatrixSolve.o) $(B)(MatterConduction.o) $(B)(MatterDiagonal.o)     \
	  $(B)(MatterWainwright.o) $(B)(RadiationMemory.o)                        \
	  $(B)(RadiationSourceBC.o) $(B)(RegionTable.o)                           \
	  $(B)(SetFaceTemperature.o) $(B)(bound_free.o) $(B)(cblkbc.o)            \
	  $(B)(cblkbc2.o) $(B)(cblkbc3.o) $(B)(diagonal.o) $(B)(diff1g.o)         \
	  $(B)(divgrad2.o) $(B)(divgrad3.o) $(B)(divgradpert2d.o)                 \
	  $(B)(divgradpert3d.o) $(B)(geteicouple.o) $(B)(gettfzstar.o)            \
	  $(B)(getzabar0.o) $(B)(gtkappabnd.o) $(B)(kapmlt.o) $(B)(newMatrix.o)   \
	  $(B)(norml2.o) $(B)(opac2t.o) $(B)(opaclmt.o) $(B)(planck_opacity.o)    \
	  $(B)(radfree.o) $(B)(radinit.o) $(B)(rdiff.o) $(B)(rdiffbc.o)           \
	  $(B)(rdiffbc2.o) $(B)(rdiffbc3.o) $(B)(rdiffset.o) $(B)(rdiffsrc.o)     \
	  $(B)(reicouple.o) $(B)(retransfer.o) $(B)(rmatmult.o) $(B)(rmatmult2.o) \
	  $(B)(rmatmult3.o) $(B)(rsrcbc.o) $(B)(rsrcbc2.o) $(B)(rsrcbc3.o)        \
	  $(B)(setpz1.o) $(B)(setpz2.o) $(B)(tblkinit.o) $(B)(tdiff.o)            \
	  $(B)(teicouple.o) $(B)(zstarcal.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(B) *.o; \
		$$irs_ar $(B) *.o; \
		rm *.o object_file_flag); \
	  fi
	  @echo 'tdiff library current'

# creation deps
#---------------
$(B)(ChemPotCalc.o):ChemPotCalc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ChemPotCalc.c $(DB)/ChemPotCalc.c 

$(B)(ConductionCoef.o):ConductionCoef.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/ConductionCoef.c $(DB)/ConductionCoef.c 

../../includes/DiffusionData.hh:../../includes/DiffusionData.h
	cp ../../includes/DiffusionData.h ../../includes/DiffusionData.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/DiffusionData.hh
	irs_hhinit ../../includes/DiffusionData.hh

$(B)(DiffCoef.o):../../includes/DiffusionData.hh

$(B)(DiffCoef.o):DiffCoef.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/DiffCoef.c $(DB)/DiffCoef.c 

$(B)(DivgradDriver.o):DivgradDriver.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/DivgradDriver.c $(DB)/DivgradDriver.c 

$(B)(FemDivgrad3.o):FemDivgrad3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FemDivgrad3.c $(DB)/FemDivgrad3.c 

$(B)(FemGrad3d.o):FemGrad3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FemGrad3d.c $(DB)/FemGrad3d.c 

$(B)(FluxLimiter2d.o):FluxLimiter2d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FluxLimiter2d.c $(DB)/FluxLimiter2d.c 

$(B)(FluxLimiter3d.o):FluxLimiter3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FluxLimiter3d.c $(DB)/FluxLimiter3d.c 

$(B)(FluxLimiterDriver.o):FluxLimiterDriver.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/FluxLimiterDriver.c $(DB)/FluxLimiterDriver.c 

$(B)(GefaGedi.o):GefaGedi.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/GefaGedi.c $(DB)/GefaGedi.c 

$(B)(KpAnalytic.o):KpAnalytic.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/KpAnalytic.c $(DB)/KpAnalytic.c 

$(B)(KrAnalytic.o):KrAnalytic.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/KrAnalytic.c $(DB)/KrAnalytic.c 

$(B)(MatrixSolve.o):MatrixSolve.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/MatrixSolve.c $(DB)/MatrixSolve.c 

$(B)(MatterConduction.o):MatterConduction.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/MatterConduction.c $(DB)/MatterConduction.c 

$(B)(MatterDiagonal.o):MatterDiagonal.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/MatterDiagonal.c $(DB)/MatterDiagonal.c 

$(B)(MatterWainwright.o):MatterWainwright.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/MatterWainwright.c $(DB)/MatterWainwright.c 

../../includes/RadiationData.hh:../../includes/RadiationData.h
	cp ../../includes/RadiationData.h ../../includes/RadiationData.hh
	perl -p -i -e 's/extern\s+//g' ../../includes/RadiationData.hh
	irs_hhinit ../../includes/RadiationData.hh

$(B)(RadiationMemory.o):../../includes/RadiationData.hh

$(B)(RadiationMemory.o):RadiationMemory.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/RadiationMemory.c $(DB)/RadiationMemory.c 

$(B)(RadiationSourceBC.o):RadiationSourceBC.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/RadiationSourceBC.c $(DB)/RadiationSourceBC.c 

$(B)(RegionTable.o):RegionTable.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/RegionTable.c $(DB)/RegionTable.c 

$(B)(SetFaceTemperature.o):SetFaceTemperature.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/SetFaceTemperature.c $(DB)/SetFaceTemperature.c 

$(B)(bound_free.o):bound_free.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/bound_free.c $(DB)/bound_free.c 

$(B)(cblkbc.o):cblkbc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/cblkbc.c $(DB)/cblkbc.c 

$(B)(cblkbc2.o):cblkbc2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/cblkbc2.c $(DB)/cblkbc2.c 

$(B)(cblkbc3.o):cblkbc3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/cblkbc3.c $(DB)/cblkbc3.c 

$(B)(diagonal.o):diagonal.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/diagonal.c $(DB)/diagonal.c 

$(B)(diff1g.o):diff1g.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/diff1g.c $(DB)/diff1g.c 

$(B)(divgrad2.o):divgrad2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/divgrad2.c $(DB)/divgrad2.c 

$(B)(divgrad3.o):divgrad3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/divgrad3.c $(DB)/divgrad3.c 

$(B)(divgradpert2d.o):divgradpert2d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/divgradpert2d.c $(DB)/divgradpert2d.c 

$(B)(divgradpert3d.o):divgradpert3d.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/divgradpert3d.c $(DB)/divgradpert3d.c 

$(B)(geteicouple.o):geteicouple.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/geteicouple.c $(DB)/geteicouple.c 

$(B)(gettfzstar.o):gettfzstar.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/gettfzstar.c $(DB)/gettfzstar.c 

$(B)(getzabar0.o):getzabar0.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/getzabar0.c $(DB)/getzabar0.c 

$(B)(gtkappabnd.o):gtkappabnd.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/gtkappabnd.c $(DB)/gtkappabnd.c 

$(B)(kapmlt.o):kapmlt.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/kapmlt.c $(DB)/kapmlt.c 

$(B)(newMatrix.o):newMatrix.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/newMatrix.c $(DB)/newMatrix.c 

$(B)(norml2.o):norml2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/norml2.c $(DB)/norml2.c 

$(B)(opac2t.o):opac2t.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/opac2t.c $(DB)/opac2t.c 

$(B)(opaclmt.o):opaclmt.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/opaclmt.c $(DB)/opaclmt.c 

$(B)(planck_opacity.o):planck_opacity.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/planck_opacity.c $(DB)/planck_opacity.c 

$(B)(radfree.o):radfree.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/radfree.c $(DB)/radfree.c 

$(B)(radinit.o):radinit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/radinit.c $(DB)/radinit.c 

$(B)(rdiff.o):rdiff.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiff.c $(DB)/rdiff.c 

$(B)(rdiffbc.o):rdiffbc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffbc.c $(DB)/rdiffbc.c 

$(B)(rdiffbc2.o):rdiffbc2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffbc2.c $(DB)/rdiffbc2.c 

$(B)(rdiffbc3.o):rdiffbc3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffbc3.c $(DB)/rdiffbc3.c 

$(B)(rdiffset.o):rdiffset.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffset.c $(DB)/rdiffset.c 

$(B)(rdiffsrc.o):rdiffsrc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rdiffsrc.c $(DB)/rdiffsrc.c 

$(B)(reicouple.o):reicouple.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/reicouple.c $(DB)/reicouple.c 

$(B)(retransfer.o):retransfer.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/retransfer.c $(DB)/retransfer.c 

$(B)(rmatmult.o):rmatmult.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rmatmult.c $(DB)/rmatmult.c 

$(B)(rmatmult2.o):rmatmult2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rmatmult2.c $(DB)/rmatmult2.c 

$(B)(rmatmult3.o):rmatmult3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rmatmult3.c $(DB)/rmatmult3.c 

$(B)(rsrcbc.o):rsrcbc.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rsrcbc.c $(DB)/rsrcbc.c 

$(B)(rsrcbc2.o):rsrcbc2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rsrcbc2.c $(DB)/rsrcbc2.c 

$(B)(rsrcbc3.o):rsrcbc3.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/rsrcbc3.c $(DB)/rsrcbc3.c 

$(B)(setpz1.o):setpz1.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setpz1.c $(DB)/setpz1.c 

$(B)(setpz2.o):setpz2.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/setpz2.c $(DB)/setpz2.c 

$(B)(tblkinit.o):tblkinit.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tblkinit.c $(DB)/tblkinit.c 

$(B)(tdiff.o):tdiff.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/tdiff.c $(DB)/tdiff.c 

$(B)(teicouple.o):teicouple.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/teicouple.c $(DB)/teicouple.c 

$(B)(zstarcal.o):zstarcal.c 
	$$irs_cc $<
	@touch object_file_flag
	@ln -sf $(SRCDIR)/zstarcal.c $(DB)/zstarcal.c 

#---------------------
# lint pass one target 
#---------------------
lint:ChemPotCalc.ln ConductionCoef.ln DiffCoef.ln DivgradDriver.ln FemDivgrad3.ln \
	  FemGrad3d.ln FluxLimiter2d.ln FluxLimiter3d.ln FluxLimiterDriver.ln     \
	  GefaGedi.ln KpAnalytic.ln KrAnalytic.ln MatrixSolve.ln                  \
	  MatterConduction.ln MatterDiagonal.ln MatterWainwright.ln               \
	  RadiationMemory.ln RadiationSourceBC.ln RegionTable.ln                  \
	  SetFaceTemperature.ln bound_free.ln cblkbc.ln cblkbc2.ln cblkbc3.ln     \
	  diagonal.ln diff1g.ln divgrad2.ln divgrad3.ln divgradpert2d.ln          \
	  divgradpert3d.ln geteicouple.ln gettfzstar.ln getzabar0.ln              \
	  gtkappabnd.ln kapmlt.ln newMatrix.ln norml2.ln opac2t.ln opaclmt.ln     \
	  planck_opacity.ln radfree.ln radinit.ln rdiff.ln rdiffbc.ln rdiffbc2.ln \
	  rdiffbc3.ln rdiffset.ln rdiffsrc.ln reicouple.ln retransfer.ln          \
	  rmatmult.ln rmatmult2.ln rmatmult3.ln rsrcbc.ln rsrcbc2.ln rsrcbc3.ln   \
	  setpz1.ln setpz2.ln tblkinit.ln tdiff.ln teicouple.ln zstarcal.ln

#------------------------------
# individual lint .ln file deps
#------------------------------
ChemPotCalc.ln:ChemPotCalc.c ../../includes/irs.h ../../includes/irsreg.h         \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ChemPotCalc.c ***' >> $(LO)
	$$irs_lint ChemPotCalc.c 2>&1 | tee -a $(LO)

ConductionCoef.ln:ConductionCoef.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irsdefs.h ../../includes/irstdiff.h                      \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON ConductionCoef.c ***' >> $(LO)
	$$irs_lint ConductionCoef.c 2>&1 | tee -a $(LO)

DiffCoef.ln:DiffCoef.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irstdiff.h ../../includes/irsdefs.h                      \
	  ../../includes/DiffusionData.hh ../../includes/FunctionTimer.h          \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON DiffCoef.c ***' >> $(LO)
	$$irs_lint DiffCoef.c 2>&1 | tee -a $(LO)

DivgradDriver.ln:DivgradDriver.c ../../includes/irsdefs.h ../../includes/irs.h    \
	  ../../includes/irstdiff.h ../../includes/irsgen.h                       \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON DivgradDriver.c ***' >> $(LO)
	$$irs_lint DivgradDriver.c 2>&1 | tee -a $(LO)

FemDivgrad3.ln:FemDivgrad3.c ../../includes/irs.h ../../includes/irstdiff.h       \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FemDivgrad3.c ***' >> $(LO)
	$$irs_lint FemDivgrad3.c 2>&1 | tee -a $(LO)

FemGrad3d.ln:FemGrad3d.c ../../includes/irs.h ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FemGrad3d.c ***' >> $(LO)
	$$irs_lint FemGrad3d.c 2>&1 | tee -a $(LO)

FluxLimiter2d.ln:FluxLimiter2d.c ../../includes/irsdefs.h ../../includes/irs.h    \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FluxLimiter2d.c ***' >> $(LO)
	$$irs_lint FluxLimiter2d.c 2>&1 | tee -a $(LO)

FluxLimiter3d.ln:FluxLimiter3d.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FluxLimiter3d.c ***' >> $(LO)
	$$irs_lint FluxLimiter3d.c 2>&1 | tee -a $(LO)

FluxLimiterDriver.ln:FluxLimiterDriver.c ../../includes/irsdefs.h                 \
	  ../../includes/irs.h ../../includes/irstdiff.h ../../includes/irsgen.h  \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON FluxLimiterDriver.c ***' >> $(LO)
	$$irs_lint FluxLimiterDriver.c 2>&1 | tee -a $(LO)

GefaGedi.ln:GefaGedi.c ../../includes/irs.h ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON GefaGedi.c ***' >> $(LO)
	$$irs_lint GefaGedi.c 2>&1 | tee -a $(LO)

KpAnalytic.ln:KpAnalytic.c ../../includes/irsdefs.h ../../includes/irs.h          \
	  ../../includes/irseos.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON KpAnalytic.c ***' >> $(LO)
	$$irs_lint KpAnalytic.c 2>&1 | tee -a $(LO)

KrAnalytic.ln:KrAnalytic.c ../../includes/irsdefs.h ../../includes/irs.h          \
	  ../../includes/irseos.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON KrAnalytic.c ***' >> $(LO)
	$$irs_lint KrAnalytic.c 2>&1 | tee -a $(LO)

MatrixSolve.ln:MatrixSolve.c ../../includes/irs.h ../../includes/irssys.h         \
	  ../../includes/irscom.h ../../includes/irsdefs.h                        \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h           \
	  ../../includes/TimeStepControl.h ../../includes/pardo.h                 \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON MatrixSolve.c ***' >> $(LO)
	$$irs_lint MatrixSolve.c 2>&1 | tee -a $(LO)

MatterConduction.ln:MatterConduction.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON MatterConduction.c ***' >> $(LO)
	$$irs_lint MatterConduction.c 2>&1 | tee -a $(LO)

MatterDiagonal.ln:MatterDiagonal.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irstdiff.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/DiffusionData.h                  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h           \
	  ../../includes/irs.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON MatterDiagonal.c ***' >> $(LO)
	$$irs_lint MatterDiagonal.c 2>&1 | tee -a $(LO)

MatterWainwright.ln:MatterWainwright.c ../../includes/irs.h                       \
	  ../../includes/irsreg.h ../../includes/irsdefs.h                        \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON MatterWainwright.c ***' >> $(LO)
	$$irs_lint MatterWainwright.c 2>&1 | tee -a $(LO)

RadiationMemory.ln:RadiationMemory.c ../../includes/irsdefs.h                     \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/DiffusionData.h ../../includes/ProblemArray.h            \
	  ../../includes/RadiationData.hh ../../includes/pardo.h                  \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON RadiationMemory.c ***' >> $(LO)
	$$irs_lint RadiationMemory.c 2>&1 | tee -a $(LO)

RadiationSourceBC.ln:RadiationSourceBC.c ../../includes/irs.h                     \
	  ../../includes/irstdiff.h ../../includes/irsrgst.h                      \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/Rgst.h ../../includes/RadiationData.h                    \
	  ../../includes/Source.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON RadiationSourceBC.c ***' >> $(LO)
	$$irs_lint RadiationSourceBC.c 2>&1 | tee -a $(LO)

RegionTable.ln:RegionTable.c ../../includes/irs.h ../../includes/irsreg.h         \
	  ../../includes/irstdiff.h ../../includes/irs.h ../../includes/Domain.h  \
	  ../../includes/Region.h ../../includes/SpeciesFraction.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON RegionTable.c ***' >> $(LO)
	$$irs_lint RegionTable.c 2>&1 | tee -a $(LO)

SetFaceTemperature.ln:SetFaceTemperature.c ../../includes/irs.h                   \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON SetFaceTemperature.c ***' >> $(LO)
	$$irs_lint SetFaceTemperature.c 2>&1 | tee -a $(LO)

bound_free.ln:bound_free.c ../../includes/irs.h ../../includes/irstdiff.h         \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON bound_free.c ***' >> $(LO)
	$$irs_lint bound_free.c 2>&1 | tee -a $(LO)

cblkbc.ln:cblkbc.c ../../includes/irs.h ../../includes/irstdiff.h                 \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON cblkbc.c ***' >> $(LO)
	$$irs_lint cblkbc.c 2>&1 | tee -a $(LO)

cblkbc2.ln:cblkbc2.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON cblkbc2.c ***' >> $(LO)
	$$irs_lint cblkbc2.c 2>&1 | tee -a $(LO)

cblkbc3.ln:cblkbc3.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON cblkbc3.c ***' >> $(LO)
	$$irs_lint cblkbc3.c 2>&1 | tee -a $(LO)

diagonal.ln:diagonal.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irstdiff.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/DiffusionData.h                  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON diagonal.c ***' >> $(LO)
	$$irs_lint diagonal.c 2>&1 | tee -a $(LO)

diff1g.ln:diff1g.c ../../includes/irs.h ../../includes/irstdiff.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON diff1g.c ***' >> $(LO)
	$$irs_lint diff1g.c 2>&1 | tee -a $(LO)

divgrad2.ln:divgrad2.c ../../includes/irsdefs.h ../../includes/irs.h              \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON divgrad2.c ***' >> $(LO)
	$$irs_lint divgrad2.c 2>&1 | tee -a $(LO)

divgrad3.ln:divgrad3.c ../../includes/irsdefs.h ../../includes/irs.h              \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON divgrad3.c ***' >> $(LO)
	$$irs_lint divgrad3.c 2>&1 | tee -a $(LO)

divgradpert2d.ln:divgradpert2d.c ../../includes/irsdefs.h ../../includes/irs.h    \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON divgradpert2d.c ***' >> $(LO)
	$$irs_lint divgradpert2d.c 2>&1 | tee -a $(LO)

divgradpert3d.ln:divgradpert3d.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON divgradpert3d.c ***' >> $(LO)
	$$irs_lint divgradpert3d.c 2>&1 | tee -a $(LO)

geteicouple.ln:geteicouple.c ../../includes/irsdefs.h ../../includes/irs.h        \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON geteicouple.c ***' >> $(LO)
	$$irs_lint geteicouple.c 2>&1 | tee -a $(LO)

gettfzstar.ln:gettfzstar.c ../../includes/irs.h ../../includes/irstdiff.h         \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON gettfzstar.c ***' >> $(LO)
	$$irs_lint gettfzstar.c 2>&1 | tee -a $(LO)

getzabar0.ln:getzabar0.c ../../includes/irs.h ../../includes/irstdiff.h           \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON getzabar0.c ***' >> $(LO)
	$$irs_lint getzabar0.c 2>&1 | tee -a $(LO)

gtkappabnd.ln:gtkappabnd.c ../../includes/irs.h ../../includes/irscom.h           \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/ProblemArray.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON gtkappabnd.c ***' >> $(LO)
	$$irs_lint gtkappabnd.c 2>&1 | tee -a $(LO)

kapmlt.ln:kapmlt.c ../../includes/irs.h ../../includes/irstdiff.h                 \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON kapmlt.c ***' >> $(LO)
	$$irs_lint kapmlt.c 2>&1 | tee -a $(LO)

newMatrix.ln:newMatrix.c ../../includes/irsdefs.h ../../includes/irs.h            \
	  ../../includes/irstdiff.h ../../includes/irs.h                          \
	  ../../includes/RadiationData.h ../../includes/irs.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON newMatrix.c ***' >> $(LO)
	$$irs_lint newMatrix.c 2>&1 | tee -a $(LO)

norml2.ln:norml2.c ../../includes/irs.h ../../includes/irstdiff.h                 \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON norml2.c ***' >> $(LO)
	$$irs_lint norml2.c 2>&1 | tee -a $(LO)

opac2t.ln:opac2t.c ../../includes/irs.h ../../includes/irsreg.h                   \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON opac2t.c ***' >> $(LO)
	$$irs_lint opac2t.c 2>&1 | tee -a $(LO)

opaclmt.ln:opaclmt.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON opaclmt.c ***' >> $(LO)
	$$irs_lint opaclmt.c 2>&1 | tee -a $(LO)

planck_opacity.ln:planck_opacity.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON planck_opacity.c ***' >> $(LO)
	$$irs_lint planck_opacity.c 2>&1 | tee -a $(LO)

radfree.ln:radfree.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/ProblemArray.h ../../includes/DiffusionData.h            \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON radfree.c ***' >> $(LO)
	$$irs_lint radfree.c 2>&1 | tee -a $(LO)

radinit.ln:radinit.c ../../includes/irs.h ../../includes/irsreg.h                 \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/DiffusionData.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON radinit.c ***' >> $(LO)
	$$irs_lint radinit.c 2>&1 | tee -a $(LO)

rdiff.ln:rdiff.c ../../includes/irs.h ../../includes/irscom.h                     \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h           \
	  ../../includes/Source.h ../../includes/pardo.h ../../includes/pardo.h   \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiff.c ***' >> $(LO)
	$$irs_lint rdiff.c 2>&1 | tee -a $(LO)

rdiffbc.ln:rdiffbc.c ../../includes/irs.h ../../includes/irscom.h                 \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffbc.c ***' >> $(LO)
	$$irs_lint rdiffbc.c 2>&1 | tee -a $(LO)

rdiffbc2.ln:rdiffbc2.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffbc2.c ***' >> $(LO)
	$$irs_lint rdiffbc2.c 2>&1 | tee -a $(LO)

rdiffbc3.ln:rdiffbc3.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffbc3.c ***' >> $(LO)
	$$irs_lint rdiffbc3.c 2>&1 | tee -a $(LO)

rdiffset.ln:rdiffset.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffset.c ***' >> $(LO)
	$$irs_lint rdiffset.c 2>&1 | tee -a $(LO)

rdiffsrc.ln:rdiffsrc.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/irscom.h ../../includes/irssrc.h                         \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rdiffsrc.c ***' >> $(LO)
	$$irs_lint rdiffsrc.c 2>&1 | tee -a $(LO)

reicouple.ln:reicouple.c ../../includes/irs.h ../../includes/irstdiff.h           \
	  ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON reicouple.c ***' >> $(LO)
	$$irs_lint reicouple.c 2>&1 | tee -a $(LO)

retransfer.ln:retransfer.c ../../includes/irs.h ../../includes/irsreg.h           \
	  ../../includes/irstdiff.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/DiffusionData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON retransfer.c ***' >> $(LO)
	$$irs_lint retransfer.c 2>&1 | tee -a $(LO)

rmatmult.ln:rmatmult.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rmatmult.c ***' >> $(LO)
	$$irs_lint rmatmult.c 2>&1 | tee -a $(LO)

rmatmult2.ln:rmatmult2.c ../../includes/irs.h ../../includes/irstdiff.h           \
	  ../../includes/irscom.h ../../includes/FunctionTimer.h                  \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rmatmult2.c ***' >> $(LO)
	$$irs_lint rmatmult2.c 2>&1 | tee -a $(LO)

rmatmult3.ln:rmatmult3.c ../../includes/irs.h ../../includes/irstdiff.h           \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rmatmult3.c ***' >> $(LO)
	$$irs_lint rmatmult3.c 2>&1 | tee -a $(LO)

rsrcbc.ln:rsrcbc.c ../../includes/irs.h ../../includes/irscom.h                   \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rsrcbc.c ***' >> $(LO)
	$$irs_lint rsrcbc.c 2>&1 | tee -a $(LO)

rsrcbc2.ln:rsrcbc2.c ../../includes/irs.h ../../includes/irstdiff.h               \
	  ../../includes/irssrc.h ../../includes/DiffusionData.h                  \
	  ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rsrcbc2.c ***' >> $(LO)
	$$irs_lint rsrcbc2.c 2>&1 | tee -a $(LO)

rsrcbc3.ln:rsrcbc3.c ../../includes/irs.h ../../includes/irssrc.h                 \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON rsrcbc3.c ***' >> $(LO)
	$$irs_lint rsrcbc3.c 2>&1 | tee -a $(LO)

setpz1.ln:setpz1.c ../../includes/irs.h ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setpz1.c ***' >> $(LO)
	$$irs_lint setpz1.c 2>&1 | tee -a $(LO)

setpz2.ln:setpz2.c ../../includes/irs.h ../../includes/irstdiff.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON setpz2.c ***' >> $(LO)
	$$irs_lint setpz2.c 2>&1 | tee -a $(LO)

tblkinit.ln:tblkinit.c ../../includes/irs.h ../../includes/irstdiff.h             \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/irscom.h ../../includes/pardo.h ../../includes/pardo.h   \
	  ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tblkinit.c ***' >> $(LO)
	$$irs_lint tblkinit.c 2>&1 | tee -a $(LO)

tdiff.ln:tdiff.c ../../includes/irs.h ../../includes/irsgen.h                     \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/SpeciesFraction.h ../../includes/pardo.h                 \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON tdiff.c ***' >> $(LO)
	$$irs_lint tdiff.c 2>&1 | tee -a $(LO)

teicouple.ln:teicouple.c ../../includes/irs.h ../../includes/irsreg.h             \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON teicouple.c ***' >> $(LO)
	$$irs_lint teicouple.c 2>&1 | tee -a $(LO)

zstarcal.ln:zstarcal.c ../../includes/irs.h ../../includes/irsreg.h               \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	  @echo '  *** RUNNING $(SYNTAX_CHECKER) ON zstarcal.c ***' >> $(LO)
	$$irs_lint zstarcal.c 2>&1 | tee -a $(LO)

#------------------------------------------
# preprocess files and create .i files 
#------------------------------------------
preprocess:$(PREDIR)/ChemPotCalc.inst.i $(PREDIR)/ConductionCoef.inst.i           \
	  $(PREDIR)/DiffCoef.inst.i $(PREDIR)/DivgradDriver.inst.i                \
	  $(PREDIR)/FemDivgrad3.inst.i $(PREDIR)/FemGrad3d.inst.i                 \
	  $(PREDIR)/FluxLimiter2d.inst.i $(PREDIR)/FluxLimiter3d.inst.i           \
	  $(PREDIR)/FluxLimiterDriver.inst.i $(PREDIR)/GefaGedi.inst.i            \
	  $(PREDIR)/KpAnalytic.inst.i $(PREDIR)/KrAnalytic.inst.i                 \
	  $(PREDIR)/MatrixSolve.inst.i $(PREDIR)/MatterConduction.inst.i          \
	  $(PREDIR)/MatterDiagonal.inst.i $(PREDIR)/MatterWainwright.inst.i       \
	  $(PREDIR)/RadiationMemory.inst.i $(PREDIR)/RadiationSourceBC.inst.i     \
	  $(PREDIR)/RegionTable.inst.i $(PREDIR)/SetFaceTemperature.inst.i        \
	  $(PREDIR)/bound_free.inst.i $(PREDIR)/cblkbc.inst.i                     \
	  $(PREDIR)/cblkbc2.inst.i $(PREDIR)/cblkbc3.inst.i                       \
	  $(PREDIR)/diagonal.inst.i $(PREDIR)/diff1g.inst.i                       \
	  $(PREDIR)/divgrad2.inst.i $(PREDIR)/divgrad3.inst.i                     \
	  $(PREDIR)/divgradpert2d.inst.i $(PREDIR)/divgradpert3d.inst.i           \
	  $(PREDIR)/geteicouple.inst.i $(PREDIR)/gettfzstar.inst.i                \
	  $(PREDIR)/getzabar0.inst.i $(PREDIR)/gtkappabnd.inst.i                  \
	  $(PREDIR)/kapmlt.inst.i $(PREDIR)/newMatrix.inst.i                      \
	  $(PREDIR)/norml2.inst.i $(PREDIR)/opac2t.inst.i                         \
	  $(PREDIR)/opaclmt.inst.i $(PREDIR)/planck_opacity.inst.i                \
	  $(PREDIR)/radfree.inst.i $(PREDIR)/radinit.inst.i                       \
	  $(PREDIR)/rdiff.inst.i $(PREDIR)/rdiffbc.inst.i                         \
	  $(PREDIR)/rdiffbc2.inst.i $(PREDIR)/rdiffbc3.inst.i                     \
	  $(PREDIR)/rdiffset.inst.i $(PREDIR)/rdiffsrc.inst.i                     \
	  $(PREDIR)/reicouple.inst.i $(PREDIR)/retransfer.inst.i                  \
	  $(PREDIR)/rmatmult.inst.i $(PREDIR)/rmatmult2.inst.i                    \
	  $(PREDIR)/rmatmult3.inst.i $(PREDIR)/rsrcbc.inst.i                      \
	  $(PREDIR)/rsrcbc2.inst.i $(PREDIR)/rsrcbc3.inst.i                       \
	  $(PREDIR)/setpz1.inst.i $(PREDIR)/setpz2.inst.i                         \
	  $(PREDIR)/tblkinit.inst.i $(PREDIR)/tdiff.inst.i                        \
	  $(PREDIR)/teicouple.inst.i $(PREDIR)/zstarcal.inst.i

#---------------------------------------
# individual preprocessed .i file deps
#---------------------------------------
$(PREDIR)/ChemPotCalc.inst.i:ChemPotCalc.c ../../includes/irs.h                   \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f ChemPotCalc.i
	$$irs_pre ChemPotCalc.c >> ChemPotCalc.i
	@mv -f ChemPotCalc.i $(PREDIR)/ChemPotCalc.inst.i

$(PREDIR)/ConductionCoef.inst.i:ConductionCoef.c ../../includes/irs.h             \
	  ../../includes/irsreg.h ../../includes/irsdefs.h                        \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f ConductionCoef.i
	$$irs_pre ConductionCoef.c >> ConductionCoef.i
	@mv -f ConductionCoef.i $(PREDIR)/ConductionCoef.inst.i

$(PREDIR)/DiffCoef.inst.i:DiffCoef.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irstdiff.h ../../includes/irsdefs.h                      \
	  ../../includes/DiffusionData.hh ../../includes/FunctionTimer.h          \
	  ../../includes/RadiationData.h
	@rm -f DiffCoef.i
	$$irs_pre DiffCoef.c >> DiffCoef.i
	@mv -f DiffCoef.i $(PREDIR)/DiffCoef.inst.i

$(PREDIR)/DivgradDriver.inst.i:DivgradDriver.c ../../includes/irsdefs.h           \
	  ../../includes/irs.h ../../includes/irstdiff.h ../../includes/irsgen.h  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f DivgradDriver.i
	$$irs_pre DivgradDriver.c >> DivgradDriver.i
	@mv -f DivgradDriver.i $(PREDIR)/DivgradDriver.inst.i

$(PREDIR)/FemDivgrad3.inst.i:FemDivgrad3.c ../../includes/irs.h                   \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	@rm -f FemDivgrad3.i
	$$irs_pre FemDivgrad3.c >> FemDivgrad3.i
	@mv -f FemDivgrad3.i $(PREDIR)/FemDivgrad3.inst.i

$(PREDIR)/FemGrad3d.inst.i:FemGrad3d.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h
	@rm -f FemGrad3d.i
	$$irs_pre FemGrad3d.c >> FemGrad3d.i
	@mv -f FemGrad3d.i $(PREDIR)/FemGrad3d.inst.i

$(PREDIR)/FluxLimiter2d.inst.i:FluxLimiter2d.c ../../includes/irsdefs.h           \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/FunctionTimer.h
	@rm -f FluxLimiter2d.i
	$$irs_pre FluxLimiter2d.c >> FluxLimiter2d.i
	@mv -f FluxLimiter2d.i $(PREDIR)/FluxLimiter2d.inst.i

$(PREDIR)/FluxLimiter3d.inst.i:FluxLimiter3d.c ../../includes/irs.h               \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f FluxLimiter3d.i
	$$irs_pre FluxLimiter3d.c >> FluxLimiter3d.i
	@mv -f FluxLimiter3d.i $(PREDIR)/FluxLimiter3d.inst.i

$(PREDIR)/FluxLimiterDriver.inst.i:FluxLimiterDriver.c ../../includes/irsdefs.h   \
	  ../../includes/irs.h ../../includes/irstdiff.h ../../includes/irsgen.h  \
	  ../../includes/FunctionTimer.h
	@rm -f FluxLimiterDriver.i
	$$irs_pre FluxLimiterDriver.c >> FluxLimiterDriver.i
	@mv -f FluxLimiterDriver.i $(PREDIR)/FluxLimiterDriver.inst.i

$(PREDIR)/GefaGedi.inst.i:GefaGedi.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h
	@rm -f GefaGedi.i
	$$irs_pre GefaGedi.c >> GefaGedi.i
	@mv -f GefaGedi.i $(PREDIR)/GefaGedi.inst.i

$(PREDIR)/KpAnalytic.inst.i:KpAnalytic.c ../../includes/irsdefs.h                 \
	  ../../includes/irs.h ../../includes/irseos.h ../../includes/irstdiff.h  \
	  ../../includes/FunctionTimer.h
	@rm -f KpAnalytic.i
	$$irs_pre KpAnalytic.c >> KpAnalytic.i
	@mv -f KpAnalytic.i $(PREDIR)/KpAnalytic.inst.i

$(PREDIR)/KrAnalytic.inst.i:KrAnalytic.c ../../includes/irsdefs.h                 \
	  ../../includes/irs.h ../../includes/irseos.h ../../includes/irstdiff.h  \
	  ../../includes/FunctionTimer.h
	@rm -f KrAnalytic.i
	$$irs_pre KrAnalytic.c >> KrAnalytic.i
	@mv -f KrAnalytic.i $(PREDIR)/KrAnalytic.inst.i

$(PREDIR)/MatrixSolve.inst.i:MatrixSolve.c ../../includes/irs.h                   \
	  ../../includes/irssys.h ../../includes/irscom.h                         \
	  ../../includes/irsdefs.h ../../includes/irstdiff.h                      \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h ../../includes/TimeStepControl.h         \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h
	@rm -f MatrixSolve.i
	$$irs_pre MatrixSolve.c >> MatrixSolve.i
	@mv -f MatrixSolve.i $(PREDIR)/MatrixSolve.inst.i

$(PREDIR)/MatterConduction.inst.i:MatterConduction.c ../../includes/irs.h         \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f MatterConduction.i
	$$irs_pre MatterConduction.c >> MatterConduction.i
	@mv -f MatterConduction.i $(PREDIR)/MatterConduction.inst.i

$(PREDIR)/MatterDiagonal.inst.i:MatterDiagonal.c ../../includes/irs.h             \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/RadiationData.h ../../includes/irs.h                     \
	  ../../includes/irscom.h
	@rm -f MatterDiagonal.i
	$$irs_pre MatterDiagonal.c >> MatterDiagonal.i
	@mv -f MatterDiagonal.i $(PREDIR)/MatterDiagonal.inst.i

$(PREDIR)/MatterWainwright.inst.i:MatterWainwright.c ../../includes/irs.h         \
	  ../../includes/irsreg.h ../../includes/irsdefs.h                        \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f MatterWainwright.i
	$$irs_pre MatterWainwright.c >> MatterWainwright.i
	@mv -f MatterWainwright.i $(PREDIR)/MatterWainwright.inst.i

$(PREDIR)/RadiationMemory.inst.i:RadiationMemory.c ../../includes/irsdefs.h       \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/DiffusionData.h ../../includes/ProblemArray.h            \
	  ../../includes/RadiationData.hh ../../includes/pardo.h                  \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h
	@rm -f RadiationMemory.i
	$$irs_pre RadiationMemory.c >> RadiationMemory.i
	@mv -f RadiationMemory.i $(PREDIR)/RadiationMemory.inst.i

$(PREDIR)/RadiationSourceBC.inst.i:RadiationSourceBC.c ../../includes/irs.h       \
	  ../../includes/irstdiff.h ../../includes/irsrgst.h                      \
	  ../../includes/DiffusionData.h ../../includes/FunctionTimer.h           \
	  ../../includes/Rgst.h ../../includes/RadiationData.h                    \
	  ../../includes/Source.h
	@rm -f RadiationSourceBC.i
	$$irs_pre RadiationSourceBC.c >> RadiationSourceBC.i
	@mv -f RadiationSourceBC.i $(PREDIR)/RadiationSourceBC.inst.i

$(PREDIR)/RegionTable.inst.i:RegionTable.c ../../includes/irs.h                   \
	  ../../includes/irsreg.h ../../includes/irstdiff.h ../../includes/irs.h  \
	  ../../includes/Domain.h ../../includes/Region.h                         \
	  ../../includes/SpeciesFraction.h
	@rm -f RegionTable.i
	$$irs_pre RegionTable.c >> RegionTable.i
	@mv -f RegionTable.i $(PREDIR)/RegionTable.inst.i

$(PREDIR)/SetFaceTemperature.inst.i:SetFaceTemperature.c ../../includes/irs.h     \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f SetFaceTemperature.i
	$$irs_pre SetFaceTemperature.c >> SetFaceTemperature.i
	@mv -f SetFaceTemperature.i $(PREDIR)/SetFaceTemperature.inst.i

$(PREDIR)/bound_free.inst.i:bound_free.c ../../includes/irs.h                     \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f bound_free.i
	$$irs_pre bound_free.c >> bound_free.i
	@mv -f bound_free.i $(PREDIR)/bound_free.inst.i

$(PREDIR)/cblkbc.inst.i:cblkbc.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/RadiationData.h
	@rm -f cblkbc.i
	$$irs_pre cblkbc.c >> cblkbc.i
	@mv -f cblkbc.i $(PREDIR)/cblkbc.inst.i

$(PREDIR)/cblkbc2.inst.i:cblkbc2.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/RadiationData.h
	@rm -f cblkbc2.i
	$$irs_pre cblkbc2.c >> cblkbc2.i
	@mv -f cblkbc2.i $(PREDIR)/cblkbc2.inst.i

$(PREDIR)/cblkbc3.inst.i:cblkbc3.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/RadiationData.h
	@rm -f cblkbc3.i
	$$irs_pre cblkbc3.c >> cblkbc3.i
	@mv -f cblkbc3.i $(PREDIR)/cblkbc3.inst.i

$(PREDIR)/diagonal.inst.i:diagonal.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irstdiff.h ../../includes/irsbndry.h                     \
	  ../../includes/irscom.h ../../includes/DiffusionData.h                  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f diagonal.i
	$$irs_pre diagonal.c >> diagonal.i
	@mv -f diagonal.i $(PREDIR)/diagonal.inst.i

$(PREDIR)/diff1g.inst.i:diff1g.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f diff1g.i
	$$irs_pre diff1g.c >> diff1g.i
	@mv -f diff1g.i $(PREDIR)/diff1g.inst.i

$(PREDIR)/divgrad2.inst.i:divgrad2.c ../../includes/irsdefs.h                     \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f divgrad2.i
	$$irs_pre divgrad2.c >> divgrad2.i
	@mv -f divgrad2.i $(PREDIR)/divgrad2.inst.i

$(PREDIR)/divgrad3.inst.i:divgrad3.c ../../includes/irsdefs.h                     \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f divgrad3.i
	$$irs_pre divgrad3.c >> divgrad3.i
	@mv -f divgrad3.i $(PREDIR)/divgrad3.inst.i

$(PREDIR)/divgradpert2d.inst.i:divgradpert2d.c ../../includes/irsdefs.h           \
	  ../../includes/irs.h ../../includes/irstdiff.h                          \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f divgradpert2d.i
	$$irs_pre divgradpert2d.c >> divgradpert2d.i
	@mv -f divgradpert2d.i $(PREDIR)/divgradpert2d.inst.i

$(PREDIR)/divgradpert3d.inst.i:divgradpert3d.c ../../includes/irs.h               \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	@rm -f divgradpert3d.i
	$$irs_pre divgradpert3d.c >> divgradpert3d.i
	@mv -f divgradpert3d.i $(PREDIR)/divgradpert3d.inst.i

$(PREDIR)/geteicouple.inst.i:geteicouple.c ../../includes/irsdefs.h               \
	  ../../includes/irs.h ../../includes/irsreg.h ../../includes/irstdiff.h  \
	  ../../includes/FunctionTimer.h
	@rm -f geteicouple.i
	$$irs_pre geteicouple.c >> geteicouple.i
	@mv -f geteicouple.i $(PREDIR)/geteicouple.inst.i

$(PREDIR)/gettfzstar.inst.i:gettfzstar.c ../../includes/irs.h                     \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f gettfzstar.i
	$$irs_pre gettfzstar.c >> gettfzstar.i
	@mv -f gettfzstar.i $(PREDIR)/gettfzstar.inst.i

$(PREDIR)/getzabar0.inst.i:getzabar0.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f getzabar0.i
	$$irs_pre getzabar0.c >> getzabar0.i
	@mv -f getzabar0.i $(PREDIR)/getzabar0.inst.i

$(PREDIR)/gtkappabnd.inst.i:gtkappabnd.c ../../includes/irs.h                     \
	  ../../includes/irscom.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h ../../includes/ProblemArray.h
	@rm -f gtkappabnd.i
	$$irs_pre gtkappabnd.c >> gtkappabnd.i
	@mv -f gtkappabnd.i $(PREDIR)/gtkappabnd.inst.i

$(PREDIR)/kapmlt.inst.i:kapmlt.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h
	@rm -f kapmlt.i
	$$irs_pre kapmlt.c >> kapmlt.i
	@mv -f kapmlt.i $(PREDIR)/kapmlt.inst.i

$(PREDIR)/newMatrix.inst.i:newMatrix.c ../../includes/irsdefs.h                   \
	  ../../includes/irs.h ../../includes/irstdiff.h ../../includes/irs.h     \
	  ../../includes/RadiationData.h ../../includes/irs.h
	@rm -f newMatrix.i
	$$irs_pre newMatrix.c >> newMatrix.i
	@mv -f newMatrix.i $(PREDIR)/newMatrix.inst.i

$(PREDIR)/norml2.inst.i:norml2.c ../../includes/irs.h ../../includes/irstdiff.h   \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h
	@rm -f norml2.i
	$$irs_pre norml2.c >> norml2.i
	@mv -f norml2.i $(PREDIR)/norml2.inst.i

$(PREDIR)/opac2t.inst.i:opac2t.c ../../includes/irs.h ../../includes/irsreg.h     \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f opac2t.i
	$$irs_pre opac2t.c >> opac2t.i
	@mv -f opac2t.i $(PREDIR)/opac2t.inst.i

$(PREDIR)/opaclmt.inst.i:opaclmt.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/FunctionTimer.h
	@rm -f opaclmt.i
	$$irs_pre opaclmt.c >> opaclmt.i
	@mv -f opaclmt.i $(PREDIR)/opaclmt.inst.i

$(PREDIR)/planck_opacity.inst.i:planck_opacity.c ../../includes/irs.h             \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f planck_opacity.i
	$$irs_pre planck_opacity.c >> planck_opacity.i
	@mv -f planck_opacity.i $(PREDIR)/planck_opacity.inst.i

$(PREDIR)/radfree.inst.i:radfree.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/ProblemArray.h ../../includes/DiffusionData.h            \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f radfree.i
	$$irs_pre radfree.c >> radfree.i
	@mv -f radfree.i $(PREDIR)/radfree.inst.i

$(PREDIR)/radinit.inst.i:radinit.c ../../includes/irs.h ../../includes/irsreg.h   \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/DiffusionData.h ../../includes/pardo.h                   \
	  ../../includes/pardo.h
	@rm -f radinit.i
	$$irs_pre radinit.c >> radinit.i
	@mv -f radinit.i $(PREDIR)/radinit.inst.i

$(PREDIR)/rdiff.inst.i:rdiff.c ../../includes/irs.h ../../includes/irscom.h       \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h           \
	  ../../includes/Source.h ../../includes/pardo.h ../../includes/pardo.h   \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f rdiff.i
	$$irs_pre rdiff.c >> rdiff.i
	@mv -f rdiff.i $(PREDIR)/rdiff.inst.i

$(PREDIR)/rdiffbc.inst.i:rdiffbc.c ../../includes/irs.h ../../includes/irscom.h   \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rdiffbc.i
	$$irs_pre rdiffbc.c >> rdiffbc.i
	@mv -f rdiffbc.i $(PREDIR)/rdiffbc.inst.i

$(PREDIR)/rdiffbc2.inst.i:rdiffbc2.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rdiffbc2.i
	$$irs_pre rdiffbc2.c >> rdiffbc2.i
	@mv -f rdiffbc2.i $(PREDIR)/rdiffbc2.inst.i

$(PREDIR)/rdiffbc3.inst.i:rdiffbc3.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rdiffbc3.i
	$$irs_pre rdiffbc3.c >> rdiffbc3.i
	@mv -f rdiffbc3.i $(PREDIR)/rdiffbc3.inst.i

$(PREDIR)/rdiffset.inst.i:rdiffset.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	@rm -f rdiffset.i
	$$irs_pre rdiffset.c >> rdiffset.i
	@mv -f rdiffset.i $(PREDIR)/rdiffset.inst.i

$(PREDIR)/rdiffsrc.inst.i:rdiffsrc.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/irssrc.h ../../includes/DiffusionData.h                  \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rdiffsrc.i
	$$irs_pre rdiffsrc.c >> rdiffsrc.i
	@mv -f rdiffsrc.i $(PREDIR)/rdiffsrc.inst.i

$(PREDIR)/reicouple.inst.i:reicouple.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f reicouple.i
	$$irs_pre reicouple.c >> reicouple.i
	@mv -f reicouple.i $(PREDIR)/reicouple.inst.i

$(PREDIR)/retransfer.inst.i:retransfer.c ../../includes/irs.h                     \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/FunctionTimer.h ../../includes/DiffusionData.h
	@rm -f retransfer.i
	$$irs_pre retransfer.c >> retransfer.i
	@mv -f retransfer.i $(PREDIR)/retransfer.inst.i

$(PREDIR)/rmatmult.inst.i:rmatmult.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rmatmult.i
	$$irs_pre rmatmult.c >> rmatmult.i
	@mv -f rmatmult.i $(PREDIR)/rmatmult.inst.i

$(PREDIR)/rmatmult2.inst.i:rmatmult2.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/irscom.h                       \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rmatmult2.i
	$$irs_pre rmatmult2.c >> rmatmult2.i
	@mv -f rmatmult2.i $(PREDIR)/rmatmult2.inst.i

$(PREDIR)/rmatmult3.inst.i:rmatmult3.c ../../includes/irs.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/RadiationData.h
	@rm -f rmatmult3.i
	$$irs_pre rmatmult3.c >> rmatmult3.i
	@mv -f rmatmult3.i $(PREDIR)/rmatmult3.inst.i

$(PREDIR)/rsrcbc.inst.i:rsrcbc.c ../../includes/irs.h ../../includes/irscom.h     \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rsrcbc.i
	$$irs_pre rsrcbc.c >> rsrcbc.i
	@mv -f rsrcbc.i $(PREDIR)/rsrcbc.inst.i

$(PREDIR)/rsrcbc2.inst.i:rsrcbc2.c ../../includes/irs.h ../../includes/irstdiff.h \
	  ../../includes/irssrc.h ../../includes/DiffusionData.h                  \
	  ../../includes/RadiationData.h
	@rm -f rsrcbc2.i
	$$irs_pre rsrcbc2.c >> rsrcbc2.i
	@mv -f rsrcbc2.i $(PREDIR)/rsrcbc2.inst.i

$(PREDIR)/rsrcbc3.inst.i:rsrcbc3.c ../../includes/irs.h ../../includes/irssrc.h   \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/RadiationData.h
	@rm -f rsrcbc3.i
	$$irs_pre rsrcbc3.c >> rsrcbc3.i
	@mv -f rsrcbc3.i $(PREDIR)/rsrcbc3.inst.i

$(PREDIR)/setpz1.inst.i:setpz1.c ../../includes/irs.h ../../includes/irstdiff.h
	@rm -f setpz1.i
	$$irs_pre setpz1.c >> setpz1.i
	@mv -f setpz1.i $(PREDIR)/setpz1.inst.i

$(PREDIR)/setpz2.inst.i:setpz2.c ../../includes/irs.h ../../includes/irstdiff.h
	@rm -f setpz2.i
	$$irs_pre setpz2.c >> setpz2.i
	@mv -f setpz2.i $(PREDIR)/setpz2.inst.i

$(PREDIR)/tblkinit.inst.i:tblkinit.c ../../includes/irs.h                         \
	  ../../includes/irstdiff.h ../../includes/DiffusionData.h                \
	  ../../includes/FunctionTimer.h ../../includes/irscom.h                  \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f tblkinit.i
	$$irs_pre tblkinit.c >> tblkinit.i
	@mv -f tblkinit.i $(PREDIR)/tblkinit.inst.i

$(PREDIR)/tdiff.inst.i:tdiff.c ../../includes/irs.h ../../includes/irsgen.h       \
	  ../../includes/irsbndry.h ../../includes/irscom.h                       \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h                \
	  ../../includes/SpeciesFraction.h ../../includes/pardo.h                 \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h    \
	  ../../includes/pardo.h ../../includes/pardo.h ../../includes/pardo.h
	@rm -f tdiff.i
	$$irs_pre tdiff.c >> tdiff.i
	@mv -f tdiff.i $(PREDIR)/tdiff.inst.i

$(PREDIR)/teicouple.inst.i:teicouple.c ../../includes/irs.h                       \
	  ../../includes/irsreg.h ../../includes/irstdiff.h                       \
	  ../../includes/FunctionTimer.h
	@rm -f teicouple.i
	$$irs_pre teicouple.c >> teicouple.i
	@mv -f teicouple.i $(PREDIR)/teicouple.inst.i

$(PREDIR)/zstarcal.inst.i:zstarcal.c ../../includes/irs.h ../../includes/irsreg.h \
	  ../../includes/irstdiff.h ../../includes/FunctionTimer.h
	@rm -f zstarcal.i
	$$irs_pre zstarcal.c >> zstarcal.i
	@mv -f zstarcal.i $(PREDIR)/zstarcal.inst.i

#-----------------------------------------------------------
# post-process files and create library from .i files 
#-----------------------------------------------------------
postprocess:libtdiff_inst

libtdiff_inst:$(BI)(ChemPotCalc.inst.o) $(BI)(ConductionCoef.inst.o)              \
	  $(BI)(DiffCoef.inst.o) $(BI)(DivgradDriver.inst.o)                      \
	  $(BI)(FemDivgrad3.inst.o) $(BI)(FemGrad3d.inst.o)                       \
	  $(BI)(FluxLimiter2d.inst.o) $(BI)(FluxLimiter3d.inst.o)                 \
	  $(BI)(FluxLimiterDriver.inst.o) $(BI)(GefaGedi.inst.o)                  \
	  $(BI)(KpAnalytic.inst.o) $(BI)(KrAnalytic.inst.o)                       \
	  $(BI)(MatrixSolve.inst.o) $(BI)(MatterConduction.inst.o)                \
	  $(BI)(MatterDiagonal.inst.o) $(BI)(MatterWainwright.inst.o)             \
	  $(BI)(RadiationMemory.inst.o) $(BI)(RadiationSourceBC.inst.o)           \
	  $(BI)(RegionTable.inst.o) $(BI)(SetFaceTemperature.inst.o)              \
	  $(BI)(bound_free.inst.o) $(BI)(cblkbc.inst.o) $(BI)(cblkbc2.inst.o)     \
	  $(BI)(cblkbc3.inst.o) $(BI)(diagonal.inst.o) $(BI)(diff1g.inst.o)       \
	  $(BI)(divgrad2.inst.o) $(BI)(divgrad3.inst.o)                           \
	  $(BI)(divgradpert2d.inst.o) $(BI)(divgradpert3d.inst.o)                 \
	  $(BI)(geteicouple.inst.o) $(BI)(gettfzstar.inst.o)                      \
	  $(BI)(getzabar0.inst.o) $(BI)(gtkappabnd.inst.o) $(BI)(kapmlt.inst.o)   \
	  $(BI)(newMatrix.inst.o) $(BI)(norml2.inst.o) $(BI)(opac2t.inst.o)       \
	  $(BI)(opaclmt.inst.o) $(BI)(planck_opacity.inst.o)                      \
	  $(BI)(radfree.inst.o) $(BI)(radinit.inst.o) $(BI)(rdiff.inst.o)         \
	  $(BI)(rdiffbc.inst.o) $(BI)(rdiffbc2.inst.o) $(BI)(rdiffbc3.inst.o)     \
	  $(BI)(rdiffset.inst.o) $(BI)(rdiffsrc.inst.o) $(BI)(reicouple.inst.o)   \
	  $(BI)(retransfer.inst.o) $(BI)(rmatmult.inst.o) $(BI)(rmatmult2.inst.o) \
	  $(BI)(rmatmult3.inst.o) $(BI)(rsrcbc.inst.o) $(BI)(rsrcbc2.inst.o)      \
	  $(BI)(rsrcbc3.inst.o) $(BI)(setpz1.inst.o) $(BI)(setpz2.inst.o)         \
	  $(BI)(tblkinit.inst.o) $(BI)(tdiff.inst.o) $(BI)(teicouple.inst.o)      \
	  $(BI)(zstarcal.inst.o)
	  @if test -f object_file_flag; then  \
		(echo $$irs_ar ar $(BI) *.o; \
		$$irs_ar $(BI) *.o; \
		rm *.o object_file_flag; \
		echo ln -sf libtdiff_inst.a $(B); \
		ln -sf libtdiff_inst.a $(B)); \
	  fi
	  @echo 'libtdiff_inst library current'


#-------------------------------------------------------------------------------
# individual rules to compile .i files into .o files within instrumented library
#-------------------------------------------------------------------------------
$(BI)(ChemPotCalc.inst.o):$(INSTDIR)/ChemPotCalc.inst.i
	$$irs_post $(INSTDIR)/ChemPotCalc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ChemPotCalc.inst.i $(DB)/ChemPotCalc.c 

$(BI)(ConductionCoef.inst.o):$(INSTDIR)/ConductionCoef.inst.i
	$$irs_post $(INSTDIR)/ConductionCoef.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/ConductionCoef.inst.i $(DB)/ConductionCoef.c 

$(BI)(DiffCoef.inst.o):$(INSTDIR)/DiffCoef.inst.i
	$$irs_post $(INSTDIR)/DiffCoef.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/DiffCoef.inst.i $(DB)/DiffCoef.c 

$(BI)(DivgradDriver.inst.o):$(INSTDIR)/DivgradDriver.inst.i
	$$irs_post $(INSTDIR)/DivgradDriver.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/DivgradDriver.inst.i $(DB)/DivgradDriver.c 

$(BI)(FemDivgrad3.inst.o):$(INSTDIR)/FemDivgrad3.inst.i
	$$irs_post $(INSTDIR)/FemDivgrad3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FemDivgrad3.inst.i $(DB)/FemDivgrad3.c 

$(BI)(FemGrad3d.inst.o):$(INSTDIR)/FemGrad3d.inst.i
	$$irs_post $(INSTDIR)/FemGrad3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FemGrad3d.inst.i $(DB)/FemGrad3d.c 

$(BI)(FluxLimiter2d.inst.o):$(INSTDIR)/FluxLimiter2d.inst.i
	$$irs_post $(INSTDIR)/FluxLimiter2d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FluxLimiter2d.inst.i $(DB)/FluxLimiter2d.c 

$(BI)(FluxLimiter3d.inst.o):$(INSTDIR)/FluxLimiter3d.inst.i
	$$irs_post $(INSTDIR)/FluxLimiter3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FluxLimiter3d.inst.i $(DB)/FluxLimiter3d.c 

$(BI)(FluxLimiterDriver.inst.o):$(INSTDIR)/FluxLimiterDriver.inst.i
	$$irs_post $(INSTDIR)/FluxLimiterDriver.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/FluxLimiterDriver.inst.i $(DB)/FluxLimiterDriver.c 

$(BI)(GefaGedi.inst.o):$(INSTDIR)/GefaGedi.inst.i
	$$irs_post $(INSTDIR)/GefaGedi.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/GefaGedi.inst.i $(DB)/GefaGedi.c 

$(BI)(KpAnalytic.inst.o):$(INSTDIR)/KpAnalytic.inst.i
	$$irs_post $(INSTDIR)/KpAnalytic.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/KpAnalytic.inst.i $(DB)/KpAnalytic.c 

$(BI)(KrAnalytic.inst.o):$(INSTDIR)/KrAnalytic.inst.i
	$$irs_post $(INSTDIR)/KrAnalytic.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/KrAnalytic.inst.i $(DB)/KrAnalytic.c 

$(BI)(MatrixSolve.inst.o):$(INSTDIR)/MatrixSolve.inst.i
	$$irs_post $(INSTDIR)/MatrixSolve.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/MatrixSolve.inst.i $(DB)/MatrixSolve.c 

$(BI)(MatterConduction.inst.o):$(INSTDIR)/MatterConduction.inst.i
	$$irs_post $(INSTDIR)/MatterConduction.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/MatterConduction.inst.i $(DB)/MatterConduction.c 

$(BI)(MatterDiagonal.inst.o):$(INSTDIR)/MatterDiagonal.inst.i
	$$irs_post $(INSTDIR)/MatterDiagonal.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/MatterDiagonal.inst.i $(DB)/MatterDiagonal.c 

$(BI)(MatterWainwright.inst.o):$(INSTDIR)/MatterWainwright.inst.i
	$$irs_post $(INSTDIR)/MatterWainwright.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/MatterWainwright.inst.i $(DB)/MatterWainwright.c 

$(BI)(RadiationMemory.inst.o):$(INSTDIR)/RadiationMemory.inst.i
	$$irs_post $(INSTDIR)/RadiationMemory.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/RadiationMemory.inst.i $(DB)/RadiationMemory.c 

$(BI)(RadiationSourceBC.inst.o):$(INSTDIR)/RadiationSourceBC.inst.i
	$$irs_post $(INSTDIR)/RadiationSourceBC.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/RadiationSourceBC.inst.i $(DB)/RadiationSourceBC.c 

$(BI)(RegionTable.inst.o):$(INSTDIR)/RegionTable.inst.i
	$$irs_post $(INSTDIR)/RegionTable.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/RegionTable.inst.i $(DB)/RegionTable.c 

$(BI)(SetFaceTemperature.inst.o):$(INSTDIR)/SetFaceTemperature.inst.i
	$$irs_post $(INSTDIR)/SetFaceTemperature.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/SetFaceTemperature.inst.i $(DB)/SetFaceTemperature.c 

$(BI)(bound_free.inst.o):$(INSTDIR)/bound_free.inst.i
	$$irs_post $(INSTDIR)/bound_free.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/bound_free.inst.i $(DB)/bound_free.c 

$(BI)(cblkbc.inst.o):$(INSTDIR)/cblkbc.inst.i
	$$irs_post $(INSTDIR)/cblkbc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/cblkbc.inst.i $(DB)/cblkbc.c 

$(BI)(cblkbc2.inst.o):$(INSTDIR)/cblkbc2.inst.i
	$$irs_post $(INSTDIR)/cblkbc2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/cblkbc2.inst.i $(DB)/cblkbc2.c 

$(BI)(cblkbc3.inst.o):$(INSTDIR)/cblkbc3.inst.i
	$$irs_post $(INSTDIR)/cblkbc3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/cblkbc3.inst.i $(DB)/cblkbc3.c 

$(BI)(diagonal.inst.o):$(INSTDIR)/diagonal.inst.i
	$$irs_post $(INSTDIR)/diagonal.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/diagonal.inst.i $(DB)/diagonal.c 

$(BI)(diff1g.inst.o):$(INSTDIR)/diff1g.inst.i
	$$irs_post $(INSTDIR)/diff1g.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/diff1g.inst.i $(DB)/diff1g.c 

$(BI)(divgrad2.inst.o):$(INSTDIR)/divgrad2.inst.i
	$$irs_post $(INSTDIR)/divgrad2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/divgrad2.inst.i $(DB)/divgrad2.c 

$(BI)(divgrad3.inst.o):$(INSTDIR)/divgrad3.inst.i
	$$irs_post $(INSTDIR)/divgrad3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/divgrad3.inst.i $(DB)/divgrad3.c 

$(BI)(divgradpert2d.inst.o):$(INSTDIR)/divgradpert2d.inst.i
	$$irs_post $(INSTDIR)/divgradpert2d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/divgradpert2d.inst.i $(DB)/divgradpert2d.c 

$(BI)(divgradpert3d.inst.o):$(INSTDIR)/divgradpert3d.inst.i
	$$irs_post $(INSTDIR)/divgradpert3d.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/divgradpert3d.inst.i $(DB)/divgradpert3d.c 

$(BI)(geteicouple.inst.o):$(INSTDIR)/geteicouple.inst.i
	$$irs_post $(INSTDIR)/geteicouple.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/geteicouple.inst.i $(DB)/geteicouple.c 

$(BI)(gettfzstar.inst.o):$(INSTDIR)/gettfzstar.inst.i
	$$irs_post $(INSTDIR)/gettfzstar.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/gettfzstar.inst.i $(DB)/gettfzstar.c 

$(BI)(getzabar0.inst.o):$(INSTDIR)/getzabar0.inst.i
	$$irs_post $(INSTDIR)/getzabar0.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/getzabar0.inst.i $(DB)/getzabar0.c 

$(BI)(gtkappabnd.inst.o):$(INSTDIR)/gtkappabnd.inst.i
	$$irs_post $(INSTDIR)/gtkappabnd.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/gtkappabnd.inst.i $(DB)/gtkappabnd.c 

$(BI)(kapmlt.inst.o):$(INSTDIR)/kapmlt.inst.i
	$$irs_post $(INSTDIR)/kapmlt.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/kapmlt.inst.i $(DB)/kapmlt.c 

$(BI)(newMatrix.inst.o):$(INSTDIR)/newMatrix.inst.i
	$$irs_post $(INSTDIR)/newMatrix.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/newMatrix.inst.i $(DB)/newMatrix.c 

$(BI)(norml2.inst.o):$(INSTDIR)/norml2.inst.i
	$$irs_post $(INSTDIR)/norml2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/norml2.inst.i $(DB)/norml2.c 

$(BI)(opac2t.inst.o):$(INSTDIR)/opac2t.inst.i
	$$irs_post $(INSTDIR)/opac2t.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/opac2t.inst.i $(DB)/opac2t.c 

$(BI)(opaclmt.inst.o):$(INSTDIR)/opaclmt.inst.i
	$$irs_post $(INSTDIR)/opaclmt.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/opaclmt.inst.i $(DB)/opaclmt.c 

$(BI)(planck_opacity.inst.o):$(INSTDIR)/planck_opacity.inst.i
	$$irs_post $(INSTDIR)/planck_opacity.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/planck_opacity.inst.i $(DB)/planck_opacity.c 

$(BI)(radfree.inst.o):$(INSTDIR)/radfree.inst.i
	$$irs_post $(INSTDIR)/radfree.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/radfree.inst.i $(DB)/radfree.c 

$(BI)(radinit.inst.o):$(INSTDIR)/radinit.inst.i
	$$irs_post $(INSTDIR)/radinit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/radinit.inst.i $(DB)/radinit.c 

$(BI)(rdiff.inst.o):$(INSTDIR)/rdiff.inst.i
	$$irs_post $(INSTDIR)/rdiff.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiff.inst.i $(DB)/rdiff.c 

$(BI)(rdiffbc.inst.o):$(INSTDIR)/rdiffbc.inst.i
	$$irs_post $(INSTDIR)/rdiffbc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffbc.inst.i $(DB)/rdiffbc.c 

$(BI)(rdiffbc2.inst.o):$(INSTDIR)/rdiffbc2.inst.i
	$$irs_post $(INSTDIR)/rdiffbc2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffbc2.inst.i $(DB)/rdiffbc2.c 

$(BI)(rdiffbc3.inst.o):$(INSTDIR)/rdiffbc3.inst.i
	$$irs_post $(INSTDIR)/rdiffbc3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffbc3.inst.i $(DB)/rdiffbc3.c 

$(BI)(rdiffset.inst.o):$(INSTDIR)/rdiffset.inst.i
	$$irs_post $(INSTDIR)/rdiffset.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffset.inst.i $(DB)/rdiffset.c 

$(BI)(rdiffsrc.inst.o):$(INSTDIR)/rdiffsrc.inst.i
	$$irs_post $(INSTDIR)/rdiffsrc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rdiffsrc.inst.i $(DB)/rdiffsrc.c 

$(BI)(reicouple.inst.o):$(INSTDIR)/reicouple.inst.i
	$$irs_post $(INSTDIR)/reicouple.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/reicouple.inst.i $(DB)/reicouple.c 

$(BI)(retransfer.inst.o):$(INSTDIR)/retransfer.inst.i
	$$irs_post $(INSTDIR)/retransfer.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/retransfer.inst.i $(DB)/retransfer.c 

$(BI)(rmatmult.inst.o):$(INSTDIR)/rmatmult.inst.i
	$$irs_post $(INSTDIR)/rmatmult.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rmatmult.inst.i $(DB)/rmatmult.c 

$(BI)(rmatmult2.inst.o):$(INSTDIR)/rmatmult2.inst.i
	$$irs_post $(INSTDIR)/rmatmult2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rmatmult2.inst.i $(DB)/rmatmult2.c 

$(BI)(rmatmult3.inst.o):$(INSTDIR)/rmatmult3.inst.i
	$$irs_post $(INSTDIR)/rmatmult3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rmatmult3.inst.i $(DB)/rmatmult3.c 

$(BI)(rsrcbc.inst.o):$(INSTDIR)/rsrcbc.inst.i
	$$irs_post $(INSTDIR)/rsrcbc.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rsrcbc.inst.i $(DB)/rsrcbc.c 

$(BI)(rsrcbc2.inst.o):$(INSTDIR)/rsrcbc2.inst.i
	$$irs_post $(INSTDIR)/rsrcbc2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rsrcbc2.inst.i $(DB)/rsrcbc2.c 

$(BI)(rsrcbc3.inst.o):$(INSTDIR)/rsrcbc3.inst.i
	$$irs_post $(INSTDIR)/rsrcbc3.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/rsrcbc3.inst.i $(DB)/rsrcbc3.c 

$(BI)(setpz1.inst.o):$(INSTDIR)/setpz1.inst.i
	$$irs_post $(INSTDIR)/setpz1.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setpz1.inst.i $(DB)/setpz1.c 

$(BI)(setpz2.inst.o):$(INSTDIR)/setpz2.inst.i
	$$irs_post $(INSTDIR)/setpz2.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/setpz2.inst.i $(DB)/setpz2.c 

$(BI)(tblkinit.inst.o):$(INSTDIR)/tblkinit.inst.i
	$$irs_post $(INSTDIR)/tblkinit.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tblkinit.inst.i $(DB)/tblkinit.c 

$(BI)(tdiff.inst.o):$(INSTDIR)/tdiff.inst.i
	$$irs_post $(INSTDIR)/tdiff.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/tdiff.inst.i $(DB)/tdiff.c 

$(BI)(teicouple.inst.o):$(INSTDIR)/teicouple.inst.i
	$$irs_post $(INSTDIR)/teicouple.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/teicouple.inst.i $(DB)/teicouple.c 

$(BI)(zstarcal.inst.o):$(INSTDIR)/zstarcal.inst.i
	$$irs_post $(INSTDIR)/zstarcal.inst.i
	@touch object_file_flag
	@ln -sf $(INSTDIR_D)/zstarcal.inst.i $(DB)/zstarcal.c 

DEP_SRCS = \
	ChemPotCalc.c ConductionCoef.c DiffCoef.c DivgradDriver.c FemDivgrad3.c  \
	FemGrad3d.c FluxLimiter2d.c FluxLimiter3d.c FluxLimiterDriver.c GefaGedi.c  \
	KpAnalytic.c KrAnalytic.c MatrixSolve.c MatterConduction.c MatterDiagonal.c  \
	MatterWainwright.c RadiationMemory.c RadiationSourceBC.c RegionTable.c  \
	SetFaceTemperature.c bound_free.c cblkbc.c cblkbc2.c cblkbc3.c diagonal.c  \
	diff1g.c divgrad2.c divgrad3.c divgradpert2d.c divgradpert3d.c geteicouple.c  \
	gettfzstar.c getzabar0.c gtkappabnd.c kapmlt.c newMatrix.c norml2.c opac2t.c  \
	opaclmt.c planck_opacity.c radfree.c radinit.c rdiff.c rdiffbc.c rdiffbc2.c  \
	rdiffbc3.c rdiffset.c rdiffsrc.c reicouple.c retransfer.c rmatmult.c rmatmult2.c  \
	rmatmult3.c rsrcbc.c rsrcbc2.c rsrcbc3.c setpz1.c setpz2.c tblkinit.c  \
	tdiff.c teicouple.c zstarcal.c  

depend:
	@cp -f Makefile.tdiff Makefile
	makedepend -- $(DEPFLAGS) -- $(DEP_SRCS)
	irs_fixdepend Makefile

# DO NOT DELETE

$(B)(ChemPotCalc.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(ChemPotCalc.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(ChemPotCalc.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(ChemPotCalc.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(ChemPotCalc.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(ChemPotCalc.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(ChemPotCalc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(ChemPotCalc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(ChemPotCalc.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(ChemPotCalc.o): /usr/include/time.h /usr/include/endian.h
$(B)(ChemPotCalc.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(ChemPotCalc.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(ChemPotCalc.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(ChemPotCalc.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(ChemPotCalc.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(ChemPotCalc.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(ChemPotCalc.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(ChemPotCalc.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(ChemPotCalc.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(ChemPotCalc.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(ChemPotCalc.o): /usr/include/ctype.h /usr/include/math.h
$(B)(ChemPotCalc.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(ChemPotCalc.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(ChemPotCalc.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(ChemPotCalc.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(ChemPotCalc.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(ChemPotCalc.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(ChemPotCalc.o): ../../includes/FunctionTimer.h
$(B)(ConductionCoef.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(ConductionCoef.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(ConductionCoef.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(ConductionCoef.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(ConductionCoef.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(ConductionCoef.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(ConductionCoef.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(ConductionCoef.o): /usr/include/bits/stdio_lim.h
$(B)(ConductionCoef.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(ConductionCoef.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(ConductionCoef.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(ConductionCoef.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(ConductionCoef.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(ConductionCoef.o): /usr/include/sys/sysmacros.h
$(B)(ConductionCoef.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(ConductionCoef.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(ConductionCoef.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(ConductionCoef.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(ConductionCoef.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(ConductionCoef.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(ConductionCoef.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(ConductionCoef.o): /usr/include/ctype.h /usr/include/math.h
$(B)(ConductionCoef.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(ConductionCoef.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(ConductionCoef.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(ConductionCoef.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(ConductionCoef.o): ../../includes/RadiationData.h
$(B)(ConductionCoef.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(ConductionCoef.o): ../../includes/DiffusionData.h
$(B)(ConductionCoef.o): ../../includes/FunctionTimer.h
$(B)(DiffCoef.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(DiffCoef.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(DiffCoef.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(DiffCoef.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(DiffCoef.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(DiffCoef.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(DiffCoef.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(DiffCoef.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(DiffCoef.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(DiffCoef.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(DiffCoef.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(DiffCoef.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(DiffCoef.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(DiffCoef.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(DiffCoef.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(DiffCoef.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(DiffCoef.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(DiffCoef.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(DiffCoef.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(DiffCoef.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(DiffCoef.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(DiffCoef.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(DiffCoef.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(DiffCoef.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(DiffCoef.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(DiffCoef.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(DiffCoef.o): ../../includes/FunctionTimer.h
$(B)(DivgradDriver.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(DivgradDriver.o): /usr/include/stdio.h /usr/include/features.h
$(B)(DivgradDriver.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(DivgradDriver.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(DivgradDriver.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(DivgradDriver.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(DivgradDriver.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(DivgradDriver.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(DivgradDriver.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(DivgradDriver.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(DivgradDriver.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(DivgradDriver.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(DivgradDriver.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(DivgradDriver.o): /usr/include/sys/sysmacros.h
$(B)(DivgradDriver.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(DivgradDriver.o): /usr/include/sys/times.h ../../includes/irsctl.h
$(B)(DivgradDriver.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(DivgradDriver.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(DivgradDriver.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(DivgradDriver.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(DivgradDriver.o): ../../includes/mach.h /usr/include/ctype.h
$(B)(DivgradDriver.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(DivgradDriver.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(DivgradDriver.o): /usr/include/string.h /usr/include/malloc.h
$(B)(DivgradDriver.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(DivgradDriver.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(DivgradDriver.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(DivgradDriver.o): ../../includes/irsgen.h ../../includes/NodeList.h
$(B)(DivgradDriver.o): ../../includes/Extents.h ../../includes/FunctionTimer.h
$(B)(FemDivgrad3.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(FemDivgrad3.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(FemDivgrad3.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(FemDivgrad3.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(FemDivgrad3.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FemDivgrad3.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FemDivgrad3.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FemDivgrad3.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(FemDivgrad3.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(FemDivgrad3.o): /usr/include/time.h /usr/include/endian.h
$(B)(FemDivgrad3.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(FemDivgrad3.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(FemDivgrad3.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(FemDivgrad3.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FemDivgrad3.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FemDivgrad3.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(FemDivgrad3.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(FemDivgrad3.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(FemDivgrad3.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(FemDivgrad3.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(FemDivgrad3.o): /usr/include/ctype.h /usr/include/math.h
$(B)(FemDivgrad3.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(FemDivgrad3.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(FemDivgrad3.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(FemDivgrad3.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(FemDivgrad3.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(FemDivgrad3.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(FemGrad3d.o): /usr/include/math.h /usr/include/features.h
$(B)(FemGrad3d.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FemGrad3d.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FemGrad3d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(FemGrad3d.o): /usr/include/bits/mathcalls.h ../../includes/irs.h
$(B)(FemGrad3d.o): /usr/include/stdio.h /usr/include/bits/types.h
$(B)(FemGrad3d.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FemGrad3d.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FemGrad3d.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FemGrad3d.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(FemGrad3d.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(FemGrad3d.o): /usr/include/time.h /usr/include/endian.h
$(B)(FemGrad3d.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(FemGrad3d.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(FemGrad3d.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(FemGrad3d.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FemGrad3d.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FemGrad3d.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(FemGrad3d.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(FemGrad3d.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(FemGrad3d.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(FemGrad3d.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(FemGrad3d.o): /usr/include/ctype.h /usr/include/string.h /usr/include/malloc.h
$(B)(FemGrad3d.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(FemGrad3d.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(FemGrad3d.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(FluxLimiter2d.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(FluxLimiter2d.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FluxLimiter2d.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FluxLimiter2d.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FluxLimiter2d.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(FluxLimiter2d.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(FluxLimiter2d.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(FluxLimiter2d.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(FluxLimiter2d.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FluxLimiter2d.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FluxLimiter2d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FluxLimiter2d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FluxLimiter2d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FluxLimiter2d.o): /usr/include/sys/sysmacros.h
$(B)(FluxLimiter2d.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FluxLimiter2d.o): /usr/include/sys/times.h ../../includes/irsctl.h
$(B)(FluxLimiter2d.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(FluxLimiter2d.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(FluxLimiter2d.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(FluxLimiter2d.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(FluxLimiter2d.o): ../../includes/mach.h /usr/include/ctype.h
$(B)(FluxLimiter2d.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(FluxLimiter2d.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(FluxLimiter2d.o): /usr/include/string.h /usr/include/malloc.h
$(B)(FluxLimiter2d.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(FluxLimiter2d.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(FluxLimiter2d.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(FluxLimiter2d.o): ../../includes/FunctionTimer.h
$(B)(FluxLimiter3d.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(FluxLimiter3d.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(FluxLimiter3d.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(FluxLimiter3d.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(FluxLimiter3d.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(FluxLimiter3d.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(FluxLimiter3d.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(FluxLimiter3d.o): /usr/include/bits/stdio_lim.h
$(B)(FluxLimiter3d.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FluxLimiter3d.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FluxLimiter3d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FluxLimiter3d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FluxLimiter3d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FluxLimiter3d.o): /usr/include/sys/sysmacros.h
$(B)(FluxLimiter3d.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FluxLimiter3d.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(FluxLimiter3d.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(FluxLimiter3d.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(FluxLimiter3d.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(FluxLimiter3d.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(FluxLimiter3d.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(FluxLimiter3d.o): /usr/include/ctype.h /usr/include/math.h
$(B)(FluxLimiter3d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(FluxLimiter3d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(FluxLimiter3d.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(FluxLimiter3d.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(FluxLimiter3d.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(FluxLimiter3d.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(FluxLimiterDriver.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(FluxLimiterDriver.o): /usr/include/stdio.h /usr/include/features.h
$(B)(FluxLimiterDriver.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(FluxLimiterDriver.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(FluxLimiterDriver.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(FluxLimiterDriver.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(FluxLimiterDriver.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(FluxLimiterDriver.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(FluxLimiterDriver.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(FluxLimiterDriver.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(FluxLimiterDriver.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(FluxLimiterDriver.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(FluxLimiterDriver.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(FluxLimiterDriver.o): /usr/include/sys/sysmacros.h
$(B)(FluxLimiterDriver.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(FluxLimiterDriver.o): /usr/include/sys/times.h ../../includes/irsctl.h
$(B)(FluxLimiterDriver.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(FluxLimiterDriver.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(FluxLimiterDriver.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(FluxLimiterDriver.o): ../../includes/BoundaryCondition.h
$(B)(FluxLimiterDriver.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(FluxLimiterDriver.o): /usr/include/ctype.h /usr/include/math.h
$(B)(FluxLimiterDriver.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(FluxLimiterDriver.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(FluxLimiterDriver.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(FluxLimiterDriver.o): ../../includes/RadiationData.h
$(B)(FluxLimiterDriver.o): ../../includes/BlockMapping.h
$(B)(FluxLimiterDriver.o): ../../includes/BndMapping.h
$(B)(FluxLimiterDriver.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(FluxLimiterDriver.o): ../../includes/irsgen.h ../../includes/NodeList.h
$(B)(FluxLimiterDriver.o): ../../includes/Extents.h ../../includes/FunctionTimer.h
$(B)(GefaGedi.o): /usr/include/math.h /usr/include/features.h
$(B)(GefaGedi.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(GefaGedi.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(GefaGedi.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(GefaGedi.o): /usr/include/bits/mathcalls.h ../../includes/irs.h
$(B)(GefaGedi.o): /usr/include/stdio.h /usr/include/bits/types.h
$(B)(GefaGedi.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(GefaGedi.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(GefaGedi.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(GefaGedi.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(GefaGedi.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(GefaGedi.o): /usr/include/time.h /usr/include/endian.h
$(B)(GefaGedi.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(GefaGedi.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(GefaGedi.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(GefaGedi.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(GefaGedi.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(GefaGedi.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(GefaGedi.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(GefaGedi.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(GefaGedi.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(GefaGedi.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(GefaGedi.o): /usr/include/ctype.h /usr/include/string.h /usr/include/malloc.h
$(B)(GefaGedi.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(GefaGedi.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(GefaGedi.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(KpAnalytic.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(KpAnalytic.o): /usr/include/stdio.h /usr/include/features.h
$(B)(KpAnalytic.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(KpAnalytic.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(KpAnalytic.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(KpAnalytic.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(KpAnalytic.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(KpAnalytic.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(KpAnalytic.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(KpAnalytic.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(KpAnalytic.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(KpAnalytic.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(KpAnalytic.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(KpAnalytic.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(KpAnalytic.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(KpAnalytic.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(KpAnalytic.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(KpAnalytic.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(KpAnalytic.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(KpAnalytic.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(KpAnalytic.o): /usr/include/ctype.h /usr/include/math.h
$(B)(KpAnalytic.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(KpAnalytic.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(KpAnalytic.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(KpAnalytic.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(KpAnalytic.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(KpAnalytic.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(KpAnalytic.o): ../../includes/DiffusionData.h ../../includes/FunctionTimer.h
$(B)(KrAnalytic.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(KrAnalytic.o): /usr/include/stdio.h /usr/include/features.h
$(B)(KrAnalytic.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(KrAnalytic.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(KrAnalytic.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(KrAnalytic.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(KrAnalytic.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(KrAnalytic.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(KrAnalytic.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(KrAnalytic.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(KrAnalytic.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(KrAnalytic.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(KrAnalytic.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(KrAnalytic.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(KrAnalytic.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(KrAnalytic.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(KrAnalytic.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(KrAnalytic.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(KrAnalytic.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(KrAnalytic.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(KrAnalytic.o): /usr/include/ctype.h /usr/include/math.h
$(B)(KrAnalytic.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(KrAnalytic.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(KrAnalytic.o): /usr/include/malloc.h ../../includes/irseos.h
$(B)(KrAnalytic.o): ../../includes/Region.h ../../includes/Thermo.h
$(B)(KrAnalytic.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(KrAnalytic.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(KrAnalytic.o): ../../includes/DiffusionData.h ../../includes/FunctionTimer.h
$(B)(MatrixSolve.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(MatrixSolve.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(MatrixSolve.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(MatrixSolve.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(MatrixSolve.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(MatrixSolve.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(MatrixSolve.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(MatrixSolve.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(MatrixSolve.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(MatrixSolve.o): /usr/include/time.h /usr/include/endian.h
$(B)(MatrixSolve.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(MatrixSolve.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(MatrixSolve.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(MatrixSolve.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(MatrixSolve.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(MatrixSolve.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(MatrixSolve.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(MatrixSolve.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(MatrixSolve.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(MatrixSolve.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(MatrixSolve.o): /usr/include/ctype.h /usr/include/math.h
$(B)(MatrixSolve.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(MatrixSolve.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(MatrixSolve.o): /usr/include/malloc.h ../../includes/irssys.h
$(B)(MatrixSolve.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(MatrixSolve.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(MatrixSolve.o): ../../includes/Extents.h ../../includes/irstdiff.h
$(B)(MatrixSolve.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(MatrixSolve.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(MatrixSolve.o): ../../includes/Region.h ../../includes/TimeStepControl.h
$(B)(MatrixSolve.o): ../../includes/pardo.h
$(B)(MatterConduction.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(MatterConduction.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(MatterConduction.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(MatterConduction.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(MatterConduction.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(MatterConduction.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(MatterConduction.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(MatterConduction.o): /usr/include/bits/stdio_lim.h
$(B)(MatterConduction.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(MatterConduction.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(MatterConduction.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(MatterConduction.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(MatterConduction.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(MatterConduction.o): /usr/include/sys/sysmacros.h
$(B)(MatterConduction.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(MatterConduction.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(MatterConduction.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(MatterConduction.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(MatterConduction.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(MatterConduction.o): ../../includes/Source.h
$(B)(MatterConduction.o): ../../includes/BoundaryCondition.h
$(B)(MatterConduction.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(MatterConduction.o): /usr/include/ctype.h /usr/include/math.h
$(B)(MatterConduction.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(MatterConduction.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(MatterConduction.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(MatterConduction.o): ../../includes/RadiationData.h
$(B)(MatterConduction.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(MatterConduction.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(MatterConduction.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(MatterConduction.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(MatterConduction.o): ../../includes/Extents.h ../../includes/pardo.h
$(B)(MatterDiagonal.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(MatterDiagonal.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(MatterDiagonal.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(MatterDiagonal.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(MatterDiagonal.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(MatterDiagonal.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(MatterDiagonal.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(MatterDiagonal.o): /usr/include/bits/stdio_lim.h
$(B)(MatterDiagonal.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(MatterDiagonal.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(MatterDiagonal.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(MatterDiagonal.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(MatterDiagonal.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(MatterDiagonal.o): /usr/include/sys/sysmacros.h
$(B)(MatterDiagonal.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(MatterDiagonal.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(MatterDiagonal.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(MatterDiagonal.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(MatterDiagonal.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(MatterDiagonal.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(MatterDiagonal.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(MatterDiagonal.o): /usr/include/ctype.h /usr/include/math.h
$(B)(MatterDiagonal.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(MatterDiagonal.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(MatterDiagonal.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(MatterDiagonal.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(MatterDiagonal.o): ../../includes/RadiationData.h
$(B)(MatterDiagonal.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(MatterDiagonal.o): ../../includes/DiffusionData.h ../../includes/irsbndry.h
$(B)(MatterDiagonal.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(MatterDiagonal.o): ../../includes/FunctionTimer.h ../../includes/NodeList.h
$(B)(MatterDiagonal.o): ../../includes/Extents.h
$(B)(MatterWainwright.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(MatterWainwright.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(MatterWainwright.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(MatterWainwright.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(MatterWainwright.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(MatterWainwright.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(MatterWainwright.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(MatterWainwright.o): /usr/include/bits/stdio_lim.h
$(B)(MatterWainwright.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(MatterWainwright.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(MatterWainwright.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(MatterWainwright.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(MatterWainwright.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(MatterWainwright.o): /usr/include/sys/sysmacros.h
$(B)(MatterWainwright.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(MatterWainwright.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(MatterWainwright.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(MatterWainwright.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(MatterWainwright.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(MatterWainwright.o): ../../includes/Source.h
$(B)(MatterWainwright.o): ../../includes/BoundaryCondition.h
$(B)(MatterWainwright.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(MatterWainwright.o): /usr/include/ctype.h /usr/include/math.h
$(B)(MatterWainwright.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(MatterWainwright.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(MatterWainwright.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(MatterWainwright.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(MatterWainwright.o): ../../includes/RadiationData.h
$(B)(MatterWainwright.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(MatterWainwright.o): ../../includes/DiffusionData.h
$(B)(MatterWainwright.o): ../../includes/FunctionTimer.h
$(B)(RadiationMemory.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(RadiationMemory.o): /usr/include/stdio.h /usr/include/features.h
$(B)(RadiationMemory.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(RadiationMemory.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(RadiationMemory.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(RadiationMemory.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(RadiationMemory.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(RadiationMemory.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(RadiationMemory.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(RadiationMemory.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(RadiationMemory.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(RadiationMemory.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(RadiationMemory.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(RadiationMemory.o): /usr/include/sys/sysmacros.h
$(B)(RadiationMemory.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(RadiationMemory.o): /usr/include/sys/times.h ../../includes/irsctl.h
$(B)(RadiationMemory.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(RadiationMemory.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(RadiationMemory.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(RadiationMemory.o): ../../includes/BoundaryCondition.h
$(B)(RadiationMemory.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(RadiationMemory.o): /usr/include/ctype.h /usr/include/math.h
$(B)(RadiationMemory.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(RadiationMemory.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(RadiationMemory.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(RadiationMemory.o): ../../includes/RadiationData.h
$(B)(RadiationMemory.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(RadiationMemory.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(RadiationMemory.o): ../../includes/ProblemArray.h ../../includes/pardo.h
$(B)(RadiationSourceBC.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(RadiationSourceBC.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(RadiationSourceBC.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(RadiationSourceBC.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(RadiationSourceBC.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(RadiationSourceBC.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(RadiationSourceBC.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(RadiationSourceBC.o): /usr/include/bits/stdio_lim.h
$(B)(RadiationSourceBC.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(RadiationSourceBC.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(RadiationSourceBC.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(RadiationSourceBC.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(RadiationSourceBC.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(RadiationSourceBC.o): /usr/include/sys/sysmacros.h
$(B)(RadiationSourceBC.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(RadiationSourceBC.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(RadiationSourceBC.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(RadiationSourceBC.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(RadiationSourceBC.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(RadiationSourceBC.o): ../../includes/Source.h
$(B)(RadiationSourceBC.o): ../../includes/BoundaryCondition.h
$(B)(RadiationSourceBC.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(RadiationSourceBC.o): /usr/include/ctype.h /usr/include/math.h
$(B)(RadiationSourceBC.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(RadiationSourceBC.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(RadiationSourceBC.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(RadiationSourceBC.o): ../../includes/RadiationData.h
$(B)(RadiationSourceBC.o): ../../includes/BlockMapping.h
$(B)(RadiationSourceBC.o): ../../includes/BndMapping.h
$(B)(RadiationSourceBC.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(RadiationSourceBC.o): ../../includes/irsrgst.h ../../includes/FunctionTimer.h
$(B)(RegionTable.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(RegionTable.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(RegionTable.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(RegionTable.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(RegionTable.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(RegionTable.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(RegionTable.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(RegionTable.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(RegionTable.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(RegionTable.o): /usr/include/time.h /usr/include/endian.h
$(B)(RegionTable.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(RegionTable.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(RegionTable.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(RegionTable.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(RegionTable.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(RegionTable.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(RegionTable.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(RegionTable.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(RegionTable.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(RegionTable.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(RegionTable.o): /usr/include/ctype.h /usr/include/math.h
$(B)(RegionTable.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(RegionTable.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(RegionTable.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(RegionTable.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(RegionTable.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(RegionTable.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(SetFaceTemperature.o): /usr/include/math.h /usr/include/features.h
$(B)(SetFaceTemperature.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(SetFaceTemperature.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(SetFaceTemperature.o): /usr/include/bits/huge_val.h
$(B)(SetFaceTemperature.o): /usr/include/bits/mathdef.h
$(B)(SetFaceTemperature.o): /usr/include/bits/mathcalls.h ../../includes/irs.h
$(B)(SetFaceTemperature.o): /usr/include/stdio.h /usr/include/bits/types.h
$(B)(SetFaceTemperature.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(SetFaceTemperature.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(SetFaceTemperature.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(SetFaceTemperature.o): /usr/include/bits/stdio_lim.h
$(B)(SetFaceTemperature.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(SetFaceTemperature.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(SetFaceTemperature.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(SetFaceTemperature.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(SetFaceTemperature.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(SetFaceTemperature.o): /usr/include/sys/sysmacros.h
$(B)(SetFaceTemperature.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(SetFaceTemperature.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(SetFaceTemperature.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(SetFaceTemperature.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(SetFaceTemperature.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(SetFaceTemperature.o): ../../includes/Source.h
$(B)(SetFaceTemperature.o): ../../includes/BoundaryCondition.h
$(B)(SetFaceTemperature.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(SetFaceTemperature.o): /usr/include/ctype.h /usr/include/string.h
$(B)(SetFaceTemperature.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(SetFaceTemperature.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(SetFaceTemperature.o): ../../includes/RadiationData.h
$(B)(SetFaceTemperature.o): ../../includes/BlockMapping.h
$(B)(SetFaceTemperature.o): ../../includes/BndMapping.h
$(B)(SetFaceTemperature.o): ../../includes/DiffusionData.h
$(B)(SetFaceTemperature.o): ../../includes/FunctionTimer.h
$(B)(bound_free.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(bound_free.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(bound_free.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(bound_free.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(bound_free.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(bound_free.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(bound_free.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(bound_free.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(bound_free.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(bound_free.o): /usr/include/time.h /usr/include/endian.h
$(B)(bound_free.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(bound_free.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(bound_free.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(bound_free.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(bound_free.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(bound_free.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(bound_free.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(bound_free.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(bound_free.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(bound_free.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(bound_free.o): /usr/include/ctype.h /usr/include/math.h
$(B)(bound_free.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(bound_free.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(bound_free.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(bound_free.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(bound_free.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(bound_free.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(cblkbc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(cblkbc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(cblkbc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(cblkbc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(cblkbc.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(cblkbc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(cblkbc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(cblkbc.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(cblkbc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(cblkbc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(cblkbc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(cblkbc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(cblkbc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(cblkbc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(cblkbc.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(cblkbc.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(cblkbc.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(cblkbc.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(cblkbc.o): /usr/include/ctype.h /usr/include/math.h
$(B)(cblkbc.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(cblkbc.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(cblkbc.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(cblkbc.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(cblkbc.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(cblkbc.o): ../../includes/Region.h
$(B)(cblkbc2.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(cblkbc2.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(cblkbc2.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(cblkbc2.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(cblkbc2.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(cblkbc2.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(cblkbc2.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(cblkbc2.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(cblkbc2.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(cblkbc2.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(cblkbc2.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(cblkbc2.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(cblkbc2.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(cblkbc2.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(cblkbc2.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(cblkbc2.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(cblkbc2.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(cblkbc2.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(cblkbc2.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(cblkbc2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(cblkbc2.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(cblkbc2.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(cblkbc2.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(cblkbc2.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(cblkbc2.o): ../../includes/Region.h
$(B)(cblkbc3.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(cblkbc3.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(cblkbc3.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(cblkbc3.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(cblkbc3.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(cblkbc3.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(cblkbc3.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(cblkbc3.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(cblkbc3.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(cblkbc3.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(cblkbc3.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(cblkbc3.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(cblkbc3.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(cblkbc3.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(cblkbc3.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(cblkbc3.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(cblkbc3.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(cblkbc3.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(cblkbc3.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(cblkbc3.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(cblkbc3.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(cblkbc3.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(cblkbc3.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(cblkbc3.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(cblkbc3.o): ../../includes/Region.h
$(B)(diagonal.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(diagonal.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(diagonal.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(diagonal.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(diagonal.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(diagonal.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(diagonal.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(diagonal.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(diagonal.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(diagonal.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(diagonal.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(diagonal.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(diagonal.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(diagonal.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(diagonal.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(diagonal.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(diagonal.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(diagonal.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(diagonal.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(diagonal.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(diagonal.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(diagonal.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(diagonal.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(diagonal.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(diagonal.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(diagonal.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(diagonal.o): ../../includes/irsbndry.h ../../includes/irscom.h
$(B)(diagonal.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(diagonal.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(diff1g.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(diff1g.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(diff1g.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(diff1g.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(diff1g.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(diff1g.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(diff1g.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(diff1g.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(diff1g.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(diff1g.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(diff1g.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(diff1g.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(diff1g.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(diff1g.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(diff1g.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(diff1g.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(diff1g.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(diff1g.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(diff1g.o): /usr/include/ctype.h /usr/include/math.h
$(B)(diff1g.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(diff1g.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(diff1g.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(diff1g.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(diff1g.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(diff1g.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(diff1g.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(diff1g.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(divgrad2.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(divgrad2.o): /usr/include/stdio.h /usr/include/features.h
$(B)(divgrad2.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(divgrad2.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(divgrad2.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(divgrad2.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(divgrad2.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(divgrad2.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(divgrad2.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(divgrad2.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(divgrad2.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(divgrad2.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(divgrad2.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(divgrad2.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(divgrad2.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(divgrad2.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(divgrad2.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(divgrad2.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(divgrad2.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(divgrad2.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(divgrad2.o): /usr/include/ctype.h /usr/include/math.h
$(B)(divgrad2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(divgrad2.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(divgrad2.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(divgrad2.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(divgrad2.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(divgrad2.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(divgrad3.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(divgrad3.o): /usr/include/stdio.h /usr/include/features.h
$(B)(divgrad3.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(divgrad3.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(divgrad3.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(divgrad3.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(divgrad3.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(divgrad3.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(divgrad3.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(divgrad3.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(divgrad3.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(divgrad3.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(divgrad3.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(divgrad3.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(divgrad3.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(divgrad3.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(divgrad3.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(divgrad3.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(divgrad3.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(divgrad3.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(divgrad3.o): /usr/include/ctype.h /usr/include/math.h
$(B)(divgrad3.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(divgrad3.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(divgrad3.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(divgrad3.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(divgrad3.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(divgrad3.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(divgradpert2d.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(divgradpert2d.o): /usr/include/stdio.h /usr/include/features.h
$(B)(divgradpert2d.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(divgradpert2d.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(divgradpert2d.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(divgradpert2d.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(divgradpert2d.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(divgradpert2d.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(divgradpert2d.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(divgradpert2d.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(divgradpert2d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(divgradpert2d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(divgradpert2d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(divgradpert2d.o): /usr/include/sys/sysmacros.h
$(B)(divgradpert2d.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(divgradpert2d.o): /usr/include/sys/times.h ../../includes/irsctl.h
$(B)(divgradpert2d.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(divgradpert2d.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(divgradpert2d.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(divgradpert2d.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(divgradpert2d.o): ../../includes/mach.h /usr/include/ctype.h
$(B)(divgradpert2d.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(divgradpert2d.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(divgradpert2d.o): /usr/include/string.h /usr/include/malloc.h
$(B)(divgradpert2d.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(divgradpert2d.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(divgradpert2d.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(divgradpert2d.o): ../../includes/FunctionTimer.h
$(B)(divgradpert3d.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(divgradpert3d.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(divgradpert3d.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(divgradpert3d.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(divgradpert3d.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(divgradpert3d.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(divgradpert3d.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(divgradpert3d.o): /usr/include/bits/stdio_lim.h
$(B)(divgradpert3d.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(divgradpert3d.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(divgradpert3d.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(divgradpert3d.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(divgradpert3d.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(divgradpert3d.o): /usr/include/sys/sysmacros.h
$(B)(divgradpert3d.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(divgradpert3d.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(divgradpert3d.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(divgradpert3d.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(divgradpert3d.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(divgradpert3d.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(divgradpert3d.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(divgradpert3d.o): /usr/include/ctype.h /usr/include/math.h
$(B)(divgradpert3d.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(divgradpert3d.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(divgradpert3d.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(divgradpert3d.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(divgradpert3d.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(divgradpert3d.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(geteicouple.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(geteicouple.o): /usr/include/stdio.h /usr/include/features.h
$(B)(geteicouple.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(geteicouple.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(geteicouple.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(geteicouple.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(geteicouple.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(geteicouple.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(geteicouple.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(geteicouple.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(geteicouple.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(geteicouple.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(geteicouple.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(geteicouple.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(geteicouple.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(geteicouple.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(geteicouple.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(geteicouple.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(geteicouple.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(geteicouple.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(geteicouple.o): /usr/include/ctype.h /usr/include/math.h
$(B)(geteicouple.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(geteicouple.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(geteicouple.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(geteicouple.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(geteicouple.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(geteicouple.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(geteicouple.o): ../../includes/FunctionTimer.h
$(B)(gettfzstar.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(gettfzstar.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(gettfzstar.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(gettfzstar.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(gettfzstar.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(gettfzstar.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(gettfzstar.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(gettfzstar.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(gettfzstar.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(gettfzstar.o): /usr/include/time.h /usr/include/endian.h
$(B)(gettfzstar.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(gettfzstar.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(gettfzstar.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(gettfzstar.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(gettfzstar.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(gettfzstar.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(gettfzstar.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(gettfzstar.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(gettfzstar.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(gettfzstar.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(gettfzstar.o): /usr/include/ctype.h /usr/include/math.h
$(B)(gettfzstar.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(gettfzstar.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(gettfzstar.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(gettfzstar.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(gettfzstar.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(gettfzstar.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(getzabar0.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(getzabar0.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(getzabar0.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(getzabar0.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(getzabar0.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(getzabar0.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(getzabar0.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(getzabar0.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(getzabar0.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(getzabar0.o): /usr/include/time.h /usr/include/endian.h
$(B)(getzabar0.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(getzabar0.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(getzabar0.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(getzabar0.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(getzabar0.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(getzabar0.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(getzabar0.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(getzabar0.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(getzabar0.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(getzabar0.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(getzabar0.o): /usr/include/ctype.h /usr/include/math.h
$(B)(getzabar0.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(getzabar0.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(getzabar0.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(getzabar0.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(getzabar0.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(getzabar0.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(gtkappabnd.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(gtkappabnd.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(gtkappabnd.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(gtkappabnd.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(gtkappabnd.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(gtkappabnd.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(gtkappabnd.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(gtkappabnd.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(gtkappabnd.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(gtkappabnd.o): /usr/include/time.h /usr/include/endian.h
$(B)(gtkappabnd.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(gtkappabnd.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(gtkappabnd.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(gtkappabnd.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(gtkappabnd.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(gtkappabnd.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(gtkappabnd.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(gtkappabnd.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(gtkappabnd.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(gtkappabnd.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(gtkappabnd.o): /usr/include/ctype.h /usr/include/math.h
$(B)(gtkappabnd.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(gtkappabnd.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(gtkappabnd.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(gtkappabnd.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(gtkappabnd.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(gtkappabnd.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(gtkappabnd.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(gtkappabnd.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(gtkappabnd.o): ../../includes/ProblemArray.h
$(B)(kapmlt.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(kapmlt.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(kapmlt.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(kapmlt.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(kapmlt.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(kapmlt.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(kapmlt.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(kapmlt.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(kapmlt.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(kapmlt.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(kapmlt.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(kapmlt.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(kapmlt.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(kapmlt.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(kapmlt.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(kapmlt.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(kapmlt.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(kapmlt.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(kapmlt.o): /usr/include/ctype.h /usr/include/math.h
$(B)(kapmlt.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(kapmlt.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(kapmlt.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(kapmlt.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(kapmlt.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(kapmlt.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(newMatrix.o): ../../includes/irsdefs.h ../../includes/irs.h
$(B)(newMatrix.o): /usr/include/stdio.h /usr/include/features.h
$(B)(newMatrix.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(newMatrix.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(newMatrix.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(newMatrix.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(newMatrix.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(newMatrix.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(newMatrix.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(newMatrix.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(newMatrix.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(newMatrix.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(newMatrix.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(newMatrix.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(newMatrix.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(newMatrix.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(newMatrix.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(newMatrix.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(newMatrix.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(newMatrix.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(newMatrix.o): /usr/include/ctype.h /usr/include/math.h
$(B)(newMatrix.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(newMatrix.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(newMatrix.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(newMatrix.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(newMatrix.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(newMatrix.o): ../../includes/Region.h
$(B)(norml2.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(norml2.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(norml2.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(norml2.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(norml2.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(norml2.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(norml2.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(norml2.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(norml2.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(norml2.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(norml2.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(norml2.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(norml2.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(norml2.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(norml2.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(norml2.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(norml2.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(norml2.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(norml2.o): /usr/include/ctype.h /usr/include/math.h
$(B)(norml2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(norml2.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(norml2.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(norml2.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(norml2.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(norml2.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(norml2.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(norml2.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(opac2t.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(opac2t.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(opac2t.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(opac2t.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(opac2t.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(opac2t.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(opac2t.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(opac2t.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(opac2t.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(opac2t.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(opac2t.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(opac2t.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(opac2t.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(opac2t.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(opac2t.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(opac2t.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(opac2t.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(opac2t.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(opac2t.o): /usr/include/ctype.h /usr/include/math.h
$(B)(opac2t.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(opac2t.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(opac2t.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(opac2t.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(opac2t.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(opac2t.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(opac2t.o): ../../includes/FunctionTimer.h
$(B)(opaclmt.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(opaclmt.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(opaclmt.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(opaclmt.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(opaclmt.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(opaclmt.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(opaclmt.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(opaclmt.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(opaclmt.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(opaclmt.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(opaclmt.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(opaclmt.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(opaclmt.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(opaclmt.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(opaclmt.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(opaclmt.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(opaclmt.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(opaclmt.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(opaclmt.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(opaclmt.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(opaclmt.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(opaclmt.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(opaclmt.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(opaclmt.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(opaclmt.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(planck_opacity.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(planck_opacity.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(planck_opacity.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(planck_opacity.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(planck_opacity.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(planck_opacity.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(planck_opacity.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(planck_opacity.o): /usr/include/bits/stdio_lim.h
$(B)(planck_opacity.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(planck_opacity.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(planck_opacity.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(planck_opacity.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(planck_opacity.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(planck_opacity.o): /usr/include/sys/sysmacros.h
$(B)(planck_opacity.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(planck_opacity.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(planck_opacity.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(planck_opacity.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(planck_opacity.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(planck_opacity.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(planck_opacity.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(planck_opacity.o): /usr/include/ctype.h /usr/include/math.h
$(B)(planck_opacity.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(planck_opacity.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(planck_opacity.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(planck_opacity.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(planck_opacity.o): ../../includes/RadiationData.h
$(B)(planck_opacity.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(planck_opacity.o): ../../includes/DiffusionData.h
$(B)(planck_opacity.o): ../../includes/FunctionTimer.h
$(B)(radfree.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(radfree.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(radfree.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(radfree.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(radfree.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(radfree.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(radfree.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(radfree.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(radfree.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(radfree.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(radfree.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(radfree.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(radfree.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(radfree.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(radfree.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(radfree.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(radfree.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(radfree.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(radfree.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(radfree.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(radfree.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(radfree.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(radfree.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(radfree.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(radfree.o): ../../includes/Region.h ../../includes/ProblemArray.h
$(B)(radfree.o): ../../includes/pardo.h
$(B)(radinit.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(radinit.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(radinit.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(radinit.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(radinit.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(radinit.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(radinit.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(radinit.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(radinit.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(radinit.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(radinit.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(radinit.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(radinit.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(radinit.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(radinit.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(radinit.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(radinit.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(radinit.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(radinit.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(radinit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(radinit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(radinit.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(radinit.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(radinit.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(radinit.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(radinit.o): ../../includes/FunctionTimer.h ../../includes/pardo.h
$(B)(rdiff.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rdiff.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rdiff.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rdiff.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rdiff.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(rdiff.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(rdiff.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(rdiff.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(rdiff.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rdiff.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rdiff.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rdiff.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rdiff.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rdiff.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rdiff.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(rdiff.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(rdiff.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(rdiff.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(rdiff.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(rdiff.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(rdiff.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irscom.h
$(B)(rdiff.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(rdiff.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rdiff.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(rdiff.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(rdiff.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(rdiff.o): ../../includes/pardo.h
$(B)(rdiffbc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rdiffbc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rdiffbc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rdiffbc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rdiffbc.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(rdiffbc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(rdiffbc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(rdiffbc.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(rdiffbc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rdiffbc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rdiffbc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rdiffbc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rdiffbc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rdiffbc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rdiffbc.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rdiffbc.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rdiffbc.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rdiffbc.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rdiffbc.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rdiffbc.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rdiffbc.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rdiffbc.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(rdiffbc.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(rdiffbc.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rdiffbc.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(rdiffbc.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(rdiffbc.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(rdiffbc2.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rdiffbc2.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rdiffbc2.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rdiffbc2.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rdiffbc2.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(rdiffbc2.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(rdiffbc2.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(rdiffbc2.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(rdiffbc2.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(rdiffbc2.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rdiffbc2.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rdiffbc2.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rdiffbc2.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rdiffbc2.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rdiffbc2.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rdiffbc2.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rdiffbc2.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rdiffbc2.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rdiffbc2.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rdiffbc2.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rdiffbc2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rdiffbc2.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rdiffbc2.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(rdiffbc2.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rdiffbc2.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rdiffbc2.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(rdiffbc3.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rdiffbc3.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rdiffbc3.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rdiffbc3.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rdiffbc3.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(rdiffbc3.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(rdiffbc3.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(rdiffbc3.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(rdiffbc3.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(rdiffbc3.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rdiffbc3.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rdiffbc3.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rdiffbc3.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rdiffbc3.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rdiffbc3.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rdiffbc3.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rdiffbc3.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rdiffbc3.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rdiffbc3.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rdiffbc3.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rdiffbc3.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rdiffbc3.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rdiffbc3.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(rdiffbc3.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rdiffbc3.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rdiffbc3.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(rdiffset.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rdiffset.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rdiffset.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rdiffset.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rdiffset.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(rdiffset.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(rdiffset.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(rdiffset.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(rdiffset.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(rdiffset.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rdiffset.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rdiffset.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rdiffset.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rdiffset.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rdiffset.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rdiffset.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rdiffset.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rdiffset.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rdiffset.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rdiffset.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rdiffset.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rdiffset.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rdiffset.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(rdiffset.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(rdiffset.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rdiffset.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rdiffset.o): ../../includes/FunctionTimer.h
$(B)(rdiffsrc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rdiffsrc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rdiffsrc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rdiffsrc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rdiffsrc.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(rdiffsrc.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(rdiffsrc.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(rdiffsrc.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(rdiffsrc.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(rdiffsrc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rdiffsrc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rdiffsrc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rdiffsrc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rdiffsrc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rdiffsrc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rdiffsrc.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rdiffsrc.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rdiffsrc.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rdiffsrc.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rdiffsrc.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rdiffsrc.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rdiffsrc.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rdiffsrc.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(rdiffsrc.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rdiffsrc.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rdiffsrc.o): ../../includes/Region.h ../../includes/irscom.h
$(B)(rdiffsrc.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(rdiffsrc.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rdiffsrc.o): ../../includes/irssrc.h
$(B)(reicouple.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(reicouple.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(reicouple.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(reicouple.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(reicouple.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(reicouple.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(reicouple.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(reicouple.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(reicouple.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(reicouple.o): /usr/include/time.h /usr/include/endian.h
$(B)(reicouple.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(reicouple.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(reicouple.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(reicouple.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(reicouple.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(reicouple.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(reicouple.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(reicouple.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(reicouple.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(reicouple.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(reicouple.o): /usr/include/ctype.h /usr/include/math.h
$(B)(reicouple.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(reicouple.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(reicouple.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(reicouple.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(reicouple.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(reicouple.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(retransfer.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(retransfer.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(retransfer.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(retransfer.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(retransfer.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(retransfer.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(retransfer.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(retransfer.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(retransfer.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(retransfer.o): /usr/include/time.h /usr/include/endian.h
$(B)(retransfer.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(retransfer.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(retransfer.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(retransfer.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(retransfer.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(retransfer.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(retransfer.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(retransfer.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(retransfer.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(retransfer.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(retransfer.o): /usr/include/ctype.h /usr/include/math.h
$(B)(retransfer.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(retransfer.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(retransfer.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(retransfer.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(retransfer.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(retransfer.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(retransfer.o): ../../includes/irsbndry.h ../../includes/irscom.h
$(B)(retransfer.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(retransfer.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rmatmult.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rmatmult.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rmatmult.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rmatmult.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rmatmult.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(rmatmult.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(rmatmult.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(rmatmult.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(rmatmult.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(rmatmult.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rmatmult.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rmatmult.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rmatmult.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rmatmult.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rmatmult.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rmatmult.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rmatmult.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rmatmult.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rmatmult.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rmatmult.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rmatmult.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rmatmult.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rmatmult.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(rmatmult.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rmatmult.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rmatmult.o): ../../includes/Region.h ../../includes/irscom.h
$(B)(rmatmult.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(rmatmult.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rmatmult2.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(rmatmult2.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(rmatmult2.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(rmatmult2.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(rmatmult2.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(rmatmult2.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(rmatmult2.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(rmatmult2.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(rmatmult2.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(rmatmult2.o): /usr/include/time.h /usr/include/endian.h
$(B)(rmatmult2.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(rmatmult2.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(rmatmult2.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(rmatmult2.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(rmatmult2.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(rmatmult2.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(rmatmult2.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(rmatmult2.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(rmatmult2.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(rmatmult2.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(rmatmult2.o): /usr/include/ctype.h /usr/include/math.h
$(B)(rmatmult2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rmatmult2.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rmatmult2.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(rmatmult2.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rmatmult2.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rmatmult2.o): ../../includes/Region.h ../../includes/irscom.h
$(B)(rmatmult2.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(rmatmult2.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rmatmult3.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(rmatmult3.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(rmatmult3.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(rmatmult3.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(rmatmult3.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(rmatmult3.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(rmatmult3.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(rmatmult3.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(rmatmult3.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(rmatmult3.o): /usr/include/time.h /usr/include/endian.h
$(B)(rmatmult3.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(rmatmult3.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(rmatmult3.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(rmatmult3.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(rmatmult3.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(rmatmult3.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(rmatmult3.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(rmatmult3.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(rmatmult3.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(rmatmult3.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(rmatmult3.o): /usr/include/ctype.h /usr/include/math.h
$(B)(rmatmult3.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rmatmult3.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rmatmult3.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(rmatmult3.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rmatmult3.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rmatmult3.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(rsrcbc.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rsrcbc.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rsrcbc.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rsrcbc.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rsrcbc.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(rsrcbc.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(rsrcbc.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(rsrcbc.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(rsrcbc.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rsrcbc.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rsrcbc.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rsrcbc.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rsrcbc.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rsrcbc.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rsrcbc.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(rsrcbc.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(rsrcbc.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(rsrcbc.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(rsrcbc.o): /usr/include/ctype.h /usr/include/math.h
$(B)(rsrcbc.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rsrcbc.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rsrcbc.o): /usr/include/malloc.h ../../includes/irscom.h
$(B)(rsrcbc.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(rsrcbc.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rsrcbc.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(rsrcbc.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(rsrcbc.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(rsrcbc2.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rsrcbc2.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rsrcbc2.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rsrcbc2.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rsrcbc2.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(rsrcbc2.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(rsrcbc2.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(rsrcbc2.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(rsrcbc2.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rsrcbc2.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rsrcbc2.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rsrcbc2.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rsrcbc2.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rsrcbc2.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rsrcbc2.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rsrcbc2.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rsrcbc2.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rsrcbc2.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rsrcbc2.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rsrcbc2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rsrcbc2.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rsrcbc2.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(rsrcbc2.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(rsrcbc2.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(rsrcbc2.o): ../../includes/Region.h ../../includes/irssrc.h
$(B)(rsrcbc2.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rsrcbc3.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(rsrcbc3.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(rsrcbc3.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(rsrcbc3.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(rsrcbc3.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(rsrcbc3.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(rsrcbc3.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(rsrcbc3.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(rsrcbc3.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(rsrcbc3.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(rsrcbc3.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(rsrcbc3.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(rsrcbc3.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(rsrcbc3.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(rsrcbc3.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(rsrcbc3.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(rsrcbc3.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(rsrcbc3.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(rsrcbc3.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(rsrcbc3.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(rsrcbc3.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(rsrcbc3.o): /usr/include/malloc.h ../../includes/irssrc.h
$(B)(rsrcbc3.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(rsrcbc3.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(rsrcbc3.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(rsrcbc3.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(rsrcbc3.o): ../../includes/FunctionTimer.h
$(B)(setpz1.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(setpz1.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(setpz1.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(setpz1.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(setpz1.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setpz1.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setpz1.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setpz1.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(setpz1.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(setpz1.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(setpz1.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(setpz1.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(setpz1.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(setpz1.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(setpz1.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(setpz1.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(setpz1.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(setpz1.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(setpz1.o): /usr/include/ctype.h /usr/include/math.h
$(B)(setpz1.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setpz1.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setpz1.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(setpz1.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(setpz1.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(setpz1.o): ../../includes/Region.h
$(B)(setpz2.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(setpz2.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(setpz2.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(setpz2.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(setpz2.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(setpz2.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(setpz2.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(setpz2.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(setpz2.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(setpz2.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(setpz2.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(setpz2.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(setpz2.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(setpz2.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(setpz2.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(setpz2.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(setpz2.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(setpz2.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(setpz2.o): /usr/include/ctype.h /usr/include/math.h
$(B)(setpz2.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(setpz2.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(setpz2.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(setpz2.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(setpz2.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(setpz2.o): ../../includes/Region.h
$(B)(tblkinit.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(tblkinit.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(tblkinit.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(tblkinit.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(tblkinit.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(tblkinit.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(tblkinit.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(tblkinit.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(tblkinit.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(tblkinit.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(tblkinit.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(tblkinit.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(tblkinit.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(tblkinit.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(tblkinit.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(tblkinit.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(tblkinit.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(tblkinit.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(tblkinit.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(tblkinit.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(tblkinit.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(tblkinit.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(tblkinit.o): /usr/include/malloc.h ../../includes/irstdiff.h
$(B)(tblkinit.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(tblkinit.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(tblkinit.o): ../../includes/Region.h ../../includes/FunctionTimer.h
$(B)(tblkinit.o): ../../includes/irscom.h ../../includes/Combuffer.h
$(B)(tblkinit.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(tblkinit.o): ../../includes/pardo.h
$(B)(tdiff.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(tdiff.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(tdiff.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(tdiff.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(tdiff.o): /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
$(B)(tdiff.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(tdiff.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(tdiff.o): /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h
$(B)(tdiff.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(tdiff.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(tdiff.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(tdiff.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(tdiff.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(tdiff.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(tdiff.o): ../../includes/Rgst.h ../../includes/Hash.h ../../includes/Domain.h
$(B)(tdiff.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(tdiff.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(tdiff.o): ../../includes/Boundary.h ../../includes/mach.h /usr/include/ctype.h
$(B)(tdiff.o): /usr/include/math.h /usr/include/bits/huge_val.h
$(B)(tdiff.o): /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
$(B)(tdiff.o): /usr/include/string.h /usr/include/malloc.h ../../includes/irsgen.h
$(B)(tdiff.o): ../../includes/NodeList.h ../../includes/Extents.h
$(B)(tdiff.o): ../../includes/irsbndry.h ../../includes/irscom.h
$(B)(tdiff.o): ../../includes/Combuffer.h ../../includes/FunctionTimer.h
$(B)(tdiff.o): ../../includes/irstdiff.h ../../includes/RadiationData.h
$(B)(tdiff.o): ../../includes/BlockMapping.h ../../includes/BndMapping.h
$(B)(tdiff.o): ../../includes/DiffusionData.h ../../includes/Region.h
$(B)(tdiff.o): ../../includes/pardo.h
$(B)(teicouple.o): ../../includes/irs.h /usr/include/stdio.h
$(B)(teicouple.o): /usr/include/features.h /usr/include/sys/cdefs.h
$(B)(teicouple.o): /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
$(B)(teicouple.o): /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
$(B)(teicouple.o): /usr/include/bits/typesizes.h /usr/include/libio.h
$(B)(teicouple.o): /usr/include/_G_config.h /usr/include/wchar.h
$(B)(teicouple.o): /usr/include/bits/wchar.h /usr/include/gconv.h
$(B)(teicouple.o): /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
$(B)(teicouple.o): /usr/include/stdlib.h /usr/include/sys/types.h
$(B)(teicouple.o): /usr/include/time.h /usr/include/endian.h
$(B)(teicouple.o): /usr/include/bits/endian.h /usr/include/sys/select.h
$(B)(teicouple.o): /usr/include/bits/select.h /usr/include/bits/sigset.h
$(B)(teicouple.o): /usr/include/bits/time.h /usr/include/sys/sysmacros.h
$(B)(teicouple.o): /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
$(B)(teicouple.o): /usr/include/sys/times.h ../../includes/irsdefs.h
$(B)(teicouple.o): ../../includes/irsctl.h ../../includes/Rgst.h
$(B)(teicouple.o): ../../includes/Hash.h ../../includes/Domain.h
$(B)(teicouple.o): ../../includes/pint.h ../../includes/SpeciesFraction.h
$(B)(teicouple.o): ../../includes/Source.h ../../includes/BoundaryCondition.h
$(B)(teicouple.o): ../../includes/Boundary.h ../../includes/mach.h
$(B)(teicouple.o): /usr/include/ctype.h /usr/include/math.h
$(B)(teicouple.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(teicouple.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(teicouple.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(teicouple.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(teicouple.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(teicouple.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(teicouple.o): ../../includes/FunctionTimer.h
$(B)(zstarcal.o): ../../includes/irs.h /usr/include/stdio.h /usr/include/features.h
$(B)(zstarcal.o): /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
$(B)(zstarcal.o): /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
$(B)(zstarcal.o): /usr/include/bits/types.h /usr/include/bits/typesizes.h
$(B)(zstarcal.o): /usr/include/libio.h /usr/include/_G_config.h
$(B)(zstarcal.o): /usr/include/wchar.h /usr/include/bits/wchar.h
$(B)(zstarcal.o): /usr/include/gconv.h /usr/include/bits/stdio_lim.h
$(B)(zstarcal.o): /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
$(B)(zstarcal.o): /usr/include/sys/types.h /usr/include/time.h
$(B)(zstarcal.o): /usr/include/endian.h /usr/include/bits/endian.h
$(B)(zstarcal.o): /usr/include/sys/select.h /usr/include/bits/select.h
$(B)(zstarcal.o): /usr/include/bits/sigset.h /usr/include/bits/time.h
$(B)(zstarcal.o): /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
$(B)(zstarcal.o): /usr/include/alloca.h /usr/include/sys/times.h
$(B)(zstarcal.o): ../../includes/irsdefs.h ../../includes/irsctl.h
$(B)(zstarcal.o): ../../includes/Rgst.h ../../includes/Hash.h
$(B)(zstarcal.o): ../../includes/Domain.h ../../includes/pint.h
$(B)(zstarcal.o): ../../includes/SpeciesFraction.h ../../includes/Source.h
$(B)(zstarcal.o): ../../includes/BoundaryCondition.h ../../includes/Boundary.h
$(B)(zstarcal.o): ../../includes/mach.h /usr/include/ctype.h /usr/include/math.h
$(B)(zstarcal.o): /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
$(B)(zstarcal.o): /usr/include/bits/mathcalls.h /usr/include/string.h
$(B)(zstarcal.o): /usr/include/malloc.h ../../includes/irsreg.h
$(B)(zstarcal.o): ../../includes/Region.h ../../includes/irstdiff.h
$(B)(zstarcal.o): ../../includes/RadiationData.h ../../includes/BlockMapping.h
$(B)(zstarcal.o): ../../includes/BndMapping.h ../../includes/DiffusionData.h
$(B)(zstarcal.o): ../../includes/FunctionTimer.h
